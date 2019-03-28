#include "stdafx.h"
#include "player.h"


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

	//boolean
	_isLeft = false;

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
}

void player::render()
{
	drawBody();
	drawHead();
}

void player::playerDead()
{
	_playerStat.isLive = false;
	//사운드설정
	OBJECTMANAGER->setIsPlayerAlive();
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

void player::drawBody()
{
	if (_isLeft)	IMAGEMANAGER->findImage("player_body")->aniRenderReverseX(_posX, _posY + _posZ, _playerBody_Ani);
	else			IMAGEMANAGER->findImage("player_body")->aniRender(_posX, _posY + _posZ, _playerBody_Ani);
}

void player::drawHead()
{

	if (_isLeft)	IMAGEMANAGER->findImage("player_head")->aniRenderReverseX(_posX, _posY + _posZ, _playerHead_Ani);
	else			IMAGEMANAGER->findImage("player_head")->aniRender(_posX, _posY + _posZ, _playerHead_Ani);
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
					_playerItem->useItem(_idxX, _idxY, 0);
				//사운드적용
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
		//움직임함수 설정
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_isLeft = true;
		if (_isBeat)
		{
			target = OBJECTMANAGER->getCheckObj(_idxX - 1, _idxY);
			if (_playerWeapon != NULL && _playerWeapon->useItem(_idxX - 1, _idxY, 4))
			{
				//사운드적용
				//카메라흔들림적용
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

				if (target != NULL && target->getObjType() == OBJECT_TYPE_ITEM)
				{
					addInven(target);
				}
			}
			else if (target->getObjType() == OBJECT_TYPE_WALL)
			{
				if (target->getImgName() == IMAGE_NAME[IMAGE_NAME_DOOR_01] || target->getImgName() == IMAGE_NAME[IMAGE_NAME_DOOR_02])
				{
					//사운드적용
					//카메라흔들림적용
					OBJECTMANAGER->deleteObject(target);
				}
				else if (_playerShovel != NULL)
				{
					if (_playerShovel->useItem(_idxX - 1, _idxY, 4))
					{
						//카메라흔들림적용
						//사운드적용
					}
				}
			}
		}
		_isBeat = false;
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_isLeft = false;
		if (_isBeat)
		{
			target = OBJECTMANAGER->getCheckObj(_idxX + 1, _idxY);
			if (_playerWeapon != NULL && _playerWeapon->useItem(_idxX + 1, _idxY, 6))
			{
				//사운드적용
				//카메라흔들림적용
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

				if (target != NULL && target->getObjType() == OBJECT_TYPE_ITEM)
				{
					addInven(target);
				}
			}
			else if (target->getObjType() == OBJECT_TYPE_WALL)
			{
				if (target->getImgName() == IMAGE_NAME[IMAGE_NAME_DOOR_01] || target->getImgName() == IMAGE_NAME[IMAGE_NAME_DOOR_02])
				{
					//사운드적용
					//카메라흔들림적용
					OBJECTMANAGER->deleteObject(target);
				}
				else if (_playerShovel != NULL)
				{
					if (_playerShovel->useItem(_idxX + 1, _idxY, 6))
					{
						//카메라흔들림적용
						//사운드적용
					}
				}
			}
		}
		_isBeat = false;
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (_isBeat)
		{
			target = OBJECTMANAGER->getCheckObj(_idxX, _idxY - 1);
			if (_playerWeapon != NULL && _playerWeapon->useItem(_idxX, _idxY - 1, 8))
			{
				//사운드적용
				//카메라흔들림적용
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

				if (target != NULL && target->getObjType() == OBJECT_TYPE_ITEM)
				{
					addInven(target);
				}
			}
			else if (target->getObjType() == OBJECT_TYPE_WALL)
			{
				if (target->getImgName() == IMAGE_NAME[IMAGE_NAME_DOOR_01] || target->getImgName() == IMAGE_NAME[IMAGE_NAME_DOOR_02])
				{
					//사운드적용
					//카메라흔들림적용
					OBJECTMANAGER->deleteObject(target);
				}
				else if (_playerShovel != NULL)
				{
					if (_playerShovel->useItem(_idxX, _idxY - 1, 8))
					{
						//카메라흔들림적용
						//사운드적용
					}
				}
			}
		}
		_isBeat = false;
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (_isBeat)
		{
			target = OBJECTMANAGER->getCheckObj(_idxX, _idxY + 1);
			if (_playerWeapon != NULL && _playerWeapon->useItem(_idxX, _idxY + 1, 2))
			{
				//사운드적용
				//카메라흔들림적용
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

				if (target != NULL && target->getObjType() == OBJECT_TYPE_ITEM)
				{
					addInven(target);
				}
			}
			else if (target->getObjType() == OBJECT_TYPE_WALL)
			{
				if (target->getImgName() == IMAGE_NAME[IMAGE_NAME_DOOR_01] || target->getImgName() == IMAGE_NAME[IMAGE_NAME_DOOR_02])
				{
					//사운드적용
					//카메라흔들림적용
					OBJECTMANAGER->deleteObject(target);
				}
				else if (_playerShovel != NULL)
				{
					if (_playerShovel->useItem(_idxX, _idxY + 1, 2))
					{
						//카메라흔들림적용
						//사운드적용
					}
				}
			}
		}
		_isBeat = false;
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

				}


				break;
			}
			case PLAYER_STATE_JUMP_RIGHT:
			{

				break;
			}
			case PLAYER_STATE_JUMP_UP:
			{

				break;
			}
			case PLAYER_STATE_JUMP_DOWN:
			{

				break;
			}
		}
	}
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
	_playerStat = { _playerStat.heart, _playerStat.maxHeart, };

	if (_playerShovel != NULL)
	{
		_inven[0].isUse = true;
		_inven[0].UIKey = "equipUI_shovel";
		_inven[0].object = _playerShovel;

		if (_playerShovel == obj)
			obj->setItemInven(_inven[0].pos.x + 8, _inven[0].pos.y + 13);
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
					obj->setItemInven(_inven[i].pos.x + 8, _inven[i].pos.y + 13);

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

				if (_playerArmor == obj)
					obj->setItemInven(_inven[i].pos.x + 8, _inven[i].pos.y + 13);

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
					obj->setItemInven(_inven[i].pos.x + 8, _inven[i].pos.y + 13);

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
					obj->setItemInven(_inven[i].pos.x + 8, _inven[i].pos.y + 13);

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
					obj->setItemInven(_inven[i].pos.x + 8, _inven[i].pos.y + 13);

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
					obj->setItemInven(_inven[i].pos.x + 8, _inven[i].pos.y + 13);

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
					obj->setItemInven(_inven[i].pos.x + 8, _inven[i].pos.y + 13);

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
	_playerStat = { _playerStat.heart, _playerStat.maxHeart, };

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

void player::putItem(parentObj * obj)
{
	obj->setXY(_posX, _posY - 20);
	OBJECTMANAGER->setTileIdx(obj, _tempX, _tempY);
	obj->setIsItemInven(false);
}

void player::addInven(parentObj * obj)
{
	if (obj->getObjType() != OBJECT_TYPE_NONE)
	{
		switch (obj->getItemKind())
		{
			case ITEM_TYPE_SHOVEL:
			{
				//사운드 적용
				_putObj = _playerShovel;
				_playerShovel = obj;

				//적용값
				//_playerStat.shovelPower += obj

				break;
			}
			case ITEM_TYPE_WEAPON:
			{
				//사운드 적용
				_putObj = _playerWeapon;
				_playerWeapon = obj;

				//적용값
				//_playerStat.attack += obj
				break;
			}
			case ITEM_TYPE_TORCH:
			{
				//사운드 적용
				_putObj = _playerTorch;
				_playerTorch = obj;
				break;
			}
			case ITEM_TYPE_ARMOR:
			{
				//사운드 적용
				_putObj = _playerArmor;
				_playerArmor = obj;
				break;
			}
			case ITEM_TYPE_HEADWEAR:
			{
				//사운드 적용
				_putObj = _playerShovel;
				_playerShovel = obj;
				break;
			}
			case ITEM_TYPE_FOOTWEAR:
			{
				//사운드 적용
				_putObj = _playerFootWear;
				_playerFootWear = obj;
				break;
			}
			case ITEM_TYPE_CONSUMABLE:
			{
				//사운드 적용
				_putObj = _playerItem;
				_playerItem = obj;
				break;
			}
			case ITEM_TYPE_HEART:
			{
				//사운드 적용
				//하트증가시키자
				//_playerStat.heart += 
				OBJECTMANAGER->deleteObject(obj);
				break;
			}
			case ITEM_TYPE_COIN:
			{
				//사운드 적용
				//코인증가시키자
				//_playerStat.coin += obj
				OBJECTMANAGER->deleteObject(obj);
				break;
			}
			case ITEM_TYPE_BOMB:
			{
				//사운드 적용
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
	if (_playerArmor->getImgName() == ARMOR_NAME[ITEM_ARMOR_GLASS])	//갑옷이 유리갑옷일때
	{
		_curArmor = ARMOR_NAME[ITEM_ARMOR_NONE];

		playerAniStart_Head("right_head");
		playerAniStart_Body(_curArmor);

		//적용값설정
		//_playerStat.defence -= _playerArmor.방어력

		_playerArmor = NULL;

		SOUNDMANAGER->play("effect_glass_break");
		{
			brokenItemEquipUI();
		}
	}
	else if (_playerHeadWear->getImgName() == HEADWEAR_NAME[ITEM_HEADWEAR_TELEPORT])
	{
		SOUNDMANAGER->play("effect_teleport");
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
	else
	{
		int rand = RND->getFromIntTo(1, 6);

		switch (rand)
		{
			case 1: SOUNDMANAGER->play("effect_hurt_player_01"); break;
			case 2: SOUNDMANAGER->play("effect_hurt_player_02"); break;
			case 3: SOUNDMANAGER->play("effect_hurt_player_03"); break;
			case 4: SOUNDMANAGER->play("effect_hurt_player_04"); break;
			case 5: SOUNDMANAGER->play("effect_hurt_player_05"); break;
			case 6: SOUNDMANAGER->play("effect_hurt_player_06"); break;
		}

		int hurt;

		if (_playerArmor->getImgName() == ARMOR_NAME[ITEM_ARMOR_KARADE])	hurt = (damage * 2 - _playerStat.defence) * 2;	//(적공격력 - 내방어력) X 2;
		else																hurt = damage * 2 - _playerStat.defence;	//플레이어가 입은 데미지 = 적데미지 * 2 - 플레이어 방어력

		if (hurt < 0) hurt = 0;

		_playerStat.heart -= hurt;

		if (_playerTorch->getImgName() == TORCH_NAME[ITEM_TORCH_GLASS])
		{
			SOUNDMANAGER->play("effect_glass_break");
			_playerTorch = NULL;
			{
				brokenItemEquipUI();
			}
		}
		if (_playerWeapon->getImgName() == WEAPON_NAME[ITEM_WEAPON_DAGGER_GLASS] || _playerWeapon->getImgName() == WEAPON_NAME[ITEM_WEAPON_BROADSWORD_GLASS]
		|| _playerWeapon->getImgName() == WEAPON_NAME[ITEM_WEAPON_RAPIER_GLASS] || _playerWeapon->getImgName() == WEAPON_NAME[ITEM_WEAPON_SPEAR_GLASS]
		|| _playerWeapon->getImgName() == WEAPON_NAME[ITEM_WEAPON_LONGSWORD_GLASS] || _playerWeapon->getImgName() == WEAPON_NAME[ITEM_WEAPON_WHIP_GLASS]
		|| _playerWeapon->getImgName() == WEAPON_NAME[ITEM_WEAPON_BOW_GLASS] || _playerWeapon->getImgName() == WEAPON_NAME[ITEM_WEAPON_CROSSBOW_GLASS]
		|| _playerWeapon->getImgName() == WEAPON_NAME[ITEM_WEAPON_NINETAILS_GLASS] || _playerWeapon->getImgName() == WEAPON_NAME[ITEM_WEAPON_FIAIL_GLASS])
		{
			SOUNDMANAGER->play("effect_glass_break");
			_playerWeapon = NULL;
			//바닥에 유리조각 떨어져야 한다.
			{
				brokenItemEquipUI();
			}
		}
		if (_playerShovel->getImgName() == SHOVEL_NAME[ITEM_SHOVEL_GLASS])
		{
			SOUNDMANAGER->play("effect_glass_break");
			_playerShovel = NULL;
			//바닥에 유리조각 떨어져야 한다.
			{
				brokenItemEquipUI();
			}
		}
	}
	//카메라 흔들림 설정
	if (_playerStat.heart <= 0)
	{
		_playerStat.heart = 0;
		this->playerDead();
	}

}
