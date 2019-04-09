#include "stdafx.h"
#include "enemy_coralriff_head.h"


enemy_coralriff_head::enemy_coralriff_head()
{
}


enemy_coralriff_head::~enemy_coralriff_head()
{
}

HRESULT enemy_coralriff_head::init(string imgName, int idxX, int idxY)
{
	enemy::init(imgName, idxX, idxY);

	_subX = 42;
	_subY = 98;
	_damage = 3;
	_heart = 3;
	_maxHeart = 3;
	_moveBeat = 9999;

	aniSetUp();

	_isSaw = true;
	_hasLight = true;
	_isSight = true;

	_isPlayerIn = false;

	_frameX = 0;

	return S_OK;
}

void enemy_coralriff_head::release()
{
}

void enemy_coralriff_head::update()
{
	KEYANIMANAGER->update("boss_attack");

	if(!OBJECTMANAGER->getIsEnter())
		createWall();

	moveEnemy();

	if (OBJECTMANAGER->getIsEnter())
	{
		if (_isBeat)
		{
			_isBeat = false;
			_beatCount++;
			if (_beatCount >= 53 || _heart != _maxHeart)
			{
				OBJECTMANAGER->setBossHit(true);
				_curMoveBeat++;
				_shakeVal = 3;
				SOUNDMANAGER->setBossVolume("boss", 1.0f);
				OBJECTMANAGER->setTileFloor(_posX / TILE_SIZE, _posY / TILE_SIZE);
				if (_curMoveBeat == 2)
				{
					aStarLoad();
					setFrame();
					_shakeVal = 0;
					if (_beatCount >= 1000) _beatCount = 54;
					_curMoveBeat = 0;
				}
			}
		}
		if (_shakeVal != 0)
		{
			if (_heart <= 0)
			{
				_shakeVal = 0;
			}
			else
			{
				_shakeCount++;
				if (_shakeCount >= 3)
				{
					_shakeCount = 0;
					_shakeVal == 3 ? _shakeVal = -3 : _shakeVal = 3;
				}
			}
		}
	}
}

