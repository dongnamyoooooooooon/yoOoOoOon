#include "stdafx.h"
#include "wallShop.h"


wallShop::wallShop()
{
}


wallShop::~wallShop()
{
}

HRESULT wallShop::init(string imgName, int idxX, int idxY, bool isTorch)
{
	wall::init(imgName, idxX, idxY, isTorch);
	_wallPower = 4;
	return S_OK;
}

void wallShop::release()
{
}

void wallShop::update()
{
	wall::update();
}

void wallShop::render()
{
	wall::render();
}
