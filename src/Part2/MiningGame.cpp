#include "../header.h"
#include "AnimatedImage.hpp"
#include "MiningGame.hpp"
#include "SDL_keycode.h"
#include "WorldGen.hpp"
#include "Player.hpp"

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

    getForegroundSurface()->setDrawPointsFilter(&filter_translate);
    getBackgroundSurface()->setDrawPointsFilter(&filter_translate);

    tiles_back.setTileImages(&tile_images_bg);
    tiles_front.setTileImages(&tile_images);

    WorldGen::generateWorld(312023212, &tiles_front, &tiles_back);
}

void MiningGameEngine::virtSetupBackgroundBuffer() {
    fillBackground(0x0095e9);

    tiles_back.drawAllTiles(this, this->getBackgroundSurface());
    tiles_front.drawAllTiles(this, this->getBackgroundSurface());

    std::cout << "Drawn background" << std::endl;
}

int MiningGameEngine::virtInitialiseObjects() {
    drawableObjectsChanged();
    destroyOldObjects(true);
    createObjectArray(1);

    Player *player = new Player(this, 100, 100);

    // AnimatedImageObject *obj = new AnimatedImageObject(this, 100, 100, 1);
    // animation_t anim_idle = {
    //     ImageManager::get()->getImagePtrbyURL("player_idle1.png", true),
    //     ImageManager::get()->getImagePtrbyURL("player_idle2.png", true),
    // };
    // obj->getImage()->addAnimation("idle1", anim_idle);
    // obj->getImage()->setCurrentAnimation("idle1");
    // obj->getImage()->setFrame(0);
    // obj->getImage()->setTimePerFrame(1000);

    storeObjectInArray(0, player);

    return 0;
}

void MiningGameEngine::virtDrawStringsUnderneath() {
}

void MiningGameEngine::virtDrawStringsOnTop() {
}

void MiningGameEngine::virtMouseDown(int btn, int x, int y) {
}

void MiningGameEngine::virtKeyDown(int key) {
    // if (key == SDLK_LEFT) {
    //     filter_translate.changeOffset(-8, 0);
    // } else if (key == SDLK_RIGHT) {
    //     filter_translate.changeOffset(8, 0);
    // } else if (key == SDLK_UP) {
    //     filter_translate.changeOffset(0, -8);
    // } else if (key == SDLK_DOWN) {
    //     filter_translate.changeOffset(0, 8);
    // }

    getBackgroundSurface()->fillSurface(0x0095e9);
    tiles_back.drawAllTiles(this, getBackgroundSurface());
    tiles_front.drawAllTiles(this, getBackgroundSurface());
    redrawDisplay();
}