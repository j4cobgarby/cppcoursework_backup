#include "../header.h"
#include "AnimatedImage.hpp"
#include "EventHandler.hpp"
#include "GlobalState.hpp"
#include "Inventory.hpp"
#include "MiningGame.hpp"
#include "SDL_keycode.h"
#include "SDL_surface.h"
#include "WorldGen.hpp"
#include "WorldTileManager.hpp"
#include "StateIngame.hpp"
#include "StateMainmenu.hpp"

#define NUM_TILES 7

MiningGameEngine::MiningGameEngine()
    :   filter_scale(4,4),
        filter_translate(0, 0, &filter_scale) {
    getForegroundSurface()->setDrawPointsFilter(&filter_translate);

    current_state = nullptr;

    states["ingame"] = new StateIngame(this);
    states["mainmenu"] = new StateMainmenu(this);
}

void MiningGameEngine::virtSetupBackgroundBuffer() {
    if (current_state) current_state->virtSetupBackgroundBuffer();
}

int MiningGameEngine::virtInitialiseObjects() {
    changeState("mainmenu");
    return 0;
}

void MiningGameEngine::virtDrawStringsUnderneath() {
}

void MiningGameEngine::virtDrawStringsOnTop() {
}

void MiningGameEngine::virtMouseDown(int btn, int x, int y) {
    if (current_state) {
        current_state->virtMouseDown(btn, x, y);
    }
}

void MiningGameEngine::virtKeyDown(int key) {
    if (current_state) {
        current_state->virtKeyDown(key);
    }
}

void MiningGameEngine::setFilterEnabled(bool enabled) {
    FilterPoints *f = enabled ? &filter_translate : nullptr;
	getForegroundSurface()->setDrawPointsFilter(f);
    getBackgroundSurface()->setDrawPointsFilter(f);
}

void MiningGameEngine::copyAllBackgroundBuffer() {
    float bg_offset;
    if (current_state) bg_offset = current_state->getBackgroundOffset();
    else bg_offset = 0;

    m_pForegroundSurface->copyRectangleFrom(m_pBackgroundSurface, 0, 0, getWindowWidth(), getWindowHeight(), bg_offset, 0);
    m_pForegroundSurface->copyRectangleFrom(m_pBackgroundSurface, getWindowWidth()-bg_offset,
        0, getWindowWidth(), getWindowHeight(), bg_offset-getWindowWidth(), 0);
}

void MiningGameEngine::changeState(std::string state_name) {
    std::cout << "Changing state to " << state_name << std::endl;

    GameState *target = states.at(state_name);
    target->onChangeTo();
    target->virtSetupBackgroundBuffer();

    drawableObjectsChanged();
    destroyOldObjects(true);
    createObjectArray(target->getObjectsCount());

    for (int i = 0; i < target->getObjectsCount(); i++) {
        storeObjectInArray(i, target->getObject(i));
    }

    redrawDisplay();

    current_state = target;
}

void MiningGameEngine::virtMainLoopStartIteration() {
    if (current_state) current_state->virtMainLoopStartIteration();
}

void MiningGameEngine::virtMainLoopPreUpdate() {
    if (current_state) current_state->virtMainLoopPreUpdate();
}

void MiningGameEngine::virtMainLoopDoBeforeUpdate() {
    if (current_state) current_state->virtMainLoopDoBeforeUpdate();
}

void MiningGameEngine::virtMainLoopDoAfterUpdate() {
    if (current_state) current_state->virtMainLoopDoAfterUpdate();
}

void MiningGameEngine::virtMainLoopPostUpdate() {
    if (current_state) {
        current_state->virtMainLoopPostUpdate();
        if (current_state->getNextState() != "") {
            changeState(current_state->getNextState());
        }
    }
}

void MiningGameEngine::setZoomLevel(float x, float y) {
    filter_scale.setStretch(x, y);
    redrawDisplay();
}