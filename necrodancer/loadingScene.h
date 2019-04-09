#pragma once
#include "gameNode.h"
#include "Infomation.h"
#include "tileNode.h"
#include "testMapScene.h"
//#include "loadingScene.h"
#include "bossIntroScene.h"
#include "lobbyScene.h"
#include "bossScene.h"
#include "mapToolScene.h"

#define LOADINGMAX 300

class progressBar;

class loadingScene : public gameNode
{
private:
	progressBar* _loadingBar;

	bossIntroScene* _bossIntro;
	testMapScene* _testMap;
	lobbyScene* _lobby;
	mapToolScene* _maptool;
	//loadingScene* _loading;
	bossScene* _boss;

	int _count = 0;
	int _curFrameX = 17;

public:
	loadingScene();
	~loadingScene();


	int _curCount;

	HRESULT init();
	void release();
	void update();
	void render();
};

static DWORD CALLBACK ThreadFunction(LPVOID lpParameter);