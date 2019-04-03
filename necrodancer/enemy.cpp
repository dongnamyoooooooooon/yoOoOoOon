#include "stdafx.h"
#include "enemy.h"


enemy::enemy()
{
}


enemy::~enemy()
{
}

HRESULT enemy::init(string imgName, int idxX, int idxY)
{
	_imgName = imgName;
	_img = IMAGEMANAGER->findImage(_imgName);
	_isHalfMove = false;

	_moveBeat = 1;
	_curMoveBeat = 0;

	_idxX = idxX;
	_idxY = idxY;

	_posX = _idxX * TILE_SIZE + 26;
	_posY = _idxY * TILE_SIZE + 26;

	_subX = 0;
	_subY = 0;

	_frameX = 0;
	_frameY = 0;

	_maxFrameX = IMAGEMANAGER->findImage(_imgName)->GetMaxFrameX();
	_maxFrameY = IMAGEMANAGER->findImage(_imgName)->GetMaxFrameY();
	_count = 0;

	_objType = OBJECT_TYPE_ENEMY;

	_heart = 2;
	_maxHeart = 2;
	_damage = 1;
	_isLeft = false;
	_isBeat = false;
	_isDrawHP = false;
	_isSaw = false;

	_gravity = GRAVETY;
	_jumpPower = 0;

	_move = DIRECITON_NONE;
	_direction = DIRECITON_NONE;

	_tileY = OBJECTMANAGER->getTileY();
	_tileX = OBJECTMANAGER->getTileX();

	for (int i = 0; i < _tileY; i++)
	{
		vector<aStarTile> vTile;
		for (int j = 0; j < _tileX; j++)
		{
			aStarTile aTile;
			aTile = {};
			vTile.push_back(aTile);
			//이거 업데이트로 받아야 플레이어 변한위치 받을수있음....
		}
		_vvTile.push_back(vTile);
	}

	return E_NOTIMPL;
}

void enemy::release()
{
}

void enemy::update()
{

	aniEnemy();
	moveEnemy();

	if (_isBeat)
	{
		_curMoveBeat++;
		if (_moveBeat == _curMoveBeat)
		{
			_curMoveBeat = 0;
			aStarLoad();
		}
		_isBeat = false;
	}
}

void enemy::render()
{
	if (_isSaw)
	{
		//그림자이미지
		if (_isSight)
		{
			if (_hasLight)
			{
				if (_isLeft) _img->frameRenderReverseX(_posX - _subX, _posY - _subY + _jumpPower, _frameX, 0);
				else		_img->frameRender(_posX - _subX, _posY - _subY + _jumpPower, _frameX, 0);
			}
			else
			{
				if (_isLeft) _img->frameRenderReverseX(_posX - _subX, _posY - _subY + _jumpPower, _frameX, 1);
				else		_img->frameRender(_posX - _subX, _posY - _subY + _jumpPower, _frameX, 1);
			}
		}
		else
		{
			if (_isLeft) _img->frameRenderReverseX(_posX - _subX, _posY - _subY + _jumpPower, _frameX, 1);
			else		_img->frameRender(_posX - _subX, _posY - _subY + _jumpPower, _frameX, 1);
		}
	}

	if (_isDrawHP && _heart != _maxHeart)
	{
		for (int i = _heart; i < _maxHeart; i++)
		{
			IMAGEMANAGER->findImage("enemy_heart_empty")->render((_posX + 26) - (_maxHeart / 2) * 24 + 24 * i - 7, _posY - _subY - 24);
		}
		for (int i = 0; i < _heart; i++)
		{
			IMAGEMANAGER->findImage("enemy_heart")->render((_posX + 26) - (_maxHeart / 2) * 24 + 24 * i - 7, _posY - _subY - 24);
		}
	}
}

void enemy::aniEnemy()
{
	_count++;
	if (_count % 10 == 0)
	{
		_frameX++;
		if (_frameX > _maxFrameX) _frameX = 0;
	}

}

void enemy::moveEnemy()
{

	//_moveDistance = TILE_SIZE;
	_speed = 4;

	switch (_direction)
	{
	case DIRECTION_LEFT:
		_posX -= _speed;
		_moveDistance -= _speed;
		if (_moveDistance <= 0)
		{
			//horizonSet();
			_direction = DIRECITON_NONE;
		}
		break;
	case DIRECTION_RIGHT:
		_posX += _speed;
		_moveDistance -= _speed;
		if (_moveDistance <= 0)
		{
			//horizonSet();
			_direction = DIRECITON_NONE;
		}
		break;
	case DIRECTION_UP:
		_posY -= _speed;
		_moveDistance -= _speed;
		if (_moveDistance <= 0)
		{
			//verticalSet();
			_direction = DIRECITON_NONE;
		}
		break;
	case DIRECTION_DOWN:
		_posY += _speed;
		_moveDistance -= _speed;
		if (_moveDistance <= 0)
		{
			//verticalSet();
			_direction = DIRECITON_NONE;
		}
		break;
	}
}

