#include "stdafx.h"
#include "weapon_blunderbuss.h"


weapon_blunderbuss::weapon_blunderbuss()
{
}


weapon_blunderbuss::~weapon_blunderbuss()
{
}

HRESULT weapon_blunderbuss::init(string imgName, int idxX, int idxY, ITEM_TYPE type)
{
	item::init(imgName, idxX, idxY, type);

	_appliedValue = 2;
	_knockBack = 0;
	_isReload = true;
	return S_OK;
}

void weapon_blunderbuss::release()
{
}

void weapon_blunderbuss::update()
{
	item::update();
}

void weapon_blunderbuss::render()
{

	if (_isSight)
	{
		if (!_isCurInven)
		{
			if (_isSaw)
			{
				if (_hasLight)	_img->frameRender(_posX - 26, _posY - _jumpPower - 20, _frameX, 0);
				else			_img->frameRender(_posX - 26, _posY - _jumpPower - 20, _frameX, 1);
			}
			else	_img->frameRender(_posX - 26, _posY - _jumpPower, _frameX, 1);
		}
	}
	else if (_isMoveInven)
		_img->frameRender(_posX - 26, _posY - _jumpPower - 20, _frameX, _frameY);
}

void weapon_blunderbuss::drawHint()
{
	IMAGEMANAGER->render("hint_blunderbuss", _posX - 164, _posY - 26);
}

