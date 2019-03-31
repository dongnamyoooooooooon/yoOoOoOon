#include "stdafx.h"
#include "item.h"


item::item()
{
}


item::~item()
{
}

HRESULT item::init(string keyName, int idxX, int idxY, ITEM_TYPE type)
{
	_imgName = keyName;
	
	_img = IMAGEMANAGER->findImage(keyName);

	_idxX = idxX;
	_idxY = idxY;

	_posX = _idxX * TILE_SIZE + 26;
	_posY = _idxY * TILE_SIZE;
	
	_objType = OBJECT_TYPE_ITEM;
	_itemType = type;
	_itemKind = type;
	
	_floatCount = 0;
	_gravity = 2;
	_jumpPower = 0;

	_isMoveInven = false;
	_isCurInven = false;

	_frameX = 0;
	_frameY = 0;
	_hasLight = false;
	_isSight = false;



	return S_OK;
}

void item::release()
{
}

void item::update()
{
	this->drawFloorItem();
	this->moveItem();
}

void item::render()
{
	if (_isSight)
	{
		if (!_isCurInven)
		{
			if (_isSaw)
			{
				if (_hasLight)	_img->frameRender(_posX - 26, _posY - _jumpPower, _frameX, 0);
				else			_img->frameRender(_posX - 26, _posY - _jumpPower, _frameX, 1);
			}
			else	_img->frameRender(_posX - 26, _posY - _jumpPower, _frameX, 1);
		}
	}
	else if (_isMoveInven)	_img->frameRender(_posX, _posY - _jumpPower, _frameX, _frameY);

}

void item::itemInven(int moveX, int moveY)
{
	_isMoveInven = true;

	_moveX = moveX;
	_moveY = moveY;
}

void item::drawFloorItem()
{
	if (!_isCurInven)
	{
		_count++;
		if (_count % 16 == 0)
		{
			_jumpPower += _gravity;

			if (_jumpPower > 6 || _jumpPower < 0) _gravity = (-1) * _gravity;
		}
	}
}

void item::moveItem()
{
	if (_isMoveInven)
	{
		_posX -= (_posX - _moveX - CAMERA->getPosX()) / 8.0f;
		_posY -= (_posY - _moveY - CAMERA->getPosY()) / 8.0f;

		if (_posX - _moveX - CAMERA->getPosX() <= 10)
			_posX = _moveX + CAMERA->getPosX();
		if (_posY - _moveY - CAMERA->getPosY() <= 10)
			_posY = _moveY + CAMERA->getPosY();

		if (_posX <= CAMERA->getPosX() + _moveX && _posY <= CAMERA->getPosY() + _moveY)
		{
			_isMoveInven = false;
			_isCurInven = true;
		}
	}
}
