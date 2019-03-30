#include "stdafx.h"
#include "wallZone_01.h"


wallZone_01::wallZone_01()
{
}


wallZone_01::~wallZone_01()
{
}

HRESULT wallZone_01::init(string imgName, int idxX, int idxY, bool isTorch)
{
	wall::init(imgName, idxX, idxY, isTorch);
	_wallPower = 1;
	_frameX = RND->getInt(16);
	return S_OK;
}

void wallZone_01::release()
{
}

void wallZone_01::update()
{
	wall::update();
}

void wallZone_01::render()
{
	wall::render();
}
