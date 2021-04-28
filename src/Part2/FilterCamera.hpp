#ifndef FILTERCAMERA_HPP
#include "../FilterPoints.h"

class FilterCamera : public FilterPoints {
public: 
    FilterCamera(int xleft, int ytop, int width, int height);

    virtual bool filter(DrawingSurface *surf, int &virtx, int &virty, unsigned int &col) override;

    virtual int filterConvertRealToVirtualXPosition(int realx) override;
    virtual int filterConvertVirtualToRealXPosition(int virtx) override;
    virtual int filterConvertRealToVirtualYPosition(int realy) override;
    virtual int filterConvertVirtualToRealYPosition(int virty) override;

    void setOffset(int x, int y) {
        xleft = x;
        ytop = y;
    }

    void move(int dx, int dy) {
        
    }

    int getX() {return xleft;}
    int getY() {return ytop;}
private:
    int xleft;
    int ytop;
    int width;
    int height;
};

#endif