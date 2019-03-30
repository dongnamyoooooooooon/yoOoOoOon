#pragma once
#include "parentObj.h"

class wall : public parentObj
{
protected:
	int _wallPower;

	int _torchFrameX;
	int _frameCount;


public:
	wall();
	~wall();

	HRESULT init(string imgName, int idxX, int idxY, bool isTorch);
	void release();
	void update();
	void render();

	bool wallBroken(int power);
	
	void rayCast();
};

