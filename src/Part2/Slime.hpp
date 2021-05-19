#ifndef SLIME_HPP
#define SLIME_HPP

#include "Entity.hpp"
#include "WorldTileManager.hpp"
#include "Player.hpp"

class Slime : public Entity {
private:
    int hp;
    Player *target;
    int previous_jump_time;
    int previous_hit_time;
public:
    Slime(BaseEngine *eng, WorldTileManager *front, WorldTileManager *back, float x, float y, Player *target);

    virtual void virtDoUpdate(int iCurrentTime) override;
    virtual void virtDraw() override;

    bool beHit(float dx, float dy);
};

#endif