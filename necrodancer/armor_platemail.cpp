#include "stdafx.h"
#include "armor_platemail.h"


armor_platemail::armor_platemail()
{
}


armor_platemail::~armor_platemail()
{
}

HRESULT armor_platemail::init(string imgName, int idxX, int idxY, ITEM_TYPE type)
{
	item::init(imgName, idxX, idxY, type);

	_appliedValue = 3;

	return S_OK;
}

void armor_platemail::release()
{
}

void armor_platemail::update()
{
	item::update();
}

void armor_platemail::render()
{
	item::render();
}

void armor_platemail::drawHint()
{
	IMAGEMANAGER->render("hint_armor_platemail", _posX - 45, _posY - 26);
}
