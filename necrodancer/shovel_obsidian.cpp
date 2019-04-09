#include "stdafx.h"
#include "shovel_obsidian.h"


shovel_obsidian::shovel_obsidian()
{
}


shovel_obsidian::~shovel_obsidian()
{
}

HRESULT shovel_obsidian::init(string imgName, int idxX, int idxY, ITEM_TYPE type)
{
	item::init(imgName, idxX, idxY, type);

	_shovelPower = 1;

	return S_OK;
}

void shovel_obsidian::release()
{
}

void shovel_obsidian::update()
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

void shovel_obsidian::render()
{
	item::render();
}

void shovel_obsidian::drawHint()
{
	IMAGEMANAGER->findImage("hint_shovel_obsidian")->render(_posX - 79, _posY - 26);
}

bool shovel_obsidian::useItem(int idxX, int idxY, int way)
{
	parentObj* obj = OBJECTMANAGER->getCheckObj(idxX, idxY);

	_drawX = OBJECTMANAGER->getPlayer()->getPlayerPosX();
	_drawY = OBJECTMANAGER->getPlayer()->getPlayerPosY();

	switch (way)
	{
	case 2:
	{
		_drawY += TILE_SIZE;
		break;
	}

	case 4:
	{
		_drawX -= TILE_SIZE;
		break;
	}

	case 6:
	{
		_drawX += TILE_SIZE;
		break;
	}

	case 8:
	{
		_drawY -= TILE_SIZE;
		break;
	}
	}

	if (obj != NULL)
	{
		if (obj->getObjType() == OBJECT_TYPE_WALL)
		{
			if (obj->wallBroken(_shovelPower))
			{
				OBJECTMANAGER->deleteObject(obj);
				return true;
			}
			else
			{
				OBJECTMANAGER->breakChain();
			}
		}

	}
	return false;
}
