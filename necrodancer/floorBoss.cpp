#include "stdafx.h"
#include "floorBoss.h"


floorBoss::floorBoss()
{
}


floorBoss::~floorBoss()
{
}

HRESULT floorBoss::init(int idxX, int idxY)
{
	_count = 0;
	checkFever(idxX, idxY);
	_idxX = idxX;
	_idxY = idxY;

	setTileX(OBJECTMANAGER->getTileX());
	setTileY(OBJECTMANAGER->getTileY());

	if (_isCrossStripes)
	{
		_frameX = 0;
		_frameY = 0;
	}
	else
	{
		_frameX = 2;
		_frameY = 0;
	}

	_posX = _idxX * TILE_SIZE;
	_posY = _idxY * TILE_SIZE;

	_hasLight = false;
	_isSight = false;
	_isSaw = true;



	return S_OK;
}

void floorBoss::release()
{
}

void floorBoss::update()
{
	if (_isBeat)
	{
		if (_isCrossStripes)
		{
			if (_frameX == 0) _frameX = 1;
			else _frameX = 0;
		}
		else
		{
			if (_frameX == 0) _frameX = 2;
			else _frameX = 0;
		}
		_isBeat = false;
	}

	if (OBJECTMANAGER->getChainCount() != 0)
		_frameY = 1;
	else
		_frameY = 0;
}

void floorBoss::render()
{
	if (_frameX == 0)
	{
		if (_isSaw)
		{
			if (_isSight)
			{
				if (_hasLight)
					IMAGEMANAGER->findImage(IMAGE_NAME[IMAGE_NAME_FLOOR_03])->frameRender(_idxX * TILE_SIZE, _idxY * TILE_SIZE, _frameX, 1);
				else
					IMAGEMANAGER->findImage(IMAGE_NAME[IMAGE_NAME_FLOOR_03])->frameRender(_idxX * TILE_SIZE, _idxY * TILE_SIZE, _frameX, 1, 0.5f);
			}
			else
			{
				IMAGEMANAGER->findImage(IMAGE_NAME[IMAGE_NAME_FLOOR_03])->frameRender(_idxX * TILE_SIZE, _idxY * TILE_SIZE, _frameX, 1, 0.5f);
			}
		}
	}
	else
	{
		if (_isSaw)
		{
			if (_isSight)
			{
				if (_hasLight)
					IMAGEMANAGER->findImage(IMAGE_NAME[IMAGE_NAME_FLOOR_03])->frameRender(_idxX * TILE_SIZE, _idxY * TILE_SIZE, _frameX, _frameY);
				else
					IMAGEMANAGER->findImage(IMAGE_NAME[IMAGE_NAME_FLOOR_03])->frameRender(_idxX * TILE_SIZE, _idxY * TILE_SIZE, _frameX, _frameY, 0.5f);
			}
			else
			{
				IMAGEMANAGER->findImage(IMAGE_NAME[IMAGE_NAME_FLOOR_03])->frameRender(_idxX * TILE_SIZE, _idxY * TILE_SIZE, _frameX, _frameY, 0.5f);
			}
		}
	}
}

void floorBoss::checkFever(int idxX, int idxY)
{
	if ((idxX % 2 == 1 && idxY % 2 == 0) || (idxX % 2 == 0 && idxY % 2 == 1))						//y->Ȧ x->¦ / y->¦ x->Ȧ �϶�
	{
		_isCrossStripes = true;
	}
	else if ((idxY % 2 == 0 && idxX % 2 == 0) || (idxY % 2 == 1 && idxX % 2 == 1))
	{
		_isCrossStripes = false;
	}
}

void floorBoss::floorAni()
{
}
