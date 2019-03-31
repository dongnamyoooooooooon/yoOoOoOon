#pragma once
#include "wall.h"
class wallDoor_front : public wall
{	
public:
	wallDoor_front();
	~wallDoor_front();

	HRESULT init(string imgName, int idxX, int idxY, bool isTorch);
	void release();
	void update();
	void render();
};

