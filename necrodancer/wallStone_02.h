#pragma once
#include "wall.h"
class wallStone_02 : public wall
{
public:
	wallStone_02();
	~wallStone_02();

	HRESULT init(string imgName, int idxX, int idxY, bool isTorch);
	void release();
	void update();
	void render();
};

