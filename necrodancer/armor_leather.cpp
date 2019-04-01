#include "stdafx.h"
#include "armor_leather.h"


armor_leather::armor_leather()
{
}


armor_leather::~armor_leather()
{
}

HRESULT armor_leather::init(string imgName, int idxX, int idxY, ITEM_TYPE type)
{
	item::init(imgName, idxX, idxY, type);

	_appliedValue = 1;
	
	return S_OK;
}

void armor_leather::release()
{
}

void armor_leather::update()
{
	item::update();
}

void armor_leather::render()
{
	item::render();
}

void armor_leather::drawHint()
{
	IMAGEMANAGER->render("hint_armor_leather", _posX - 45, _posY - 26);
}
