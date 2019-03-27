#pragma once
#include "itemInfomation.h"
#include "parentObj.h"
// ==============================================
//					 설     정
// ==============================================

#define TILE_SIZE			52							//타일사이즈는 20
#define SAMPLETILE			6							//샘플타일은 6
#define TOTAL_SAMPLE_SIZE	TILE_SIZE * SAMPLETILE		//샘플 총 개수 = 타일사이즈 * 샘플개수
#define WALLHEIGHT			104							//벽높이는 96




// ==============================================
//						타 일 
// ==============================================




typedef class tagTile
{
public:
	tagTile() :
		floor(nullptr),
		wall(nullptr),
		objETC(nullptr),
		trap(nullptr),
		item(nullptr),
		enemy(nullptr),
		player(nullptr),
		floorName(""),
		floorPosX(NULL),
		floorPosY(NULL),
		type_floor(),
		objName(""),
		objPosX(NULL),
		objPosY(NULL),
		type_obj(),
		isTorch(false),
		terrain_frameX(NULL),
		terrain_frameY(NULL),
		object_frameX(NULL),
		object_frameY(NULL)
	{};
	~tagTile()
	{};

	parentObj* floor;
	parentObj* wall;
	parentObj* item;
	parentObj* trap;
	parentObj* enemy;
	parentObj* player;
	parentObj* objETC;

	string floorName;
	int floorPosX;
	int floorPosY;
	OBJECT_TYPE type_floor;

	string objName;
	int objPosX;
	int objPosY;
	OBJECT_TYPE type_obj;
	UINT imgKey;
	ITEM_TYPE itemType;

	IMAGE_NAME_INFO floorKey;
	IMAGE_NAME_INFO objKey;

	bool isTorch = false;

	//밑에 있는 것들은 첫 초기화는 0 / none으로 초기화
	UINT	terrain_frameX;										//타일프레임 X
	UINT	terrain_frameY;										//타일프레임 Y
	UINT	object_frameX;										//오브젝트프레임 X
	UINT	object_frameY;										//오브젝트프레임 Y


	void setTile()
	{
		floor = nullptr;
		wall = nullptr;
		item = nullptr;
		enemy = nullptr;
		player = nullptr;
		objETC = nullptr;
		trap = nullptr;
		parentObj* temp;

		if (type_floor == OBJECT_TYPE_FLOOR)
		{
			temp = new parentObj;
			temp->init(floorName, floorPosX, floorPosY, type_floor, imgKey);
			floor = temp;
		}
		if (type_obj != OBJECT_TYPE_NONE)
		{
			switch (type_obj)
			{
				case OBJECT_TYPE_WALL:
				{	
					temp = new parentObj;
					temp->init(objName, objPosX, objPosY, type_obj, imgKey);
					wall = temp;
					break;
				}
				case OBJECT_TYPE_ITEM:
				{
					temp = new parentObj;
					temp->init(objName, objPosX, objPosY, type_obj, imgKey, itemType);
					item = temp;
					break;
				}
				case OBJECT_TYPE_TRAP:
				{
					temp = new parentObj;
					temp->init(objName, objPosX, objPosY, type_obj, imgKey);
					trap = temp;
					break;
				}
				case OBJECT_TYPE_ENEMY:
				{
					temp = new parentObj;
					temp->init(objName, objPosX, objPosY, type_obj, imgKey);
					enemy = temp;
					break;
				}
				case OBJECT_TYPE_PLAYER:
				{
					temp = new parentObj;
					temp->init(objName, objPosX, objPosY, type_obj, imgKey);
					player = temp;
					break;
				}
				case OBJECT_TYPE_ETC:
				{
					temp = new parentObj;
					temp->init(objName, objPosX, objPosY, type_obj, imgKey);
					objETC = temp;
				}
				if (isTorch)
					temp->setTorch(true);
			}
		}
	}
	tagPack makeSave()
	{
		tagPack* pack = new tagPack;

		pack->floorName = floorKey;
		pack->floorPosX = floorPosX;
		pack->floorPosY = floorPosY;
		pack->type_floor = type_floor;

		pack->objName = objKey;
		pack->objPosX = objPosX;
		pack->objPosY = objPosY;
		pack->type_obj = type_obj;
		pack->imgKey = imgKey;

		pack->isTorch = isTorch;

		pack->terrain_frameX = terrain_frameX;										//타일프레임 X
		pack->terrain_frameY = terrain_frameY;										//타일프레임 Y
		pack->object_frameX = object_frameX;										//오브젝트프레임 X
		pack->object_frameY = object_frameY;										//오브젝트프레임 Y

		if (type_obj == OBJECT_TYPE_ITEM)
			pack->itemType = itemType;
		else
			pack->itemType = itemType;
		
		if (floor)
			pack->floor = floor->makeSave();
		if (wall)
			pack->wall = wall->makeSave();
		if (objETC)
			pack->objETC = objETC->makeSave();
		if (trap)
			pack->trap = trap->makeSave();
		if (item)
			pack->item = item->makeSave();
		if (enemy)
			pack->enemy = enemy->makeSave();
		if (player)
			pack->player = player->makeSave();

		return *pack;
	}

	void makeLoad(tagPack* pack)
	{
		floorKey = (IMAGE_NAME_INFO)pack->floorName;
		floorPosX = pack->floorPosX;
		floorPosY = pack->floorPosY;
		type_floor = pack->type_floor;
		floorName = IMAGE_NAME[floorKey];

		objKey = (IMAGE_NAME_INFO)pack->objName;
		objPosX = pack->objPosX;
		objPosY = pack->objPosY;
		type_obj = pack->type_obj;
		objName = IMAGE_NAME[objKey];
		imgKey = pack->imgKey;
		
		if (pack->type_obj == OBJECT_TYPE_ITEM)
		{
			itemType = pack->itemType;
			switch (itemType)
			{
				case 0: objName = SHOVEL_NAME[imgKey]; break;
				case 1: objName = WEAPON_NAME[imgKey]; break;
				case 2: objName = TORCH_NAME[imgKey]; break;
				case 3: objName = ARMOR_NAME[imgKey]; break;
				case 4: objName = HEADWEAR_NAME[imgKey]; break;
				case 5: objName = FOOTWEAR_NAME[imgKey]; break;
				case 6: objName = CONSUMABLE_NAME[imgKey]; break;
				case 7: objName = HEART_NAME[imgKey]; break;
				case 8: objName = COIN_NAME[imgKey]; break;
				case 9: objName = BOMB_NAME[imgKey]; break;
			}
		}
		else
			objName = IMAGE_NAME[imgKey];

		isTorch = pack->isTorch;

		terrain_frameX = pack->terrain_frameX;
		terrain_frameY = pack->terrain_frameY;
		object_frameX = pack->object_frameX;
		object_frameY = pack->object_frameY;

		parentObj* temp;
		if (type_floor == OBJECT_TYPE_FLOOR)
		{
			temp = new parentObj;
			temp->init(floorName, floorPosX, floorPosY, type_floor, imgKey);
			floor = temp;
		}
		if (type_obj != OBJECT_TYPE_NONE)
		{
			switch (type_obj)
			{
			case OBJECT_TYPE_WALL:
			{
				temp = new parentObj;
				temp->init(objName, objPosX, objPosY, type_obj, imgKey);
				wall = temp;
				break;
			}
			case OBJECT_TYPE_ITEM:
			{
				temp = new parentObj;
				temp->init(objName, objPosX, objPosY, type_obj, imgKey, itemType);
				item = temp;
				break;
			}
			case OBJECT_TYPE_TRAP:
			{
				temp = new parentObj;
				temp->init(objName, objPosX, objPosY, type_obj, imgKey);
				trap = temp;
				break;
			}
			case OBJECT_TYPE_ENEMY:
			{
				temp = new parentObj;
				temp->init(objName, objPosX, objPosY, type_obj, imgKey);
				enemy = temp;
				break;
			}
			case OBJECT_TYPE_PLAYER:
			{
				temp = new parentObj;
				temp->init(objName, objPosX, objPosY, type_obj, imgKey);
				player = temp;
				break;
			}
			case OBJECT_TYPE_ETC:
			{
				temp = new parentObj;
				temp->init(objName, objPosX, objPosY, type_obj, imgKey);
				objETC = temp;
			}
			if (isTorch)
				temp->setTorch(true);
			}
		}

		if(floor != NULL)
			floor->makeLoad(&pack->floor);
		if (wall != NULL)
			wall->makeLoad(&pack->wall);
		if (objETC != NULL)
			objETC->makeLoad(&pack->objETC);
		if (trap != NULL)
			trap->makeLoad(&pack->trap);
		if (item != NULL)
			item->makeLoad(&pack->item);
		if (enemy != NULL)
			enemy->makeLoad(&pack->enemy);
		if (player != NULL)
			player->makeLoad(&pack->player);

	}

	//void makePack()
	//{
	//	floor->makeSaveInfo()


	//}
	//	void loadPack();

}TILE;

//타일의 포인터는 LPTILE
typedef class tagTile *LPTILE;