void enemy::jumpMoveEnemy()
{
	//_jumpPower = TIMEMANAGER->getElapsedTime() * JUMPPOWER;
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
				/*if (_moveDistance > TILE_SIZE / 2)
				{
					_jumpPower -= _jumpPower;
				}
				else _jumpPower += _jumpPower;*/
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
				_posZ -= _jumpPower;
				_jumpPower -= 1.2f;
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
				_posZ += _jumpPower;
				_jumpPower -= 1.2f;
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
				_posZ += _jumpPower;
				_jumpPower -= 1.2f;
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

	/*_speed = TIMEMANAGER->getElapsedTime() * PLAYER_SPEED;
	_jumpPower = JUMPPOWER;
	_gravity = GRAVETY;

	if (!_isHalfMove)
	{
		switch (_direction)
		{
		case DIRECTION_LEFT:
			_moveDistance -= _speed;
			_posX -= _speed;
			_posZ -= _jumpPower * TIMEMANAGER->getElapsedTime();
			_jumpPower -= _gravity * TIMEMANAGER->getElapsedTime();
			if (_posZ > 0) _posZ = 0;
			if (_moveDistance < _speed)
			{
				horizonSet();
				_jumpPower = 0;
				_posZ = 0;
				_direction = DIRECITON_NONE;
				_isHalfMove = false;
			}
			break;
		case DIRECTION_RIGHT:
			_moveDistance -= _speed;
			_posX += _speed;
			_posZ -= _jumpPower * TIMEMANAGER->getElapsedTime();
			_jumpPower -= _gravity * TIMEMANAGER->getElapsedTime();
			if (_posZ > 0) _posZ = 0;
			if (_moveDistance < _speed)
			{
				horizonSet();
				_jumpPower = 0;
				_posZ = 0;
				_direction = DIRECITON_NONE;
				_isHalfMove = false;
			}
			break;
		case DIRECTION_UP:
			_moveDistance -= _speed;
			_posY -= _speed;
			_posZ -= _jumpPower * TIMEMANAGER->getElapsedTime();
			_jumpPower -= _gravity * TIMEMANAGER->getElapsedTime();
			if (_posZ > 0) _posZ = 0;
			if (_moveDistance < _speed)
			{
				verticalSet();
				_jumpPower = 0;
				_posZ = 0;
				_direction = DIRECITON_NONE;
				_isHalfMove = false;
			}
			break;
		case DIRECTION_DOWN:
			_moveDistance -= _speed;
			_posY += _speed;
			_posZ -= _jumpPower * TIMEMANAGER->getElapsedTime();
			_jumpPower -= _gravity * TIMEMANAGER->getElapsedTime();
			if (_posZ > 0) _posZ = 0;
			if (_moveDistance < _speed)
			{
				verticalSet();
				_jumpPower = 0;
				_posZ = 0;
				_direction = DIRECITON_NONE;
				_isHalfMove = false;
			}
			break;
		}
	}
	else
	{
		switch (_direction)
		{
		case DIRECTION_LEFT:
			_posX -= _speed;
			_moveDistance -= _speed;
			_posZ -= _jumpPower * TIMEMANAGER->getElapsedTime();
			_jumpPower -= _gravity * TIMEMANAGER->getElapsedTime();
			if (_posZ > 0) _posZ = 0;
			if (_moveDistance < _speed)
			{
				horizonSet();
				_jumpPower = 0;
				_posZ = 0;
				_direction = DIRECITON_NONE;
			}

			break;
		case DIRECTION_RIGHT:
			_posX += _speed;
			_moveDistance -= _speed;
			_posZ -= _jumpPower * TIMEMANAGER->getElapsedTime();
			_jumpPower -= _gravity * TIMEMANAGER->getElapsedTime();
			if (_posZ > 0) _posZ = 0;
			if (_moveDistance < _speed)
			{
				horizonSet();
				_jumpPower = 0;
				_posZ = 0;
				_direction = DIRECITON_NONE;
			}
			break;
		case DIRECTION_UP:
			_posY -= _speed;
			_moveDistance -= _speed;
			_posZ -= _jumpPower * TIMEMANAGER->getElapsedTime();
			_jumpPower -= _gravity * TIMEMANAGER->getElapsedTime();
			if (_posZ > 0) _posZ = 0;
			if (_moveDistance < _speed)
			{
				horizonSet();
				_jumpPower = 0;
				_posZ = 0;
				_direction = DIRECITON_NONE;
			}
			break;
		case DIRECTION_DOWN:
			_posY += _speed;
			_moveDistance -= _speed;
			_posZ -= _jumpPower * TIMEMANAGER->getElapsedTime();
			_jumpPower -= _gravity * TIMEMANAGER->getElapsedTime();
			if (_posZ > 0) _posZ = 0;
			if (_moveDistance < _speed)
			{
				verticalSet();
				_jumpPower = 0;
				_posZ = 0;
				_direction = DIRECITON_NONE;
			}
			break;
		}
	}*/
}

