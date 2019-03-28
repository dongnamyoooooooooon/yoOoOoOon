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
				_playerItem->useItem(_idxX, _idxY, 0);
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
				
				if(_putObj != NULL)
				{ 
					putItem(_putObj);
					_putObj = nullptr;
				}
				_playerState = PLAYER_STATE_JUMP_LEFT;
				_moveDistance = TILE_SIZE;
				_jumpPower = 0;

				if (target != NULL && target->getObjType() == OBJECT_TYPE_ITEM)
				{
					addInven(target);
				}
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
