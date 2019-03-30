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
				if(_isLeft) _img->frameRenderReverseX(_posX - _subX, _posY - _subY + _jumpPower, _frameX, 0);
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
	if(_count % 10 == 0)
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

	if (_direction == DIRECTION_LEFT)
		parentObj* obj = OBJECTMANAGER->getCheckObj(_idxX - 1, _idxY);
	else if (_direction == DIRECTION_RIGHT)
		parentObj* obj = OBJECTMANAGER->getCheckObj(_idxX + 1, _idxY);
	else if (_direction == DIRECTION_UP)
		parentObj* obj = OBJECTMANAGER->getCheckObj(_idxX, _idxY - 1);
	else if (_direction == DIRECTION_DOWN)
		parentObj* obj = OBJECTMANAGER->getCheckObj(_idxX, _idxY + 1);


	GameObject * obj = OBJECTMANAGER->GetIsThereObj(m_pos + m_move);
	OBJECTKIND objKind;

	if (obj != NULL)
	{
		objKind = obj->GetObjKind();

		if (objKind == OBJ_PLAYER)
			Attcked(m_move);

		m_move = M_NONE;
		moveCount = 0;
	}

	OBJECTMANAGER->SetTilePos(this, m_pos + m_move);

}

void enemy::patternMove()
{
}

bool enemy::aStarLoad()
{
	return false;
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
