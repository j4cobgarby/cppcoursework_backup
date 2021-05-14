#include "../header.h"

#include "MiningGame.hpp"
#include "WorldTileManager.hpp"

#include <cstring>
#include <fstream>
#include <ios>

WorldTileManager::WorldTileManager(std::string tilesheet_path) :
        TileManager(8, 8) {
    setMapSize(WORLD_TILES_X, WORLD_TILES_Y);
    setTopLeftPositionOnScreen(0, 0);

    tilesheet = ImageManager::loadImage(tilesheet_path, true);
    tilesheet.setTransparencyColour(0x000000);

    for (int x = 0; x < WORLD_TILES_X; x++) {
        for (int y = 0; y < WORLD_TILES_Y; y++) {
            setMapValue(x, y, 0);
        }
    }
}

void WorldTileManager::setTileshet(std::string tilesheet_path) {
    tilesheet = ImageManager::loadImage(tilesheet_path, true);
}

void WorldTileManager::virtDrawTileAt(BaseEngine *eng, DrawingSurface *surf, int x, int y, int sx, int sy) const {
    int dat = m_pData[y * WORLD_TILES_X + x];

    if (dat >= 1 && dat <= 7) {
        tilesheet.renderImage(surf, 8*(getMapValue(x, y)-1), 0, sx, sy, 8, 8);
        //tile_images->at(dat-1).renderImage(surf, 0, 0, sx, sy, 8, 8);
    }
}

WorldTilesObject::WorldTilesObject(BaseEngine *eng, std::string tilesheet_path_front,
std::string tilesheet_path_back) : 
    DisplayableObject(eng), 
    tiles_back(tilesheet_path_back),
    tiles_front(tilesheet_path_front) 
{}

void WorldTilesObject::virtDraw() {
    int startx = -((MiningGameEngine*)getEngine())->getTranslateX() >> 3;
    int starty = -((MiningGameEngine*)getEngine())->getTranslateY() >> 3;
    startx--; starty --; // Make sure there are no empty spaces
    // int startx = 10;
    // int starty = 0;
    int countx = 40;
    int county = 25;

    tiles_front.setTopLeftPositionOnScreen(startx * 8, starty * 8);
    tiles_back.setTopLeftPositionOnScreen(startx * 8, starty * 8);

    getEngine()->getForegroundSurface()->mySDLLockSurface();
    for (int x = 0; x < countx; x++) {
        for (int y = 0; y < county; y++) {
            if (tiles_front.getMapValue(startx + x, starty + y) == 0) {
                tiles_back.virtDrawTileAt(getEngine(), getEngine()->getForegroundSurface(), 
                    x+startx, y+starty, startx * 8 + x * 8, starty * 8 + y * 8);
            } else {
                tiles_front.virtDrawTileAt(getEngine(), getEngine()->getForegroundSurface(), 
                    x+startx, y+starty, startx * 8 + x * 8, starty * 8 + y * 8);
            }
        }
    }
    getEngine()->getForegroundSurface()->mySDLUnlockSurface();

    //tiles_back.drawSomeTiles(getEngine(), getEngine()->getForegroundSurface(), startx, starty, countx, county);
    //tiles_front.drawSomeTiles(getEngine(), getEngine()->getForegroundSurface(), startx, starty, countx, county);
}

char *WorldTileManager::serialise() {
    return (char*)m_pData;
}

void WorldTileManager::setData(int *dat) {
    memcpy(m_pData, dat, WORLD_TILES_X * WORLD_TILES_Y * sizeof(int));
}

void WorldTilesObject::saveToFile(std::string filepath) {
    std::ofstream of;
    of.open(filepath, std::ios::out | std::ios::binary);
    
    // TODO: Make WorldTileManager implicitly convertable to char*
    of.write(tiles_back.serialise(), WORLD_TILES_X * WORLD_TILES_Y * (sizeof(int)/sizeof(char)));
    of.write(tiles_front.serialise(), WORLD_TILES_X * WORLD_TILES_Y * (sizeof(int)/sizeof(char)));

    of.close();
}

void WorldTilesObject::loadFromFile(std::string filepath) {
    std::ifstream f;
    f.open(filepath, std::ios::in | std::ios::binary);

    char *tmp = (char*)malloc(WORLD_TILES_X * WORLD_TILES_Y * (sizeof(int)/sizeof(char)));
    
    f.read(tmp, WORLD_TILES_X * WORLD_TILES_Y * (sizeof(int)/sizeof(char)));
    tiles_back.setData((int*)tmp);

    f.read(tmp, WORLD_TILES_X * WORLD_TILES_Y * (sizeof(int)/sizeof(char)));
    tiles_front.setData((int*)tmp);

    f.close();
}