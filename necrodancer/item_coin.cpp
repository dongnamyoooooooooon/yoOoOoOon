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

	_posX = idxX * TILE_SIZE;
	_posY = idxY * TILE_SIZE;

	if (_appliedValue == 1) _img = IMAGEMANAGER->findImage(COIN_NAME[ITEM_COIN_1]);
	else if (_appliedValue == 2) _img = IMAGEMANAGER->findImage(COIN_NAME[ITEM_COIN_2]);
	else if (_appliedValue == 3) _img = IMAGEMANAGER->findImage(COIN_NAME[ITEM_COIN_3]);
	else if (_appliedValue == 4) _img = IMAGEMANAGER->findImage(COIN_NAME[ITEM_COIN_4]);
	else if (_appliedValue == 5) _img = IMAGEMANAGER->findImage(COIN_NAME[ITEM_COIN_5]);
	else if (_appliedValue == 6) _img = IMAGEMANAGER->findImage(COIN_NAME[ITEM_COIN_6]);
	else if (_appliedValue == 7) _img = IMAGEMANAGER->findImage(COIN_NAME[ITEM_COIN_7]);
	else if (_appliedValue == 8) _img = IMAGEMANAGER->findImage(COIN_NAME[ITEM_COIN_8]);
	else if (_appliedValue == 9) _img = IMAGEMANAGER->findImage(COIN_NAME[ITEM_COIN_9]);
	else if (_appliedValue == 10) _img = IMAGEMANAGER->findImage(COIN_NAME[ITEM_COIN_10]);
	else if (_appliedValue > 11 && _appliedValue < 26) _img = IMAGEMANAGER->findImage(COIN_NAME[ITEM_COIN_25]);
	else if (_appliedValue > 25 && _appliedValue < 36) _img = IMAGEMANAGER->findImage(COIN_NAME[ITEM_COIN_35]);
	else if (_appliedValue > 35) _img = IMAGEMANAGER->findImage(COIN_NAME[ITEM_COIN_50]);

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