void enemy::attackEnemy(DIRECTION dir)
{
	soundAtt();
	_direction = dir;
	player* tempPlayer = OBJECTMANAGER->getPlayer();

	//_posX = tempPlayer->getPosX();
	//_posY = tempPlayer->getPosY();
	tempPlayer->hitPlayer(_damage);

}

void enemy::hitEnemy(int damage)
{
	soundHit();
	_isDrawHP = true;
	_heart -= damage;

	if (_heart <= 0) this->dieEnemy();
}

void enemy::dieEnemy()
{
	soundDie();
	OBJECTMANAGER->grooveChain();

	OBJECTMANAGER->deleteObject(this);
}


void enemy::rendomMove()
{
	_moveDistance = TILE_SIZE;
	if (RND->getInt(2) == 0)
	{
		if (RND->getInt(2) == 0)
		{
			_isLeft = false;
			_frameX = 0;
			_direction = DIRECTION_RIGHT;
		}
		else
		{
			_isLeft = true;
			_frameX = 0;
			_direction = DIRECTION_LEFT;
		}
	}
	else
	{
		if (RND->getInt(2) == 0)
			_direction = DIRECTION_UP;
		else
			_direction = DIRECTION_DOWN;
	}

	OBJECT_TYPE objType;

	if (_direction == DIRECTION_LEFT)
	{
		parentObj* obj = OBJECTMANAGER->getCheckObj(_idxX - 1, _idxY);
		if (obj != NULL)
		{
			objType = obj->getObjType();

			if (objType == OBJECT_TYPE_PLAYER)
			{
				attackEnemy(_direction);

				_direction = DIRECITON_NONE;
				_moveDistance = 0;
			}
			else if (objType == OBJECT_TYPE_WALL)
			{
				_direction = DIRECITON_NONE;
				_moveDistance = 0;
			}
			else if (objType == OBJECT_TYPE_ENEMY)
			{
				_direction = DIRECITON_NONE;
				_moveDistance = 0;
			}
		}
		else
			OBJECTMANAGER->setTileIdx(this, _idxX - 1, _idxY);
	}
	else if (_direction == DIRECTION_RIGHT)
	{
		parentObj* obj = OBJECTMANAGER->getCheckObj(_idxX + 1, _idxY);
		if (obj != NULL)
		{
			objType = obj->getObjType();

			if (objType == OBJECT_TYPE_PLAYER)
			{
				attackEnemy(_direction);

				_direction = DIRECITON_NONE;
				_moveDistance = 0;
			}
			else if (objType == OBJECT_TYPE_WALL)
			{
				_direction = DIRECITON_NONE;
				_moveDistance = 0;
			}
			else if (objType == OBJECT_TYPE_ENEMY)
			{
				_direction = DIRECITON_NONE;
				_moveDistance = 0;
			}
		}
		else
			OBJECTMANAGER->setTileIdx(this, _idxX + 1, _idxY);
	}
	else if (_direction == DIRECTION_UP)
	{
		parentObj* obj = OBJECTMANAGER->getCheckObj(_idxX, _idxY - 1);
		if (obj != NULL)
		{
			objType = obj->getObjType();

			if (objType == OBJECT_TYPE_PLAYER)
			{
				attackEnemy(_direction);

				_direction = DIRECITON_NONE;
				_moveDistance = 0;
			}
			else if (objType == OBJECT_TYPE_WALL)
			{
				_direction = DIRECITON_NONE;
				_moveDistance = 0;
			}
			else if (objType == OBJECT_TYPE_ENEMY)
			{
				_direction = DIRECITON_NONE;
				_moveDistance = 0;
			}
		}
		else
			OBJECTMANAGER->setTileIdx(this, _idxX, _idxY - 1);
	}
	else if (_direction == DIRECTION_DOWN)
	{
		parentObj* obj = OBJECTMANAGER->getCheckObj(_idxX, _idxY + 1);
		if (obj != NULL)
		{
			objType = obj->getObjType();

			if (objType == OBJECT_TYPE_PLAYER)
			{
				attackEnemy(_direction);

				_direction = DIRECITON_NONE;
				_moveDistance = 0;
			}
			else if (objType == OBJECT_TYPE_WALL)
			{
				_direction = DIRECITON_NONE;
				_moveDistance = 0;
			}
			else if (objType == OBJECT_TYPE_ENEMY)
			{
				_direction = DIRECITON_NONE;
				_moveDistance = 0;
			}
		}
		else
			OBJECTMANAGER->setTileIdx(this, _idxX, _idxY + 1);
	}
}

