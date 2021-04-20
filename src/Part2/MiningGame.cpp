#include "../header.h"
#include "AnimatedImage.hpp"
#include "MiningGame.hpp"
#include "SDL_keycode.h"
#include "SDL_surface.h"
#include "WorldGen.hpp"


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

    block_surf = new DrawingSurface(this);
    block_surf->createSurface(WORLD_TILES_X * 8, WORLD_TILES_Y * 8);

    for (int i = 0; i < NUM_TILES; i++) {
        tile_images.push_back(ImageManager::loadImage(tile_imgs[i]));
        tile_images_bg.push_back(ImageManager::loadImage(tile_imgs_bg[i]));
        tile_images.at(i).setTransparencyColour(0x000000);
        tile_images_bg.at(i).setTransparencyColour(0x000000);
    }

    getForegroundSurface()->setDrawPointsFilter(&filter_translate);
    getBackgroundSurface()->setDrawPointsFilter(&filter_translate);
    block_surf->setDrawPointsFilter(&filter_translate);

    tiles_back.setTileImages(&tile_images_bg);
    tiles_front.setTileImages(&tile_images);

    WorldGen::generateWorld(3, &tiles_front, &tiles_back);
}

void MiningGameEngine::virtSetupBackgroundBuffer() {
    fillBackground(0x0095e9);

    tiles_back.drawAllTiles(this, block_surf);
    tiles_front.drawAllTiles(this, block_surf);
    this->getBackgroundSurface()->copyRectangleFrom(block_surf, 0, 0, 
        this->getBackgroundSurface()->getSurfaceWidth(), this->getBackgroundSurface()->getSurfaceHeight());

    //tiles_back.drawSomeTiles(this, this->getBackgroundSurface(), 0, 0, 50, 50);
    //tiles_front.drawSomeTiles(this, this->getBackgroundSurface(), 0, 0, 50, 50);

    std::cout << "Drawn background" << std::endl;
}

int MiningGameEngine::virtInitialiseObjects() {
    drawableObjectsChanged();
    destroyOldObjects(true);
    createObjectArray(1);

    player = new Player(this, &tiles_front, &tiles_back, &filter_translate, 100, 100);

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

void MiningGameEngine::virtMainLoopStartIteration() {
    //filter_translate.setOffset(-player->getXCentre() + 100, -player->getYCentre() + 100);
    //fillBackground(0x0095e9);

    // tiles_back.drawAllTiles(this, this->getBackgroundSurface());
    // tiles_front.drawAllTiles(this, this->getBackgroundSurface());
    //tiles_back.drawSomeTiles(this, this->getBackgroundSurface(), 0, 0, 50, 50);
    //tiles_front.drawSomeTiles(this, this->getBackgroundSurface(), 0, 0, 50, 50);
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
    if (key == SDLK_w) {
        player->jump();
    }

    //getBackgroundSurface()->fillSurface(0x0095e9);
    //tiles_back.drawAllTiles(this, getBackgroundSurface());
    //tiles_front.drawAllTiles(this, getBackgroundSurface());
    //redrawDisplay();
}