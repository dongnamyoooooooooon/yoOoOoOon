#include "stdafx.h"
#include "enemy_dragon_green.h"


enemy_dragon_green::enemy_dragon_green()
{
}


enemy_dragon_green::~enemy_dragon_green()
{
}

HRESULT enemy_dragon_green::init(string imgName, int idxX, int idxY)
{
	enemy::init(imgName, idxX, idxY);

	_moveBeat = 2;
	_subX = 53;
	_subY = 72;
	_damage = 2;
	_heart = 4;
	_maxHeart = 4;

	_isLeft = true;

	aniSetUp();

	return S_OK;
}

void enemy_dragon_green::release()
{
}

void enemy_dragon_green::update()
{
	OBJECT_TYPE objType;
	jumpMoveEnemy();

	if (_isBeat)
	{
		_curMoveBeat++;
		aniPlay_Stand();
		if (_moveBeat == _curMoveBeat)
		{
			_curMoveBeat = 0;
			aStarLoad();

			if (_direction == DIRECTION_LEFT)
			{
				_isLeft = true;
				parentObj* obj = OBJECTMANAGER->getCheckObj(_idxX - 1, _idxY);

				if (obj != NULL)
				{
					objType = obj->getObjType();

					if (objType == OBJECT_TYPE_WALL && obj->getImgName() != "wall_11")
					{
						if (obj->getImgName() == IMAGE_NAME[IMAGE_NAME_WALL_01] || obj->getImgName() == IMAGE_NAME[IMAGE_NAME_WALL_02])
						{
							SOUNDMANAGER->play("sound_dig_dirt");
						}
						else
							SOUNDMANAGER->play("sound_dig_stone");
						OBJECTMANAGER->deleteObject(obj);
					}
				}
			}
			else if (_direction == DIRECTION_RIGHT)
			{
				_isLeft = false;
				parentObj* obj = OBJECTMANAGER->getCheckObj(_idxX + 1, _idxY);

				if (obj != NULL)
				{
					objType = obj->getObjType();

					if (objType == OBJECT_TYPE_WALL && obj->getImgName() != "wall_11")
					{
						if (obj->getImgName() == IMAGE_NAME[IMAGE_NAME_WALL_01] || obj->getImgName() == IMAGE_NAME[IMAGE_NAME_WALL_02])
						{
							SOUNDMANAGER->play("sound_dig_dirt");
						}
						else
							SOUNDMANAGER->play("sound_dig_stone");
						OBJECTMANAGER->deleteObject(obj);
					}
				}
			}
			else if (_direction == DIRECTION_UP)
			{
				parentObj* obj = OBJECTMANAGER->getCheckObj(_idxX, _idxY - 1);

				if (obj != NULL)
				{
					objType = obj->getObjType();

					if (objType == OBJECT_TYPE_WALL && obj->getImgName() != "wall_11")
					{
						if (obj->getImgName() == IMAGE_NAME[IMAGE_NAME_WALL_01] || obj->getImgName() == IMAGE_NAME[IMAGE_NAME_WALL_02])
						{
							SOUNDMANAGER->play("sound_dig_dirt");
						}
						else
							SOUNDMANAGER->play("sound_dig_stone");
						OBJECTMANAGER->deleteObject(obj);
					}
				}
			}
			else if (_direction == DIRECTION_DOWN)
			{
				parentObj* obj = OBJECTMANAGER->getCheckObj(_idxX, _idxY + 1);

				if (obj != NULL)
				{
					objType = obj->getObjType();

					if (objType == OBJECT_TYPE_WALL && obj->getImgName() != "wall_11")
					{
						if (obj->getImgName() == IMAGE_NAME[IMAGE_NAME_WALL_01] || obj->getImgName() == IMAGE_NAME[IMAGE_NAME_WALL_02])
						{
							SOUNDMANAGER->play("sound_dig_dirt");
						}
						else
							SOUNDMANAGER->play("sound_dig_stone");
						OBJECTMANAGER->deleteObject(obj);
					}
				}
			}
		}
		_isBeat = false;
	}
}

void enemy_dragon_green::render()
{
	if (_isSaw)
	{
		IMAGEMANAGER->findImage("enemy_shadow")->render(_posX - _subX, _posY - _subY + _posZ);
		if (!_isLeft)
			_img->aniRenderReverseX(_posX - _subX, _posY - _subY + _posZ, _ani);
		else
			_img->aniRender(_posX - _subX, _posY - _subY + _posZ, _ani);
	}

	if (_isDrawHP && _heart != _maxHeart)
	{
		for (int i = _heart; i < _maxHeart; i++)
		{
			IMAGEMANAGER->findImage("enemy_heart_empty")->render((_posX + 5) - (_maxHeart / 2) * 24 + 24 * i - 7, _posY - _subY - 24);
		}
		for (int i = 0; i < _heart; i++)
		{
			IMAGEMANAGER->findImage("enemy_heart")->render((_posX + 5) - (_maxHeart / 2) * 24 + 24 * i - 7, _posY - _subY - 24);
		}
	}
}

