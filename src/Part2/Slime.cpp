#include "../header.h"
#include "Entity.hpp"
#include "SDL_stdinc.h"
#include "WorldTileManager.hpp"
#include "Slime.hpp"
#include "CollisionShape.hpp"
#include <array>

Slime::Slime(BaseEngine *eng, WorldTileManager *front, WorldTileManager *back, float x, float y, Player *target) :
    Entity(eng, x, y, 0, 7, 0, 7, front, back) {

    this->target = target;
    hp = 4;
    previous_jump_time = eng->getModifiedTime();
    previous_hit_time = eng->getModifiedTime();

    ImageManager::loadImage("slime.png", true);
    animation_t anim_slime = {
        .spritesheet=ImageManager::get()->getImagePtrbyURL("slime.png"),
        .frame_width=8, .frame_height=8,
        .frame_count=1, .time_per_frame=500
    };
    getImage()->addAnimation("main", anim_slime);
    getImage()->setCurrentAnimation("main");
    getImage()->setPlaying(false);
    getImage()->setFrame(0);
}

void Slime::virtDoUpdate(int iCurrentTime) {
    // Find which way to jump to get towards the player
    float x_multiplier = target->getXfloat() > x_f ? 1 : -1;
    
    if (iCurrentTime >= previous_jump_time + 2000 + (rand() % 500)) {
        previous_jump_time = iCurrentTime;
        vel_y -= 3 + (float)(rand()%10)/10.f;
        vel_x += (((float)(rand()%10)/10.f)+2.5) * x_multiplier;
    }

    Entity::virtDoUpdate(iCurrentTime);

    if (getEngine()->getModifiedTime()-previous_hit_time > 1000) {
        std::array<float, 4> my_bbox = getBBox();
        std::array<float, 4> target_bbox = target->getBBox();
        if (overlaps(my_bbox.at(0), my_bbox.at(1), my_bbox.at(2), my_bbox.at(3), 
        target_bbox.at(0), target_bbox.at(1), target_bbox.at(2), target_bbox.at(3))) {
            std::cout << "HIT" << std::endl;
            previous_hit_time = getEngine()->getModifiedTime();
            float deltax = target->getXfloat() - x_f;
            float deltay = target->getYfloat() - y_f;
            float deltamag = sqrtf(deltax * deltax + deltay * deltay);
            std::cout << deltax << ", " << deltay << std::endl;
            deltax /= deltamag;
            deltay /= deltamag;
            target->applyImpulse(deltax * 3, deltay * 3);
            applyImpulse(-deltax * 2, -deltay * 2);
            target->changehp(-2);
        }
    }
};

void Slime::virtDraw() {
    Entity::virtDraw();
}

bool Slime::beHit(float dx, float dy) {
    applyImpulse(dx*4, -4);
    hp--;
    if (hp <= 0) return true;
    return false;
}