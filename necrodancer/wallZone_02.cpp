#include "stdafx.h"
#include "wallZone_02.h"


wallZone_02::wallZone_02()
{
}


wallZone_02::~wallZone_02()
{
}

HRESULT wallZone_02::init(string imgName, int idxX, int idxY, bool isTorch)
{
	wall::init(imgName, idxX, idxY, isTorch);
	_wallPower = 1;
	_frameX = RND->getInt(8);
	return S_OK;
}

void wallZone_02::release()
{
}

void wallZone_02::update()
{
	wall::update();
}

void wallZone_02::render()
{
	wall::render();
}
