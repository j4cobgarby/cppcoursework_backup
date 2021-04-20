#ifndef MININGGAME_HPP
#define MININGGAME_HPP

#include "../BaseEngine.h"
#include "AnimatedImage.hpp"
#include "SDL_surface.h"
#include "WorldTileManager.hpp"
#include "../ExampleFilterPointClasses.h" 
#include "Player.hpp"

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
private:
	WorldTileManager tiles_back;
	WorldTileManager tiles_front;

	FilterPointsTranslation filter_translate;
	FilterPointsScaling filter_scale;

	std::vector<SimpleImage> tile_images;
	std::vector<SimpleImage> tile_images_bg;

	Player *player;

	DrawingSurface *block_surf;
};

#endif