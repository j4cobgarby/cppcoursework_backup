#include "../header.h"

#include "Inventory.hpp"
#include "MiningGame.hpp"
#include "SDL_keycode.h"
#include <string>

Item::Item(std::string icnpath, int icon_number, bool canHit, bool canPlace,
        bool breaksWood, bool breaksStone, bool breaksDirt, int goodBlockEfficiency, int badBlockEfficiency, 
        int placesBlockId, int hitDmg, int stack_size) 
:   icon(ImageManager::loadImage(icnpath, true)), icon_startx(icon_number*8), stack_size(stack_size), canHit(canPlace), 
    hitDmg(hitDmg), canPlace(canPlace), placesBlockId(placesBlockId), breaksWood(breaksWood), breaksStone(breaksStone),
    breaksDirt(breaksDirt), goodBlockEfficiency(goodBlockEfficiency), badBlockEfficiency(badBlockEfficiency)
{
    icon.setTransparencyColour(0x000000);
    amount = 0;
}

Inventory::Inventory(BaseEngine *eng) :
    DisplayableObject(eng) {

    for (int i = 0; i < INVENTORY_SLOTS; i++) {
        items[i].item_id = -1;
        items[i].count = 0;
    }

    active_cell = 0;
}

void Inventory::virtDraw() {
    if (getEngine()->isKeyPressed(SDLK_TAB)) {
        int startx = - ((MiningGameEngine*)getEngine())->getTranslateX();
        int starty = - ((MiningGameEngine*)getEngine())->getTranslateY();
        if (startx < 0) startx = 0;
        if (starty < 0) starty = 0;

        getEngine()->getForegroundSurface()->drawRectangle(startx, starty, startx+CELLSIZE*INVENTORY_COLS, starty+CELLSIZE*INVENTORY_ROWS, 0xdbd0bc);

        for (int r = 0; r < INVENTORY_ROWS; r++) {
            for (int c = 0; c < INVENTORY_COLS; c++) {
                drawCell(startx, starty, r, c);
            }
        }

        int active_startx = startx + CELLSIZE * (active_cell % INVENTORY_COLS);
        int active_starty = starty + CELLSIZE * (active_cell / INVENTORY_COLS);

        getEngine()->getForegroundSurface()->drawLine(active_startx, active_starty, active_startx + CELLSIZE, active_starty, 0xffffff);
        getEngine()->getForegroundSurface()->drawLine(active_startx + CELLSIZE, active_starty, active_startx + CELLSIZE, active_starty + CELLSIZE, 0xffffff);
        getEngine()->getForegroundSurface()->drawLine(active_startx + CELLSIZE, active_starty + CELLSIZE, active_startx, active_starty+CELLSIZE, 0xffffff);
        getEngine()->getForegroundSurface()->drawLine(active_startx, active_starty+CELLSIZE, active_startx, active_starty, 0xffffff);
    }
}

void Inventory::drawCell(int ox, int oy, int row, int column) {
    struct inventory_cell_t *theCell = &(items[row * INVENTORY_COLS + column]);

    int startc = ox + column * CELLSIZE;
    int startr = oy + row * CELLSIZE;

    getEngine()->getForegroundSurface()->drawLine(startc, startr, startc + CELLSIZE, startr, 0x3f3c37);
    getEngine()->getForegroundSurface()->drawLine(startc + CELLSIZE, startr, startc + CELLSIZE, startr + CELLSIZE, 0x3f3c37);
    getEngine()->getForegroundSurface()->drawLine(startc + CELLSIZE, startr + CELLSIZE, startc, startr+CELLSIZE, 0x3f3c37);
    getEngine()->getForegroundSurface()->drawLine(startc, startr+CELLSIZE, startc, startr, 0x3f3c37);

    if (theCell->item_id >= 0 && theCell->count > 0) {
        const struct item_t *theItem = &(item_table[theCell->item_id]);
        spritesheet.renderImage(getEngine()->getForegroundSurface(), theItem->icon_startx, 0, startc+1, startr+5, 8, 8);
        drawNumber(theCell->count, startc+1, startr+1);
    }
}

int Inventory::findEmptyCell() {
    for (int i = 0; i < INVENTORY_SLOTS; i++) {
        if (items[i].count == 0) {
            return i;
        }
    }
    return -1;
}

bool Inventory::add(int item_id, int cell) {
    if (cell == -1) {
        for (int i = 0; i < INVENTORY_SLOTS; i++) {
            if (items[i].item_id == item_id && items[i].count < item_table[item_id].stack_size
            && items[i].count > 0) {
                cell = i;
            }
        }

        if (cell == -1) {
            cell = findEmptyCell();
        }

        if (cell == -1) {
            return false;
        }
    }

    // Now cell is a valid cell in the inventory
    items[cell].item_id = item_id;
    items[cell].count++;

    return true;
}

void Inventory::drawNumber(int n, int x, int y) {
    int i = 0;

    do {
        int digit = n % 10;
        ImageManager::loadImage("numbers.png", true).renderImage(getEngine()->getForegroundSurface(), 
            digit*3, 0, x+9-i*4, y, 3, 5);
        n /= 10;
        i++;
    } while (n);
}