#include "stdafx.h"
#include "parentObj.h"


parentObj::parentObj()
{
}


parentObj::~parentObj()
{
}

HRESULT parentObj::init(string imgName, int idx_X, int idx_Y, OBJECT_TYPE type)
{
	_imgName = imgName;
	_img = IMAGEMANAGER->findImage(_imgName);

	_idxX = idx_X;
	_idxY = idx_Y;
	_objType = type;
	_frameX = 0;
	_frameY = 0;

	return S_OK;
}

void parentObj::release()
{
}

void parentObj::update()
{
}

void parentObj::render()
{
	_img->frameRender(_rc.left, _rc.top, 0, 0);
}
