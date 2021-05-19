#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include "../SimpleImage.h"
#include "../DisplayableObject.h"

#define INVENTORY_COLS  8
#define INVENTORY_ROWS  8
#define INVENTORY_SLOTS INVENTORY_COLS * INVENTORY_ROWS

#define CELLSIZE        13

struct item_t {
    // Where the tile begins in the tilesheet (x)
    int icon_startx;

    int stack_size;

    bool canHit; // can it hit living things
    int hitDmg; // How much damage the item does to living things when hit with it

    bool canPlace; // if the item can be placed down in the world
    int placesBlockId; // the id of the block it places, if it canPlace

    bool breaksWood;
    bool breaksStone;
    bool breaksDirt;

    int goodBlockEfficiency; // how much damage it does to a block per hit which it is good at breaking
    int badBlockEfficiency; // how much damage per hit to a block that it isn't good at breaking
};

struct inventory_cell_t {
    int item_id;
    int count;
};

class Inventory : public DisplayableObject {
private:

    struct inventory_cell_t items[INVENTORY_SLOTS];

    SimpleImage spritesheet;

    int active_cell;

    void drawCell(int ox, int oy, int row, int column);
    void drawNumber(int n, int x, int y);
public:
    const struct item_t item_table[32] = {
        {0,64,  false,0,    true,1,     false,false,false,  0,0}, // Dirt
        {8,64,  false,0,    true,2,     false,false,false,  0,0}, // Grass
        {16,64, false,0,    true,3,     false,false,false,  0,0}, // Stone
        {24,64, false,0,    true,4,     false,false,false,  0,0}, // Trunk
        {32,64, false,0,    true,5,     false,false,false,  0,0}, // Leaf
        {40,64, false,0,    true,6,     false,false,false,  0,0}, // Water
        {48,64, false,0,    true,7,     false,false,false,  0,0}, // Sand

        {}, // Bow
        {}, // Arrow
        {72,1,  false,0,    false,0,    true,true,true,     1,1}, // Pickaxe
        {80,1,  true,1,     false,0,    false,false,false,  0,0}, // Sword
    };

    Inventory(BaseEngine *eng);

    void setSpritesheet(SimpleImage img) {
        spritesheet = img;
        spritesheet.setTransparencyColour(0x000000);
    }

    void incrStack(int cell);
    void decrStack(int cell);
    void setStack(int cell);
    int getStack(int cell);

    int findEmptyCell();

    // Adds an item to the inventory.
    // Tries to stack it with other items of the same type.
    // If cell is -1, it'll put it in the next available slot, if it
    // can't stack, or will stack if it can.
    // Otherwise, it will put it in the specificed cell
    bool add(int item_id, int cell = -1);

    void setCell(int cell, int item_id, int count) {
        items[cell].item_id = item_id;
        items[cell].count = count;
    }

    void setActiveCell(int i) {active_cell = i;}
    struct inventory_cell_t *getActiveCell() {return &(items[active_cell]);}

    void virtDraw() override;

    void loadFromFile();
    void saveToFile();
};

#endif