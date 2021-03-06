#include "stdafx.h"
#include "player.h"
#include "weapon_dagger_basic.h"
#include "shovel_basic.h"


player::player()
{
}


player::~player()
{
}

HRESULT player::init(UINT idx_X, UINT idx_Y)
{
	_tileX = idx_X;
	_tileY = idx_Y;
	_idxX = idx_X;
	_idxY = idx_Y;
	_posX = _tileX * 52 + 26;
	_posY = _tileY * 52 + 26;
	_posZ = 0;
	_playerState = PLAYER_STATE_NONE;
	_moveDistance = 0;
	_jumpPower = 0;
	_gravity = GRAVETY;

	_playerHead = "player_head";
	_playerBody = "player_body";
	_playerLute = "player_body_lute";

	//boolean
	_isLeft = false;

	_playerStat = { _playerStat.heart, _playerStat.maxHeart, };

	_heartBeat = 0;
	_heartBeatCount = 0;


	initEquipUI();
	initItem();
	playerAniSetUp();

	return S_OK;
}

void player::release()
{
	SAFE_DELETE(_playerWeapon);
	SAFE_DELETE(_playerArmor);
	SAFE_DELETE(_playerShovel);
	SAFE_DELETE(_playerTorch);
	SAFE_DELETE(_playerBomb);
	SAFE_DELETE(_playerItem);
	SAFE_DELETE(_playerFootWear);
	SAFE_DELETE(_playerHeadWear);
}

void player::update()
{
	KEYANIMANAGER->update(_playerHead);
	KEYANIMANAGER->update(_playerBody);

	keyUpdate();

	layCast();

	if (_isUseShovel)
	{
		_count++;
		if (_count > 10)
		{
			_isUseShovel = false;
			_count = 0;
		}
	}
}

void player::render()
{
	drawBody();
	drawHead();
	drawShadow();
	//layCast();
	drawItemHint();


	/*WCHAR temp[128];
	swprintf_s(temp, L"%d", _playerStat.attack);
	D2DMANAGER->drawText(temp, CAMERA->getPosX() + WINSIZEX - 100, CAMERA->getPosY() + 150, 15, RGB(0, 255, 255));
	swprintf_s(temp, L"%d", _playerStat.attackCount);
	D2DMANAGER->drawText(temp, CAMERA->getPosX() + WINSIZEX - 100, CAMERA->getPosY() + 180, 15, RGB(0, 255, 255));
	swprintf_s(temp, L"%d", _playerStat.defence);
	D2DMANAGER->drawText(temp, CAMERA->getPosX() + WINSIZEX - 100, CAMERA->getPosY() + 210, 15, RGB(0, 255, 255));
	swprintf_s(temp, L"%d", _playerStat.shovelPower);
	D2DMANAGER->drawText(temp, CAMERA->getPosX() + WINSIZEX - 100, CAMERA->getPosY() + 240, 15, RGB(0, 255, 255));
	swprintf_s(temp, L"%d", _playerStat.torchLight);
	D2DMANAGER->drawText(temp, CAMERA->getPosX() + WINSIZEX - 100, CAMERA->getPosY() + 260, 15, RGB(0, 255, 255));*/
}

void player::playerDead()
{
	_playerStat.isLive = false;
	//사운드설정
	OBJECTMANAGER->setIsPlayerAlive();
}

void player::layCast()
{
	OBJECTMANAGER->initLight();

	float	bright = 0;
	int		tempVal = 0;
	float	sightMax = 6.0f;
	float	currentSight = 0.0f;

	_playerX = (float)_idxX;
	_playerY = (float)_idxY;

	_layValue = 0;
	_layMax = (float)_playerStat.torchLight - 0.25;

	_radius = 0;
	_angle = (12.0f * PI) / 180.0f;

	if (_playerTorch != NULL)
	{
		_layMax += (float)_playerTorch->getAppliedValue();
		tempVal = _playerTorch->getAppliedValue();
	}

	while (_radius < 2 * PI)
	{
		if (KEYMANAGER->isStayKeyDown(VK_F5))
		{
			D2DMANAGER->drawLine(RGB(0, 255, 255), this->_posX + 26, this->_posY + 26,
				this->_posX + 26 + _layValue * cos(_radius) * TILE_SIZE,
				this->_posY + 26 + _layValue * (-sin(_radius)) * TILE_SIZE);
		}

		if (_layValue > _layMax) bright = 0;
		else					 bright = _layValue;

		if (currentSight > sightMax)
		{
			currentSight = 0;
			bright = 0;
			_layValue = 0;
			_radius += _angle;
		}

		_subX = _playerX + currentSight * cos(_radius) + 0.5;
		_subY = _playerY + currentSight * (-sin(_radius)) + 0.5;

		if (_subX < 0) _subX = 0;
		if (_subY < 0) _subY = 0;

		if (_playerX < 0 || _playerY < 0)
		{
			currentSight = sightMax + 0.1f;
			continue;
		}

		int comValX = _subX - _playerX;
		if (comValX < 0) comValX *= -1;
		int comValY = _subY - _playerY;
		if (comValY < 0) comValY *= -1;

		int tempResult;
		if (comValX > comValY) tempResult = comValX;
		else					tempResult = comValY;

		tempResult = comValX + comValY;

		parentObj* obj = OBJECTMANAGER->getCheckObj(_subX, _subY);
		parentObj* floorObj = OBJECTMANAGER->getCheckFloor(_subX, _subY);

		if (obj != NULL)
		{
			if (obj->getIsSight() == false)
			{
				if (tempResult <= 2 + tempVal)
				{
					obj->setHasLight(true);
					obj->setIsSaw();
				}
				obj->setIsSight(true);
			}

			if (obj->getObjType() == OBJECT_TYPE_WALL)
			{
				if (obj->getImgName() == IMAGE_NAME[IMAGE_NAME_DOOR_01] || obj->getImgName() == IMAGE_NAME[IMAGE_NAME_DOOR_02])
				{
					if (floorObj->getIsSight() == false)
					{
						if (tempResult <= 2 + tempVal)
						{
							floorObj->setHasLight(true);
							floorObj->setIsSaw();
						}
						floorObj->setIsSight(true);
					}
				}

				_layValue = 0;
				currentSight = 0;
				_radius += _angle;

				continue;
			}
		}

		if (floorObj != NULL)
		{
			if (floorObj->getIsSight() == false)
			{
				if (tempResult <= 2 + tempVal)
				{
					floorObj->setHasLight(true);
					floorObj->setIsSaw();
				}
				floorObj->setIsSight(true);
			}
		}

		_layValue += 0.25f;
		currentSight += 0.25f;
	}



}

