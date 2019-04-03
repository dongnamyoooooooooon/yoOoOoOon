#include "stdafx.h"
#include "enemy_skeleton_yellow.h"


enemy_skeleton_yellow::enemy_skeleton_yellow()
{
}


enemy_skeleton_yellow::~enemy_skeleton_yellow()
{
}

HRESULT enemy_skeleton_yellow::init(string imgName, int idxX, int idxY)
{
	enemy::init(imgName, idxX, idxY);

	_moveBeat = 2;
	_subX = 26;
	_subY = 36;
	_damage = 3;
	_heart = 2;
	_maxHeart = 2;

	_isHeartOne = false;

	aniSetUp();

	return S_OK;
}

void enemy_skeleton_yellow::release()
{
}

void enemy_skeleton_yellow::update()
{
	jumpMoveEnemy();

	if (_isBeat)
	{
		_curMoveBeat++;
		if (!_isHeartOne)
		{
			if (_curMoveBeat == 1)
			{
				aniPlay_Attack();
			}
			if (_moveBeat == _curMoveBeat)
			{
				_curMoveBeat = 0;
				aniPlay_Stand();
				aStarLoad();
			}
		}
		else
		{
			aniPlay_NoHead();
			patternMove();

		}
		_isBeat = false;
	}
}

void enemy_skeleton_yellow::render()
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

void enemy_skeleton_yellow::aniSetUp()
{
	KEYANIMANAGER->addAnimationType("enemy_skeleton_yellow");

	int stand[] = { 0,1,2,3 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_skeleton_yellow", "skeleton_yellow_stand", "enemy_skeleton_yellow", stand, 4, ANISPEED, true);

	int attack[] = { 4,5,6,7 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_skeleton_yellow", "skeleton_yellow_attack", "enemy_skeleton_yellow", attack, 4, ANISPEED, false);

	int noHead[] = { 8 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_skeleton_yellow", "skeleton_yellow_noHead", "enemy_skeleton_yellow", noHead, 1, ANISPEED, true);

	int stand_shadow[] = { 9,10,11,12 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_skeleton_yellow", "skeleton_yellow_stand_shadow", "enemy_skeleton_yellow", stand_shadow, 4, ANISPEED, true);

	int attack_shadow[] = { 13,14,15,16 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_skeleton_yellow", "skeleton_yellow_attack_shadow", "enemy_skeleton_yellow", attack_shadow, 4, ANISPEED, false);

	int noHead_shadow[] = { 17 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_skeleton_yellow", "skeleton_yellow_noHead_shadow", "enemy_skeleton_yellow", noHead_shadow, 1, ANISPEED, true);

	_ani = KEYANIMANAGER->findAnimation("enemy_skeleton_yellow", "skeleton_yellow_stand");
	_ani->start();
}

void enemy_skeleton_yellow::aniPlay_Attack()
{
	if (_isSaw)
	{
		//그림자이미지
		if (_isSight)
		{
			if (_hasLight)
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_skeleton_yellow", "skeleton_yellow_attack");
				_ani->start();
			}
			else
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_skeleton_yellow", "skeleton_yellow_attack_shadow");
				_ani->start();
			}
		}
		else
		{
			_ani = KEYANIMANAGER->findAnimation("enemy_skeleton_yellow", "skeleton_yellow_attack_shadow");
			_ani->start();
		}
	}
}

void enemy_skeleton_yellow::aniPlay_Stand()
{
	if (_isSaw)
	{
		//그림자이미지
		if (_isSight)
		{
			if (_hasLight)
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_skeleton_yellow", "skeleton_yellow_stand");
				_ani->start();
			}
			else
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_skeleton_yellow", "skeleton_yellow_stand_shadow");
				_ani->start();
			}
		}
		else
		{
			_ani = KEYANIMANAGER->findAnimation("enemy_skeleton_yellow", "skeleton_yellow_stand_shadow");
			_ani->start();
		}
	}
}

void enemy_skeleton_yellow::aniPlay_NoHead()
{
	if (_isSaw)
	{
		//그림자이미지
		if (_isSight)
		{
			if (_hasLight)
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_skeleton_yellow", "skeleton_yellow_noHead");
				_ani->start();
			}
			else
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_skeleton_yellow", "skeleton_yellow_noHead_shadow");
				_ani->start();
			}
		}
		else
		{
			_ani = KEYANIMANAGER->findAnimation("enemy_skeleton_yellow", "skeleton_yellow_noHead_shadow");
			_ani->start();
		}
	}
}

