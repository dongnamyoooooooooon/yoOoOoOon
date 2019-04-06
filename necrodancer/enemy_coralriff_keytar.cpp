#include "stdafx.h"
#include "enemy_coralriff_keytar.h"


enemy_coralriff_keytar::enemy_coralriff_keytar()
{
}


enemy_coralriff_keytar::~enemy_coralriff_keytar()
{
}

HRESULT enemy_coralriff_keytar::init(string imgName, int idxX, int idxY)
{
	enemy::init(imgName, idxX, idxY);


	_damage = 3;
	_heart = 1;
	_maxHeart = 1;
	_moveBeat = 17;

	_saveX = _idxX;
	_saveY = _idxY;

	if (idxX < 9)
	{
		_isLeft = true;
		_subX = 26;
		_subY = 96;
		_checkPos = true;
	}
	else
	{
		_isLeft = false;
		_subX = 16;
		_subY = 96;
		_checkPos = false;
	}

	_isSaw = true;
	_hasLight = true;
	_isSight = true;

	aniSetUp();

	return S_OK;
}
void enemy_coralriff_keytar::release()
{
}

void enemy_coralriff_keytar::update()
{
	if (!OBJECTMANAGER->getBossAlive())
	{
		OBJECTMANAGER->deleteObject(this);
	}

	moveEnemy();
	if (OBJECTMANAGER->getIsEnter())
	{
		if (_isBeat)
		{
			if (_heart > 0)
			{
				_isBeat = false;
				_beatCount++;
				if (_beatCount >= 53)
				{
					_curMoveBeat++;
					_shakeVal = 3;
					OBJECTMANAGER->setTileFloor(_posX / TILE_SIZE, _posY / TILE_SIZE);
					if (_curMoveBeat == 2)
					{
						aStarLoad();
						_shakeVal = 0;
						if (_beatCount >= 1000) _beatCount = 54;
						_curMoveBeat = 0;
					}
				}
				else
				{
					if (_moveBeat <= _beatCount)
					{
						player* tempPlayer = OBJECTMANAGER->getPlayer();
						if (_moveBeat == _beatCount)
						{
							_shakeVal = 3;
						}
						else if ((_moveBeat == _beatCount - 1) || (_moveBeat == _beatCount - 2))
						{
							_shakeVal = 0;
							_isShowShadow = true;
						}
						else if (_moveBeat == _beatCount - 3)
						{
							_isShowShadow = false;
							if (_isLeft)
							{
								OBJECTMANAGER->setTileIdx(this, tempPlayer->getIdxX() + respawnX_left, tempPlayer->getIdxY() + respawnY_left);
								_posX = ((tempPlayer->getIdxX() + respawnX_left) * 52) + 26;
								_posY = ((tempPlayer->getIdxY() + respawnY_left) * 52) + 26;
								OBJECTMANAGER->setTileFloor(_posX / TILE_SIZE, _posY / TILE_SIZE);
							}
							else if (!_isLeft)
							{
								OBJECTMANAGER->setTileIdx(this, tempPlayer->getIdxX() + respawnX_right, tempPlayer->getIdxY() + respawnY_right);
								_posX = ((tempPlayer->getIdxX() + respawnX_right) * 52) + 26;
								_posY = ((tempPlayer->getIdxY() + respawnY_right) * 52) + 26;
								OBJECTMANAGER->setTileFloor(_posX / TILE_SIZE, _posY / TILE_SIZE);
							}
						}
						else if ((_moveBeat == _beatCount - 4) || (_moveBeat == _beatCount - 5))
						{
							_shakeVal = 3;
							if ((tempPlayer->getIdxX() == _idxX - 1 && tempPlayer->getIdxY() == _idxY) ||
								(tempPlayer->getIdxX() == _idxX + 1 && tempPlayer->getIdxY() == _idxY) ||
								(tempPlayer->getIdxX() == _idxX && tempPlayer->getIdxY() == _idxY - 1) ||
								(tempPlayer->getIdxX() == _idxX && tempPlayer->getIdxY() == _idxY + 1))
							{
								if (!OBJECTMANAGER->getPlayer()->getIsHit())
								{
									if (_isLeft)
									{
										_direction = DIRECTION_LEFT;
										attackEnemy(_direction);
									}
									else if (!_isLeft)
									{
										_direction = DIRECTION_RIGHT;
										attackEnemy(_direction);
									}
									OBJECTMANAGER->getPlayer()->setIsHit(true);
								}
							}

						}
						else if (_moveBeat == _beatCount - 6)
						{
							_shakeVal = 0;
						}
						else if (_moveBeat == _beatCount - 7)
						{
							OBJECTMANAGER->setTileIdx(this, _saveX, _saveY);
							_posX = _saveX * TILE_SIZE + 26;
							_posY = _saveY * TILE_SIZE + 26;
							_moveBeat += 24;
							OBJECTMANAGER->getPlayer()->setIsHit(false);
						}
					}
				}
			}
		}
		if (_shakeVal != 0)
		{
			if (_heart <= 0)
			{
				_shakeVal = 0;
			}
			else
			{
				_shakeCount++;
				if (_shakeCount >= 3)
				{
					_shakeCount = 0;
					_shakeVal == 3 ? _shakeVal = -3 : _shakeVal = 3;
				}
			}
		}
	}
}

