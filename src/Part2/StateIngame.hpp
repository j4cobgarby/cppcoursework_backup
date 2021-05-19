#ifndef STATEINGAME_HPP
#define STATEINGAME_HPP
#include "GameState.hpp"
#include "WorldTileManager.hpp"
#include "Player.hpp"
#include "Entity.hpp"
#include "EventHandler.hpp"
#include "Inventory.hpp"
#include "Slime.hpp"

#define NUM_SLIMES 10

class StateIngame : public GameState {
protected:
    WorldTilesObject *tiles;
    Player *player;
    Inventory *player_inv;

    int last_slime_wave_time;
    
    int seed;

    void savePlayerToFile();
public: 
    StateIngame(MiningGameEngine *eng);

    void virtSetupBackgroundBuffer() override;
    void virtMainLoopStartIteration() override;
    void onChangeTo() override;

    void virtMouseDown(int btn, int x, int y) override;
    void virtKeyDown(int key) override;

    void loadEntities();
    void saveAndQuit();

    void playerHit(int x, int y, int px, int py);
};
#endif