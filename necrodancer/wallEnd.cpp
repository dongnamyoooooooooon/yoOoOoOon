#include "stdafx.h"
#include "wallEnd.h"


wallEnd::wallEnd()
{
}


wallEnd::~wallEnd()
{
}

HRESULT wallEnd::init(string imgName, int idxX, int idxY, bool isTorch)
{

	wall::init(imgName, idxX, idxY, isTorch);
	_wallPower = 999;
	_hasLight = false;
	_isSight = false;

	return S_OK;
}

void wallEnd::release()
{
}

void wallEnd::update()
{
	wall::update();
}

void wallEnd::render()
{
	wall::render();
}
