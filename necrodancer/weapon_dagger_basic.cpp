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
}

void weapon_dagger_basic::drawHint()
{
	IMAGEMANAGER->render("hint_dagger_basic", _posX, _posY);
}

bool weapon_dagger_basic::useItem(int idxX, int idxY, int way)
{
	return false;
}
