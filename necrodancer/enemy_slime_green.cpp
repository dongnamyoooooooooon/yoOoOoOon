#include "stdafx.h"
#include "enemy_slime_green.h"


enemy_slime_green::enemy_slime_green()
{
}


enemy_slime_green::~enemy_slime_green()
{
}

HRESULT enemy_slime_green::init(string imgName, int idxX, int idxY)
{
	enemy::init(imgName, idxX, idxY);

	_moveBeat = 1;
	_subX = 26;
	_subY = 36;
	_damage = 500;
	_heart = 1;
	_maxHeart = 1;

	aniSetUp();

	return S_OK;
}

void enemy_slime_green::release()
{
}

void enemy_slime_green::update()
{
	if (_isBeat)
	{
		_curMoveBeat++;
		aniPlay_Stand();
		
		if (_moveBeat == _curMoveBeat)
		{
			_curMoveBeat = 0;
			_moveDistance = TILE_SIZE;
			_jumpPower = 10.0f;
			_posZ = 0;
		}
		_isBeat = false;
	}

	if (_jumpPower >= -6.0f && _jumpPower != 0)
	{
		_posZ += _jumpPower;
		_jumpPower -= 1.2f;
	}
	else
	{
		_posZ = 0;
		_jumpPower = 0;
	}
}

void enemy_slime_green::render()
{
	if (_isSaw)
	{
		IMAGEMANAGER->findImage("enemy_shadow")->render(_posX - _subX, _posY - _subY - _posZ);
		if (_isLeft)
			_img->aniRenderReverseX(_posX - _subX, _posY - _subY - _posZ, _ani);
		else
			_img->aniRender(_posX - _subX, _posY - _subY - _posZ, _ani);
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

void enemy_slime_green::aniSetUp()
{
	KEYANIMANAGER->addAnimationType("enemy_slime_green");

	int stand[] = { 0,1,2,3 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_slime_green", "slime_green_stand", "enemy_slime_green", stand, 4, ANISPEED, true);

	int stand_shadow[] = { 4,5,6,7 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_slime_green", "slime_green_stand_shadow", "enemy_slime_green", stand_shadow, 4, ANISPEED, true);

	_ani = KEYANIMANAGER->findAnimation("enemy_slime_green", "slime_green_stand");
	_ani->start();
}

void enemy_slime_green::aniPlay_Stand()
{
	if (_isSaw)
	{
		//그림자이미지
		if (_isSight)
		{
			if (_hasLight)
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_slime_green", "slime_green_stand");
				_ani->start();
			}
			else
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_slime_green", "slime_green_stand_shadow");
				_ani->start();
			}
		}
		else
		{
			_ani = KEYANIMANAGER->findAnimation("enemy_slime_green", "slime_green_stand_shadow");
			_ani->start();
		}
	}
}
