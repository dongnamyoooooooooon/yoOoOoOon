#include "stdafx.h"
#include "enemy_skeleton_mage_yellow.h"


enemy_skeleton_mage_yellow::enemy_skeleton_mage_yellow()
{
}


enemy_skeleton_mage_yellow::~enemy_skeleton_mage_yellow()
{
}

HRESULT enemy_skeleton_mage_yellow::init(string imgName, int idxX, int idxY)
{
	enemy::init(imgName, idxX, idxY);

	_moveBeat = 2;
	_subX = 26;
	_subY = 36;
	_damage = 2;
	_heart = 2;
	_maxHeart = 2;

	aniSetUp();

	return S_OK;
}

void enemy_skeleton_mage_yellow::release()
{
}

void enemy_skeleton_mage_yellow::update()
{
	jumpMoveEnemy();

	if (_isBeat)
	{
		aniPlay_Stand();
		_curMoveBeat++;
		if (_moveBeat == _curMoveBeat)
		{
			_curMoveBeat = 0;
			if (windMagic())
			{
				aniPlay_Attack();
				OBJECTMANAGER->magicOn();
			}
			else
				aStarLoad();
		}
		_isBeat = false;
	}
}

void enemy_skeleton_mage_yellow::render()
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
			IMAGEMANAGER->findImage("enemy_heart_empty")->render((_posX + 5) - (_maxHeart / 2) * 24 + 24 * i - 7, _posY - _subY - 24);
		}
		for (int i = 0; i < _heart; i++)
		{
			IMAGEMANAGER->findImage("enemy_heart")->render((_posX + 5) - (_maxHeart / 2) * 24 + 24 * i - 7, _posY - _subY - 24);
		}
	}
}

void enemy_skeleton_mage_yellow::aniSetUp()
{
	KEYANIMANAGER->addAnimationType("enemy_skeleton_mage_yellow");

	int stand[] = { 0,1,5,6 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_skeleton_mage_yellow", "skeleton_mage_stand", "enemy_skeleton_mage_yellow", stand, 4, ANISPEED, true);

	int attack[] = { 2,3,4 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_skeleton_mage_yellow", "skeleton_mage_attack", "enemy_skeleton_mage_yellow", attack, 3, ANISPEED, true);

	int stand_shadow[] = { 7,8,12,13 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_skeleton_mage_yellow", "skeleton_mage_stand_shadow", "enemy_skeleton_mage_yellow", stand_shadow, 4, ANISPEED, true);

	int attack_shadow[] = { 9,10,11 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_skeleton_mage_yellow", "skeleton_mage_attack_shadow", "enemy_skeleton_mage_yellow", attack_shadow, 3, ANISPEED, false);

	_ani = KEYANIMANAGER->findAnimation("enemy_skeleton_mage_yellow", "skeleton_mage_stand");
	_ani->start();
}

void enemy_skeleton_mage_yellow::aniPlay_Attack()
{
	if (_isSaw)
	{
		//그림자이미지
		if (_isSight)
		{
			if (_hasLight)
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_skeleton_mage_yellow", "skeleton_mage_attack");
				_ani->start();
			}
			else
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_skeleton_mage_yellow", "skeleton_mage_attack_shadow");
				_ani->start();
			}
		}
		else
		{
			_ani = KEYANIMANAGER->findAnimation("enemy_skeleton_mage_yellow", "skeleton_mage_attack_shadow");
			_ani->start();
		}
	}
}

void enemy_skeleton_mage_yellow::aniPlay_Stand()
{
	if (_isSaw)
	{
		//그림자이미지
		if (_isSight)
		{
			if (_hasLight)
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_skeleton_mage_yellow", "skeleton_mage_stand");
				_ani->start();
			}
			else
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_skeleton_mage_yellow", "skeleton_mage_stand_shadow");
				_ani->start();
			}
		}
		else
		{
			_ani = KEYANIMANAGER->findAnimation("enemy_skeleton_mage_yellow", "skeleton_mage_stand_shadow");
			_ani->start();
		}
	}
}

bool enemy_skeleton_mage_yellow::windMagic()
{
	player* tempPlayer = OBJECTMANAGER->getPlayer();

	int pIdxX = tempPlayer->getIdxX();
	int pIdxY = tempPlayer->getIdxY();

	if (pIdxX - _idxX == 0)
	{
		if (pIdxY == _idxY + 2) //아래
		{
			if (OBJECTMANAGER->getCheckObj(_idxX, _idxY + 1) == NULL)
			{
				SOUNDMANAGER->play("sound_spell_wind");
				int playerX = tempPlayer->getPlayerPosX();
				int playerY = tempPlayer->getPlayerPosY();
				OBJECTMANAGER->setTileIdx(tempPlayer, _idxX, _idxY + 1);
				tempPlayer->setPlayerPos(playerX, playerY - 52);
				return true;
			}
		}
		else if (pIdxY == _idxY - 2) //위
		{
			if (OBJECTMANAGER->getCheckObj(_idxX, _idxY - 1) == NULL)
			{
				SOUNDMANAGER->play("sound_spell_wind");
				int playerX = tempPlayer->getPlayerPosX();
				int playerY = tempPlayer->getPlayerPosY();
				OBJECTMANAGER->setTileIdx(tempPlayer, _idxX, _idxY - 1);
				tempPlayer->setPlayerPos(playerX, playerY + 52);
				return true;
			}
		}
	}
	else if (pIdxY - _idxY == 0)
	{
		if (pIdxX == _idxX + 2)	//오른쪽
		{
			if (OBJECTMANAGER->getCheckObj(_idxX + 1, _idxY) == NULL)
			{
				SOUNDMANAGER->play("sound_spell_wind");
				int playerX = tempPlayer->getPlayerPosX();
				int playerY = tempPlayer->getPlayerPosY();
				OBJECTMANAGER->setTileIdx(tempPlayer, _idxX + 1, _idxY);
				tempPlayer->setPlayerPos(playerX - 52, playerY);
				return true;
			}
		}
		else if (pIdxX == _idxX - 2)
		{
			if (OBJECTMANAGER->getCheckObj(_idxX - 1, _idxY) == NULL)
			{
				SOUNDMANAGER->play("sound_spell_wind");
				int playerX = tempPlayer->getPlayerPosX();
				int playerY = tempPlayer->getPlayerPosY();
				OBJECTMANAGER->setTileIdx(tempPlayer, _idxX - 1, _idxY);
				tempPlayer->setPlayerPos(playerX + 52, playerY);
				return true;
			}
		}
	}
	return false;
}
