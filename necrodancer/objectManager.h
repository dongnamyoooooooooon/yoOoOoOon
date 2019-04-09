#pragma once
#include "singletonBase.h"
#include "gameNode.h"
#include "parentObj.h"
#include "floorWater.h"
#include "floorBoss.h"
#include "wallBoss.h"
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
class weapon_rapier_basic;
class weapon_spear_basic;
class weapon_longsword_basic;
class weapon_bow_basic;
class weapon_fiail_basic;
class weapon_blunderbuss;
class weapon_golden_lute;
class shovel_basic;
class shovel_titanium;
class shovel_glass;
class shovel_obsidian;
class shovel_blood;
class shovel_crystal;
class shovel_glass_shard;
class armor_Gi;
class armor_leather;
class armor_chainmail;
class armor_platemail;
class armor_heavyplate;
class armor_obsidian;
class armor_glass;
class torch_basic;
class torch_bright;
class item_coin;
class item_food_1;
class item_food_2;
class item_food_3;
class item_food_4;
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
class enemy_skeleton_yellow;
class enemy_skeleton_black;
class enemy_skeleton_mage;
class enemy_skeleton_mage_yellow;
class enemy_skeleton_mage_black;
class enemy_slime_blue;
class enemy_slime_green;
class enemy_dragon_green;
class enemy_banshee;
class enemy_zombie;
class enemy_clone;
class enemy_armadillo;
class enemy_minotaur;
class enemy_bat;
class enemy_bat_red;
class enemy_bat_boss;
class enemy_coralriff_drums;
class enemy_coralriff_horns;
class enemy_coralriff_keytar;
class enemy_coralriff_strings;
class enemy_coralriff_head;
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

	int		_isMagic;

	bool	_bossHit;
	bool	_bossAlive = true;
	bool	_isEnter = false;
	
	bool	_isEffectUse = false;
	image*  _effectHImg;
	image*  _effectVImg;
	int		_effectCount;
	int		_effectX;
	int		_effectY;

	int		_subX;
	int		_subY;

	int		_rangeVal;
	float	_posZ = 0;
	float   _ruteAlpha = 1.0f;


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
	void deleteFloorTile(parentObj* obj);

	void mageMagic();

	//비트
	void initBeat(const char* fileName, string musicKey);
	void createBeat();
	void deleteBeat();
	void replaySong();

	void weaponEff();


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

	UINT getTileX() { return _tileX; }
	UINT getTileY() { return _tileY; }

	void magicOn() { _isMagic = 1; }

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

	void setTileFloor(UINT idxX, UINT idxY)
	{
		parentObj* deleteFloor;
		deleteFloor = _vvFloorTile[idxY][idxX];
		deleteFloorTile(deleteFloor);

		parentObj* tempObj;
		tempObj = createWater(idxX, idxY);
		_vvFloorTile[idxY][idxX] = tempObj;
		_vObj.push_back(tempObj);
	}

	void setBossFloor(UINT idxX, UINT idxY)
	{

		parentObj* deleteFloor;
		deleteFloor = _vvFloorTile[idxY][idxX];
		deleteFloorTile(deleteFloor);

		parentObj* tempObj;
		tempObj = createFloor(idxX, idxY);
		_vvFloorTile[idxY][idxX] = tempObj;
		_vObj.push_back(tempObj);

	}

	parentObj* createWater(UINT idxX, UINT idxY)
	{
		floorWater* tempObj = new floorWater;
		tempObj->init(idxX, idxY);
		tempObj->setObjType(OBJECT_TYPE_FLOOR);

		return tempObj;
	}

	parentObj* createFloor(UINT idxX, UINT idxY)
	{
		floorBoss* tempObj = new floorBoss;
		tempObj->init(idxX, idxY);
		tempObj->setObjType(OBJECT_TYPE_FLOOR);

		return tempObj;
	}

	parentObj* createWall(UINT idxX, UINT idxY)
	{
		wallBoss* tempObj = new wallBoss;
		tempObj->init("wall_08",idxX, idxY,false);
		tempObj->setObjType(OBJECT_TYPE_WALL);
		tempObj->setIsSight(true);
		tempObj->setIsSaw();
		tempObj->setHasLight(true);

		return tempObj;
	}

	void setBossWall(UINT idxX, UINT idxY)
	{
		parentObj* tempObj;
		tempObj = createWall(idxX, idxY);
		_vvObjTile[idxY][idxX] = tempObj;
		_vObj.push_back(tempObj);

	}

	void pushObj(parentObj* obj)
	{
		_vObj.push_back(obj);
		setTileIdx(obj, obj->getIdxX(), obj->getIdxY());
	}

	//시야
	void initLight();
	void initSight();

	//보스

	bool getBossAlive() { return _bossAlive; }
	void setBossAlive(bool check) { _bossAlive = check; }

	bool getIsEnter() { return _isEnter; }
	void setIsEnter(bool check) { _isEnter = check; }

	bool getIsEffectUse() { return _isEffectUse;}
	void setIsEffectUse(bool check) { _isEffectUse = check; }

	image* getEffectImg() { return _effectHImg; }

	int getRangeVal() { return _rangeVal; }
	void setRangeVal(int val) { _rangeVal = val; }

	bool getBossHit() { return _bossHit; }
	void setBossHit(bool check) { _bossHit = check; }
};

