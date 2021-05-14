#include "GameState.hpp"
#include "WorldTileManager.hpp"
#include "Player.hpp"
#include "Entity.hpp"
#include "EventHandler.hpp"
#include "Inventory.hpp"

class StateIngame : public GameState {
protected:
    WorldTilesObject *tiles;
    Player *player;
    Inventory *player_inv;
    
public: 
    StateIngame(MiningGameEngine *eng);
};