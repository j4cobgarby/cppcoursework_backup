#include "../header.h"

#include "AnimatedImage.hpp"
#include "Entity.hpp"
#include "ExtraDrawing.hpp"
#include "Inventory.hpp"
#include "MiningGame.hpp"
#include "Player.hpp"
#include "SDL_keycode.h"
#include "StateIngame.hpp"
#include "WorldTileManager.hpp"
#include "../UtilCollisionDetection.h"

Player::Player(BaseEngine *eng, WorldTileManager *front, WorldTileManager *back,
    FilterPointsTranslation *translation, float x, float y)
    : Entity(eng, x, y, 2, 4, 0, 15, front, back) { 
    this->hp = 20;
    this->maxhp = 20;
    this->xp = 0;
    this->facing_right = true;
    this->tiles_back = back;
    this->tiles_front = front;
    this->translation = translation;
    this->editing_front = true;

    healthbarimg = ImageManager::loadImage("healthbar_overlay.png", true);
    healthbarimg.setTransparencyColour(0x000000);

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
                overlaps(new_x+2, new_x+4, new_y, new_y+15, c*8, c*8+7, r*8, r*8+7)) {
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

    if (getEngine()->isKeyPressed(SDLK_a)) {
        moving = true;
        vel_x -= PLAYER_WALK_SPEED;
        facing_right = false;
    } if (getEngine()->isKeyPressed(SDLK_d)) {
        moving = true;
        vel_x += PLAYER_WALK_SPEED;
        facing_right = true;
        
    }

    std::string current_anim = getImage()->getCurrentAnimation();

    if (moving) {
        if (facing_right && current_anim != "run_right") getImage()->setCurrentAnimation("run_right");
        if (!facing_right && current_anim != "run_left") getImage()->setCurrentAnimation("run_left");
    } else {
        if (facing_right && current_anim != "idle_right") getImage()->setCurrentAnimation("idle_right");
        if (!facing_right && current_anim != "idle_left") getImage()->setCurrentAnimation("idle_left");
    }

    Entity::virtDoUpdate(iCurrentTime);

    int newTransX, newTransY;

    if (getEngine()->isKeyPressed(SDLK_z)) {
        ((MiningGameEngine *)getEngine())->setZoomLevel(7, 7);
        newTransX = -(m_iCurrentScreenX - 8 * 10);
        newTransY = -(m_iCurrentScreenY - 8 * 6);
    } else {
        newTransX = -(m_iCurrentScreenX - 8 * 16);
        newTransY = -(m_iCurrentScreenY - 8 * 10);
        ((MiningGameEngine *)getEngine())->setZoomLevel(4, 4);
    }

    newTransX = newTransX < 0 ? newTransX : 0;
    newTransX = newTransX > -(WORLD_TILES_X*4) + 8 ? newTransX : -(WORLD_TILES_X*4) + 8;

    
    newTransY = newTransY < 0 ? newTransY : 0;
    newTransY = newTransY > -(WORLD_TILES_Y*4) + 8 ? newTransY : -(WORLD_TILES_Y*4) + 8;

    translation->setOffset(newTransX, newTransY);
    AnimatedImageObject::virtDoUpdate(iCurrentTime);
}

void Player::virtDraw() {
    Entity::virtDraw();

    if (!getEngine()->isKeyPressed(SDLK_z)) {
        drawHealthBar();
    }

    if (inventory->getActiveCell()->count > 0 && 
            inventory->item_table[inventory->getActiveCell()->item_id].canPlace ||
            inventory->item_table[inventory->getActiveCell()->item_id].breaksDirt) {
        int bx = (getEngine()->getCurrentMouseX() >> 3) << 3;
        int by = (getEngine()->getCurrentMouseY() >> 3) << 3;
        int bx_end = bx + 7;
        int by_end = by + 7;

        if (reachable(bx, by)) {
            if (translation->filterConvertVirtualToRealXPosition(bx) < 0 
                || translation->filterConvertVirtualToRealXPosition(bx_end) >= getEngine()->getWindowWidth() 
                || translation->filterConvertVirtualToRealYPosition(by) < 0 
                || translation->filterConvertVirtualToRealYPosition(by_end) >= getEngine()->getWindowHeight()) return;

            if (editing_front) {
                ExtraDrawing::drawRectangleOutline(getEngine()->getForegroundSurface(), bx, by, bx_end, by_end, 0xffff00);
            } else {
                ExtraDrawing::drawDottedRectangle(getEngine()->getForegroundSurface(), bx, by, bx_end, by_end, 0xffff00);
            }
        }
    }
}