void player::playerAniSetUp()
{
	KEYANIMANAGER->addAnimationType(_playerHead);
	KEYANIMANAGER->addAnimationType(_playerBody);

	//머리

	//오른쪽
	int right_head[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	KEYANIMANAGER->addArrayFrameAnimation(_playerHead, "right_head", _playerHead.c_str(), right_head, 8, ANISPEED, true);


	//몸

	//오른쪽
	int right_body_noArmor[] = { 0, 1, 2, 3 };
	KEYANIMANAGER->addArrayFrameAnimation(_playerBody, ARMOR_NAME[ITEM_ARMOR_NONE], _playerBody.c_str(), right_body_noArmor, 4, ANISPEED, true);

	int right_body_leather[] = { 4, 5, 6, 7 };
	KEYANIMANAGER->addArrayFrameAnimation(_playerBody, ARMOR_NAME[ITEM_ARMOR_LEATHER], _playerBody.c_str(), right_body_leather, 4, ANISPEED, true);

	int right_body_chainmail[] = { 8, 9, 10, 11 };
	KEYANIMANAGER->addArrayFrameAnimation(_playerBody, ARMOR_NAME[ITEM_ARMOR_CHAINMAIL], _playerBody.c_str(), right_body_chainmail, 4, ANISPEED, true);

	int right_body_platemail[] = { 12, 13, 14, 15 };
	KEYANIMANAGER->addArrayFrameAnimation(_playerBody, ARMOR_NAME[ITEM_ARMOR_PLATEMAIL], _playerBody.c_str(), right_body_platemail, 4, ANISPEED, true);

	int right_body_heavyplate[] = { 16, 17, 18, 19 };
	KEYANIMANAGER->addArrayFrameAnimation(_playerBody, ARMOR_NAME[ITEM_ARMOR_HEAVYPLATE], _playerBody.c_str(), right_body_heavyplate, 4, ANISPEED, true);

	int right_body_karade[] = { 20, 21, 22, 23 };
	KEYANIMANAGER->addArrayFrameAnimation(_playerBody, ARMOR_NAME[ITEM_ARMOR_KARADE], _playerBody.c_str(), right_body_karade, 4, ANISPEED, true);

	int right_body_obsidian[] = { 24, 25, 26, 27 };
	KEYANIMANAGER->addArrayFrameAnimation(_playerBody, ARMOR_NAME[ITEM_ARMOR_OBSIDIAN], _playerBody.c_str(), right_body_obsidian, 4, ANISPEED, true);

	int right_body_obsidian_X2[] = { 28, 29, 30, 31 };
	KEYANIMANAGER->addArrayFrameAnimation(_playerBody, ARMOR_NAME[ITEM_ARMOR_OBSIDIAN_X2], _playerBody.c_str(), right_body_obsidian_X2, 4, ANISPEED, true);

	int right_body_obsidian_X3[] = { 32, 33, 34, 35 };
	KEYANIMANAGER->addArrayFrameAnimation(_playerBody, ARMOR_NAME[ITEM_ARMOR_OBSIDIAN_X3], _playerBody.c_str(), right_body_obsidian_X3, 4, ANISPEED, true);

	int right_body_glass[] = { 36, 37, 38, 39 };
	KEYANIMANAGER->addArrayFrameAnimation(_playerBody, ARMOR_NAME[ITEM_ARMOR_GLASS], _playerBody.c_str(), right_body_glass, 4, ANISPEED, true);

	int lute_right_body_noArmor[] = { 0, 1, 2, 3 };
	KEYANIMANAGER->addArrayFrameAnimation(_playerBody, ARMOR_NAME[ITEM_ARMOR_NONE], _playerLute.c_str(), lute_right_body_noArmor, 4, ANISPEED, true);

	int lute_right_body_leather[] = { 4, 5, 6, 7 };
	KEYANIMANAGER->addArrayFrameAnimation(_playerBody, ARMOR_NAME[ITEM_ARMOR_LEATHER], _playerLute.c_str(), lute_right_body_leather, 4, ANISPEED, true);

	int lute_right_body_chainmail[] = { 8, 9, 10, 11 };
	KEYANIMANAGER->addArrayFrameAnimation(_playerBody, ARMOR_NAME[ITEM_ARMOR_CHAINMAIL], _playerLute.c_str(), lute_right_body_chainmail, 4, ANISPEED, true);

	int lute_right_body_platemail[] = { 12, 13, 14, 15 };
	KEYANIMANAGER->addArrayFrameAnimation(_playerBody, ARMOR_NAME[ITEM_ARMOR_PLATEMAIL], _playerLute.c_str(), lute_right_body_platemail, 4, ANISPEED, true);

	int lute_right_body_heavyplate[] = { 16, 17, 18, 19 };
	KEYANIMANAGER->addArrayFrameAnimation(_playerBody, ARMOR_NAME[ITEM_ARMOR_HEAVYPLATE], _playerLute.c_str(), lute_right_body_heavyplate, 4, ANISPEED, true);

	int lute_right_body_karade[] = { 20, 21, 22, 23 };
	KEYANIMANAGER->addArrayFrameAnimation(_playerBody, ARMOR_NAME[ITEM_ARMOR_KARADE], _playerLute.c_str(), lute_right_body_karade, 4, ANISPEED, true);

	int lute_right_body_obsidian[] = { 24, 25, 26, 27 };
	KEYANIMANAGER->addArrayFrameAnimation(_playerBody, ARMOR_NAME[ITEM_ARMOR_OBSIDIAN], _playerLute.c_str(), lute_right_body_obsidian, 4, ANISPEED, true);

	int lute_right_body_obsidian_X2[] = { 28, 29, 30, 31 };
	KEYANIMANAGER->addArrayFrameAnimation(_playerBody, ARMOR_NAME[ITEM_ARMOR_OBSIDIAN_X2], _playerLute.c_str(), lute_right_body_obsidian_X2, 4, ANISPEED, true);

	int lute_right_body_obsidian_X3[] = { 32, 33, 34, 35 };
	KEYANIMANAGER->addArrayFrameAnimation(_playerBody, ARMOR_NAME[ITEM_ARMOR_OBSIDIAN_X3], _playerLute.c_str(), lute_right_body_obsidian_X3, 4, ANISPEED, true);

	int lute_right_body_glass[] = { 36, 37, 38, 39 };
	KEYANIMANAGER->addArrayFrameAnimation(_playerBody, ARMOR_NAME[ITEM_ARMOR_GLASS], _playerLute.c_str(), lute_right_body_glass, 4, ANISPEED, true);

	_curArmor = ARMOR_NAME[ITEM_ARMOR_NONE];

	playerAniStart_Head("right_head");
	playerAniStart_Body(_curArmor);
}

void player::playerAniStart_Head(string keyName)
{
	_playerHead_Ani = KEYANIMANAGER->findAnimation(_playerHead, keyName);
	_playerHead_Ani->start();
}

void player::playerAniStart_Body(string keyName)
{
	_playerBody_Ani = KEYANIMANAGER->findAnimation(_playerBody, keyName);
	_playerBody_Ani->start();
}

void player::playerAniStart_BodyLute(string keyName)
{
	_playerBody_Ani = KEYANIMANAGER->findAnimation(_playerLute, keyName);
	_playerBody_Ani->start();
}

void player::drawBody()
{
	if (_playerWeapon != NULL)
	{
		if (_playerWeapon->getImgName() == "weapon_golden_lute")
		{
			if (_isLeft)	IMAGEMANAGER->findImage("player_body_lute")->aniRenderReverseX(_posX - 26, _posY + _posZ - 36, _playerBody_Ani);
			else			IMAGEMANAGER->findImage("player_body_lute")->aniRender(_posX - 26, _posY + _posZ - 36, _playerBody_Ani);
		}
		else
		{
			if (_isLeft)	IMAGEMANAGER->findImage("player_body")->aniRenderReverseX(_posX - 26, _posY + _posZ - 36, _playerBody_Ani);
			else			IMAGEMANAGER->findImage("player_body")->aniRender(_posX - 26, _posY + _posZ - 36, _playerBody_Ani);
		}
	}
	else
	{
		if (_isLeft)	IMAGEMANAGER->findImage("player_body")->aniRenderReverseX(_posX - 26, _posY + _posZ - 36, _playerBody_Ani);
		else			IMAGEMANAGER->findImage("player_body")->aniRender(_posX - 26, _posY + _posZ - 36, _playerBody_Ani);
	}
	
}

void player::drawHead()
{

	if (_isLeft)	IMAGEMANAGER->findImage("player_head")->aniRenderReverseX(_posX - 26, _posY + _posZ - 36, _playerHead_Ani);
	else			IMAGEMANAGER->findImage("player_head")->aniRender(_posX - 26, _posY + _posZ - 36, _playerHead_Ani);
}

void player::drawShadow()
{
	IMAGEMANAGER->findImage("player_shadow")->render(_posX - 26, _posY - 36);
}

void player::keyUpdate()
{
	parentObj* target;

	if (KEYMANAGER->isOnceKeyDown('Q'))		//아이템
	{
		if (_isBeat)
		{
			if (_playerItem != NULL)
			{
				if (_playerItem->getImgName() == CONSUMABLE_NAME[ITEM_CONSUMABLE_WARDRUM])
				{
					_playerItem->useItem(_idxX, _idxY, 1);
					//사운드적용
				}
				else
				{
					int num = RND->getFromIntTo(1, 3);
					switch (num)
					{
					case 1:
						SOUNDMANAGER->play("sound_heal_player_01");
						break;
					case 2:
						SOUNDMANAGER->play("sound_heal_player_02");
						break;
					case 3:
						SOUNDMANAGER->play("sound_heal_player_03");
						break;
					}
					_playerItem->useItem(_idxX, _idxY, 0);
				}
			}
			_isBeat = false;
		}
	}

	if (KEYMANAGER->isOnceKeyDown('W'))		//리로드
	{
		if (_isBeat)
		{
			if (_playerWeapon->getImgName() == WEAPON_NAME[ITEM_WEAPON_BLUNDERBUSS] || _playerWeapon->getImgName() == WEAPON_NAME[ITEM_WEAPON_RIFLE]
				|| _playerWeapon->getImgName() == WEAPON_NAME[ITEM_WEAPON_CROSSBOW_BASIC] || _playerWeapon->getImgName() == WEAPON_NAME[ITEM_WEAPON_CROSSBOW_TITANIUM]
				|| _playerWeapon->getImgName() == WEAPON_NAME[ITEM_WEAPON_CROSSBOW_GLASS] || _playerWeapon->getImgName() == WEAPON_NAME[ITEM_WEAPON_CROSSBOW_OBSIDIAN]
				|| _playerWeapon->getImgName() == WEAPON_NAME[ITEM_WEAPON_CROSSBOW_BLOOD] || _playerWeapon->getImgName() == WEAPON_NAME[ITEM_WEAPON_CROSSBOW_GOLD])
			{
				_playerWeapon->useItem(_idxX, _idxY, 5);
			}
			_isBeat = false;
		}
	}

	if (KEYMANAGER->isOnceKeyDown('E'))		//폭탄
	{
		if (_isBeat)
		{
			if (_playerBomb != NULL)
			{
				_playerBomb->useItem(_idxX, _idxY, 0);
				//사운드적용
			}
			_isBeat = false;
		}
	}

	if (_playerState != PLAYER_STATE_NONE)
	{
		_isPress = false;
		playerStateUpdate(true);
	}

	if (_moveDistance == 0)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			_attDir = PLAYER_STATE_JUMP_LEFT;
			_isLeft = true;
			if (_isBeat)
			{
				target = OBJECTMANAGER->getCheckObj(_idxX - 1, _idxY);
				if (_playerWeapon != NULL && _playerWeapon->useItem(_idxX - 1, _idxY, 4))
				{
					OBJECTMANAGER->setIsEffectUse(true);
					int num = RND->getFromIntTo(1, 17);
					switch (num)
					{
					case 1: SOUNDMANAGER->play("sound_cad_melee_1_01"); break;
					case 2: SOUNDMANAGER->play("sound_cad_melee_1_02"); break;
					case 3: SOUNDMANAGER->play("sound_cad_melee_1_03"); break;
					case 4: SOUNDMANAGER->play("sound_cad_melee_1_04"); break;
					case 5: SOUNDMANAGER->play("sound_cad_melee_2_01"); break;
					case 6: SOUNDMANAGER->play("sound_cad_melee_2_02"); break;
					case 7: SOUNDMANAGER->play("sound_cad_melee_2_03"); break;
					case 8: SOUNDMANAGER->play("sound_cad_melee_2_04"); break;
					case 9: SOUNDMANAGER->play("sound_cad_melee_3_01"); break;
					case 10: SOUNDMANAGER->play("sound_cad_melee_3_02"); break;
					case 11: SOUNDMANAGER->play("sound_cad_melee_3_03"); break;
					case 12: SOUNDMANAGER->play("sound_cad_melee_3_04"); break;
					case 13: SOUNDMANAGER->play("sound_cad_melee_4_01"); break;
					case 14: SOUNDMANAGER->play("sound_cad_melee_4_02"); break;
					case 15: SOUNDMANAGER->play("sound_cad_melee_4_03"); break;
					case 16: SOUNDMANAGER->play("sound_cad_melee_4_04"); break;
					case 17: SOUNDMANAGER->play("sound_cad_melee_4_05"); break;
					}
					CAMERA->isQuake();
				}
				else if (target == NULL || target->getObjType() == OBJECT_TYPE_FLOOR || target->getObjType() == OBJECT_TYPE_ITEM)
				{
					_tempX = _idxX;
					_tempY = _idxY;
					OBJECTMANAGER->setTileIdx(this, _idxX - 1, _idxY);
					
					if (_putObj != NULL)
					{
						putItem(_putObj);
						_putObj = nullptr;
					}
					_playerState = PLAYER_STATE_JUMP_LEFT;
					_moveDistance = TILE_SIZE;
					_jumpPower = JUMPPOWER;
					_isPress = true;

					if (target != NULL && target->getObjType() == OBJECT_TYPE_ITEM)
					{
						addInven(target);
					}
				}
				else if (target->getObjType() == OBJECT_TYPE_WALL)
				{
					if (target->getImgName() == IMAGE_NAME[IMAGE_NAME_DOOR_01] || target->getImgName() == IMAGE_NAME[IMAGE_NAME_DOOR_02])
					{
						SOUNDMANAGER->play("sound_door_open");
						CAMERA->isQuake();
						OBJECTMANAGER->deleteObject(target);
					}
					else if (_playerShovel != NULL)
					{
						if (_playerShovel->useItem(_idxX - 1, _idxY, 4))
						{
							_isUseShovel = true;
							CAMERA->isQuake();
						}
						_isUseShovel = true;
					}
				}
			}
			_isBeat = false;
			//_isUseShovel = false;
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			_attDir = PLAYER_STATE_JUMP_RIGHT;
			_isLeft = false;
			if (_isBeat)
			{
				target = OBJECTMANAGER->getCheckObj(_idxX + 1, _idxY);
				if (_playerWeapon != NULL && _playerWeapon->useItem(_idxX + 1, _idxY, 6))
				{
					OBJECTMANAGER->setIsEffectUse(true);
					int num = RND->getFromIntTo(1, 17);
					switch (num)
					{
					case 1: SOUNDMANAGER->play("sound_cad_melee_1_01"); break;
					case 2: SOUNDMANAGER->play("sound_cad_melee_1_02"); break;
					case 3: SOUNDMANAGER->play("sound_cad_melee_1_03"); break;
					case 4: SOUNDMANAGER->play("sound_cad_melee_1_04"); break;
					case 5: SOUNDMANAGER->play("sound_cad_melee_2_01"); break;
					case 6: SOUNDMANAGER->play("sound_cad_melee_2_02"); break;
					case 7: SOUNDMANAGER->play("sound_cad_melee_2_03"); break;
					case 8: SOUNDMANAGER->play("sound_cad_melee_2_04"); break;
					case 9: SOUNDMANAGER->play("sound_cad_melee_3_01"); break;
					case 10: SOUNDMANAGER->play("sound_cad_melee_3_02"); break;
					case 11: SOUNDMANAGER->play("sound_cad_melee_3_03"); break;
					case 12: SOUNDMANAGER->play("sound_cad_melee_3_04"); break;
					case 13: SOUNDMANAGER->play("sound_cad_melee_4_01"); break;
					case 14: SOUNDMANAGER->play("sound_cad_melee_4_02"); break;
					case 15: SOUNDMANAGER->play("sound_cad_melee_4_03"); break;
					case 16: SOUNDMANAGER->play("sound_cad_melee_4_04"); break;
					case 17: SOUNDMANAGER->play("sound_cad_melee_4_05"); break;
					}
					CAMERA->isQuake();
				}
				else if (target == NULL || target->getObjType() == OBJECT_TYPE_FLOOR || target->getObjType() == OBJECT_TYPE_ITEM)
				{
					_tempX = _idxX;
					_tempY = _idxY;
					OBJECTMANAGER->setTileIdx(this, _idxX + 1, _idxY);

					if (_putObj != NULL)
					{
						putItem(_putObj);
						_putObj = nullptr;
					}
					_playerState = PLAYER_STATE_JUMP_RIGHT;
					_moveDistance = TILE_SIZE;
					_jumpPower = JUMPPOWER;
					_isPress = true;

					if (target != NULL && target->getObjType() == OBJECT_TYPE_ITEM)
					{
						addInven(target);
					}
				}
				else if (target->getObjType() == OBJECT_TYPE_WALL)
				{
					if (target->getImgName() == IMAGE_NAME[IMAGE_NAME_DOOR_01] || target->getImgName() == IMAGE_NAME[IMAGE_NAME_DOOR_02])
					{
						SOUNDMANAGER->play("sound_door_open");
						CAMERA->isQuake();
						OBJECTMANAGER->deleteObject(target);
					}
					else if (_playerShovel != NULL)
					{
						if (_playerShovel->useItem(_idxX + 1, _idxY, 6))
						{
							_isUseShovel = true;
							CAMERA->isQuake();
						}
						_isUseShovel = true;
					}
				}
			}
			_isBeat = false;
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_attDir = PLAYER_STATE_JUMP_UP;
			if (_isBeat)
			{
				target = OBJECTMANAGER->getCheckObj(_idxX, _idxY - 1);
				if (_playerWeapon != NULL && _playerWeapon->useItem(_idxX, _idxY - 1, 8))
				{
					OBJECTMANAGER->setIsEffectUse(true);
					int num = RND->getFromIntTo(1, 17);
					switch (num)
					{
					case 1: SOUNDMANAGER->play("sound_cad_melee_1_01"); break;
					case 2: SOUNDMANAGER->play("sound_cad_melee_1_02"); break;
					case 3: SOUNDMANAGER->play("sound_cad_melee_1_03"); break;
					case 4: SOUNDMANAGER->play("sound_cad_melee_1_04"); break;
					case 5: SOUNDMANAGER->play("sound_cad_melee_2_01"); break;
					case 6: SOUNDMANAGER->play("sound_cad_melee_2_02"); break;
					case 7: SOUNDMANAGER->play("sound_cad_melee_2_03"); break;
					case 8: SOUNDMANAGER->play("sound_cad_melee_2_04"); break;
					case 9: SOUNDMANAGER->play("sound_cad_melee_3_01"); break;
					case 10: SOUNDMANAGER->play("sound_cad_melee_3_02"); break;
					case 11: SOUNDMANAGER->play("sound_cad_melee_3_03"); break;
					case 12: SOUNDMANAGER->play("sound_cad_melee_3_04"); break;
					case 13: SOUNDMANAGER->play("sound_cad_melee_4_01"); break;
					case 14: SOUNDMANAGER->play("sound_cad_melee_4_02"); break;
					case 15: SOUNDMANAGER->play("sound_cad_melee_4_03"); break;
					case 16: SOUNDMANAGER->play("sound_cad_melee_4_04"); break;
					case 17: SOUNDMANAGER->play("sound_cad_melee_4_05"); break;
					}
					CAMERA->isQuake();
				}
				else if (target == NULL || target->getObjType() == OBJECT_TYPE_FLOOR || target->getObjType() == OBJECT_TYPE_ITEM)
				{
					_tempX = _idxX;
					_tempY = _idxY;
					OBJECTMANAGER->setTileIdx(this, _idxX, _idxY - 1);

					if (_putObj != NULL)
					{
						putItem(_putObj);
						_putObj = nullptr;
					}
					_playerState = PLAYER_STATE_JUMP_UP;
					_moveDistance = TILE_SIZE;
					_jumpPower = JUMPPOWER;
					_isPress = true;

					if (target != NULL && target->getObjType() == OBJECT_TYPE_ITEM)
					{
						addInven(target);
					}
				}
				else if (target->getObjType() == OBJECT_TYPE_WALL)
				{
					if (target->getImgName() == IMAGE_NAME[IMAGE_NAME_DOOR_01] || target->getImgName() == IMAGE_NAME[IMAGE_NAME_DOOR_02])
					{
						SOUNDMANAGER->play("sound_door_open");
						CAMERA->isQuake();
						OBJECTMANAGER->deleteObject(target);
					}
					else if (_playerShovel != NULL)
					{
						if (_playerShovel->useItem(_idxX, _idxY - 1, 8))
						{
							_isUseShovel = true;
							_isQuakeCamera = true;
							CAMERA->isQuake();
						}
						_isUseShovel = true;
					}
				}
			}
			_isBeat = false;
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_attDir = PLAYER_STATE_JUMP_DOWN;
			if (_isBeat)
			{
				target = OBJECTMANAGER->getCheckObj(_idxX, _idxY + 1);
				if (_playerWeapon != NULL && _playerWeapon->useItem(_idxX, _idxY + 1, 2))
				{
					OBJECTMANAGER->setIsEffectUse(true);
					int num = RND->getFromIntTo(1, 17);
					switch (num)
					{
					case 1: SOUNDMANAGER->play("sound_cad_melee_1_01"); break;
					case 2: SOUNDMANAGER->play("sound_cad_melee_1_02"); break;
					case 3: SOUNDMANAGER->play("sound_cad_melee_1_03"); break;
					case 4: SOUNDMANAGER->play("sound_cad_melee_1_04"); break;
					case 5: SOUNDMANAGER->play("sound_cad_melee_2_01"); break;
					case 6: SOUNDMANAGER->play("sound_cad_melee_2_02"); break;
					case 7: SOUNDMANAGER->play("sound_cad_melee_2_03"); break;
					case 8: SOUNDMANAGER->play("sound_cad_melee_2_04"); break;
					case 9: SOUNDMANAGER->play("sound_cad_melee_3_01"); break;
					case 10: SOUNDMANAGER->play("sound_cad_melee_3_02"); break;
					case 11: SOUNDMANAGER->play("sound_cad_melee_3_03"); break;
					case 12: SOUNDMANAGER->play("sound_cad_melee_3_04"); break;
					case 13: SOUNDMANAGER->play("sound_cad_melee_4_01"); break;
					case 14: SOUNDMANAGER->play("sound_cad_melee_4_02"); break;
					case 15: SOUNDMANAGER->play("sound_cad_melee_4_03"); break;
					case 16: SOUNDMANAGER->play("sound_cad_melee_4_04"); break;
					case 17: SOUNDMANAGER->play("sound_cad_melee_4_05"); break;
					}
					CAMERA->isQuake();
				}
				else if (target == NULL || target->getObjType() == OBJECT_TYPE_FLOOR || target->getObjType() == OBJECT_TYPE_ITEM)
				{
					_tempX = _idxX;
					_tempY = _idxY;
					OBJECTMANAGER->setTileIdx(this, _idxX, _idxY + 1);

					if (_putObj != NULL)
					{
						putItem(_putObj);
						_putObj = nullptr;
					}
					_playerState = PLAYER_STATE_JUMP_DOWN;
					_moveDistance = TILE_SIZE;
					_jumpPower = JUMPPOWER;
					_isPress = true;

					if (target != NULL && target->getObjType() == OBJECT_TYPE_ITEM)
					{
						addInven(target);
					}
				}
				else if (target->getObjType() == OBJECT_TYPE_WALL)
				{
					if (target->getImgName() == IMAGE_NAME[IMAGE_NAME_DOOR_01] || target->getImgName() == IMAGE_NAME[IMAGE_NAME_DOOR_02])
					{
						SOUNDMANAGER->play("sound_door_open");
						CAMERA->isQuake();
						OBJECTMANAGER->deleteObject(target);
					}
					else if (_playerShovel != NULL)
					{
						if (_playerShovel->useItem(_idxX, _idxY + 1, 2))
						{
							_isUseShovel = true;
							CAMERA->isQuake();
						}
						_isUseShovel = true;
					}
				}
			}
			_isBeat = false;
		}
	}
}

