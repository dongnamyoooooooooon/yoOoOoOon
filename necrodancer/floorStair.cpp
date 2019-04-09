#include "stdafx.h"
#include "floorStair.h"


floorStair::floorStair()
{
}


floorStair::~floorStair()
{
}

HRESULT floorStair::init(int idxX, int idxY)
{
	_idxX = idxX;
	_idxY = idxY;

	_posX = _idxX * TILE_SIZE;
	_posY = _idxY * TILE_SIZE;

	_hasLight = false;
	_objType = OBJECT_TYPE_FLOOR;

	return S_OK;
}

void floorStair::release()
{
}

void floorStair::update()
{
	parentObj* tempPlayer = NULL;
	vector<parentObj*> vTemp = OBJECTMANAGER->getVObj();
	vector<parentObj*>::iterator viTemp = OBJECTMANAGER->getVIObj();
	
	player* _player = OBJECTMANAGER->getPlayer();

	for (viTemp = vTemp.begin(); viTemp != vTemp.end(); viTemp++)
	{
		if ((*viTemp)->getObjType() == OBJECT_TYPE_PLAYER)
		{
			tempPlayer = *viTemp;
			break;
		}
	}

	if (_player != NULL)
	{
		/*if (nextScene == "·Îºñ")
		{
			int num = 5;
			num++;
		}*/
		if (_player->getIdxX() == _idxX && _player->getIdxY() == _idxY)
		{
			SOUNDMANAGER->allSoundStop();
			SCENEMANAGER->changeScene(nextScene);
		}
	}
}

void floorStair::render()
{

	if (_isSaw)
	{
		if (_isSight)
		{
			if (_hasLight)
				IMAGEMANAGER->findImage(IMAGE_NAME[IMAGE_NAME_STAIRS_01])->render(_posX, _posY);
			else
				IMAGEMANAGER->findImage(IMAGE_NAME[IMAGE_NAME_STAIRS_01])->render(_posX, _posY, 0.5f);
		}
		else
		{
			IMAGEMANAGER->findImage(IMAGE_NAME[IMAGE_NAME_STAIRS_01])->render(_posX, _posY, 0.5f);
		}
	}
}
