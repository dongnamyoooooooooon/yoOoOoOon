#include "stdafx.h"
#include "armor_glass.h"


armor_glass::armor_glass()
{
}


armor_glass::~armor_glass()
{
}

HRESULT armor_glass::init(string imgName, int idxX, int idxY, ITEM_TYPE type)
{
	item::init(imgName, idxX, idxY, type);

	_appliedValue = 999;

	return S_OK;
}

void armor_glass::release()
{
}

void armor_glass::update()
{
	item::update();
}

void armor_glass::render()
{
	item::render();
}

void armor_glass::drawHint()
{
	IMAGEMANAGER->render("hint_armor_glass", _posX - 85, _posY - 26);
}
