#pragma once
#include "wall.h"
class wallStone_Cracked_02 : public wall
{
public:
	wallStone_Cracked_02();
	~wallStone_Cracked_02();


	HRESULT init(string imgName, int idxX, int idxY, bool isTorch);
	void release();
	void update();
	void render();
};

