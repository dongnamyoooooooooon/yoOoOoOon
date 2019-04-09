#include "stdafx.h"
#include "objectManager.h"
#include "parentObj.h"

#include "floorZone_01.h"
#include "floorZone_02.h"
#include "floorBoss.h"
#include "floorShop.h"
#include "floorWater.h"
#include "floorStair.h"
#include "floorStair_nothing.h"

#include "weapon_dagger_basic.h"
#include "weapon_broadsword_basic.h"
#include "weapon_rapier_basic.h"
#include "weapon_spear_basic.h"
#include "weapon_longsword_basic.h"
#include "weapon_bow_basic.h"
#include "weapon_fiail_basic.h"
#include "weapon_blunderbuss.h"
#include "weapon_golden_lute.h"

#include "shovel_basic.h"
#include "shovel_titanium.h"
#include "shovel_glass.h"
#include "shovel_obsidian.h"
#include "shovel_blood.h"
#include "shovel_crystal.h"
#include "shovel_glass_shard.h"

#include "armor_Gi.h"
#include "armor_leather.h"
#include "armor_chainmail.h"
#include "armor_platemail.h"
#include "armor_heavyplate.h"
#include "armor_obsidian.h"
#include "armor_glass.h"

#include "torch_basic.h"
#include "torch_bright.h"

#include "item_coin.h"
#include "item_food_1.h"
#include "item_food_2.h"
#include "item_food_3.h"
#include "item_food_4.h"

#include "wallZone_01.h"
#include "wallZone_02.h"
#include "wallShop.h"
#include "wallShop_Cracked.h"
#include "wallStone_01.h"
#include "wallStone_02.h"
#include "wallCatacomb.h"
#include "wallBoss.h"
#include "wallStone_Cracked_01.h"
#include "wallStone_Cracked_02.h"
#include "wallEnd.h"
#include "wallDoor_front.h"
#include "wallDoor_side.h"

#include "enemy_skeleton.h"
#include "enemy_skeleton_yellow.h"
#include "enemy_skeleton_black.h"
#include "enemy_skeleton_mage.h"
#include "enemy_skeleton_mage_yellow.h"
#include "enemy_skeleton_mage_black.h"
#include "enemy_zombie.h"
#include "enemy_clone.h"
#include "enemy_slime_blue.h"
#include "enemy_slime_green.h"
#include "enemy_dragon_green.h"
#include "enemy_banshee.h"
#include "enemy_armadillo.h"
#include "enemy_bat.h"
#include "enemy_bat_red.h"
#include "enemy_bat_boss.h"
#include "enemy_minotaur.h"
#include "enemy_coralriff_drums.h"
#include "enemy_coralriff_horns.h"
#include "enemy_coralriff_keytar.h"
#include "enemy_coralriff_strings.h"
#include "enemy_coralriff_head.h"
#include "enemy_shopkeeper.h"


objectManager::objectManager()
{
}

objectManager::~objectManager()
{
}

HRESULT objectManager::init()
{

	for (UINT i = 0; i < _tileY; i++)
	{
		vector<parentObj*> vFloorTile;
		vector<parentObj*> vObjectTile;
		for (UINT j = 0; j < _tileX; j++)
		{
			parentObj* floorTile = new parentObj;
			parentObj* objTile = new parentObj;

			floorTile = NULL;
			objTile = NULL;

			vFloorTile.push_back(floorTile);
			vObjectTile.push_back(objTile);
		}
		_vvFloorTile.push_back(vFloorTile);
		_vvObjTile.push_back(vObjectTile);
	}


	return S_OK;
}

void objectManager::release()
{
}

void objectManager::update()
{
	SOUNDMANAGER->getSingShopkeeper(_musicKey);


	if (_vBeat.begin()->beat <= _playTime + 400 && _vBeat.begin()->beat >= _playTime - 400 && !_player->getIsBeat() && !_isGiveBeatTime)
	{
		_player->setIsBeat(true);
		_isGiveBeatTime = true;
	}

	if (_vBeat.begin()->beat < _playTime - 50)
	{
		for (_viObj = _vObj.begin(); _viObj != _vObj.end(); _viObj++)
		{
			if ((*_viObj)->getObjType() == OBJECT_TYPE_PLAYER || (*_viObj)->getObjType() == OBJECT_TYPE_WALL) continue;

			if (_isPlayerAlive)
			{
				(*_viObj)->setIsBeat(true);
			}

			if (_player->getIsBeat())
			{
				breakChain();
			}
			_player->setIsBeat(false);
			_isGiveBeatTime = false;
		}
		_player->bounceHeart();
		_vBeat.erase(_vBeat.begin());
	}

	if (_vBeat.size() <= 0)
	{
		replaySong();
	}
}

