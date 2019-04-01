#pragma once
#include "parentObj.h"
class floorWater : public parentObj
{
private:
	bool _isCrossStripes;

	int _frameX;
	int _frameY;

	int _count;


public:
	floorWater();
	~floorWater();

	HRESULT init(int idxX, int idxY);
	void release();
	void update();
	void render();

	void checkFever(int idxX, int idxY);
	void floorAni();

	UINT getTileX() { return _tileX; }
	UINT getTileY() { return _tileY; }
};

