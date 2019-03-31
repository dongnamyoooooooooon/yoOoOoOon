#pragma once
#include "parentObj.h"
class floorStair_nothing : public parentObj
{
private:

public:
	floorStair_nothing();
	~floorStair_nothing();

	HRESULT init(int idxX, int idxY);
	void release();
	void update();
	void render();
};