void player::playerStateUpdate(bool check)
{
	_speed = TIMEMANAGER->getElapsedTime() * PLAYER_SPEED;
	if (check)
	{
		switch (_playerState)
		{
		case PLAYER_STATE_JUMP_LEFT:
		{
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
				_isPress = true;
				_playerState = PLAYER_STATE_NONE;
			}
			break;
		}
		case PLAYER_STATE_JUMP_RIGHT:
		{
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
				_isPress = true;
				_playerState = PLAYER_STATE_NONE;
			}
			break;
		}
		case PLAYER_STATE_JUMP_UP:
		{
			_posY -= _speed;
			_moveDistance -= _speed;
			_posZ -= _jumpPower * TIMEMANAGER->getElapsedTime();
			_jumpPower -= _gravity * TIMEMANAGER->getElapsedTime();
			if (_posZ > 0) _posZ = 0;
			if (_moveDistance < _speed)
			{
				verticalSet();
				_jumpPower = 0;
				_posZ = 0;
				_isPress = true;
				_playerState = PLAYER_STATE_NONE;
			}
			break;
		}
		case PLAYER_STATE_JUMP_DOWN:
		{
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
				_isPress = true;
				_playerState = PLAYER_STATE_NONE;
			}
			break;
		}
		}
		if (_moveDistance == 0) _isMove = true;
	}
	else
	{
		switch (_playerState)
		{
		case PLAYER_STATE_JUMP_LEFT:
		{
			_moveDistance -= _speed;
			//_posX -= _speed;
			if (_moveDistance < _speed)
			{
				horizonSet();
				_jumpPower = 0;
				_posZ = 0;
				_playerState = PLAYER_STATE_NONE;
				_isPress = true;
			}
			break;
		}
		case PLAYER_STATE_JUMP_RIGHT:
		{
			_moveDistance -= _speed;
			//_posX += _speed;
			if (_moveDistance < _speed)
			{
				horizonSet();
				_jumpPower = 0;
				_posZ = 0;
				_playerState = PLAYER_STATE_NONE;
				_isPress = true;
			}
			break;
		}
		case PLAYER_STATE_JUMP_UP:
		{
			_moveDistance -= _speed;
			//_posY -= _speed;
			if (_moveDistance < _speed)
			{
				verticalSet();
				_jumpPower = 0;
				_posZ = 0;
				_playerState = PLAYER_STATE_NONE;
				_isPress = true;
			}
			break;
		}
		case PLAYER_STATE_JUMP_DOWN:
		{
			_moveDistance -= _speed;
			//_posY += _speed;
			if (_moveDistance < _speed)
			{
				verticalSet();
				_jumpPower = 0;
				_posZ = 0;
				_playerState = PLAYER_STATE_NONE;
				_isPress = true;
			}
			break;
		}
		}
		if (_moveDistance == 0) _isMove = true;
	}
}

