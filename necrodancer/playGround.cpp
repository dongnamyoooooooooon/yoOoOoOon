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

	

	{
		//�������
		IMAGEMANAGER->addImage("maptoolbackground", L"image/mapTool/maptoolBackground.png", 240, 540);

		//����Ÿ�Ϲ��
		IMAGEMANAGER->addImage("samplebackground", L"image/mapTool/mapTool_sampleTile.png", 400, 400);

		//������ư
		IMAGEMANAGER->addFrameImage(BUTTON_NAME[MAPTOOL_BUTTON_FLOOR], L"image/button/mapTool_floor.png", 100, 90, 1, 3);
		IMAGEMANAGER->addFrameImage(BUTTON_NAME[MAPTOOL_BUTTON_WALL], L"image/button/mapTool_wall.png", 100, 90, 1, 3);
		IMAGEMANAGER->addFrameImage(BUTTON_NAME[MAPTOOL_BUTTON_PLAYER], L"image/button/mapTool_player.png", 100, 90, 1, 3);
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



		//�����̹���
		IMAGEMANAGER->addImage("mapTool_cursor", L"image/mapTool/cursor.png", 48, 48);
		IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_FLOOR_01], L"image/mapTool/floor_dirt1.png", 156, 104, 3, 2);
		IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_FLOOR_02], L"image/mapTool/floor_dirt2.png", 156, 208, 3, 4);
		IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_FLOOR_03], L"image/mapTool/floor_boss.png", 156, 104, 3, 2);
		IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_FLOOR_04], L"image/mapTool/floor_shop.png", 156, 52, 3, 1);
		IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_FLOOR_05], L"image/mapTool/floor_water.png", 156, 52, 3, 1);
		IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_STAIRS_01], L"image/mapTool/floor_stairs_01.png", TILE_SIZE, TILE_SIZE, 1, 1);
		IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_STAIRS_02], L"image/mapTool/floor_stairs_02.png", TILE_SIZE, TILE_SIZE, 1, 1);
		//IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_STAIRS_01], L"image/mapTool/stairs.png", 288, 48, 6, 1);
		IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_WALL_01], L"image/mapTool/wall_zone1.png", TILE_SIZE * 16, WALLHEIGHT, 16, 1);
		IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_WALL_02], L"image/mapTool/wall_zone2.png", TILE_SIZE * 8, WALLHEIGHT, 8, 1);
		IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_WALL_03], L"image/mapTool/wall_shop.png", TILE_SIZE, WALLHEIGHT, 1, 1);
		IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_WALL_04], L"image/mapTool/wall_shop_cracked.png", TILE_SIZE, WALLHEIGHT, 1, 1);
		IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_WALL_05], L"image/mapTool/wall_stone_01.png", TILE_SIZE, WALLHEIGHT, 1, 1);
		IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_WALL_06], L"image/mapTool/wall_stone_02.png", TILE_SIZE, WALLHEIGHT, 1, 1);
		IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_WALL_07], L"image/mapTool/wall_catacomb_1.png", TILE_SIZE, WALLHEIGHT, 1, 1);
		IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_WALL_08], L"image/mapTool/wall_boss.png", TILE_SIZE * 5, WALLHEIGHT, 5, 1);
		IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_WALL_09], L"image/mapTool/wall_stone_cracked_01.png", TILE_SIZE, WALLHEIGHT, 1, 1);
		IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_WALL_10], L"image/mapTool/wall_stone_cracked_02.png", TILE_SIZE, WALLHEIGHT, 1, 1);
		IMAGEMANAGER->addFrameImage(IMAGE_NAME[IMAGE_NAME_WALL_11], L"image/mapTool/wall_end_of_world.png", TILE_SIZE * 8, WALLHEIGHT, 8, 1);
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

		//��
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


		//ȶ��(��)
		IMAGEMANAGER->addFrameImage("frame_fire", L"image/frame_fire.png", 192, 48, 4, 1);

		//������
		IMAGEMANAGER->addImage("item_shadow", L"image/items/item_shadow.png", 48, 58);


		//����
		IMAGEMANAGER->addFrameImage(ARMOR_NAME[ITEM_ARMOR_LEATHER], L"image/items/armor_leather.png", 48, 96, 1, 2);
		IMAGEMANAGER->addFrameImage(ARMOR_NAME[ITEM_ARMOR_CHAINMAIL], L"image/items/armor_chainmail.png", 48, 96, 1, 2);
		IMAGEMANAGER->addFrameImage(ARMOR_NAME[ITEM_ARMOR_PLATEMAIL], L"image/items/armor_platemail.png", 48, 96, 1, 2);
		IMAGEMANAGER->addFrameImage(ARMOR_NAME[ITEM_ARMOR_HEAVYPLATE], L"image/items/armor_heavyplate.png", 48, 96, 1, 2);
		IMAGEMANAGER->addFrameImage(ARMOR_NAME[ITEM_ARMOR_KARADE], L"image/items/armor_gi.png", 48, 96, 1, 2);
		IMAGEMANAGER->addFrameImage(ARMOR_NAME[ITEM_ARMOR_OBSIDIAN], L"image/items/armor_obsidian.png", 156, 104, 3, 2);
		IMAGEMANAGER->addFrameImage(ARMOR_NAME[ITEM_ARMOR_GLASS], L"image/items/armor_glass.png", 48, 96, 1, 2);

		//��
		IMAGEMANAGER->addFrameImage(SHOVEL_NAME[ITEM_SHOVEL_BASIC], L"image/items/shovel_basic.png", 48, 96, 1, 2);
		IMAGEMANAGER->addFrameImage(SHOVEL_NAME[ITEM_SHOVEL_TITANIUM], L"image/items/shovel_titanium.png", 48, 96, 1, 2);
		IMAGEMANAGER->addFrameImage(SHOVEL_NAME[ITEM_SHOVEL_GLASS], L"image/items/shovel_glass.png", 48, 96, 1, 2);
		IMAGEMANAGER->addFrameImage(SHOVEL_NAME[ITEM_SHOVEL_OBSIDIAN], L"image/items/shovel_obsidian.png", 156, 104, 3, 2);
		IMAGEMANAGER->addFrameImage(SHOVEL_NAME[ITEM_SHOVEL_BLOOD], L"image/items/shovel_blood.png", 48, 96, 1, 2);
		IMAGEMANAGER->addFrameImage(SHOVEL_NAME[ITEM_SHOVEL_CRYSTAL], L"image/items/shovel_crystal.png", 48, 96, 1, 2);
		IMAGEMANAGER->addFrameImage(SHOVEL_NAME[ITEM_SHOVEL_GLASSSHARD], L"image/items/shovel_shard.png", 48, 96, 1, 2);

		//����
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

		//ȶ��(������)
		IMAGEMANAGER->addFrameImage(TORCH_NAME[ITEM_TORCH_BASIC], L"image/items/torch_1.png", 48, 96, 1, 2);
		IMAGEMANAGER->addFrameImage(TORCH_NAME[ITEM_TORCH_BRIGHT], L"image/items/torch_2.png", 48, 96, 1, 2);
		IMAGEMANAGER->addFrameImage(TORCH_NAME[ITEM_TORCH_LUMINIOUS], L"image/items/torch_3.png", 48, 96, 1, 2);
		IMAGEMANAGER->addFrameImage(TORCH_NAME[ITEM_TORCH_GLASS], L"image/items/torch_glass.png", 48, 96, 1, 2);
		IMAGEMANAGER->addFrameImage(TORCH_NAME[ITEM_TORCH_OBSIDIAN], L"image/items/torch_obsidian.png", 144, 108, 3, 2);
		IMAGEMANAGER->addFrameImage(TORCH_NAME[ITEM_TORCH_INFERNAL], L"image/items/torch_infernal.png", 48, 96, 1, 2);
		IMAGEMANAGER->addFrameImage(TORCH_NAME[ITEM_TORCH_FORESIGHT], L"image/items/torch_foresight.png", 48, 96, 1, 2);

		//����
		IMAGEMANAGER->addFrameImage(HEADWEAR_NAME[ITEM_HEADWEAR_HELMAT], L"image/items/head_helmet.png", 48, 84, 1, 2);
		IMAGEMANAGER->addFrameImage(HEADWEAR_NAME[ITEM_HEADWEAR_BLASTHELM], L"image/items/head_blast_helm.png", 48, 96, 1, 2);
		IMAGEMANAGER->addFrameImage(HEADWEAR_NAME[ITEM_HEADWEAR_TELEPORT], L"image/items/head_crown_of_teleportation.png", 48, 96, 1, 2);

		//�Ź�
		IMAGEMANAGER->addFrameImage(FOOTWEAR_NAME[ITEM_FOOTWEAR_BALLET], L"image/items/feet_ballet_shoes.png", 48, 96, 1, 2);
		IMAGEMANAGER->addFrameImage(FOOTWEAR_NAME[ITEM_FOOTWEAR_WINGED], L"image/items/feet_boots_winged.png", 48, 96, 1, 2);
		IMAGEMANAGER->addFrameImage(FOOTWEAR_NAME[ITEM_FOOTWEAR_LEAD], L"image/items/feet_boots_lead.png", 48, 100, 1, 2);
		IMAGEMANAGER->addFrameImage(FOOTWEAR_NAME[ITEM_FOOTWEAR_HARGREAVES], L"image/items/feet_greaves.png", 48, 96, 1, 2);
		IMAGEMANAGER->addFrameImage(FOOTWEAR_NAME[ITEM_FOOTWEAR_STRENGTH], L"image/items/feet_boots_strength.png", 48, 96, 1, 2);

		//�Ҹ�ǰ
		IMAGEMANAGER->addFrameImage(CONSUMABLE_NAME[ITEM_CONSUMABLE_APPLE], L"image/items/food_1.png", 48, 96, 1, 2);
		IMAGEMANAGER->addFrameImage(CONSUMABLE_NAME[ITEM_CONSUMABLE_CHEESE], L"image/items/food_2.png", 48, 96, 1, 2);
		IMAGEMANAGER->addFrameImage(CONSUMABLE_NAME[ITEM_CONSUMABLE_DRUMSTICK], L"image/items/food_3.png", 48, 96, 1, 2);
		IMAGEMANAGER->addFrameImage(CONSUMABLE_NAME[ITEM_CONSUMABLE_HAM], L"image/items/food_4.png", 48, 96, 1, 2);
		IMAGEMANAGER->addFrameImage(CONSUMABLE_NAME[ITEM_CONSUMABLE_WARDRUM], L"image/items/war_drum.png", 156, 112, 3, 2);

		//��ź
		IMAGEMANAGER->addFrameImage(BOMB_NAME[ITEM_BOMB_X1], L"image/items/bomb.png", 240, 96, 5, 2);
		IMAGEMANAGER->addFrameImage(BOMB_NAME[ITEM_BOMB_X3], L"image/items/bomb_3.png", 48, 96, 1, 2);

		//��Ʈ
		IMAGEMANAGER->addFrameImage(HEART_NAME[ITEM_HEART_FILLED], L"image/items/misc_heart_container.png", 48, 96, 1, 2);
		IMAGEMANAGER->addFrameImage(HEART_NAME[ITEM_HEART_DOUBLE_FILLED], L"image/items/misc_heart_container2.png", 48, 96, 1, 2);
		IMAGEMANAGER->addFrameImage(HEART_NAME[ITEM_HEART_EMPTY], L"image/items/misc_heart_container_empty.png", 48, 96, 1, 2);
		IMAGEMANAGER->addFrameImage(HEART_NAME[ITEM_HEART_DOUBLE_EMPTY], L"image/items/misc_heart_container_empty2.png", 48, 96, 1, 2);

		//����
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

		//��������Ʈ
		IMAGEMANAGER->addFrameImage("attack_dagger_basic", L"image/effect/swipe_dagger.png", 144, 48, 3, 1);
	

		//����(������)
		IMAGEMANAGER->addImage("enemy_heart_empty", L"image/enemy/heart_empty_small.png", 24, 24);
		IMAGEMANAGER->addImage("enemy_heart", L"image/enemy/heart_small.png", 24, 24);
		IMAGEMANAGER->addImage("enemy_shadow", L"image/enemy/shadow_standard.png", 48, 54);
		IMAGEMANAGER->addImage("boss_shadow", L"image/enemy/tentacle_tell.png", 30, 20);
		IMAGEMANAGER->addFrameImage("boss_attack", L"image/enemy/boss_attack.png", 710, 145, 5, 1);

		//������
		IMAGEMANAGER->addFrameImage("shovel_basic", L"image/items/shovel_basic.png", 48, 96, 1, 2);

		//�÷��̾�
		IMAGEMANAGER->addImage("player_shadow", L"image/player/player_shadow.png", 48, 54);
		IMAGEMANAGER->addFrameImage("player_head", L"image/player/player_heads.png", 192, 96, 4, 2);
		IMAGEMANAGER->addFrameImage("player_body", L"image/player/player_body.png", 192, 480, 4, 10);

		//��������
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

		//��Ÿ(���ĺ�����)
		IMAGEMANAGER->addImage("alpha_black", L"image/black.png", 100, 100);
		IMAGEMANAGER->addImage("magic_white", L"image/white.png", 100, 100);
		IMAGEMANAGER->addImage("magic_red", L"image/red.png", 100, 100);
		IMAGEMANAGER->addImage("magic_gray", L"image/gray.png", 100, 100);

		//UI(���)
		IMAGEMANAGER->addImage("equipUI_shovel", L"image/ui/ui_slot_1.png", 60, 66);
		IMAGEMANAGER->addImage("equipUI_weapon", L"image/ui/ui_slot_2.png", 60, 66);
		IMAGEMANAGER->addImage("equipUI_armor", L"image/ui/ui_slot_3.png", 60, 66);
		IMAGEMANAGER->addImage("equipUI_headwear", L"image/ui/ui_slot_4.png", 60, 66);
		IMAGEMANAGER->addImage("equipUI_footwear", L"image/ui/ui_slot_5.png", 60, 66);
		IMAGEMANAGER->addImage("equipUI_torch", L"image/ui/ui_slot_6.png", 60, 66);
		IMAGEMANAGER->addImage("equipUI_item", L"image/ui/ui_slot_action1.png", 60, 84);
		IMAGEMANAGER->addImage("equipUI_bomb", L"image/ui/ui_slot_bomb.png", 60, 84);
		IMAGEMANAGER->addImage("equipUI_reload", L"image/ui/ui_slot_reload.png", 60, 84);
		IMAGEMANAGER->addImage("equipUI_throw", L"image/ui/ui_slot_throw.png", 60, 84);
		IMAGEMANAGER->addImage("equipUI_throw2", L"image/ui/ui_slot_throw2.png", 60, 84);

		//�����ۼ���
		IMAGEMANAGER->addImage("hint_dagger_basic", L"image/hint/hint_daggerthrowable.png", 140, 18);
		IMAGEMANAGER->addImage("hint_broadsword_basic", L"image/hint/hint_widerattack.png", 97, 18);
		IMAGEMANAGER->addImage("hint_shovel_basic", L"image/hint/hint_1dig.png", 85, 18);
		IMAGEMANAGER->addImage("hint_armor_gi", L"image/hint/hint_takeanddealdoubledamage.png", 223, 18);
		IMAGEMANAGER->addImage("hint_armor_leather", L"image/hint/hint_0-5defense.png", 95, 18);
		IMAGEMANAGER->addImage("hint_armorchainmail", L"image/hint/hint_1defense.png", 81, 18);
		IMAGEMANAGER->addImage("hint_armor_platemail", L"image/hint/hint_1-5defense.png", 95, 18);
		IMAGEMANAGER->addImage("hint_armor_heavyplate", L"image/hint/hint_2defenseheavy.png", 127, 18);
		IMAGEMANAGER->addImage("hint_armor_obsidian", L"image/hint/hint_multiplierbaseddefense.png", 136, 18);
		IMAGEMANAGER->addImage("hint_armor_glass", L"image/hint/hint_preventsdamagethenshatters.png", 169, 18);

		IMAGEMANAGER->addImage("hint_torch_basic", L"image/hint/hint_1visionradius.png", 63, 18);

		//������Ʈ��
		IMAGEMANAGER->addImage("boss_bottom", L"image/bossUI/bg_bottomblade.png", 728, 64);
		IMAGEMANAGER->addImage("boss_background", L"image/bossUI/bg_gradient.png", 1920, 296);
		IMAGEMANAGER->addImage("boss_top", L"image/bossUI/bg_topblade.png", 602, 68);
		IMAGEMANAGER->addImage("boss_face", L"image/bossUI/bosscreen_coralriff.png", 960, 424);
		IMAGEMANAGER->addImage("boss_name", L"image/bossUI/boss_coralriffsplash.png", 202, 48);



		//����
		SOUNDMANAGER->addSound("mapTool", "sound/music/boss_10.ogg", true, true);
		SOUNDMANAGER->addSound("test_music", "sound/music/zone1.ogg", true, true);
		SOUNDMANAGER->addSound("test_music_shopkeeper", "sound/music/zone1_shopkeeper.ogg", true, true);
		SOUNDMANAGER->addSound("boss_bass", "sound/music/boss4_bass.ogg", true, true);
		SOUNDMANAGER->addSound("boss_drum", "sound/music/boss4_drum.ogg", true, true);
		SOUNDMANAGER->addSound("boss_horn", "sound/music/boss4_horn.ogg", true, true);
		SOUNDMANAGER->addSound("boss_keytar", "sound/music/boss4_keytar.ogg", true, true);
		SOUNDMANAGER->addSound("boss_strings", "sound/music/boss4_strings.ogg", true, true);

		//����
		SOUNDMANAGER->addSound("sound_dig_fail", "sound/effect/sfx_dig_fail.ogg", false, false);
		SOUNDMANAGER->addSound("sound_door_open", "sound/effect/obj_door_open.ogg", false, false);
		SOUNDMANAGER->addSound("sound_glass_break", "sound/effect/sfx_glass_break.ogg", false, false);
		SOUNDMANAGER->addSound("sound_teleport", "sound/effect/sfx_teleport.ogg", false, false);
		SOUNDMANAGER->addSound("sound_hurt_player_01", "sound/effect/vo_cad_hurt_01.ogg", false, false);
		SOUNDMANAGER->addSound("sound_hurt_player_02", "sound/effect/vo_cad_hurt_02.ogg", false, false);
		SOUNDMANAGER->addSound("sound_hurt_player_03", "sound/effect/vo_cad_hurt_03.ogg", false, false);
		SOUNDMANAGER->addSound("sound_hurt_player_04", "sound/effect/vo_cad_hurt_04.ogg", false, false);
		SOUNDMANAGER->addSound("sound_hurt_player_05", "sound/effect/vo_cad_hurt_05.ogg", false, false);
		SOUNDMANAGER->addSound("sound_hurt_player_06", "sound/effect/vo_cad_hurt_06.ogg", false, false);
		SOUNDMANAGER->addSound("sound_pickup_armor", "sound/effect/sfx_pickup_armor.ogg", false, false);
		SOUNDMANAGER->addSound("sound_pickup_weapon", "sound/effect/sfx_pickup_weapon.ogg", false, false);
		SOUNDMANAGER->addSound("sound_pickup_gold_01", "sound/effect/sfx_pickup_gold_01.ogg", false, false);
		SOUNDMANAGER->addSound("sound_pickup_gold_02", "sound/effect/sfx_pickup_gold_02.ogg", false, false);
		SOUNDMANAGER->addSound("sound_pickup_gold_03", "sound/effect/sfx_pickup_gold_03.ogg", false, false);
	
		SOUNDMANAGER->addSound("sound_dig_brick", "sound/effect/mov_dig_brick.ogg", false, false);
		SOUNDMANAGER->addSound("sound_dig_dirt", "sound/effect/mov_dig_dirt.ogg", false, false);
		SOUNDMANAGER->addSound("sound_dig_stone", "sound/effect/mov_dig_stone.ogg", false, false);
		SOUNDMANAGER->addSound("sound_dig_player_01", "sound/effect/vo_cad_dig_01.ogg", false, false);
		SOUNDMANAGER->addSound("sound_dig_player_02", "sound/effect/vo_cad_dig_02.ogg", false, false);
		SOUNDMANAGER->addSound("sound_dig_player_03", "sound/effect/vo_cad_dig_03.ogg", false, false);
		SOUNDMANAGER->addSound("sound_dig_player_04", "sound/effect/vo_cad_dig_04.ogg", false, false);
		SOUNDMANAGER->addSound("sound_dig_player_05", "sound/effect/vo_cad_dig_05.ogg", false, false);
		SOUNDMANAGER->addSound("sound_dig_player_06", "sound/effect/vo_cad_dig_06.ogg", false, false);

		SOUNDMANAGER->addSound("sound_cad_melee_1_01", "sound/effect/vo_cad_melee_1_01.ogg", false, false);
		SOUNDMANAGER->addSound("sound_cad_melee_1_02", "sound/effect/vo_cad_melee_1_02.ogg", false, false);
		SOUNDMANAGER->addSound("sound_cad_melee_1_03", "sound/effect/vo_cad_melee_1_03.ogg", false, false);
		SOUNDMANAGER->addSound("sound_cad_melee_1_04", "sound/effect/vo_cad_melee_1_04.ogg", false, false);
		SOUNDMANAGER->addSound("sound_cad_melee_2_01", "sound/effect/vo_cad_melee_2_01.ogg", false, false);
		SOUNDMANAGER->addSound("sound_cad_melee_2_02", "sound/effect/vo_cad_melee_2_02.ogg", false, false);
		SOUNDMANAGER->addSound("sound_cad_melee_2_03", "sound/effect/vo_cad_melee_2_03.ogg", false, false);
		SOUNDMANAGER->addSound("sound_cad_melee_2_04", "sound/effect/vo_cad_melee_2_04.ogg", false, false);
		SOUNDMANAGER->addSound("sound_cad_melee_3_01", "sound/effect/vo_cad_melee_3_01.ogg", false, false);
		SOUNDMANAGER->addSound("sound_cad_melee_3_02", "sound/effect/vo_cad_melee_3_02.ogg", false, false);
		SOUNDMANAGER->addSound("sound_cad_melee_3_03", "sound/effect/vo_cad_melee_3_03.ogg", false, false);
		SOUNDMANAGER->addSound("sound_cad_melee_3_04", "sound/effect/vo_cad_melee_3_04.ogg", false, false);
		SOUNDMANAGER->addSound("sound_cad_melee_4_01", "sound/effect/vo_cad_melee_4_01.ogg", false, false);
		SOUNDMANAGER->addSound("sound_cad_melee_4_02", "sound/effect/vo_cad_melee_4_02.ogg", false, false);
		SOUNDMANAGER->addSound("sound_cad_melee_4_03", "sound/effect/vo_cad_melee_4_03.ogg", false, false);
		SOUNDMANAGER->addSound("sound_cad_melee_4_04", "sound/effect/vo_cad_melee_4_04.ogg", false, false);
		SOUNDMANAGER->addSound("sound_cad_melee_4_05", "sound/effect/vo_cad_melee_4_05.ogg", false, false);

		SOUNDMANAGER->addSound("sound_zombie_attack", "sound/effect/en_zombie_attack.ogg", false, false);
		SOUNDMANAGER->addSound("sound_armadillo_attack", "sound/effect/en_armadillo_attack.ogg", false, false);
		SOUNDMANAGER->addSound("sound_bat_attack", "sound/effect/en_bat_attack.ogg", false, false);
		SOUNDMANAGER->addSound("sound_clone_attack", "sound/effect/en_clone_attack.ogg", false, false);
		SOUNDMANAGER->addSound("sound_skel_attack_melee", "sound/effect/en_skel_attack_melee.ogg", false, false);
		SOUNDMANAGER->addSound("sound_slime_attack", "sound/effect/en_slime_attack.ogg", false, false);
		SOUNDMANAGER->addSound("sound_wraith_attack", "sound/effect/en_wraith_attack.ogg", false, false);
		SOUNDMANAGER->addSound("sound_banshee_attack", "sound/effect/en_banshee_attack.ogg", false, false);
		SOUNDMANAGER->addSound("sound_vampbat_attack", "sound/effect/en_vampbat_attack.ogg", false, false);
		SOUNDMANAGER->addSound("sound_dragon_attack_melee", "sound/effect/en_dragon_attack_melee.ogg", false, false);
		SOUNDMANAGER->addSound("sound_minotaur_attack", "sound/effect/en_minotaur_attack.ogg", false, false);
		SOUNDMANAGER->addSound("sound_coralriff_attack_mel_01", "sound/effect/en_coralriff_attack_mel_01.ogg", false, false);
		SOUNDMANAGER->addSound("sound_coralriff_attack_mel_02", "sound/effect/en_coralriff_attack_mel_02.ogg", false, false);
		SOUNDMANAGER->addSound("sound_coralriff_attack_mel_03", "sound/effect/en_coralriff_attack_mel_03.ogg", false, false);
		SOUNDMANAGER->addSound("sound_coralriff_attack_mel_04", "sound/effect/en_coralriff_attack_mel_04.ogg", false, false);
		SOUNDMANAGER->addSound("sound_coralriff_attack_splash_01", "sound/effect/en_coralriff_attack_splash_01.ogg", false, false);
		SOUNDMANAGER->addSound("sound_coralriff_attack_splash_02", "sound/effect/en_coralriff_attack_splash_02.ogg", false, false);
		SOUNDMANAGER->addSound("sound_coralriff_attack_splash_03", "sound/effect/en_coralriff_attack_splash_03.ogg", false, false);
		SOUNDMANAGER->addSound("sound_coralriff_attack_splash_04", "sound/effect/en_coralriff_attack_splash_04.ogg", false, false);
		SOUNDMANAGER->addSound("sound_shopkeep_norm_attack_01", "sound/effect/en_shopkeep_norm_attack_01.ogg", false, false);
		SOUNDMANAGER->addSound("sound_shopkeep_norm_attack_02", "sound/effect/en_shopkeep_norm_attack_02.ogg", false, false);
		SOUNDMANAGER->addSound("sound_shopkeep_norm_attack_03", "sound/effect/en_shopkeep_norm_attack_03.ogg", false, false);
		SOUNDMANAGER->addSound("sound_shopkeep_norm_attack_04", "sound/effect/en_shopkeep_norm_attack_04.ogg", false, false);

		SOUNDMANAGER->addSound("sound_skel_head_loss_01", "sound/effect/en_skel_head_loss_01.ogg", false, false);
		SOUNDMANAGER->addSound("sound_skel_head_loss_02", "sound/effect/en_skel_head_loss_02.ogg", false, false);
		SOUNDMANAGER->addSound("sound_skel_head_loss_03", "sound/effect/en_skel_head_loss_03.ogg", false, false);

		SOUNDMANAGER->addSound("sound_zombie_death", "sound/effect/en_zombie_death.ogg", false, false);
		SOUNDMANAGER->addSound("sound_armadillo_death", "sound/effect/en_armadillo_death.ogg", false, false);
		SOUNDMANAGER->addSound("sound_bat_death", "sound/effect/en_bat_death.ogg", false, false);
		SOUNDMANAGER->addSound("sound_clone_death", "sound/effect/en_clone_death.ogg", false, false);
		SOUNDMANAGER->addSound("sound_skel_death", "sound/effect/en_skel_death.ogg", false, false);
		SOUNDMANAGER->addSound("sound_slime_death", "sound/effect/en_slime_death.ogg", false, false);
		SOUNDMANAGER->addSound("sound_slime_death_01", "sound/effect/en_slime_death_01.ogg", false, false);
		SOUNDMANAGER->addSound("sound_slime_death_02", "sound/effect/en_slime_death_02.ogg", false, false);
		SOUNDMANAGER->addSound("sound_slime_death_03", "sound/effect/en_slime_death_03.ogg", false, false);
		SOUNDMANAGER->addSound("sound_wraith_death", "sound/effect/en_wraith_death.ogg", false, false);
		SOUNDMANAGER->addSound("sound_banshee_death", "sound/effect/en_banshee_death.ogg", false, false);
		SOUNDMANAGER->addSound("sound_vampbat_death", "sound/effect/en_vampbat_death.ogg", false, false);
		SOUNDMANAGER->addSound("sound_dragon_death", "sound/effect/en_dragon_death.ogg", false, false);
		SOUNDMANAGER->addSound("sound_minotaur_death", "sound/effect/en_minotaur_death.ogg", false, false);
		SOUNDMANAGER->addSound("sound_coralriff_death", "sound/effect/en_coralriff_death.ogg", false, false);
		SOUNDMANAGER->addSound("sound_shopkeep_norm_death_01", "sound/effect/en_shopkeep_norm_death_01.ogg", false, false);
		SOUNDMANAGER->addSound("sound_shopkeep_norm_death_02", "sound/effect/en_shopkeep_norm_death_02.ogg", false, false);
		SOUNDMANAGER->addSound("sound_shopkeep_norm_death_03", "sound/effect/en_shopkeep_norm_death_03.ogg", false, false);
		SOUNDMANAGER->addSound("sound_shopkeep_norm_death_04", "sound/effect/en_shopkeep_norm_death_04.ogg", false, false);
		SOUNDMANAGER->addSound("sound_shopkeep_norm_death_05", "sound/effect/en_shopkeep_norm_death_05.ogg", false, false);

		SOUNDMANAGER->addSound("sound_armadillo_hit", "sound/effect/en_armadillo_hit.ogg", false, false);
		SOUNDMANAGER->addSound("sound_bat_hit", "sound/effect/en_bat_hit.ogg", false, false);
		SOUNDMANAGER->addSound("sound_skel_hit", "sound/effect/en_skel_hit.ogg", false, false);
		SOUNDMANAGER->addSound("sound_skel_hit_01", "sound/effect/en_skel_hit_01.ogg", false, false);
		SOUNDMANAGER->addSound("sound_skel_hit_02", "sound/effect/en_skel_hit_02.ogg", false, false);
		SOUNDMANAGER->addSound("sound_skel_hit_03", "sound/effect/en_skel_hit_03.ogg", false, false);
		SOUNDMANAGER->addSound("sound_slime_hit", "sound/effect/en_slime_hit.ogg", false, false);
		SOUNDMANAGER->addSound("sound_slime_hit_01", "sound/effect/en_slime_hit_01.ogg", false, false);
		SOUNDMANAGER->addSound("sound_slime_hit_02", "sound/effect/en_slime_hit_02.ogg", false, false);
		SOUNDMANAGER->addSound("sound_slime_hit_03", "sound/effect/en_slime_hit_03.ogg", false, false);
		SOUNDMANAGER->addSound("sound_banshee_hit_01", "sound/effect/en_banshee_hit_01.ogg", false, false);
		SOUNDMANAGER->addSound("sound_banshee_hit_02", "sound/effect/en_banshee_hit_02.ogg", false, false);
		SOUNDMANAGER->addSound("sound_banshee_hit_03", "sound/effect/en_banshee_hit_03.ogg", false, false);
		SOUNDMANAGER->addSound("sound_vampbat_hit_01", "sound/effect/en_vampbat_hit_01.ogg", false, false);
		SOUNDMANAGER->addSound("sound_vampbat_hit_02", "sound/effect/en_vampbat_hit_02.ogg", false, false);
		SOUNDMANAGER->addSound("sound_vampbat_hit_03", "sound/effect/en_vampbat_hit_03.ogg", false, false);
		SOUNDMANAGER->addSound("sound_dragon_hit_01", "sound/effect/en_dragon_hit_01.ogg", false, false);
		SOUNDMANAGER->addSound("sound_dragon_hit_02", "sound/effect/en_dragon_hit_02.ogg", false, false);
		SOUNDMANAGER->addSound("sound_dragon_hit_03", "sound/effect/en_dragon_hit_03.ogg", false, false);
		SOUNDMANAGER->addSound("sound_minotaur_hit", "sound/effect/en_minotaur_hit.ogg", false, false);
		SOUNDMANAGER->addSound("sound_minotaur_hit_01", "sound/effect/en_minotaur_hit_01.ogg", false, false);
		SOUNDMANAGER->addSound("sound_minotaur_hit_02", "sound/effect/en_minotaur_hit_02.ogg", false, false);
		SOUNDMANAGER->addSound("sound_minotaur_hit_03", "sound/effect/en_minotaur_hit_03.ogg", false, false);
		SOUNDMANAGER->addSound("sound_coralriff_hit_01", "sound/effect/en_coralriff_hit_01.ogg", false, false);
		SOUNDMANAGER->addSound("sound_coralriff_hit_02", "sound/effect/en_coralriff_hit_02.ogg", false, false);
		SOUNDMANAGER->addSound("sound_coralriff_hit_03", "sound/effect/en_coralriff_hit_03.ogg", false, false);
		SOUNDMANAGER->addSound("sound_coralriff_hit_04", "sound/effect/en_coralriff_hit_04.ogg", false, false);
		SOUNDMANAGER->addSound("sound_shopkeep_norm_hit_01", "sound/effect/en_shopkeep_norm_hit_01.ogg", false, false);
		SOUNDMANAGER->addSound("sound_shopkeep_norm_hit_02", "sound/effect/en_shopkeep_norm_hit_02.ogg", false, false);
		SOUNDMANAGER->addSound("sound_shopkeep_norm_hit_03", "sound/effect/en_shopkeep_norm_hit_03.ogg", false, false);
		SOUNDMANAGER->addSound("sound_shopkeep_norm_hit_04", "sound/effect/en_shopkeep_norm_hit_04.ogg", false, false);
		SOUNDMANAGER->addSound("sound_shopkeep_norm_hit_05", "sound/effect/en_shopkeep_norm_hit_05.ogg", false, false);
		SOUNDMANAGER->addSound("sound_shopkeep_norm_hit_06", "sound/effect/en_shopkeep_norm_hit_06.ogg", false, false);

		SOUNDMANAGER->addSound("sound_wraith_cry", "sound/effect/en_wraith_cry.ogg", false, false);
		SOUNDMANAGER->addSound("sound_vampbat_cry", "sound/effect/en_vampbat_cry.ogg", false, false);
		SOUNDMANAGER->addSound("sound_banshee_cry", "sound/effect/en_banshee_cry.ogg", false, false);
		SOUNDMANAGER->addSound("sound_dragon_cry", "sound/effect/en_dragon_cry.ogg", false, false);
		SOUNDMANAGER->addSound("sound_minotaur_cry", "sound/effect/en_minotaur_cry.ogg", false, false);
		SOUNDMANAGER->addSound("sound_coralriff_cry", "sound/effect/en_coralriff_cry.ogg", false, false);

		SOUNDMANAGER->addSound("sound_banshee_loop", "sound/effect/en_banshee_loop.ogg", false, false);

		SOUNDMANAGER->addSound("sound_dragon_walk_01", "sound/effect/en_dragon_walk_01.ogg", false, false);
		SOUNDMANAGER->addSound("sound_dragon_walk_02", "sound/effect/en_dragon_walk_02.ogg", false, false);
		SOUNDMANAGER->addSound("sound_dragon_walk_03", "sound/effect/en_dragon_walk_03.ogg", false, false);

		SOUNDMANAGER->addSound("sound_skel_head_loss_01", "sound/effect/en_skel_head_loss_01.ogg", false, false);
		SOUNDMANAGER->addSound("sound_skel_head_loss_02", "sound/effect/en_skel_head_loss_02.ogg", false, false);
		SOUNDMANAGER->addSound("sound_skel_head_loss_03", "sound/effect/en_skel_head_loss_03.ogg", false, false);

		SOUNDMANAGER->addSound("sound_armadillo_shielded", "sound/effect/en_armadillo_shielded.ogg", false, false);

		SOUNDMANAGER->addSound("sound_armadillo_wallimpact", "sound/effect/en_armadillo_wallimpact.ogg", false, false);
		SOUNDMANAGER->addSound("sound_minotaur_wallimpact", "sound/effect/en_minotaur_wallimpact.ogg", false, false);

		SOUNDMANAGER->addSound("sound_minotaur_charge", "sound/effect/en_minotaur_charge.ogg", false, false);

		SOUNDMANAGER->addSound("sound_spell_wind", "sound/effect/wep_spell_wind.ogg", false, false);

		SOUNDMANAGER->addSound("sound_chain_break", "sound/effect/sfx_chain_break.ogg", false, false);
		SOUNDMANAGER->addSound("sound_chain_groove", "sound/effect/sfx_chain_groove.ogg", false, false);

		SOUNDMANAGER->addSound("sound_announcer_coralriff", "sound/effect/vo_announcer_coralriff.ogg", false, false);

		SOUNDMANAGER->addSound("sound_boss_wall", "sound/effect/boss_zone1_walls.ogg", false, false);

		SOUNDMANAGER->addSound("sound_boss_intro", "sound/effect/vo_announcer_coralriff.ogg", false, false);

	}
	_bossIntro = new bossIntroScene;
	_testMap = new testMapScene;

	SCENEMANAGER->addScene("����", new mapToolScene);
	SCENEMANAGER->addScene("�׽���", _testMap);
	SCENEMANAGER->addScene("�ε�", new loadingScene);
	SCENEMANAGER->addScene("����", _bossIntro);


	SCENEMANAGER->changeScene("����");
	
	//Ŀ��
	initCursor();
	
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

	//Ŀ��
	frameCursor();

}

