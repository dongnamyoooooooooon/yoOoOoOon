#include "stdafx.h"
#include "objectManager.h"
#include "parentObj.h"


objectManager::objectManager()
{
}

objectManager::~objectManager()
{
}

void objectManager::release()
{
}

void objectManager::update()
{
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
			if(_vvObjTile[(*_viObj)->getIdxY()][(*_viObj)->getIdxX()] == NULL)
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


	////��Ʈ
	////RECT rc;
	//for (_viBeat = _vBeat.begin(); _viBeat != _vBeat.end(); _viBeat++)
	//{
	//	if (_viBeat->beat < 1500)
	//	{
	//		_viBeat->img->render(CAMERA->getPosX() + _viBeat->left_RC.left, CAMERA->getPosY() + _viBeat->left_RC.top, 10, 48, 1.0f);
	//		_viBeat->img->render(CAMERA->getPosX() + _viBeat->right_RC.left, CAMERA->getPosY() + _viBeat->right_RC.top, 10, 48, 1.0f);
	//	}
	//	else
	//	{
	//		_viBeat->img->render(CAMERA->getPosX() + _viBeat->left_RC.left, CAMERA->getPosY() + _viBeat->left_RC.top, 10, 48, _viBeat->alpha);
	//		_viBeat->img->render(CAMERA->getPosX() + _viBeat->right_RC.left, CAMERA->getPosY() + _viBeat->right_RC.top, 10, 48, _viBeat->alpha);
	//	}
	//}
	//if (_vBeat.begin()->left_RC.right <= WINSIZEX / 2)
	//	IMAGEMANAGER->findImage("ui_beat_heart")->frameRender2((CAMERA->getPosX() + (WINSIZEX / 2) - 40), CAMERA->getPosY() + WINSIZEY - 124, 0, 0);
	//else
	//	IMAGEMANAGER->findImage("ui_beat_heart")->frameRender2((CAMERA->getPosX() + (WINSIZEX / 2) - 40), CAMERA->getPosY() + WINSIZEY - 124, 1, 0);





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
	//�÷��̾� ������Ʈ
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

void objectManager::createBeat()
{

	SOUNDMANAGER->loadBeat(_beatFile, _beatKey);

	if (_musicKey == "boss")
		SOUNDMANAGER->playBossZone(_musicKey, _volume);
	else
		SOUNDMANAGER->playZone(_musicKey, 1.0f);

	_vBeat = SOUNDMANAGER->getVBeat();
	_viBeat = SOUNDMANAGER->getVIBeat();
	_mBeat = SOUNDMANAGER->getMBeat();
	_miBeat = SOUNDMANAGER->getMIBeat();


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

		_vObj.push_back(tempObject);
	}
	return 0;
}

parentObj * objectManager::createFloor(parentObj obj)
{

	if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_FLOOR_01])
	{

	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_FLOOR_02])
	{

	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_FLOOR_03])
	{

	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_FLOOR_04])
	{

	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_FLOOR_05])
	{

	}


	return nullptr;
}

parentObj * objectManager::createWall(parentObj obj)
{

	if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_WALL_01])
	{

	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_WALL_02])
	{

	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_WALL_03])
	{

	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_WALL_04])
	{

	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_WALL_05])
	{

	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_WALL_06])
	{

	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_WALL_07])
	{

	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_WALL_08])
	{

	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_WALL_09])
	{

	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_WALL_10])
	{

	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_WALL_11])
	{

	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_DOOR_01])
	{

	}
	else if (obj.getImgName() == IMAGE_NAME[IMAGE_NAME_DOOR_02])
	{

	}

	return nullptr;
}

parentObj * objectManager::createItem(parentObj obj)
{
	if (obj.getImgName() == SHOVEL_NAME[ITEM_SHOVEL_BASIC])
	{

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

	}
	else if (obj.getImgName() == ARMOR_NAME[ITEM_ARMOR_CHAINMAIL])
	{

	}
	else if (obj.getImgName() == ARMOR_NAME[ITEM_ARMOR_PLATEMAIL])
	{

	}
	else if (obj.getImgName() == ARMOR_NAME[ITEM_ARMOR_HEAVYPLATE])
	{

	}
	else if (obj.getImgName() == ARMOR_NAME[ITEM_ARMOR_KARADE])
	{

	}
	else if (obj.getImgName() == ARMOR_NAME[ITEM_ARMOR_OBSIDIAN])
	{

	}
	else if (obj.getImgName() == ARMOR_NAME[ITEM_ARMOR_GLASS])
	{

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

	return nullptr;
}