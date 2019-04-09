#include "stdafx.h"
#include "torch_luminious.h"


torch_luminious::torch_luminious()
{
}


torch_luminious::~torch_luminious()
{
}

HRESULT torch_luminious::init(string imgName, int idxX, int idxY, ITEM_TYPE type)
{
	item::init(imgName, idxX, idxY, type);

	_appliedValue = 3;

	return S_OK;
}

void torch_luminious::release()
{
}

void torch_luminious::update()
{
	item::update();
}

void torch_luminious::render()
{
	item::render();
}

void torch_luminious::drawHint()
{
	IMAGEMANAGER->render("hint_torch_luminious", _posX - 32, _posY - 26);
}