void objectManager::render()
{
	objectSort_IndexX();
	objectSort_IndexY();

	_viObj = _vObj.begin();


	for (_viObj; _viObj != _vObj.end(); ++_viObj)
	{
		//POINTF temp = (*_viObj)->getPos();

		if ((*_viObj)->getObjType() == OBJECT_TYPE_FLOOR)
		{
			if (_vvObjTile[(*_viObj)->getIdxY()][(*_viObj)->getIdxX()] == NULL)
			{
				(*_viObj)->render();
			}
			else if (_vvObjTile[(*_viObj)->getIdxY()][(*_viObj)->getIdxX()]->getImgName() == IMAGE_NAME[IMAGE_NAME_DOOR_01] ||
				_vvObjTile[(*_viObj)->getIdxY()][(*_viObj)->getIdxX()]->getImgName() == IMAGE_NAME[IMAGE_NAME_DOOR_02])
			{
				(*_viObj)->render();
			}
			else if (_vvObjTile[(*_viObj)->getIdxY()][(*_viObj)->getIdxX()]->getObjType() != OBJECT_TYPE_WALL)
			{
				(*_viObj)->render();
			}
		}
	}

	_viObj = _vObj.begin();
	for (_viObj; _viObj != _vObj.end(); ++_viObj)
	{
		//POINTF temp = (*_viObj)->getPos();
		if ((*_viObj)->getObjType() != OBJECT_TYPE_FLOOR)
		{
			(*_viObj)->render();
		}
	}

	_viObj = _vObj.begin();
	for (_viObj; _viObj != _vObj.end(); ++_viObj)
	{
		if ((*_viObj)->getImgName() == "enemy_coralriff_drums" || (*_viObj)->getImgName() == "enemy_coralriff_horns" ||
			(*_viObj)->getImgName() == "enemy_coralriff_keytar" || (*_viObj)->getImgName() == "enemy_coralriff_strings" ||
			(*_viObj)->getImgName() == "enemy_coralriff_head")
		{
			(*_viObj)->render();
		}
	}

	player* tempPlayer = OBJECTMANAGER->getPlayer();

	if (_isEffectUse)
	{
		if (tempPlayer->getPlayerWeapon()->getImgName() == "weapon_bow_basic")
		{
			switch (_player->getAttDir())
			{
			case PLAYER_STATE_JUMP_LEFT:
				for (int i = 0; i < _rangeVal; i++)
				{
					_effectHImg->frameRenderReverseX(tempPlayer->getPlayerPosX() - 78 - i * 52, tempPlayer->getPlayerPosY() - 26 - _subY, 6 - _effectX - i, 0);
				}
				break;

			case PLAYER_STATE_JUMP_RIGHT:
				for (int i = 0; i < _rangeVal; i++)
				{
					_effectHImg->frameRender(tempPlayer->getPlayerPosX() + 26 + i * 52, tempPlayer->getPlayerPosY() - 26 - _subY, _effectX - i, 0);
				}
				break;

			case PLAYER_STATE_JUMP_UP:
				for (int i = 0; i < _rangeVal; i++)
				{
					_effectVImg->frameRenderReverseY(tempPlayer->getPlayerPosX() - 26 - _subX, tempPlayer->getPlayerPosY() - 78 - i * 52, 0, 6 - _effectY - i);
				}
				break;

			case PLAYER_STATE_JUMP_DOWN:
				for (int i = 0; i < _rangeVal; i++)
				{
					_effectVImg->frameRender(tempPlayer->getPlayerPosX() - 26 - _subX, tempPlayer->getPlayerPosY() + 26 + i * 52, 0, 6 - _effectY - i);
				}
				break;

			}

		}
		else if (tempPlayer->getPlayerWeapon()->getImgName() == "weapon_spear_basic")
		{
			if (tempPlayer->getIsLong())
			{
				if (tempPlayer->getAttDir() == PLAYER_STATE_JUMP_LEFT)
				{
					_effectHImg->frameRenderReverseX(tempPlayer->getPlayerPosX() - 78 - 26, tempPlayer->getPlayerPosY() - 26 - _subY, _effectX, 0);
				}
				else if (tempPlayer->getAttDir() == PLAYER_STATE_JUMP_RIGHT)
				{
					_effectHImg->frameRender(tempPlayer->getPlayerPosX() + 26 + 26, tempPlayer->getPlayerPosY() - 26 - _subY, _effectX, 0);
				}
				else if (tempPlayer->getAttDir() == PLAYER_STATE_JUMP_UP)
				{
					_effectVImg->frameRenderReverseY(tempPlayer->getPlayerPosX() - 26 - _subX, tempPlayer->getPlayerPosY() - 78 - 52, 0, _effectY);
				}
				else if (tempPlayer->getAttDir() == PLAYER_STATE_JUMP_DOWN)
				{
					_effectVImg->frameRender(tempPlayer->getPlayerPosX() - 26 - _subX, tempPlayer->getPlayerPosY() + 26 + 26, 0, _effectY);
				}
			}
			else
			{
				if (tempPlayer->getAttDir() == PLAYER_STATE_JUMP_LEFT)
				{
					_effectHImg->frameRenderReverseX(tempPlayer->getPlayerPosX() - 78, tempPlayer->getPlayerPosY() - 26 - _subY, _effectX, 0);
				}
				else if (tempPlayer->getAttDir() == PLAYER_STATE_JUMP_RIGHT)
				{
					_effectHImg->frameRender(tempPlayer->getPlayerPosX() + 26, tempPlayer->getPlayerPosY() - 26 - _subY, _effectX, 0);
				}
				else if (tempPlayer->getAttDir() == PLAYER_STATE_JUMP_UP)
				{
					_effectVImg->frameRenderReverseY(tempPlayer->getPlayerPosX() - 26 - _subX, tempPlayer->getPlayerPosY() - 78, 0, _effectY);
				}
				else if (tempPlayer->getAttDir() == PLAYER_STATE_JUMP_DOWN)
				{
					_effectVImg->frameRender(tempPlayer->getPlayerPosX() - 26 - _subX, tempPlayer->getPlayerPosY() + 26, 0, _effectY);
				}
			}
		}
		else if (tempPlayer->getPlayerWeapon()->getImgName() == "weapon_longsword_basic" || tempPlayer->getPlayerWeapon()->getImgName() == "weapon_fiail_basic")
		{
			if (tempPlayer->getAttDir() == PLAYER_STATE_JUMP_LEFT)
			{
				_effectHImg->frameRenderReverseX(tempPlayer->getPlayerPosX() - 78 - 26, tempPlayer->getPlayerPosY() - 26 - _subY, _effectX, 0);
			}
			else if (tempPlayer->getAttDir() == PLAYER_STATE_JUMP_RIGHT)
			{
				_effectHImg->frameRender(tempPlayer->getPlayerPosX() + 26 + 26, tempPlayer->getPlayerPosY() - 26 - _subY, _effectX, 0);
			}
			else if (tempPlayer->getAttDir() == PLAYER_STATE_JUMP_UP)
			{
				_effectVImg->frameRenderReverseY(tempPlayer->getPlayerPosX() - 26 - _subX, tempPlayer->getPlayerPosY() - 78 - 52, 0, _effectY);
			}
			else if (tempPlayer->getAttDir() == PLAYER_STATE_JUMP_DOWN)
			{
				_effectVImg->frameRender(tempPlayer->getPlayerPosX() - 26 - _subX, tempPlayer->getPlayerPosY() + 26 + 52, 0, _effectY);
			}
		}
		else if (tempPlayer->getPlayerWeapon()->getImgName() == "weapon_blunderbuss")
		{
			if (tempPlayer->getAttDir() == PLAYER_STATE_JUMP_LEFT)
			{
				_effectHImg->frameRenderReverseX(tempPlayer->getPlayerPosX() - 78 - 128, tempPlayer->getPlayerPosY() + 10 - _subY, _effectX, 0);
			}
			else if (tempPlayer->getAttDir() == PLAYER_STATE_JUMP_RIGHT)
			{
				_effectHImg->frameRender(tempPlayer->getPlayerPosX() + 26 + 16, tempPlayer->getPlayerPosY() + 26 - _subY, _effectX, 0);
			}
			else if (tempPlayer->getAttDir() == PLAYER_STATE_JUMP_UP)
			{
				_effectVImg->frameRenderReverseY(tempPlayer->getPlayerPosX() - 52 - _subX, tempPlayer->getPlayerPosY() - 78 - 156, 0, _effectY);
			}
			else if (tempPlayer->getAttDir() == PLAYER_STATE_JUMP_DOWN)
			{
				_effectVImg->frameRender(tempPlayer->getPlayerPosX() - 52 - _subX, tempPlayer->getPlayerPosY() + 26, 0, _effectY);
			}
		}
		else if (_player->getPlayerWeapon()->getImgName() == "weapon_golden_lute")
		{
			if (tempPlayer->getAttDir() == PLAYER_STATE_JUMP_LEFT)
			{
				_effectHImg->frameRender(tempPlayer->getPlayerPosX(), tempPlayer->getPlayerPosY() - 10 - _posZ, 0, 0, _ruteAlpha);
			}
			else if (tempPlayer->getAttDir() == PLAYER_STATE_JUMP_RIGHT)
			{
				_effectHImg->frameRender(tempPlayer->getPlayerPosX(), tempPlayer->getPlayerPosY() - 10 - _posZ, 0, 0, _ruteAlpha);
			}
			else if (tempPlayer->getAttDir() == PLAYER_STATE_JUMP_UP)
			{
				_effectVImg->frameRender(tempPlayer->getPlayerPosX(), tempPlayer->getPlayerPosY() - 10 - _posZ, 0, 0, _ruteAlpha);
			}
			else if (tempPlayer->getAttDir() == PLAYER_STATE_JUMP_DOWN)
			{
				_effectVImg->frameRender(tempPlayer->getPlayerPosX(), tempPlayer->getPlayerPosY() - 10 - _posZ, 0, 0, _ruteAlpha);
			}
		}
		else
		{
			if (tempPlayer->getAttDir() == PLAYER_STATE_JUMP_LEFT)
			{
				_effectHImg->frameRenderReverseX(tempPlayer->getPlayerPosX() - 78, tempPlayer->getPlayerPosY() - 26 - _subY, _effectX, 0);
			}
			else if (tempPlayer->getAttDir() == PLAYER_STATE_JUMP_RIGHT)
			{
				_effectHImg->frameRender(tempPlayer->getPlayerPosX() + 26, tempPlayer->getPlayerPosY() - 26 - _subY, _effectX, 0);
			}
			else if (tempPlayer->getAttDir() == PLAYER_STATE_JUMP_UP)
			{
				_effectVImg->frameRenderReverseY(tempPlayer->getPlayerPosX() - 26 - _subX, tempPlayer->getPlayerPosY() - 78, 0, _effectY);
			}
			else if (tempPlayer->getAttDir() == PLAYER_STATE_JUMP_DOWN)
			{
				_effectVImg->frameRender(tempPlayer->getPlayerPosX() - 26 - _subX, tempPlayer->getPlayerPosY() + 26, 0, _effectY);
			}
		}
	}


	/*_viObj = _vObj.begin();
	for (_viObj; _viObj != _vObj.end(); ++_viObj)
	{
		if ((*_viObj)->getObjType() == OBJECT_TYPE_PLAYER)
		{
			(*_viObj)->render();
		}
	}*/

	mageMagic();

	//비트
	//RECT rc;

	for (_viBeat = _vBeat.begin(); _viBeat != _vBeat.end(); _viBeat++)
	{
		if (_viBeat->beat < 1500)
		{
			_viBeat->img->render(CAMERA->getPosX() + _viBeat->left_RC.left, CAMERA->getPosY() + _viBeat->left_RC.top, 10, 48, 1.0f);
			_viBeat->img->render(CAMERA->getPosX() + _viBeat->right_RC.left, CAMERA->getPosY() + _viBeat->right_RC.top, 10, 48, 1.0f);
		}
		else
		{
			_viBeat->img->render(CAMERA->getPosX() + _viBeat->left_RC.left, CAMERA->getPosY() + _viBeat->left_RC.top, 10, 48, _viBeat->alpha);
			_viBeat->img->render(CAMERA->getPosX() + _viBeat->right_RC.left, CAMERA->getPosY() + _viBeat->right_RC.top, 10, 48, _viBeat->alpha);
		}
	}

	if (_vBeat.begin()->left_RC.right <= WINSIZEX / 2)
		IMAGEMANAGER->findImage("ui_beat_heart")->frameRender2((CAMERA->getPosX() + (WINSIZEX / 2) - 40), CAMERA->getPosY() + WINSIZEY - 124, 0, 0);
	else
		IMAGEMANAGER->findImage("ui_beat_heart")->frameRender2((CAMERA->getPosX() + (WINSIZEX / 2) - 40), CAMERA->getPosY() + WINSIZEY - 124, 1, 0);

	IMAGEMANAGER->render("ui_multiplier", CAMERA->getPosX() + WINSIZEX / 2 - 80, CAMERA->getPosY() + WINSIZEY - 20);
	IMAGEMANAGER->findImage("ui_digit")->frameRender(CAMERA->getPosX() + WINSIZEX / 2 + 10, CAMERA->getPosY() + WINSIZEY - 25, 1 + _chainCount, 0);

	_player->drawEquipUI();
	_player->drawPlayerUI();




	//WCHAR str[128];
	//swprintf_s(str, L"%d", _time);
	//D2DMANAGER->drawText(str, CAMERA->getPosX() + 10, CAMERA->getPosY() + 200, 50, RGB(255, 0, 255));
	//swprintf_s(str, L"%d", SOUNDMANAGER->getPosition(_musicKey));
	//D2DMANAGER->drawText(str, CAMERA->getPosX() + 10, CAMERA->getPosY() + 270, 50, RGB(255, 0, 255));

}

