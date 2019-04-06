#pragma once
#include "parentObj.h"

enum ENEMY_TYPE
{
	ENEMY_TYPE_NONE,
	ENEMY_TYPE_SKELETON,
	ENEMY_TYPE_SKELETON_YELLOW,
	ENEMY_TYPE_SKELETON_BLACK,
	ENEMY_TYPE_SKELETON_MAGE_WHITE,
	ENEMY_TYPE_SKELETON_MAGE_YELLOW,
	ENEMY_TYPE_SKELETON_MAGE_BLACK,
	ENEMY_TYPE_ARMADILLO,
	ENEMY_TYPE_SLIME_GREEN,
	ENEMY_TYPE_SLIME_BLUE,
	ENEMY_TYPE_ZOMBIE,
	ENEMY_TYPE_BAT,
	ENEMY_TYPE_BAT_RED,
	ENEMY_TYPE_CLONE,
	ENEMY_TYPE_BAT_MINIBOSS,
	ENEMY_TYPE_BANSHEE,
	ENEMY_TYPE_DRAGON_GREEN,
	ENEMY_TYPE_MINOTAUR,
	ENEMY_TYPE_CORALRIFF_DRUMS,
	ENEMY_TYPE_CORALRIFF_HEAD,
	ENEMY_TYPE_CORALRIFF_HORNS,
	ENEMY_TYPE_CORALRIFF_KEYTAR,
	ENEMY_TYPE_CORALRIFF_STRINGS,
	ENEMY_TYPE_SHOPKEEPER,


	ENEMY_TYPE_COUNT
};



static string ENEMY_NAME[ENEMY_TYPE_COUNT] = { "enemy_none", "enemy_skeleton", "enemy_skeleton_yellow",
"enemy_skeleton_black", "enemy_skeleton_mage_white", "enemy_skeleton_mage_yellow", "enemy_skeleton_mage_black",
"enemy_armadillo",  "enemy_slime_green", "enemy_slime_blue", "enemy_zombie",
"enemy_bat", "enemy_bat_red", "enemy_clone", "enemy_bat_miniboss", "enemy_banshee", "enemy_dragon_green",
"enemy_minotaur", "enemy_coralriff_drums", "enemy_coralriff_head", "enemy_coralriff_horns", "enemy_coralriff_keytar",
"enemy_coralriff_strings", "enemy_shopkeeper"};