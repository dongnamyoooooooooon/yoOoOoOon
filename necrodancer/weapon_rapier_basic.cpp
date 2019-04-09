#include "stdafx.h"
#include "weapon_rapier_basic.h"


weapon_rapier_basic::weapon_rapier_basic()
{
}


weapon_rapier_basic::~weapon_rapier_basic()
{
}

HRESULT weapon_rapier_basic::init(string imgName, int idxX, int idxY, ITEM_TYPE type)
{
	item::init(imgName, idxX, idxY, type);

	_appliedValue = 1;
	return S_OK;
}

void weapon_rapier_basic::release()
{
}

void weapon_rapier_basic::update()
{
	item::update();
}

void weapon_rapier_basic::render()
{
	item::render();
}

void weapon_rapier_basic::drawHint()
{
	IMAGEMANAGER->render("hint_rapier_basic", _posX - 76, _posY - 26);
}

bool weapon_rapier_basic::useItem(int idxX, int idxY, int way)
{
	parentObj* tempObj[2];
	player* tempPlayer = OBJECTMANAGER->getPlayer();

	_posX = OBJECTMANAGER->getPlayer()->getPlayerPosX();
	_posY = OBJECTMANAGER->getPlayer()->getPlayerPosY();

	switch (way)
	{
	case 2:
		tempObj[1] = OBJECTMANAGER->getCheckObj(idxX, idxY + 1);
		tempObj[0] = OBJECTMANAGER->getCheckObj(idxX, idxY);

		_posY += 52;
		break;

	case 4:
		tempObj[1] = OBJECTMANAGER->getCheckObj(idxX - 1, idxY);
		tempObj[0] = OBJECTMANAGER->getCheckObj(idxX, idxY);

		_posX -= 104;
		break;

	case 6:
		tempObj[1] = OBJECTMANAGER->getCheckObj(idxX + 1, idxY);
		tempObj[0] = OBJECTMANAGER->getCheckObj(idxX, idxY);

		_posX += 52;
		break;

	case 8:
		tempObj[1] = OBJECTMANAGER->getCheckObj(idxX, idxY - 1);
		tempObj[0] = OBJECTMANAGER->getCheckObj(idxX, idxY);

		_posY -= 104;
		break;
	}
	
	bool haveObj = false;
	_isLong = false;
	tempPlayer->setIsLong(false);

	for (int i = 0; i < 2; i++)
	{
		if (tempObj[i] != NULL && tempObj[i]->getObjType() == OBJECT_TYPE_ENEMY)
		{
			_attackWay = way;

			haveObj = true;
			
			if (i == 1)
			{
				tempObj[i]->hitEnemy(_appliedValue * 2);
				_isLong = true;
				tempPlayer->setIsLong(true);

				switch (way)
				{
				case 2:
					OBJECTMANAGER->setTileIdx(tempPlayer, tempPlayer->getIdxX(), tempPlayer->getIdxY() + 1);
					tempPlayer->setjump(PLAYER_STATE_JUMP_DOWN);
					break;
				case 4:
					OBJECTMANAGER->setTileIdx(tempPlayer, tempPlayer->getIdxX() - 1, tempPlayer->getIdxY());
					tempPlayer->setjump(PLAYER_STATE_JUMP_LEFT);
					break;
				case 6:
					OBJECTMANAGER->setTileIdx(tempPlayer, tempPlayer->getIdxX() + 1, tempPlayer->getIdxY());
					tempPlayer->setjump(PLAYER_STATE_JUMP_RIGHT);
					break;
				case 8:
					OBJECTMANAGER->setTileIdx(tempPlayer, tempPlayer->getIdxX(), tempPlayer->getIdxY() - 1);
					tempPlayer->setjump(PLAYER_STATE_JUMP_UP);
					break;
				}
			}
			else
				tempObj[i]->hitEnemy(_appliedValue);

			break;
		}
	}

	return haveObj;
}
