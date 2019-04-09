#include "stdafx.h"
#include "armor_obsidian.h"


armor_obsidian::armor_obsidian()
{
}


armor_obsidian::~armor_obsidian()
{
}

HRESULT armor_obsidian::init(string imgName, int idxX, int idxY, ITEM_TYPE type)
{
	item::init(imgName, idxX, idxY, type);

	_appliedValue = 1;

	return S_OK;
}

void armor_obsidian::release()
{
}

void armor_obsidian::update()
{
	item::update();

	if (OBJECTMANAGER->getChainCount() == 0)
	{
		_appliedValue = 1;
		_frameX = 0;
	}
	else if (OBJECTMANAGER->getChainCount() == 1 || OBJECTMANAGER->getChainCount() == 2)
	{
		_appliedValue = 2;
		_frameX = 1;
	}
	else if (OBJECTMANAGER->getChainCount() == 3)
	{
		_appliedValue = 3;
		_frameX = 2;
	}
}

void armor_obsidian::render()
{
	item::render();
}

void armor_obsidian::drawHint()
{
	IMAGEMANAGER->render("hint_armor_obsidian", _posX - 67, _posY - 26);
}
