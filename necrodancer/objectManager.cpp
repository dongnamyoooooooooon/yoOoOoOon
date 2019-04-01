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
#include "shovel_basic.h"
#include "armor_Gi.h"
#include "armor_leather.h"
#include "armor_chainmail.h"
#include "armor_platemail.h"
#include "armor_heavyplate.h"
#include "armor_obsidian.h"
#include "armor_glass.h"
#include "torch_basic.h"
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


	if (_vBeat.begin()->beat <= _playTime + 300 && _vBeat.begin()->beat >= _playTime - 300 && !_player->getIsBeat() && !_isGiveBeatTime)
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
		if (_musicKey != "어쩌고 저쩌고") _vBeat.erase(_vBeat.begin());
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

	_player->drawEquipUI();
	_player->drawPlayerUI();

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
}

void objectManager::deleteObject(parentObj * obj)
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
	_vvObjTile[tempY][tempX] = nullptr;
}

void objectManager::initBeat(const char * fileName, string musicKey)
{
	SOUNDMANAGER->loadBeat(fileName, _beatKey);

	_beatFile = fileName;
	_musicKey = musicKey;

	if (_musicKey == "boss")
		SOUNDMANAGER->playBossZone(_musicKey, _volume);
	else
		SOUNDMANAGER->playZone(_musicKey, 0.1f);

	_vBeat = SOUNDMANAGER->getVBeat();
	_viBeat = SOUNDMANAGER->getVIBeat();
	_mBeat = SOUNDMANAGER->getMBeat();
	_miBeat = SOUNDMANAGER->getMIBeat();
}

void objectManager::createBeat()
{

	_playTime = SOUNDMANAGER->getPosition(_musicKey);

	//RECT rc;
	for (_viBeat = _vBeat.begin(); _viBeat != _vBeat.end(); _viBeat++)
	{

		_viBeat->left_RC = { (float)(WINSIZEX / 2) - ((_viBeat->beat - _playTime) / 3.7f),
							 (float)WINSIZEY - 90,
							 (float)(WINSIZEX / 2) - ((_viBeat->beat - _playTime) / 3.7f) + 12,
							 (float)WINSIZEY - 42 };

		_viBeat->right_RC = { (float)(WINSIZEX / 2) + ((_viBeat->beat - _playTime) / 3.7f),
							  (float)WINSIZEY - 90,
							  (float)(WINSIZEX / 2) + ((_viBeat->beat - _playTime) / 3.7f) + 12,
							  (float)WINSIZEY - 42 };


		if (_viBeat->beat >= (SOUNDMANAGER->getLength(_musicKey) - (SOUNDMANAGER->getLength(_musicKey) / 6)))
			_viBeat->img = IMAGEMANAGER->findImage("ui_beat_marker_red");
		else
			_viBeat->img = IMAGEMANAGER->findImage("ui_beat_marker");

		if (_viBeat->left_RC.left >= 0) _viBeat->alpha += 0.03f;

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

	}
	else if (obj.getImgName() == SHOVEL_NAME[ITEM_SHOVEL_GLASS])
	{

	}
	else if (obj.getImgName() == SHOVEL_NAME[ITEM_SHOVEL_OBSIDIAN])
	{

	}
	else if (obj.getImgName() == SHOVEL_NAME[ITEM_SHOVEL_BLOOD])
	{

	}
	else if (obj.getImgName() == SHOVEL_NAME[ITEM_SHOVEL_CRYSTAL])
	{

	}
	else if (obj.getImgName() == SHOVEL_NAME[ITEM_SHOVEL_GLASSSHARD])
	{

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

	}
	else if (obj.getImgName() == TORCH_NAME[ITEM_TORCH_BASIC])
	{
		torch_basic* tempObj = new torch_basic;
		tempObj->init(obj.getImgName(), obj.getIdxX(), obj.getIdxY(), ITEM_TYPE_TORCH);
		return tempObj;
	}
	else if (obj.getImgName() == TORCH_NAME[ITEM_TORCH_BRIGHT])
	{

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

	}
	else if (obj.getImgName() == CONSUMABLE_NAME[ITEM_CONSUMABLE_CHEESE])
	{

	}
	else if (obj.getImgName() == CONSUMABLE_NAME[ITEM_CONSUMABLE_DRUMSTICK])
	{

	}
	else if (obj.getImgName() == CONSUMABLE_NAME[ITEM_CONSUMABLE_HAM])
	{

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
	else if (obj.getImgName() == COIN_NAME[ITEM_COIN_1])
	{

	}
	else if (obj.getImgName() == COIN_NAME[ITEM_COIN_2])
	{

	}
	else if (obj.getImgName() == COIN_NAME[ITEM_COIN_3])
	{

	}
	else if (obj.getImgName() == COIN_NAME[ITEM_COIN_4])
	{

	}
	else if (obj.getImgName() == COIN_NAME[ITEM_COIN_5])
	{

	}
	else if (obj.getImgName() == COIN_NAME[ITEM_COIN_6])
	{

	}
	else if (obj.getImgName() == COIN_NAME[ITEM_COIN_7])
	{

	}
	else if (obj.getImgName() == COIN_NAME[ITEM_COIN_8])
	{

	}
	else if (obj.getImgName() == COIN_NAME[ITEM_COIN_9])
	{

	}
	else if (obj.getImgName() == COIN_NAME[ITEM_COIN_10])
	{

	}
	else if (obj.getImgName() == COIN_NAME[ITEM_COIN_25])
	{

	}
	else if (obj.getImgName() == COIN_NAME[ITEM_COIN_35])
	{

	}
	else if (obj.getImgName() == COIN_NAME[ITEM_COIN_50])
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

	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_ENEMY_SKELETON_BLACK])
	{

	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_ENEMY_SKELETON_MAGE_WHITE])
	{

	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_ENEMY_SKELETON_MAGE_YELLOW])
	{

	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_ENEMY_SKELETON_MAGE_BLACK])
	{

	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_ENEMY_ARMADILLO])
	{

	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_ENEMY_SLIME_GREEN])
	{

	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_ENEMY_SLIME_BLUE])
	{

	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_ENEMY_ZOMBIE])
	{

	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_ENEMY_BAT])
	{

	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_ENEMY_BAT_RED])
	{

	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_ENEMY_CLONE])
	{

	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_ENEMY_BAT_MINIBOSS])
	{

	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_ENEMY_BANSHEE])
	{

	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_ENEMY_DRAGON_GREEN])
	{

	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_ENEMY_MINOTAUR])
	{

	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_ENEMY_CORALRIFF_DRUMS])
	{

	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_ENEMY_CORALRIFF_HEAD])
	{

	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_ENEMY_CORALRIFF_HORNS])
	{

	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_ENEMY_CORALRIFF_KEYTAR])
	{

	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_ENEMY_CORALRIFF_STRINGS])
	{

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
		SOUNDMANAGER->play("sound_chain_groove");
	}

	_killCount++;

	if (_killCount % 5 == 0 && _chainCount < 4)
	{
		_chainCount++;
		//사운드 적용
		SOUNDMANAGER->play("sound_chain_groove");
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
