#pragma once
#include "gameNode.h"
#include "mapToolScene.h"
#include "testMapScene.h"
#include "loadingScene.h"
#include "bossIntroScene.h"
#include "lobbyScene.h"
#include "bossScene.h"



class playGround : public gameNode
{
private:
	//============
	//   Ä¿¼­¿ë
	//============
	HCURSOR a;
	HCURSOR b;
	HCURSOR c;
	HCURSOR d;
	int _count;

	bossIntroScene* _bossIntro;
	testMapScene* _testMap;
	lobbyScene* _lobby;
	mapToolScene* _maptool;
	loadingScene* _loading;
	bossScene* _boss;


public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void initCursor();
	void frameCursor();
};