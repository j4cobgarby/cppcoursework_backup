#include "../header.h"

#include "AnimatedImage.hpp"
#include "Player.hpp"
#include "SDL_keycode.h"
#include "WorldTileManager.hpp"
#include "../UtilCollisionDetection.h"

Player::Player(BaseEngine *eng, WorldTileManager *front, WorldTileManager *back,
    FilterPointsTranslation *translation, float x, float y)
    : AnimatedImageObject(eng, (int)x, (int)y, 1.0f) { 
    this->hp = 100;
    this->xp = 0;
    this->x_f = x;
    this->y_f = y;
    this->vel_x = 0;
    this->vel_y = 0;
    this->facing_right = true;
    this->tiles_back = back;
    this->tiles_front = front;
    this->translation = translation;

    ImageManager::loadImage("player_run_right.png", true);
    ImageManager::loadImage("player_run_left.png", true);
    ImageManager::loadImage("player_idle_right.png", true);
    ImageManager::loadImage("player_idle_left.png", true);

    animation_t anim_run_right = {
        .spritesheet=ImageManager::get()->getImagePtrbyURL("player_run_right.png"),
        .frame_width=8, .frame_height=16,
        .frame_count=9, .time_per_frame=50
    };

    animation_t anim_run_left = {
        .spritesheet=ImageManager::get()->getImagePtrbyURL("player_run_left.png"),
        .frame_width=8, .frame_height=16,
        .frame_count=9, .time_per_frame=50
    };

    animation_t anim_idle_right = {
        .spritesheet=ImageManager::get()->getImagePtrbyURL("player_idle_right.png"),
        .frame_width=8, .frame_height=16,
        .frame_count=2, .time_per_frame=800
    };

    animation_t anim_idle_left = {
        .spritesheet=ImageManager::get()->getImagePtrbyURL("player_idle_left.png"),
        .frame_width=8, .frame_height=16,
        .frame_count=2, .time_per_frame=800
    };

    getImage()->addAnimation("run_right", anim_run_right);
    getImage()->addAnimation("run_left", anim_run_left);
    getImage()->addAnimation("idle_right", anim_idle_right);
    getImage()->addAnimation("idle_left", anim_idle_left);

    getImage()->setCurrentAnimation("idle_right");
    getImage()->setFrame(0);
}

bool Player::overlaps(float ax_l, float ax_r, float ay_t, float ay_b, float bx_l, float bx_r, float by_t, float by_b) {
    return !(ax_r < bx_l || bx_r < ax_l || ay_b < by_t || by_b < ay_t);
}

bool Player::try_move(float vx, float vy) {
    float new_x = x_f + vx;
    float new_y = y_f + vy;

    int check_start_x = (m_iCurrentScreenX/8)-2;
    int check_start_y = (m_iCurrentScreenY/8)-2;
    int check_end_x = check_start_x+6;
    int check_end_y = check_start_y+6;

    bool can_move = true;

    for (int r = check_start_y; r <= check_end_y; r++) {
        for (int c = check_start_x; c <= check_end_x; c++) {
            if (tiles_front->getMapValue(c, r) != 0 &&
                overlaps(new_x+2, new_x+5, new_y, new_y+15, c*8, c*8+8, r*8, r*8+8)) {
                can_move = false;
            }
        }
    }

    if (can_move) {
        x_f = new_x;
        y_f = new_y;
    }

    return !can_move;
}

void Player::virtDoUpdate(int iCurrentTime) {
    bool moving = false;
    bool will_hit_x = false;
    bool will_hit_y = false;

    // std::cout << m_iDrawWidth << ", " << m_iStartDrawPosX << ", " << m_iCurrentScreenX << " | " <<
    //     getXCentre() << ", " << getYCentre() << " | " <<
    //     translation->getXOffset() << ", " << translation->getYOffset() << std::endl;

    if (getEngine()->isKeyPressed(SDLK_a)) {
        moving = true;
        vel_x -= PLAYER_WALK_SPEED;
        facing_right = false;
        
    } if (getEngine()->isKeyPressed(SDLK_d)) {
        moving = true;
        vel_x += PLAYER_WALK_SPEED;
        facing_right = true;
        
    } if (getEngine()->isKeyPressed(SDLK_UP)) {
        translation->changeOffset(0, -1);
    } if (getEngine()->isKeyPressed(SDLK_DOWN)) {
        translation->changeOffset(0, 1);
    } if (getEngine()->isKeyPressed(SDLK_LEFT)) {
        translation->changeOffset(-1, 0);
    } if (getEngine()->isKeyPressed(SDLK_RIGHT)) {
        translation->changeOffset(1, 0);
    }

    vel_y += 0.13;

    std::string current_anim = getImage()->getCurrentAnimation();

    if (moving) {
        if (facing_right && current_anim != "run_right") getImage()->setCurrentAnimation("run_right");
        if (!facing_right && current_anim != "run_left") getImage()->setCurrentAnimation("run_left");
    } else {
        if (facing_right && current_anim != "idle_right") getImage()->setCurrentAnimation("idle_right");
        if (!facing_right && current_anim != "idle_left") getImage()->setCurrentAnimation("idle_left");
    }

    vel_x *= 0.93;
    vel_y *= 0.93;

    if (try_move(vel_x, 0.f)) {
        vel_x = 0;
    }

    if (try_move(0.f, vel_y)) {
        vel_y = 0;
    } 

    m_iCurrentScreenX = (int)x_f;
    m_iCurrentScreenY = (int)y_f;

    AnimatedImageObject::virtDoUpdate(iCurrentTime);

    getEngine()->copyAllBackgroundBuffer();
}

void Player::virtDraw() {
    AnimatedImageObject::virtDraw();
}

void Player::jump() {
    if (on_ground) {
        vel_y -= 4;
    }
}