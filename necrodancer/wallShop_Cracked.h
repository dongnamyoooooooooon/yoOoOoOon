#pragma once
#include "wall.h"
class wallShop_Cracked : public wall
{
public:
	wallShop_Cracked();
	~wallShop_Cracked();

	HRESULT init(string imgName, int idxX, int idxY, bool isTorch);
	void release();
	void update();
	void render();
};

