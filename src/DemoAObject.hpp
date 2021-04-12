#ifndef DEMOAOBJECT_HPP
#define DEMOAOBJECT_HPP

#include "BaseEngine.h"
#include "DisplayableObject.h"
#include "MyDemoTileManager.hpp"

class SpaceshipObject : public DisplayableObject {
private:
    float x, y;
    float vel_x, vel_y;
    float theta;
    Psyjg12TileManager *tiles;
public:
    SpaceshipObject(BaseEngine *eng, float x, float y, Psyjg12TileManager *tiles)
        : DisplayableObject(eng), x(x), y(y), vel_x(0), vel_y(0), theta(0), tiles(tiles) {
        m_iCurrentScreenX = x;
        m_iCurrentScreenY = y;
        m_iDrawHeight = 50;
        m_iDrawWidth = 50;

        setVisible(true);
    }

    void virtDraw() override;

    void virtDoUpdate(int iCurrentTime) override;
};

#endif