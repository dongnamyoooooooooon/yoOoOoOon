#include "stdafx.h"
#include "objectManager.h"
#include "parentObj.h"


objectManager::objectManager()
{
}


objectManager::~objectManager()
{
}

void objectManager::vectorClear()
{
	for (int i = 0; i < _tileY; i++)
	{
		for (int j = 0; i < _tileX; j++)
		{
			_vvObjTile[i][j] = nullptr;
			_vvFloorTile[i][j] = nullptr;
		}
	}
}

parentObj* objectManager::objectPush(parentObj obj)
{
	parentObj* tempObject;
	switch (obj.getObjType())
	//{
	//case OBJECT_TYPE_FLOOR:
	//	tempObject = CreateFloor(obj);
	//	tempObject->SetObjKind(OBJ_FLOOR);
	//	if (obj.GetImageKey() == "floor_stairs")
	//		objTile[tempObject->GetPos()] = tempObject;
	//	else
	//		FloorTile[obj.GetPos()] = tempObject;
	//	break;
	//case OBJECT_TYPE_WALL:
	//	tempObject = CreateWall(obj);
	//	tempObject->SetObjKind(OBJ_WALL);
	//	objTile[tempObject->GetPos()] = tempObject;
	//	break;
	//case OBJECT_TYPE_ITEM:
	//	tempObject = CreateItem(obj);
	//	tempObject->SetObjKind(OBJ_ITEM);
	//	objTile[tempObject->GetPos()] = tempObject;
	//	break;
	//case OBJECT_TYPE_ENEMY:
	//	tempObject = CreateMonster(obj);
	//	tempObject->SetObjKind(OBJ_MONSTER);
	//	objTile[tempObject->GetPos()] = tempObject;
	//	break;

	//case OBJECT_TYPE_TRAP:
	//	tempObject = CreateMonster(obj);
	//	tempObject->SetObjKind(OBJ_MONSTER);
	//	objTile[tempObject->GetPos()] = tempObject;
	//	break;

	//case OBJECT_TYPE_ETC:
	//	tempObject = CreateMonster(obj);
	//	tempObject->SetObjKind(OBJ_MONSTER);
	//	objTile[tempObject->GetPos()] = tempObject;
	//	break;
	//case OBJECT_TYPE_PLAYER:
	//	tempObject = CreatePlayer(obj);
	//	tempObject->SetObjKind(OBJ_PLAYER);
	//	objTile[tempObject->GetPos()] = tempObject;
	//	break;
	}

	m_vObj.push_back(tempObject);

	return tempObject;
}
