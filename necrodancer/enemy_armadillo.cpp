#include "stdafx.h"
#include "enemy_armadillo.h"


enemy_armadillo::enemy_armadillo()
{
}


enemy_armadillo::~enemy_armadillo()
{
}

HRESULT enemy_armadillo::init(string imgName, int idxX, int idxY)
{
	enemy::init(imgName, idxX, idxY);

	_subX = 26;
	_subY = 26;
	_damage = 3;
	_heart = 1;
	_maxHeart = 1;

	_isLeft = true;
	_isStop = true;
	_isStun = false;

	aniSetUp();

	return S_OK;
}

void enemy_armadillo::release()
{
}

void enemy_armadillo::update()
{
	jumpMoveEnemy();

	player* tempPlayer = OBJECTMANAGER->getPlayer();

	if (_isStun)
	{
		aniPlay_Stun();
	}

	if (_isBeat)
	{
		if (_isStun)
		{
			_curMoveBeat++;
			if (_curMoveBeat == 3)
			{
				_isStun = false;
				_curMoveBeat = 0;
				aniPlay_Stand();
			}
		}

		if (!_isStun && _isStop)
		{
			if (tempPlayer->getIdxX() == _idxX && _idxY > tempPlayer->getIdxY() - 10 && _idxY < tempPlayer->getIdxY() + 10)
			{
				if (_idxY >= tempPlayer->getIdxY())
				{
					_direction = DIRECTION_UP;
					_isStop = false;
					aniPlay_Vertical();
				}
				else if (_idxY < tempPlayer->getIdxY())
				{
					_direction = DIRECTION_DOWN;
					_isStop = false;
					aniPlay_Vertical();
				}

			}
			if (tempPlayer->getIdxY() == _idxY && _idxX > tempPlayer->getIdxX() - 10 && _idxX < tempPlayer->getIdxX() + 10)
			{
				if (_idxX >= tempPlayer->getIdxX())
				{
					_direction = DIRECTION_LEFT;
					_isStop = false;
					_isLeft = true;
					aniPlay_Horizon();
				}
				else if (_idxX < tempPlayer->getIdxX())
				{
					_direction = DIRECTION_RIGHT;
					_isLeft = false;
					_isStop = false;
					aniPlay_Horizon();
				}
			}
		}

		OBJECT_TYPE objType;

		if (_direction == DIRECTION_LEFT)
		{
			parentObj* tempObj = OBJECTMANAGER->getCheckObj(_idxX - 1, _idxY);

			if (tempObj != NULL)
			{
				objType = tempObj->getObjType();

				if (objType == OBJECT_TYPE_WALL)
				{
					if(tempObj->getImgName() == "wall_01" || tempObj->getImgName() == "wall_02" || 
						tempObj->getImgName() == "wall_05" || tempObj->getImgName() == "wall_06")
						OBJECTMANAGER->deleteObject(tempObj);
					_moveDistance = TILE_SIZE;
					_isHalfMove = true;
					_isStun = true;
					SOUNDMANAGER->play("sound_armadillo_wallimpact");
				}
				else if (objType == OBJECT_TYPE_ENEMY)
				{
					_moveDistance = TILE_SIZE;
					_isHalfMove = true;
					_isStun = true;
					SOUNDMANAGER->play("sound_armadillo_wallimpact");
				}
				else if (objType == OBJECT_TYPE_PLAYER)
				{
					_moveDistance = TILE_SIZE;
					_isHalfMove = true;
					_isStun = true;
					SOUNDMANAGER->play("sound_armadillo_wallimpact");
					attackEnemy(_direction);
				}
			}
			else
			{
				_moveDistance = TILE_SIZE;
				OBJECTMANAGER->setTileIdx(this, _idxX - 1, _idxY);
			}
		}
		else if (_direction == DIRECTION_RIGHT)
		{
			parentObj* tempObj = OBJECTMANAGER->getCheckObj(_idxX + 1, _idxY);

			if (tempObj != NULL)
			{
				objType = tempObj->getObjType();

				if (objType == OBJECT_TYPE_WALL)
				{
					if (tempObj->getImgName() == "wall_01" || tempObj->getImgName() == "wall_02" ||
						tempObj->getImgName() == "wall_05" || tempObj->getImgName() == "wall_06")
						OBJECTMANAGER->deleteObject(tempObj);
					_moveDistance = TILE_SIZE;
					_isHalfMove = true;
					_isStun = true;
					SOUNDMANAGER->play("sound_armadillo_wallimpact");
				}
				else if (objType == OBJECT_TYPE_ENEMY)
				{
					_moveDistance = TILE_SIZE;
					_isHalfMove = true;
					_isStun = true;
					SOUNDMANAGER->play("sound_armadillo_wallimpact");
				}
				else if (objType == OBJECT_TYPE_PLAYER)
				{
					_moveDistance = TILE_SIZE;
					_isHalfMove = true;
					_isStun = true;
					SOUNDMANAGER->play("sound_armadillo_wallimpact");
					attackEnemy(_direction);
				}
			}
			else
			{
				_moveDistance = TILE_SIZE;
				OBJECTMANAGER->setTileIdx(this, _idxX + 1, _idxY);
			}
		}
		else if (_direction == DIRECTION_UP)
		{
			parentObj* tempObj = OBJECTMANAGER->getCheckObj(_idxX, _idxY - 1);

			if (tempObj != NULL)
			{
				objType = tempObj->getObjType();

				if (objType == OBJECT_TYPE_WALL)
				{
					if (tempObj->getImgName() == "wall_01" || tempObj->getImgName() == "wall_02" ||
						tempObj->getImgName() == "wall_05" || tempObj->getImgName() == "wall_06")
						OBJECTMANAGER->deleteObject(tempObj);
					_moveDistance = TILE_SIZE;
					_isHalfMove = true;
					_isStun = true;
					SOUNDMANAGER->play("sound_armadillo_wallimpact");
				}
				else if (objType == OBJECT_TYPE_ENEMY)
				{
					_moveDistance = TILE_SIZE;
					_isHalfMove = true;
					_isStun = true;
					SOUNDMANAGER->play("sound_armadillo_wallimpact");
				}
				else if (objType == OBJECT_TYPE_PLAYER)
				{
					_moveDistance = TILE_SIZE;
					_isHalfMove = true;
					_isStun = true;
					SOUNDMANAGER->play("sound_armadillo_wallimpact");
					attackEnemy(_direction);
				}
			}
			else
			{
				_moveDistance = TILE_SIZE;
				OBJECTMANAGER->setTileIdx(this, _idxX, _idxY - 1);
			}
		}
		else if (_direction == DIRECTION_DOWN)
		{
			parentObj* tempObj = OBJECTMANAGER->getCheckObj(_idxX, _idxY + 1);

			if (tempObj != NULL)
			{
				objType = tempObj->getObjType();

				if (objType == OBJECT_TYPE_WALL)
				{
					if (tempObj->getImgName() == "wall_01" || tempObj->getImgName() == "wall_02" ||
						tempObj->getImgName() == "wall_05" || tempObj->getImgName() == "wall_06")
						OBJECTMANAGER->deleteObject(tempObj);
					_moveDistance = TILE_SIZE;
					_isHalfMove = true;
					_isStun = true;
					SOUNDMANAGER->play("sound_armadillo_wallimpact");
				}
				else if (objType == OBJECT_TYPE_ENEMY)
				{
					_moveDistance = TILE_SIZE;
					_isHalfMove = true;
					_isStun = true;
					SOUNDMANAGER->play("sound_armadillo_wallimpact");
				}
				else if (objType == OBJECT_TYPE_PLAYER)
				{
					_moveDistance = TILE_SIZE;
					_isHalfMove = true;
					_isStun = true;
					SOUNDMANAGER->play("sound_armadillo_wallimpact");
					attackEnemy(_direction);
				}
			}
			else
			{
				_moveDistance = TILE_SIZE;
				OBJECTMANAGER->setTileIdx(this, _idxX, _idxY + 1);
			}
		}

		_isBeat = false;
	}

	
}

