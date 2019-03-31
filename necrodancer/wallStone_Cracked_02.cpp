#include "stdafx.h"
#include "wallStone_Cracked_02.h"


wallStone_Cracked_02::wallStone_Cracked_02()
{
}


wallStone_Cracked_02::~wallStone_Cracked_02()
{
}

HRESULT wallStone_Cracked_02::init(string imgName, int idxX, int idxY, bool isTorch)
{
	wall::init(imgName, idxX, idxY, isTorch);
	_wallPower = 2;
	return S_OK;
}

void wallStone_Cracked_02::release()
{
}

void wallStone_Cracked_02::update()
{
	wall::update();
}

void wallStone_Cracked_02::render()
{
	wall::render();
}
