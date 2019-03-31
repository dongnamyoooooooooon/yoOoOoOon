#pragma once
#include "wall.h"
class wallEnd : public wall
{
public:
	wallEnd();
	~wallEnd();

	HRESULT init(string imgName, int idxX, int idxY, bool isTorch);
	void release();
	void update();
	void render();
};

