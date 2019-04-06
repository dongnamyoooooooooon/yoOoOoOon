#pragma once
#include "gameNode.h"
#include "mapToolScene.h"
#include "testMapScene.h"
#include "loadingScene.h"
#include "bossIntroScene.h"



class playGround : public gameNode
{
private:
	//============
	//   Ŀ����
	//============
	HCURSOR a;
	HCURSOR b;
	HCURSOR c;
	HCURSOR d;
	int _count;

	bossIntroScene* _bossIntro;
	testMapScene* _testMap;


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