bool weapon_blunderbuss::useItem(int idxX, int idxY, int way)
{
	parentObj* tempObj[9];
	player* tempPlayer = OBJECTMANAGER->getPlayer();

	if (_isReload && way != 5)
	{
		_posX = tempPlayer->getPlayerPosX();
		_posY = tempPlayer->getPlayerPosY();
		_posY -= 10;

		switch (way)
		{
		case 2:
			tempObj[0] = OBJECTMANAGER->getCheckObj(idxX, idxY);
			tempObj[1] = OBJECTMANAGER->getCheckObj(idxX - 1, idxY + 1);
			tempObj[2] = OBJECTMANAGER->getCheckObj(idxX, idxY + 1);
			tempObj[3] = OBJECTMANAGER->getCheckObj(idxX + 1, idxY + 1);
			tempObj[4] = OBJECTMANAGER->getCheckObj(idxX, idxY + 2);
			tempObj[5] = OBJECTMANAGER->getCheckObj(idxX - 2, idxY + 2);
			tempObj[6] = OBJECTMANAGER->getCheckObj(idxX - 1, idxY + 2);
			tempObj[7] = OBJECTMANAGER->getCheckObj(idxX + 1, idxY + 2);
			tempObj[8] = OBJECTMANAGER->getCheckObj(idxX + 2, idxY + 2);
			_posX -= 104;
			_posY += 52;
			break;
		case 4:
			tempObj[0] = OBJECTMANAGER->getCheckObj(idxX, idxY);
			tempObj[1] = OBJECTMANAGER->getCheckObj(idxX - 1, idxY - 1);
			tempObj[2] = OBJECTMANAGER->getCheckObj(idxX - 1, idxY + 1);
			tempObj[3] = OBJECTMANAGER->getCheckObj(idxX - 1, idxY);
			tempObj[4] = OBJECTMANAGER->getCheckObj(idxX - 2, idxY);
			tempObj[5] = OBJECTMANAGER->getCheckObj(idxX - 2, idxY + 2);
			tempObj[6] = OBJECTMANAGER->getCheckObj(idxX - 2, idxY + 1);
			tempObj[7] = OBJECTMANAGER->getCheckObj(idxX - 2, idxY - 2);
			tempObj[8] = OBJECTMANAGER->getCheckObj(idxX - 2, idxY - 1);
			_posX -= 156;
			_posY -= 104;
			break;
		case 6:
			tempObj[0] = OBJECTMANAGER->getCheckObj(idxX, idxY);
			tempObj[1] = OBJECTMANAGER->getCheckObj(idxX + 1, idxY - 1);
			tempObj[2] = OBJECTMANAGER->getCheckObj(idxX + 1, idxY);
			tempObj[3] = OBJECTMANAGER->getCheckObj(idxX + 1, idxY + 1);
			tempObj[4] = OBJECTMANAGER->getCheckObj(idxX + 2, idxY - 2);
			tempObj[5] = OBJECTMANAGER->getCheckObj(idxX + 2, idxY - 1);
			tempObj[6] = OBJECTMANAGER->getCheckObj(idxX + 2, idxY);
			tempObj[7] = OBJECTMANAGER->getCheckObj(idxX + 2, idxY + 1);
			tempObj[8] = OBJECTMANAGER->getCheckObj(idxX + 2, idxY + 2);
			_posX += 52;
			_posY -= 104;
			break;
		case 8:
			tempObj[0] = OBJECTMANAGER->getCheckObj(idxX, idxY);
			tempObj[1] = OBJECTMANAGER->getCheckObj(idxX - 1, idxY - 1);
			tempObj[2] = OBJECTMANAGER->getCheckObj(idxX, idxY - 1);
			tempObj[3] = OBJECTMANAGER->getCheckObj(idxX + 1, idxY - 1);
			tempObj[4] = OBJECTMANAGER->getCheckObj(idxX - 2, idxY - 2);
			tempObj[5] = OBJECTMANAGER->getCheckObj(idxX - 1, idxY - 2);
			tempObj[6] = OBJECTMANAGER->getCheckObj(idxX , idxY - 2);
			tempObj[7] = OBJECTMANAGER->getCheckObj(idxX + 1, idxY - 2);
			tempObj[8] = OBJECTMANAGER->getCheckObj(idxX + 2, idxY - 2);
			_posX -= 104;
			_posY -= 208;
			break;
		}

		bool haveObj = false;

		for (int i = 0; i < 9; i++)
		{
			if (tempObj[i] != NULL && tempObj[i]->getObjType() == OBJECT_TYPE_ENEMY)
			{
				haveObj = true;
				tempObj[i]->hitEnemy(_appliedValue);
			}
		}
		if (haveObj)
		{
			_attackWay = way;
			SOUNDMANAGER->play("sound_blunderbuss_fire");
			_knockBack = 0;

			parentObj* target;

			switch (way)
			{
			case 2:
				target = OBJECTMANAGER->getCheckObj(tempPlayer->getIdxX(), tempPlayer->getIdxY() - 1);
				{
					if (target == NULL || target->getObjType() == OBJECT_TYPE_ITEM)
					{
						OBJECTMANAGER->setTileIdx(tempPlayer, tempPlayer->getIdxX(), tempPlayer->getIdxY() - 1);
						tempPlayer->setjump(PLAYER_STATE_JUMP_UP);
					}
				}
				break;

			case 4:
				target = OBJECTMANAGER->getCheckObj(tempPlayer->getIdxX() + 1, tempPlayer->getIdxY());
				{
					if (target == NULL || target->getObjType() == OBJECT_TYPE_ITEM)
					{
						OBJECTMANAGER->setTileIdx(tempPlayer, tempPlayer->getIdxX() + 1, tempPlayer->getIdxY());
						tempPlayer->setjump(PLAYER_STATE_JUMP_RIGHT);
					}
				}
				break;

			case 6:
				target = OBJECTMANAGER->getCheckObj(tempPlayer->getIdxX() - 1, tempPlayer->getIdxY());
				{
					if (target == NULL || target->getObjType() == OBJECT_TYPE_ITEM)
					{
						OBJECTMANAGER->setTileIdx(tempPlayer, tempPlayer->getIdxX() - 1, tempPlayer->getIdxY());
						tempPlayer->setjump(PLAYER_STATE_JUMP_LEFT);
					}
				}
				break;

			case 8:
				target = OBJECTMANAGER->getCheckObj(tempPlayer->getIdxX(), tempPlayer->getIdxY() + 1);
				{
					if (target == NULL || target->getObjType() == OBJECT_TYPE_ITEM)
					{
						OBJECTMANAGER->setTileIdx(tempPlayer, tempPlayer->getIdxX(), tempPlayer->getIdxY() + 1);
						tempPlayer->setjump(PLAYER_STATE_JUMP_DOWN);
					}
				}
				break;
			}
			_isReload = false;
			_frameX = 1;
		}
		return haveObj;
	}
	else if (way == 5)
	{
		_isReload = true;
		_frameX = 0;
		SOUNDMANAGER->play("sound_blunderbuss_reload");
		return false;
	}
	else
		return false;
}
