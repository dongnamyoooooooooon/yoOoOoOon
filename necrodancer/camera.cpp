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
	return S_OK;
}

void camera::release()
{
}

void camera::update()
{
}

void camera::cameraMove()
{
}