void objectManager::vectorClear()
{
	for (UINT i = 0; i < _tileY; i++)
	{
		for (UINT j = 0; i < _tileX; j++)
		{
			_vvObjTile[i][j] = nullptr;
			_vvFloorTile[i][j] = nullptr;
		}
	}
}

void objectManager::objectSort_IndexY()
{
	sort(_vObj.begin(), _vObj.end(), [](parentObj* a, parentObj* b) { return a->getIdxY() < b->getIdxY(); });
}

void objectManager::objectSort_IndexX()
{
	sort(_vObj.begin(), _vObj.end(), [](parentObj* a, parentObj* b) { return a->getIdxX() < b->getIdxX(); });
}

void objectManager::allObjectUpdate()
{
	for (UINT i = 0; i < _tileY; i++)
	{
		for (UINT j = 0; j < _tileX; j++)
		{
			if (_vvFloorTile[i][j] != NULL)
			{
				_vvFloorTile[i][j]->update();
			}

			if (_vvObjTile[i][j] != NULL)
			{
				if (_vvObjTile[i][j]->getObjType() == OBJECT_TYPE_PLAYER) continue;
				else _vvObjTile[i][j]->update();
			}
		}
	}
	KEYANIMANAGER->update("enemy_slime_blue");
	KEYANIMANAGER->update("enemy_slime_green");
	KEYANIMANAGER->update("enemy_zombie");
	KEYANIMANAGER->update("enemy_skeleton");
	KEYANIMANAGER->update("enemy_skeleton_yellow");
	KEYANIMANAGER->update("enemy_skeleton_black");
	KEYANIMANAGER->update("enemy_skeleton_mage");
	KEYANIMANAGER->update("enemy_skeleton_mage_yellow");
	KEYANIMANAGER->update("enemy_skeleton_mage_black");
	KEYANIMANAGER->update("enemy_dragon_green");
	KEYANIMANAGER->update("enemy_banshee");
	KEYANIMANAGER->update("enemy_armadillo");
	KEYANIMANAGER->update("enemy_clone");
	KEYANIMANAGER->update("enemy_bat");
	KEYANIMANAGER->update("enemy_bat_red");
	KEYANIMANAGER->update("enemy_bat_miniboss");
	KEYANIMANAGER->update("enemy_minotaur");
	KEYANIMANAGER->update("enemy_coralriff_drums");
	KEYANIMANAGER->update("enemy_coralriff_horns");
	KEYANIMANAGER->update("enemy_coralriff_keytar");
	KEYANIMANAGER->update("enemy_coralriff_strings");
	KEYANIMANAGER->update("enemy_coralriff_head");
}

