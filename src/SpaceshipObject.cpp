#include "header.h"
#include "SDL_keycode.h"
#include "DemoAObject.hpp"

void SpaceshipObject::virtDraw() {
    getEngine()->drawForegroundOval(
        m_iCurrentScreenX,
        m_iCurrentScreenY,
        m_iCurrentScreenX + m_iDrawWidth,
        m_iCurrentScreenY + m_iDrawHeight,
        0xffff00);
}

void SpaceshipObject::virtDoUpdate(int iCurrentTime) {
    static int prev_tile_x = -1;
    static int prev_tile_y = -1;

    if (getEngine()->isKeyPressed(SDLK_w)) {
        m_iCurrentScreenY -= 2;
    } if (getEngine()->isKeyPressed(SDLK_s)) {
        m_iCurrentScreenY += 2;
    } if (getEngine()->isKeyPressed(SDLK_a)) {
        m_iCurrentScreenX -= 2;
    } if (getEngine()->isKeyPressed(SDLK_d)) {
        m_iCurrentScreenX += 2;
    }

    if (tiles->isValidTilePosition(m_iCurrentScreenX + m_iDrawWidth/2, m_iCurrentScreenY + m_iDrawHeight/2)) {
        int tile_x = tiles->getMapXForScreenX(m_iCurrentScreenX + m_iDrawWidth/2);
        int tile_y = tiles->getMapYForScreenY(m_iCurrentScreenY + m_iDrawHeight/2);
        if (tile_x != prev_tile_x || tile_y != prev_tile_y) {
            tiles->flipTile(tile_x, tile_y);
            tiles->setAndRedrawMapValueAt(tile_x, tile_y, 0, getEngine(), getEngine()->getBackgroundSurface());
            prev_tile_x = tile_x;
            prev_tile_y = tile_y;
        }
    } else {
        prev_tile_x = prev_tile_y = -1;
    }

    redrawDisplay();
}