void player::horizonSet()
{
	_posX = (int)_posX / TILE_SIZE * TILE_SIZE + 26;
	_moveDistance = 0;
	_tileX = _posX / TILE_SIZE;
	_idxX = _posX / TILE_SIZE;
}

void player::verticalSet()
{
	_posY = (int)_posY / TILE_SIZE * TILE_SIZE + 26;
	_moveDistance = 0;
	_tileY = _posY / TILE_SIZE;
	_idxY = _posY / TILE_SIZE;
}

bool player::checkMove()
{
	if (_playerState != PLAYER_STATE_NONE) return true;
	else return false;
}

void player::initEquipUI()
{
	for (int i = 0; i < 9; i++)
	{
		if (i < 6)
			_inven[i].pos = { 20 + (i * 70) , 10 };
		else
			_inven[i].pos = { 20, 10 + ((i - 5) * 85) };

		_inven[i].UIKey = "";
		_inven[i].object = nullptr;
		_inven[i].isUse = false;
	}
}

void player::setEquipUI(parentObj* obj)
{
	for (int i = 0; i < 9; i++)
	{
		_inven[i] = { };
		if (i < 6)
			_inven[i].pos = { 20 + (i * 70) , 10 };
		else
			_inven[i].pos = { 20, 10 + ((i - 5) * 85) };
	}

	//플레이어 스탯 초기화
	_playerStat = { _playerStat.heart, _playerStat.maxHeart, _playerStat.coin, };

	if (_playerShovel != NULL)
	{
		_inven[0].isUse = true;
		_inven[0].UIKey = "equipUI_shovel";
		_inven[0].object = _playerShovel;

		if (_playerShovel == obj)
			obj->itemInven(_inven[0].pos.x + 8, _inven[0].pos.y + 13);
		_playerStat.shovelPower += _playerShovel->getAppliedValue();
	}
	if (_playerWeapon != NULL)
	{
		for (int i = 0; i < 2; i++)
		{
			if (!_inven[i].isUse)
			{
				_inven[i].isUse = true;
				_inven[i].UIKey = "equipUI_weapon";
				_inven[i].object = _playerWeapon;

				if (_playerWeapon == obj)
					obj->itemInven(_inven[i].pos.x + 8, _inven[i].pos.y + 13);
				_playerStat.attack += _playerWeapon->getAppliedValue();
				if (_inven[i].object->getImgName() == "weapon_golden_lute")
				{
					if (_playerArmor == NULL)
						_curArmor = ARMOR_NAME[ITEM_ARMOR_NONE];
					else
						_curArmor = _playerArmor->getImgName();
					playerAniStart_Body(_curArmor);

				}

				break;
			}
		}
	}
	if (_playerArmor != NULL)
	{
		for (int i = 0; i < 3; i++)
		{
			if (!_inven[i].isUse)
			{
				_inven[i].isUse = true;
				_inven[i].UIKey = "equipUI_armor";
				_inven[i].object = _playerArmor;

				//if (_playerArmor == obj)
				//	obj->itemInven(_inven[i].pos.x + 8, _inven[i].pos.y + 13);
				if (_inven[i].object->getImgName() == "weapon_golden_lute")
				{
					playerAniStart_Body(_curArmor);
				}
				else
				{
					_curArmor = _playerArmor->getImgName();
					playerAniStart_Head("right_head");
					playerAniStart_Body(_curArmor);
				}


				_playerStat.defence += _playerArmor->getAppliedValue();
				break;
			}
		}
	}
	if (_playerHeadWear != NULL)
	{
		for (int i = 0; i < 4; i++)
		{
			if (!_inven[i].isUse)
			{
				_inven[i].isUse = true;
				_inven[i].UIKey = "equipUI_headwear";
				_inven[i].object = _playerHeadWear;

				if (_playerHeadWear == obj)
					obj->itemInven(_inven[i].pos.x + 8, _inven[i].pos.y + 13);
				_playerStat.defence += _playerHeadWear->getAppliedValue();

				break;
			}
		}
	}
	if (_playerFootWear != NULL)
	{
		for (int i = 0; i < 5; i++)
		{
			if (!_inven[i].isUse)
			{
				_inven[i].isUse = true;
				_inven[i].UIKey = "equipUI_footwear";
				_inven[i].object = _playerFootWear;

				if (_playerFootWear == obj)
					obj->itemInven(_inven[i].pos.x + 8, _inven[i].pos.y + 13);
				_playerStat.defence += _playerFootWear->getAppliedValue();
				break;
			}
		}
	}
	if (_playerTorch != NULL)
	{
		for (int i = 0; i < 6; i++)
		{
			if (!_inven[i].isUse)
			{
				_inven[i].isUse = true;
				_inven[i].UIKey = "equipUI_torch";
				_inven[i].object = _playerTorch;

				if (_playerTorch == obj)
					obj->itemInven(_inven[i].pos.x + 8, _inven[i].pos.y + 13);

				break;
			}
		}
	}
	if (_playerItem != NULL)
	{
		for (int i = 6; i < 9; i++)
		{
			if (!_inven[i].isUse)
			{
				_inven[i].isUse = true;
				_inven[i].UIKey = "equipUI_item";
				_inven[i].object = _playerItem;

				if (_playerItem == obj)
					obj->itemInven(_inven[i].pos.x + 8, _inven[i].pos.y + 13);

				break;
			}
		}
	}
	if (_playerBomb != NULL)
	{
		for (int i = 6; i < 9; i++)
		{
			if (!_inven[i].isUse)
			{
				_inven[i].isUse = true;
				_inven[i].UIKey = "equipUI_bomb";
				_inven[i].object = _playerBomb;

				if (_playerBomb == obj)
					obj->itemInven(_inven[i].pos.x + 8, _inven[i].pos.y + 13);

				break;
			}
		}
	}
}

