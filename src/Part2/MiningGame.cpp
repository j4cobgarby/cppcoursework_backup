#include "../header.h"
#include "AnimatedImage.hpp"
#include "EventHandler.hpp"
#include "Inventory.hpp"
#include "MiningGame.hpp"
#include "SDL_keycode.h"
#include "SDL_surface.h"
#include "WorldGen.hpp"
#include "WorldTileManager.hpp"


#define NUM_TILES 7

MiningGameEngine::MiningGameEngine()
    :   filter_scale(4,4),
        filter_translate(0, 0, &filter_scale) {

    seed = 0;
    bg_offset = 0;

    tiles = new WorldTilesObject(this, "block.png", "block_dark.png");

    getForegroundSurface()->setDrawPointsFilter(&filter_translate);

    //WorldGen::generateWorld(seed, &tiles->tiles_front, &tiles->tiles_back);
    tiles->loadFromFile("someworld.world");


    // tiles->saveToFile("someworld.world");
}

void MiningGameEngine::virtSetupBackgroundBuffer() {
    fillBackground(0x0095e9);

    SimpleImage cloudsheet = ImageManager::loadImage("cloud.png");
    cloudsheet.setTransparencyColour(0x000000);
    int n_cloud_types = 3;
    int total_clouds = 100;

    srand(seed);

    for (int i = 0; i < total_clouds; i++) {
        cloudsheet.renderImageBlit(this, getBackgroundSurface(), 
        rand() % getBackgroundSurface()->getSurfaceWidth(), 
        rand() % getBackgroundSurface()->getSurfaceHeight(), 
        32,32, 
        32 * (rand() % n_cloud_types), 0, 32, 32);
    }

    //cloudsheet.renderImageBlit(this, getBackgroundSurface(), 0, 0, 96, 32, 0, 0, 96, 32);

    std::cout << "Drawn background" << std::endl;
}

int MiningGameEngine::virtInitialiseObjects() {
    drawableObjectsChanged();
    destroyOldObjects(true);
    createObjectArray(3);

    float py = WorldGen::getTerrainTop(&tiles->tiles_front, 10) * 8 + 32;
    player = new Player(this, &tiles->tiles_front, &tiles->tiles_back, &filter_translate, 0, 100);

    player_inv = new Inventory(this);
    player_inv->setSpritesheet(ImageManager::loadImage("item.png"));

    player->assignInventory(player_inv);

    storeObjectInArray(0, tiles);
    storeObjectInArray(1, player);
    storeObjectInArray(2, player_inv);

    event_handlers.push_back(player);

    return 0;
}

void MiningGameEngine::virtDrawStringsUnderneath() {
}

void MiningGameEngine::virtDrawStringsOnTop() {
}

void MiningGameEngine::virtMouseDown(int btn, int x, int y) {
    for (EventHandler *eh : event_handlers) {
        eh->handleMouseDown(btn, x, y);
    }
}

void MiningGameEngine::virtKeyDown(int key) {
    for (EventHandler *eh : event_handlers) {
        eh->handleKeyDown(key);
    }

    if (key == SDLK_t) {
        std::cout << getTranslateX() << ", " << getTranslateY() << std::endl;
        std::cout << getCurrentMouseX()/8 << ", " << getCurrentMouseY()/8 << std::endl;
        std::cout << player->getXCentre() << ", " << player->getYCentre() << std::endl;
    }
}

void MiningGameEngine::setFilterEnabled(bool enabled) {
    FilterPoints *f = enabled ? &filter_translate : nullptr;
	getForegroundSurface()->setDrawPointsFilter(f);
    getBackgroundSurface()->setDrawPointsFilter(f);
}

void MiningGameEngine::copyAllBackgroundBuffer() {
    m_pForegroundSurface->copyRectangleFrom(m_pBackgroundSurface, 0, 0, getWindowWidth(), getWindowHeight(), bg_offset, 0);
    m_pForegroundSurface->copyRectangleFrom(m_pBackgroundSurface, getWindowWidth()-bg_offset,
        0, getWindowWidth(), getWindowHeight(), bg_offset-getWindowWidth(), 0);
}

void MiningGameEngine::changeState(std::string state_name) {
    GameState *target = &(states.at(state_name));

    destroyOldObjects(true);
    createObjectArray(target->getObjectsCount());

    for (int i = 0; i < target->getObjectsCount(); i++) {
        storeObjectInArray(i, target->getObject(i));
    }

    redrawDisplay();
}

void MiningGameEngine::virtMainLoopStartIteration() {
    if (current_state) current_state->virtMainLoopStartIteration();

    bg_offset = (bg_offset + 0.2);
    if (bg_offset >= getWindowWidth()) bg_offset = 0;
    redrawDisplay();
}

void MiningGameEngine::virtMainLoopPreUpdate() {
    if (current_state) current_state->virtMainLoopPreUpdate();
}

void MiningGameEngine::virtMainLoopDoBeforeUpdate() {
    if (current_state) current_state->virtMainLoopDoBeforeUpdate();
}

void MiningGameEngine::virtMainLoopDoAfterUpdate() {
    if (current_state) current_state->virtMainLoopDoAfterUpdate();
}

void MiningGameEngine::virtMainLoopPostUpdate() {
    if (current_state) current_state->virtMainLoopPostUpdate();
}