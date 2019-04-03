#include "stdafx.h"
#include "enemy_slime_blue.h"


enemy_slime_blue::enemy_slime_blue()
{
}


enemy_slime_blue::~enemy_slime_blue()
{
}

HRESULT enemy_slime_blue::init(string imgName, int idxX, int idxY)
{
	enemy::init(imgName, idxX, idxY);

	_moveBeat = 2;
	_heart = 2;
	_maxHeart = 2;
	_damage = 1;
	_subX = 26;
	_subY = 36;

	_enemyAni = "enemy_slime_blue";

	aniSetUp();

	return S_OK;
}

void enemy_slime_blue::release()
{
}

void enemy_slime_blue::update()
{
	

	jumpMoveEnemy();

	if (_isBeat)
	{
		_curMoveBeat++;
		aniPlay_Stand();

		if (_moveBeat == _curMoveBeat)
		{
			aniPlay_Attack();
			patternMove();
			_curMoveBeat = 0;
		}
		_isBeat = false;
	}
}

void enemy_slime_blue::render()
{
	if (_isSaw)
	{
		IMAGEMANAGER->findImage("enemy_shadow")->render(_posX - _subX, _posY - _subY + _posZ);
		if (_isLeft)
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

void enemy_slime_blue::aniSetUp()
{
	KEYANIMANAGER->addAnimationType("enemy_slime_blue");

	int stand[] = { 0,1,2,3 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_slime_blue", "slime_blue_stand", "enemy_slime_blue", stand, 4, ANISPEED, true);

	int attack[] = { 4,5,6,7 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_slime_blue", "slime_blue_attack", "enemy_slime_blue", attack, 4, ANISPEED, true);

	int stand_shadow[] = { 8,9,10,11 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_slime_blue", "slime_blue_stand_shadow", "enemy_slime_blue", stand_shadow, 4, ANISPEED, true);

	int attack_shadow[] = { 12,13,14,15 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_slime_blue", "slime_blue_attack_shadow", "enemy_slime_blue", attack_shadow, 4, ANISPEED, false);

	_ani = KEYANIMANAGER->findAnimation("enemy_slime_blue", "slime_blue_stand");
	_ani->start();

}

void enemy_slime_blue::aniPlay_Attack()
{
	if (_isSaw)
	{
		//그림자이미지
		if (_isSight)
		{
			if (_hasLight)
			{
				_ani = KEYANIMANAGER->findAnimation(_enemyAni, "slime_blue_attack");
				_ani->start();
			}
			else
			{
				_ani = KEYANIMANAGER->findAnimation(_enemyAni, "slime_blue_attack_shadow");
				_ani->start();
			}
		}
		else
		{
			_ani = KEYANIMANAGER->findAnimation(_enemyAni, "slime_blue_attack_shadow");
			_ani->start();
		}
	}
}

void enemy_slime_blue::aniPlay_Stand()
{
	if (_isSaw)
	{
		//그림자이미지
		if (_isSight)
		{
			if (_hasLight)
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_slime_blue", "slime_blue_stand");
				_ani->start();
			}
			else
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_slime_blue", "slime_blue_stand_shadow");
				_ani->start();
			}
		}
		else
		{
			_ani = KEYANIMANAGER->findAnimation("enemy_slime_blue", "slime_blue_stand_shadow");
			_ani->start();
		}
	}
}
