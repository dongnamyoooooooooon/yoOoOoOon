#include "stdafx.h"
#include "floorStair_nothing.h"


floorStair_nothing::floorStair_nothing()
{
}


floorStair_nothing::~floorStair_nothing()
{
}

HRESULT floorStair_nothing::init(int idxX, int idxY)
{

	_idxX = idxX;
	_idxY = idxY;

	_posX = _idxX * TILE_SIZE;
	_posY = _idxY * TILE_SIZE;

	_hasLight = false;
	_objType = OBJECT_TYPE_FLOOR;


	return S_OK;
}

void floorStair_nothing::release()
{
}

void floorStair_nothing::update()
{
}

void floorStair_nothing::render()
{
	if (_isSaw)
	{
		if (_isSight)
		{
			if (_hasLight)
				IMAGEMANAGER->findImage(IMAGE_NAME[IMAGE_NAME_STAIRS_02])->render(_posX, _posY);
			else
				IMAGEMANAGER->findImage(IMAGE_NAME[IMAGE_NAME_STAIRS_02])->render(_posX, _posY, 0.5f);
		}
		else
		{
			IMAGEMANAGER->findImage(IMAGE_NAME[IMAGE_NAME_STAIRS_02])->render(_posX, _posY, 0.5f);
		}
	}
}