void player::brokenItemEquipUI()
{
	for (int i = 0; i < 9; i++)
	{
		_inven[i] = { };
		if (i < 6)
			_inven[i].pos = { 20 + (i * 70) , 10 };
		else
			_inven[i].pos = { 20, 10 + ((i - 5) * 85) };
	}

	//플레이어 스탯 초기화
	_playerStat = { _playerStat.heart, _playerStat.maxHeart, _playerStat.coin, };

	if (_playerShovel != NULL)
	{
		_inven[0].isUse = true;
		_inven[0].UIKey = "equipUI_shovel";
		_inven[0].object = _playerShovel;
	}
	if (_playerWeapon != NULL)
	{
		for (int i = 0; i < 2; i++)
		{
			if (!_inven[i].isUse)
			{
				_inven[i].isUse = true;
				_inven[i].UIKey = "equipUI_weapon";
				_inven[i].object = _playerWeapon;
				break;
			}
		}
	}
	if (_playerArmor != NULL)
	{
		for (int i = 0; i < 3; i++)
		{
			if (!_inven[i].isUse)
			{
				_inven[i].isUse = true;
				_inven[i].UIKey = "equipUI_armor";
				_inven[i].object = _playerArmor;
				break;
			}
		}
	}
	if (_playerHeadWear != NULL)
	{
		for (int i = 0; i < 4; i++)
		{
			if (!_inven[i].isUse)
			{
				_inven[i].isUse = true;
				_inven[i].UIKey = "equipUI_headwear";
				_inven[i].object = _playerHeadWear;
				break;
			}
		}
	}
	if (_playerFootWear != NULL)
	{
		for (int i = 0; i < 5; i++)
		{
			if (!_inven[i].isUse)
			{
				_inven[i].isUse = true;
				_inven[i].UIKey = "equipUI_footwear";
				_inven[i].object = _playerFootWear;
				break;
			}
		}
	}
	if (_playerTorch != NULL)
	{
		for (int i = 0; i < 6; i++)
		{
			if (!_inven[i].isUse)
			{
				_inven[i].isUse = true;
				_inven[i].UIKey = "equipUI_torch";
				_inven[i].object = _playerTorch;
				break;
			}
		}
	}
	if (_playerItem != NULL)
	{
		for (int i = 6; i < 9; i++)
		{
			if (!_inven[i].isUse)
			{
				_inven[i].isUse = true;
				_inven[i].UIKey = "equipUI_item";
				_inven[i].object = _playerItem;
				break;
			}
		}
	}
	if (_playerBomb != NULL)
	{
		for (int i = 6; i < 9; i++)
		{
			if (!_inven[i].isUse)
			{
				_inven[i].isUse = true;
				_inven[i].UIKey = "equipUI_bomb";
				_inven[i].object = _playerBomb;
				break;
			}
		}
	}
}

