#pragma once
#include "gameNode.h"
#include "playGround.h"

#define LOADINGMAX 300

class progressBar;

class loadingScene : public gameNode
{
private:
	progressBar* _loadingBar;

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