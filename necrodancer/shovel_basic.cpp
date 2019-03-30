#include "stdafx.h"
#include "shovel_basic.h"


shovel_basic::shovel_basic()
{
}


shovel_basic::~shovel_basic()
{
}

HRESULT shovel_basic::init(string imgName, int idxX, int idxY, ITEM_TYPE type)
{
	item::init(imgName, idxX, idxY, type);

	shovelPower = 1;



	return S_OK;
}

void shovel_basic::release()
{
}

void shovel_basic::update()
{
	item::update();
}

void shovel_basic::render()
{
	item::render();
}

void shovel_basic::drawHint()
{
	IMAGEMANAGER->findImage("hint_shovel_basic")->render(_posX, _posY);
}

bool shovel_basic::useItem(int idxX, int idxY, int way)
{
	parentObj* obj = OBJECTMANAGER->getCheckObj(idxX, idxY);

	_posX = OBJECTMANAGER->getPlayer()->getPosX();
	_posY = OBJECTMANAGER->getPlayer()->getPosY();

	switch (way)
	{
		case 2:
		{
			_posY += TILE_SIZE;
			break;
		}

		case 4:
		{
			_posX -= TILE_SIZE;
			break;
		}

		case 6:
		{
			_posX += TILE_SIZE;
			break;
		}

		case 8:
		{
			_posY -= TILE_SIZE;
			break;
		}

		if (obj != NULL)
		{
			if (obj->getObjType() == OBJECT_TYPE_WALL)
			{
				if (obj->wallBroken(shovelPower))
				{
					OBJECTMANAGER->deleteObject(obj);
					return true;
				}
				else OBJECTMANAGER->breakChain();
			}
		}
	}
	return false;
}
