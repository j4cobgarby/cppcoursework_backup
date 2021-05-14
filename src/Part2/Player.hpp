#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../DisplayableObject.h"
#include "AnimatedImage.hpp"
#include "WorldTileManager.hpp"
#include "Entity.hpp"
#include "EventHandler.hpp"
#include "../ExampleFilterPointClasses.h"
#include "Inventory.hpp"

#define PLAYER_WALK_SPEED 0.06

class Player : public Entity, public EventHandler {
private:
    int hp;
    int xp;

    bool facing_right;
    bool on_ground;

    FilterPointsTranslation *translation;

    Inventory *inventory;
public:
    Player(BaseEngine *eng, WorldTileManager *front, WorldTileManager *back, 
        FilterPointsTranslation *translation, float x, float y);

    bool overlaps(float ax_l, float ax_r, float ay_t, float ay_b,
        float bx_l, float bx_r, float by_t, float by_b);
    bool try_move(float vx, float vy); // Return true if collided

    virtual void virtDoUpdate(int iCurrentTime) override;
    virtual void virtDraw() override;

    void handleMouseDown(int btn, int x, int y) override;
    void handleKeyDown(int key) override;

    void jump();

    void assignInventory(Inventory *inv) {inventory = inv;}
};

#endif