void enemy_armadillo::render()
{
	if (_isSaw)
	{
		IMAGEMANAGER->findImage("enemy_shadow")->render(_posX - _subX, _posY - _subY - _posZ);
		if (!_isLeft)
			_img->aniRenderReverseX(_posX - _subX, _posY - _subY - _posZ, _ani);
		else
			_img->aniRender(_posX - _subX, _posY - _subY - _posZ, _ani);
	}

	if (_isDrawHP && _heart != _maxHeart)
	{
		for (int i = _heart; i < _maxHeart; i++)
		{
			IMAGEMANAGER->findImage("enemy_heart_empty")->render((_posX - 5) - (_maxHeart / 2) * 24 + 24 * i - 7, _posY - _subY - 24);
		}
		for (int i = 0; i < _heart; i++)
		{
			IMAGEMANAGER->findImage("enemy_heart")->render((_posX - 5) - (_maxHeart / 2) * 24 + 24 * i - 7, _posY - _subY - 24);
		}
	}
}

void enemy_armadillo::aniSetUp()
{
	KEYANIMANAGER->addAnimationType("enemy_armadillo");

	int stand[] = { 0,1 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_armadillo", "armadillo_stand", "enemy_armadillo", stand, 2, 2, true);

	int stun[] = { 2 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_armadillo", "armadillo_stun", "enemy_armadillo", stun, 1, 1, true);

	int vertical[] = { 3,4,5,6 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_armadillo", "armadillo_vertical", "enemy_armadillo", vertical, 4, ANISPEED, true);

	int horizon[] = { 7,8,9,10 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_armadillo", "armadillo_horizon", "enemy_armadillo", horizon, 4, ANISPEED, true);

	int stand_Shadow[] = { 11,12 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_armadillo", "armadillo_stand_shadow", "enemy_armadillo", stand_Shadow, 2, 2, true);

	int stun_Shadow[] = { 13 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_armadillo", "armadillo_stun_shadow", "enemy_armadillo", stun_Shadow, 1, 1, true);

	int vertical_Shadow[] = { 14,15,16,17 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_armadillo", "armadillo_vertical_shadow", "enemy_armadillo", vertical_Shadow, 4, ANISPEED, true);

	int horizon_Shadow[] = { 18,19,20,21 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_armadillo", "armadillo_horizon_shadow", "enemy_armadillo", horizon_Shadow, 4, ANISPEED, true);


	_ani = KEYANIMANAGER->findAnimation("enemy_armadillo", "armadillo_stand");
	_ani->start();
}

void enemy_armadillo::aniPlay_Stand()
{
	if (_isSaw)
	{
		//그림자이미지
		if (_isSight)
		{
			if (_hasLight)
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_armadillo", "armadillo_stand");
				_ani->start();
			}
			else
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_armadillo", "armadillo_stand_shadow");
				_ani->start();
			}
		}
		else
		{
			_ani = KEYANIMANAGER->findAnimation("enemy_armadillo", "armadillo_stand_shadow");
			_ani->start();
		}
	}
}

void enemy_armadillo::aniPlay_Stun()
{
	if (_isSaw)
	{
		//그림자이미지
		if (_isSight)
		{
			if (_hasLight)
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_armadillo", "armadillo_stun");
				_ani->start();
			}
			else
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_armadillo", "armadillo_stun_shadow");
				_ani->start();
			}
		}
		else
		{
			_ani = KEYANIMANAGER->findAnimation("enemy_armadillo", "armadillo_stun_shadow");
			_ani->start();
		}
	}
}

void enemy_armadillo::aniPlay_Horizon()
{
	if (_isSaw)
	{
		//그림자이미지
		if (_isSight)
		{
			if (_hasLight)
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_armadillo", "armadillo_horizon");
				_ani->start();
			}
			else
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_armadillo", "armadillo_horizon_shadow");
				_ani->start();
			}
		}
		else
		{
			_ani = KEYANIMANAGER->findAnimation("enemy_armadillo", "armadillo_horizon_shadow");
			_ani->start();
		}
	}
}

void enemy_armadillo::aniPlay_Vertical()
{
	if (_isSaw)
	{
		//그림자이미지
		if (_isSight)
		{
			if (_hasLight)
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_armadillo", "armadillo_vertical");
				_ani->start();
			}
			else
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_armadillo", "armadillo_vertical_shadow");
				_ani->start();
			}
		}
		else
		{
			_ani = KEYANIMANAGER->findAnimation("enemy_armadillo", "armadillo_vertical_shadow");
			_ani->start();
		}
	}
}

