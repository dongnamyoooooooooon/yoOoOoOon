#pragma once
#include "wall.h"
class wallBoss : public wall
{
public:
	wallBoss();
	~wallBoss();

	HRESULT init(string imgName, int idxX, int idxY, bool isTorch);
	void release();
	void update();
	void render();
};

