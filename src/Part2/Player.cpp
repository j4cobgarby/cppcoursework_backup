#include "../header.h"

#include "AnimatedImage.hpp"
#include "Player.hpp"
#include "SDL_keycode.h"

Player::Player(BaseEngine *eng, float x, float y)
    : AnimatedImageObject(eng, (int)x, (int)y, 1.0f) { 
    this->hp = 100;
    this->xp = 0;
    this->x_f = x;
    this->y_f = y;
    this->vel_x = 0;
    this->vel_y = 0;

    animation_t anim_idle = {
        ImageManager::get()->getImagePtrbyURL("player_idle1.png", true),
        ImageManager::get()->getImagePtrbyURL("player_idle2.png", true),
    };

    getImage()->addAnimation("idle1", anim_idle);
    getImage()->setCurrentAnimation("idle1");
    getImage()->setFrame(0);
    getImage()->setTimePerFrame(1000);
}

void Player::virtDoUpdate(int iCurrentTime) {
    if (getEngine()->isKeyPressed(SDLK_w)) {
    } if (getEngine()->isKeyPressed(SDLK_s)) {
    } if (getEngine()->isKeyPressed(SDLK_a)) {
        vel_x -= PLAYER_WALK_SPEED;
    } if (getEngine()->isKeyPressed(SDLK_d)) {
        vel_x += PLAYER_WALK_SPEED;
    }

    vel_x *= 0.9;
    vel_y *= 0.9;

    x_f += vel_x;
    y_f += vel_y;

    m_iCurrentScreenX = (int)x_f;
    m_iCurrentScreenY = (int)y_f;

    AnimatedImageObject::virtDoUpdate(iCurrentTime);
}