void player::drawPlayerUI()
{
	WCHAR str[128];

	int fullHeart = _playerStat.heart / 2;
	int halfHeart = _playerStat.heart % 2;
	int	emptyHeart = _playerStat.maxHeart - fullHeart / 2;

	if (_playerStat.maxHeart / 2 <= 3)
	{
		for (int i = 0; i < _playerStat.maxHeart / 2; i++)
		{
			if (i < fullHeart)
			{
				if (i == _heartBeat && _heartBeatCount > 0)
				{
					IMAGEMANAGER->findImage("ui_large_heart")->render2(CAMERA->getPosX() + 630 + i * 53, CAMERA->getPosY() + 7);
					_heartBeatCount--;
				}
				else
					IMAGEMANAGER->findImage("ui_heart")->render2(CAMERA->getPosX() + 633 - i * 53, CAMERA->getPosY() + 10);
			}
			else if (halfHeart)
			{
				if (i == _heartBeat && _heartBeatCount > 0)
				{
					IMAGEMANAGER->findImage("ui_large_half_heart")->render2(CAMERA->getPosX() + 630 + i * 53, CAMERA->getPosY() + 7);
					_heartBeatCount--;
				}
				else
					IMAGEMANAGER->findImage("ui_half_heart")->render2(CAMERA->getPosX() + 633 + i * 53, CAMERA->getPosY() + 10);
				halfHeart = 0;
			}
			else
				IMAGEMANAGER->findImage("ui_empty_heart")->render2(CAMERA->getPosX() + 633 + i * 53, CAMERA->getPosY() + 10);
		}
	}
	else
	{
		for (int i = 0; i < _playerStat.maxHeart / 2; i++)
		{
			if (i < fullHeart)
			{
				if (i == _heartBeat && _heartBeatCount > 0)
				{
					if (i > 4)
						IMAGEMANAGER->findImage("ui_large_heart")->render2(CAMERA->getPosX() + 770 + (i - 9) * 53, CAMERA->getPosY() + 57);
					else
						IMAGEMANAGER->findImage("ui_large_heart")->render2(CAMERA->getPosX() + 560 + i * 53, CAMERA->getPosY() + 7);
					_heartBeatCount--;
				}
				else
				{
					if (i > 4)
						IMAGEMANAGER->findImage("ui_heart")->render2(CAMERA->getPosX() + 773 + (i - 9) * 53, CAMERA->getPosY() + 60);
					else
						IMAGEMANAGER->findImage("ui_heart")->render2(CAMERA->getPosX() + 563 + i * 53, CAMERA->getPosY() + 10);
				}
			}
			else if (halfHeart)
			{
				if (i == _heartBeat && _heartBeatCount > 0)
				{
					if (i > 4)
						IMAGEMANAGER->findImage("ui_large_half_heart")->render2(CAMERA->getPosX() + 770 + (i - 9) * 53, CAMERA->getPosY() + 57);
					else
						IMAGEMANAGER->findImage("ui_large_half_heart")->render2(CAMERA->getPosX() + 560 + i * 53, CAMERA->getPosY() + 7);
					_heartBeatCount--;
				}
				else
				{
					if (i > 4)
						IMAGEMANAGER->findImage("ui_half_heart")->render2(CAMERA->getPosX() + 773 + (i - 9) * 53, CAMERA->getPosY() + 60);
					else
						IMAGEMANAGER->findImage("ui_half_heart")->render2(CAMERA->getPosX() + 563 + i * 53, CAMERA->getPosY() + 10);
				}
				halfHeart = 0;
			}
			else
			{
				if (i > 4)
					IMAGEMANAGER->findImage("ui_empty_heart")->render2(CAMERA->getPosX() + 773 + (i - 9) * 53, CAMERA->getPosY() + 60);
				else
					IMAGEMANAGER->findImage("ui_empty_heart")->render2(CAMERA->getPosX() + 563 + i * 53, CAMERA->getPosY() + 10);
			}
		}
	}



	//돈
	IMAGEMANAGER->findImage("ui_coins")->render2(CAMERA->getPosX() + 830, CAMERA->getPosY() + 10);
	IMAGEMANAGER->findImage("ui_X")->render2(CAMERA->getPosX() + 880, CAMERA->getPosY() + 40);

	int chipher[4] = { 0, };

	chipher[0] = _playerStat.coin / 1000;
	chipher[1] = (_playerStat.coin - chipher[0] * 1000) / 100;
	chipher[2] = (_playerStat.coin - chipher[0] * 1000 - chipher[1] * 100) / 10;
	chipher[3] = (_playerStat.coin - chipher[0] * 1000 - chipher[1] * 100 - chipher[2] * 10) / 1;

	bool check = false;

	for (int i = 0; i < 4; i++)
	{
		if (check || i == 3)
		{
			IMAGEMANAGER->findImage("ui_digit")->frameRender2(CAMERA->getPosX() + 890 + 12 * i, CAMERA->getPosY() + 30, chipher[i], 0);
		}
		else if (check == false && chipher[i] != 0)
		{
			IMAGEMANAGER->findImage("ui_digit")->frameRender2(CAMERA->getPosX() + 890 + 12 * i, CAMERA->getPosY() + 30, chipher[i], 0);
			check = true;
		}
	}
}

