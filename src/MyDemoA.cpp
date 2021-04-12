#include "header.h"
#include "SDL_mouse.h"
#include "SimpleImage.h"

// This is a basic implementation, without fancy stuff

#include "BaseEngine.h"
#include "MyDemoA.h"
#include "ImageManager.h"
#include "DemoAObject.hpp"
#include "Follower.hpp"

void Psyjg12Engine::virtSetupBackgroundBuffer()
{
	fillBackground(0x000000);

	SimpleImage img = ImageManager::loadImage("space.png", false);
	img.renderImage(getBackgroundSurface(), 0, 0, getWindowWidth()/2 - img.getWidth()/2, 
		getWindowHeight()/2 - img.getHeight()/2, img.getWidth(), img.getHeight());

	// Create space objects
	for (int i = 0; i < 200; i++) {
		int mid_x = rand() % getWindowWidth();
		int mid_y = rand() % getWindowHeight();

		int rnd = rand() % 20;
		if (rnd <= 16) {
			for (int x_offset = -2; x_offset <= 2; x_offset++) {
				setBackgroundPixel(mid_x + x_offset, mid_y, 0xffffff);
			}

			for (int y_offset = -2; y_offset <= 2; y_offset++) {
				setBackgroundPixel(mid_x, mid_y + y_offset, 0xffffff);
			}
		} else if (rnd <= 18) {
			drawBackgroundOval(mid_x, mid_y, mid_x+20, mid_y+20, rand() % 0xffffff);
		} else {
			drawBackgroundOval(mid_x, mid_y, mid_x+20, mid_y+20, rand() % 0xffffff);
			drawBackgroundOval(mid_x-10, mid_y+8, mid_x+30, mid_y+12, rand() % 0xffffff);
		}
	}

	tiles.drawAllTiles(this, getBackgroundSurface());
}

int Psyjg12Engine::virtInitialiseObjects()
{
	drawableObjectsChanged();
	destroyOldObjects(true);
	createObjectArray(2);

	SpaceshipObject *sship = new SpaceshipObject(this, 100, 100, &tiles);

	storeObjectInArray(0, sship);
	storeObjectInArray(1, new FollowerObject(this, 600, 600, sship));
	return 0;
}

void Psyjg12Engine::virtDrawStringsUnderneath() {
	drawBackgroundString(10, 10, "psyjg12", 0x00ffff);
}

void Psyjg12Engine::virtDrawStringsOnTop() {
	char buf[64];
	static int prevTime = getRawTime();
	static int r = rand() % 0xffffff;

	if (getRawTime() - prevTime >= 500) {
		prevTime = getRawTime();
		r = rand() % 0xffffff;
	}

	sprintf(buf, "Counter: %d, Colour: 0x%06x", counter, r);

	drawForegroundString(10, 100, buf, r);
}

void Psyjg12Engine::virtMouseDown(int btn, int x, int y) {
	if (btn == SDL_BUTTON_LEFT) {
		counter++;
	} else if (btn == SDL_BUTTON_RIGHT) {
		counter--;
	}
}

void Psyjg12Engine::virtKeyDown(int key) {
	switch (key)
	{
	case SDLK_ESCAPE:
		setExitWithCode(0);
		break;
	}
}
