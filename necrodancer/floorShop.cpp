#include "stdafx.h"
#include "floorShop.h"


floorShop::floorShop()
{
}


floorShop::~floorShop()
{
}

HRESULT floorShop::init(int idxX, int idxY)
{
	_idxX = idxX;
	_idxY = idxY;

	setTileX(OBJECTMANAGER->getTileX());
	setTileY(OBJECTMANAGER->getTileY());

	_posX = _idxX * TILE_SIZE;
	_posY = _idxY * TILE_SIZE;

	_frameX = 0;
	_frameY = 0;

	_hasLight = false;
	_isSight = false;
	_isSaw = true;

	return S_OK;
}

void floorShop::release()
{
}

void floorShop::update()
{
}

void floorShop::render()
{
	if (_isSaw)
	{
		if (_isSight)
		{
			if (_hasLight)
				IMAGEMANAGER->findImage(IMAGE_NAME[IMAGE_NAME_FLOOR_04])->frameRender(_idxX * TILE_SIZE, _idxY * TILE_SIZE, _frameX, _frameY);
			else
				IMAGEMANAGER->findImage(IMAGE_NAME[IMAGE_NAME_FLOOR_04])->frameRender(_idxX * TILE_SIZE, _idxY * TILE_SIZE, _frameX, _frameY, 0.5f);
		}
		else
		{
			IMAGEMANAGER->findImage(IMAGE_NAME[IMAGE_NAME_FLOOR_04])->frameRender(_idxX * TILE_SIZE, _idxY * TILE_SIZE, _frameX, _frameY, 0.5f);
		}
	}
}
