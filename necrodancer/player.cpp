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
	_posX = (float)_tileX * 48 + 24;
	_posY = (float)_tileY * 48 + 24;
	_posZ = 0;
	_playerState = PLAYER_STATE_IDLE;
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
}

void player::update()
{
	KEYANIMANAGER->update(_playerHead);
	KEYANIMANAGER->update(_playerBody);
}

void player::render()
{
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
	if (_isLeft)	IMAGEMANAGER->findImage("player_body")->aniRenderReverseX(_posX - 24, _posY - 36 + _posZ, _playerBody_Ani);
	else			IMAGEMANAGER->findImage("player_body")->aniRender(_posX - 24, _posY - 36 + _posZ, _playerBody_Ani);
}

void player::drawHead()
{

	if (_isLeft)	IMAGEMANAGER->findImage("player_head")->aniRenderReverseX(_posX - 24, _posY - 36 + _posZ, _playerHead_Ani);
	else			IMAGEMANAGER->findImage("player_head")->aniRender(_posX - 24, _posY - 36 + _posZ, _playerHead_Ani);
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
