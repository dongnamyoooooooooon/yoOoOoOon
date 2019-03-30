#pragma once
#include "wall.h"
class wallZone_01 : public wall
{
public:
	wallZone_01();
	~wallZone_01();


	HRESULT init(string imgName, int idxX, int idxY, bool isTorch);
	void release();
	void update();
	void render();
};

