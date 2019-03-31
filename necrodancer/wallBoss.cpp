#include "stdafx.h"
#include "wallBoss.h"


wallBoss::wallBoss()
{
}


wallBoss::~wallBoss()
{
}

HRESULT wallBoss::init(string imgName, int idxX, int idxY, bool isTorch)
{
	wall::init(imgName, idxX, idxY, isTorch);
	_wallPower = 999;
	return S_OK;
}

void wallBoss::release()
{
}

void wallBoss::update()
{
	wall::update();
}

void wallBoss::render()
{
	wall::render();
}
