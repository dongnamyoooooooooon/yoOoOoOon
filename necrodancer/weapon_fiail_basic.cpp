#include "stdafx.h"
#include "weapon_fiail_basic.h"


weapon_fiail_basic::weapon_fiail_basic()
{
}


weapon_fiail_basic::~weapon_fiail_basic()
{
}

HRESULT weapon_fiail_basic::init(string imgName, int idxX, int idxY, ITEM_TYPE type)
{
	item::init(imgName, idxX, idxY, type);

	_appliedValue = 1;
	return S_OK;
}

void weapon_fiail_basic::release()
{
}

void weapon_fiail_basic::update()
{
	item::update();
}

void weapon_fiail_basic::render()
{
	item::render();
}

void weapon_fiail_basic::drawHint()
{
	IMAGEMANAGER->render("hint_fiail_basic", _posX - 35, _posY - 26);
}

bool weapon_fiail_basic::useItem(int idxX, int idxY, int way)
{
	parentObj* tempObj[5];
	parentObj* target;
	player* tempPlayer = OBJECTMANAGER->getPlayer();

	_posX = OBJECTMANAGER->getPlayer()->getPlayerPosX();
	_posY = OBJECTMANAGER->getPlayer()->getPlayerPosY();

	switch (way)
	{
	case 2:
		tempObj[0] = OBJECTMANAGER->getCheckObj(idxX - 1, idxY);
		tempObj[1] = OBJECTMANAGER->getCheckObj(idxX, idxY);
		tempObj[2] = OBJECTMANAGER->getCheckObj(idxX + 1, idxY);
		tempObj[3] = OBJECTMANAGER->getCheckObj(idxX - 1, idxY - 1);
		tempObj[4] = OBJECTMANAGER->getCheckObj(idxX + 1, idxY - 1);

		_posX -= 52;
		_posY += 52;
		break;

	case 4:
		tempObj[0] = OBJECTMANAGER->getCheckObj(idxX, idxY - 1);
		tempObj[1] = OBJECTMANAGER->getCheckObj(idxX, idxY);
		tempObj[2] = OBJECTMANAGER->getCheckObj(idxX, idxY + 1);
		tempObj[3] = OBJECTMANAGER->getCheckObj(idxX + 1, idxY - 1);
		tempObj[4] = OBJECTMANAGER->getCheckObj(idxX + 1, idxY + 1);

		_posX -= 52;
		_posY -= 52;
		break;

	case 6:
		tempObj[0] = OBJECTMANAGER->getCheckObj(idxX, idxY - 1);
		tempObj[1] = OBJECTMANAGER->getCheckObj(idxX, idxY);
		tempObj[2] = OBJECTMANAGER->getCheckObj(idxX, idxY + 1);
		tempObj[3] = OBJECTMANAGER->getCheckObj(idxX - 1, idxY - 1);
		tempObj[4] = OBJECTMANAGER->getCheckObj(idxX - 1, idxY + 1);

		_posX += 52;
		_posY -= 52;
		break;

	case 8:
		tempObj[0] = OBJECTMANAGER->getCheckObj(idxX - 1, idxY);
		tempObj[1] = OBJECTMANAGER->getCheckObj(idxX, idxY);
		tempObj[2] = OBJECTMANAGER->getCheckObj(idxX + 1, idxY);
		tempObj[3] = OBJECTMANAGER->getCheckObj(idxX - 1, idxY + 1);
		tempObj[4] = OBJECTMANAGER->getCheckObj(idxX + 1, idxY + 1);

		_posX -= 52;
		_posY -= 52;
		break;
	}

	bool haveObj = false;

	for (int i = 0; i < 3; i++)
	{
		OBJECTMANAGER->setRangeVal(i + 1);
		if (tempObj[i] != NULL && tempObj[i]->getObjType() == OBJECT_TYPE_ENEMY)
		{
			_attackWay = way;
			//이펙트방향 설정

			switch (way)
			{
			case 2:
				target = OBJECTMANAGER->getCheckObj(tempObj[i]->getIdxX(), tempObj[i]->getIdxY() + 1);
				if (target == NULL)
				{
					OBJECTMANAGER->setTileIdx(tempObj[i], tempObj[i]->getIdxX(), tempObj[i]->getIdxY() + 1);
					tempObj[i]->setXY((tempObj[i]->getIdxX() * 52) + 26, (tempObj[i]->getIdxY() * 52) + 26);
				}
				break;
			case 4:
				target = OBJECTMANAGER->getCheckObj(tempObj[i]->getIdxX() - 1, tempObj[i]->getIdxY());
				if (target == NULL)
				{
					OBJECTMANAGER->setTileIdx(tempObj[i], tempObj[i]->getIdxX() - 1, tempObj[i]->getIdxY());
					tempObj[i]->setXY((tempObj[i]->getIdxX() * 52) + 26, (tempObj[i]->getIdxY() * 52) + 26);
				}
				break;

			case 6:
				target = OBJECTMANAGER->getCheckObj(tempObj[i]->getIdxX() + 1, tempObj[i]->getIdxY());
				if (target == NULL)
				{
					OBJECTMANAGER->setTileIdx(tempObj[i], tempObj[i]->getIdxX() + 1, tempObj[i]->getIdxY());
					tempObj[i]->setXY((tempObj[i]->getIdxX() * 52) + 26, (tempObj[i]->getIdxY() * 52) + 26);
				}
				break;

			case 8:
				target = OBJECTMANAGER->getCheckObj(tempObj[i]->getIdxX(), tempObj[i]->getIdxY() - 1);
				if (target == NULL)
				{
					OBJECTMANAGER->setTileIdx(tempObj[i], tempObj[i]->getIdxX(), tempObj[i]->getIdxY() - 1);
					tempObj[i]->setXY((tempObj[i]->getIdxX() * 52) + 26, (tempObj[i]->getIdxY() * 52) + 26);
				}
				break;
			}
			tempObj[i]->hitEnemy(_appliedValue);

			//이펙트 나감?
			haveObj = true;
		}
	}

	return haveObj;
}
