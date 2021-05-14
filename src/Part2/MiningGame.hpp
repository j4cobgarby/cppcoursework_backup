#ifndef MININGGAME_HPP
#define MININGGAME_HPP

#include "../BaseEngine.h"
#include "AnimatedImage.hpp"
#include "SDL_surface.h"
#include "WorldTileManager.hpp"
#include "../ExampleFilterPointClasses.h" 
#include "Player.hpp"
#include "Entity.hpp"
#include "EventHandler.hpp"
#include "Inventory.hpp"
#include <map>

class GameState : public DisplayableObjectContainer {
	GameState(BaseEngine* eng);

	void onChangeTo() {}

	DisplayableObject *getObject(int i);
	int getObjectsCount();

    virtual void virtMainLoopStartIteration() {}

	virtual void virtMainLoopPreUpdate() {}
	virtual void virtMainLoopDoBeforeUpdate() {}
	virtual void virtMainLoopDoAfterUpdate() {}
	virtual void virtMainLoopPostUpdate() {}
};

class MiningGameEngine : public BaseEngine {
public:
    MiningGameEngine();

    virtual void virtSetupBackgroundBuffer() override;
	virtual int virtInitialiseObjects() override;
	virtual void virtMainLoopStartIteration() override;
	virtual void virtDrawStringsUnderneath() override;
	virtual void virtDrawStringsOnTop() override;
	virtual void virtMouseDown(int btn, int x, int y) override;
	virtual void virtKeyDown(int key) override;
	virtual void copyAllBackgroundBuffer() override;
	virtual void virtMainLoopPreUpdate() override;
	virtual void virtMainLoopDoBeforeUpdate() override;
	virtual void virtMainLoopDoAfterUpdate() override;
	virtual void virtMainLoopPostUpdate() override;

	int getTranslateX() {return filter_translate.getXOffset();}
	int getTranslateY() {return filter_translate.getYOffset();}
	FilterPointsTranslation *getTranslation() {return &filter_translate;}

	void setFilterEnabled(bool enabled);

	void changeState(std::string state_name);
private:
	GameState *current_state;
	std::map<std::string, GameState> states;

	FilterPointsTranslation filter_translate;
	FilterPointsScaling filter_scale;

	std::vector<EventHandler *> event_handlers;

	Player *player;
	Inventory *player_inv;

	WorldTilesObject *tiles;

	int seed;
	float bg_offset;
};

#endif