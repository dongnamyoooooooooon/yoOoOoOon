#pragma once
#include "wall.h"
class wallZone_02 : public wall
{
public:
	wallZone_02();
	~wallZone_02();


	HRESULT init(string imgName, int idxX, int idxY, bool isTorch);
	void release();
	void update();
	void render();
};

