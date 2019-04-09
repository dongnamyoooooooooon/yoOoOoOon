#include "stdafx.h"
#include "shovel_crystal.h"


shovel_crystal::shovel_crystal()
{
}


shovel_crystal::~shovel_crystal()
{
}

HRESULT shovel_crystal::init(string imgName, int idxX, int idxY, ITEM_TYPE type)
{
	item::init(imgName, idxX, idxY, type);

	_shovelPower = 3;

	return E_NOTIMPL;
}

void shovel_crystal::release()
{
}

void shovel_crystal::update()
{
	item::update();
}

void shovel_crystal::render()
{
	item::render();
}

void shovel_crystal::drawHint()
{
	IMAGEMANAGER->findImage("hint_shovel_crystal")->render(_posX - 43, _posY - 26);
}

bool shovel_crystal::useItem(int idxX, int idxY, int way)
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
