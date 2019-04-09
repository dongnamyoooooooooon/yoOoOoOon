#include "stdafx.h"
#include "shovel_glass_shard.h"


shovel_glass_shard::shovel_glass_shard()
{
}


shovel_glass_shard::~shovel_glass_shard()
{
}

HRESULT shovel_glass_shard::init(string imgName, int idxX, int idxY, ITEM_TYPE type)
{
	item::init(imgName, idxX, idxY, type);

	_shovelPower = 1;

	return S_OK;
}

void shovel_glass_shard::release()
{
}

void shovel_glass_shard::update()
{
	item::update();
}

void shovel_glass_shard::render()
{
	item::render();
}

void shovel_glass_shard::drawHint()
{
	IMAGEMANAGER->findImage("hint_shovel_glassShard")->render(_posX - 38, _posY - 26);
}

bool shovel_glass_shard::useItem(int idxX, int idxY, int way)
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
