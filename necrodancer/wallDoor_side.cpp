#include "stdafx.h"
#include "wallDoor_side.h"


wallDoor_side::wallDoor_side()
{
}


wallDoor_side::~wallDoor_side()
{
}

HRESULT wallDoor_side::init(string imgName, int idxX, int idxY, bool isTorch)
{

	wall::init(imgName, idxX, idxY, isTorch);
	_wallPower = 0;
	return S_OK;
}

void wallDoor_side::release()
{
}

void wallDoor_side::update()
{
	wall::update();
}

void wallDoor_side::render()
{
	wall::render();
}
