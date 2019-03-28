#include "stdafx.h"
#include "parentObj.h"


parentObj::parentObj()
{
}


parentObj::~parentObj()
{
}

HRESULT parentObj::init(string imgName, int idx_X, int idx_Y, OBJECT_TYPE type, UINT key)
{
	_imgName = imgName;
	_img = IMAGEMANAGER->findImage(_imgName);

	_imgKey = key;

	_idxX = idx_X;
	_idxY = idx_Y;
	_objType = type;
	_frameX = 0;
	_frameY = 0;

	return S_OK;
}

HRESULT parentObj::init(string imgName, int idx_X, int idx_Y, OBJECT_TYPE type, UINT key, ITEM_TYPE itemtype)
{

	_imgName = imgName;
	_img = IMAGEMANAGER->findImage(_imgName);

	_imgKey = key;

	_idxX = idx_X;
	_idxY = idx_Y;
	_objType = type;
	_frameX = 0;
	_frameY = 0;

	switch (itemtype)
	{
	case ITEM_TYPE_SHOVEL:
	{

		_itemType = ITEM_TYPE_SHOVEL;
		_itemSubType = key;
		break;
	}
	case ITEM_TYPE_WEAPON:
	{

		_itemType = ITEM_TYPE_WEAPON;
		_itemSubType = key;
		break;
	}
	case ITEM_TYPE_TORCH:
	{

		_itemType = ITEM_TYPE_TORCH;
		_itemSubType = key;
		break;
	}
	case ITEM_TYPE_ARMOR:
	{

		_itemType = ITEM_TYPE_ARMOR;
		_itemSubType = key;
		break;
	}
	case ITEM_TYPE_HEADWEAR:
	{

		_itemType = ITEM_TYPE_HEADWEAR;
		_itemSubType = key;
		break;
	}
	case ITEM_TYPE_FOOTWEAR:
	{

		_itemType = ITEM_TYPE_FOOTWEAR;
		_itemSubType = key;
		break;
	}
	case ITEM_TYPE_CONSUMABLE:
	{

		_itemType = ITEM_TYPE_CONSUMABLE;
		_itemSubType = key;
		break;
	}
	case ITEM_TYPE_HEART:
	{

		_itemType = ITEM_TYPE_HEART;
		_itemSubType = key;
		break;
	}
	case ITEM_TYPE_COIN:
	{

		_itemType = ITEM_TYPE_COIN;
		_itemSubType = key;
		break;
	}
	case ITEM_TYPE_BOMB:
	{

		_itemType = ITEM_TYPE_BOMB;
		_itemSubType = key;
		break;
	}
	}
	return S_OK;
}

void parentObj::release()
{
}

void parentObj::update()
{
}

void parentObj::render()
{
	_img->frameRender(_rc.left, _rc.top, 0, 0);
}

void parentObj::render(float x, float y, int frameX)
{
	_img->frameRender(x, y, frameX, 0);
}

tagTilePack parentObj::makeSave()
{
	tagTilePack* pack = new tagTilePack;

	pack->frameX = _frameX;
	pack->frameY = _frameY;
	pack->appValue = _appValue;
	pack->idxX = _idxX;
	pack->idxY = _idxY;
	pack->imgName = _imgKey;
	pack->posX = _pos.x;
	pack->posY = _pos.y;
	pack->objType = _objType;
	pack->rc = _rc;
	pack->isTorch = _isTorch;

	if (pack->objType == OBJECT_TYPE_ITEM)
	{
		pack->itemType = _itemType;
		pack->itemSubType = _itemSubType;
	}



	return *pack;
}

void parentObj::makeLoad(tagTilePack * pack)
{
	_frameX = pack->frameX;
	_frameY = pack->frameY;
	_appValue = pack->appValue;
	_idxX = pack->idxX;
	_idxY = pack->idxY;
	_imgKey = (IMAGE_NAME_INFO)pack->imgName;
	_pos.x = pack->posX;
	_pos.y = pack->posY;
	_objType = pack->objType;
	_rc = pack->rc;
	_isTorch = pack->isTorch;
	_itemType = pack->itemType;

	if (_objType == OBJECT_TYPE_ITEM)
	{
		_itemSubType = pack->itemSubType;
		
		switch (_itemType)
		{
			case 0: _img = IMAGEMANAGER->findImage(SHOVEL_NAME[_itemSubType]); break;
			case 1: _img = IMAGEMANAGER->findImage(WEAPON_NAME[_itemSubType]); break;
			case 2: _img = IMAGEMANAGER->findImage(TORCH_NAME[_itemSubType]); break;
			case 3: _img = IMAGEMANAGER->findImage(ARMOR_NAME[_itemSubType]); break;
			case 4: _img = IMAGEMANAGER->findImage(HEADWEAR_NAME[_itemSubType]); break;
			case 5: _img = IMAGEMANAGER->findImage(FOOTWEAR_NAME[_itemSubType]); break;
			case 6: _img = IMAGEMANAGER->findImage(CONSUMABLE_NAME[_itemSubType]); break;
			case 7: _img = IMAGEMANAGER->findImage(HEART_NAME[_itemSubType]); break;
			case 8: _img = IMAGEMANAGER->findImage(COIN_NAME[_itemSubType]); break;
			case 9: _img = IMAGEMANAGER->findImage(BOMB_NAME[_itemSubType]); break;
		}
	}
	else
	{
		_imgName = IMAGE_NAME[_imgKey];
		_img = IMAGEMANAGER->findImage(IMAGE_NAME[_imgKey]);
	}


}
