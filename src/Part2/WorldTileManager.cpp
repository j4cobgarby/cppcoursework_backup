#include "../header.h"

#include "WorldTileManager.hpp"

WorldTileManager::WorldTileManager() : TileManager(8, 8) {
    setMapSize(WORLD_TILES_X, WORLD_TILES_Y);
    setTopLeftPositionOnScreen(0, 0);

    for (int x = 0; x < WORLD_TILES_X; x++) {
        for (int y = 0; y < WORLD_TILES_Y; y++) {
            setMapValue(x, y, 0);
        }
    }
}

WorldTileManager::WorldTileManager(std::vector<SimpleImage> *tile_images) :
        TileManager(8, 8), tile_images(tile_images) {
    setMapSize(WORLD_TILES_X, WORLD_TILES_Y);
    setTopLeftPositionOnScreen(0, 0);

    for (int x = 0; x < WORLD_TILES_X; x++) {
        for (int y = 0; y < WORLD_TILES_Y; y++) {
            setMapValue(x, y, 0);
        }
    }
}

void WorldTileManager::setTileImages(std::vector<SimpleImage> *tile_images) {
    this->tile_images = tile_images;
}

void WorldTileManager::virtDrawTileAt(BaseEngine *eng, DrawingSurface *surf, int x, int y, int sx, int sy) const {
    int dat = m_pData[y * WORLD_TILES_X + x];

    if (dat > 0) {
        //tile_images->at(dat-1).setTransparencyColour(0x000000);
        tile_images->at(dat-1).renderImage(surf, 0, 0, sx, sy, 8, 8);
    }
}