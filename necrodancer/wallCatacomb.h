#pragma once
#include "wall.h"
class wallCatacomb : public wall
{
public:
	wallCatacomb();
	~wallCatacomb();


	HRESULT init(string imgName, int idxX, int idxY, bool isTorch);
	void release();
	void update();
	void render();
};

