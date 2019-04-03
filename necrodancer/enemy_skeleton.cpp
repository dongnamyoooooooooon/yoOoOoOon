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
	_subX = 26;
	_subY = 36;
	_damage = 1; 
	_heart = 1;
	_maxHeart = 1;


	aniSetUp();

	return S_OK;
}

void enemy_skeleton::release()
{
}

void enemy_skeleton::update()
{
	//aniPlay();
	jumpMoveEnemy();

	if (_isBeat)
	{
		_curMoveBeat++;
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
		_isBeat = false;
	}
}

void enemy_skeleton::render()
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
			IMAGEMANAGER->findImage("enemy_heart_empty")->render((_posX + 26) - (_maxHeart / 2) * 24 + 24 * i - 7, _posY - _subY - 24);
		}
		for (int i = 0; i < _heart; i++)
		{
			IMAGEMANAGER->findImage("enemy_heart")->render((_posX + 26) - (_maxHeart / 2) * 24 + 24 * i - 7, _posY - _subY - 24);
		}
	}
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

void enemy_skeleton::aniSetUp()
{
	KEYANIMANAGER->addAnimationType("enemy_skeleton");

	int stand[] = { 0,1,2,3 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_skeleton", "skeleton_stand", "enemy_skeleton", stand, 4, ANISPEED, true);

	int attack[] = { 4,5,6,7 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_skeleton", "skeleton_attack", "enemy_skeleton", attack, 4, ANISPEED, true);

	int stand_shadow[] = { 8,9,10,11 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_skeleton", "skeleton_stand_shadow", "enemy_skeleton", stand_shadow, 4, ANISPEED, true);

	int attack_shadow[] = { 12,13,14,15 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_skeleton", "skeleton_attack_shadow", "enemy_skeleton", attack_shadow, 4, ANISPEED, false);

	_ani = KEYANIMANAGER->findAnimation("enemy_skeleton", "skeleton_stand");
	_ani->start();


}

void enemy_skeleton::aniPlay_Attack()
{
	if (_isSaw)
	{
		//그림자이미지
		if (_isSight)
		{
			if (_hasLight)
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_skeleton", "skeleton_attack");
				_ani->start();
			}
			else
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_skeleton", "skeleton_attack_shadow");
				_ani->start();
			}
		}
		else
		{
			_ani = KEYANIMANAGER->findAnimation("enemy_skeleton", "skeleton_attack_shadow");
			_ani->start();
		}
	}
}

void enemy_skeleton::aniPlay_Stand()
{
	if (_isSaw)
	{
		//그림자이미지
		if (_isSight)
		{
			if (_hasLight)
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_skeleton", "skeleton_stand");
				_ani->start();
			}
			else
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_skeleton", "skeleton_stand_shadow");
				_ani->start();
			}
		}
		else
		{
			_ani = KEYANIMANAGER->findAnimation("enemy_skeleton", "skeleton_stand_shadow");
			_ani->start();
		}
	}
}