void enemy::patternMove()
{
	_moveDistance = TILE_SIZE;
	OBJECT_TYPE objType;

	if (_idxY % 2 == 0)
	{
		_direction = DIRECTION_UP;
	}
	else
	{
		_direction = DIRECTION_DOWN;
	}

	if (_direction == DIRECTION_UP)
	{
		parentObj* obj = OBJECTMANAGER->getCheckObj(_idxX, _idxY - 1);
		if (obj != NULL)
		{
			objType = obj->getObjType();

			if (objType == OBJECT_TYPE_PLAYER)
			{
				attackEnemy(_direction);

				_direction = DIRECITON_NONE;
				_moveDistance = 0;
			}
			else if (objType == OBJECT_TYPE_WALL)
			{
				_direction = DIRECITON_NONE;
				_moveDistance = 0;
			}

		}
		else
			OBJECTMANAGER->setTileIdx(this, _idxX, _idxY - 1);
	}
	else if (_direction == DIRECTION_DOWN)
	{
		parentObj* obj = OBJECTMANAGER->getCheckObj(_idxX, _idxY + 1);
		if (obj != NULL)
		{
			objType = obj->getObjType();

			if (objType == OBJECT_TYPE_PLAYER)
			{
				attackEnemy(_direction);

				_direction = DIRECITON_NONE;
				_moveDistance = 0;
			}
			else if (objType == OBJECT_TYPE_WALL)
			{
				_direction = DIRECITON_NONE;
				_moveDistance = 0;
			}
		}
		else
			OBJECTMANAGER->setTileIdx(this, _idxX, _idxY + 1);
	}

}

