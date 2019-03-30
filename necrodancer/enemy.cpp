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
	_isHalfMove = false;

	_moveBeat = 1;
	_curMoveBeat = 0;

	_idxX = idxX;
	_idxY = idxY;

	_posX = _idxX * TILE_SIZE;
	_posY = _idxY * TILE_SIZE;

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

	_gravity = 0;
	_jumpPower = 0;

	_move = DIRECITON_NONE;
	_direction = DIRECITON_NONE;

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
	_speed = TIMEMANAGER->getElapsedTime() * PLAYER_SPEED;
	_moveDistance = TILE_SIZE;

	switch (_direction)
	{
	case DIRECTION_LEFT:
		_posX -= _speed;
		_moveDistance -= _speed;
		if (_moveDistance < _speed)
		{
			horizonSet();
			_direction = DIRECITON_NONE;
		}
		break;
	case DIRECTION_RIGHT:
		_posX += _speed;
		_moveDistance -= _speed;
		if (_moveDistance < _speed)
		{
			horizonSet();
			_direction = DIRECITON_NONE;
		}
		break;
	case DIRECTION_UP:
		_posY -= _speed;
		_moveDistance -= _speed;
		if (_moveDistance < _speed)
		{
			verticalSet();
			_direction = DIRECITON_NONE;
		}
		break;
	case DIRECTION_DOWN:
		_posY += _speed;
		_moveDistance -= _speed;
		if (_moveDistance < _speed)
		{
			verticalSet();
			_direction = DIRECITON_NONE;
		}
		break;
	}
}

void enemy::jumpMoveEnemy()
{
	_speed = TIMEMANAGER->getElapsedTime() * PLAYER_SPEED;
	_moveDistance = TILE_SIZE;

	if (_isHalfMove)
	{
		switch (_direction)
		{
		case DIRECTION_LEFT:
			_moveDistance -= _speed;
			if (_moveDistance > TILE_SIZE / 2)
			{
				_posX -= _speed;
				_posZ -= _jumpPower * TIMEMANAGER->getElapsedTime();
				_jumpPower -= _gravity * TIMEMANAGER->getElapsedTime();
			}
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
			if (_moveDistance > TILE_SIZE / 2)
			{
				_posX += _speed;
				_posZ -= _jumpPower * TIMEMANAGER->getElapsedTime();
				_jumpPower -= _gravity * TIMEMANAGER->getElapsedTime();
			}
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
			if (_moveDistance > TILE_SIZE / 2)
			{
				_posY -= _speed;
				_posZ -= _jumpPower * TIMEMANAGER->getElapsedTime();
				_jumpPower -= _gravity * TIMEMANAGER->getElapsedTime();
			}
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
			if (_moveDistance > TILE_SIZE / 2)
			{
				_posY += _speed;
				_posZ -= _jumpPower * TIMEMANAGER->getElapsedTime();
				_jumpPower -= _gravity * TIMEMANAGER->getElapsedTime();
			}
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
	}
}

void enemy::attackEnemy(DIRECTION dir)
{
}

void enemy::hitEnemy(int damage)
{
}

void enemy::dieEnemy()
{
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
		}

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
		}

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
		}

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
		}

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
		}

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
		}

		OBJECTMANAGER->setTileIdx(this, _idxX, _idxY + 1);
	}

}

bool enemy::aStarLoad()
{
	player* _player = OBJECTMANAGER->getPlayer();

	int direction_X = _player->getIdxX() - _idxX;
	int direction_Y = _player->getIdxY() - _idxY;

	if (direction_X == -1)
	{
		direction_X = DIRECTION_LEFT;
		this->_direction = (DIRECTION)direction_X;
		attackEnemy(_direction);
		return true;
	} 
	else if (direction_X == 1)
	{
		direction_X = DIRECTION_RIGHT;
		this->_direction = (DIRECTION)direction_X;
		attackEnemy(_direction);
		return true;
	}
	else if (direction_Y == -1)
	{
		direction_Y = DIRECTION_UP;
		this->_direction = (DIRECTION)direction_Y;
		attackEnemy(_direction);
		return true;
	}
	else if(direction_Y == 1)
	{
		direction_Y = DIRECTION_DOWN;
		this->_direction = (DIRECTION)direction_Y;
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
			int nextIdx = tile->i * TILE_SIZE + tile->j;
			int nextIdxX = nextIdx / TILE_SIZE;
			int nextIdxY = nextIdx % TILE_SIZE;
			tempObj = OBJECTMANAGER->getCheckObj(nextIdxX, nextIdxY);

			if (tempObj == NULL)
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
				}
				return true;
			}
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

void enemy::constructionTile()
{
}

void enemy::initTile()
{
}

void enemy::addOpenList()
{
}

void enemy::addCloseList()
{
}

void enemy::calculateH()
{
}

void enemy::calculateF()
{
}

void enemy::checkArrive()
{
}

void enemy::soundAtt()
{
}

void enemy::soundHit()
{
}

void enemy::soundCry()
{
}

void enemy::soundDie()
{
}

void enemy::horizonSet()
{
}

void enemy::verticalSet()
{
}