void objectManager::deleteObject(parentObj * obj)
{
	if (obj == NULL) return;

	int tempX = obj->getIdxX();
	int tempY = obj->getIdxY();

	_viObj = _vObj.begin();

	for (_viObj; _viObj != _vObj.end();)
	{
		if ((*_viObj)->getObjType() != obj->getObjType())
		{
			_viObj++;
			continue;
		}
		if ((*_viObj)->getIdxX() == tempX && (*_viObj)->getIdxY() == tempY)
		{
			delete(*_viObj);
			_viObj = _vObj.erase(_viObj);
			break;
		}
		else
			_viObj++;
	}
	_vvObjTile[tempY][tempX] = nullptr;
}

void objectManager::deleteFloorTile(parentObj * obj)
{
	int tempX = obj->getIdxX();
	int tempY = obj->getIdxY();

	_viObj = _vObj.begin();

	for (_viObj; _viObj != _vObj.end();)
	{
		if ((*_viObj)->getObjType() != obj->getObjType())
		{
			_viObj++;
			continue;
		}
		if ((*_viObj)->getIdxX() == tempX && (*_viObj)->getIdxY() == tempY)
		{
			delete(*_viObj);
			_viObj = _vObj.erase(_viObj);
			break;
		}
		else
			_viObj++;
	}
	_vvFloorTile[tempY][tempX] = nullptr;
}

void objectManager::mageMagic()
{
	if (_isMagic)
	{
		_isMagic++;
		if (_isMagic < 2)
			IMAGEMANAGER->findImage("alpha_black")->render(0, 0, WINSIZEX, WINSIZEY);
		else if (_isMagic < 4)
			IMAGEMANAGER->findImage("magic_red")->render(0, 0, WINSIZEX, WINSIZEY);
		else if (_isMagic < 6)
			IMAGEMANAGER->findImage("magic_white")->render(0, 0, WINSIZEX, WINSIZEY, 0.3f);
		else if (_isMagic < 8)
			IMAGEMANAGER->findImage("magic_gray")->render(0, 0, WINSIZEX, WINSIZEY);
		else
			_isMagic = 0;
	}

}

void objectManager::initBeat(const char * fileName, string musicKey)
{
	_beatKey = musicKey;
	SOUNDMANAGER->loadBeat(fileName, _beatKey);

	_beatFile = fileName;
	_musicKey = musicKey;

	if (_musicKey == "boss")
		SOUNDMANAGER->playBossZone(_musicKey, 1.0f);
	else if (_musicKey == "어쩌고")
		SOUNDMANAGER->playZone(_musicKey, 0.8f);
	else
		SOUNDMANAGER->play(_musicKey, 0.8f);

	_vBeat = SOUNDMANAGER->getVBeat();
	_viBeat = _vBeat.begin();
	_mBeat = SOUNDMANAGER->getMBeat();
	_miBeat = SOUNDMANAGER->getMIBeat();
}

void objectManager::createBeat()
{

	if (_musicKey == "boss")
		_playTime = SOUNDMANAGER->getPosition(_musicKey + "_bass");
	else
		_playTime = SOUNDMANAGER->getPosition(_musicKey);
	_time = SOUNDMANAGER->getLength(_musicKey);

	//RECT rc;
	for (int i = 0; i < _vBeat.size(); i++)
	{

		_vBeat[i].left_RC = { (float)(WINSIZEX / 2) - ((_vBeat[i].beat - _playTime) / 3.7f),
							 (float)WINSIZEY - 90,
							 (float)(WINSIZEX / 2) - ((_vBeat[i].beat - _playTime) / 3.7f) + 12,
							 (float)WINSIZEY - 42 };

		_vBeat[i].right_RC = { (float)(WINSIZEX / 2) + ((_vBeat[i].beat - _playTime) / 3.7f),
							  (float)WINSIZEY - 90,
							  (float)(WINSIZEX / 2) + ((_vBeat[i].beat - _playTime) / 3.7f) + 12,
							  (float)WINSIZEY - 42 };

		if (_vBeat[i].left_RC.left >= 0) _vBeat[i].alpha += 0.03f;

	}

	_failBeat = { (float)(WINSIZEX / 2) - 120,
				  (float)WINSIZEY - 90,
				  (float)(WINSIZEX / 2) + 120,
				  (float)WINSIZEY - 40 };

	_successBeat = { (float)(WINSIZEX / 2) - 70,
					(float)WINSIZEY - 90,
					(float)(WINSIZEX / 2) + 70,
					(float)WINSIZEY - 40 };


}

void objectManager::deleteBeat()
{
	if (_vBeat.begin()->beat < _playTime - 50)
	{

	}
}

void objectManager::replaySong()
{
	SOUNDMANAGER->loadBeat(_beatFile, _beatKey);

	if (_musicKey == "boss")
		SOUNDMANAGER->playBossZone(_musicKey, 1.0f);
	else
		SOUNDMANAGER->playZone(_musicKey, 1.0f);

	_vBeat = SOUNDMANAGER->getVBeat();
	_viBeat = SOUNDMANAGER->getVIBeat();
	_mBeat = SOUNDMANAGER->getMBeat();
	_miBeat = SOUNDMANAGER->getMIBeat();
}

