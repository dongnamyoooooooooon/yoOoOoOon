#include "stdafx.h"
#include "wallShop_Cracked.h"


wallShop_Cracked::wallShop_Cracked()
{
}


wallShop_Cracked::~wallShop_Cracked()
{
}

HRESULT wallShop_Cracked::init(string imgName, int idxX, int idxY, bool isTorch)
{
	wall::init(imgName, idxX, idxY, isTorch);
	_wallPower = 4;
	return S_OK;
}

void wallShop_Cracked::release()
{
}

void wallShop_Cracked::update()
{
	wall::update();
}

void wallShop_Cracked::render()
{
	wall::render();
}