void enemy_armadillo::jumpMoveEnemy()
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
				//_direction = DIRECITON_NONE;
				_posZ = 0;
				_jumpPower = 0;
				horizonSet();
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
				//_direction = DIRECITON_NONE;
				_posZ = 0;
				_jumpPower = 0;
				horizonSet();
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
				//_direction = DIRECITON_NONE;
				_posZ = 0;
				_jumpPower = 0;
				verticalSet();
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
				//_direction = DIRECITON_NONE;
				_posZ = 0;
				_jumpPower = 0;
				verticalSet();
			}
			break;
		}
	}
	else
	{
		switch (_direction)
		{
		case DIRECTION_LEFT:
			_moveDistance -= _speed;
			if (_moveDistance)
			{
				if (_moveDistance > TILE_SIZE / 2)
				{
					_posX -= _speed;
					_posZ -= _jumpPower;
					_jumpPower -= 1.2f;
				}
				else
				{
					_posX += _speed;
					_posZ += _jumpPower;
					_jumpPower -= 1.2f;
				}

			}
			if (_moveDistance <= 0)
			{
				_direction = DIRECITON_NONE;
				_posZ = 0;
				_jumpPower = 0;
				horizonSet();
				_isHalfMove = false;
				
				_isStop = true;
			}

			break;
		case DIRECTION_RIGHT:
			_moveDistance -= _speed;
			if (_moveDistance)
			{
				if (_moveDistance > TILE_SIZE / 2)
				{
					_posX += _speed;
					_posZ -= _jumpPower;
					_jumpPower -= 1.2f;
				}
				else
				{
					_posX -= _speed;
					_posZ += _jumpPower;
					_jumpPower -= 1.2f;
				}
			}
			if (_moveDistance <= 0)
			{
				_direction = DIRECITON_NONE;
				_posZ = 0;
				_jumpPower = 0;
				horizonSet();
				_isHalfMove = false;
				
				_isStop = true;
			}
			break;
		case DIRECTION_UP:
			_moveDistance -= _speed;
			if (_moveDistance)
			{
				if (_moveDistance > TILE_SIZE / 2)
				{
					_posY -= _speed;
					_posZ -= _jumpPower;
					_jumpPower -= 1.2f;
				}
				else
				{
					_posY += _speed;
					_posZ += _jumpPower;
					_jumpPower -= 1.2f;
				}
			}
			if (_moveDistance <= 0)
			{
				_direction = DIRECITON_NONE;
				_posZ = 0;
				_jumpPower = 0;
				verticalSet();
				_isHalfMove = false;
				
				_isStop = true;
			}

			break;
		case DIRECTION_DOWN:
			_moveDistance -= _speed;
			if (_moveDistance)
			{
				if (_moveDistance > TILE_SIZE / 2)
				{
					_posY += _speed;
					_posZ += _jumpPower;
					_jumpPower -= 1.2f;
				}
				else
				{
					_posY -= _speed;
					_posZ -= _jumpPower;
					_jumpPower -= 1.2f;
				}
			}
			if (_moveDistance <= 0)
			{
				_direction = DIRECITON_NONE;
				_posZ = 0;
				_jumpPower = 0;
				verticalSet();
				_isHalfMove = false;
				
				_isStop = true;
			}
			break;
		}
	}
}