void objectManager::weaponEff()
{
	player* _player = OBJECTMANAGER->getPlayer();

	if (_player->getPlayerWeapon()->getImgName() == "weapon_dagger_basic")
	{
		_effectHImg = IMAGEMANAGER->findImage("attack_dagger_basic");
		_effectVImg = IMAGEMANAGER->findImage("attack_dagger_basic_ver");
		_subX = 0;
		_subY = 0;
	}
	else if (_player->getPlayerWeapon()->getImgName() == "weapon_broadsword_basic")
	{
		_effectHImg = IMAGEMANAGER->findImage("attack_broadsword_basic");
		_effectVImg = IMAGEMANAGER->findImage("attack_broadsword_basic_ver");
		_subX = 26;
		_subY = 26;
	}
	else if (_player->getPlayerWeapon()->getImgName() == "weapon_rapier_basic" || _player->getPlayerWeapon()->getImgName() == "weapon_spear_basic")
	{
		if (_player->getIsLong())
		{
			_effectHImg = IMAGEMANAGER->findImage("attack_rapier_basic");
			_effectVImg = IMAGEMANAGER->findImage("attack_rapier_basic_v");
			_subX = 0;
			_subY = 26;
		}
		else
		{
			_effectHImg = IMAGEMANAGER->findImage("attack_dagger_basic");
			_effectVImg = IMAGEMANAGER->findImage("attack_dagger_basic_ver");
			_subX = 0;
			_subY = 0;
		}

	}
	else if (_player->getPlayerWeapon()->getImgName() == "weapon_longsword_basic")
	{
		if (_player->getIsLong())
		{
			_effectHImg = IMAGEMANAGER->findImage("attack_longsword_basic");
			_effectVImg = IMAGEMANAGER->findImage("attack_longsword_basic_v");
			_subX = 0;
			_subY = 26;
		}
	}
	else if (_player->getPlayerWeapon()->getImgName() == "weapon_bow_basic")
	{
		if (_player->getIsLong())
		{
			_effectHImg = IMAGEMANAGER->findImage("attack_bow_basic");
			_effectVImg = IMAGEMANAGER->findImage("attack_bow_basic_v");
			_subX = 0;
			_subY = 26;
		}
		else
		{
			_effectHImg = IMAGEMANAGER->findImage("attack_dagger_basic");
			_effectVImg = IMAGEMANAGER->findImage("attack_dagger_basic_ver");
			_subX = 0;
			_subY = 0;
		}
	}
	else if (_player->getPlayerWeapon()->getImgName() == "weapon_fiail_basic")
	{
		_effectHImg = IMAGEMANAGER->findImage("attack_flail_basic");
		_effectVImg = IMAGEMANAGER->findImage("attack_flail_basic_v");
		_subX = 26;
		_subY = 52;
	}
	else if (_player->getPlayerWeapon()->getImgName() == "weapon_blunderbuss")
	{
		_effectHImg = IMAGEMANAGER->findImage("attack_blunderbuss");
		_effectVImg = IMAGEMANAGER->findImage("attack_blunderbuss_v");
		_subX = 52;
		_subY = 150;
	}
	else if (_player->getPlayerWeapon()->getImgName() == "weapon_golden_lute")
	{
		_effectHImg = IMAGEMANAGER->findImage("attack_golden_lute");
		_effectVImg = IMAGEMANAGER->findImage("attack_golden_lute");
	}

	if (_isEffectUse)
	{
		_effectCount++;
		if (_effectCount >= 3)
		{
			_effectCount = 0;
			if (_effectX == _effectHImg->GetMaxFrameX() || _effectY == _effectVImg->GetMaxFrameY())
			{
				_isEffectUse = false;
				_effectX = 0;
				_effectY = 0;
			}
			else
			{
				_effectX++;
				_effectY++;
			}

			if (_posZ >= 15.0f)
			{
				_ruteAlpha = 1.0f;
				_posZ = 0;
				_isEffectUse = false;
			}
			else
			{
				_posZ += 0.5f;
				_ruteAlpha -= 0.1f;
			}
		}
	}
}

parentObj* objectManager::objectPush(parentObj obj)
{
	parentObj* tempObject;
	switch (obj.getObjType())
	{
	case OBJECT_TYPE_FLOOR:
	{
		tempObject = createFloor(obj);
		tempObject->setObjType(OBJECT_TYPE_FLOOR);
		if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_STAIRS_01])
			_vvObjTile[tempObject->getIdxY()][tempObject->getIdxX()] = tempObject;
		else
			_vvFloorTile[obj.getIdxY()][obj.getIdxX()] = tempObject;
		break;
	}
	case OBJECT_TYPE_WALL:
	{
		tempObject = createWall(obj);
		tempObject->setObjType(OBJECT_TYPE_WALL);
		_vvObjTile[tempObject->getIdxY()][tempObject->getIdxX()] = tempObject;
		break;
	}
	case OBJECT_TYPE_ITEM:
	{
		tempObject = createItem(obj);
		tempObject->setObjType(OBJECT_TYPE_ITEM);
		_vvObjTile[tempObject->getIdxY()][tempObject->getIdxX()] = tempObject;
		break;
	}
	case OBJECT_TYPE_ENEMY:
	{
		tempObject = createEnemy(obj);
		tempObject->setObjType(OBJECT_TYPE_ENEMY);
		_vvObjTile[tempObject->getIdxY()][tempObject->getIdxX()] = tempObject;
		break;
	}
	case OBJECT_TYPE_TRAP:
	{
		tempObject = createTrap(obj);
		tempObject->setObjType(OBJECT_TYPE_TRAP);
		_vvObjTile[tempObject->getIdxY()][tempObject->getIdxX()] = tempObject;
		break;
	}
	case OBJECT_TYPE_PLAYER:
	{
		tempObject = createPlayer(obj);
		tempObject->setObjType(OBJECT_TYPE_PLAYER);
		_vvObjTile[tempObject->getIdxY()][tempObject->getIdxX()] = tempObject;
		break;
	}
	}
	_vObj.push_back(tempObject);
	return tempObject;
}

