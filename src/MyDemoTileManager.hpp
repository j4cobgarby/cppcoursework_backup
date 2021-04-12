#ifndef MYDEMOTILEMANAGER_HPP
#define MYDEMOTILEMANAGER_HPP

#include "BaseEngine.h"
#include "DrawingSurface.h"
#include "TileManager.h"

#define TILESX 10
#define TILESY 10

class Psyjg12TileManager : public TileManager {
public:
    Psyjg12TileManager();
    ~Psyjg12TileManager() {}
    
    virtual void virtDrawTileAt(BaseEngine *eng, DrawingSurface *surf, 
            int x, int y, int sx, int sy) const override;
    void flipTile(int x, int y);
private:
    bool tiles_flipped[TILESX * TILESY] = {false};
};

#endif