#include "stdafx.h"
#include "armor_heavyplate.h"


armor_heavyplate::armor_heavyplate()
{
}


armor_heavyplate::~armor_heavyplate()
{
}

HRESULT armor_heavyplate::init(string imgName, int idxX, int idxY, ITEM_TYPE type)
{
	item::init(imgName, idxX, idxY, type);

	_appliedValue = 4;

	return S_OK;
}

void armor_heavyplate::release()
{
}

void armor_heavyplate::update()
{
	item::update();
}

void armor_heavyplate::render()
{
	item::render();
}

void armor_heavyplate::drawHint()
{
	IMAGEMANAGER->render("hint_armor_heavyplate", _posX - 64, _posY - 26);
}
