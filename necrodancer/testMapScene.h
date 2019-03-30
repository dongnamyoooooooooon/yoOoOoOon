#pragma once
#include "gameNode.h"
#include "player.h"
#include "tileNode.h"

class testMapScene : public gameNode
{
private:

	player* _player;
	POINT _pos;
	POINT _curPos;

	vector<parentObj*>			 _vObj;
	vector<parentObj*>::iterator _viObj;

	vector<vector<tagTile*>>			_vvTile;
	UINT								_tileX;
	UINT								_tiray;
	UINT								_ii;
	UINT								_jj;
	UINT								_iiMax;
	UINT								_jjMax;

public:
	testMapScene();
	~testMapScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void load(const char* size, const char* data);
	void playerMgr();
};

