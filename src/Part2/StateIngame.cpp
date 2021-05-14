#include "../header.h"
#include "GameState.hpp"
#include "Inventory.hpp"
#include "StateIngame.hpp"
#include "WorldTileManager.hpp"

StateIngame::StateIngame(MiningGameEngine *eng) :
    GameState(eng) {

    // Create objects in this state
    tiles = new WorldTilesObject(eng, "block.png", "block_dark.png");
    tiles->loadFromFile("someworld.world");

    player = new Player(eng, &tiles->tiles_front, &tiles->tiles_back, eng->getTranslation(), 10, 800);

    player_inv = new Inventory(eng);
    player_inv->setSpritesheet(ImageManager::loadImage("item.png"));

    //player = new Player(eng, &tiles->tiles_front, &tiles->tiles_back
}