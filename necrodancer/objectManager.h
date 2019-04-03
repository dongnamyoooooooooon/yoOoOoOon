#pragma once
#include "singletonBase.h"
#include "gameNode.h"
#include "parentObj.h"
#include "player.h"
#include <algorithm>

class floorZone_01;
class floorZone_02;
class floorBoss;
class floorShop;
class floorWater;
class floorStair;
class floorStair_nothing;
class weapon_dagger_basic;
class weapon_broadsword_basic;
class shovel_basic;
class armor_Gi;
class armor_leather;
class armor_chainmail;
class armor_platemail;
class armor_heavyplate;
class armor_obsidian;
class armor_glass;
class torch_basic;
class wallZone_01;
class wallZone_02;
class wallShop;
class wallShop_Cracked;
class wallStone_01;
class wallStone_02;
class wallCatacomb;
class wallBoss;
class wallStone_Cracked_01;
class wallStone_Cracked_02;
class wallEnd;
class wallDoor_front;
class wallDoor_side;
class enemy_skeleton;
class enemy_slime_blue;
class enemy_slime_green;
class enemy_bat;
class enemy_bat_red;
class enemy_bat_boss;
class enemy_shopkeeper;

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
	int										_time;
	float									_beatAlpha;


	// =================================
	//			   플레이어
	// =================================

	player* _player;
	bool	_isPlayerAlive = true;
	int		_killCount;

	int		_chainCount;

public:
	objectManager();
	~objectManager();

	HRESULT init();
	void release();
	void update();
	void render();

	bool _isGiveBeatTime = false;

	//오브젝트
	void vectorClear();					//벡터클리어용 함수
	void objectSort_IndexY();			//오브젝트정렬(Y)
	void objectSort_IndexX();			//오브젝트정렬(X)
	void allObjectUpdate();
	void deleteObject(parentObj* obj);

	//비트
	void initBeat(const char* fileName, string musicKey);
	void createBeat();
	void deleteBeat();


	//오브젝트생성
	parentObj* objectPush(parentObj obj);
	parentObj* createFloor(parentObj obj);
	parentObj* createWall(parentObj obj);
	parentObj* createItem(parentObj obj);
	parentObj* createEnemy(parentObj obj);
	parentObj* createTrap(parentObj obj);
	parentObj* createPlayer(parentObj obj);

	//카메라
	
	
	void setTileX(UINT x) { _tileX = x; }
	void setTileY(UINT y) { _tileY = y; }

	UINT getTileX() { return _tileX; }
	UINT getTileY() { return _tileY; }


	void setIsPlayerAlive() { _isPlayerAlive = false; }

	vector<parentObj*> getVObj() { return _vObj; }
	vector<parentObj*>::iterator getVIObj() { return _viObj; }

	int getChainCount() { return _chainCount; }
	void grooveChain();
	void breakChain();


	//플레이어
	player* getPlayer() { return _player; }

	//타일
	parentObj* getCheckObj(int x, int y) 
	{ 
		return _vvObjTile[y][x]; 
	}
	parentObj* getCheckFloor(int x, int y) { return _vvFloorTile[y][x]; }
	void setTileIdx(parentObj* obj, UINT idxX, UINT idxY)
	{
		_vvObjTile[obj->getIdxY()][obj->getIdxX()] = nullptr;
		obj->setIdxX(idxX);
		obj->setIdxY(idxY);
		_vvObjTile[idxY][idxX] = obj;
	}

	//시야
	void initLight();
	void initSight();

};