bool enemy::aStarLoad()
{
	//for (int i = 0; i < _tileY; i++)
	//{
	//	vector<aStarTile> vTile;
	//	for (int j = 0; j < _tileX; j++)
	//	{
	//		aStarTile aTile;
	//		aTile = {};
	//		vTile.push_back(aTile);
	//		//이거 업데이트로 받아야 플레이어 변한위치 받을수있음....
	//	}
	//	_vvTile.push_back(vTile);
	//}

	player* _player = OBJECTMANAGER->getPlayer();

	int direction_X = _player->getIdxX() - _idxX;
	int direction_Y = _player->getIdxY() - _idxY;

	if ((direction_X == -1 && direction_Y == 0) || (direction_X == 0 && direction_Y == -1)
		|| (direction_X == 1 && direction_Y == 0) || (direction_X == 0 && direction_Y == 1))
	{

		attackEnemy(_direction);
		return true;
	}

	//if (direction_X == -1)
	//{
	//	direction_X = DIRECTION_LEFT;
	//	this->_direction = (DIRECTION)direction_X;
	//	attackEnemy(_direction);
	//	return true;
	//}
	//else if (direction_X == 1)
	//{
	//	direction_X = DIRECTION_RIGHT;
	//	this->_direction = (DIRECTION)direction_X;
	//	attackEnemy(_direction);
	//	return true;
	//}
	//else if (direction_Y == -1)
	//{
	//	direction_Y = DIRECTION_UP;
	//	this->_direction = (DIRECTION)direction_Y;
	//	attackEnemy(_direction);
	//	return true;
	//}
	//else if (direction_Y == 1)
	//{
	//	direction_Y = DIRECTION_DOWN;
	//	this->_direction = (DIRECTION)direction_Y;
	//	attackEnemy(_direction);
	//	return true;
	//}


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
void enemy::initTile()
{
	parentObj* tempObj;

	for (int i = 0; i < _tileY; i++)
	{
		for (int j = 0; j < _tileX; j++)
		{
			tempObj = OBJECTMANAGER->getCheckObj(j, i);

			if (tempObj == NULL)
			{
				_vvTile[i][j].isWalk = true;
				_vvTile[i][j].listOn = false;
			}
			else
			{
				OBJECT_TYPE objType = tempObj->getObjType();
				if (objType == OBJECT_TYPE_WALL)
				{
					_vvTile[i][j].isWalk = false;
					_vvTile[i][j].listOn = false;
				}
				else if (objType == OBJECT_TYPE_ITEM)
				{
					_vvTile[i][j].isWalk = false;
					_vvTile[i][j].listOn = false;
				}
				else if (objType == OBJECT_TYPE_ENEMY)
				{
					if (tempObj->getIdxX() == _idxX && tempObj->getIdxY() == _idxY)
					{
						_vvTile[i][j].isWalk = true;
						_vvTile[i][j].listOn = true;
						_closeList.push_back(&_vvTile[i][j]);
						_startPoint = true;
						_startX = j;
						_startY = i;
					}
					else
					{
						_vvTile[i][j].isWalk = false;
						_vvTile[i][j].listOn = false;
					}
				}
				else if (objType == OBJECT_TYPE_PLAYER)
				{
					_vvTile[i][j].isWalk = true;
					_vvTile[i][j].listOn = false;
					_endX = j;
					_endY = i;
				}
			}
		}
	}
	_aStarState = ASTAR_STATE_SEARCHING;
	_lastIndex = 0;
}

void enemy::addOpenList()
{
	_closeI = _closeList[_lastIndex]->i;
	_closeJ = _closeList[_lastIndex]->j;
	_closeGoal = _closeList[_lastIndex]->G;

	if (_closeI - 1 >= 0)
	{
		if (_vvTile[_closeI - 1][_closeJ].isWalk)
		{
			if (!_vvTile[_closeI - 1][_closeJ].listOn)
			{
				_vvTile[_closeI - 1][_closeJ].listOn = true;
				_vvTile[_closeI - 1][_closeJ].G = _closeGoal + 10;
				_vvTile[_closeI - 1][_closeJ].parent = _closeList[_lastIndex];
				_openList.push_back(&_vvTile[_closeI - 1][_closeJ]);
			}
			else
			{
				if (_closeGoal + 10 < _vvTile[_closeI - 1][_closeJ].G)
				{
					_vvTile[_closeI - 1][_closeJ].G = _closeGoal + 10;
					_vvTile[_closeI - 1][_closeJ].parent = _closeList[_lastIndex];
				}
			}
		}
	}

	if (_closeI + 1 <= _vvTile.size() - 1)
	{
		if (_vvTile[_closeI + 1][_closeJ].isWalk)
		{
			if (!_vvTile[_closeI + 1][_closeJ].listOn)
			{
				_vvTile[_closeI + 1][_closeJ].listOn = true;
				_vvTile[_closeI + 1][_closeJ].G = _closeGoal + 10;
				_vvTile[_closeI + 1][_closeJ].parent = _closeList[_lastIndex];
				_openList.push_back(&_vvTile[_closeI + 1][_closeJ]);
			}
			else
			{
				if (_closeGoal + 10 < _vvTile[_closeI + 1][_closeJ].G)
				{
					_vvTile[_closeI + 1][_closeJ].G = _closeGoal + 10;
					_vvTile[_closeI + 1][_closeJ].parent = _closeList[_lastIndex];
				}
			}
		}
	}

	if (_closeJ - 1 >= 0)
	{
		if (_vvTile[_closeI][_closeJ - 1].isWalk)
		{
			if (!_vvTile[_closeI][_closeJ - 1].listOn)
			{
				_vvTile[_closeI][_closeJ - 1].listOn = true;
				_vvTile[_closeI][_closeJ - 1].G = _closeGoal + 10;
				_vvTile[_closeI][_closeJ - 1].parent = _closeList[_lastIndex];
				_openList.push_back(&_vvTile[_closeI][_closeJ - 1]);
			}
			else
			{
				if (_closeGoal + 10 < _vvTile[_closeI][_closeJ - 1].G)
				{
					_vvTile[_closeI][_closeJ - 1].G = _closeGoal + 10;
					_vvTile[_closeI][_closeJ - 1].parent = _closeList[_lastIndex];
				}
			}
		}
	}

	if (_closeJ + 1 <= _vvTile[0].size() - 1)
	{
		if (_vvTile[_closeI][_closeJ + 1].isWalk)
		{
			if (!_vvTile[_closeI][_closeJ + 1].listOn)
			{
				_vvTile[_closeI][_closeJ + 1].listOn = true;
				_vvTile[_closeI][_closeJ + 1].G = _closeGoal + 10;
				_vvTile[_closeI][_closeJ + 1].parent = _closeList[_lastIndex];
				_openList.push_back(&_vvTile[_closeI][_closeJ + 1]);
			}
			else
			{
				if (_closeGoal + 10 < _vvTile[_closeI][_closeJ + 1].G)
				{
					_vvTile[_closeI][_closeJ + 1].G = _closeGoal + 10;
					_vvTile[_closeI][_closeJ + 1].parent = _closeList[_lastIndex];
				}
			}
		}
	}
}

void enemy::addCloseList()
{
	if (_openList.size() == 0)
	{
		_aStarState = ASTAR_STATE_NOWAY; return;
	}

	int index = 0;
	int lowest = 5000;
	for (int i = 0; i < _openList.size(); i++)
	{
		if (_openList[i]->F < lowest)
		{
			lowest = _openList[i]->F;
			index = i;
		}
	}
	_closeList.push_back(_openList[index]);
	_openList.erase(_openList.begin() + index);

	_lastIndex++;
}

void enemy::calculateH()
{
	for (int i = 0; i < _openList.size(); i++)
	{
		int vertical = (_endX - _openList[i]->j) * 10;
		int horizontal = (_endY - _openList[i]->i) * 10;

		if (vertical < 0)	vertical *= -1;
		if (horizontal < 0) horizontal *= -1;

		_openList[i]->H = vertical + horizontal;
	}
}

void enemy::calculateF()
{
	for (int i = 0; i < _openList.size(); i++)
	{
		_openList[i]->F = _openList[i]->G + _openList[i]->H;
	}
}

void enemy::checkArrive()
{
	if (_closeList[_lastIndex]->i == _endY && _closeList[_lastIndex]->j == _endX)
		_aStarState = ASTAR_STATE_FOUND;
}

void enemy::soundAtt()
{
	if (_imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_SKELETON] || _imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_SKELETON_YELLOW]
		|| _imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_SKELETON_BLACK] || _imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_SKELETON_MAGE_WHITE]
		|| _imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_SKELETON_MAGE_YELLOW] || _imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_SKELETON_MAGE_BLACK])
	{
		SOUNDMANAGER->play("sound_skel_attack_melee");
	}
	else if (_imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_ARMADILLO])
	{
		SOUNDMANAGER->play("sound_armadillo_attack");
	}
	else if (_imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_SLIME_GREEN] || _imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_SLIME_BLUE])
	{
		SOUNDMANAGER->play("sound_slime_attack");
	}
	else if (_imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_ZOMBIE])
	{
		SOUNDMANAGER->play("sound_zombie_attack");
	}
	else if (_imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_CLONE])
	{
		SOUNDMANAGER->play("sound_clone_attack");
	}
	else if (_imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_BAT] || _imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_BAT_RED])
	{
		SOUNDMANAGER->play("sound_bat_attack");
	}
	else if (_imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_BAT_MINIBOSS])
	{
		SOUNDMANAGER->play("sound_vampbat_attack");
	}
	else if (_imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_BANSHEE])
	{
		SOUNDMANAGER->play("sound_banshee_attack");
	}
	else if (_imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_DRAGON_GREEN])
	{
		SOUNDMANAGER->play("sound_dragon_attack_melee");
	}
	else if (_imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_MINOTAUR])
	{
		SOUNDMANAGER->play("sound_minotaur_attack");
	}
	else if (_imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_CORALRIFF_HEAD])
	{
		if ("그냥어택인지?")
		{
			int random = RND->getFromIntTo(1, 4);
			switch (random)
			{
			case 1:
				SOUNDMANAGER->play("sound_coralriff_attack_mel_01");
				break;
			case 2:
				SOUNDMANAGER->play("sound_coralriff_attack_mel_02");
				break;
			case 3:
				SOUNDMANAGER->play("sound_coralriff_attack_mel_03");
				break;
			case 4:
				SOUNDMANAGER->play("sound_coralriff_attack_mel_04");
				break;
			}
		}
		else if ("스플어택인지?")
		{
			int random = RND->getFromIntTo(1, 4);
			switch (random)
			{
			case 1:
				SOUNDMANAGER->play("sound_coralriff_attack_splash_01");
				break;
			case 2:
				SOUNDMANAGER->play("sound_coralriff_attack_splash_02");
				break;
			case 3:
				SOUNDMANAGER->play("sound_coralriff_attack_splash_03");
				break;
			case 4:
				SOUNDMANAGER->play("sound_coralriff_attack_splash_04");
				break;
			}
		}
	}
	else if (_imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_SHOPKEEPER])
	{
		int random = RND->getFromIntTo(1, 4);
		switch (random)
		{
		case 1:
			SOUNDMANAGER->play("sound_shopkeep_norm_attack_01");
			break;
		case 2:
			SOUNDMANAGER->play("sound_shopkeep_norm_attack_02");
			break;
		case 3:
			SOUNDMANAGER->play("sound_shopkeep_norm_attack_03");
			break;
		case 4:
			SOUNDMANAGER->play("sound_shopkeep_norm_attack_04");
			break;
		}
	}
}

