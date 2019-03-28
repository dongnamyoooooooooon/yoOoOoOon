#include "stdafx.h"
#include "floorZone_01.h"


floorZone_01::floorZone_01()
{
}


floorZone_01::~floorZone_01()
{
}

HRESULT floorZone_01::init(int idxX, int idxY)
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
	_isSaw = false;

	return S_OK;
}

void floorZone_01::release()
{
}

void floorZone_01::update()
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

	if (OBJECTMANAGER->getFeverCount() != 0)
		_frameY = 1;
	else
		_frameY = 0;
}

void floorZone_01::render()
{
	if (_frameX == 0)
	{
		if (_isSaw)
		{
			if (_isSight)
			{
				if(_hasLight)
					IMAGEMANAGER->findImage(this->getImgName())->frameRender(_idxX, _idxY, _frameX, _frameY);
				else
					IMAGEMANAGER->findImage(this->getImgName())->frameRender(_idxX, _idxY, _frameX, _frameY, 0.5f);
			}
			else
			{
				IMAGEMANAGER->findImage(this->getImgName())->frameRender(_idxX, _idxY, _frameX, _frameY, 0.5f);
			}
			
		}
	}


}

void floorZone_01::checkFever(int idxX, int idxY)
{


}

