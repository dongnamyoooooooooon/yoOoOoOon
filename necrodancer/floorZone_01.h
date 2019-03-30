#pragma once
#include "parentObj.h"
#include "mapTool.h"

class floorZone_01 : public parentObj
{
private:
	bool _isCrossStripes;

	int _frameX;
	int _frameY;
	
	int _count;

public:
	floorZone_01();
	~floorZone_01();

	HRESULT init(int idxX, int idxY);
	void release();
	void update();
	void render();

	void checkFever(int idxX, int idxY);
	void floorAni();

	UINT getTileX() { return _tileX; }
	UINT getTiray() { return _tiray; }


};