parentObj * objectManager::createFloor(parentObj obj)
{

	if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_FLOOR_01])
	{
		floorZone_01* tempObj = new floorZone_01;
		tempObj->init(obj.getIdxX(), obj.getIdxY());
		return tempObj;
	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_FLOOR_02])
	{
		floorZone_02* tempObj = new floorZone_02;
		tempObj->init(obj.getIdxX(), obj.getIdxY());
		return tempObj;
	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_FLOOR_03])
	{
		floorBoss* tempObj = new floorBoss;
		tempObj->init(obj.getIdxX(), obj.getIdxY());
		return tempObj;
	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_FLOOR_04])
	{
		floorShop* tempObj = new floorShop;
		tempObj->init(obj.getIdxX(), obj.getIdxY());
		return tempObj;
	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_FLOOR_05])
	{
		floorWater* tempObj = new floorWater;
		tempObj->init(obj.getIdxX(), obj.getIdxY());
		return tempObj;
	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_STAIRS_01])
	{
		floorStair* tempObj = new floorStair;
		tempObj->init(obj.getIdxX(), obj.getIdxY());
		return tempObj;
	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_STAIRS_02])
	{
		floorStair_nothing* tempObj = new floorStair_nothing;
		tempObj->init(obj.getIdxX(), obj.getIdxY());
		return tempObj;
	}


	return nullptr;
}

parentObj * objectManager::createWall(parentObj obj)
{

	if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_WALL_01])
	{
		wallZone_01* tempObj = new wallZone_01;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY(), obj.getIsTorch());
		return tempObj;
	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_WALL_02])
	{
		wallZone_02* tempObj = new wallZone_02;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY(), obj.getIsTorch());
		return tempObj;
	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_WALL_03])
	{
		wallShop* tempObj = new wallShop;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY(), obj.getIsTorch());
		return tempObj;
	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_WALL_04])
	{
		wallShop_Cracked* tempObj = new wallShop_Cracked;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY(), obj.getIsTorch());
		return tempObj;
	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_WALL_05])
	{
		wallStone_01* tempObj = new wallStone_01;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY(), obj.getIsTorch());
		return tempObj;
	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_WALL_06])
	{
		wallStone_02* tempObj = new wallStone_02;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY(), obj.getIsTorch());
		return tempObj;
	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_WALL_07])
	{
		wallCatacomb* tempObj = new wallCatacomb;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY(), obj.getIsTorch());
		return tempObj;
	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_WALL_08])
	{
		wallBoss* tempObj = new wallBoss;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY(), obj.getIsTorch());
		return tempObj;
	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_WALL_09])
	{
		wallStone_Cracked_01* tempObj = new wallStone_Cracked_01;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY(), obj.getIsTorch());
		return tempObj;
	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_WALL_10])
	{
		wallStone_Cracked_02* tempObj = new wallStone_Cracked_02;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY(), obj.getIsTorch());
		return tempObj;
	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_WALL_11])
	{
		wallEnd* tempObj = new wallEnd;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY(), obj.getIsTorch());
		return tempObj;
	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_DOOR_01])
	{
		wallDoor_front* tempObj = new wallDoor_front;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY(), obj.getIsTorch());
		return tempObj;
	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_DOOR_02])
	{
		wallDoor_side* tempObj = new wallDoor_side;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY(), obj.getIsTorch());
		return tempObj;
	}

	return nullptr;
}

