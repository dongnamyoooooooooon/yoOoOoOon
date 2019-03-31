#include "stdafx.h"
#include "wallCatacomb.h"


wallCatacomb::wallCatacomb()
{
}


wallCatacomb::~wallCatacomb()
{
}

HRESULT wallCatacomb::init(string imgName, int idxX, int idxY, bool isTorch)
{
	wall::init(imgName, idxX, idxY, isTorch);
	_wallPower = 3;
	return S_OK;
}

void wallCatacomb::release()
{
}

void wallCatacomb::update()
{
	wall::update();
}

void wallCatacomb::render()
{
	wall::render();
}