void enemy_armadillo::hitEnemy(int damage)
{
	player* tempPlayer = OBJECTMANAGER->getPlayer();

	//int tempX = _idxX - tempPlayer->getIdxX();
	//int tempY = _idxY - tempPlayer->getIdxY();

	PLAYER_STATE tempState = tempPlayer->getAttDir();


	if (!_isStun && !_isStop)
	{
		_direction = (DIRECTION)tempState;

		if (_direction == DIRECTION_LEFT || _direction == DIRECTION_RIGHT)
			aniPlay_Horizon();
		else if (_direction == DIRECTION_DOWN || _direction == DIRECTION_UP)
			aniPlay_Vertical();
	}
	else if (_isStop || _isStun)
	{
		_isDrawHP = true;
		_heart -= damage;

		if (_heart <= 0) this->dieEnemy();
	}

	//if (tempX < 0) //왼
	//{
	//	_direction = DIRECTION_LEFT;
	//	_isLeft = true;
	//	if (tempY < 0)
	//	{
	//		_direction = DIRECTION_UP;
	//	}
	//	else if (tempY > 0)
	//	{
	//		_direction = DIRECTION_DOWN;
	//	}
	//	//_moveDistance = TILE_SIZE;
	//	//OBJECTMANAGER->setTileIdx(this, _idxX - 1, _idxY);
	//}
	//else if (tempX > 0)
	//{
	//	_direction = DIRECTION_RIGHT;
	//	_isLeft = false;
	//	if (tempY < 0)
	//	{
	//		_direction = DIRECTION_UP;
	//	}
	//	else if (tempY > 0)
	//	{
	//		_direction = DIRECTION_DOWN;
	//	}
	//	//_moveDistance = TILE_SIZE;
	//	//OBJECTMANAGER->setTileIdx(this, _idxX + 1, _idxY);
	//}
	//else if (tempY < 0)
	//{
	//	_direction = DIRECTION_UP;
	//	if (tempX < 0)
	//	{
	//		_direction = DIRECTION_LEFT;
	//		_isLeft = true;
	//	}
	//	else if (tempX > 0)
	//	{
	//		_direction = DIRECTION_RIGHT;
	//		_isLeft = false;
	//	}
	//	//_moveDistance = TILE_SIZE;
	//	//OBJECTMANAGER->setTileIdx(this, _idxX, _idxY - 1);
	//}
	//else if (tempY > 0)
	//{
	//	_direction = DIRECTION_DOWN;
	//	if (tempX < 0)
	//	{
	//		_direction = DIRECTION_LEFT;
	//		_isLeft = true;
	//	}
	//	else if (tempX > 0)
	//	{
	//		_direction = DIRECTION_RIGHT;
	//		_isLeft = false;
	//	}
	//	//_moveDistance = TILE_SIZE;
	//	//OBJECTMANAGER->setTileIdx(this, _idxX, _idxY + 1);
	//}

}