void player::drawEquipUI()
{
	for (int i = 0; i < 9; i++)
	{
		if (_inven[i].UIKey == "") break;

		if (_inven[i].object->getImgName() == "armor_none" || _inven[i].object->getImgName() == "weapon_none"
			|| _inven[i].object->getImgName() == "footwear_none" || _inven[i].object->getImgName() == "headwear_none"
			|| _inven[i].object->getImgName() == "weapon_none" || _inven[i].object->getImgName() == "consumable_none"
			|| _inven[i].object->getImgName() == "heart_none" || _inven[i].object->getImgName() == "coin_none"
			|| _inven[i].object->getImgName() == "bomb_none" || _inven[i].object->getImgName() == "none") continue;

		if (_inven[i].isUse)
		{
			_inven[i].object->setXY(_inven[i].pos.x + 3, _inven[i].pos.y + 12);

			if (_inven[i].object->getPosX() == _inven[i].pos.x + 3)
			{
				if (_inven[i].object->getImgName() == "weapon_blunderbuss")
				{
					IMAGEMANAGER->frameRender(_inven[i].object->getImgName(), CAMERA->getPosX() + _inven[i].pos.x, CAMERA->getPosY() + _inven[i].pos.y - 13, _inven[i].object->getFrameX(), _inven[i].object->getFrameY());
				}
				else
					IMAGEMANAGER->frameRender(_inven[i].object->getImgName(), CAMERA->getPosX() + _inven[i].pos.x + 8, CAMERA->getPosY() + _inven[i].pos.y + 13, _inven[i].object->getFrameX(), _inven[i].object->getFrameY());
			}
			if (_inven[i].object->getImgName() == "weapon_blunderbuss")
			{
				if (_inven[6].object != NULL)
				{
					if (_inven[i].object->getFrameX() == 1)
					{
						IMAGEMANAGER->frameRender("equipUI_reload", CAMERA->getPosX() + _inven[7].pos.x, CAMERA->getPosY() + _inven[7].pos.y, 0, 0);
						IMAGEMANAGER->findImage(_inven[i].object->getImgName())->frameRender2(CAMERA->getPosX() + _inven[7].pos.x + 5, CAMERA->getPosY() + _inven[7].pos.y - 12, _inven[i].object->getFrameX(), 0);
					}
				}
				else
				{
					if (_inven[i].object->getFrameX() == 1)
					{
						IMAGEMANAGER->frameRender("equipUI_reload", CAMERA->getPosX() + _inven[6].pos.x, CAMERA->getPosY() + _inven[6].pos.y, 0, 0);
						IMAGEMANAGER->findImage(_inven[i].object->getImgName())->frameRender2(CAMERA->getPosX() + _inven[6].pos.x + 5, CAMERA->getPosY() + _inven[6].pos.y - 12, _inven[i].object->getFrameX(), 0);
					}
				}
			}
			if (_inven[i].object->getIsThrow())
			{
				if (_inven[6].object != NULL)
				{
					IMAGEMANAGER->findImage("equipUI_throw")->render2(CAMERA->getPosX() + _inven[7].pos.x, CAMERA->getPosY() + _inven[7].pos.y);
					IMAGEMANAGER->findImage(_inven[i].object->getImgName())->frameRender2(CAMERA->getPosX() + _inven[7].pos.x + 5, CAMERA->getPosY() + _inven[7].pos.y + 12, 0, 0);
				}
				else
				{
					IMAGEMANAGER->findImage("equipUI_throw")->render2(CAMERA->getPosX() + _inven[6].pos.x, CAMERA->getPosY() + _inven[6].pos.y);
					IMAGEMANAGER->findImage(_inven[i].object->getImgName())->frameRender2(CAMERA->getPosX() + _inven[6].pos.x + 5, CAMERA->getPosY() + _inven[6].pos.y + 12, 0, 0);
				}
			}

			if (_inven[i].UIKey == "equipUI_shovel")
				IMAGEMANAGER->findImage("equipUI_shovel")->render2(CAMERA->getPosX() + _inven[i].pos.x, CAMERA->getPosY() + _inven[i].pos.y);
			else if (_inven[i].UIKey == "equipUI_weapon")
				IMAGEMANAGER->findImage("equipUI_weapon")->render2(CAMERA->getPosX() + _inven[i].pos.x, CAMERA->getPosY() + _inven[i].pos.y);
			else if (_inven[i].UIKey == "equipUI_armor")
				IMAGEMANAGER->findImage("equipUI_armor")->render2(CAMERA->getPosX() + _inven[i].pos.x, CAMERA->getPosY() + _inven[i].pos.y);
			else if (_inven[i].UIKey == "equipUI_head")
				IMAGEMANAGER->findImage("equipUI_head")->render2(CAMERA->getPosX() + _inven[i].pos.x, CAMERA->getPosY() + _inven[i].pos.y);
			else if (_inven[i].UIKey == "equipUI_feet")
				IMAGEMANAGER->findImage("equipUI_feet")->render2(CAMERA->getPosX() + _inven[i].pos.x, CAMERA->getPosY() + _inven[i].pos.y);
			else if (_inven[i].UIKey == "equipUI_torch")
				IMAGEMANAGER->findImage("equipUI_torch")->render2(CAMERA->getPosX() + _inven[i].pos.x, CAMERA->getPosY() + _inven[i].pos.y);
			else if (_inven[i].UIKey == "equipUI_item")
				IMAGEMANAGER->findImage("equipUI_item")->render2(CAMERA->getPosX() + _inven[i].pos.x, CAMERA->getPosY() + _inven[i].pos.y);
		}
	}
}

void player::bounceHeart()
{
	if (_playerStat.isLive)
	{
		_heartBeat++;
		_heartBeatCount = _playerStat.maxHeart - (_playerStat.maxHeart - 2);
		int fullHeart = _playerStat.heart / 2;
		bool heartCheck = ((_playerStat.heart % 2) != 0);

		_heartBeat = _heartBeat % (fullHeart + heartCheck);
	}
}

void player::initItem()
{
	_playerArmor = nullptr;
	_playerWeapon = nullptr;
	_playerBomb = nullptr;
	_playerFootWear = nullptr;
	_playerHeadWear = nullptr;
	_playerItem = nullptr;
	_playerShovel = nullptr;
	_playerTorch = nullptr;

	parentObj tempObj;
	parentObj* pTempObj;
	weapon_dagger_basic weapon;

	weapon.init(WEAPON_NAME[ITEM_WEAPON_DAGGER_BASIC], 0, 0, ITEM_TYPE_WEAPON);
	tempObj = weapon;
	pTempObj = OBJECTMANAGER->objectPush(tempObj);

	_playerWeapon = pTempObj;
	_playerWeapon->setIsCurInven(true);
	OBJECTMANAGER->setTileIdx(_playerWeapon, 0, 0);
	_playerWeapon->setIsMoveInven(false);
	_playerWeapon->setIsThrow(true);

	shovel_basic shovel;
	shovel.init(SHOVEL_NAME[ITEM_SHOVEL_BASIC], 0, 0, ITEM_TYPE_SHOVEL);
	tempObj = shovel;
	pTempObj = OBJECTMANAGER->objectPush(tempObj);

	_playerShovel = pTempObj;
	_playerShovel->setIsCurInven(true);
	OBJECTMANAGER->setTileIdx(_playerShovel, 0, 0);
	_playerShovel->setIsMoveInven(false);


	if (_playerShovel != NULL)
	{
		if (_inven[0].isUse == false)
		{
			_inven[0].isUse = true;
			_inven[0].UIKey = "equipUI_shovel";
			_inven[0].object = _playerShovel;
		}
	}
	if (_playerWeapon != NULL)
	{
		for (int i = 0; i < 2; i++)
		{
			if (_inven[i].isUse == false)
			{
				_inven[i].isUse = true;
				_inven[i].UIKey = "equipUI_weapon";
				_inven[i].object = _playerWeapon;
				break;
			}
		}
	}
}

void player::putItem(parentObj * obj)
{
	obj->setXY(_posX, _posY - 20);
	OBJECTMANAGER->setTileIdx(obj, _tempX, _tempY);
	obj->setIsCurInven(false);
}

void player::addInven(parentObj * obj)
{
	if (obj->getObjType() != OBJECT_TYPE_NONE)
	{
		switch (obj->getItemKind())
		{
		case ITEM_TYPE_SHOVEL:
		{
			int random = RND->getFromIntTo(1, 3);
			switch (random)
			{
			case 1:
				SOUNDMANAGER->play("sound_pickup_gold_01");
				break;
			case 2:
				SOUNDMANAGER->play("sound_pickup_gold_02");
				break;
			case 3:
				SOUNDMANAGER->play("sound_pickup_gold_03");
				break;
			}
			_putObj = _playerShovel;
			_playerShovel = obj;

			break;
		}
		case ITEM_TYPE_WEAPON:
		{
			SOUNDMANAGER->play("sound_pickup_weapon");
			_putObj = _playerWeapon;
			_putObj->setIsSight(true);
			_playerWeapon = obj;
			break;
		}
		case ITEM_TYPE_TORCH:
		{
			int random = RND->getFromIntTo(1, 3);
			switch (random)
			{
			case 1:
				SOUNDMANAGER->play("sound_pickup_gold_01");
				break;
			case 2:
				SOUNDMANAGER->play("sound_pickup_gold_02");
				break;
			case 3:
				SOUNDMANAGER->play("sound_pickup_gold_03");
				break;
			}
			_putObj = _playerTorch;
			_playerTorch = obj;
			break;
		}
		case ITEM_TYPE_ARMOR:
		{
			SOUNDMANAGER->play("sound_pickup_armor");
			_putObj = _playerArmor;
			if (_playerArmor != NULL)
				_putObj->setIsSight(true);
			_playerArmor = obj;
			_curArmor = _playerArmor->getImgName();
			break;
		}
		case ITEM_TYPE_HEADWEAR:
		{
			int random = RND->getFromIntTo(1, 3);
			switch (random)
			{
			case 1:
				SOUNDMANAGER->play("sound_pickup_gold_01");
				break;
			case 2:
				SOUNDMANAGER->play("sound_pickup_gold_02");
				break;
			case 3:
				SOUNDMANAGER->play("sound_pickup_gold_03");
				break;
			}
			_putObj = _playerHeadWear;
			_playerHeadWear = obj;
			
			break;
		}
		case ITEM_TYPE_FOOTWEAR:
		{
			int random = RND->getFromIntTo(1, 3);
			switch (random)
			{
			case 1:
				SOUNDMANAGER->play("sound_pickup_gold_01");
				break;
			case 2:
				SOUNDMANAGER->play("sound_pickup_gold_02");
				break;
			case 3:
				SOUNDMANAGER->play("sound_pickup_gold_03");
				break;
			}
			_putObj = _playerFootWear;
			_playerFootWear = obj;

			break;
		}
		case ITEM_TYPE_CONSUMABLE:
		{
			int random = RND->getFromIntTo(1, 3);
			switch (random)
			{
			case 1:
				SOUNDMANAGER->play("sound_pickup_gold_01");
				break;
			case 2:
				SOUNDMANAGER->play("sound_pickup_gold_02");
				break;
			case 3:
				SOUNDMANAGER->play("sound_pickup_gold_03");
				break;
			}
			_putObj = _playerItem;
			_playerItem = obj;
			break;
		}
		case ITEM_TYPE_HEART:
		{
			int random = RND->getFromIntTo(1, 3);
			switch (random)
			{
			case 1:
				SOUNDMANAGER->play("sound_pickup_gold_01");
				break;
			case 2:
				SOUNDMANAGER->play("sound_pickup_gold_02");
				break;
			case 3:
				SOUNDMANAGER->play("sound_pickup_gold_03");
				break;
			}
			//하트증가시키자
			//_playerStat.heart += 
			OBJECTMANAGER->deleteObject(obj);
			break;
		}
		case ITEM_TYPE_COIN:
		{
			int random = RND->getFromIntTo(1, 3);
			switch (random)
			{
			case 1:
				SOUNDMANAGER->play("sound_pickup_gold_01");
				break;
			case 2:
				SOUNDMANAGER->play("sound_pickup_gold_02");
				break;
			case 3:
				SOUNDMANAGER->play("sound_pickup_gold_03");
				break;
			}
			//코인증가시키자
			_playerStat.coin += obj->getAppliedValue();
			OBJECTMANAGER->deleteObject(obj);
			break;
		}
		case ITEM_TYPE_BOMB:
		{
			int random = RND->getFromIntTo(1, 3);
			switch (random)
			{
			case 1:
				SOUNDMANAGER->play("sound_pickup_gold_01");
				break;
			case 2:
				SOUNDMANAGER->play("sound_pickup_gold_02");
				break;
			case 3:
				SOUNDMANAGER->play("sound_pickup_gold_03");
				break;
			}
			_putObj = _playerBomb;
			_playerBomb = obj;
			break;
		}
		}
		setEquipUI(obj);
	}
}

