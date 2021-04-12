#ifndef MYDEMO_H
#define MYDEMO_H

#include "BaseEngine.h"
#include "MyDemoTileManager.hpp"

class Psyjg12Engine : public BaseEngine {
public:
	Psyjg12Engine(){
		counter = 0;
	}

	virtual void virtSetupBackgroundBuffer() override;
	virtual int virtInitialiseObjects() override;
	virtual void virtDrawStringsUnderneath() override;
	virtual void virtDrawStringsOnTop() override;
	virtual void virtMouseDown(int btn, int x, int y) override;
	virtual void virtKeyDown(int key) override;
private:
	int counter;
	Psyjg12TileManager tiles;
};

#endif
