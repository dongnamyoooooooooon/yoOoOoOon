#include "stdafx.h"
#include "item_coin.h"


item_coin::item_coin()
{
}


item_coin::~item_coin()
{
}

HRESULT item_coin::init(string keyName, int idxX, int idxY, ITEM_TYPE type)
{
	item::init(keyName, idxX, idxY, type);

	_appliedValue = RND->getFromIntTo(1, 9) * (OBJECTMANAGER->getChainCount() + 1);

	_posX = OBJECTMANAGER->getCheckObj(idxX, idxY)->getPosX();
	_posY = OBJECTMANAGER->getCheckObj(idxX, idxY)->getPosY();

	if (_appliedValue == 1) _img = IMAGEMANAGER->findImage("coin_1");
	else if (_appliedValue == 2) _img = IMAGEMANAGER->findImage("coin_2");
	else if (_appliedValue == 3) _img = IMAGEMANAGER->findImage("coin_3");
	else if (_appliedValue == 4) _img = IMAGEMANAGER->findImage("coin_4");
	else if (_appliedValue == 5) _img = IMAGEMANAGER->findImage("coin_5");
	else if (_appliedValue == 6) _img = IMAGEMANAGER->findImage("coin_6");
	else if (_appliedValue == 7) _img = IMAGEMANAGER->findImage("coin_7");
	else if (_appliedValue == 8) _img = IMAGEMANAGER->findImage("coin_8");
	else if (_appliedValue == 9) _img = IMAGEMANAGER->findImage("coin_9");
	else if (_appliedValue == 10) _img = IMAGEMANAGER->findImage("coin_10");
	else if (_appliedValue > 25) _img = IMAGEMANAGER->findImage("coin_25");
	else if (_appliedValue > 35) _img = IMAGEMANAGER->findImage("coin_35");
	else if (_appliedValue > 50) _img = IMAGEMANAGER->findImage("coin_50");

	return S_OK;
}

void item_coin::release()
{
}

void item_coin::update()
{
}

void item_coin::render()
{
	_img->frameRender(_posX, _posY, 0, 0);
}
