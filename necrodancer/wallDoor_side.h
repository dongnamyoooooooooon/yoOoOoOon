#pragma once
#include "wall.h"
class wallDoor_side : public wall
{
public:
	wallDoor_side();
	~wallDoor_side();

	HRESULT init(string imgName, int idxX, int idxY, bool isTorch);
	void release();
	void update();
	void render();
};

