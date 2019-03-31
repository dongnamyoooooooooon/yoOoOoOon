#include "stdafx.h"
#include "wallDoor_front.h"


wallDoor_front::wallDoor_front()
{
}


wallDoor_front::~wallDoor_front()
{
}

HRESULT wallDoor_front::init(string imgName, int idxX, int idxY, bool isTorch)
{
	wall::init(imgName, idxX, idxY, isTorch);
	_wallPower = 0;
	return S_OK;
}

void wallDoor_front::release()
{
}

void wallDoor_front::update()
{
	wall::update();
}

void wallDoor_front::render()
{
	wall::render();
}