void enemy_coralriff_head::render()
{
	if (_heart > 0)
	{
		if (_beatCount >= 53 || _heart != _maxHeart)
		{
			if (_shakeVal == 0)
				IMAGEMANAGER->findImage("boss_attack")->aniRender(_posX - _subX - 25, _posY - _subY, _attackAni);
		}
		if (_isSaw)
		{
			//IMAGEMANAGER->findImage("enemy_shadow")->render(_posX - 24, _posY - 26 + _posZ);
			if (!_isLeft)
				_img->aniRenderReverseX(_posX - _subX + _shakeVal, _posY - _subY + _posZ, _ani);
			else
				_img->aniRender(_posX - _subX + _shakeVal, _posY - _subY + _posZ, _ani);
		}
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

void enemy_coralriff_head::aniSetUp()
{
	KEYANIMANAGER->addAnimationType("enemy_coralriff_head");
	KEYANIMANAGER->addAnimationType("boss_attack");

	int attack[] = { 0,1,2,3,4 };
	KEYANIMANAGER->addArrayFrameAnimation("boss_attack", "boss_attack", "boss_attack", attack, 5, ANISPEED, false);

	int stand[] = { 0,1,2,3 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_coralriff_head", "coralriff_head_stand", "enemy_coralriff_head", stand, 4, ANISPEED, true);

	int stand_shadow[] = { 4,5,6,7 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_coralriff_head", "coralriff_head_stand_shadow", "enemy_coralriff_head", stand, 4, ANISPEED, true);

	_ani = KEYANIMANAGER->findAnimation("enemy_coralriff_head", "coralriff_head_stand");
	_ani->start();

	_attackAni = KEYANIMANAGER->findAnimation("boss_attack", "boss_attack");
	//_attackAni->start();
}

void enemy_coralriff_head::aniPlay_Stand()
{
	if (_isSaw)
	{
		//그림자이미지
		if (_isSight)
		{
			if (_hasLight)
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_coralriff_head", "coralriff_head_stand");
				_ani->start();
			}
			else
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_coralriff_head", "coralriff_head_stand_shadow");
				_ani->start();
			}
		}
		else
		{
			_ani = KEYANIMANAGER->findAnimation("enemy_coralriff_head", "coralriff_head_stand_shadow");
			_ani->start();
		}
	}
}

bool enemy_coralriff_head::aStarLoad()
{
	player* _player = OBJECTMANAGER->getPlayer();

	int direction_X = _player->getIdxX() - _idxX;
	int direction_Y = _player->getIdxY() - _idxY;

	if ((direction_X == -1 && direction_Y == 0) || (direction_X == 0 && direction_Y == -1)
		|| (direction_X == 1 && direction_Y == 0) || (direction_X == 0 && direction_Y == 1) 
		|| (direction_X == -1 && direction_Y == -1) || (direction_X == 1 && direction_Y == 1)
		|| (direction_X == -1 && direction_Y == 1) || (direction_X == 1 && direction_Y == -1))
	{

		attackEnemy(_direction);
		return true;
	}

	_startPoint = false;
	_endPoint = false;

	for (int i = 0; i < _tileY; i++)
	{
		for (int j = 0; j < _tileX; j++)
		{
			_vvTile[i][j].moveWay = TILE_MOVE_WAY_NONE;
			_vvTile[i][j].parent = NULL;
			_vvTile[i][j].F = 5000;
			_vvTile[i][j].H = 0;
			_vvTile[i][j].i = i;
			_vvTile[i][j].j = j;
		}
	}

	_closeList.clear();
	_openList.clear();
	initTile();

	while (true)
	{
		if (_aStarState == ASTAR_STATE_FOUND)
		{
			int i;
			int j;

			aStarTile* tile = _closeList[_lastIndex];

			while (true)
			{
				tile = tile->parent;
				if (tile->parent == NULL || tile->parent->parent == NULL)	break;
			}
			parentObj* tempObj;
			int nextIdx = tile->i * _tileX + tile->j;
			int nextIdxX = nextIdx % _tileX;
			int nextIdxY = nextIdx / _tileX;
			tempObj = OBJECTMANAGER->getCheckObj(nextIdxX, nextIdxY);

			if (tempObj == NULL || tempObj->getObjType() == OBJECT_TYPE_NONE)
			{
				direction_X = nextIdxX - _idxX;
				direction_Y = nextIdxY - _idxY;

				if (direction_X == -1)
				{
					direction_X = DIRECTION_LEFT;
					this->_direction = (DIRECTION)direction_X;
					_isLeft = true;
					_moveDistance = TILE_SIZE;
					_posZ = 0;
					_jumpPower = 7.0f;
					OBJECTMANAGER->setTileIdx(this, _idxX - 1, _idxY);
				}
				else if (direction_X == 1)
				{
					direction_X = DIRECTION_RIGHT;
					this->_direction = (DIRECTION)direction_X;
					_isLeft = false;
					_moveDistance = TILE_SIZE;
					_posZ = 0;
					_jumpPower = 7.0f;
					OBJECTMANAGER->setTileIdx(this, _idxX + 1, _idxY);
				}
				else if (direction_Y == -1)
				{
					direction_Y = DIRECTION_UP;
					this->_direction = (DIRECTION)direction_Y;
					_moveDistance = TILE_SIZE;
					_posZ = 0;
					_jumpPower = 3.0f;
					OBJECTMANAGER->setTileIdx(this, _idxX, _idxY - 1);
				}
				else if (direction_Y == 1)
				{
					direction_Y = DIRECTION_DOWN;
					this->_direction = (DIRECTION)direction_Y;
					_moveDistance = TILE_SIZE;
					_posZ = 0;
					_jumpPower = 3.0f;
					OBJECTMANAGER->setTileIdx(this, _idxX, _idxY + 1);
				}

			}
			else if (tempObj->getObjType() == OBJECT_TYPE_ENEMY)
			{
				if (tempObj->getImgName() != IMAGE_NAME[IMAGE_NAME_ENEMY_BANSHEE])
				{
					direction_X = nextIdxX - _idxX;
					direction_Y = nextIdxY - _idxY;
					if (direction_X == -1)
					{
						direction_X = DIRECTION_LEFT;
						this->_direction = (DIRECTION)direction_X;
						_isLeft = true;
						OBJECTMANAGER->setTileIdx(this, _idxX - 1, _idxY);
					}
					else if (direction_X == 1)
					{
						direction_X = DIRECTION_RIGHT;
						this->_direction = (DIRECTION)direction_X;
						_isLeft = false;
						OBJECTMANAGER->setTileIdx(this, _idxX + 1, _idxY);
					}
					else if (direction_Y == -1)
					{
						direction_Y = DIRECTION_UP;
						this->_direction = (DIRECTION)direction_Y;
						OBJECTMANAGER->setTileIdx(this, _idxX, _idxY - 1);
					}
					else if (direction_Y == 1)
					{
						direction_Y = DIRECTION_DOWN;
						this->_direction = (DIRECTION)direction_Y;
						OBJECTMANAGER->setTileIdx(this, _idxX, _idxY + 1);
					}
					_moveDistance = TILE_SIZE;
					_isHalfMove = true;
					_posZ = 0;
					_jumpPower = 6.0f;
				}
			}
			return true;
		}
		else if (_aStarState == ASTAR_STATE_NOWAY)
		{
			return false;
		}

		addOpenList();
		calculateH();
		calculateF();
		addCloseList();
		checkArrive();
	}
}

void enemy_coralriff_head::hitEnemy(int damage)
{
	soundHit();
	_isDrawHP = true;
	_heart -= damage;

	int num = RND->getFromIntTo(1, 4);
	int idxX;
	int idxY;
	switch (num)
	{
	case 1:
		idxX = 5;
		idxY = 9;
		OBJECTMANAGER->setTileIdx(this, idxX, idxY);
		_posX = _idxX * TILE_SIZE + 26;
		_posY = _idxY * TILE_SIZE + 26;
		break;
	case 2:
		idxX = 13;
		idxY = 9;
		OBJECTMANAGER->setTileIdx(this, idxX, idxY);
		_posX = _idxX * TILE_SIZE + 26;
		_posY = _idxY * TILE_SIZE + 26;
		break;
	case 3:
		idxX = 13;
		idxY = 14;
		OBJECTMANAGER->setTileIdx(this, idxX, idxY);
		_posX = _idxX * TILE_SIZE + 26;
		_posY = _idxY * TILE_SIZE + 26;
		break;
	case 4:
		idxX = 5;
		idxY = 14;
		OBJECTMANAGER->setTileIdx(this, idxX, idxY);
		_posX = _idxX * TILE_SIZE + 26;
		_posY = _idxY * TILE_SIZE + 26;
		break;
	}

	if (_heart <= 0)
	{
		soundDie();
		OBJECTMANAGER->grooveChain();
		_isDrawHP = false;
		dieEnemy();
		OBJECTMANAGER->setBossAlive(false);

		for (int idxX = 7; idxX < 12; idxX++)
			OBJECTMANAGER->deleteObject(OBJECTMANAGER->getCheckObj(idxX, 7));

		for (int idxY = 8; idxY < 16; idxY++)
		{
			for (int idxX = 4; idxX < 16; idxX++)
			{
				OBJECTMANAGER->setBossFloor(idxX, idxY);
			}
		}
		
	}
}

void enemy_coralriff_head::createWall()
{
	parentObj* tempPlayer = OBJECTMANAGER->getPlayer();

	if (tempPlayer->getIdxY() < 15)
	{
		for (int idxX = 8; idxX < 11; idxX++)
		{
			OBJECTMANAGER->deleteObject(OBJECTMANAGER->getCheckObj(idxX, 16));
			OBJECTMANAGER->setBossWall(idxX, 16);
		}

		/*for (int idxY = 15; idxY >= 1; idxY--)
		{
			for (int idxX = 7; idxX < 12; idxX++)
			{
				if (OBJECTMANAGER->getCheckObj(idxX, idxY) == NULL) continue;
				OBJECTMANAGER->deleteObject(OBJECTMANAGER->getCheckObj(idxX, idxY));
			}
		}

		for (int idxY = 15; idxY >= 1; idxY--)
		{
			for (int idxX = 7; idxX < 12; idxX++)
			{
				if (OBJECTMANAGER->getCheckFloor(idxX, idxY) == NULL) continue;
				OBJECTMANAGER->deleteFloorTile(OBJECTMANAGER->getCheckFloor(idxX, idxY));
			}
		}*/
		SOUNDMANAGER->play("sound_boss_wall", 0.5f);
		OBJECTMANAGER->setIsEnter(true);
		CAMERA->isQuake();
	}

}

void enemy_coralriff_head::setFrame()
{
	_attackAni = KEYANIMANAGER->findAnimation("boss_attack", "boss_attack");
	_attackAni->start();
}

void enemy_coralriff_head::dieEnemy()
{
	soundDie();
	OBJECTMANAGER->grooveChain();
	OBJECTMANAGER->deleteObject(this);
}
