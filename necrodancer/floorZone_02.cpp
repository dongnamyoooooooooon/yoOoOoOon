#include "stdafx.h"
#include "floorZone_02.h"


floorZone_02::floorZone_02()
{
}


floorZone_02::~floorZone_02()
{
}

HRESULT floorZone_02::init(int idxX, int idxY)
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


	_posX = _idxX * TILE_SIZE;
	_posY = _idxY * TILE_SIZE;

	_hasLight = false;
	_isSight = false;
	_isSaw = true;

	_num = 0;

	_frameY = RND->getInt(4);

	return S_OK;
}

void floorZone_02::release()
{
}

void floorZone_02::update()
{
	if (_isBeat)
	{
		if (OBJECTMANAGER->getChainCount() != 0)
		{
			_num++;
			if (_num % 2 != 0)
			{
				if (_isCrossStripes)
				{
					if (_frameX == 0) _frameX = 1;
					
				}
				else  _frameX = 0;
			}
			else if (_num % 2 == 0)
			{
				if (!_isCrossStripes)
				{
					if (_frameX == 0) _frameX = 2;
				}
				else _frameX = 0;
			}
			if (_num >= 1000) _num = 0;
		}
		else
			_frameX = 0;

		_isBeat = false;
	}

	
	

}

void floorZone_02::render()
{
	if (_isSaw)
	{
		if (_isSight)
		{
			if (_hasLight)
				IMAGEMANAGER->findImage(IMAGE_NAME[IMAGE_NAME_FLOOR_02])->frameRender(_idxX * TILE_SIZE, _idxY * TILE_SIZE, _frameX, _frameY);
			else
				IMAGEMANAGER->findImage(IMAGE_NAME[IMAGE_NAME_FLOOR_02])->frameRender(_idxX * TILE_SIZE, _idxY * TILE_SIZE, _frameX, _frameY, 0.5f);
		}
		else
		{
			IMAGEMANAGER->findImage(IMAGE_NAME[IMAGE_NAME_FLOOR_02])->frameRender(_idxX * TILE_SIZE, _idxY * TILE_SIZE, _frameX, _frameY, 0.5f);
		}
	}

}

void floorZone_02::checkFever(int idxX, int idxY)
{
	if ((idxX % 2 == 0 && idxY % 2 == 1) || (idxX % 2 == 1 && idxY % 2 == 0))						//y->Ȧ x->¦ / y->¦ x->Ȧ �϶�
	{
		_isCrossStripes = true;
	}
	else if ((idxY % 2 == 0 && idxX % 2 == 0) || (idxY % 2 == 1 && idxX % 2 == 1))
	{
		_isCrossStripes = false;
	}
}

void floorZone_02::floorAni()
{
	_count++;

	if (_count % 10 == 0)
	{
		_count = 0;
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
	}
}
