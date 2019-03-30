#include "stdafx.h"
#include "wall.h"


wall::wall()
{
}


wall::~wall()
{
}

HRESULT wall::init(string imgName, int idxX, int idxY, bool isTorch)
{
	_img = IMAGEMANAGER->findImage(imgName);
	_blackImg = IMAGEMANAGER->findImage("alpha_black");
	_imgName = imgName;

	_isTorch = isTorch;

	_idxX = idxX;
	_idxY = idxY;

	_posX = _idxX * TILE_SIZE;
	_posY = _idxY * TILE_SIZE;

	_frameX = 0;
	_frameY = 0;

	_torchFrameX = 0;
	_frameCount = 0;

	_isSaw = false;
	_isSight = false;

	return S_OK;
}

void wall::release()
{
}

void wall::update()
{
	_frameCount++;
	if (_isTorch)
	{
		if (_frameCount % 10 == 0)
		{
			_torchFrameX++;
			if (_torchFrameX >= 4) _torchFrameX = 0;
			if (_frameCount >= 1000) _frameCount = 0;
		}

		rayCast();
	}

}

void wall::render()
{
	if (_isTorch)
	{
		_hasLight = true;

		if (_isSight)
			_isSaw = true;
	}

	if (_isSaw)
	{
		_img->frameRender(_posX, _posY, _frameX, _frameY);
		
		if (_isTorch)	
			IMAGEMANAGER->findImage("frame_fire")->frameRender(_posX + 13, _posY, _torchFrameX, 0);

		if (_isSight)
		{
			if (!_hasLight)		
				_blackImg->render(_posX, _posY, 0, 0, 52, 52, 0.4f);
		}
		else			
			_blackImg->render(_posX, _posY, 0, 0, 52, 52, 0.4f);
	}
	else	
		_blackImg->render(_posX, _posY, 0, 0, 52, 52);
}

bool wall::wallBroken(int power)
{
	if (_wallPower > power)
	{
		SOUNDMANAGER->play("sound_dig_fail");
		return false;
	}
	else
	{
		if (_imgName == IMAGE_NAME[IMAGE_NAME_DOOR_01] || _imgName == IMAGE_NAME[IMAGE_NAME_DOOR_02])
		{
			SOUNDMANAGER->play("sound_door_open");
		}
		else if (_imgName == IMAGE_NAME[IMAGE_NAME_WALL_01] || _imgName == IMAGE_NAME[IMAGE_NAME_WALL_02])
		{
			SOUNDMANAGER->play("sound_dig_dirt");
		}
		else
			SOUNDMANAGER->play("sound_dig_stone");
		return true;
	}
	return false;
}

