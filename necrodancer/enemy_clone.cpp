#include "stdafx.h"
#include "enemy_clone.h"


enemy_clone::enemy_clone()
{
}


enemy_clone::~enemy_clone()
{
}

HRESULT enemy_clone::init(string imgName, int idxX, int idxY)
{
	enemy::init(imgName, idxX, idxY);

	_subX = 26;
	_subY = 36;
	_damage = 1;
	_heart = 1;
	_maxHeart = 1;

	aniSetUp();

	return S_OK;
}

void enemy_clone::release()
{
}

void enemy_clone::update()
{
	player* tempPlayer = OBJECTMANAGER->getPlayer();

	if (tempPlayer->getIsMove() && tempPlayer->getIsPress())
	{
		switch (tempPlayer->getPlayerState())
		{
		case PLAYER_STATE_JUMP_LEFT:
			_attDir = DIRECTION_RIGHT;
			_isLeft = true;
			break;

		case PLAYER_STATE_JUMP_RIGHT:
			_attDir = DIRECTION_LEFT;
			_isLeft = false;
			break;

		case PLAYER_STATE_JUMP_UP:
			_attDir = DIRECTION_DOWN;
			break;

		case PLAYER_STATE_JUMP_DOWN:
			_attDir = DIRECTION_UP;
			break;
		}
	}

	int idxAdd = 1;

	if (_isBeat)
	{
		aniPlay_Stand();

		OBJECT_TYPE objType;

		if (_attDir == DIRECTION_LEFT)
		{
			parentObj* tempObj = OBJECTMANAGER->getCheckObj(_idxX - idxAdd, _idxY);

			if (tempObj != NULL)
			{
				objType = tempObj->getObjType();

				if (objType == OBJECT_TYPE_PLAYER)
				{
					attackEnemy(_attDir);
					_attDir = DIRECITON_NONE;
					_direction = DIRECITON_NONE;
				}
				if (objType == OBJECT_TYPE_WALL)
				{
					_isHalfMove = true;
					_direction = _attDir;
					_attDir = DIRECITON_NONE;
					_moveDistance = TILE_SIZE;
					_jumpPower = 150.0f;
					_gravity = GRAVETY;
				}
			}
			else
			{
				_direction = _attDir;
				_attDir = DIRECITON_NONE;
				OBJECTMANAGER->setTileIdx(this, _idxX - 1, _idxY);
				_moveDistance = TILE_SIZE;
				_jumpPower = 150.0f;
				_gravity = GRAVETY;
			}
		}
		else if (_attDir == DIRECTION_RIGHT)
		{
			parentObj* tempObj = OBJECTMANAGER->getCheckObj(_idxX + idxAdd, _idxY);

			if (tempObj != NULL)
			{
				objType = tempObj->getObjType();

				if (objType == OBJECT_TYPE_PLAYER)
				{
					attackEnemy(_attDir);
					_attDir = DIRECITON_NONE;
					_direction = DIRECITON_NONE;
				}
				if (objType == OBJECT_TYPE_WALL)
				{
					_isHalfMove = true;
					_direction = _attDir;
					_attDir = DIRECITON_NONE;
					_moveDistance = TILE_SIZE;
					_jumpPower = 150.0f;
					_gravity = GRAVETY;
				}
			}
			else
			{
				_direction = _attDir;
				_attDir = DIRECITON_NONE;
				OBJECTMANAGER->setTileIdx(this, _idxX + 1, _idxY);
				_moveDistance = TILE_SIZE;
				_jumpPower = 150.0f;
				_gravity = GRAVETY;
			}
		}
		else if (_attDir == DIRECTION_UP)
		{
			parentObj* tempObj = OBJECTMANAGER->getCheckObj(_idxX, _idxY - idxAdd);

			if (tempObj != NULL)
			{
				objType = tempObj->getObjType();

				if (objType == OBJECT_TYPE_PLAYER)
				{
					attackEnemy(_attDir);
					_attDir = DIRECITON_NONE;
					_direction = DIRECITON_NONE;
				}
				if (objType == OBJECT_TYPE_WALL)
				{
					_isHalfMove = true;
					_direction = _attDir;
					_attDir = DIRECITON_NONE;
					_moveDistance = TILE_SIZE;
					_jumpPower = 150.0f;
					_gravity = GRAVETY;
				}
			}
			else
			{
				_direction = _attDir;
				_attDir = DIRECITON_NONE;
				OBJECTMANAGER->setTileIdx(this, _idxX, _idxY - 1);
				_moveDistance = TILE_SIZE;
				_jumpPower = 150.0f;
				_gravity = GRAVETY;
			}
		}
		else if (_attDir == DIRECTION_DOWN)
		{
			parentObj* tempObj = OBJECTMANAGER->getCheckObj(_idxX, _idxY + idxAdd);

			if (tempObj != NULL)
			{
				objType = tempObj->getObjType();

				if (objType == OBJECT_TYPE_PLAYER)
				{
					attackEnemy(_attDir);
					_attDir = DIRECITON_NONE;
					_direction = DIRECITON_NONE;
				}
				if (objType == OBJECT_TYPE_WALL)
				{
					_isHalfMove = true;
					_direction = _attDir;
					_attDir = DIRECITON_NONE;
					_moveDistance = TILE_SIZE;
					_jumpPower = 150.0f;
					_gravity = GRAVETY;
				}
			}
			else
			{
				_direction = _attDir;
				_attDir = DIRECITON_NONE;
				OBJECTMANAGER->setTileIdx(this, _idxX, _idxY + 1);
				_moveDistance = TILE_SIZE;
				_jumpPower = 150.0f;
				_gravity = GRAVETY;
			}
		}


		_isBeat = false;
	}

	jumpMoveEnemy();
}

