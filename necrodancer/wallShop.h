#pragma once
#include "wall.h"
class wallShop : public wall
{
public:
	wallShop();
	~wallShop();

	HRESULT init(string imgName, int idxX, int idxY, bool isTorch);
	void release();
	void update();
	void render();
};

