#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../DisplayableObject.h"
#include "AnimatedImage.hpp"

#define PLAYER_WALK_SPEED 0.06

class Player : public AnimatedImageObject {
private:
    int hp;
    int xp;

    // x and y as floats, for the physics
    // converted to int when needed to draw
    float x_f;
    float y_f;

    float vel_x, vel_y;
public:
    Player(BaseEngine *eng, float x, float y);

    virtual void virtDoUpdate(int iCurrentTime) override;
};

#endif