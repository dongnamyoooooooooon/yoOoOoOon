#pragma once
#include "parentObj.h"
class floorShop : public parentObj
{
private:
	

public:
	floorShop();
	~floorShop();

	HRESULT init(int idxX, int idxY);
	void release();
	void update();
	void render();
};

