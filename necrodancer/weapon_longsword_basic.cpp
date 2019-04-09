#include "stdafx.h"
#include "weapon_longsword_basic.h"


weapon_longsword_basic::weapon_longsword_basic()
{
}


weapon_longsword_basic::~weapon_longsword_basic()
{
}

HRESULT weapon_longsword_basic::init(string imgName, int idxX, int idxY, ITEM_TYPE type)
{
	item::init(imgName, idxX, idxY, type);

	_appliedValue = 1;

	return S_OK;
}

void weapon_longsword_basic::release()
{
}

void weapon_longsword_basic::update()
{
	item::update();
}

void weapon_longsword_basic::render()
{
	item::render();
}

void weapon_longsword_basic::drawHint()
{
	IMAGEMANAGER->render("hint_longsword_basic", _posX - 28, _posY - 26);
}

bool weapon_longsword_basic::useItem(int idxX, int idxY, int way)
{
	parentObj* tempObj[2];
	player* tempPlayer = OBJECTMANAGER->getPlayer();

	_posX = OBJECTMANAGER->getPlayer()->getPlayerPosX();
	_posY = OBJECTMANAGER->getPlayer()->getPlayerPosY();

	switch (way)
	{
	case 2:
		tempObj[0] = OBJECTMANAGER->getCheckObj(idxX, idxY + 1);
		tempObj[1] = OBJECTMANAGER->getCheckObj(idxX, idxY);

		_posY += 52;
		break;

	case 4:
		tempObj[0] = OBJECTMANAGER->getCheckObj(idxX - 1, idxY);
		tempObj[1] = OBJECTMANAGER->getCheckObj(idxX, idxY);

		_posX -= 104;
		break;

	case 6:
		tempObj[0] = OBJECTMANAGER->getCheckObj(idxX + 1, idxY);
		tempObj[1] = OBJECTMANAGER->getCheckObj(idxX, idxY);

		_posX += 52;
		break;

	case 8:
		tempObj[0] = OBJECTMANAGER->getCheckObj(idxX, idxY - 1);
		tempObj[1] = OBJECTMANAGER->getCheckObj(idxX, idxY);

		_posY -= 104;
		break;
	}

	_isLong = false;
	tempPlayer->setIsLong(false);
	bool haveObj = false;

	for (int i = 0; i < 2; i++)
	{
		if (tempObj[i] != NULL && tempObj[i]->getObjType() == OBJECT_TYPE_ENEMY)
		{
			_attackWay = way;
			//이펙트방향 설정

			tempObj[i]->hitEnemy(_appliedValue);
			//이펙트 나감?
			haveObj = true;
			if (i == 1)
			{
				_isLong = true;
				tempPlayer->setIsLong(true);
				break;
			}
		}
	}

	return haveObj;
}