void playGround::render()
{
	// Draw ���� - �� �ڵ尡 ������ D2D ��� X
	D2DMANAGER->beginDraw();
	//===========================================================================
	//				##		���⿡ �ڵ� �ۼ�(Start)			##



	SCENEMANAGER->render();




	//				##			���⿡ �ڵ� �ۼ�(End)			##
	//===========================================================================
	//				##ī�޶� ���� ���콺 ���� �ð����� ���	##===================
	WCHAR str[128];
	if (KEYMANAGER->isToggleKey(VK_F9))
	{
		swprintf_s(str, L"cameraX : %.0f", CAMERA->getPosX());
		D2DMANAGER->drawText(str, CAMERA->getPosX() + 12, CAMERA->getPosY() + 82, 15, RGB(255, 0, 0));
		swprintf_s(str, L"cameraY : %.0f", CAMERA->getPosY());
		D2DMANAGER->drawText(str, CAMERA->getPosX() + 12, CAMERA->getPosY() + 102, 15, RGB(255, 0, 0));
		swprintf_s(str, L"mouseX : %.2f", _ptMouse.x);
		D2DMANAGER->drawText(str, CAMERA->getPosX() + 12, CAMERA->getPosY() + 142, 15, RGB(255, 0, 0));
		swprintf_s(str, L"mouseY : %.2f", _ptMouse.y);
		D2DMANAGER->drawText(str, CAMERA->getPosX() + 12, CAMERA->getPosY() + 162, 15, RGB(255, 0, 0));

		swprintf_s(str, L"cameraX : %.0f", CAMERA->getPosX());
		D2DMANAGER->drawText(str, CAMERA->getPosX() + 10, CAMERA->getPosY() + 80, 15, RGB(0, 255, 255));
		swprintf_s(str, L"cameraY : %.0f", CAMERA->getPosY());
		D2DMANAGER->drawText(str, CAMERA->getPosX() + 10, CAMERA->getPosY() + 100, 15, RGB(0, 255, 255));
		swprintf_s(str, L"mouseX : %.2f", _ptMouse.x);
		D2DMANAGER->drawText(str, CAMERA->getPosX() + 10, CAMERA->getPosY() + 140, 15, RGB(0, 255, 255));
		swprintf_s(str, L"mouseY : %.2f", _ptMouse.y);
		D2DMANAGER->drawText(str, CAMERA->getPosX() + 10, CAMERA->getPosY() + 160, 15, RGB(0, 255, 255));
		TIMEMANAGER->render();
	}
	// Draw �� - �� �ڵ尡 ������ D2D ��� X
	D2DMANAGER->endDraw();
}

void playGround::initCursor()
{
	a = LoadCursorFromFile("a.cur");
	b = LoadCursorFromFile("b.cur");
	c = LoadCursorFromFile("c.cur");
	d = LoadCursorFromFile("d.cur");
	_count = 0;
}

void playGround::frameCursor()
{
	_count++;
	if (_count % 40 > 20)
	{
		SetCursor(a);
	}
	else if (_count % 40 < 20)
	{
		SetCursor(c);
		if (_count == 1000)
			_count = 0;
	}
}
