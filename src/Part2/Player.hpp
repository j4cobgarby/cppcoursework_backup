#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../DisplayableObject.h"
#include "AnimatedImage.hpp"
#include "WorldTileManager.hpp"
#include "../ExampleFilterPointClasses.h" 

#define PLAYER_WALK_SPEED 0.06

class Player : public AnimatedImageObject {
private:
    int hp;
    int xp;

    bool facing_right;
    bool on_ground;

    // x and y as floats, for the physics
    // converted to int when needed to draw
    float x_f;
    float y_f;

    float vel_x, vel_y;

    WorldTileManager *tiles_front;
    WorldTileManager *tiles_back;

    FilterPointsTranslation *translation;
public:
    Player(BaseEngine *eng, WorldTileManager *front, WorldTileManager *back, 
        FilterPointsTranslation *translation, float x, float y);

    bool overlaps(float ax_l, float ax_r, float ay_t, float ay_b,
        float bx_l, float bx_r, float by_t, float by_b);
    bool try_move(float vx, float vy); // Return true if collided

    virtual void virtDoUpdate(int iCurrentTime) override;
    virtual void virtDraw() override;

    void jump();
};

#endif