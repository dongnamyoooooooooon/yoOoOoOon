#include "stdafx.h"
#include "weapon_golden_lute.h"


weapon_golden_lute::weapon_golden_lute()
{
}


weapon_golden_lute::~weapon_golden_lute()
{
}

HRESULT weapon_golden_lute::init(string imgName, int idxX, int idxY, ITEM_TYPE type)
{
	item::init(imgName, idxX, idxY, type);

	_appliedValue = 1;

	return S_OK;
}

void weapon_golden_lute::release()
{
}

void weapon_golden_lute::update()
{
}

void weapon_golden_lute::render()
{
	item::render();
}

void weapon_golden_lute::drawHint()
{
	IMAGEMANAGER->render("hint_golden_lute", _posX - 55, _posY - 26);
}

bool weapon_golden_lute::useItem(int idxX, int idxY, int way)
{
	parentObj* tempObj[6];
	player* tempPlayer = OBJECTMANAGER->getPlayer();

	_posX = OBJECTMANAGER->getPlayer()->getPlayerPosX();
	_posY = OBJECTMANAGER->getPlayer()->getPlayerPosY();

	switch (way)
	{
	case 2:
		tempObj[0] = OBJECTMANAGER->getCheckObj(idxX, idxY - 2);
		tempObj[1] = OBJECTMANAGER->getCheckObj(idxX - 1, idxY - 1);
		tempObj[2] = OBJECTMANAGER->getCheckObj(idxX + 1, idxY - 1);
		tempObj[3] = OBJECTMANAGER->getCheckObj(idxX - 1, idxY);
		tempObj[4] = OBJECTMANAGER->getCheckObj(idxX + 1, idxY);
		tempObj[5] = OBJECTMANAGER->getCheckObj(idxX, idxY + 1);

		_posY += 52;
		break;

	case 4:
		tempObj[0] = OBJECTMANAGER->getCheckObj(idxX + 2, idxY);
		tempObj[1] = OBJECTMANAGER->getCheckObj(idxX + 1, idxY - 1);
		tempObj[2] = OBJECTMANAGER->getCheckObj(idxX + 1, idxY + 1);
		tempObj[3] = OBJECTMANAGER->getCheckObj(idxX, idxY - 1);
		tempObj[4] = OBJECTMANAGER->getCheckObj(idxX, idxY + 1);
		tempObj[5] = OBJECTMANAGER->getCheckObj(idxX - 1, idxY);

		_posX -= 104;
		break;

	case 6:
		tempObj[0] = OBJECTMANAGER->getCheckObj(idxX - 2, idxY);
		tempObj[1] = OBJECTMANAGER->getCheckObj(idxX - 1, idxY - 1);
		tempObj[2] = OBJECTMANAGER->getCheckObj(idxX - 1, idxY + 1);
		tempObj[3] = OBJECTMANAGER->getCheckObj(idxX, idxY - 1);
		tempObj[4] = OBJECTMANAGER->getCheckObj(idxX, idxY + 1);
		tempObj[5] = OBJECTMANAGER->getCheckObj(idxX + 1, idxY);

		_posX += 52;
		break;

	case 8:
		tempObj[0] = OBJECTMANAGER->getCheckObj(idxX, idxY + 2);
		tempObj[1] = OBJECTMANAGER->getCheckObj(idxX - 1, idxY + 1);
		tempObj[2] = OBJECTMANAGER->getCheckObj(idxX + 1, idxY + 1);
		tempObj[3] = OBJECTMANAGER->getCheckObj(idxX - 1, idxY);
		tempObj[4] = OBJECTMANAGER->getCheckObj(idxX + 1, idxY);
		tempObj[5] = OBJECTMANAGER->getCheckObj(idxX, idxY - 1);

		_posY -= 104;
		break;
	}

	bool haveObj = false;
	tempPlayer->setIsLong(false);

	for (int i = 0; i < 6; i++)
	{
		if (tempObj[i] != NULL && tempObj[i]->getObjType() == OBJECT_TYPE_ENEMY)
		{
			_attackWay = way;
			//이펙트방향 설정

			tempObj[i]->hitEnemy(_appliedValue);
			//이펙트 나감?
			haveObj = true;
			tempPlayer->setIsLong(true);
		}
	}

	return haveObj;
}
