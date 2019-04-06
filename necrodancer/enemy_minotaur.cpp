#include "stdafx.h"
#include "enemy_minotaur.h"


enemy_minotaur::enemy_minotaur()
{
}


enemy_minotaur::~enemy_minotaur()
{
}

HRESULT enemy_minotaur::init(string imgName, int idxX, int idxY)
{
	enemy::init(imgName, idxX, idxY);
	_moveBeat = 1;
	_subX = 50;
	_subY = 72;
	_damage = 4;
	_heart = 3;
	_maxHeart = 3;
	_count = 0;

	_isLeft = true;

	aniSetUp();


	return S_OK;
}

void enemy_minotaur::release()
{
}

void enemy_minotaur::update()
{
	jumpMoveEnemy();

	if (_minoState == MINOTAUR_STATE_STUN)
		stun();

	if (_isBeat)
	{
		_curMoveBeat++;
		if (_moveBeat == _curMoveBeat)
		{
			_curMoveBeat = 0;

			switch (_minoState)
			{
			case MINOTAUR_STATE_IDLE:
				aniPlay_Stand();
				if (aStarLoad())
					searchTarget();
				break;
			case MINOTAUR_STATE_RUN:
				aniPlay_Run();
				run();
				break;
			case MINOTAUR_STATE_STUN:
				aniPlay_Stun();
				break;
			}
		}

		_isBeat = false;
	}

}