void enemy::soundHit()
{
	if (_imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_SKELETON] || _imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_SKELETON_YELLOW]
		|| _imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_SKELETON_BLACK] || _imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_SKELETON_MAGE_WHITE]
		|| _imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_SKELETON_MAGE_YELLOW] || _imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_SKELETON_MAGE_BLACK])
	{
		int random = RND->getFromIntTo(1, 4);
		switch (random)
		{
		case 1:
			SOUNDMANAGER->play("sound_skel_hit");
			break;
		case 2:
			SOUNDMANAGER->play("sound_skel_hit_01");
			break;
		case 3:
			SOUNDMANAGER->play("sound_skel_hit_02");
			break;
		case 4:
			SOUNDMANAGER->play("sound_skel_hit_03");
			break;
		}
	}
	else if (_imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_ARMADILLO])
	{
		SOUNDMANAGER->play("sound_armadillo_hit");
	}
	else if (_imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_SLIME_GREEN] || _imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_SLIME_BLUE])
	{
		int random = RND->getFromIntTo(1, 4);
		switch (random)
		{
		case 1:
			SOUNDMANAGER->play("sound_slime_hit");
			break;
		case 2:
			SOUNDMANAGER->play("sound_slime_hit_01");
			break;
		case 3:
			SOUNDMANAGER->play("sound_slime_hit_02");
			break;
		case 4:
			SOUNDMANAGER->play("sound_slime_hit_03");
			break;
		}
	}
	else if (_imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_BAT] || _imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_BAT_RED])
	{
		SOUNDMANAGER->play("sound_bat_hit");
	}
	else if (_imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_BAT_MINIBOSS])
	{
		int random = RND->getFromIntTo(1, 3);
		switch (random)
		{
		case 1:
			SOUNDMANAGER->play("sound_vampbat_hit_01");
			break;
		case 2:
			SOUNDMANAGER->play("sound_vampbat_hit_02");
			break;
		case 3:
			SOUNDMANAGER->play("sound_vampbat_hit_03");
			break;
		}
	}
	else if (_imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_BANSHEE])
	{
		int random = RND->getFromIntTo(1, 3);
		switch (random)
		{
		case 1:
			SOUNDMANAGER->play("sound_banshee_hit_01");
			break;
		case 2:
			SOUNDMANAGER->play("sound_banshee_hit_02");
			break;
		case 3:
			SOUNDMANAGER->play("sound_banshee_hit_03");
			break;
		}
	}
	else if (_imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_DRAGON_GREEN])
	{
		int random = RND->getFromIntTo(1, 3);
		switch (random)
		{
		case 1:
			SOUNDMANAGER->play("sound_dragon_hit_01");
			break;
		case 2:
			SOUNDMANAGER->play("sound_dragon_hit_02");
			break;
		case 3:
			SOUNDMANAGER->play("sound_dragon_hit_03");
			break;
		}
	}
	else if (_imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_MINOTAUR])
	{
		int random = RND->getFromIntTo(1, 4);
		switch (random)
		{
		case 1:
			SOUNDMANAGER->play("sound_minotaur_hit");
			break;
		case 2:
			SOUNDMANAGER->play("sound_minotaur_hit_01");
			break;
		case 3:
			SOUNDMANAGER->play("sound_minotaur_hit_02");
			break;
		case 4:
			SOUNDMANAGER->play("sound_minotaur_hit_03");
			break;
		}
	}
	else if (_imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_CORALRIFF_HEAD])
	{
		int random = RND->getFromIntTo(1, 4);
		switch (random)
		{
		case 1:
			SOUNDMANAGER->play("sound_coralriff_hit_01");
			break;
		case 2:
			SOUNDMANAGER->play("sound_coralriff_hit_02");
			break;
		case 3:
			SOUNDMANAGER->play("sound_coralriff_hit_03");
			break;
		case 4:
			SOUNDMANAGER->play("sound_coralriff_hit_04");
			break;
		}
	}
	else if (_imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_SHOPKEEPER])
	{
		int random = RND->getFromIntTo(1, 6);
		switch (random)
		{
		case 1:
			SOUNDMANAGER->play("sound_shopkeep_norm_hit_01");
			break;
		case 2:
			SOUNDMANAGER->play("sound_shopkeep_norm_hit_02");
			break;
		case 3:
			SOUNDMANAGER->play("sound_shopkeep_norm_hit_03");
			break;
		case 4:
			SOUNDMANAGER->play("sound_shopkeep_norm_hit_04");
			break;
		case 5:
			SOUNDMANAGER->play("sound_shopkeep_norm_hit_05");
			break;
		case 6:
			SOUNDMANAGER->play("sound_shopkeep_norm_hit_06");
			break;
		}
	}
}

