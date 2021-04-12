#ifndef WORLDTILEMANAGER_HPP
#define WORLDTILEMANAGER_HPP

#include "../BaseEngine.h"
#include "../TileManager.h"

#include <vector>

#define WORLD_TILES_X 512
#define WORLD_TILES_Y 64

class WorldTileManager : public TileManager {
public:
    WorldTileManager();
    WorldTileManager(std::vector<SimpleImage> *tile_images);

    void setTileImages(std::vector<SimpleImage> *tile_images);
    
    virtual void virtDrawTileAt(BaseEngine *eng, DrawingSurface *surf, 
            int x, int y, int sx, int sy) const override;
protected:
    std::vector<SimpleImage> *tile_images;
};

#endif