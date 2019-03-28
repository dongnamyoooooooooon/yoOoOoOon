#pragma once
#include "gameNode.h"
#include "mapToolScene.h"


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