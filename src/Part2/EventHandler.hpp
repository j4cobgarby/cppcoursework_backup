#ifndef EVENTHANDLER_HPP
#define EVENTHANDLER_HPP

class EventHandler {
public:
    virtual void handleMouseDown(int btn, int x, int y) = 0;
    virtual void handleKeyDown(int key) = 0;
};

#endif