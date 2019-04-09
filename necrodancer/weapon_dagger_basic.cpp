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
	_isEffectUse = false;

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

		_drawX = tempObj->getIdxX() * TILE_SIZE;
		_drawY = tempObj->getIdxY() * TILE_SIZE;

		tempObj->hitEnemy(_appliedValue);

		return true;
	}
	return false;
}
