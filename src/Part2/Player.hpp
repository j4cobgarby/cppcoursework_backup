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

#define HEALTHBAR_LENGTH 28
#define HEALTHBAR_HEIGHT 3
#define HEALTHBAR_OVERLAY_LENGTH 32
#define HEALTHBAR_OVERLAY_HEIGHT 8

class Player : public Entity, public EventHandler {
private:
    int hp;
    int maxhp;
    int xp;

    bool facing_right;
    bool editing_front;

    FilterPointsTranslation *translation;

    Inventory *inventory;

    SimpleImage healthbarimg;

    void drawHealthBar();
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

    void changehp(int deltahp);

    bool reachable(int x, int y);
    bool checkOnGround();
};

#endif