void enemy_skeleton_yellow::hitEnemy(int damage)
{
	_isDrawHP = true;
	_heart -= damage;

	if (_heart <= 0) this->dieEnemy();
	else if (_heart == 1)
	{
		_isHeartOne = true;
		int random = RND->getFromIntTo(1, 3);
		{
			switch (random)
			{
			case 1:
				SOUNDMANAGER->play("sound_skel_head_loss_01");
				break;
			case 2:
				SOUNDMANAGER->play("sound_skel_head_loss_02");
				break;
			case 3:
				SOUNDMANAGER->play("sound_skel_head_loss_03");
				break;
			}
		}

		player* tempPlayer = OBJECTMANAGER->getPlayer();

		int playerX = tempPlayer->getPlayerPosX();
		int playerY = tempPlayer->getPlayerPosY();

		int tempX = playerX - _posX;
		int tempY = playerY - _posY;

		if (tempX == -52 && tempY == 0)
		{
			_skelDir = DIRECTION_RIGHT;
		}
		else if (tempX == 0 && tempY == -52)
		{
			_skelDir = DIRECTION_DOWN;
		}
		else if (tempX == 52 && tempY == 0)
		{
			_skelDir = DIRECTION_LEFT;
		}
		else if (tempX == 0 && tempY == 52)
		{
			_skelDir = DIRECTION_UP;
		}
		_moveBeat = 1;
		_curMoveBeat = 1;
	}
}

void enemy_skeleton_yellow::patternMove()
{
	_moveDistance = TILE_SIZE;
	_direction = _skelDir;

	if (_skelDir == DIRECTION_LEFT) _isLeft = true;
	else _isLeft = false;
	
	OBJECT_TYPE objType;
	if (_direction == DIRECTION_LEFT)
	{
		parentObj* tempObj = OBJECTMANAGER->getCheckObj(_idxX - 1, _idxY);
		if (tempObj != NULL)
		{
			objType = tempObj->getObjType();

			if (objType == OBJECT_TYPE_PLAYER)
			{
				attackEnemy(_direction);
			}
			else if (objType == OBJECT_TYPE_WALL)
			{
				_isHalfMove = true;
				_moveDistance = TILE_SIZE;
				
			}
			else
			{
				_direction = _skelDir;
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
		if (tempObj != NULL)
		{
			objType = tempObj->getObjType();

			if (objType == OBJECT_TYPE_PLAYER)
			{
				attackEnemy(_direction);
			}
			else if (objType == OBJECT_TYPE_WALL)
			{
				_isHalfMove = true;
				_moveDistance = TILE_SIZE;
			}
			else
			{
				_direction = _skelDir;
				_moveDistance = TILE_SIZE;
				OBJECTMANAGER->setTileIdx(this, _idxX + 1, _idxY);
			}
			return;
		}
		OBJECTMANAGER->setTileIdx(this, _idxX + 1, _idxY);
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
			}
			else if (objType == OBJECT_TYPE_WALL)
			{
				_isHalfMove = true;
				_moveDistance = TILE_SIZE;
			}
			else
			{
				_direction = _skelDir;
				_moveDistance = TILE_SIZE;
				OBJECTMANAGER->setTileIdx(this, _idxX, _idxY + 1);
			}
			return;
		}
		OBJECTMANAGER->setTileIdx(this, _idxX, _idxY + 1);
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
			}
			else if (objType == OBJECT_TYPE_WALL)
			{
				_isHalfMove = true;
				_moveDistance = TILE_SIZE;
			}
			else
			{
				_direction = _skelDir;
				_moveDistance = TILE_SIZE;
				OBJECTMANAGER->setTileIdx(this, _idxX, _idxY - 1);
			}
			return;
		}
		OBJECTMANAGER->setTileIdx(this, _idxX, _idxY - 1);
	}

}
