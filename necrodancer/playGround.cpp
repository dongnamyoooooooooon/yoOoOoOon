#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

HRESULT playGround::init()
{
	gameNode::init(true);

	//맵툴배경
	IMAGEMANAGER->addImage("maptoolbackground", L"image/mapTool/maptoolBackground.png", 240, 540);

	//샘플타일배경
	IMAGEMANAGER->addImage("samplebackground", L"image/mapTool/mapTool_sampleTile.png", 400, 400);

	//맵툴버튼
	IMAGEMANAGER->addFrameImage(BUTTON_NAME[MAPTOOL_BUTTON_FLOOR], L"image/button/mapTool_floor.png", 100, 90, 1, 3);
	IMAGEMANAGER->addFrameImage(BUTTON_NAME[MAPTOOL_BUTTON_WALL], L"image/button/mapTool_wall.png", 100, 90, 1, 3);
	//IMAGEMANAGER->addFrameImage(BUTTON_NAME[MAPTOOL_BUTTON_CHEST], L"image/button/mapTool_chest.png", 100, 90, 1, 3);
	IMAGEMANAGER->addFrameImage(BUTTON_NAME[MAPTOOL_BUTTON_ENEMY], L"image/button/mapTool_enemy.png", 100, 90, 1, 3);
	IMAGEMANAGER->addFrameImage(BUTTON_NAME[MAPTOOL_BUTTON_TRAP], L"image/button/mapTool_trap.png", 100, 90, 1, 3);
	IMAGEMANAGER->addFrameImage(BUTTON_NAME[MAPTOOL_BUTTON_ITEM], L"image/button/mapTool_item.png", 100, 90, 1, 3);
	IMAGEMANAGER->addFrameImage(BUTTON_NAME[MAPTOOL_BUTTON_ETC], L"image/button/mapTool_container.png", 100, 90, 1, 3);
	IMAGEMANAGER->addFrameImage(BUTTON_NAME[MAPTOOL_BUTTON_NAME], L"image/button/mapTool_name.png", 100, 90, 1, 3);
	IMAGEMANAGER->addFrameImage(BUTTON_NAME[MAPTOOL_BUTTON_PREV], L"image/button/mapTool_left_button.png", 30, 60, 1, 2);
	IMAGEMANAGER->addFrameImage(BUTTON_NAME[MAPTOOL_BUTTON_NEXT], L"image/button/mapTool_right_button.png", 30, 60, 1, 2);
	IMAGEMANAGER->addFrameImage(BUTTON_NAME[MAPTOOL_BUTTON_SAVE], L"image/button/mapTool_save.png", 100, 60, 1, 2);
	IMAGEMANAGER->addFrameImage(BUTTON_NAME[MAPTOOL_BUTTON_LOAD], L"image/button/mapTool_load.png", 100, 60, 1, 2);
	IMAGEMANAGER->addFrameImage(BUTTON_NAME[MAPTOOL_BUTTON_PLAY], L"image/button/mapTool_play.png", 100, 60, 1, 2);
	IMAGEMANAGER->addFrameImage(BUTTON_NAME[MAPTOOL_BUTTON_LOBBY], L"image/button/mapTool_lobby.png", 100, 60, 1, 2);
	IMAGEMANAGER->addFrameImage(BUTTON_NAME[MAPTOOL_BUTTON_SIZE], L"image/button/mapTool_mapsize.png", 100, 90, 1, 3);
	IMAGEMANAGER->addFrameImage(BUTTON_NAME[MAPTOOL_BUTTON_SIZE_WIDTH_UP], L"image/button/mapTool_Width_Up.png", 55, 40, 1, 2);
	IMAGEMANAGER->addFrameImage(BUTTON_NAME[MAPTOOL_BUTTON_SIZE_WIDTH_DOWN], L"image/button/mapTool_Width_Down.png", 55, 40, 1, 2);
	IMAGEMANAGER->addFrameImage(BUTTON_NAME[MAPTOOL_BUTTON_SIZE_HEIGHT_UP], L"image/button/mapTool_Height_Up.png", 55, 40, 1, 2);
	IMAGEMANAGER->addFrameImage(BUTTON_NAME[MAPTOOL_BUTTON_SIZE_HEIGHT_DOWN], L"image/button/mapTool_Height_Down.png", 55, 40, 1, 2);
	IMAGEMANAGER->addFrameImage("mapTool_left", L"image/button/mapTool_left.png", 30, 60, 1, 2);
	IMAGEMANAGER->addFrameImage("mapTool_right", L"image/button/mapTool_right.png", 30, 60, 1, 2);
	IMAGEMANAGER->addFrameImage("mapTool_erase", L"image/button/mapTool_erase.png", 40, 60, 1, 2);
	IMAGEMANAGER->addFrameImage("mapTool_rendom", L"image/button/mapTool_rendom.png", 60, 60, 1, 2);
	IMAGEMANAGER->addFrameImage("mapTool_floor_choice", L"image/button/mapTool_floor_choice.png", 70, 90, 1, 3);



	//맵툴이미지
	IMAGEMANAGER->addImage("mapTool_cursor", L"image/mapTool/cursor.png", 48, 48);
	IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_FLOOR_01], L"image/mapTool/floor_dirt1.png", 156, 104, 3, 2);
	IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_FLOOR_02], L"image/mapTool/floor_dirt2.png", 156, 208, 3, 4);
	IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_FLOOR_03], L"image/mapTool/floor_boss.png", 156, 104, 3, 2);
	IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_FLOOR_04], L"image/mapTool/floor_shop.png", 156, 52, 3, 1);
	IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_FLOOR_05], L"image/mapTool/floor_water.png", 156, 52, 3, 1);
	IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_STAIRS_01], L"image/mapTool/floor_stairs_01.png", 48, 48, 1, 1);
	IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_STAIRS_02], L"image/mapTool/floor_stairs_02.png", 48, 48, 1, 1);
	//IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_STAIRS_01], L"image/mapTool/stairs.png", 288, 48, 6, 1);
	IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_WALL_01], L"image/mapTool/wall_zone1.png", TILE_SIZE * 16, WALLHEIGHT, 16, 1);
	IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_WALL_02], L"image/mapTool/wall_zone2.png", TILE_SIZE * 8, WALLHEIGHT, 8, 1);
	IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_WALL_03], L"image/mapTool/wall_shop.png", TILE_SIZE, WALLHEIGHT, 1, 1);
	IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_WALL_04], L"image/mapTool/wall_shop_cracked.png", TILE_SIZE, WALLHEIGHT, 1, 1);
	IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_WALL_05], L"image/mapTool/wall_stone_01.png", TILE_SIZE, WALLHEIGHT, 1, 1);
	IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_WALL_06], L"image/mapTool/wall_stone_02.png", TILE_SIZE, WALLHEIGHT, 1, 1);
	IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_WALL_07], L"image/mapTool/wall_catacomb_1.png", TILE_SIZE, WALLHEIGHT, 1, 1);
	IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_WALL_08], L"image/mapTool/wall_catacomb_cracked.png", TILE_SIZE, WALLHEIGHT, 1, 1);
	IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_WALL_09], L"image/mapTool/wall_stone_cracked_01.png", TILE_SIZE, WALLHEIGHT, 1, 1);
	IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_WALL_10], L"image/mapTool/wall_stone_cracked_02.png", TILE_SIZE, WALLHEIGHT, 1, 1);
	IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_WALL_11], L"image/mapTool/wall_end_of_world.png", TILE_SIZE*8, WALLHEIGHT, 8, 1);
	IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_DOOR_01], L"image/mapTool/door_front.png", TILE_SIZE, WALLHEIGHT, 1, 1);
	IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_DOOR_02], L"image/mapTool/door_side.png", TILE_SIZE, WALLHEIGHT, 1, 1);
	IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_CHEST], L"image/mapTool/chest.png", 288, 48, 6, 1);
	IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_TRAP_BOUNCE], L"image/mapTool/trap_bounce.png", 56, 192, 2, 6);
	IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_TRAP_SLOWDOWN], L"image/mapTool/trap_slowdown.png", 56, 64, 2, 2);
	IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_TRAP_SPEEDUP], L"image/mapTool/trap_speedup.png", 56, 64, 2, 2);
	IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_TRAP_SPIKE], L"image/mapTool/trap_spike.png", 68, 240, 1, 6);
	IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_SHRINE_01], L"image/mapTool/shrine_01.png", 288, 288, 2, 2);
	IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_SHRINE_02], L"image/mapTool/shrine_02.png", 288, 288, 2, 2);
	IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_SHRINE_03], L"image/mapTool/shrine_03.png", 288, 288, 2, 2);
	IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_SHRINE_04], L"image/mapTool/shrine_04.png", 288, 288, 2, 2);
	IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_SHRINE_05], L"image/mapTool/shrine_05.png", 288, 288, 2, 2);
	IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_SHRINE_06], L"image/mapTool/shrine_06.png", 288, 288, 2, 2);
	IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_ETC_01], L"image/mapTool/etc_01.png", 192, 48, 4, 1);

	//적
	IMAGEMANAGER->addFrameImage(ENEMY_NAME[ENEMY_TYPE_SKELETON], L"image/enemy/skeleton.png", 384, 100, 8, 2);
	IMAGEMANAGER->addFrameImage(ENEMY_NAME[ENEMY_TYPE_SKELETON_YELLOW], L"image/enemy/skeleton_yellow.png", 432, 100, 9, 2);
	IMAGEMANAGER->addFrameImage(ENEMY_NAME[ENEMY_TYPE_SKELETON_BLACK], L"image/enemy/skeleton_black.png", 432, 100, 9, 2);
	IMAGEMANAGER->addFrameImage(ENEMY_NAME[ENEMY_TYPE_SKELETON_MAGE_WHITE], L"image/enemy/skeleton_mage_white.png", 336, 108, 7, 2);
	IMAGEMANAGER->addFrameImage(ENEMY_NAME[ENEMY_TYPE_SKELETON_MAGE_YELLOW], L"image/enemy/skeleton_mage_yellow.png", 336, 108, 7, 2);
	IMAGEMANAGER->addFrameImage(ENEMY_NAME[ENEMY_TYPE_SKELETON_MAGE_BLACK], L"image/enemy/skeleton_mage_black.png", 336, 108, 7, 2);
	IMAGEMANAGER->addFrameImage(ENEMY_NAME[ENEMY_TYPE_ARMADILLO], L"image/enemy/armadillo.png", 528, 96, 11, 2);
	IMAGEMANAGER->addFrameImage(ENEMY_NAME[ENEMY_TYPE_BANSHEE], L"image/enemy/banshee.png", 544, 156, 8, 2);
	IMAGEMANAGER->addFrameImage(ENEMY_NAME[ENEMY_TYPE_BAT], L"image/enemy/bat.png", 192, 96, 4, 2);
	IMAGEMANAGER->addFrameImage(ENEMY_NAME[ENEMY_TYPE_BAT_RED], L"image/enemy/bat_red.png", 192, 96, 4, 2);
	IMAGEMANAGER->addFrameImage(ENEMY_NAME[ENEMY_TYPE_BAT_MINIBOSS], L"image/enemy/bat_miniboss.png", 288, 96, 4, 2);
	IMAGEMANAGER->addFrameImage(ENEMY_NAME[ENEMY_TYPE_CLONE], L"image/enemy/clone.png", 192, 96, 4, 2);
	IMAGEMANAGER->addFrameImage(ENEMY_NAME[ENEMY_TYPE_DRAGON_GREEN], L"image/enemy/dragon_green.png", 216, 204, 2, 2);
	IMAGEMANAGER->addFrameImage(ENEMY_NAME[ENEMY_TYPE_SLIME_GREEN], L"image/enemy/slime_green.png", 208, 104, 4, 2);
	IMAGEMANAGER->addFrameImage(ENEMY_NAME[ENEMY_TYPE_SLIME_BLUE], L"image/enemy/slime_blue.png", 416, 100, 8, 2);
	IMAGEMANAGER->addFrameImage(ENEMY_NAME[ENEMY_TYPE_SHOPKEEPER], L"image/enemy/shopkeeper.png", 752, 152, 8, 2);
	IMAGEMANAGER->addFrameImage(ENEMY_NAME[ENEMY_TYPE_ZOMBIE], L"image/enemy/zombie.png", 1152, 100, 24, 2);
	IMAGEMANAGER->addFrameImage(ENEMY_NAME[ENEMY_TYPE_MINOTAUR], L"image/enemy/minotaur.png", 900, 196, 9, 2);
	IMAGEMANAGER->addFrameImage(ENEMY_NAME[ENEMY_TYPE_CORALRIFF_DRUMS], L"image/enemy/coralriff_drums.png", 328, 220, 4, 2);
	IMAGEMANAGER->addFrameImage(ENEMY_NAME[ENEMY_TYPE_CORALRIFF_HEAD], L"image/enemy/coralriff_head.png", 344, 240, 4, 2);
	IMAGEMANAGER->addFrameImage(ENEMY_NAME[ENEMY_TYPE_CORALRIFF_HORNS], L"image/enemy/coralriff_horns.png", 288, 230, 4, 2);
	IMAGEMANAGER->addFrameImage(ENEMY_NAME[ENEMY_TYPE_CORALRIFF_KEYTAR], L"image/enemy/coralriff_keytar.png", 208, 220, 4, 2);
	IMAGEMANAGER->addFrameImage(ENEMY_NAME[ENEMY_TYPE_CORALRIFF_STRINGS], L"image/enemy/coralriff_strings.png", 360, 224, 4, 2);


	//횃불(벽)
	IMAGEMANAGER->addFrameImage("frame_fire", L"image/frame_fire.png", 192, 48, 4, 1);

	//아이템
	IMAGEMANAGER->addImage("item_shadow", L"image/items/item_shadow.png", 48, 58);


	//갑옷
	IMAGEMANAGER->addFrameImage(ARMOR_NAME[ITEM_ARMOR_LEATHER], L"image/items/armor_leather.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(ARMOR_NAME[ITEM_ARMOR_CHAINMAIL], L"image/items/armor_chainmail.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(ARMOR_NAME[ITEM_ARMOR_PLATEMAIL], L"image/items/armor_platemail.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(ARMOR_NAME[ITEM_ARMOR_HEAVYPLATE], L"image/items/armor_heavyplate.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(ARMOR_NAME[ITEM_ARMOR_KARADE], L"image/items/armor_gi.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(ARMOR_NAME[ITEM_ARMOR_OBSIDIAN], L"image/items/armor_obsidian.png", 156, 104, 3, 2);
	IMAGEMANAGER->addFrameImage(ARMOR_NAME[ITEM_ARMOR_GLASS], L"image/items/armor_glass.png", 48, 96, 1, 2);

	//삽
	IMAGEMANAGER->addFrameImage(SHOVEL_NAME[ITEM_SHOVEL_BASIC], L"image/items/shovel_basic.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(SHOVEL_NAME[ITEM_SHOVEL_TITANIUM], L"image/items/shovel_titanium.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(SHOVEL_NAME[ITEM_SHOVEL_GLASS], L"image/items/shovel_glass.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(SHOVEL_NAME[ITEM_SHOVEL_OBSIDIAN], L"image/items/shovel_obsidian.png", 156, 104, 3, 2);
	IMAGEMANAGER->addFrameImage(SHOVEL_NAME[ITEM_SHOVEL_BLOOD], L"image/items/shovel_blood.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(SHOVEL_NAME[ITEM_SHOVEL_CRYSTAL], L"image/items/shovel_crystal.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(SHOVEL_NAME[ITEM_SHOVEL_GLASSSHARD], L"image/items/shovel_shard.png", 48, 96, 1, 2);

	//무기
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_DAGGER_BASIC], L"image/items/weapon_dagger.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_DAGGER_TITANIUM], L"image/items/weapon_dagger_titanium.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_DAGGER_GLASS], L"image/items/weapon_dagger_glass.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_DAGGER_OBSIDIAN], L"image/items/weapon_dagger_obsidian.png", 144, 96, 3, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_DAGGER_BLOOD], L"image/items/weapon_dagger_blood.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_DAGGER_GOLD], L"image/items/weapon_dagger_golden.png", 48, 96, 1, 2);

	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_BROADSWORD_BASIC], L"image/items/weapon_broadsword.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_BROADSWORD_TITANIUM], L"image/items/weapon_broadsword_titanium.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_BROADSWORD_GLASS], L"image/items/weapon_broadsword_glass.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_BROADSWORD_OBSIDIAN], L"image/items/weapon_broadsword_obsidian.png", 156, 104, 3, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_BROADSWORD_BLOOD], L"image/items/weapon_broadsword_blood.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_BROADSWORD_GOLD], L"image/items/weapon_broadsword_golden.png", 48, 96, 1, 2);

	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_RAPIER_BASIC], L"image/items/weapon_rapier.png", 52, 108, 1, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_RAPIER_TITANIUM], L"image/items/weapon_rapier_titanium.png", 52, 108, 1, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_RAPIER_GLASS], L"image/items/weapon_rapier_glass.png", 52, 108, 1, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_RAPIER_OBSIDIAN], L"image/items/weapon_rapier_obsidian.png", 156, 108, 3, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_RAPIER_BLOOD], L"image/items/weapon_rapier_blood.png", 52, 108, 1, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_RAPIER_GOLD], L"image/items/weapon_rapier_golden.png", 52, 108, 1, 2);

	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_SPEAR_BASIC], L"image/items/weapon_spear.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_SPEAR_TITANIUM], L"image/items/weapon_spear_titanium.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_SPEAR_GLASS], L"image/items/weapon_spear_glass.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_SPEAR_OBSIDIAN], L"image/items/weapon_spear_obsidian.png", 144, 96, 3, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_SPEAR_BLOOD], L"image/items/weapon_spear_blood.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_SPEAR_GOLD], L"image/items/weapon_spear_golden.png", 48, 96, 1, 2);

	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_LONGSWORD_BASIC], L"image/items/weapon_longsword.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_LONGSWORD_TITANIUM], L"image/items/weapon_longsword_titanium.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_LONGSWORD_GLASS], L"image/items/weapon_longsword_glass.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_LONGSWORD_OBSIDIAN], L"image/items/weapon_longsword_obsidian.png", 156, 108, 3, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_LONGSWORD_BLOOD], L"image/items/weapon_longsword_blood.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_LONGSWORD_GOLD], L"image/items/weapon_longsword_golden.png", 48, 96, 1, 2);

	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_WHIP_BASIC], L"image/items/weapon_whip.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_WHIP_TITANIUM], L"image/items/weapon_whip_titanium.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_WHIP_GLASS], L"image/items/weapon_whip_glass.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_WHIP_OBSIDIAN], L"image/items/weapon_whip_obsidian.png", 144, 96, 3, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_WHIP_BLOOD], L"image/items/weapon_whip_blood.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_WHIP_GOLD], L"image/items/weapon_whip_golden.png", 48, 96, 1, 2);

	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_BOW_BASIC], L"image/items/weapon_bow.png", 50, 104, 1, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_BOW_TITANIUM], L"image/items/weapon_bow_titanium.png", 50, 104, 1, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_BOW_GLASS], L"image/items/weapon_bow_glass.png", 50, 104, 1, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_BOW_OBSIDIAN], L"image/items/weapon_bow_obsidian.png", 150, 104, 3, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_BOW_BLOOD], L"image/items/weapon_bow_blood.png", 50, 104, 1, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_BOW_GOLD], L"image/items/weapon_bow_golden.png", 50, 104, 1, 2);

	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_CROSSBOW_BASIC], L"image/items/weapon_crossbow.png", 216, 108, 4, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_CROSSBOW_TITANIUM], L"image/items/weapon_crossbow_titanium.png", 216, 108, 4, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_CROSSBOW_GLASS], L"image/items/weapon_crossbow_glass.png", 216, 108, 4, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_CROSSBOW_OBSIDIAN], L"image/items/weapon_crossbow_obsidian.png", 648, 108, 12, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_CROSSBOW_BLOOD], L"image/items/weapon_crossbow_blood.png", 216, 108, 4, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_CROSSBOW_GOLD], L"image/items/weapon_crossbow_golden.png", 216, 108, 4, 2);

	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_NINETAILS_BASIC], L"image/items/weapon_cat.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_NINETAILS_TITANIUM], L"image/items/weapon_cat_titanium.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_NINETAILS_GLASS], L"image/items/weapon_cat_glass.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_NINETAILS_OBSIDIAN], L"image/items/weapon_cat_obsidian.png", 150, 96, 3, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_NINETAILS_BLOOD], L"image/items/weapon_cat_blood.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_NINETAILS_GOLD], L"image/items/weapon_cat_gold.png", 48, 96, 1, 2);

	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_FIAIL_BASIC], L"image/items/weapon_flail.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_FIAIL_TITANIUM], L"image/items/weapon_flail_titanium.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_FIAIL_GLASS], L"image/items/weapon_flail_glass.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_FIAIL_OBSIDIAN], L"image/items/weapon_flail_obsidian.png", 144, 96, 3, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_FIAIL_BLOOD], L"image/items/weapon_flail_blood.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_FIAIL_GOLD], L"image/items/weapon_flail_gold.png", 48, 96, 1, 2);

	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_BLUNDERBUSS], L"image/items/weapon_blunderbuss.png", 100, 144, 2, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_RIFLE], L"image/items/weapon_rifle.png", 100, 148, 2, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_GLASSSHARD], L"image/items/weapon_dagger_shard.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_JEWELEDDAGGER], L"image/items/weapon_dagger_jeweled.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(WEAPON_NAME[ITEM_WEAPON_GOLDENLUTE], L"image/items/weapon_golden_lute.png", 60, 100, 1, 2);

	//횃불(아이템)
	IMAGEMANAGER->addFrameImage(TORCH_NAME[ITEM_TORCH_BASIC], L"image/items/torch_1.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(TORCH_NAME[ITEM_TORCH_BRIGHT], L"image/items/torch_2.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(TORCH_NAME[ITEM_TORCH_LUMINIOUS], L"image/items/torch_3.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(TORCH_NAME[ITEM_TORCH_GLASS], L"image/items/torch_glass.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(TORCH_NAME[ITEM_TORCH_OBSIDIAN], L"image/items/torch_obsidian.png", 144, 108, 3, 2);
	IMAGEMANAGER->addFrameImage(TORCH_NAME[ITEM_TORCH_INFERNAL], L"image/items/torch_infernal.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(TORCH_NAME[ITEM_TORCH_FORESIGHT], L"image/items/torch_foresight.png", 48, 96, 1, 2);

	//투구
	IMAGEMANAGER->addFrameImage(HEADWEAR_NAME[ITEM_HEADWEAR_HELMAT], L"image/items/head_helmet.png", 48, 84, 1, 2);
	IMAGEMANAGER->addFrameImage(HEADWEAR_NAME[ITEM_HEADWEAR_BLASTHELM], L"image/items/head_blast_helm.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(HEADWEAR_NAME[ITEM_HEADWEAR_TELEPORT], L"image/items/head_crown_of_teleportation.png", 48, 96, 1, 2);

	//신발
	IMAGEMANAGER->addFrameImage(FOOTWEAR_NAME[ITEM_FOOTWEAR_BALLET], L"image/items/feet_ballet_shoes.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(FOOTWEAR_NAME[ITEM_FOOTWEAR_WINGED], L"image/items/feet_boots_winged.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(FOOTWEAR_NAME[ITEM_FOOTWEAR_LEAD], L"image/items/feet_boots_lead.png", 48, 100, 1, 2);
	IMAGEMANAGER->addFrameImage(FOOTWEAR_NAME[ITEM_FOOTWEAR_HARGREAVES], L"image/items/feet_greaves.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(FOOTWEAR_NAME[ITEM_FOOTWEAR_STRENGTH], L"image/items/feet_boots_strength.png", 48, 96, 1, 2);

	//소모품
	IMAGEMANAGER->addFrameImage(CONSUMABLE_NAME[ITEM_CONSUMABLE_APPLE], L"image/items/food_1.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(CONSUMABLE_NAME[ITEM_CONSUMABLE_CHEESE], L"image/items/food_2.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(CONSUMABLE_NAME[ITEM_CONSUMABLE_DRUMSTICK], L"image/items/food_3.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(CONSUMABLE_NAME[ITEM_CONSUMABLE_HAM], L"image/items/food_4.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(CONSUMABLE_NAME[ITEM_CONSUMABLE_WARDRUM], L"image/items/war_drum.png", 156, 112, 3, 2);

	//폭탄
	IMAGEMANAGER->addFrameImage(BOMB_NAME[ITEM_BOMB_X1], L"image/items/bomb.png", 240, 96, 5, 2);
	IMAGEMANAGER->addFrameImage(BOMB_NAME[ITEM_BOMB_X3], L"image/items/bomb_3.png", 48, 96, 1, 2);

	//하트
	IMAGEMANAGER->addFrameImage(HEART_NAME[ITEM_HEART_FILLED], L"image/items/misc_heart_container.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(HEART_NAME[ITEM_HEART_DOUBLE_FILLED], L"image/items/misc_heart_container2.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(HEART_NAME[ITEM_HEART_EMPTY], L"image/items/misc_heart_container_empty.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(HEART_NAME[ITEM_HEART_DOUBLE_EMPTY], L"image/items/misc_heart_container_empty2.png", 48, 96, 1, 2);

	//동전
	IMAGEMANAGER->addFrameImage(COIN_NAME[ITEM_COIN_1], L"image/items/resource_coin1.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(COIN_NAME[ITEM_COIN_2], L"image/items/resource_coin2.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(COIN_NAME[ITEM_COIN_3], L"image/items/resource_coin3.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(COIN_NAME[ITEM_COIN_4], L"image/items/resource_coin4.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(COIN_NAME[ITEM_COIN_5], L"image/items/resource_coin5.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(COIN_NAME[ITEM_COIN_6], L"image/items/resource_coin6.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(COIN_NAME[ITEM_COIN_7], L"image/items/resource_coin7.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(COIN_NAME[ITEM_COIN_8], L"image/items/resource_coin8.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(COIN_NAME[ITEM_COIN_9], L"image/items/resource_coin9.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(COIN_NAME[ITEM_COIN_10], L"image/items/resource_coin10.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(COIN_NAME[ITEM_COIN_25], L"image/items/resource_hoard_gold_small.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(COIN_NAME[ITEM_COIN_35], L"image/items/resource_hoard_gold.png", 48, 96, 1, 2);
	IMAGEMANAGER->addFrameImage(COIN_NAME[ITEM_COIN_50], L"image/items/resource_hoard.png", 68, 76, 1, 2);

	//몬스터
	//IMAGEMANAGER->addFrameImage(ENEMY_NAME[ENEMY_SKELETON_WHITE],				L"image/enemy/skeleton.png",					768, 112, 16, 2);

	//아이템
	IMAGEMANAGER->addFrameImage("shovel_basic", L"image/items/shovel_basic.png", 48, 96, 1, 2);

	//플레이어
	IMAGEMANAGER->addImage("player_shadow", L"image/player/player_shadow.png", 48, 54);
	IMAGEMANAGER->addFrameImage("player_head", L"image/player/player_heads.png", 192, 96, 4, 2);
	IMAGEMANAGER->addFrameImage("player_body", L"image/player/player_body.png", 192, 480, 4, 10);

	//상점주인
	IMAGEMANAGER->addImage("musical_note", L"image/musical_note.png", 6, 6);

	//UI
	IMAGEMANAGER->addImage("ui_beat_marker", L"image/ui/ui_beat_marker.png", 12, 64);
	IMAGEMANAGER->addImage("ui_beat_marker_red", L"image/ui/ui_beat_marker_red.png", 12, 64);
	IMAGEMANAGER->addImage("ui_heart", L"image/ui/ui_heart.png", 48, 44);
	IMAGEMANAGER->addImage("ui_half_heart", L"image/ui/ui_heart_half.png", 48, 44);
	IMAGEMANAGER->addImage("ui_empty_heart", L"image/ui/ui_heart_empty.png", 48, 44);
	IMAGEMANAGER->addImage("ui_large_heart", L"image/ui/ui_heart_large.png", 57, 53);
	IMAGEMANAGER->addImage("ui_large_half_heart", L"image/ui/ui_half_heart_large.png", 57, 53);
	IMAGEMANAGER->addImage("ui_X", L"image/ui/ui_X.png", 9, 9);
	IMAGEMANAGER->addImage("ui_coins", L"image/ui/ui_coins.png", 48, 48);

	IMAGEMANAGER->addFrameImage("ui_digit", L"image/ui/ui_digits.png", 198, 24, 11, 1);
	IMAGEMANAGER->addFrameImage("ui_beat_heart", L"image/ui/ui_beat_heart.png", 160, 100, 2, 1);


	//UI(장비)
	IMAGEMANAGER->addImage("equipUI_shovel", L"image/ui/ui_slot_1.png", 60, 66);
	IMAGEMANAGER->addImage("equipUI_attack", L"image/ui/ui_slot_2.png", 60, 66);
	IMAGEMANAGER->addImage("equipUI_body", L"image/ui/ui_slot_3.png", 60, 66);
	IMAGEMANAGER->addImage("equipUI_head", L"image/ui/ui_slot_4.png", 60, 66);
	IMAGEMANAGER->addImage("equipUI_feet", L"image/ui/ui_slot_5.png", 60, 66);
	IMAGEMANAGER->addImage("equipUI_torch", L"image/ui/ui_slot_6.png", 60, 66);
	IMAGEMANAGER->addImage("equipUI_item", L"image/ui/ui_slot_action1.png", 60, 84);
	IMAGEMANAGER->addImage("equipUI_bomb", L"image/ui/ui_slot_bomb.png", 60, 84);
	IMAGEMANAGER->addImage("equipUI_reload", L"image/ui/ui_slot_reload.png", 60, 84);
	IMAGEMANAGER->addImage("equipUI_throw", L"image/ui/ui_slot_throw.png", 60, 84);
	IMAGEMANAGER->addImage("equipUI_throw2", L"image/ui/ui_slot_throw2.png", 60, 84);



	//음악
	SOUNDMANAGER->addSound("mapTool", "sound/music/boss_10.ogg", true, true);
	SOUNDMANAGER->addSound("test_music", "sound/music/zone1.ogg", true, true);
	SOUNDMANAGER->addSound("test_music_shopkeeper", "sound/music/zone1_shopkeeper.ogg", true, true);
	SOUNDMANAGER->addSound("boss_bass", "sound/music/boss4_bass.ogg", true, true);
	SOUNDMANAGER->addSound("boss_drum", "sound/music/boss4_drum.ogg", true, true);
	SOUNDMANAGER->addSound("boss_horn", "sound/music/boss4_horn.ogg", true, true);
	SOUNDMANAGER->addSound("boss_keytar", "sound/music/boss4_keytar.ogg", true, true);
	SOUNDMANAGER->addSound("boss_strings", "sound/music/boss4_strings.ogg", true, true);
	SOUNDMANAGER->addSound("boss_all", "sound/music/boss4_all.mp3", true, true);

	//사운드
	SOUNDMANAGER->addSound("effect_dig_fail", "sound/effect/sfx_dig_fail.ogg", false, false);
	SOUNDMANAGER->addSound("effect_glass_break", "sound/effect/sfx_glass_break.ogg", false, false);
	SOUNDMANAGER->addSound("effect_teleport", "sound/effect/sfx_teleport.ogg", false, false);
	SOUNDMANAGER->addSound("effect_hurt_player_01", "sound/effect/vo_cad_hurt_01.ogg", false, false);
	SOUNDMANAGER->addSound("effect_hurt_player_02", "sound/effect/vo_cad_hurt_02.ogg", false, false);
	SOUNDMANAGER->addSound("effect_hurt_player_03", "sound/effect/vo_cad_hurt_03.ogg", false, false);
	SOUNDMANAGER->addSound("effect_hurt_player_04", "sound/effect/vo_cad_hurt_04.ogg", false, false);
	SOUNDMANAGER->addSound("effect_hurt_player_05", "sound/effect/vo_cad_hurt_05.ogg", false, false);
	SOUNDMANAGER->addSound("effect_hurt_player_06", "sound/effect/vo_cad_hurt_06.ogg", false, false);
	SOUNDMANAGER->addSound("effect_pickup_armor", "sound/effect/sfx_pickup_armor.ogg", false, false);
	SOUNDMANAGER->addSound("effect_pickup_weapon", "sound/effect/sfx_pickup_weapon.ogg", false, false);


	SCENEMANAGER->addScene("맵툴", new mapToolScene);

	SCENEMANAGER->changeScene("맵툴");
	

	
	return S_OK;
}

void playGround::release()
{
	gameNode::release();
	
}

void playGround::update()
{
	gameNode::update();

	SCENEMANAGER->update();

}

void playGround::render()
{
	// Draw 시작 - 이 코드가 빠지면 D2D 출력 X
	D2DMANAGER->beginDraw();
	//===========================================================================
	//				##		여기에 코드 작성(Start)			##



	SCENEMANAGER->render();




	//				##			여기에 코드 작성(End)			##
	//===========================================================================
	//				##카메라 정보 마우스 정보 시간정보 출력	##===================
	WCHAR str[128];
	swprintf_s(str, L"cameraX : %d", CAMERA->getPosX());
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 80);
	swprintf_s(str, L"cameraY : %d", CAMERA->getPosY());
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 100);
	swprintf_s(str, L"mouseX : %.2f", _ptMouse.x);
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 140);
	swprintf_s(str, L"mouseY : %.2f", _ptMouse.y);
	D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY() + 160);
	TIMEMANAGER->render();
	// Draw 끝 - 이 코드가 빠지면 D2D 출력 X
	D2DMANAGER->endDraw();
}