void player::drawItemHint()
{
	parentObj* tempObj;
	tempObj = OBJECTMANAGER->getCheckObj(_idxX - 1, _idxY);
	if (tempObj != NULL && tempObj->getObjType() == OBJECT_TYPE_ITEM)
		tempObj->drawHint();
	tempObj = OBJECTMANAGER->getCheckObj(_idxX, _idxY - 1);
	if (tempObj != NULL && tempObj->getObjType() == OBJECT_TYPE_ITEM)
		tempObj->drawHint();
	tempObj = OBJECTMANAGER->getCheckObj(_idxX, _idxY + 1);
	if (tempObj != NULL && tempObj->getObjType() == OBJECT_TYPE_ITEM)
		tempObj->drawHint();
	tempObj = OBJECTMANAGER->getCheckObj(_idxX + 1, _idxY);
	if (tempObj != NULL && tempObj->getObjType() == OBJECT_TYPE_ITEM)
		tempObj->drawHint();
}

void player::hitPlayer(int damage)
{
	if (_playerArmor != NULL)
	{
		if (_playerArmor->getImgName() == ARMOR_NAME[ITEM_ARMOR_GLASS])	//갑옷이 유리갑옷일때
		{
			_curArmor = ARMOR_NAME[ITEM_ARMOR_NONE];

			if (_playerWeapon != NULL)
			{
				if (_playerWeapon->getImgName() == "weapon_golden_lute")
				{
					playerAniStart_Head("right_head");
					playerAniStart_BodyLute(_curArmor);
				}
				else
				{
					playerAniStart_Head("right_head");
					playerAniStart_Body(_curArmor);
				}
			}
			else
			{
				playerAniStart_Head("right_head");
				playerAniStart_Body(_curArmor);
			}

			//적용값설정
			//_playerStat.defence -= _playerArmor.방어력

			_playerArmor = NULL;

			SOUNDMANAGER->play("sound_glass_break");
			{
				brokenItemEquipUI();
			}
		}
	}
	if (_playerHeadWear != NULL)
	{
		if (_playerHeadWear->getImgName() == HEADWEAR_NAME[ITEM_HEADWEAR_TELEPORT])
		{
			SOUNDMANAGER->play("sound_teleport");
			_playerHeadWear = NULL;
			/*_indX =
			_indY =
			_tileX =				//상점주인이 있는 곳으로
			_tileY =*/
			_posX = _idxX * 52 + 26;
			_posY = _idxY * 52 + 26;
			{
				brokenItemEquipUI();
			}
		}
	}
	else
	{
		int rand = RND->getFromIntTo(1, 6);

		switch (rand)
		{
		case 1: SOUNDMANAGER->play("sound_hurt_player_01"); break;
		case 2: SOUNDMANAGER->play("sound_hurt_player_02"); break;
		case 3: SOUNDMANAGER->play("sound_hurt_player_03"); break;
		case 4: SOUNDMANAGER->play("sound_hurt_player_04"); break;
		case 5: SOUNDMANAGER->play("sound_hurt_player_05"); break;
		case 6: SOUNDMANAGER->play("sound_hurt_player_06"); break;
		}

		int hurt;

		if (_playerArmor != NULL)
		{
			if (_playerArmor->getImgName() == ARMOR_NAME[ITEM_ARMOR_KARADE])	hurt = (damage * 2 - _playerStat.defence) * 2;	//(적공격력 - 내방어력) X 2;
			else if (damage < _playerStat.defence)
			{
				hurt = 1;
			}
			else
				hurt = damage - _playerStat.defence;	//플레이어가 입은 데미지 = 적데미지 * 2 - 플레이어 방어력
		
		}
		else
			hurt = damage - _playerStat.defence;
		

		if (hurt < 0) hurt = 0;

		_playerStat.heart -= hurt;

		if (_playerTorch != NULL)
		{
			if (_playerTorch->getImgName() == TORCH_NAME[ITEM_TORCH_GLASS])
			{
				SOUNDMANAGER->play("sound_glass_break");
				_playerTorch = NULL;
				{
					brokenItemEquipUI();
				}
			}
		}
		if (_playerWeapon != NULL)
		{
			if (_playerWeapon->getImgName() == WEAPON_NAME[ITEM_WEAPON_DAGGER_GLASS] || _playerWeapon->getImgName() == WEAPON_NAME[ITEM_WEAPON_BROADSWORD_GLASS]
				|| _playerWeapon->getImgName() == WEAPON_NAME[ITEM_WEAPON_RAPIER_GLASS] || _playerWeapon->getImgName() == WEAPON_NAME[ITEM_WEAPON_SPEAR_GLASS]
				|| _playerWeapon->getImgName() == WEAPON_NAME[ITEM_WEAPON_LONGSWORD_GLASS] || _playerWeapon->getImgName() == WEAPON_NAME[ITEM_WEAPON_WHIP_GLASS]
				|| _playerWeapon->getImgName() == WEAPON_NAME[ITEM_WEAPON_BOW_GLASS] || _playerWeapon->getImgName() == WEAPON_NAME[ITEM_WEAPON_CROSSBOW_GLASS]
				|| _playerWeapon->getImgName() == WEAPON_NAME[ITEM_WEAPON_NINETAILS_GLASS] || _playerWeapon->getImgName() == WEAPON_NAME[ITEM_WEAPON_FIAIL_GLASS])
			{
				SOUNDMANAGER->play("sound_glass_break");
				_playerWeapon = NULL;
				//바닥에 유리조각 떨어져야 한다.
				{
					brokenItemEquipUI();
				}
			}
		}
		if (_playerShovel != NULL)
		{
			if (_playerShovel->getImgName() == SHOVEL_NAME[ITEM_SHOVEL_GLASS])
			{
				SOUNDMANAGER->play("sound_glass_break");
				_playerShovel = NULL;
				//바닥에 유리조각 떨어져야 한다.
				{
					brokenItemEquipUI();
				}
			}
		}
	}
	CAMERA->isQuake();
	if (_playerStat.heart <= 0)
	{
		_playerStat.heart = 1;
		//this->playerDead();
	}

}

void player::equipUpdate()
{
	if (_playerWeapon)
		_playerWeapon->update();
	if (_playerArmor)
		_playerArmor->update();
	if (_playerShovel)
		_playerShovel->update();
	if (_playerHeadWear)
		_playerHeadWear->update();
	if (_playerFootWear)
		_playerFootWear->update();
	if (_playerTorch)
		_playerTorch->update();
	if (_playerItem)
		_playerItem->update();
	if (_playerBomb)
		_playerBomb->update();

}

bool player::getIsMove()
{
	if (_playerState != PLAYER_STATE_NONE)
		return true;
	else return false;
}
