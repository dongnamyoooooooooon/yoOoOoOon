#pragma once
#include "singletonBase.h"

class parentObj;

class objectManager : public singletonBase<objectManager>
{
private:
	UINT	_tileX;				//∏ ≈©±‚X
	UINT	_tileY;				//∏ ≈©±‚Y


	vector<vector<parentObj*>> _vvObjTile;
	vector<vector<parentObj*>> _vvFloorTile;

	vector<parentObj*> _vObj;
	vector<parentObj*>::iterator _viObj;
	vector<parentObj*>::iterator _viObj2;

public:
	objectManager();
	~objectManager();


	void vectorClear();

	parentObj* objectPush(parentObj obj);



	void setTileX(UINT x) { _tileX = x; }
	void setTileY(UINT y) { _tileY = y; }

};

