#include "stdafx.h"
#include "torch_bright.h"


torch_bright::torch_bright()
{
}


torch_bright::~torch_bright()
{
}

HRESULT torch_bright::init(string imgName, int idxX, int idxY, ITEM_TYPE type)
{
	item::init(imgName, idxX, idxY, type);

	_appliedValue = 2;

	return E_NOTIMPL;
}

void torch_bright::release()
{
}

void torch_bright::update()
{
	item::update();
}

void torch_bright::render()
{
	item::render();
}

void torch_bright::drawHint()
{
	IMAGEMANAGER->render("hint_torch_bright", _posX - 32, _posY - 26);
}
