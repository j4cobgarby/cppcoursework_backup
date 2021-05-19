#include "../header.h"
#include "Form.hpp"
#include "MiningGame.hpp"
#include "SDL_keycode.h"
#include "Settings.hpp"
#include "SDL_video.h"
#include "StateMainmenu.hpp"
#include "Settings.hpp"
#include "WorldGen.hpp"
#include "WorldTileManager.hpp"
#include "Inventory.hpp"

#include "GlobalState.hpp"
#include <filesystem>
#include <stdexcept>
#include <string>

namespace fs = std::filesystem;

WorldTilesObject *worldTiles = nullptr;
fs::path worldFolder;
bool newWorld;

StateMainmenu::StateMainmenu(MiningGameEngine *eng) :
    GameState(eng) {
}

void StateMainmenu::onChangeTo() {
    nextState = "";
    eng->setFilterEnabled(false);
    objects.clear();
    event_handlers.clear();
    menu = new Form(eng, 10, 10, 400, eng->getWindowHeight()-20);

    menu->addItem(new FILabel(menu, 0, "Enter your world name:"), "label1");
    menu->addItem(new FITextField(menu, 1), "inputloadworldname");
    menu->addItem(new FIButton(menu, 2,
        [=]() -> std::string {
            FITextField *it = static_cast<FITextField*>(menu->getItem("inputloadworldname"));
            if (!it) return "";
            
            worldFolder = fs::path("worlds") / it->getValue();
            fs::path worlddata = worldFolder / "data.world";
            if (fs::exists(worlddata)) {
                worldTiles = new WorldTilesObject(eng, "block.png", "block_dark.png");
                worldTiles->loadFromFile(worlddata);
                newWorld = false;
                setNextState("ingame");
            }
            return "";
        }, 
        "Enter World"), "btn1");
        menu->addItem(new FIButton(menu, 3,
        [=]() -> std::string {
            FITextField *it = static_cast<FITextField*>(menu->getItem("inputloadworldname"));
            if (!it) return "";
            worldFolder = fs::path("worlds") / it->getValue();
            fs::remove_all(worldFolder);
            return "";   
        },"Delete World"), "btndelete");
    menu->addItem(new FILabel(menu, 4, "~~~"), "label4");
    menu->addItem(new FILabel(menu, 5, "Or, name a new world:"), "label2");
    menu->addItem(new FITextField(menu, 6), "inputnewworldname");
    menu->addItem(new FILabel(menu, 7, "And pick a seed:"), "label3");
    menu->addItem(new FITextField(menu, 8), "inputseed");
    menu->addItem(new FIButton(menu, 9,
        [=]() -> std::string {
            try {
                int new_seed = std::stoi(menu->getItem("inputseed")->getValue());

                if (menu->getItem("inputnewworldname")->getValue().size() == 0) return "";

                worldFolder = fs::path("worlds")/menu->getItem("inputnewworldname")->getValue();

                if (!fs::exists(fs::path("worlds")/menu->getItem("inputnewworldname")->getValue())) {
                    worldTiles = new WorldTilesObject(eng, "block.png", "block_dark.png");
                    WorldGen::generateWorld(new_seed, &worldTiles->tiles_front, &worldTiles->tiles_back);
                    newWorld = true;
                    setNextState("ingame");
                }
            } catch (std::invalid_argument e) {
                std::cout << ":( bad seed" << std::endl;
            } 
            
            return "";
        },
        "Generate"), "btn2");
    menu->addItem(new FILabel(menu, 10, "~~~"), "div");
    menu->addItem(new FIButton(menu, 11,
        [=]() -> std::string {
            std::cout << "Goodbye :)" << std::endl;
            eng->setExitWithCode(0);
            return "";
        },
        "Quit Game"), "btnquit");

    menu->setActiveItem(1);
    objects.push_back(menu);
    event_handlers.push_back(menu);
    //eng->setFilterEnabled(false);
}

void StateMainmenu::virtSetupBackgroundBuffer() {
    eng->fillBackground(0xdbd0bc);
    eng->drawBackgroundString(450, 30, "Terrainia", 0x000000, eng->getFont("alagard.ttf", 70));
}

void StateMainmenu::virtMouseDown(int btn, int x, int y) {
    for (EventHandler *eh : event_handlers) {
        eh->handleMouseDown(btn, x, y);
    }
}

void StateMainmenu::virtKeyDown(int key) {
    for (EventHandler *eh : event_handlers) {
        eh->handleKeyDown(key);
    }
}