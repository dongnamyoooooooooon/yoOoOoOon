#include "stdafx.h"
#include "wallStone_01.h"


wallStone_01::wallStone_01()
{
}


wallStone_01::~wallStone_01()
{
}

HRESULT wallStone_01::init(string imgName, int idxX, int idxY, bool isTorch)
{
	wall::init(imgName, idxX, idxY, isTorch);
	_wallPower = 2;
	return S_OK;
}

void wallStone_01::release()
{
}

void wallStone_01::update()
{
	wall::update();
}

void wallStone_01::render()
{
	wall::render();
}
