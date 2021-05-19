#include "../header.h"
#include "GameState.hpp"

float GameState::getBackgroundOffset() {
    return bg_offset_x;
}

void GameState::onChangeTo() {}

void GameState::virtMainLoopStartIteration() {}

void GameState::virtSetupBackgroundBuffer() {}
void GameState::virtMainLoopPreUpdate() {}
void GameState::virtMainLoopDoBeforeUpdate() {}
void GameState::virtMainLoopDoAfterUpdate() {}
void GameState::virtMainLoopPostUpdate() {}

void GameState::virtKeyDown(int key) {}
void GameState::virtMouseDown(int btn, int x, int y) {std::cout << "Base state mouse" << std::endl;}

DisplayableObject *GameState::getObject(int i) {return objects.at(i);}
int GameState::getObjectsCount() {return objects.size();}