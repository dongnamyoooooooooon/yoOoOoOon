#include "stdafx.h"
#include "shovel_titanium.h"


shovel_titanium::shovel_titanium()
{
}


shovel_titanium::~shovel_titanium()
{
}

HRESULT shovel_titanium::init(string imgName, int idxX, int idxY, ITEM_TYPE type)
{
	item::init(imgName, idxX, idxY, type);

	_shovelPower = 2;

	return S_OK;
}

void shovel_titanium::release()
{
}

void shovel_titanium::update()
{
	item::update();
}

void shovel_titanium::render()
{
	item::render();
}

void shovel_titanium::drawHint()
{
	IMAGEMANAGER->findImage("hint_shovel_titanium")->render(_posX - 43, _posY - 26);
}

bool shovel_titanium::useItem(int idxX, int idxY, int way)
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
