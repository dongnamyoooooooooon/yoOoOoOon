#include "stdafx.h"
#include "shovel_glass.h"


shovel_glass::shovel_glass()
{
}


shovel_glass::~shovel_glass()
{
}

HRESULT shovel_glass::init(string imgName, int idxX, int idxY, ITEM_TYPE type)
{
	item::init(imgName, idxX, idxY, type);

	_shovelPower = 3;

	return S_OK;
}

void shovel_glass::release()
{
}

void shovel_glass::update()
{
	item::update();
}

void shovel_glass::render()
{
	item::render();
}

void shovel_glass::drawHint()
{
	IMAGEMANAGER->findImage("hint_shovel_glass")->render(_posX - 87, _posY - 26);
}

bool shovel_glass::useItem(int idxX, int idxY, int way)
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
