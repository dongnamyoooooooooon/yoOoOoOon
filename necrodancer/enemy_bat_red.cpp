#include "stdafx.h"
#include "enemy_bat_red.h"


enemy_bat_red::enemy_bat_red()
{
}


enemy_bat_red::~enemy_bat_red()
{
}

HRESULT enemy_bat_red::init(string imgName, int idxX, int idxY)
{
	enemy::init(imgName, idxX, idxY);

	_moveBeat = 1;
	_heart = 4;
	_maxHeart = 4;
	_damage = 2;
	_subX = 0;
	_subY = 26;

	aniSetUp();

	return S_OK;
}

void enemy_bat_red::release()
{
}

void enemy_bat_red::update()
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

void enemy_bat_red::render()
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
			IMAGEMANAGER->findImage("enemy_heart_empty")->render((_posX + 26) - (_maxHeart / 2) * 24 + 24 * i - 7, _posY - _subY - 24);
		}
		for (int i = 0; i < _heart; i++)
		{
			IMAGEMANAGER->findImage("enemy_heart")->render((_posX + 26) - (_maxHeart / 2) * 24 + 24 * i - 7, _posY - _subY - 24);
		}
	}

	WCHAR str[128];

	swprintf_s(str, L"%d", _moveDistance);
	D2DMANAGER->drawText(str, CAMERA->getPosX() + 10, CAMERA->getPosY() + 300, 60, RGB(255, 0, 255));
}

void enemy_bat_red::aniSetUp()
{
	KEYANIMANAGER->addAnimationType("enemy_bat_red");

	int stand[] = { 0,1,2,3 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_bat_red", "bat_red_stand", "enemy_bat_red", stand, 4, ANISPEED, true);

	int stand_shadow[] = { 4,5,6,7 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_bat_red", "bat_red_stand_shadow", "enemy_bat_red", stand_shadow, 4, ANISPEED, true);

	_ani = KEYANIMANAGER->findAnimation("enemy_bat_red", "bat_red_stand");
	_ani->start();
}

void enemy_bat_red::aniPlay_Stand()
{
	if (_isSaw)
	{
		//그림자이미지
		if (_isSight)
		{
			if (_hasLight)
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_bat_red", "bat_red_stand");
				_ani->start();
			}
			else
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_bat_red", "bat_red_stand_shadow");
				_ani->start();
			}
		}
		else
		{
			_ani = KEYANIMANAGER->findAnimation("enemy_bat_red", "bat_red_stand_shadow");
			_ani->start();
		}
	}
}
