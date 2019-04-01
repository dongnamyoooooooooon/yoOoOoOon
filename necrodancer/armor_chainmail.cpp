#include "stdafx.h"
#include "armor_chainmail.h"


armor_chainmail::armor_chainmail()
{
}


armor_chainmail::~armor_chainmail()
{
}

HRESULT armor_chainmail::init(string imgName, int idxX, int idxY, ITEM_TYPE type)
{
	item::init(imgName, idxX, idxY, type);

	_appliedValue = 2;
	return S_OK;
}

void armor_chainmail::release()
{
}

void armor_chainmail::update()
{
	item::update();
}

void armor_chainmail::render()
{
	item::render();
}

void armor_chainmail::drawHint()
{
	IMAGEMANAGER->render("hint_armorchainmail", _posX - 40, _posY - 26);
}
