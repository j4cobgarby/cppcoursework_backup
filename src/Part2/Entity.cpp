#include "../header.h"

#include "AnimatedImage.hpp"
#include "Entity.hpp"
#include "WorldTileManager.hpp"

Entity::Entity(BaseEngine *eng, float x, float y, float bbox_left, float bbox_right, 
        float bbox_top, float bbox_bottom, WorldTileManager *front, WorldTileManager *back, bool topleftorigin, bool visible)
    : AnimatedImageObject(eng, (int)x, (int)y, 1.0f, topleftorigin, visible) {
    
    x_f = x;
    y_f = y;

    vel_x = 0;
    vel_y = 0;

    this->bbox_left = bbox_left;
    this->bbox_right = bbox_right;
    this->bbox_top = bbox_top;
    this->bbox_bottom = bbox_bottom;

    this->tiles_front = front;
    this->tiles_back = back;
}

void Entity::virtDoUpdate(int iCurrentTime) {
    vel_y += 0.1;

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
}

void Entity::virtDraw() {
    AnimatedImageObject::virtDraw();
}

bool Entity::overlaps(float ax_l, float ax_r, float ay_t, float ay_b,
        float bx_l, float bx_r, float by_t, float by_b) {
    return !(ax_r < bx_l || bx_r < ax_l || ay_b < by_t || by_b < ay_t);
}

bool Entity::try_move(float vx, float vy) {
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
                    overlaps(new_x+bbox_left, new_x+bbox_right, new_y+bbox_top, new_y+bbox_bottom, c*8, c*8+7, r*8, r*8+7)) {
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