void enemy_dragon_green::aniSetUp()
{
	KEYANIMANAGER->addAnimationType("enemy_dragon_green");

	int stand[] = { 0,1 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_dragon_green", "dragon_green_stand", "enemy_dragon_green", stand, 2, ANISPEED, true);

	int stand_shadow[] = { 2,3 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_dragon_green", "dragon_green_stand_shadow", "enemy_dragon_green", stand_shadow, 2, ANISPEED, true);

	_ani = KEYANIMANAGER->findAnimation("enemy_dragon_green", "dragon_green_stand");
	_ani->start();

}

void enemy_dragon_green::aniPlay_Stand()
{
	if (_isSaw)
	{
		//그림자이미지
		if (_isSight)
		{
			if (_hasLight)
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_dragon_green", "dragon_green_stand");
				_ani->start();
			}
			else
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_dragon_green", "dragon_green_stand_shadow");
				_ani->start();
			}
		}
		else
		{
			_ani = KEYANIMANAGER->findAnimation("enemy_dragon_green", "dragon_green_stand_shadow");
			_ani->start();
		}
	}
}

void enemy_dragon_green::jumpMoveEnemy()
{
	_speed = TIMEMANAGER->getElapsedTime() * PLAYER_SPEED;

	if (!_isHalfMove)
	{
		switch (_direction)
		{
		case DIRECTION_LEFT:
			_moveDistance -= _speed;
			_posX -= _speed;
			if (_moveDistance)
			{
				_posZ -= _jumpPower;
				_jumpPower -= 1.2f;
			}
			if (_moveDistance <= 0)
			{
				_direction = DIRECITON_NONE;
				_posZ = 0;
				_jumpPower = 0;
				horizonSet();
				int num = RND->getFromIntTo(1, 3);
				switch (num)
				{
				case 1:
					SOUNDMANAGER->play("sound_dragon_walk_01");
					break;

				case 2:
					SOUNDMANAGER->play("sound_dragon_walk_02");
					break;

				case 3:
					SOUNDMANAGER->play("sound_dragon_walk_03");
					break;
				}
			}

			break;
		case DIRECTION_RIGHT:
			_moveDistance -= _speed;
			_posX += _speed;
			if (_moveDistance)
			{
				_posZ -= _jumpPower;
				_jumpPower -= 1.2f;
			}
			if (_moveDistance <= 0)
			{
				_direction = DIRECITON_NONE;
				_posZ = 0;
				_jumpPower = 0;
				horizonSet();
				int num = RND->getFromIntTo(1, 3);
				switch (num)
				{
				case 1:
					SOUNDMANAGER->play("sound_dragon_walk_01");
					break;

				case 2:
					SOUNDMANAGER->play("sound_dragon_walk_02");
					break;

				case 3:
					SOUNDMANAGER->play("sound_dragon_walk_03");
					break;
				}
			}
			break;
		case DIRECTION_UP:
			_moveDistance -= _speed;
			_posY -= _speed;
			if (_moveDistance)
			{
				_posZ += _jumpPower;
				_jumpPower -= 1.2f;
			}
			if (_moveDistance <= 0)
			{
				_direction = DIRECITON_NONE;
				_posZ = 0;
				_jumpPower = 0;
				verticalSet();
				int num = RND->getFromIntTo(1, 3);
				switch (num)
				{
				case 1:
					SOUNDMANAGER->play("sound_dragon_walk_01");
					break;

				case 2:
					SOUNDMANAGER->play("sound_dragon_walk_02");
					break;

				case 3:
					SOUNDMANAGER->play("sound_dragon_walk_03");
					break;
				}
			}

			break;
		case DIRECTION_DOWN:
			_moveDistance -= _speed;
			_posY += _speed;
			if (_moveDistance)
			{
				_posZ += _jumpPower;
				_jumpPower -= 1.2f;
			}
			if (_moveDistance <= 0)
			{
				_direction = DIRECITON_NONE;
				_posZ = 0;
				_jumpPower = 0;
				verticalSet();
				int num = RND->getFromIntTo(1, 3);
				switch (num)
				{
				case 1:
					SOUNDMANAGER->play("sound_dragon_walk_01");
					break;

				case 2:
					SOUNDMANAGER->play("sound_dragon_walk_02");
					break;

				case 3:
					SOUNDMANAGER->play("sound_dragon_walk_03");
					break;
				}
			}
			break;
		}
	}
}
