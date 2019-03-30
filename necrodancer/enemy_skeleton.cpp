#include "stdafx.h"
#include "enemy_skeleton.h"


enemy_skeleton::enemy_skeleton()
{
}


enemy_skeleton::~enemy_skeleton()
{
}

HRESULT enemy_skeleton::init(string imgName, int idxX, int idxY)
{
	enemy::init(imgName, idxX, idxY);
	
	_moveBeat = 2;
	_subX = 0;
	_subY = 26;
	_damage = 1;
	_heart = 1;
	_maxHeart = 1;

	return S_OK;
}

void enemy_skeleton::release()
{
}

void enemy_skeleton::update()
{
	aniPlay();
	jumpMoveEnemy();

	/*if (!_isBeat)
	{*/
		_curMoveBeat++;
		if (_moveBeat == _curMoveBeat)
		{
			_curMoveBeat = 0;
			aStarLoad();
		}
	//	_isBeat = true;
	//}

	if (KEYMANAGER->isOnceKeyDown(VK_F3)) _isBeat = false;
}

void enemy_skeleton::render()
{
	enemy::render();
}

void enemy_skeleton::aniPlay()
{
	_count++;

	if (_count % 4 == 0)
	{
		if (_curMoveBeat == 0)
		{
			_frameX++;
			if (_frameX >= 8) _frameX = 0;
		}
		else
		{
			_frameX++;
			if (_frameX >= 8) _frameX = 0;
		}

	}
}
