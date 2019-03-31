#include "stdafx.h"
#include "weapon_dagger_basic.h"


weapon_dagger_basic::weapon_dagger_basic()
{
}


weapon_dagger_basic::~weapon_dagger_basic()
{
}

HRESULT weapon_dagger_basic::init(string imgName, int idxX, int idxY, ITEM_TYPE type)
{
	item::init(imgName, idxX, idxY, type);

	_attackWay = 5;
	_effectX = -1;
	_effectY = 0;
	_effectCount = 0;

	_appliedValue = 1;

	_isThrow = true;

	return S_OK;
}

void weapon_dagger_basic::release()
{
}

void weapon_dagger_basic::update()
{
	item::update();
}

void weapon_dagger_basic::render()
{
	item::render();

	if (_isEffectUse)
	{
		switch (_attackWay)
		{
		case 8:
			IMAGEMANAGER->findImage("attack_dagger_basic")->frameRenderAngle(_posX, _posY, _effectX, 0 , 90);
			break;
		case 2:
			IMAGEMANAGER->findImage("attack_dagger_basic")->frameRenderAngle(_posX, _posY, _effectX, 0 ,-90);
			break;
		case 4:
			IMAGEMANAGER->findImage("attack_dagger_basic")->frameRenderAngle(_posX, _posY, _effectX, 0 , 0);
			break;
		case 6:
			IMAGEMANAGER->findImage("attack_dagger_basic")->frameRenderAngle(_posX, _posY, _effectX, 0 , 180);
			break;
		}
	}
}

void weapon_dagger_basic::drawHint()
{
	IMAGEMANAGER->render("hint_dagger_basic", _posX - 70, _posY - 26);
}

bool weapon_dagger_basic::useItem(int idxX, int idxY, int way)
{
	parentObj* tempObj = OBJECTMANAGER->getCheckObj(idxX, idxY);

	if (tempObj == NULL) return false;
	else if (tempObj->getObjType() == OBJECT_TYPE_ENEMY)
	{
		_attackWay = way;
		_effectX = 0;
		_effectY = 0;

		_posX = tempObj->getIdxX() * TILE_SIZE;
		_posY = tempObj->getIdxY() * TILE_SIZE;

		tempObj->hitEnemy(_appliedValue);

		_isEffectUse = true;
		return true;
	}
	_isEffectUse = false;
	return false;
}