void enemy::soundCry()
{
	if (_imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_BAT_MINIBOSS])
	{
		SOUNDMANAGER->play("sound_vampbat_cry");
	}
	else if (_imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_BANSHEE])
	{
		SOUNDMANAGER->play("sound_banshee_cry");
	}
	else if (_imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_DRAGON_GREEN])
	{
		SOUNDMANAGER->play("sound_dragon_cry");
	}
	else if (_imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_MINOTAUR])
	{
		SOUNDMANAGER->play("sound_minotaur_cry");
	}
	else if (_imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_CORALRIFF_HEAD])
	{
		SOUNDMANAGER->play("sound_coralriff_cry");
	}
}

void enemy::soundDie()
{
	if (_imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_SKELETON] || _imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_SKELETON_YELLOW]
		|| _imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_SKELETON_BLACK] || _imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_SKELETON_MAGE_WHITE]
		|| _imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_SKELETON_MAGE_YELLOW] || _imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_SKELETON_MAGE_BLACK])
	{
		SOUNDMANAGER->play("sound_skel_death");
	}
	else if (_imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_ARMADILLO])
	{
		SOUNDMANAGER->play("sound_armadillo_death");
	}
	else if (_imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_SLIME_GREEN] || _imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_SLIME_BLUE])
	{
		int random = RND->getFromIntTo(1, 4);
		switch (random)
		{
		case 1:
			SOUNDMANAGER->play("sound_slime_death");
			break;
		case 2:
			SOUNDMANAGER->play("sound_slime_death_01");
			break;
		case 3:
			SOUNDMANAGER->play("sound_slime_death_02");
			break;
		case 4:
			SOUNDMANAGER->play("sound_slime_death_03");
			break;
		}
	}
	else if (_imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_ZOMBIE])
	{
		SOUNDMANAGER->play("sound_zombie_death");
	}
	else if (_imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_CLONE])
	{
		SOUNDMANAGER->play("sound_clone_death");
	}
	else if (_imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_BAT] || _imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_BAT_RED])
	{
		SOUNDMANAGER->play("sound_bat_death");
	}
	else if (_imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_BAT_MINIBOSS])
	{
		SOUNDMANAGER->play("sound_vampbat_death");
	}
	else if (_imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_BANSHEE])
	{
		SOUNDMANAGER->play("sound_banshee_death");
	}
	else if (_imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_DRAGON_GREEN])
	{
		SOUNDMANAGER->play("sound_dragon_death");
	}
	else if (_imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_MINOTAUR])
	{
		SOUNDMANAGER->play("sound_minotaur_death");
	}
	else if (_imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_CORALRIFF_HEAD])
	{
		SOUNDMANAGER->play("sound_coralriff_death");
	}
	else if (_imgName == IMAGE_NAME[IMAGE_NAME_ENEMY_SHOPKEEPER])
	{
		int random = RND->getFromIntTo(1, 5);
		switch (random)
		{
		case 1:
			SOUNDMANAGER->play("sound_shopkeep_norm_death_01");
			break;
		case 2:
			SOUNDMANAGER->play("sound_shopkeep_norm_death_02");
			break;
		case 3:
			SOUNDMANAGER->play("sound_shopkeep_norm_death_03");
			break;
		case 4:
			SOUNDMANAGER->play("sound_shopkeep_norm_death_04");
			break;
		case 5:
			SOUNDMANAGER->play("sound_shopkeep_norm_death_05");
			break;
		}
	}
}

void enemy::horizonSet()
{
	_posX = (int)(_posX / TILE_SIZE) * TILE_SIZE + 26;
	_moveDistance = 0;
	_idxX = _posX / TILE_SIZE;
}

void enemy::verticalSet()
{
	_posY = (int)_posY / TILE_SIZE * TILE_SIZE + 26;
	_moveDistance = 0;
	_idxY = _posY / TILE_SIZE;
}