void enemy_minotaur::render()
{
	if (_isSaw)
	{
		IMAGEMANAGER->findImage("enemy_shadow")->render(_posX - 24, _posY - 26 + _posZ);
		if (!_isLeft)
			_img->aniRenderReverseX(_posX - _subX, _posY - _subY + _posZ, _ani);
		else
			_img->aniRender(_posX - _subX, _posY - _subY + _posZ, _ani);
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
	player* tempPlayer = OBJECTMANAGER->getPlayer();

	//WCHAR str[128];

	//swprintf_s(str, L"%d / %d", tempPlayer->getIdxX(), tempPlayer->getIdxY());
	D2DMANAGER->drawRectangle(RGB(255, 0, 255), tempPlayer->getIdxX() * 52, tempPlayer->getIdxY() * 52, tempPlayer->getIdxX() * 52 + 52, tempPlayer->getIdxY() * 52 + 52);
	D2DMANAGER->drawRectangle(RGB(255, 255, 0), tempPlayer->getPlayerPosX(), tempPlayer->getPlayerPosY(), tempPlayer->getPlayerPosX() + 52, tempPlayer->getPlayerPosY() + 52);

	D2DMANAGER->drawRectangle(0xff00ff, _posX - 26, _posY - 26, _posX + 52 - 26, _posY + 52 -26);
	D2DMANAGER->drawRectangle(0x0000ff, _idxX * 52, _idxY * 52, _idxX * 52 + 52, _idxY * 52 + 52);
}

void enemy_minotaur::aniSetUp()
{
	KEYANIMANAGER->addAnimationType("enemy_minotaur");

	int stand[] = { 0,1,2,3 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_minotaur", "minotaur_stand", "enemy_minotaur", stand, 4, ANISPEED, true);

	int run[] = { 4 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_minotaur", "minotaur_run", "enemy_minotaur", run, 1, ANISPEED, true);

	int stun[] = { 5,6,7,8 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_minotaur", "minotaur_stun", "enemy_minotaur", stun, 4, ANISPEED, false);

	int stand_shadow[] = { 9,10,11,12 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_minotaur", "minotaur_stand_shadow", "enemy_minotaur", stand_shadow, 4, ANISPEED, true);

	int run_shadow[] = { 13 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_minotaur", "minotaur_run_shadow", "enemy_minotaur", run_shadow, 1, ANISPEED, true);

	int stun_shadow[] = { 14,15,16,17 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_minotaur", "minotaur_stun_shadow", "enemy_minotaur", stun_shadow, 4, ANISPEED, false);

	_ani = KEYANIMANAGER->findAnimation("enemy_minotaur", "minotaur_stand");
	_ani->start();
}

void enemy_minotaur::aniPlay_Stand()
{
	if (_isSaw)
	{
		//그림자이미지
		if (_isSight)
		{
			if (_hasLight)
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_minotaur", "minotaur_stand");
				_ani->start();
			}
			else
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_minotaur", "minotaur_stand_shadow");
				_ani->start();
			}
		}
		else
		{
			_ani = KEYANIMANAGER->findAnimation("enemy_minotaur", "minotaur_stand_shadow");
			_ani->start();
		}
	}
}

void enemy_minotaur::aniPlay_Run()
{
	if (_isSaw)
	{
		//그림자이미지
		if (_isSight)
		{
			if (_hasLight)
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_minotaur", "minotaur_run");
				_ani->start();
			}
			else
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_minotaur", "minotaur_run_shadow");
				_ani->start();
			}
		}
		else
		{
			_ani = KEYANIMANAGER->findAnimation("enemy_minotaur", "minotaur_run_shadow");
			_ani->start();
		}
	}
}

void enemy_minotaur::aniPlay_Stun()
{
	if (_isSaw)
	{
		//그림자이미지
		if (_isSight)
		{
			if (_hasLight)
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_minotaur", "minotaur_stun");
				_ani->start();
			}
			else
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_minotaur", "minotaur_stun_shadow");
				_ani->start();
			}
		}
		else
		{
			_ani = KEYANIMANAGER->findAnimation("enemy_minotaur", "minotaur_stun_shadow");
			_ani->start();
		}
	}
}

bool enemy_minotaur::searchTarget()
{
	player* tempPlayer = OBJECTMANAGER->getPlayer();
	int playerIdxX = tempPlayer->getIdxX();
	int playerIdxY = tempPlayer->getIdxY();
	
	if (playerIdxX == _idxX)
	{
		SOUNDMANAGER->play("sound_minotaur_charge");
		_minoState = MINOTAUR_STATE_RUN;
		if (playerIdxY < _idxY)
		{
			_direction = DIRECTION_UP;
		}
		else if(playerIdxY > _idxY)
		{
			_direction = DIRECTION_DOWN;
		}
		return true;
	}
	else if (playerIdxY == _idxY)
	{
		_minoState = MINOTAUR_STATE_RUN;
		if (playerIdxX < _idxX)
		{
			_direction = DIRECTION_LEFT;
			_isLeft = true;
		}
		else if (playerIdxX > _idxX)
		{
			_direction = DIRECTION_RIGHT;
			_isLeft = false;
		}
		return true;
	}
	return false;
}

void enemy_minotaur::run()
{
	player* tempPlayer = OBJECTMANAGER->getPlayer();

	if (_direction == DIRECTION_LEFT)
	{
		parentObj* tempObj = OBJECTMANAGER->getCheckObj(_idxX - 1, _idxY);

		if (tempObj == NULL)
		{
			//_moveDistance = TILE_SIZE;
			OBJECTMANAGER->setTileIdx(this, _idxX - 1, _idxY);
		}
		else
		{
			if (tempObj->getObjType() == OBJECT_TYPE_WALL)
			{
				if(tempObj->wallBroken(2))
				{
					SOUNDMANAGER->play("sound_minotaur_wallimpact");
					OBJECTMANAGER->deleteObject(tempObj);
				}
			}
			else if (tempObj->getObjType() == OBJECT_TYPE_PLAYER)
			{
				SOUNDMANAGER->play("sound_minotaur_attack");
				attackEnemy(_direction);
			}

			aniPlay_Stun();
			_minoState = MINOTAUR_STATE_STUN;
		}
	}
	else if (_direction == DIRECTION_RIGHT)
	{
		parentObj* tempObj = OBJECTMANAGER->getCheckObj(_idxX + 1, _idxY);

		if (tempObj == NULL)
		{
			_moveDistance = TILE_SIZE;
			OBJECTMANAGER->setTileIdx(this, _idxX + 1, _idxY);
		}
		else
		{
			if (tempObj->getObjType() == OBJECT_TYPE_WALL)
			{
				if (tempObj->wallBroken(2))
				{
					SOUNDMANAGER->play("sound_minotaur_wallimpact");
					OBJECTMANAGER->deleteObject(tempObj);
				}
			}
			else if (tempObj->getObjType() == OBJECT_TYPE_PLAYER)
			{
				SOUNDMANAGER->play("sound_minotaur_attack");
				attackEnemy(_direction);
			}

			aniPlay_Stun();
			_minoState = MINOTAUR_STATE_STUN;
		}
	}
	else if (_direction == DIRECTION_UP)
	{
		parentObj* tempObj = OBJECTMANAGER->getCheckObj(_idxX, _idxY - 1);

		if (tempObj == NULL)
		{
			_moveDistance = TILE_SIZE;
			OBJECTMANAGER->setTileIdx(this, _idxX, _idxY - 1);
		}
		else
		{
			if (tempObj->getObjType() == OBJECT_TYPE_WALL)
			{
				if (tempObj->wallBroken(2))
				{
					SOUNDMANAGER->play("sound_minotaur_wallimpact");
					OBJECTMANAGER->deleteObject(tempObj);
				}
			}
			else if (tempObj->getObjType() == OBJECT_TYPE_PLAYER)
			{
				SOUNDMANAGER->play("sound_minotaur_attack");
				attackEnemy(_direction);
			}

			aniPlay_Stun();
			_minoState = MINOTAUR_STATE_STUN;
		}
	}
	else if (_direction == DIRECTION_DOWN)
	{
		parentObj* tempObj = OBJECTMANAGER->getCheckObj(_idxX, _idxY + 1);

		if (tempObj == NULL)
		{
			_moveDistance = TILE_SIZE;
			OBJECTMANAGER->setTileIdx(this, _idxX, _idxY + 1);
		}
		else
		{
			if (tempObj->getObjType() == OBJECT_TYPE_WALL)
			{
				if (tempObj->wallBroken(2))
				{
					SOUNDMANAGER->play("sound_minotaur_wallimpact");
					OBJECTMANAGER->deleteObject(tempObj);
				}
			}
			else if (tempObj->getObjType() == OBJECT_TYPE_PLAYER)
			{
				SOUNDMANAGER->play("sound_minotaur_attack");
				attackEnemy(_direction);
			}

			aniPlay_Stun();
			_minoState = MINOTAUR_STATE_STUN;
		}
	}
	

}

void enemy_minotaur::stun()
{
	_count++;
	if (_count >= 3)
	{
		_minoState = MINOTAUR_STATE_IDLE;
		_count = 0;
	}
}

void enemy_minotaur::jumpMoveEnemy()
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
				//_direction = DIRECITON_NONE;
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
				//_direction = DIRECITON_NONE;
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
				//_direction = DIRECITON_NONE;
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
				//_direction = DIRECITON_NONE;
				_posZ = 0;
				_jumpPower = 0;
				verticalSet();
				_isHalfMove = false;
			}
			break;
		}
	}
}
