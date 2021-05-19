#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "../DisplayableObject.h"
#include "../DisplayableObjectContainer.h"
#include <vector>
#include "../BaseEngine.h"
#include "../ExampleFilterPointClasses.h"
#include "EventHandler.hpp"

class MiningGameEngine;

class GameState : public DisplayableObjectContainer {
protected:
    std::vector<DisplayableObject*> objects;
	std::string nextState;
	MiningGameEngine *eng;
	std::vector<EventHandler *> event_handlers;
	float bg_offset_x;
public:
	GameState(MiningGameEngine *eng) {
		nextState = "";
		this->eng = eng;
	}

	virtual void onChangeTo();

	DisplayableObject *getObject(int i);
	int getObjectsCount();

    virtual void virtMainLoopStartIteration();

	virtual void virtSetupBackgroundBuffer();
	virtual void virtMainLoopPreUpdate();
	virtual void virtMainLoopDoBeforeUpdate();
	virtual void virtMainLoopDoAfterUpdate();
	virtual void virtMainLoopPostUpdate();

	virtual void virtKeyDown(int key);
	virtual void virtMouseDown(int btn, int x, int y);

	float getBackgroundOffset();

	void setNextState(std::string next) {nextState = next;}
	std::string getNextState() {return nextState;}
};

#endif