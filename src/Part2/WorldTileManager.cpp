#include "../header.h"

#include "MiningGame.hpp"
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
    std::cout << "Set tile images to " << tile_images << std::endl;
}

void WorldTileManager::virtDrawTileAt(BaseEngine *eng, DrawingSurface *surf, int x, int y, int sx, int sy) const {
    int dat = m_pData[y * WORLD_TILES_X + x];

    if (dat >= 1 && dat <= 7) {
        tile_images->at(dat-1).renderImage(surf, 0, 0, sx, sy, 8, 8);
    }
}

WorldTilesObject::WorldTilesObject(BaseEngine *eng, std::vector<SimpleImage> *imgs_fg, 
        std::vector<SimpleImage> *imgs_bg) : DisplayableObject(eng) {
    tiles_front.setTileImages(imgs_fg);
    tiles_back.setTileImages(imgs_bg);
}

void WorldTilesObject::virtDraw() {
    int startx = -((MiningGameEngine*)getEngine())->getTranslateX() >> 3;
    int starty = -((MiningGameEngine*)getEngine())->getTranslateY() >> 3;
    startx--; starty --; // Make sure there are no empty spaces
    // int startx = 10;
    // int starty = 0;
    int countx = 60;
    int county = 35;

    tiles_front.setTopLeftPositionOnScreen(startx * 8, starty * 8);
    tiles_back.setTopLeftPositionOnScreen(startx*8, starty*8);
    tiles_back.drawSomeTiles(getEngine(), getEngine()->getForegroundSurface(), startx, starty, countx, county);
    tiles_front.drawSomeTiles(getEngine(), getEngine()->getForegroundSurface(), startx, starty, countx, county);
}