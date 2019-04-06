#include "stdafx.h"
#include "enemy_banshee.h"


enemy_banshee::enemy_banshee()
{
}


enemy_banshee::~enemy_banshee()
{
}

HRESULT enemy_banshee::init(string imgName, int idxX, int idxY)
{
	enemy::init(imgName, idxX, idxY);

	_moveBeat = 1;
	_subX = 38;
	_subY = 68;
	_damage = 2;
	_heart = 3;
	_maxHeart = 3;

	_isLeft = true;
	
	aniSetUp();


	return S_OK;
}

void enemy_banshee::release()
{
}

void enemy_banshee::update()
{
	if (_heart == _maxHeart) aniPlay_Stand();
	else aniPlay_Attack();

	moveEnemy();

	if (_isBeat && _moveDistance == 0)
	{
		_curMoveBeat++;
		if (_curMoveBeat == _moveBeat)
		{
			_curMoveBeat = 0;
			aStarLoad();
		}
		_isBeat = 0;
	}

}

void enemy_banshee::render()
{
	if (_isSaw)
	{
		IMAGEMANAGER->findImage("enemy_shadow")->render(_posX - 24, _posY - 26 + _posZ);
		if (!_isLeft)
			_img->aniRenderReverseX(_posX - _subX, _posY - _subY + _posZ, _ani);
		else
			_img->aniRender(_posX - _subX, _posY - _subY + _posZ, _ani);
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

void enemy_banshee::aniSetUp()
{
	KEYANIMANAGER->addAnimationType("enemy_banshee");

	int stand[] = { 0,1,2,3 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_banshee", "banshee_stand", "enemy_banshee", stand, 4, ANISPEED, true);

	int attack[] = { 4,5,6,7 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_banshee", "banshee_attack", "enemy_banshee", attack, 4, ANISPEED, true);

	int stand_shadow[] = { 8,9,10,11 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_banshee", "banshee_stand_shadow", "enemy_banshee", stand_shadow, 4, ANISPEED, true);

	int attack_shadow[] = { 12,13,14,15 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_banshee", "banshee_attack_shadow", "enemy_banshee", attack_shadow, 4, ANISPEED, false);

	_ani = KEYANIMANAGER->findAnimation("enemy_banshee", "banshee_stand");
	_ani->start();
}

void enemy_banshee::aniPlay_Stand()
{
	if (_isSaw)
	{
		//그림자이미지
		if (_isSight)
		{
			if (_hasLight)
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_banshee", "banshee_stand");
				_ani->start();
			}
			else
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_banshee", "banshee_stand_shadow");
				_ani->start();
			}
		}
		else
		{
			_ani = KEYANIMANAGER->findAnimation("enemy_banshee", "banshee_stand_shadow");
			_ani->start();
		}
	}
}

void enemy_banshee::aniPlay_Attack()
{
	if (_isSaw)
	{
		//그림자이미지
		if (_isSight)
		{
			if (_hasLight)
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_banshee", "banshee_attack");
				_ani->start();
			}
			else
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_banshee", "banshee_attack_shadow");
				_ani->start();
			}
		}
		else
		{
			_ani = KEYANIMANAGER->findAnimation("enemy_banshee", "banshee_attack_shadow");
			_ani->start();
		}
	}
}

void enemy_banshee::hitEnemy(int damage)
{
	SOUNDMANAGER->setBgmVolume(0.0f);
	SOUNDMANAGER->play("sound_banshee_loop");

	player* tempPlayer = OBJECTMANAGER->getPlayer();

	PLAYER_STATE tempState = tempPlayer->getAttDir();

	/*int tempX = _idxX - tempPlayer->getIdxX();
	int tempY = _idxY - tempPlayer->getIdxY();*/
		
	
	_direction = (DIRECTION)tempState;

	if (_direction == DIRECTION_LEFT)
	{
		_moveDistance = TILE_SIZE;
		OBJECTMANAGER->setTileIdx(this, _idxX - 1, _idxY);
	}
	else if (_direction == DIRECTION_RIGHT)
	{
		_moveDistance = TILE_SIZE;
		OBJECTMANAGER->setTileIdx(this, _idxX + 1, _idxY);
	}
	else if (_direction == DIRECTION_UP)
	{
		_moveDistance = TILE_SIZE;
		OBJECTMANAGER->setTileIdx(this, _idxX, _idxY - 1);
	}
	else if (_direction == DIRECTION_DOWN)
	{
		_moveDistance = TILE_SIZE;
		OBJECTMANAGER->setTileIdx(this, _idxX, _idxY + 1);
	}
	_isDrawHP = true;
	_heart -= damage;

	if (_heart <= 0) this->dieEnemy();


	//if (tempX < 0) //왼
	//{
	//	_direction = DIRECTION_LEFT;
	//	_moveDistance = TILE_SIZE;
	//	OBJECTMANAGER->setTileIdx(this, _idxX - 1, _idxY);
	//}
	//else if (tempX > 0)
	//{
	//	_direction = DIRECTION_RIGHT;
	//	_moveDistance = TILE_SIZE;
	//	OBJECTMANAGER->setTileIdx(this, _idxX + 1, _idxY);
	//}
	//else if (tempY < 0)
	//{
	//	_direction = DIRECTION_UP;
	//	_moveDistance = TILE_SIZE;
	//	OBJECTMANAGER->setTileIdx(this, _idxX, _idxY - 1);
	//}
	//else if (tempY > 0)
	//{
	//	_direction = DIRECTION_DOWN;
	//	_moveDistance = TILE_SIZE;
	//	OBJECTMANAGER->setTileIdx(this, _idxX, _idxY + 1);
	//}
	

	
}