void enemy_coralriff_keytar::render()
{
	if (OBJECTMANAGER->getBossAlive())
	{
		if (_heart > 0)
		{
			if (!_isShowShadow)
			{

				if (_isSaw)
				{
					//IMAGEMANAGER->findImage("enemy_shadow")->render(_posX - 24, _posY - 26 + _posZ);
					if (!_isLeft)
						_img->aniRenderReverseX(_posX - _subX + _shakeVal, _posY - _subY + _posZ, _ani);
					else
						_img->aniRender(_posX - _subX + _shakeVal, _posY - _subY + _posZ, _ani);
				}
			}
			else if (_isShowShadow)
			{
				IMAGEMANAGER->findImage("boss_shadow")->render(_posX - 15, _posY - 10);
			}
		}
		else
		{
			if (_isSaw)
			{
				//IMAGEMANAGER->findImage("enemy_shadow")->render(_posX - 24, _posY - 26 + _posZ);
				if (!_isLeft)
					_img->aniRenderReverseX(_posX - _subX, _posY - _subY, _ani);
				else
					_img->aniRender(_posX - _subX, _posY - _subY, _ani);
			}
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
}

void enemy_coralriff_keytar::aniSetUp()
{
	KEYANIMANAGER->addAnimationType("enemy_coralriff_keytar");

	int stand[] = { 0,1,2,3 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_coralriff_keytar", "coralriff_keytar_stand", "enemy_coralriff_keytar", stand, 4, ANISPEED, true);

	int stand_shadow[] = { 4,5,6,7 };
	KEYANIMANAGER->addArrayFrameAnimation("enemy_coralriff_keytar", "coralriff_keytar_stand_shadow", "enemy_coralriff_keytar", stand, 4, ANISPEED, true);

	_ani = KEYANIMANAGER->findAnimation("enemy_coralriff_keytar", "coralriff_keytar_stand");
	_ani->start();
}

void enemy_coralriff_keytar::aniPlay_Stand()
{
	if (_isSaw)
	{
		//그림자이미지
		if (_isSight)
		{
			if (_hasLight)
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_coralriff_keytar", "coralriff_keytar_stand");
				_ani->start();
			}
			else
			{
				_ani = KEYANIMANAGER->findAnimation("enemy_coralriff_keytar", "coralriff_keytar_stand_shadow");
				_ani->start();
			}
		}
		else
		{
			_ani = KEYANIMANAGER->findAnimation("enemy_coralriff_keytar", "coralriff_keytar_stand_shadow");
			_ani->start();
		}
	}
}

void enemy_coralriff_keytar::hitEnemy(int damage)
{

	soundHit();
	_isDrawHP = true;
	_heart -= damage;

	if (_heart <= 0)
	{
		soundDie();
		OBJECTMANAGER->grooveChain();
		_isDrawHP = false;
		int idxX;
		int idxY;
		if (_checkPos)
		{
			idxX = 3;
			idxY = 7;
			_volume = 0.5f;
		}
		else if (!_checkPos)
		{
			idxX = 15;
			idxY = 7;
			_volume = 0.5f;
		}
		SOUNDMANAGER->setKeytarVolume("boss_keytar", _volume);
		OBJECTMANAGER->setTileIdx(this, idxX, idxY);
		if (_checkPos)
		{
			_posX = _idxX * TILE_SIZE + 20;
			_posY = _idxY * TILE_SIZE;
		}
		else if (!_checkPos)
		{
			_posX = _idxX * TILE_SIZE + 20;
			_posY = _idxY * TILE_SIZE;
		}
	}
}
