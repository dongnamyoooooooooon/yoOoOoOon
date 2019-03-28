#pragma once
#include "gameNode.h"
#include "player.h"
#include "tileNode.h"

class testMapScene : public gameNode
{
private:

	player* _player;

	vector<vector<tagTile*>>			_vvTile;
	UINT								_tileX;
	UINT								_tileY;
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
};

