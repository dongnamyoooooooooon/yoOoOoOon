#pragma once
#include "parentObj.h"
class floorZone_02 : public parentObj
{
private:
	bool _isCrossStripes;

	int _frameX;
	int _frameY;

	int _count;

	int _num;


public:
	floorZone_02();
	~floorZone_02();

	HRESULT init(int idxX, int idxY);
	void release();
	void update();
	void render();

	void checkFever(int idxX, int idxY);
	void floorAni();

	UINT getTileX() { return _tileX; }
	UINT getTileY() { return _tileY; }
};

