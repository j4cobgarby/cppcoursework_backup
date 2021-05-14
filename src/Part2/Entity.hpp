#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "AnimatedImage.hpp"
#include "WorldTileManager.hpp"

class Entity : public AnimatedImageObject {
public:
    Entity(BaseEngine *eng, float x, float y, float bbox_left, float bbox_right, 
        float bbox_top, float bbox_bottom, WorldTileManager *front, WorldTileManager *back, bool topleftorigin = true, bool visible = true);

    // Apply gravity and apply damping on velocity
    // Do collisions with world tiles
    virtual void virtDoUpdate(int iCurrentTime) override;
    virtual void virtDraw() override;
protected:
    float x_f;
    float y_f;

    float vel_x;
    float vel_y;

    float bbox_left;
    float bbox_right;
    float bbox_top;
    float bbox_bottom;

    WorldTileManager *tiles_front;
    WorldTileManager *tiles_back;

    bool overlaps(float ax_l, float ax_r, float ay_t, float ay_b,
        float bx_l, float bx_r, float by_t, float by_b);
    bool try_move(float vx, float vy); // Return true if collided
};

#endif