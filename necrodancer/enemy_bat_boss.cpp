#include "stdafx.h"
#include "enemy_bat_boss.h"


enemy_bat_boss::enemy_bat_boss()
{
}


enemy_bat_boss::~enemy_bat_boss()
{
}

HRESULT enemy_bat_boss::init(string imgName, int idxX, int idxY)
{
	enemy::init(imgName, idxX, idxY);

	_moveBeat = 2;
	_heart = 3;
	_maxHeart = 3;
	_damage = 4;
	_subX = 36;
	_subY = 46;

	aniSetUp();

	return S_OK;
}

void enemy_bat_boss::release()
{
}

void enemy_bat_boss::update()
{
	moveEnemy();

	if (_isBeat)
	{
		_curMoveBeat++;
		aniPlay_Stand();

		if (_moveBeat == _curMoveBeat)
		{
			rendomMove();
			_curMoveBeat = 0;
		}
		_isBeat = false;
	}
}

void enemy_bat_boss::render()
{
	if (_isSaw)
	{
		if (_isLeft)
			_img->aniRenderReverseX(_posX - _subX, _posY - _subY, _ani);
		else
			_img->aniRender(_posX - _subX, _posY - _subY, _ani);
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

void enemy_bat_boss::aniSetUp()
{
	KEYANIMANAGER->addAnimationType("enemy_bat_miniboss");

	int stand[] = { 0,1,2,3 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_bat_miniboss", "bat_miniboss_stand", "enemy_bat_miniboss", stand, 4, ANISPEED, true);

	int stand_shadow[] = { 4,5,6,7 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_bat_miniboss", "bat_miniboss_shadow", "enemy_bat_miniboss", stand_shadow, 4, ANISPEED, true);

	_ani = KEYANIMANAGER->findAnimation("enemy_bat_miniboss", "bat_miniboss_stand");
	_ani->start();
}

void enemy_bat_boss::aniPlay_Stand()
{
	if (_isSaw)
	{
		//그림자이미지
		if (_isSight)
		{
			if (_hasLight)
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_bat_miniboss", "bat_miniboss_stand");
				_ani->start();
			}
			else
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_bat_miniboss", "bat_miniboss_shadow");
				_ani->start();
			}
		}
		else
		{
			_ani = KEYANIMANAGER->findAnimation("enemy_bat_miniboss", "bat_miniboss_shadow");
			_ani->start();
		}
	}
}
