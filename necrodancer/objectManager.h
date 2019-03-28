#pragma once
#include "singletonBase.h"
#include "gameNode.h"
#include "parentObj.h"
#include <algorithm>


class parentObj;
class objectManager : public singletonBase<objectManager>, public gameNode
{
private:
	// =================================
	//			   므애앱
	// =================================

	UINT	_tileX;				//맵크기X
	UINT	_tileY;				//맵크기Y


	vector<vector<parentObj*>> _vvObjTile;
	vector<vector<parentObj*>> _vvFloorTile;

	vector<parentObj*> _vObj;
	vector<parentObj*>::iterator _viObj;
	vector<parentObj*>::iterator _viObj2;

	// =================================
	//			   사 운 드
	// =================================

	vector<tagNote>									_vBeat;			//비트 담을곳
	vector<tagNote>::iterator						_viBeat;		//비트 담을곳

	map<string, vector<tagNote>>					_mBeat;			//중복방지용
	map<string, vector<tagNote>>::iterator			_miBeat;		//중복방지용

	string											_musicKey;
	float											_volume;

	// =================================
	//				비 트
	// =================================

	string									_beatKey;
	D2D1_RECT_F								_failBeat;			//빗나감
	D2D1_RECT_F								_successBeat;		//성공
	const char*								_beatFile;
	int										_playTime;
	float									_beatAlpha;


	// =================================
	//			   플레이어
	// =================================

	bool	_isPlayerAlive;
	int		_killCount;


public:
	objectManager();
	~objectManager();

	void release();
	void update();
	void render();


	//오브젝트
	void vectorClear();					//벡터클리어용 함수
	void objectSort_IndexY();			//오브젝트정렬(Y)
	void objectSort_IndexX();			//오브젝트정렬(X)
	void allObjectUpdate();
	void deleteObject(parentObj* obj);

	//비트
	void createBeat();


	//오브젝트생성
	parentObj* objectPush(parentObj obj);
	parentObj* createFloor(parentObj obj);
	parentObj* createWall(parentObj obj);
	parentObj* createItem(parentObj obj);
	parentObj* createEnemy(parentObj obj);
	parentObj* createTrap(parentObj obj);
	parentObj* createPlayer(parentObj obj);


	
	void setTileX(UINT x) { _tileX = x; }
	void setTileY(UINT y) { _tileY = y; }

	void setIsPlayerAlive() { _isPlayerAlive = true; }

	vector<parentObj*> getVObj() { return _vObj; }
	vector<parentObj*>::iterator getVIObj() { return _viObj; }


	//타일
	parentObj* getCheckObj(int x, int y) { return _vvObjTile[y][x]; }
	void setTileIdx(parentObj* obj, UINT idxX, UINT idxY)
	{
		_vvObjTile[obj->getIdxY()][obj->getIdxX()] = nullptr;
		obj->setIdxX(idxX);
		obj->setIdxY(idxY);
		_vvObjTile[idxY][idxX] = obj;
	}


};

