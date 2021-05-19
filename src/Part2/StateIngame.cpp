#include "../header.h"
#include "GameState.hpp"
#include "Inventory.hpp"
#include "SDL_keycode.h"
#include "StateIngame.hpp"
#include "WorldTileManager.hpp"

#include "MiningGame.hpp"
#include "GlobalState.hpp"
#include <array>
#include <filesystem>
#include <fstream>

StateIngame::StateIngame(MiningGameEngine *eng) :
    GameState(eng) {

    std::cout << "Constructed" << std::endl;
    seed = 0;
    last_slime_wave_time = eng->getModifiedTime();
    // Space for:
    // - tiles
    // - player
    // - player_inv
    // - all the slimes
}

void StateIngame::onChangeTo() {
    nextState = "";
    eng->setFilterEnabled(true);
    objects.clear();
    event_handlers.clear();

    std::cout << "Changed to state" << std::endl;
    // Create objects in this state
    //tiles = new WorldTilesObject(eng, "block.png", "block_dark.png");
    //tiles->loadFromFile("someworld.world");
    // tiles = GlobalState::getTiles();
    tiles = worldTiles;

    player = new Player(eng, &tiles->tiles_front, &tiles->tiles_back, eng->getTranslation(), 0, 0);
    event_handlers.push_back(player);
    
    // This will set the player position
    loadEntities();

    player_inv = new Inventory(eng);
    player_inv->setSpritesheet(ImageManager::loadImage("item.png", true));
    if (newWorld) {
        player_inv->setCell(0, 9, 1);
        player_inv->setCell(1, 10, 1);
    } else {
        player_inv->loadFromFile();
    }

    player->assignInventory(player_inv);

    objects.push_back(tiles);
    objects.push_back(player);
    objects.push_back(player_inv);
}

void StateIngame::virtSetupBackgroundBuffer() {
    eng->fillBackground(0x0095e9);

    SimpleImage cloudsheet = ImageManager::loadImage("cloud.png", true);
    cloudsheet.setTransparencyColour(0x000000);
    int n_cloud_types = 3;
    int total_clouds = 100;

    srand(seed);

    for (int i = 0; i < total_clouds; i++) {
        cloudsheet.renderImageBlit(eng, eng->getBackgroundSurface(), 
        rand() % eng->getBackgroundSurface()->getSurfaceWidth(), 
        rand() % eng->getBackgroundSurface()->getSurfaceHeight(), 
        32,32, 
        32 * (rand() % n_cloud_types), 0, 32, 32);
    }

    //cloudsheet.renderImageBlit(this, getBackgroundSurface(), 0, 0, 96, 32, 0, 0, 96, 32);

    std::cout << "Drawn background" << std::endl;
}

void StateIngame::virtMouseDown(int btn, int x, int y) {
    for (EventHandler *eh : event_handlers) {
        eh->handleMouseDown(btn, x, y);
    }
}

void StateIngame::virtKeyDown(int key) {
    for (EventHandler *eh : event_handlers) {
        eh->handleKeyDown(key);
    }

    if (key == SDLK_t) {
        std::cout << eng->getTranslateX() << ", " << eng->getTranslateY() << std::endl;
        std::cout << eng->getCurrentMouseX()/8 << ", " << eng->getCurrentMouseY()/8 << std::endl;
        std::cout << player->getXfloat() << ", " << player->getYfloat() << std::endl;
        std::cout << eng->getModifiedTime() << std::endl;
    }

    if (key == SDLK_ESCAPE) {
        saveAndQuit();
    }
}

void StateIngame::virtMainLoopStartIteration() {
    bg_offset_x = (bg_offset_x + 0.2);
    if (bg_offset_x >= eng->getWindowWidth()) bg_offset_x = 0;
    eng->redrawDisplay();
    if (eng->getModifiedTime() - last_slime_wave_time > 10000) {
        last_slime_wave_time = eng->getModifiedTime();
        if (eng->getContentCount() < 3 + NUM_SLIMES) {
            eng->appendObjectToArray(new Slime(eng, &tiles->tiles_front, &tiles->tiles_back, rand()%WORLD_TILES_X*8, 10, player));
        }
    }
}

void StateIngame::loadEntities() {
    std::ifstream entfile;
    entfile.open(worldFolder/"entities", std::ios::in);

    char id;
    float x, y;

    while (entfile >> id >> x >> y) {
        std::cout << id << " : " << x << " : " << y << std::endl;

        if (id == 'p') {
            player->setXfloat(x);
            player->setYfloat(y-1);
        }
    }
    entfile.close();
}

void StateIngame::saveAndQuit() {
    std::filesystem::create_directories(worldFolder);
    std::cout << worldFolder/"data.world" << std::endl;
    worldTiles->saveToFile((worldFolder/"data.world"));
    player_inv->saveToFile();
    savePlayerToFile();
    nextState = "mainmenu";
}

void StateIngame::savePlayerToFile() {
    std::filesystem::create_directories(worldFolder);
    std::ofstream entfile;
    entfile.open(worldFolder/"entities", std::ios::out);
    std::string line = std::string("p ") + 
        std::to_string(player->getXfloat()) + 
        " " + std::to_string(player->getYfloat()) + "\n";
    entfile.write(line.c_str(), line.size());
    entfile.close();
}

void StateIngame::playerHit(int x, int y, int px, int py) {
    std::cout << eng->getContentCount() << std::endl;
    for (int i = 3; i < eng->getContentCount(); i++) {
        Slime *sl = (Slime *)eng->getDisplayableObject(i);
        std::array<float, 4> slbox = sl->getBBox();
        if (!(x < slbox[0] || x > slbox[1] 
        || y < slbox[2] || y > slbox[3])) {
            float dx = (float)(x - px);
            float dy = (float)(y - py);
            float dmag = sqrtf(dx*dx + dy*dy);
            if (sl->beHit(dx / dmag, dy / dmag)) {
                eng->removeDisplayableObject(sl);
            }
        }
    }
}