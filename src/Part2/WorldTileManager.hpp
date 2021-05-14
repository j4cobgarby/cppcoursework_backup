#ifndef WORLDTILEMANAGER_HPP
#define WORLDTILEMANAGER_HPP

#include "../BaseEngine.h"
#include "../TileManager.h"
#include "../DisplayableObject.h"

#include <vector>

#define WORLD_TILES_X 256
#define WORLD_TILES_Y 64

class WorldTileManager : public TileManager {
public:
    WorldTileManager(std::string tilesheet_path);

    void setTileshet(std::string tilesheet_path);
    
    virtual void virtDrawTileAt(BaseEngine *eng, DrawingSurface *surf, 
            int x, int y, int sx, int sy) const override;

    char *serialise();
    void setData(int *dat);
protected:
    SimpleImage tilesheet;
};

class WorldTilesObject : public DisplayableObject {
private:
public:
    WorldTilesObject(BaseEngine *eng, std::string tilesheet_path_front, std::string tilesheet_path_back);

    WorldTileManager tiles_front;
    WorldTileManager tiles_back;
    //virtual void virtDoUpdate(int iCurrentTime) override;
    virtual void virtDraw() override;

    void saveToFile(std::string filepath);
    void loadFromFile(std::string filepath);
};

#endif