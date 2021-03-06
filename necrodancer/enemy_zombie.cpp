#include "stdafx.h"
#include "enemy_zombie.h"


enemy_zombie::enemy_zombie()
{
}


enemy_zombie::~enemy_zombie()
{
}

HRESULT enemy_zombie::init(string imgName, int idxX, int idxY)
{
	enemy::init(imgName, idxX, idxY);

	_moveBeat = 2;
	_subX = 26;
	_subY = 36;
	_damage = 1;
	_heart = 1;
	_maxHeart = 1;

	
	////_direction = ;
	
	_tempDir = (DIRECTION)RND->getFromIntTo(1, 4);
	if (_tempDir == DIRECTION_LEFT) _isLeft = true;
	else if (_tempDir == DIRECTION_RIGHT) _isLeft = false;

	aniSetUp();

	return S_OK;
}

void enemy_zombie::release()
{
}

void enemy_zombie::update()
{
	player* tempPlayer = OBJECTMANAGER->getPlayer();
	jumpMoveEnemy();

	if (_isBeat)
	{
		_direction = _tempDir;
		_curMoveBeat++;
		//_direction = _tempDir;
		if (_moveBeat == _curMoveBeat)
		{
			_curMoveBeat = 0;
			//_moveDistance = TILE_SIZE;

			OBJECT_TYPE objType;
			
			if (_direction == DIRECTION_LEFT)
			{
				parentObj* tempObj = OBJECTMANAGER->getCheckObj(_idxX - 1, _idxY);
				_isLeft = true;
				if (tempObj != NULL)
				{
					objType = tempObj->getObjType();

					if (objType == OBJECT_TYPE_PLAYER)
					{
						attackEnemy(_direction);
						EFFECTMANAGER->play("enemy_attack", tempPlayer->getPlayerPosX(), tempPlayer->getPlayerPosY());
					}
					else if (objType == OBJECT_TYPE_WALL)
					{
						_tempDir = DIRECTION_RIGHT;
						_isLeft = false;
						_isHalfMove = true;
						_moveDistance = TILE_SIZE;
						aniPlay_Side();

					}
					else
					{
						_moveDistance = TILE_SIZE;
						OBJECTMANAGER->setTileIdx(this, _idxX - 1, _idxY);
					}
					return;
				}
				OBJECTMANAGER->setTileIdx(this, _idxX - 1, _idxY);
			}
			else if (_direction == DIRECTION_RIGHT)
			{
				parentObj* tempObj = OBJECTMANAGER->getCheckObj(_idxX + 1, _idxY);
				_isLeft = false;
				if (tempObj != NULL)
				{
					objType = tempObj->getObjType();

					if (objType == OBJECT_TYPE_PLAYER)
					{
						attackEnemy(_direction);
						EFFECTMANAGER->play("enemy_attack", tempPlayer->getPlayerPosX(), tempPlayer->getPlayerPosY());
					}
					else if (objType == OBJECT_TYPE_WALL)
					{
						_tempDir = DIRECTION_LEFT;
						_isLeft = true;
						_isHalfMove = true;
						_moveDistance = TILE_SIZE;
						aniPlay_Side();

					}
					else
					{
						_moveDistance = TILE_SIZE;
						OBJECTMANAGER->setTileIdx(this, _idxX + 1, _idxY);
					}
					return;
				}
				OBJECTMANAGER->setTileIdx(this, _idxX + 1, _idxY);

			}
			else if (_direction == DIRECTION_UP)
			{
				parentObj* tempObj = OBJECTMANAGER->getCheckObj(_idxX, _idxY - 1);
				if (tempObj != NULL)
				{
					objType = tempObj->getObjType();

					if (objType == OBJECT_TYPE_PLAYER)
					{
						attackEnemy(_direction);
						EFFECTMANAGER->play("enemy_attack", tempPlayer->getPlayerPosX(), tempPlayer->getPlayerPosY());
					}
					else if (objType == OBJECT_TYPE_WALL)
					{
						_tempDir = DIRECTION_DOWN;
						_isHalfMove = true;
						_moveDistance = TILE_SIZE;
						aniPlay_Down();

					}
					else
					{
						_moveDistance = TILE_SIZE;
						OBJECTMANAGER->setTileIdx(this, _idxX, _idxY - 1);
					}
					return;
				}
				OBJECTMANAGER->setTileIdx(this, _idxX, _idxY - 1);
			}
			else if (_direction == DIRECTION_DOWN)
			{
				parentObj* tempObj = OBJECTMANAGER->getCheckObj(_idxX, _idxY + 1);
				if (tempObj != NULL)
				{
					objType = tempObj->getObjType();

					if (objType == OBJECT_TYPE_PLAYER)
					{
						attackEnemy(_direction);
						EFFECTMANAGER->play("enemy_attack", tempPlayer->getPlayerPosX(), tempPlayer->getPlayerPosY());
					}
					else if (objType == OBJECT_TYPE_WALL)
					{
						_tempDir = DIRECTION_UP;
						_isHalfMove = true;
						_moveDistance = TILE_SIZE;
						aniPlay_Up();

					}
					else
					{
						_moveDistance = TILE_SIZE;
						OBJECTMANAGER->setTileIdx(this, _idxX, _idxY + 1);
					}
					return;
				}
				OBJECTMANAGER->setTileIdx(this, _idxX, _idxY + 1);
			}
			
			
		}
		_isBeat = false;
	}

}