void Player::jump() {
    if (on_ground) {
        vel_y -= 4;
    }
}

void Player::handleMouseDown(int btn, int x, int y) {
    if (getEngine()->isKeyPressed(SDLK_TAB)) {
        int cell_x = (x + translation->getXOffset()) / CELLSIZE;
        int cell_y = (y + translation->getYOffset()) / CELLSIZE;

        if (cell_x < 0 || cell_y < 0 ) return;

        if (cell_x < INVENTORY_COLS && cell_y < INVENTORY_ROWS) {
            int cell_i = cell_y * INVENTORY_COLS + cell_x;
            inventory->setActiveCell(cell_i);
            return;
        }
    }

    // If the cell selected was not in the inventory, then the user is probably trying to
    // interact with the world, rather than inventory, so just fall through to here.

    WorldTileManager *active_tiles = editing_front ? tiles_front : tiles_back;

    if (reachable(x, y)) {
        if (btn == 1 && inventory->getActiveCell()->count > 0 && 
        inventory->item_table[inventory->getActiveCell()->item_id].breaksDirt) {
            int broken_block = active_tiles->getMapValue(x/8, y/8);

            if (broken_block != 0) {
                active_tiles->setMapValue(x/8, y/8, 0);

                if (inventory) {
                    inventory->add(broken_block-1);
                }
            }
        }

        if (btn == 1 && inventory->getActiveCell()->count > 0 && 
        inventory->item_table[inventory->getActiveCell()->item_id].canHit) {
            ((StateIngame*)((MiningGameEngine*)getEngine())->getCurrentState())
                ->playerHit(x, y, getXCentre(), getYCentre());
        }

        if (btn == 3) { // Right click to place block
            int bx = x/8;
            int by = y/8;

            if (!overlaps(m_iCurrentScreenX+2, m_iCurrentScreenX+4, m_iCurrentScreenY, m_iCurrentScreenY+15, 
                    bx*8, bx*8+7, by*8, by*8+7)) {
                if (inventory) {
                    struct inventory_cell_t *active_cell = inventory->getActiveCell();

                    if (inventory->item_table[active_cell->item_id].canPlace) {
                        if (active_cell->count > 0) {
                            active_tiles->setMapValue(x/8, y/8, 
                                inventory->item_table[active_cell->item_id].placesBlockId);

                            active_cell->count--;
                        }
                    }
                }
            }
        }
    }
}

void Player::handleKeyDown(int key) {
    if (key == SDLK_w) {
        jump();
    }
    if (key == SDLK_LCTRL) {
        editing_front = !editing_front;
    }
}

void Player::drawHealthBar() {
    int startx = - ((MiningGameEngine*)getEngine())->getTranslateX() + INVENTORY_COLS * CELLSIZE + 10;
    int starty = - ((MiningGameEngine*)getEngine())->getTranslateY();
    if (startx < 0) startx = 0;
    if (starty < 0) starty = 0;

    getEngine()->getForegroundSurface()->drawRectangle(startx+2, starty+1, 
        startx+1+(int)(((float)hp / (float)maxhp) * (float)HEALTHBAR_LENGTH), starty+HEALTHBAR_HEIGHT, 0xff0000);
    healthbarimg.renderImage(getEngine()->getForegroundSurface(), 
        0, 0, startx, starty, HEALTHBAR_OVERLAY_LENGTH, HEALTHBAR_OVERLAY_HEIGHT);
}

void Player::changehp(int deltahp) {
    hp += deltahp;
    if (hp <= 0) {
        std::cout << "Dead." << std::endl;
        hp = 0;
    }
}

bool Player::reachable(int x, int y) {
    float dx = x+4 - getXCentre();
    float dy = y+4 - getYCentre();
    float dist = sqrt(dx*dx + dy*dy);
    return dist <= 40.f;
}

bool Player::checkOnGround() {
}