parentObj * objectManager::createItem(parentObj obj)
{
	if (obj.getImgName() == SHOVEL_NAME[ITEM_SHOVEL_BASIC])
	{
		shovel_basic* tempObj = new shovel_basic;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY(), ITEM_TYPE_SHOVEL);
		return tempObj;
	}
	else if (obj.getImgName() == SHOVEL_NAME[ITEM_SHOVEL_TITANIUM])
	{
		shovel_titanium* tempObj = new shovel_titanium;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY(), ITEM_TYPE_SHOVEL);
		return tempObj;
	}
	else if (obj.getImgName() == SHOVEL_NAME[ITEM_SHOVEL_GLASS])
	{
		shovel_glass* tempObj = new shovel_glass;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY(), ITEM_TYPE_SHOVEL);
		return tempObj;
	}
	else if (obj.getImgName() == SHOVEL_NAME[ITEM_SHOVEL_OBSIDIAN])
	{
		shovel_obsidian* tempObj = new shovel_obsidian;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY(), ITEM_TYPE_SHOVEL);
		return tempObj;
	}
	else if (obj.getImgName() == SHOVEL_NAME[ITEM_SHOVEL_BLOOD])
	{
		shovel_blood* tempObj = new shovel_blood;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY(), ITEM_TYPE_SHOVEL);
		return tempObj;
	}
	else if (obj.getImgName() == SHOVEL_NAME[ITEM_SHOVEL_CRYSTAL])
	{
		shovel_crystal* tempObj = new shovel_crystal;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY(), ITEM_TYPE_SHOVEL);
		return tempObj;
	}
	else if (obj.getImgName() == SHOVEL_NAME[ITEM_SHOVEL_GLASSSHARD])
	{
		shovel_glass_shard* tempObj = new shovel_glass_shard;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY(), ITEM_TYPE_SHOVEL);
		return tempObj;
	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_DAGGER_BASIC])
	{
		weapon_dagger_basic* tempObj = new weapon_dagger_basic;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY(), ITEM_TYPE_WEAPON);
		return tempObj;
	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_DAGGER_TITANIUM])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_DAGGER_GLASS])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_DAGGER_OBSIDIAN])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_DAGGER_BLOOD])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_DAGGER_GOLD])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_BROADSWORD_BASIC])
	{
		weapon_broadsword_basic* tempObj = new weapon_broadsword_basic;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY(), ITEM_TYPE_WEAPON);
		return tempObj;
	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_BROADSWORD_TITANIUM])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_BROADSWORD_GLASS])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_BROADSWORD_OBSIDIAN])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_BROADSWORD_BLOOD])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_BROADSWORD_GOLD])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_RAPIER_BASIC])
	{
		weapon_rapier_basic* tempObj = new weapon_rapier_basic;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY(), ITEM_TYPE_WEAPON);
		return tempObj;
	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_RAPIER_TITANIUM])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_RAPIER_GLASS])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_RAPIER_OBSIDIAN])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_RAPIER_BLOOD])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_RAPIER_GOLD])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_SPEAR_BASIC])
	{
		weapon_spear_basic* tempObj = new weapon_spear_basic;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY(), ITEM_TYPE_WEAPON);
		return tempObj;
	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_SPEAR_TITANIUM])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_SPEAR_GLASS])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_SPEAR_OBSIDIAN])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_SPEAR_BLOOD])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_SPEAR_GOLD])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_LONGSWORD_BASIC])
	{
		weapon_longsword_basic* tempObj = new weapon_longsword_basic;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY(), ITEM_TYPE_WEAPON);
		return tempObj;
	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_LONGSWORD_TITANIUM])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_LONGSWORD_GLASS])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_LONGSWORD_OBSIDIAN])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_LONGSWORD_BLOOD])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_LONGSWORD_GOLD])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_WHIP_BASIC])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_WHIP_TITANIUM])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_WHIP_GLASS])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_WHIP_OBSIDIAN])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_WHIP_BLOOD])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_WHIP_GOLD])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_BOW_BASIC])
	{
		weapon_bow_basic* tempObj = new weapon_bow_basic;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY(), ITEM_TYPE_WEAPON);
		return tempObj;
	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_BOW_TITANIUM])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_BOW_GLASS])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_BOW_OBSIDIAN])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_BOW_BLOOD])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_BOW_GOLD])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_CROSSBOW_BASIC])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_CROSSBOW_TITANIUM])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_CROSSBOW_GLASS])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_CROSSBOW_OBSIDIAN])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_CROSSBOW_BLOOD])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_CROSSBOW_GOLD])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_NINETAILS_BASIC])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_NINETAILS_TITANIUM])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_NINETAILS_GLASS])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_NINETAILS_OBSIDIAN])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_NINETAILS_BLOOD])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_NINETAILS_GOLD])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_FIAIL_BASIC])
	{
		weapon_fiail_basic* tempObj = new weapon_fiail_basic;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY(), ITEM_TYPE_WEAPON);
		return tempObj;
	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_FIAIL_TITANIUM])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_FIAIL_GLASS])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_FIAIL_OBSIDIAN])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_FIAIL_BLOOD])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_FIAIL_GOLD])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_BLUNDERBUSS])
	{
		weapon_blunderbuss* tempObj = new weapon_blunderbuss;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY(), ITEM_TYPE_WEAPON);
		return tempObj;
	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_RIFLE])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_GLASSSHARD])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_JEWELEDDAGGER])
	{

	}
	else if (obj.getImgName() == WEAPON_NAME[ITEM_WEAPON_GOLDENLUTE])
	{
		weapon_golden_lute* tempObj = new weapon_golden_lute;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY(), ITEM_TYPE_WEAPON);
		return tempObj;
	}
	else if (obj.getImgName() == TORCH_NAME[ITEM_TORCH_BASIC])
	{
		torch_basic* tempObj = new torch_basic;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY(), ITEM_TYPE_TORCH);
		return tempObj;
	}
	else if (obj.getImgName() == TORCH_NAME[ITEM_TORCH_BRIGHT])
	{
		torch_bright* tempObj = new torch_bright;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY(), ITEM_TYPE_TORCH);
		return tempObj;
	}
	else if (obj.getImgName() == TORCH_NAME[ITEM_TORCH_LUMINIOUS])
	{

	}
	else if (obj.getImgName() == TORCH_NAME[ITEM_TORCH_GLASS])
	{

	}
	else if (obj.getImgName() == TORCH_NAME[ITEM_TORCH_OBSIDIAN])
	{

	}
	else if (obj.getImgName() == TORCH_NAME[ITEM_TORCH_INFERNAL])
	{

	}
	else if (obj.getImgName() == TORCH_NAME[ITEM_TORCH_FORESIGHT])
	{

	}
	else if (obj.getImgName() == ARMOR_NAME[ITEM_ARMOR_LEATHER])
	{
		armor_leather* tempObj = new armor_leather;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY(), ITEM_TYPE_ARMOR);
		return tempObj;
	}
	else if (obj.getImgName() == ARMOR_NAME[ITEM_ARMOR_CHAINMAIL])
	{
		armor_chainmail* tempObj = new armor_chainmail;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY(), ITEM_TYPE_ARMOR);
		return tempObj;
	}
	else if (obj.getImgName() == ARMOR_NAME[ITEM_ARMOR_PLATEMAIL])
	{
		armor_platemail* tempObj = new armor_platemail;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY(), ITEM_TYPE_ARMOR);
		return tempObj;
	}
	else if (obj.getImgName() == ARMOR_NAME[ITEM_ARMOR_HEAVYPLATE])
	{
		armor_heavyplate* tempObj = new armor_heavyplate;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY(), ITEM_TYPE_ARMOR);
		return tempObj;
	}
	else if (obj.getImgName() == ARMOR_NAME[ITEM_ARMOR_KARADE])
	{
		armor_Gi* tempObj = new armor_Gi;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY(), ITEM_TYPE_ARMOR);
		return tempObj;
	}
	else if (obj.getImgName() == ARMOR_NAME[ITEM_ARMOR_OBSIDIAN])
	{
		armor_obsidian* tempObj = new armor_obsidian;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY(), ITEM_TYPE_ARMOR);
		return tempObj;
	}
	else if (obj.getImgName() == ARMOR_NAME[ITEM_ARMOR_GLASS])
	{
		armor_glass* tempObj = new armor_glass;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY(), ITEM_TYPE_ARMOR);
		return tempObj;
	}
	else if (obj.getImgName() == HEADWEAR_NAME[ITEM_HEADWEAR_HELMAT])
	{

	}
	else if (obj.getImgName() == HEADWEAR_NAME[ITEM_HEADWEAR_BLASTHELM])
	{

	}
	else if (obj.getImgName() == HEADWEAR_NAME[ITEM_HEADWEAR_TELEPORT])
	{

	}
	else if (obj.getImgName() == FOOTWEAR_NAME[ITEM_FOOTWEAR_BALLET])
	{

	}
	else if (obj.getImgName() == FOOTWEAR_NAME[ITEM_FOOTWEAR_WINGED])
	{

	}
	else if (obj.getImgName() == FOOTWEAR_NAME[ITEM_FOOTWEAR_LEAD])
	{

	}
	else if (obj.getImgName() == FOOTWEAR_NAME[ITEM_FOOTWEAR_HARGREAVES])
	{

	}
	else if (obj.getImgName() == FOOTWEAR_NAME[ITEM_FOOTWEAR_STRENGTH])
	{

	}
	else if (obj.getImgName() == CONSUMABLE_NAME[ITEM_CONSUMABLE_APPLE])
	{
		item_food_1* tempObj = new item_food_1;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY(), ITEM_TYPE_CONSUMABLE);
		return tempObj;
	}
	else if (obj.getImgName() == CONSUMABLE_NAME[ITEM_CONSUMABLE_CHEESE])
	{
		item_food_2* tempObj = new item_food_2;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY(), ITEM_TYPE_CONSUMABLE);
		return tempObj;
	}
	else if (obj.getImgName() == CONSUMABLE_NAME[ITEM_CONSUMABLE_DRUMSTICK])
	{
		item_food_3* tempObj = new item_food_3;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY(), ITEM_TYPE_CONSUMABLE);
		return tempObj;
	}
	else if (obj.getImgName() == CONSUMABLE_NAME[ITEM_CONSUMABLE_HAM])
	{
		item_food_4* tempObj = new item_food_4;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY(), ITEM_TYPE_CONSUMABLE);
		return tempObj;
	}
	else if (obj.getImgName() == CONSUMABLE_NAME[ITEM_CONSUMABLE_WARDRUM])
	{

	}
	else if (obj.getImgName() == BOMB_NAME[ITEM_BOMB_X1])
	{

	}
	else if (obj.getImgName() == BOMB_NAME[ITEM_BOMB_X3])
	{

	}
	else if (obj.getImgName() == HEART_NAME[ITEM_HEART_FILLED])
	{

	}
	else if (obj.getImgName() == HEART_NAME[ITEM_HEART_DOUBLE_FILLED])
	{

	}
	else if (obj.getImgName() == HEART_NAME[ITEM_HEART_EMPTY])
	{

	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_CHEST])
	{

	}

	return nullptr;
}

