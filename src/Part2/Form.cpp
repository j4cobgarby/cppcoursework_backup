#include "../header.h"
#include "Form.hpp"
#include "../BaseEngine.h"
#include "ExtraDrawing.hpp"
#include "SDL_keycode.h"
#include "Settings.hpp"
#include <functional>

Form::Form(BaseEngine *eng, int x, int y, int w, int h) :
    DisplayableObject(x, y, eng, w, h, true) {
    setPosition(x, y);
    margin = 15;
    item_spacing = 15;
    item_height = 30;
    active_index = 0;
}

void Form::virtDraw() {
    getEngine()->getForegroundSurface()->drawRectangle(m_iCurrentScreenX, m_iCurrentScreenY, 
        m_iCurrentScreenX + m_iDrawWidth, m_iCurrentScreenY + m_iDrawHeight, 0xffffff);

    int item_offset = 0;
    for (std::pair<std::string, FormItem *> item : items) {
        item.second->draw(getEngine()->getForegroundSurface(), m_iCurrentScreenX+margin, 
            m_iCurrentScreenY+margin+item_offset, 
            m_iDrawWidth-(margin*2), item_height);

        item_offset += item_spacing + item_height;
    }
}

void Form::handleMouseDown(int btn, int x, int y) {
    int item_offset = 0;
    for (std::pair<std::string, FormItem *> item : items) {
        int x1 = m_iCurrentScreenX+margin;
        int y1 = m_iCurrentScreenY+margin+item_offset;
        int x2 = m_iCurrentScreenX+m_iDrawWidth-margin;
        int y2 = m_iCurrentScreenY+margin+item_offset+item_height;

        if (!(x < x1 || x > x2 || y < y1 || y > y2)) {
            item.second->onClick();
            break;
        }

        item_offset += item_spacing + item_height;
    }
}

void Form::handleKeyDown(int btn) {
    if (btn == SDLK_TAB) {
        if (getEngine()->isKeyPressed(SDLK_LSHIFT)) {
            for (int try_i = 0; try_i < items.size(); try_i++) {
                if (active_index-- == 0) active_index = items.size()-1;
                if (items.at(active_index).second->isSelectable()) break;
            }
        } else {
            for (int try_i = 0; try_i < items.size(); try_i++) {
                active_index = (active_index + 1) % items.size();
                if (items.at(active_index).second->isSelectable()) break;
            }
        }
        setActiveItem(active_index);
    }

    active_item->onKey(btn);
}

int Form::addItem(FormItem *new_item, std::string id) {
    std::pair<std::string, FormItem *> new_pair;
    new_pair.first = id;
    new_pair.second = new_item;
    items.push_back(new_pair);
    return items.size()-1;
}

void Form::setActiveItem(int i) {
    active_item = items.at(i).second;
    active_index = i;
    getEngine()->redrawDisplay();
}

FormItem *Form::getActiveItem() {
    return active_item;
}

FormItem *Form::getItem(std::string name) {
    for (std::pair<std::string, FormItem *> it : items) {
        if (it.first == name) return it.second;
    }

    return nullptr;
}

FormItem::FormItem(Form *container, int index) :
    container(container), index(index) {
    selectable = true;
}

void FormItem::draw(DrawingSurface *surf, int x, int y, int w, int h) {
    if (container->getActiveItem() == this) {
        surf->drawRectangle(x, y, x+w, y+h, 0xcec9c2);
        ExtraDrawing::drawRectangleThickOutline(surf, x, y, x+w, y+h, 0x3b938d, 2);
    } else {
        surf->drawRectangle(x, y, x+w, y+h, 0xcec9c2);
        ExtraDrawing::drawRectangleThickOutline(surf, x, y, x+w, y+h, 0x1e1b17, 2);
    }

    drawActiveMarker(surf, x, y, h);
}

void FormItem::drawActiveMarker(DrawingSurface *surf, int x, int y, int h) {
    if (container->getActiveItem() == this) {
        surf->drawTriangle(x-5, y+((float)h/2), x-10, y+10, x-10, y+h-10, 0x000000);
    }
}

FILabel::FILabel(Form *container, int index, std::string text) : FormItem(container, index), text(text) {
    selectable = false;
}

void FILabel::draw(DrawingSurface *surf, int x, int y, int w, int h) {
    surf->drawFastString(x+5, y+2, text.c_str(), 0x000000, container->getEngine()->getFont(UI_FONT, 30));
    drawActiveMarker(surf, x, y, h);
}

FIButton::FIButton(Form *container, int index, std::function<std::string(void)> onClick, std::string label) : 
    FormItem(container, index), clickFunc(onClick), text(label) {
    selectable = true;
}

void FIButton::draw(DrawingSurface *surf, int x, int y, int w, int h) {

    if (container->getActiveItem() == this) {
        surf->drawRectangle(x, y, x+w, y+h, 0x52d3cb);
        ExtraDrawing::drawRectangleThickOutline(surf, x, y, x+w, y+h, 0x125b56, 2);
    } else {
        surf->drawRectangle(x, y, x+w, y+h, 0x3b938d);
        ExtraDrawing::drawRectangleThickOutline(surf, x, y, x+w, y+h, 0x125b56, 2);
    }

    surf->drawFastString(x+5, y+2, text.c_str(), 0x000000, container->getEngine()->getFont(UI_FONT, 30));
    drawActiveMarker(surf, x, y, h);
}

void FIButton::onClick() {
    clickFunc();
}

void FIButton::onKey(int key) {
    if (key == SDLK_SPACE) {
        clickFunc();
    }
}

FITextField::FITextField(Form *container, int index) : FormItem(container, index) {
    text = "";
}

void FITextField::draw(DrawingSurface *surf, int x, int y, int w, int h) {
    surf->drawRectangle(x, y, x+w, y+h, 0xdbd0bc);
    ExtraDrawing::drawRectangleThickOutline(surf, x, y, x+w, y+h, 0x3f3c37, 2);
    surf->drawFastString(x+5, y+2, text.c_str(), 0x000000, container->getEngine()->getFont(UI_FONT, 30));
    drawActiveMarker(surf, x, y, h);
}

void FITextField::onKey(int key) {
    if (key >= SDLK_a && key <= SDLK_z) {
        if (container->getEngine()->isKeyPressed(SDLK_LSHIFT)) {
            text.push_back('A' + (key - SDLK_a));
        } else {
            text.push_back('a' + (key - SDLK_a));
        }
    }

    if (key >= SDLK_0 && key <= SDLK_9) {
        text.push_back('0' + (key - SDLK_0));
    }

    if (key == SDLK_SPACE) {
        text.push_back(' ');
    }

    if (key == SDLK_BACKSPACE) {
        if (text.size() > 0) text.erase(text.size()-1);
    }

    container->getEngine()->redrawDisplay();
}