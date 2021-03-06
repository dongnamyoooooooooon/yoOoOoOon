#include "stdafx.h"
#include "camera.h"


camera::camera()
{
}


camera::~camera()
{
}

HRESULT camera::init()
{
	_posX = 0;
	_posY = 0;
	_isQuake = false;
	_count = 0;

	return S_OK;
}

HRESULT camera::init(float x, float y, int maxX, int maxY)
{
	_posX = x;
	_posY = y;
	_maxX = maxX;
	_maxY = maxY;
	_isMove = false;

	return S_OK;
}

void camera::release()
{
}

void camera::update()
{
}

void camera::move(int x, int y)
{
	_posX = x - 480;
	if (_posX <= 0) _posX = 0;
	_posY = y - 260;
	if (_posY <= 0) _posY = 0;

	quakeCamera();
}

void camera::mapToolMove()
{
	if (KEYMANAGER->isStayKeyDown('D') && _posX < _maxX)
	{
		_isMove = true;
		_posX += CAMERA_SPEED;
		if (_posX + WINSIZEX > _maxX)
			_posX = _maxX - WINSIZEX;
	}
	if (KEYMANAGER->isStayKeyDown('A') && _posX > 0)
	{
		_isMove = true;
		_posX -= CAMERA_SPEED;
		if (_posX < 0)
			_posX = 0;
	}
	if (KEYMANAGER->isStayKeyDown('S') && _posY + WINSIZEY < _maxY)
	{
		_isMove = true;
		_posY += CAMERA_SPEED;
		if (_posY + WINSIZEY > _maxY)
			_posY = _maxY - WINSIZEY;
	}

	if (KEYMANAGER->isStayKeyDown('W') && _posY > 0)
	{
		_isMove = true;
		_posY -= CAMERA_SPEED;
		if (_posY < 0)
			_posY = 0;
	}

	if (KEYMANAGER->isOnceKeyUp('A')) _isMove = false;
	if (KEYMANAGER->isOnceKeyUp('S')) _isMove = false;
	if (KEYMANAGER->isOnceKeyUp('W')) _isMove = false;
	if (KEYMANAGER->isOnceKeyUp('D')) _isMove = false;
}

void camera::sampleToolMove()
{
	if (KEYMANAGER->isStayKeyDown('D') && _posX < _maxX)
	{
		_isMove = true;
		_posX += CAMERA_SPEED;
		if (_posX + WINSIZEX > _maxX)
			_posX = _maxX - WINSIZEX;
	}
	if (KEYMANAGER->isStayKeyDown('A') && _posX > 0)
	{
		_isMove = true;
		_posX -= CAMERA_SPEED;
		if (_posX < 0)
			_posX = 0;
	}
	if (KEYMANAGER->isStayKeyDown('S') && _posY + WINSIZEY < _maxY)
	{
		_isMove = true;
		_posY += CAMERA_SPEED;
		if (_posY + WINSIZEY > _maxY)
			_posY = _maxY - WINSIZEY;
	}

	if (KEYMANAGER->isStayKeyDown('W') && _posY > 0)
	{
		_isMove = true;
		_posY -= CAMERA_SPEED;
		if (_posY < 0)
			_posY = 0;
	}
}

void camera::quakeCamera()
{
	if (_isQuake)
	{
		_quakeX= RND->getInt(4) - 2;
		_quakeY= RND->getInt(4) - 2;

		_posX += _quakeX;
		_posY += _quakeY;
		_count++;

		if (_count > 10)
		{
			_isQuake = false;
			_count = 0;
		}
	}
}
