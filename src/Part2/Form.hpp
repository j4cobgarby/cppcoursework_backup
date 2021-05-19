#ifndef FORM_HPP
#define FORM_HPP

#include "../DisplayableObject.h"
#include <string>
#include <map>
#include <vector>
#include "../DrawingSurface.h"
#include "EventHandler.hpp"
#include <functional>

typedef std::map<std::string, std::string> formcontext_t;

class FormItem;

class Form : public DisplayableObject, public EventHandler {
protected:
    //std::map<std::string, FormItem *> items;
    std::vector<std::pair<std::string, FormItem *>> items;
    FormItem *active_item;
    int active_index;
    int margin;
    int item_spacing;
    int item_height;

public:
    Form(BaseEngine *eng, int x, int y, int w, int h);

    void virtDraw() override;

    void handleMouseDown(int btn, int x, int y) override;
    void handleKeyDown(int btn) override;

    int addItem(FormItem *new_item, std::string id);
    void setActiveItem(int i);
    FormItem *getActiveItem();
    FormItem *getItem(std::string name);
};

class FormItem {
protected:
    Form *container;
    std::string value;
    bool selectable;
    int index;

    void drawActiveMarker(DrawingSurface *surf, int x, int y, int h);
public:
    FormItem(Form *container, int index);

    virtual void draw(DrawingSurface *surf, int x, int y, int w, int h);
    virtual void onClick() {container->setActiveItem(index);}
    virtual void onKey(int key) {}
    virtual std::string getValue() {return value;}
    bool isSelectable() {return selectable;}
};

class FILabel : public FormItem {
protected:
    std::string text;
public:
    FILabel(Form *container, int index, std::string text);

    void draw(DrawingSurface *surf, int x, int y, int w, int h);
};

class FIButton : public FormItem {
protected:
    std::function<std::string(void)> clickFunc;
    std::string text;
public:
    FIButton(Form *container, int index, std::function<std::string(void)>, std::string label);

    void draw(DrawingSurface *surf, int x, int y, int w, int h);
    void onClick();
    void onKey(int key);
};

class FITextField : public FormItem {
protected:
    std::string text;
public:
    FITextField(Form *container, int index);

    void draw(DrawingSurface *surf, int x, int y, int w, int h);
    void onKey(int key);
    std::string getValue() {return text;}
};

#endif