void wall::rayCast()
{
	_hasLight = true;

	if (_isSight) _isSaw = true;

	parentObj* obj;
	parentObj* floorObj;
	parentObj* obj2;
	parentObj* floorObj2;

	
	obj = OBJECTMANAGER->getCheckObj(_idxX-1, _idxY-1);
	floorObj = OBJECTMANAGER->getCheckFloor(_idxX-1, _idxY-1);

	if (obj != NULL)
	{
		obj->setHasLight(true);
		if (obj->getIsSight() == true) obj->setIsSaw();
	}
	if (floorObj != NULL)
	{
		floorObj->setHasLight(true);
		if (floorObj->getIsSight() == true) floorObj->setIsSaw();
	}


	obj = OBJECTMANAGER->getCheckObj(_idxX + 1, _idxY + 1);
	floorObj = OBJECTMANAGER->getCheckFloor(_idxX + 1, _idxY + 1);

	if (obj != NULL)
	{
		obj->setHasLight(true);
		if (obj->getIsSight() == true) obj->setIsSaw();
	}
	if (floorObj != NULL)
	{
		floorObj->setHasLight(true);
		if (floorObj->getIsSight() == true) floorObj->setIsSaw();
	}


	obj = OBJECTMANAGER->getCheckObj(_idxX + 1, _idxY - 1);
	floorObj = OBJECTMANAGER->getCheckFloor(_idxX + 1, _idxY - 1);

	if (obj != NULL)
	{
		obj->setHasLight(true);
		if (obj->getIsSight() == true) obj->setIsSaw();
	}
	if (floorObj != NULL)
	{
		floorObj->setHasLight(true);
		if (floorObj->getIsSight() == true) floorObj->setIsSaw();
	}


	obj = OBJECTMANAGER->getCheckObj(_idxX - 1, _idxY + 1);
	floorObj = OBJECTMANAGER->getCheckFloor(_idxX - 1, _idxY + 1);

	if (obj != NULL)
	{
		obj->setHasLight(true);
		if (obj->getIsSight() == true) obj->setIsSaw();
	}
	if (floorObj != NULL)
	{
		floorObj->setHasLight(true);
		if (floorObj->getIsSight() == true) floorObj->setIsSaw();
	}



	obj = OBJECTMANAGER->getCheckObj(_idxX, _idxY - 1);
	floorObj = OBJECTMANAGER->getCheckFloor(_idxX, _idxY - 1);

	if (floorObj != NULL)
	{
		floorObj->setHasLight(true);
		if (floorObj->getIsSight() == true) floorObj->setIsSaw();
	}

	if (obj != NULL)
	{
		obj->setHasLight(true);
		if (obj->getIsSight() == true) obj->setIsSaw();

		if (obj->getObjType() != OBJECT_TYPE_WALL)
		{
			if ((obj2 = OBJECTMANAGER->getCheckObj(_idxX, _idxY - 2)) != NULL)
			{
				obj2->setHasLight(true);
				if (obj2->getIsSight() == true) obj2->setIsSaw();
			}
			
			if ((floorObj2 = OBJECTMANAGER->getCheckFloor(_idxX, _idxY - 2)) != NULL)
			{
				floorObj2->setHasLight(true);
				if (floorObj2->getIsSight() == true) floorObj2->setIsSaw();
			}
		}
	}
	else
	{
		if ((obj2 = OBJECTMANAGER->getCheckObj(_idxX, _idxY - 2)) != NULL)
		{
			obj2->setHasLight(true);
			if (obj2->getIsSight() == true) obj2->setIsSaw();
		}

		if ((floorObj2 = OBJECTMANAGER->getCheckFloor(_idxX, _idxY - 2)) != NULL)
		{
			floorObj2->setHasLight(true);
			if (floorObj2->getIsSight() == true) floorObj2->setIsSaw();
		}
	}


	obj = OBJECTMANAGER->getCheckObj(_idxX, _idxY + 1);
	floorObj = OBJECTMANAGER->getCheckFloor(_idxX, _idxY + 1);

	if (floorObj != NULL)
	{
		floorObj->setHasLight(true);
		if (floorObj->getIsSight() == true) floorObj->setIsSaw();
	}

	if (obj != NULL)
	{
		obj->setHasLight(true);
		if (obj->getIsSight() == true) obj->setIsSaw();

		if (obj->getObjType() != OBJECT_TYPE_WALL)
		{
			if ((obj2 = OBJECTMANAGER->getCheckObj(_idxX, _idxY + 2)) != NULL)
			{
				obj2->setHasLight(true);
				if (obj2->getIsSight() == true) obj2->setIsSaw();
			}

			if ((floorObj2 = OBJECTMANAGER->getCheckFloor(_idxX, _idxY + 2)) != NULL)
			{
				floorObj2->setHasLight(true);
				if (floorObj2->getIsSight() == true) floorObj2->setIsSaw();
			}
		}
	}
	else
	{
		if ((obj2 = OBJECTMANAGER->getCheckObj(_idxX, _idxY + 2)) != NULL)
		{
			obj2->setHasLight(true);
			if (obj2->getIsSight() == true) obj2->setIsSaw();
		}

		if ((floorObj2 = OBJECTMANAGER->getCheckFloor(_idxX, _idxY + 2)) != NULL)
		{
			floorObj2->setHasLight(true);
			if (floorObj2->getIsSight() == true) floorObj2->setIsSaw();
		}
	}



	obj = OBJECTMANAGER->getCheckObj(_idxX - 1, _idxY);
	floorObj = OBJECTMANAGER->getCheckFloor(_idxX - 1, _idxY);

	if (floorObj != NULL)
	{
		floorObj->setHasLight(true);
		if (floorObj->getIsSight() == true) floorObj->setIsSaw();
	}

	if (obj != NULL)
	{
		obj->setHasLight(true);
		if (obj->getIsSight() == true) obj->setIsSaw();

		if (obj->getObjType() != OBJECT_TYPE_WALL)
		{
			if ((obj2 = OBJECTMANAGER->getCheckObj(_idxX - 2, _idxY)) != NULL)
			{
				obj2->setHasLight(true);
				if (obj2->getIsSight() == true) obj2->setIsSaw();
			}

			if ((floorObj2 = OBJECTMANAGER->getCheckFloor(_idxX - 2, _idxY)) != NULL)
			{
				floorObj2->setHasLight(true);
				if (floorObj2->getIsSight() == true) floorObj2->setIsSaw();
			}
		}
	}
	else
	{
		if ((obj2 = OBJECTMANAGER->getCheckObj(_idxX - 2, _idxY)) != NULL)
		{
			obj2->setHasLight(true);
			if (obj2->getIsSight() == true) obj2->setIsSaw();
		}

		if ((floorObj2 = OBJECTMANAGER->getCheckFloor(_idxX - 2, _idxY)) != NULL)
		{
			floorObj2->setHasLight(true);
			if (floorObj2->getIsSight() == true) floorObj2->setIsSaw();
		}
	}



	obj = OBJECTMANAGER->getCheckObj(_idxX + 1, _idxY);
	floorObj = OBJECTMANAGER->getCheckFloor(_idxX + 1, _idxY);

	if (floorObj != NULL)
	{
		floorObj->setHasLight(true);
		if (floorObj->getIsSight() == true) floorObj->setIsSaw();
	}

	if (obj != NULL)
	{
		obj->setHasLight(true);
		if (obj->getIsSight() == true) obj->setIsSaw();

		if (obj->getObjType() != OBJECT_TYPE_WALL)
		{
			if ((obj2 = OBJECTMANAGER->getCheckObj(_idxX + 2, _idxY)) != NULL)
			{
				obj2->setHasLight(true);
				if (obj2->getIsSight() == true) obj2->setIsSaw();
			}

			if ((floorObj2 = OBJECTMANAGER->getCheckFloor(_idxX + 2, _idxY)) != NULL)
			{
				floorObj2->setHasLight(true);
				if (floorObj2->getIsSight() == true) floorObj2->setIsSaw();
			}
		}
	}
	else
	{
		if ((obj2 = OBJECTMANAGER->getCheckObj(_idxX + 2, _idxY)) != NULL)
		{
			obj2->setHasLight(true);
			if (obj2->getIsSight() == true) obj2->setIsSaw();
		}

		if ((floorObj2 = OBJECTMANAGER->getCheckFloor(_idxX + 2, _idxY)) != NULL)
		{
			floorObj2->setHasLight(true);
			if (floorObj2->getIsSight() == true) floorObj2->setIsSaw();
		}
	}
}
