#pragma once
#include "singletonBase.h"

#define CAMERA_SPEED 10.0f


class camera : public singletonBase<camera>
{
private:

	float _posX;
	float _posY;

	float _quakeX;
	float _quakeY;

	int _maxX;
	int _maxY;

	int _count;

	bool _isMove;
	bool _isQuake;

public:
	camera();
	~camera();

	HRESULT init();
	HRESULT init(float x, float y, int maxX, int maxY);
	void release();
	void update();

	void move(int x, int y);
	void mapToolMove();
	void sampleToolMove();
	void quakeCamera();

	float getPosX() { return _posX; }
	float getPosY() { return _posY; }
	void setPosX(float x) { _posX = x; }
	void setPosY(float y) { _posX = y; }

	float getMaxX() { return _maxX; }
	float getMaxY() { return _maxY; }
	void setMaxX(int x) { _maxX = x; }
	void setMaxY(int y) { _maxY = y; }

	bool getIsMove() { return _isMove; }

	void isQuake() { _isQuake = true; }


};

