#include "stdafx.h"
#include "wallStone_02.h"


wallStone_02::wallStone_02()
{
}


wallStone_02::~wallStone_02()
{
}

HRESULT wallStone_02::init(string imgName, int idxX, int idxY, bool isTorch)
{
	wall::init(imgName, idxX, idxY, isTorch);
	_wallPower = 2;
	return S_OK;
}

void wallStone_02::release()
{
}

void wallStone_02::update()
{
	wall::update();
}

void wallStone_02::render()
{
	wall::render();
}
