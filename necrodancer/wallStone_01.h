#pragma once
#include "wall.h"
class wallStone_01 : public wall
{
public:
	wallStone_01();
	~wallStone_01();

	HRESULT init(string imgName, int idxX, int idxY, bool isTorch);
	void release();
	void update();
	void render();
};

