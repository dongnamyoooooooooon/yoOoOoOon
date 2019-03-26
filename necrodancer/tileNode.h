#pragma once
#include "parentObj.h"

// ==============================================
//					 설     정
// ==============================================

#define TILE_SIZE			52							//타일사이즈는 20
#define SAMPLETILE			6							//샘플타일은 6
#define TOTAL_SAMPLE_SIZE	TILE_SIZE * SAMPLETILE		//샘플 총 개수 = 타일사이즈 * 샘플개수
#define WALLHEIGHT			104							//벽높이는 96



// ==============================================
//					 속     성
// ==============================================

enum ATTRIBUTE
{
	TILE_FLOOR_ZONE1,
	TILE_FLOOR_ZONE2,
	TILE_FLOOR_BOSS,
	TILE_FLOOR_SHOP,
	TILE_FLOOR_WATER,
	TILE_WALL_01,
	TILE_WALL_02,
	TILE_WALL_03,
	TILE_WALL_04,
	TILE_CHEST,
	TILE_TRAP,
	TILE_STAIRS,
	TILE_DOOR,
	TILE_SHRINE,

};

enum IMAGE_NAME_INFO
{
	IMAGE_NAME_NONE,
	IMAGE_NAME_FLOOR_01,
	IMAGE_NAME_FLOOR_02,
	IMAGE_NAME_FLOOR_03,
	IMAGE_NAME_FLOOR_04,
	IMAGE_NAME_FLOOR_05,
	IMAGE_NAME_STAIRS_01,
	IMAGE_NAME_STAIRS_02,
	IMAGE_NAME_WALL_01,
	IMAGE_NAME_WALL_02,
	IMAGE_NAME_WALL_03,
	IMAGE_NAME_WALL_04,
	IMAGE_NAME_WALL_05,
	IMAGE_NAME_WALL_06,
	IMAGE_NAME_WALL_07,
	IMAGE_NAME_WALL_08,
	IMAGE_NAME_WALL_09,
	IMAGE_NAME_WALL_10,
	IMAGE_NAME_DOOR_01,
	IMAGE_NAME_DOOR_02,
	IMAGE_NAME_ENEMY_SKELETON,
	IMAGE_NAME_ENEMY_SKELETON_YELLOW,
	IMAGE_NAME_ENEMY_SKELETON_BLACK,
	IMAGE_NAME_ENEMY_SKELETON_MAGE_WHITE,
	IMAGE_NAME_ENEMY_SKELETON_MAGE_YELLOW,
	IMAGE_NAME_ENEMY_SKELETON_MAGE_BLACK,
	IMAGE_NAME_ENEMY_ARMADILLO,
	IMAGE_NAME_ENEMY_SLIME_GREEN,
	IMAGE_NAME_ENEMY_SLIME_BLUE,
	IMAGE_NAME_ENEMY_ZOMBIE,
	IMAGE_NAME_ENEMY_BAT,
	IMAGE_NAME_ENEMY_BAT_RED,
	IMAGE_NAME_ENEMY_CLONE,
	IMAGE_NAME_ENEMY_BAT_MINIBOSS,
	IMAGE_NAME_ENEMY_BANSHEE,
	IMAGE_NAME_ENEMY_DRAGON_GREEN,
	IMAGE_NAME_ENEMY_MINOTAUR,
	IMAGE_NAME_ENEMY_CORALRIFF_DRUMS,
	IMAGE_NAME_ENEMY_CORALRIFF_HEAD,
	IMAGE_NAME_ENEMY_CORALRIFF_HORNS,
	IMAGE_NAME_ENEMY_CORALRIFF_KEYTAR,
	IMAGE_NAME_ENEMY_CORALRIFF_STRINGS,
	IMAGE_NAME_ENEMY_SHOPKEEPER,
	IMAGE_NAME_CHEST,
	IMAGE_NAME_TRAP,
	IMAGE_NAME_SHRINE_01,
	IMAGE_NAME_SHRINE_02,
	IMAGE_NAME_SHRINE_03,
	IMAGE_NAME_SHRINE_04,
	IMAGE_NAME_SHRINE_05,
	IMAGE_NAME_SHRINE_06,
	IMAGE_NAME_ETC_01,


	IMAGE_NAME_END,
	IMAGE_NAME_COUNT = IMAGE_NAME_END
};

static string IMAGE_NAME[IMAGE_NAME_COUNT] = { "none", "floor_01","floor_02","floor_03","floor_04","floor_05",
											"stairs_01","stairs_02",
											"wall_01","wall_02","wall_03","wall_04","wall_05","wall_06","wall_07","wall_08","wall_09","wall_10",
											"door_01","door_02", "enemy_skeleton", "enemy_skeleton_yellow",
											"enemy_skeleton_black", "enemy_skeleton_mage_white", "enemy_skeleton_mage_yellow", "enemy_skeleton_black",
											"enemy_armadillo", "enemy_banshee", "enemy_bat", "enemy_bat_red", "enemy_bat_miniboss", "enemy_clone",
											"enemy_dragon_green", "enemy_slime_green", "enemy_slime_blue", "enemy_shopkeeper", "enemy_zombie",
											"enemy_minitaur", "enemy_coralriff_drums", "enemy_coralriff_head", "enemy_coralriff_horns", "enemy_coralriff_keytar",
											"enemy_coralriff_strings", "chest_01" ,"trap_01","shrine_01","shrine_02" ,"shrine_03","shrine_04","shrine_05",
											"shrine_06","torch_01"
};


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
			temp->init(floorName, floorPosX, floorPosY, type_floor);
			floor = temp;
		}
		if (type_obj != OBJECT_TYPE_NONE)
		{
			switch (type_obj)
			{
				case OBJECT_TYPE_WALL:
				{	
					temp = new parentObj;
					temp->init(objName, objPosX, objPosY, type_obj);
					wall = temp;
					break;
				}
				case OBJECT_TYPE_ITEM:
				{
					temp = new parentObj;
					temp->init(objName, objPosX, objPosY, type_obj);
					item = temp;
					break;
				}
				case OBJECT_TYPE_TRAP:
				{
					temp = new parentObj;
					temp->init(objName, objPosX, objPosY, type_obj);
					trap = temp;
					break;
				}
				case OBJECT_TYPE_ENEMY:
				{
					temp = new parentObj;
					temp->init(objName, objPosX, objPosY, type_obj);
					enemy = temp;
					break;
				}
				case OBJECT_TYPE_PLAYER:
				{
					temp = new parentObj;
					temp->init(objName, objPosX, objPosY, type_obj);
					player = temp;
					break;
				}
				case OBJECT_TYPE_ETC:
				{
					temp = new parentObj;
					temp->init(objName, objPosX, objPosY, type_obj);
					objETC = temp;
				}
				if (isTorch)
					temp->setTorch(true);
			}
		}
		//if (tile.image_Index > 0)							//타일의 인덱스가 0보다 크면(NONE이 아니면)
		//	image_Index = tile.image_Index;						//타일의 인덱스 대입
		//object_Index = tile.object_Index;
		//layer_Index = tile.layer_Index;
		//terrain_FrameX = tile.terrain_FrameX;				//프레임 대입
		//terrain_FrameY = tile.terrain_FrameY;				//프레임 대입
		//object_FrameX = tile.object_FrameX;
		//object_FrameY = tile.object_FrameY;
		//layer_FrameX = tile.layer_FrameX;
		//layer_FrameY = tile.layer_FrameY;
		//attr = tile.attr;									//속성 대입
	}
}TILE;

//타일의 포인터는 LPTILE
typedef class tagTile *LPTILE;