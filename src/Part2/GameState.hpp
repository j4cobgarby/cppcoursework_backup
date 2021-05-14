#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "../DisplayableObject.h"
#include "../DisplayableObjectContainer.h"
#include <vector>
#include "../BaseEngine.h"
#include "../ExampleFilterPointClasses.h"

class MiningGameEngine : public BaseEngine {
public:
	int getTranslateX();
	int getTranslateY();
	FilterPointsTranslation *getTranslation();

	void setFilterEnabled(bool enabled);

	void changeState(std::string state_name);
};

class GameState : public DisplayableObjectContainer {
protected:
    std::vector<DisplayableObject*> objects;
	std::string nextState;
	BaseEngine *eng;
public:
	GameState(MiningGameEngine *eng) {
		nextState = "";
		this->eng = eng;
	}

	void onChangeTo() {}

	DisplayableObject *getObject(int i) {return objects.at(i);}
	int getObjectsCount() {return objects.size();}

    virtual void virtMainLoopStartIteration() {}

	virtual void virtMainLoopPreUpdate() {}
	virtual void virtMainLoopDoBeforeUpdate() {}
	virtual void virtMainLoopDoAfterUpdate() {}
	virtual void virtMainLoopPostUpdate() {}
};

#endif