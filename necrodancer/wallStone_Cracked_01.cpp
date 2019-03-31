#include "stdafx.h"
#include "wallStone_Cracked_01.h"


wallStone_Cracked_01::wallStone_Cracked_01()
{
}


wallStone_Cracked_01::~wallStone_Cracked_01()
{
}

HRESULT wallStone_Cracked_01::init(string imgName, int idxX, int idxY, bool isTorch)
{
	wall::init(imgName, idxX, idxY, isTorch);
	_wallPower = 2;
	return E_NOTIMPL;
}

void wallStone_Cracked_01::release()
{
}

void wallStone_Cracked_01::update()
{
	wall::update();
}

void wallStone_Cracked_01::render()
{
	wall::render();
}
