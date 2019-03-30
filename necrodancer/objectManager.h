#pragma once
#include "singletonBase.h"
#include "gameNode.h"
#include "parentObj.h"
#include "player.h"
#include <algorithm>

class floorZone_01;
class weapon_dagger_basic;
class shovel_basic;
class wallZone_01;

class parentObj;
class objectManager : public singletonBase<objectManager>, public gameNode
{
private:
	// =================================
	//			   �Ǿ־�
	// =================================

	UINT	_tileX;				//��ũ��X
	UINT	_tiray;				//��ũ��Y


	vector<vector<parentObj*>> _vvObjTile;
	vector<vector<parentObj*>> _vvFloorTile;

	vector<parentObj*> _vObj;
	vector<parentObj*>::iterator _viObj;
	vector<parentObj*>::iterator _viObj2;

	// =================================
	//			   �� �� ��
	// =================================

	vector<tagNote>									_vBeat;			//��Ʈ ������
	vector<tagNote>::iterator						_viBeat;		//��Ʈ ������

	map<string, vector<tagNote>>					_mBeat;			//�ߺ�������
	map<string, vector<tagNote>>::iterator			_miBeat;		//�ߺ�������

	string											_musicKey;
	float											_volume;

	// =================================
	//				�� Ʈ
	// =================================

	string									_beatKey;
	D2D1_RECT_F								_failBeat;			//������
	D2D1_RECT_F								_successBeat;		//����
	const char*								_beatFile;
	int										_playTime;
	float									_beatAlpha;


	// =================================
	//			   �÷��̾�
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


	//������Ʈ
	void vectorClear();					//����Ŭ����� �Լ�
	void objectSort_IndexY();			//������Ʈ����(Y)
	void objectSort_IndexX();			//������Ʈ����(X)
	void allObjectUpdate();
	void deleteObject(parentObj* obj);

	//��Ʈ
	void initBeat(const char* fileName, string musicKey);
	void createBeat();
	void deleteBeat();


	//������Ʈ����
	parentObj* objectPush(parentObj obj);
	parentObj* createFloor(parentObj obj);
	parentObj* createWall(parentObj obj);
	parentObj* createItem(parentObj obj);
	parentObj* createEnemy(parentObj obj);
	parentObj* createTrap(parentObj obj);
	parentObj* createPlayer(parentObj obj);

	//ī�޶�
	
	
	void setTileX(UINT x) { _tileX = x; }
	void setTiray(UINT y) { _tiray = y; }

	UINT getTileX() { return _tileX; }
	UINT getTiray() { return _tiray; }


	void setIsPlayerAlive() { _isPlayerAlive = false; }

	vector<parentObj*> getVObj() { return _vObj; }
	vector<parentObj*>::iterator getVIObj() { return _viObj; }

	int getChainCount() { return _chainCount; }
	void grooveChain();
	void breakChain();


	//�÷��̾�
	player* getPlayer() { return _player; }

	//Ÿ��
	parentObj* getCheckObj(int x, int y) { return _vvObjTile[y][x]; }
	parentObj* getCheckFloor(int x, int y) { return _vvFloorTile[y][x]; }
	void setTileIdx(parentObj* obj, UINT idxX, UINT idxY)
	{
		_vvObjTile[obj->getIdxY()][obj->getIdxX()] = nullptr;
		obj->setIdxX(idxX);
		obj->setIdxY(idxY);
		_vvObjTile[idxY][idxX] = obj;
	}

	//�þ�
	void initLight();
	void initSight();

};

