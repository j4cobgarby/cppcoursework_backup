#include "../header.h"
#include "AnimatedImage.hpp"
#include "MiningGame.hpp"
#include "SDL_keycode.h"
#include "SDL_surface.h"
#include "WorldGen.hpp"
#include "WorldTileManager.hpp"


#define NUM_TILES 7

const std::string tile_imgs[] = {
    "block1.png",
    "block2.png",
    "block3.png",
    "block4.png",
    "block5.png",
    "block6.png",
    "block7.png",
};

const std::string tile_imgs_bg[] = {
    "block_bg1.png",
    "block_bg2.png",
    "block_bg3.png",
    "block_bg4.png",
    "block_bg5.png",
    "block_bg6.png",
    "block_bg7.png",
};

MiningGameEngine::MiningGameEngine()
    :   filter_scale(2, 2),
        filter_translate(0, 0, &filter_scale) {

    for (int i = 0; i < NUM_TILES; i++) {
        tile_images.push_back(ImageManager::loadImage(tile_imgs[i]));
        tile_images_bg.push_back(ImageManager::loadImage(tile_imgs_bg[i]));
        tile_images.at(i).setTransparencyColour(0x000000);
        tile_images_bg.at(i).setTransparencyColour(0x000000);
    }

    tiles = new WorldTilesObject(this, &tile_images, &tile_images_bg);

    getForegroundSurface()->setDrawPointsFilter(&filter_translate);
    getBackgroundSurface()->setDrawPointsFilter(&filter_translate);

    WorldGen::generateWorld(3, &tiles->tiles_front, &tiles->tiles_back);
}

void MiningGameEngine::virtSetupBackgroundBuffer() {
    fillBackground(0x0095e9);

    std::cout << "Drawn background" << std::endl;
}

int MiningGameEngine::virtInitialiseObjects() {
    drawableObjectsChanged();
    destroyOldObjects(true);
    createObjectArray(2);

    player = new Player(this, &tiles->tiles_front, &tiles->tiles_back, &filter_translate, 100, 100);

    storeObjectInArray(0, tiles);
    storeObjectInArray(1, player);

    return 0;
}

void MiningGameEngine::virtMainLoopStartIteration() {

}

void MiningGameEngine::virtDrawStringsUnderneath() {
}

void MiningGameEngine::virtDrawStringsOnTop() {
}

void MiningGameEngine::virtMouseDown(int btn, int x, int y) {
}

void MiningGameEngine::virtKeyDown(int key) {
    if (key == SDLK_w) {
        player->jump();
    }
    if (key == SDLK_t) {
        std::cout << filter_translate.getXOffset() << ", " << filter_translate.getYOffset() << std::endl;
        std::cout << player->getXCentre() << ", " << player->getYCentre() << std::endl << std::endl;
    }
}