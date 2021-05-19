#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "AnimatedImage.hpp"
#include "WorldTileManager.hpp"
#include <array>

class Entity : public AnimatedImageObject {
public:
    Entity(BaseEngine *eng, float x, float y, float bbox_left, float bbox_right, 
        float bbox_top, float bbox_bottom, WorldTileManager *front, WorldTileManager *back, bool topleftorigin = true, bool visible = true);

    // Apply gravity and apply damping on velocity
    // Do collisions with world tiles
    virtual void virtDoUpdate(int iCurrentTime) override;
    virtual void virtDraw() override;

    float getXfloat() {return x_f;}
    float getYfloat() {return y_f;}
    void setXfloat(float x_f) {this->x_f = x_f;}
    void setYfloat(float y_f) {this->y_f = y_f;}

    void applyImpulse(float x, float y) {this->vel_x += x; this->vel_y += y;}

    std::array<float, 4> getBBox() {
        std::array<float, 4> ret;
        ret.at(0) = x_f + bbox_left;
        ret.at(1) = x_f + bbox_right;
        ret.at(2) = y_f + bbox_top;
        ret.at(3) = y_f + bbox_bottom;
        return ret;
    }
protected:
    float x_f;
    float y_f;

    float vel_x;
    float vel_y;

    float bbox_left;
    float bbox_right;
    float bbox_top;
    float bbox_bottom;

    bool on_ground;

    WorldTileManager *tiles_front;
    WorldTileManager *tiles_back;

    bool overlaps(float ax_l, float ax_r, float ay_t, float ay_b,
        float bx_l, float bx_r, float by_t, float by_b);
    bool try_move(float vx, float vy); // Return true if collided
};

#endif