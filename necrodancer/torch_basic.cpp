#include "stdafx.h"
#include "torch_basic.h"


torch_basic::torch_basic()
{
}


torch_basic::~torch_basic()
{
}

HRESULT torch_basic::init(string imgName, int idxX, int idxY, ITEM_TYPE type)
{

	item::init(imgName, idxX, idxY, type);

	_appliedValue = 1;


	return S_OK;
}

void torch_basic::release()
{
}

void torch_basic::update()
{
	item::update();
}

void torch_basic::render()
{
	item::render();
}

void torch_basic::drawHint()
{
	IMAGEMANAGER->render("hint_torch_basic", _posX - 32, _posY - 26);
}
