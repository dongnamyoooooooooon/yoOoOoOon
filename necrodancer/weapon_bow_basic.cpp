#include "stdafx.h"
#include "weapon_bow_basic.h"


weapon_bow_basic::weapon_bow_basic()
{
}


weapon_bow_basic::~weapon_bow_basic()
{
}

HRESULT weapon_bow_basic::init(string imgName, int idxX, int idxY, ITEM_TYPE type)
{
	item::init(imgName, idxX, idxY, type);

	_appliedValue = 1;

	return S_OK;
}

void weapon_bow_basic::release()
{
}

void weapon_bow_basic::update()
{
	item::update();
}

void weapon_bow_basic::render()
{
	item::render();
}

void weapon_bow_basic::drawHint()
{
	IMAGEMANAGER->render("hint_bow_basic", _posX - 46, _posY - 26);
}

bool weapon_bow_basic::useItem(int idxX, int idxY, int way)
{

	parentObj* tempObj[3];
	player* tempPlayer = OBJECTMANAGER->getPlayer();

	_posX = OBJECTMANAGER->getPlayer()->getPlayerPosX();
	_posY = OBJECTMANAGER->getPlayer()->getPlayerPosY();
	_posY -= 10;
	switch (way)
	{
	case 2:
		tempObj[0] = OBJECTMANAGER->getCheckObj(idxX, idxY);
		tempObj[1] = OBJECTMANAGER->getCheckObj(idxX, idxY + 1);
		tempObj[2] = OBJECTMANAGER->getCheckObj(idxX, idxY + 2);

		_posY += 52;
		break;

	case 4:
		tempObj[0] = OBJECTMANAGER->getCheckObj(idxX, idxY);
		tempObj[1] = OBJECTMANAGER->getCheckObj(idxX - 1, idxY);
		tempObj[2] = OBJECTMANAGER->getCheckObj(idxX - 2, idxY);

		_posX -= 52;
		break;

	case 6:
		tempObj[0] = OBJECTMANAGER->getCheckObj(idxX, idxY);
		tempObj[1] = OBJECTMANAGER->getCheckObj(idxX + 1, idxY);
		tempObj[2] = OBJECTMANAGER->getCheckObj(idxX + 2, idxY);

		_posX += 52;
		break;

	case 8:
		tempObj[0] = OBJECTMANAGER->getCheckObj(idxX, idxY);
		tempObj[1] = OBJECTMANAGER->getCheckObj(idxX, idxY - 1);
		tempObj[2] = OBJECTMANAGER->getCheckObj(idxX, idxY - 2);

		_posY -= 52;
		break;
	}

	bool haveObj = false;
	_isLong = false;
	tempPlayer->setIsLong(false);
	OBJECTMANAGER->setRangeVal(0);

	for (int i = 0; i < 3; i++)
	{
		OBJECTMANAGER->setRangeVal(i + 1);
		if (tempObj[i] != NULL && tempObj[i]->getObjType() == OBJECT_TYPE_ENEMY)
		{
			_attackWay = way;
			//이펙트방향 설정

			tempObj[i]->hitEnemy(_appliedValue);
			//이펙트 나감?
			haveObj = true;

			if (i != 0)
			{
				_isLong = true;
				tempPlayer->setIsLong(true);
			}
			break;
		}
	}

	return haveObj;
}