void enemy_zombie::render()
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
			IMAGEMANAGER->findImage("enemy_heart_empty")->render((_posX + 5) - (_maxHeart / 2) * 24 + 24 * i - 7, _posY - _subY - 24);
		}
		for (int i = 0; i < _heart; i++)
		{
			IMAGEMANAGER->findImage("enemy_heart")->render((_posX + 5) - (_maxHeart / 2) * 24 + 24 * i - 7, _posY - _subY - 24);
		}
	}
}

void enemy_zombie::aniSetUp()
{
	KEYANIMANAGER->addAnimationType("enemy_zombie");

	int up[] = { 0,1,2,3,4,5,6,7 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_zombie", "zombie_up", "enemy_zombie", up, 8, ANISPEED, true);

	int side[] = { 8,9,10,11,12,13,14,15 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_zombie", "zombie_side", "enemy_zombie", side, 8, ANISPEED, true);

	int down[] = { 16,17,18,19,20,21,22,23 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_zombie", "zombie_down", "enemy_zombie", down, 8, ANISPEED, true);

	int up_shadow[] = { 24,25,26,27,28,29,30,31 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_zombie", "zombie_up_shadow", "enemy_zombie", up_shadow, 8, ANISPEED, true);

	int side_shadow[] = { 32,33,34,35,36,37,38,39 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_zombie", "zombie_side_shadow", "enemy_zombie", side_shadow, 8, ANISPEED, true);

	int down_shadow[] = { 40,41,42,43,44,45,46,47 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_zombie", "zombie_down_shadow", "enemy_zombie", down_shadow, 8, ANISPEED, true);

	/*if (_direction == DIRECTION_LEFT || _direction == DIRECTION_RIGHT)
	{
		_ani = KEYANIMANAGER->findAnimation("enemy_zombie", "zombie_side");
		_ani->start();
	}
	else if (_direction == DIRECTION_UP)
	{
		_ani = KEYANIMANAGER->findAnimation("enemy_zombie", "zombie_up");
		_ani->start();
	}
	else if (_direction == DIRECTION_DOWN)
	{
		_ani = KEYANIMANAGER->findAnimation("enemy_zombie", "zombie_down");
		_ani->start();
	}*/

	if (_tempDir == DIRECTION_LEFT || _tempDir == DIRECTION_RIGHT)
	{
		_ani = KEYANIMANAGER->findAnimation("enemy_zombie", "zombie_side");
		_ani->start();
	}
	else if (_tempDir == DIRECTION_UP)
	{
		_ani = KEYANIMANAGER->findAnimation("enemy_zombie", "zombie_up");
		_ani->start();
	}
	else if (_tempDir == DIRECTION_DOWN)
	{
		_ani = KEYANIMANAGER->findAnimation("enemy_zombie", "zombie_down");
		_ani->start();
	}
}

void enemy_zombie::aniPlay_Up()
{
	if (_isSaw)
	{
		//그림자이미지
		if (_isSight)
		{
			if (_hasLight)
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_zombie", "zombie_up");
				_ani->start();
			}
			else
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_zombie", "zombie_up_shadow");
				_ani->start();
			}
		}
		else
		{
			_ani = KEYANIMANAGER->findAnimation("enemy_zombie", "zombie_up_shadow");
			_ani->start();
		}
	}
}

void enemy_zombie::aniPlay_Down()
{
	if (_isSaw)
	{
		//그림자이미지
		if (_isSight)
		{
			if (_hasLight)
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_zombie", "zombie_down");
				_ani->start();
			}
			else
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_zombie", "zombie_down_shadow");
				_ani->start();
			}
		}
		else
		{
			_ani = KEYANIMANAGER->findAnimation("enemy_zombie", "zombie_down_shadow");
			_ani->start();
		}
	}
}

void enemy_zombie::aniPlay_Side()
{
	if (_isSaw)
	{
		//그림자이미지
		if (_isSight)
		{
			if (_hasLight)
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_zombie", "zombie_side");
				_ani->start();
			}
			else
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_zombie", "zombie_side_shadow");
				_ani->start();
			}
		}
		else
		{
			_ani = KEYANIMANAGER->findAnimation("enemy_zombie", "zombie_side_shadow");
			_ani->start();
		}
	}
}

void enemy_zombie::jumpMoveEnemy()
{
	//_speed = TIMEMANAGER->getElapsedTime() * PLAYER_SPEED;
	_speed = 8.0f;

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
				
				_posZ = 0;
				_jumpPower = 0;
				verticalSet();
				_isHalfMove = false;
			}
			break;
		}
	}
}
