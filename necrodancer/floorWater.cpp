#include "stdafx.h"
#include "floorWater.h"


floorWater::floorWater()
{
}


floorWater::~floorWater()
{
}

HRESULT floorWater::init(int idxX, int idxY)
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
	}
	else
	{
		_frameX = 2;
	}

	_frameY = 0;

	_posX = _idxX * TILE_SIZE;
	_posY = _idxY * TILE_SIZE;

	_hasLight = false;
	_isSight = false;
	_isSaw = true;



	return S_OK;
}

void floorWater::release()
{
}

void floorWater::update()
{
	if (_isBeat)
	{
		if (_isCrossStripes)
		{
			if (_frameX == 0) _frameX = 1;
			else _frameX = 0;
		}
		

		_isBeat = false;
	}
}

void floorWater::render()
{
	if (_frameX == 0)
	{
		if (_isSaw)
		{
			if (_isSight)
			{
				if (_hasLight)
					IMAGEMANAGER->findImage(IMAGE_NAME[IMAGE_NAME_FLOOR_05])->frameRender(_idxX * TILE_SIZE, _idxY * TILE_SIZE, _frameX, 0);
				else
					IMAGEMANAGER->findImage(IMAGE_NAME[IMAGE_NAME_FLOOR_05])->frameRender(_idxX * TILE_SIZE, _idxY * TILE_SIZE, _frameX, 0, 0.5f);
			}
			else
			{
				IMAGEMANAGER->findImage(IMAGE_NAME[IMAGE_NAME_FLOOR_05])->frameRender(_idxX * TILE_SIZE, _idxY * TILE_SIZE, _frameX, 0, 0.5f);
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
					IMAGEMANAGER->findImage(IMAGE_NAME[IMAGE_NAME_FLOOR_05])->frameRender(_idxX * TILE_SIZE, _idxY * TILE_SIZE, _frameX, _frameY);
				else
					IMAGEMANAGER->findImage(IMAGE_NAME[IMAGE_NAME_FLOOR_05])->frameRender(_idxX * TILE_SIZE, _idxY * TILE_SIZE, _frameX, _frameY, 0.5f);
			}
			else
			{
				IMAGEMANAGER->findImage(IMAGE_NAME[IMAGE_NAME_FLOOR_05])->frameRender(_idxX * TILE_SIZE, _idxY * TILE_SIZE, _frameX, _frameY, 0.5f);
			}
		}
	}

	WCHAR str[128];

	swprintf_s(str, L"%d", _frameX);
	D2DMANAGER->drawText(str, CAMERA->getPosX() + 10, CAMERA->getPosY() + 400, 50, RGB(0, 255, 255));
}

void floorWater::checkFever(int idxX, int idxY)
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

void floorWater::floorAni()
{
	if (_frameX == 0)
	{
		if (_isSaw)
		{
			if (_isSight)
			{
				if (_hasLight)
					IMAGEMANAGER->findImage(IMAGE_NAME[IMAGE_NAME_FLOOR_05])->frameRender(_idxX * TILE_SIZE, _idxY * TILE_SIZE + 26, 52, 26, _frameX, 0);
				else
					IMAGEMANAGER->findImage(IMAGE_NAME[IMAGE_NAME_FLOOR_05])->frameRender(_idxX * TILE_SIZE, _idxY * TILE_SIZE + 26, 52, 26, _frameX, 0, 0.5f);
			}
			else
			{
				IMAGEMANAGER->findImage(IMAGE_NAME[IMAGE_NAME_FLOOR_05])->frameRender(_idxX * TILE_SIZE, _idxY * TILE_SIZE + 26, 52, 26, _frameX, 0, 0.5f);
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
					IMAGEMANAGER->findImage(IMAGE_NAME[IMAGE_NAME_FLOOR_05])->frameRender(_idxX * TILE_SIZE, _idxY * TILE_SIZE + 26, 52, 26, _frameX, _frameY);
				else
					IMAGEMANAGER->findImage(IMAGE_NAME[IMAGE_NAME_FLOOR_05])->frameRender(_idxX * TILE_SIZE, _idxY * TILE_SIZE + 26, 52, 26, _frameX, _frameY, 0.5f);
			}
			else
			{
				IMAGEMANAGER->findImage(IMAGE_NAME[IMAGE_NAME_FLOOR_05])->frameRender(_idxX * TILE_SIZE, _idxY * TILE_SIZE + 26, 52, 26, _frameX, _frameY, 0.5f);
			}
		}
	}
}
