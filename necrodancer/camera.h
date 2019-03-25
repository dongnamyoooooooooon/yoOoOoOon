#pragma once
#include "singletonBase.h"

class camera : public singletonBase<camera>
{
private:

	int _posX;
	int _posY;


public:
	camera();
	~camera();

	HRESULT init();
	void release();
	void update();
	void cameraMove();

	int getPosX() { return _posX; }
	int getPosY() { return _posY; }



};