parentObj * objectManager::createEnemy(parentObj obj)
{
	if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_ENEMY_SKELETON])
	{
		enemy_skeleton* tempObj = new enemy_skeleton;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY());
		return tempObj;
	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_ENEMY_SKELETON_YELLOW])
	{
		enemy_skeleton_yellow* tempObj = new enemy_skeleton_yellow;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY());
		return tempObj;
	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_ENEMY_SKELETON_BLACK])
	{
		enemy_skeleton_black* tempObj = new enemy_skeleton_black;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY());
		return tempObj;
	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_ENEMY_SKELETON_MAGE_WHITE])
	{
		enemy_skeleton_mage* tempObj = new enemy_skeleton_mage;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY());
		return tempObj;
	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_ENEMY_SKELETON_MAGE_YELLOW])
	{
		enemy_skeleton_mage_yellow* tempObj = new enemy_skeleton_mage_yellow;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY());
		return tempObj;
	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_ENEMY_SKELETON_MAGE_BLACK])
	{
		enemy_skeleton_mage_black* tempObj = new enemy_skeleton_mage_black;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY());
		return tempObj;
	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_ENEMY_ARMADILLO])
	{
		enemy_armadillo* tempObj = new enemy_armadillo;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY());
		return tempObj;
	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_ENEMY_SLIME_GREEN])
	{
		enemy_slime_green* tempObj = new enemy_slime_green;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY());
		return tempObj;
	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_ENEMY_SLIME_BLUE])
	{
		enemy_slime_blue* tempObj = new enemy_slime_blue;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY());
		return tempObj;
	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_ENEMY_ZOMBIE])
	{
		enemy_zombie* tempObj = new enemy_zombie;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY());
		return tempObj;
	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_ENEMY_BAT])
	{
		enemy_bat* tempObj = new enemy_bat;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY());
		return tempObj;
	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_ENEMY_BAT_RED])
	{
		enemy_bat_red* tempObj = new enemy_bat_red;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY());
		return tempObj;
	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_ENEMY_CLONE])
	{
		enemy_clone* tempObj = new enemy_clone;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY());
		return tempObj;
	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_ENEMY_BAT_MINIBOSS])
	{
		enemy_bat_boss* tempObj = new enemy_bat_boss;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY());
		return tempObj;
	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_ENEMY_BANSHEE])
	{
		enemy_banshee* tempObj = new enemy_banshee;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY());
		return tempObj;
	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_ENEMY_DRAGON_GREEN])
	{
		enemy_dragon_green* tempObj = new enemy_dragon_green;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY());
		return tempObj;
	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_ENEMY_MINOTAUR])
	{
		enemy_minotaur* tempObj = new enemy_minotaur;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY());
		return tempObj;
	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_ENEMY_CORALRIFF_DRUMS])
	{
		enemy_coralriff_drums* tempObj = new enemy_coralriff_drums;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY());
		return tempObj;
	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_ENEMY_CORALRIFF_HEAD])
	{
		enemy_coralriff_head* tempObj = new enemy_coralriff_head;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY());
		return tempObj;
	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_ENEMY_CORALRIFF_HORNS])
	{
		enemy_coralriff_horns* tempObj = new enemy_coralriff_horns;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY());
		return tempObj;
	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_ENEMY_CORALRIFF_KEYTAR])
	{
		enemy_coralriff_keytar* tempObj = new enemy_coralriff_keytar;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY());
		return tempObj;
	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_ENEMY_CORALRIFF_STRINGS])
	{
		enemy_coralriff_strings* tempObj = new enemy_coralriff_strings;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY());
		return tempObj;
	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_ENEMY_SHOPKEEPER])
	{
		enemy_shopkeeper* tempObj = new enemy_shopkeeper;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY());
		return tempObj;
	}


	return nullptr;
}

parentObj * objectManager::createTrap(parentObj obj)
{
	if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_TRAP_BOUNCE])
	{

	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_TRAP_SLOWDOWN])
	{

	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_TRAP_SPEEDUP])
	{

	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_TRAP_SPIKE])
	{

	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_FLOOR_01])
	{

	}
	return nullptr;
}

parentObj * objectManager::createPlayer(parentObj obj)
{
	player* newObj = new player;

	newObj->init(obj.getIdxX(), obj.getIdxY());
	_player = newObj;
	return newObj;
}

void objectManager::grooveChain()
{
	if (_chainCount == 0)
	{
		_chainCount++;
		//사운드 적용
		SOUNDMANAGER->play("sound_chain_groove", 1.0f);
	}

	_killCount++;

	if (_killCount % 5 == 0 && _chainCount < 4)
	{
		_chainCount++;
		//사운드 적용
		SOUNDMANAGER->play("sound_chain_groove", 1.0f);
	}

}

void objectManager::breakChain()
{
	if (_chainCount != 0)
	{
		SOUNDMANAGER->play("sound_chain_break");
		_killCount = 0;
		_chainCount = 0;
	}


}

void objectManager::initLight()
{
	_viObj2 = _vObj.begin();
	for (_viObj2; _viObj2 != _vObj.end(); _viObj2++)
	{
		if ((*_viObj2)->getObjType() != OBJECT_TYPE_PLAYER)
		{
			(*_viObj2)->setHasLight(false);
			(*_viObj2)->setIsSight(false);
		}
	}
}

void objectManager::initSight()
{
	_viObj2 = _vObj.begin();
	for (_viObj2; _viObj2 != _vObj.end(); _viObj2++)
	{
		if ((*_viObj2)->getObjType() != OBJECT_TYPE_PLAYER)
		{
			if ((*_viObj2)->getImgName() == IMAGE_NAME[IMAGE_NAME_WALL_11]) continue;

			(*_viObj2)->setIsSaw();
		}
	}
}