void enemy_clone::render()
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

void enemy_clone::aniSetUp()
{
	KEYANIMANAGER->addAnimationType("enemy_clone");

	int stand[] = { 0,1,2,3 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_clone", "clone_stand", "enemy_clone", stand, 4, ANISPEED, true);

	int stand_shadow[] = { 4,5,6,7 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_clone", "clone_shadow", "enemy_clone", stand_shadow, 4, ANISPEED, true);

	_ani = KEYANIMANAGER->findAnimation("enemy_clone", "clone_stand");
	_ani->start();

}

void enemy_clone::aniPlay_Stand()
{
	if (_isSaw)
	{
		//그림자이미지
		if (_isSight)
		{
			if (_hasLight)
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_clone", "clone_stand");
				_ani->start();
			}
			else
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_clone", "clone_shadow");
				_ani->start();
			}
		}
		else
		{
			_ani = KEYANIMANAGER->findAnimation("enemy_clone", "clone_shadow");
			_ani->start();
		}
	}
}

void enemy_clone::jumpMoveEnemy()
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
				_posZ -= _jumpPower * TIMEMANAGER->getElapsedTime();
				_jumpPower -= _gravity * TIMEMANAGER->getElapsedTime();
			}
			if (_moveDistance <= 0)
			{
				_direction = DIRECITON_NONE;
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
				_posZ -= _jumpPower * TIMEMANAGER->getElapsedTime();
				_jumpPower -= _gravity * TIMEMANAGER->getElapsedTime();
			}
			if (_moveDistance <= 0)
			{
				_direction = DIRECITON_NONE;
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
				_posZ += _jumpPower * TIMEMANAGER->getElapsedTime();
				_jumpPower -= _gravity * TIMEMANAGER->getElapsedTime();
			}
			if (_moveDistance <= 0)
			{
				_direction = DIRECITON_NONE;
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
				_posZ += _jumpPower * TIMEMANAGER->getElapsedTime();
				_jumpPower -= _gravity * TIMEMANAGER->getElapsedTime();
			}
			if (_moveDistance <= 0)
			{
				_direction = DIRECITON_NONE;
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
					_posZ -= _jumpPower * TIMEMANAGER->getElapsedTime();
					_jumpPower -= _gravity * TIMEMANAGER->getElapsedTime();
				}
				else
				{
					_posX += _speed;
					_posZ += _jumpPower * TIMEMANAGER->getElapsedTime();
					_jumpPower -= _gravity * TIMEMANAGER->getElapsedTime();
				}

			}
			if (_moveDistance <= 0)
			{
				_direction = DIRECITON_NONE;
				_posZ = 0;
				_jumpPower = 0;
				horizonSet();
				_isHalfMove = false;
			}

			break;
		case DIRECTION_RIGHT:
			_moveDistance -= _speed;
			if (_moveDistance)
			{
				if (_moveDistance > TILE_SIZE / 2)
				{
					_posX += _speed;
					_posZ -= _jumpPower * TIMEMANAGER->getElapsedTime();
					_jumpPower -= _gravity * TIMEMANAGER->getElapsedTime();
				}
				else
				{
					_posX -= _speed;
					_posZ += _jumpPower * TIMEMANAGER->getElapsedTime();
					_jumpPower -= _gravity * TIMEMANAGER->getElapsedTime();
				}
			}
			if (_moveDistance <= 0)
			{
				_direction = DIRECITON_NONE;
				_posZ = 0;
				_jumpPower = 0;
				horizonSet();
				_isHalfMove = false;
			}
			break;
		case DIRECTION_UP:
			_moveDistance -= _speed;
			if (_moveDistance)
			{
				if (_moveDistance > TILE_SIZE / 2)
				{
					_posY -= _speed;
					_posZ -= _jumpPower * TIMEMANAGER->getElapsedTime();
					_jumpPower -= _gravity * TIMEMANAGER->getElapsedTime();
				}
				else
				{
					_posY += _speed;
					_posZ += _jumpPower * TIMEMANAGER->getElapsedTime();
					_jumpPower -= _gravity * TIMEMANAGER->getElapsedTime();
				}
			}
			if (_moveDistance <= 0)
			{
				_direction = DIRECITON_NONE;
				_posZ = 0;
				_jumpPower = 0;
				verticalSet();
				_isHalfMove = false;
			}

			break;
		case DIRECTION_DOWN:
			_moveDistance -= _speed;
			if (_moveDistance)
			{
				if (_moveDistance > TILE_SIZE / 2)
				{
					_posY += _speed;
					_posZ += _jumpPower * TIMEMANAGER->getElapsedTime();
					_jumpPower -= _gravity * TIMEMANAGER->getElapsedTime();
				}
				else
				{
					_posY -= _speed;
					_posZ -= _jumpPower * TIMEMANAGER->getElapsedTime();
					_jumpPower -= _gravity * TIMEMANAGER->getElapsedTime();
				}
			}
			if (_moveDistance <= 0)
			{
				_direction = DIRECITON_NONE;
				_posZ = 0;
				_jumpPower = 0;
				verticalSet();
				_isHalfMove = false;
			}
			break;
		}
	}
}