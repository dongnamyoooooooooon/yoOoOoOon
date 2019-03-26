#pragma once
#include "parentObj.h"

/*
					아이템 인포메이쎤

		1. 아이템 재질 순서
			1) 기본
			2) 티타늄
			3) 유리
			4) 흑요석
			5) 피
			6) 크리스탈
			7) 황금				(삽제외)

		2. 갑옷
			현재 갑옷보다 상위 등급의 갑옷을 획득했다면 기존의 하위 등급의 갑옷은 사라진다.

		3. 흑요석은 실시간으로 값을 계속 받아와야한다.


*/



enum ITEM_TYPE
{
	ITEM_TYPE_SHOVEL,					//삽
	ITEM_TYPE_WEAPON,					//무기
	ITEM_TYPE_TORCH,					//횃불
	ITEM_TYPE_ARMOR,					//갑옷
	ITEM_TYPE_HEADWEAR,					//투구
	ITEM_TYPE_FOOTWEAR,					//신발
	ITEM_TYPE_CONSUMABLE,				//소모품
	ITEM_TYPE_HEART,					//하트
	ITEM_TYPE_COIN,
	ITEM_TYPE_BOMB,

	ITEM_TYPE_NONE,
	ITEM_TYPE_COUNT = ITEM_TYPE_NONE
};

enum ITEM_SHOVEL
{
	//아이템이름, 팔수있는 벽
	ITEM_SHOVEL_NONE,
	ITEM_SHOVEL_BASIC,						//기본삽			(1)
	ITEM_SHOVEL_TITANIUM,					//티타늄삽		(~2)
	ITEM_SHOVEL_GLASS,						//유리삽			(~3)
	ITEM_SHOVEL_OBSIDIAN,					//흑요석삽		(코인배수에 따라서 1~3)
	ITEM_SHOVEL_BLOOD,						//피의삽			(1 / 2~3단계 깰경우 0.5씩 데미지 입음)
	ITEM_SHOVEL_CRYSTAL,					//크리스탈삽		(~3)
	ITEM_SHOVEL_GLASSSHARD,					//유리조각		(1)

	ITEM_SHOVEL_COUNT
};

enum ITEM_WEAPON
{
	//아이템이름,		데미지
	ITEM_WEAPON_NONE,
	//단검(공격범위 1X1, 데미지분류: 일반, 던지기 가능)

	ITEM_WEAPON_DAGGER_BASIC,				//기본단검			 (1)
	ITEM_WEAPON_DAGGER_TITANIUM,			//티타늄단검			 (2)
	ITEM_WEAPON_DAGGER_GLASS,				//유리단검			 (4, 깨지면 ITEM_WEAPON_GLASSSHARD)
	ITEM_WEAPON_DAGGER_OBSIDIAN,			//흑요석단검			 (코인배수에 따라서 1~3)
	ITEM_WEAPON_DAGGER_BLOOD,				//피의단검			 (1 / 10마리 죽일경우 0.5 회복, 플레이어의 체력이 0.5이면 데미지 999)
	ITEM_WEAPON_DAGGER_GOLD,				//황금단검			 (1 / 돈주운상태에서 데미지 999, 소지 시 금화 +1 획득)



	//브로드소드(공격범위 1X3, 데미지분류: 일반, 한번에 여러마리, 던지기 불가능)

	ITEM_WEAPON_BROADSWORD_BASIC,			//기본브로드소드		 (1)
	ITEM_WEAPON_BROADSWORD_TITANIUM,		//티타늄브로드소드	 (2)
	ITEM_WEAPON_BROADSWORD_GLASS,			//유리브로드소드		 (4, 깨지면 ITEM_WEAPON_GLASSSHARD)
	ITEM_WEAPON_BROADSWORD_OBSIDIAN,		//흑요석브로드소드	 (코인배수에 따라서 1~3)
	ITEM_WEAPON_BROADSWORD_BLOOD,			//피의브로드소드		 (1 / 10마리 죽일경우 0.5 회복, 플레이어의 체력이 0.5이면 데미지 999)
	ITEM_WEAPON_BROADSWORD_GOLD,			//황금브로드소드		 (1 / 돈주운상태에서 데미지 999, 소지 시 금화 +1 획득)


	//레이피어(공격범위 2X1, 데미지분류: 일반, 한번에 한마리만, 최대거리에서 공격시 2배에 대쉬, 던지기 불가능)

	ITEM_WEAPON_RAPIER_BASIC,				//기본레이피어		 (1)
	ITEM_WEAPON_RAPIER_TITANIUM,			//티타늄레이피어		 (2)
	ITEM_WEAPON_RAPIER_GLASS,				//유리레이피어		 (4, 깨지면 ITEM_WEAPON_GLASSSHARD)
	ITEM_WEAPON_RAPIER_OBSIDIAN,			//흑요석레이피어		 (코인배수에 따라서 1~3)
	ITEM_WEAPON_RAPIER_BLOOD,				//피의레이피어		 (1 / 10마리 죽일경우 0.5 회복, 플레이어의 체력이 0.5이면 데미지 999)
	ITEM_WEAPON_RAPIER_GOLD,				//황금레이피어		 (1 / 돈주운상태에서 데미지 999, 소지 시 금화 +1 획득)



	//창(공격범위 2x1, 데미지분류: 일반, 한번에 한마리만, 던지기 가능)

	ITEM_WEAPON_SPEAR_BASIC,				//기본창				 (1)
	ITEM_WEAPON_SPEAR_TITANIUM,				//티타늄창			 (2)
	ITEM_WEAPON_SPEAR_GLASS,				//유리창				 (4, 깨지면 ITEM_WEAPON_GLASSSHARD)
	ITEM_WEAPON_SPEAR_OBSIDIAN,				//흑요석창			 (코인배수에 따라서 1~3)
	ITEM_WEAPON_SPEAR_BLOOD,				//피의창				 (1 / 10마리 죽일경우 0.5 회복, 플레이어의 체력이 0.5이면 데미지 999)
	ITEM_WEAPON_SPEAR_GOLD,					//황금창				 (1 / 돈주운상태에서 데미지 999, 소지 시 금화 +1 획득)



	//롱소드(공격범위 2X1, 데미지분류: 일반, 한번에 여러마리가능, 던지기 불가능)

	ITEM_WEAPON_LONGSWORD_BASIC,			//기본롱소드			 (1)
	ITEM_WEAPON_LONGSWORD_TITANIUM,			//티타늄롱소드		 (2)
	ITEM_WEAPON_LONGSWORD_GLASS,			//유리롱소드			 (4, 깨지면 ITEM_WEAPON_GLASSSHARD)
	ITEM_WEAPON_LONGSWORD_OBSIDIAN,			//흑요석롱소드		 (코인배수에 따라서 1~3)
	ITEM_WEAPON_LONGSWORD_BLOOD,			//피의롱소드			 (1 / 10마리 죽일경우 0.5 회복, 플레이어의 체력이 0.5이면 데미지 999)
	ITEM_WEAPON_LONGSWORD_GOLD,				//황금롱소드			 (1 / 돈주운상태에서 데미지 999, 소지 시 금화 +1 획득)



	//채찍(공격범위 1X5, 데미지분류: 일반, 한번에 한마리, 던지기 불가능)

	ITEM_WEAPON_WHIP_BASIC,					//기본채찍			 (1)
	ITEM_WEAPON_WHIP_TITANIUM,				//티타늄채찍			 (2)
	ITEM_WEAPON_WHIP_GLASS,					//유리채찍			 (4, 깨지면 ITEM_WEAPON_GLASSSHARD)
	ITEM_WEAPON_WHIP_OBSIDIAN,				//흑요석채찍			 (코인배수에 따라서 1~3)
	ITEM_WEAPON_WHIP_BLOOD,					//피의채찍			 (1 / 10마리 죽일경우 0.5 회복, 플레이어의 체력이 0.5이면 데미지 999)
	ITEM_WEAPON_WHIP_GOLD,					//황금채찍			 (1 / 돈주운상태에서 데미지 999, 소지 시 금화 +1 획득)



	//활 (공격범위 3x1, 데미지분류: 일반, 한번에 한마리, 던지기 불가능)

	ITEM_WEAPON_BOW_BASIC,					//기본활				 (1)
	ITEM_WEAPON_BOW_TITANIUM,				//티타늄활			 (2)
	ITEM_WEAPON_BOW_GLASS,					//유리활				 (4, 깨지면 ITEM_WEAPON_GLASSSHARD)
	ITEM_WEAPON_BOW_OBSIDIAN,				//흑요석활			 (코인배수에 따라서 1~3)
	ITEM_WEAPON_BOW_BLOOD,					//피의활				 (1 / 10마리 죽일경우 0.5 회복, 플레이어의 체력이 0.5이면 데미지 999)
	ITEM_WEAPON_BOW_GOLD,					//황금활				 (1 / 돈주운상태에서 데미지 999, 소지 시 금화 +1 획득)



	//쇠뇌 (공격범위 4X1, 데미지분류: 관통, 한번에 한마리, 던지기 불가능, 재장전필요)

	ITEM_WEAPON_CROSSBOW_BASIC,				//기본쇠뇌			 (1)	
	ITEM_WEAPON_CROSSBOW_TITANIUM,			//티타늄쇠뇌			 (2),
	ITEM_WEAPON_CROSSBOW_GLASS,				//유리쇠뇌			 (4, 깨지면 ITEM_WEAPON_GLASSSHARD),
	ITEM_WEAPON_CROSSBOW_OBSIDIAN,			//흑요석쇠뇌			 (코인배수에 따라서 1~3),
	ITEM_WEAPON_CROSSBOW_BLOOD,				//피의쇠뇌			 (1 / 10마리 죽일경우 0.5 회복, 플레이어의 체력이 0.5이면 데미지 999)
	ITEM_WEAPON_CROSSBOW_GOLD,				//황금쇠뇌			 (1 / 돈주운상태에서 데미지 999, 소지 시 금화 +1 획득)



	//아홉꼬리고양이 (공격범위 2x3(플레이어위치제외), 데미지분류: 일반, 한번에 한마리, 던지기 불가능)

	ITEM_WEAPON_NINETAILS_BASIC,			//기본아홉꼬리고양이	 (1)
	ITEM_WEAPON_NINETAILS_TITANIUM,			//티타늄아홉꼬리고양이 (2),
	ITEM_WEAPON_NINETAILS_GLASS,			//유리아홉꼬리고양이	 (4, 깨지면 ITEM_WEAPON_GLASSSHARD),
	ITEM_WEAPON_NINETAILS_OBSIDIAN,			//흑요석아홉꼬리고양이 (코인배수에 따라서 1~3),
	ITEM_WEAPON_NINETAILS_BLOOD,			//피의아홉꼬리고양이	 (1 / 10마리 죽일경우 0.5 회복, 플레이어의 체력이 0.5이면 데미지 999)
	ITEM_WEAPON_NINETAILS_GOLD,				//황금아홉꼬리고양이	 (1 / 돈주운상태에서 데미지 999, 소지 시 금화 +1 획득)



	//철퇴 (공격범위 2X3, 데미지분류: 일반, 한번에 여러마리, 던지기 불가능, 공격시 몬스터 한칸씩 넉백)

	ITEM_WEAPON_FIAIL_BASIC,				//기본철퇴			 (1)	
	ITEM_WEAPON_FIAIL_TITANIUM,				//티타늄철퇴			 (2),
	ITEM_WEAPON_FIAIL_GLASS,				//유리철퇴			 (4, 깨지면 ITEM_WEAPON_GLASSSHARD),
	ITEM_WEAPON_FIAIL_OBSIDIAN,				//흑요석철퇴			 (코인배수에 따라서 1~3),
	ITEM_WEAPON_FIAIL_BLOOD,				//피의철퇴			 (1 / 10마리 죽일경우 0.5 회복, 플레이어의 체력이 0.5이면 데미지 999)
	ITEM_WEAPON_FIAIL_GOLD,					//황금철퇴			 (1 / 돈주운상태에서 데미지 999, 소지 시 금화 +1 획득)



	//나팔총 (공격범위 나팔모양, 데미지분류: 일반, 한번에 여러마리, 던지기 불가능, 재장전필요,	캐릭터 넉백)
	ITEM_WEAPON_BLUNDERBUSS,				//나팔총				 (2)



	//라이플 (공격범위 ∞x1, 데미지분류: 관통, 한번에 여러마리, 던지기 불가능, 재장전필요, 3발까지 장전필요, 캐릭터 넉백)
	ITEM_WEAPON_RIFLE,						//라이플				 (3)



	//유리조각 (공격범위 1x1, 데미지분류: 일반, 한번에 한마리, 던지기 가능, 모든 유리무기는 깨지면 유리조각으로)
	ITEM_WEAPON_GLASSSHARD,					//유리조각			 (1)



	//보석단검 (공격범위 1x1, 데미지분류: 일반, 한번에 한마리, 던지기 가능)
	ITEM_WEAPON_JEWELEDDAGGER,				//보석단검			 (5)



	//황금류트 (공격범위 이동할때마다 상하좌우, 데미지분류: 일반, 던지기 불가능, 몬스터 공격때마다 음표나옴)
	ITEM_WEAPON_GOLDENLUTE,					//황금류트			 (1)


	ITEM_WEAPON_COUNT
};

enum ITEM_TORCH
{
	//아이템이름,	    밝기
	ITEM_TORCH_NONE,
	ITEM_TORCH_BASIC,						//횃불			(1)
	ITEM_TORCH_BRIGHT,						//밝은 횃불		(2)
	ITEM_TORCH_LUMINIOUS,					//빛나는 횃불		(3)
	ITEM_TORCH_GLASS,						//유리 횃불		(3, 모든 적과 NPC가 보임, 데미지 입으면 파손됨)
	ITEM_TORCH_OBSIDIAN,					//흑요석 횃불		(코인 배수에 따라 1~3)
	ITEM_TORCH_INFERNAL,					//지옥불 횃불		(1, 횃불이 달린 벽 파괴할경우 지옥불 시전)
	ITEM_TORCH_FORESIGHT,					//예지의 횃불		(1, 함정볼 수 있음)


	ITEM_TORCH_COUNT
};

enum ITEM_ARMOR
{
	//아이템이름,		방어력
	ITEM_ARMOR_NONE,
	ITEM_ARMOR_LEATHER,						//가죽갑옷			 (0.5)
	ITEM_ARMOR_CHAINMAIL,					//사슬갑옷			 (1)
	ITEM_ARMOR_PLATEMAIL,					//판금갑옷			 (1.5)
	ITEM_ARMOR_HEAVYPLATE,					//판금중갑			 (2, 나팔총, 라이플의 반동면역, 화살표함정면역)
	ITEM_ARMOR_KARADE,						//가라데도복			 ((몬스터 공격력 - 방어력) X 2, 공격력 -> 무기공격력 X2 + 추가 데미지 보너스)
	ITEM_ARMOR_OBSIDIAN,					//흑요석갑옷			 (0.5)
	ITEM_ARMOR_OBSIDIAN_X2,					//흑요석갑옷			 (1.0 / 키애니용, 프레임이미지에서는 위에꺼만 사용)
	ITEM_ARMOR_OBSIDIAN_X3,					//흑요석갑옷			 (1.5 / 키애니용)
	ITEM_ARMOR_GLASS,						//유리갑옷			 (데미지 무효화 시키나 파손)

	ITEM_ARMOR_COUNT
};

enum ITEM_HEADWEAR
{
	//아이템이름,		특징
	ITEM_HEADWEAR_NONE,

	ITEM_HEADWEAR_HELMAT,					//투구				(방어력 0.5)
	ITEM_HEADWEAR_BLASTHELM,				//방폭투구			(폭탄 3개 주고 폭발데미지 면역, 즉시폭발)
	ITEM_HEADWEAR_TELEPORT,					//순간이동왕관		(맞을경우 데미지 무효화, 상인한테 이동)

	ITEM_HEADWEAR_COUNT
};

enum ITEM_FOOTWEAR
{
	//아이템이름,		특징
	ITEM_FOOTWEAR_NONE,
	ITEM_FOOTWEAR_BALLET,					//발레슈즈			(맞거나 함정에 빠지지 않는이상 코인배수 안떨어짐)
	ITEM_FOOTWEAR_WINGED,					//날개장화			(날아다닐 수 있음, 함정사용불가)
	ITEM_FOOTWEAR_LEAD,						//징박힌장화			(총 반동, 함정 등 위치변화 면역)
	ITEM_FOOTWEAR_HARGREAVES,				//하그레이브즈		(방어력 0.5)
	ITEM_FOOTWEAR_STRENGTH,					//힘의장화			(무기공격력 1증가)

	ITEM_FOOTWEAR_COUNT
};

enum ITEM_CONSUMABLE
{
	//아이템이름,		특징
	ITEM_CONSUMABLE_NONE,
	ITEM_CONSUMABLE_APPLE,					//사과				(체력 1회복)
	ITEM_CONSUMABLE_CHEESE,					//치즈				(체력 2회복)
	ITEM_CONSUMABLE_DRUMSTICK,				//닭다리				(체력 3회복)
	ITEM_CONSUMABLE_HAM,					//햄					(체력 4회복)
	ITEM_CONSUMABLE_WARDRUM,				//전쟁의북			(제자리에서 사용, 1~4 두드리면 데미지 2배, 5번 두드리면 데미지 3배)

	ITEM_CONSUMABLE_COUNT
};

enum ITEM_BOMB
{
	ITEM_BOMB_NONE,
	ITEM_BOMB_X1,				//폭탄				(3박자 후 3X3범위 공격, 몬스터 4데미지, 캐릭터 2데미지, 1~3단계 벽, 상점벽 파괴, 함정제거, 물타일 제거, 아이템, 골드 제거)
	ITEM_BOMB_X3,				//폭탄X3				(3박자 후 3X3범위 공격, 몬스터 4데미지, 캐릭터 2데미지, 1~3단계 벽, 상점벽 파괴, 함정제거, 물타일 제거, 아이템, 골드 제거)

	ITEM_BOMB_COUNT
};

enum ITEM_HEART
{
	//아이템이름,		특징
	ITEM_HEART_NONE,
	ITEM_HEART_FILLED,						//+1하트보관함		최대하트 1증가 + 채워진상태
	ITEM_HEART_DOUBLE_FILLED,				//+2하트보관함		최대하트 2증가 + 채워진상태
	ITEM_HEART_EMPTY,						//+1빈하트보관함		최대하트 1증가 + 빈상태
	ITEM_HEART_DOUBLE_EMPTY,				//+2빈하트보관함		최대하트 2증가 + 빈상태


	ITEM_HEART_COUNT

};

enum ITEM_COIN
{
	ITEM_COIN_NONE,

	ITEM_COIN_1,
	ITEM_COIN_2,
	ITEM_COIN_3,
	ITEM_COIN_4,
	ITEM_COIN_5,
	ITEM_COIN_6,
	ITEM_COIN_7,
	ITEM_COIN_8,
	ITEM_COIN_9,
	ITEM_COIN_10,
	ITEM_COIN_25,
	ITEM_COIN_35,
	ITEM_COIN_50,

	ITEM_COIN_COUNT
};
/*
	스트링배열!
*/

static string ARMOR_NAME[ITEM_ARMOR_COUNT] = { "armor_none"
											 , "armor_leather",  "armor_chainmail", "armor_platemail", "armor_heavyplate"
											 , "armor_karade" , "armor_obsidian", "armor_obsidian_X2", "armor_obsidian_X3", "armor_glass" };

static string SHOVEL_NAME[ITEM_SHOVEL_COUNT] = { "shove_none", "shovel_basic", "shovel_titanium", "shovel_glass","shovel_obsidian", "shovel_blood", "shovle_crystal", "shovel_glass_shard" };

static string TORCH_NAME[ITEM_TORCH_COUNT] = { "torch_none", "torch_basic", "torch_bright", "torch_luminious", "torch_glass", "torch_obsidian", "torch_infernal", "torch_foresight" };

static string WEAPON_NAME[ITEM_WEAPON_COUNT] = { "weapon_none"
												,"weapon_dagger_basic",		"weapon_dagger_titanium",		"weapon_dagger_glass",		"weapon_dagger_obsidian",		"weapon_dagger_blood",		"weapon_dagger_gold"
												,"weapon_broadsword_basic", "weapon_broadsword_titanium",	"weapon_broadsword_glass",	"weapon_broadsword_obsidian",	"weapon_broadsword_blood",	"weapon_broadsword_gold"
												,"weapon_rapier_basic",		"weapon_rapier_titanium",		"weapon_rapier_glass",		"weapon_rapier_obsidian",		"weapon_rapier_blood",		"weapon_rapier_gold"
												,"weapon_spear_basic",		"weapon_spear_titanium",		"weapon_spear_glass",		"weapon_spear_obsidian",		"weapon_spear_blood",		"weapon_spear_gold"
												,"weapon_longsword_basic",	"weapon_longsword_titanium",	"weapon_longsword_glass",	"weapon_longsword_obsidian",	"weapon_longsword_blood",	"weapon_longsword_gold"
												,"weapon_whip_basic",		"weapon_whip_titanium",			"weapon_whip_glass",		"weapon_whip_obsidian",			"weapon_whip_blood",		"weapon_whip_gold"
												,"weapon_bow_basic",		"weapon_bow_titanium",			"weapon_bow_glass",			"weapon_bow_obsidian",			"weapon_bow_blood",			"weapon_bow_gold"
												,"weapon_crossbow_basic",	"weapon_crossbow_titanium",		"weapon_crossbow_glass",	"weapon_crossbow_obsidian",		"weapon_crossbow_blood",	"weapon_crossbow_gold"
												,"weapon_ninetails_basic",	"weapon_ninetails_titanium",	"weapon_ninetails_glass",	"weapon_ninetails_obsidian",	"weapon_ninetails_blood",	"weapon_ninetails_gold"
												,"weapon_fiail_basic",		"weapon_fiail_titanium",		"weapon_fiail_glass",		"weapon_fiail_obsidian",		"weapon_fiail_blood",		"weapon_fiail_gold"
												,"weapon_blunderbuss",		"weapon_rifle",					"weapon_glass_shard",		"weapon_jeweled_dagger",		"weapon_golden_lute" };

static string HEADWEAR_NAME[ITEM_HEADWEAR_COUNT] = { "headwear_none", "headwear_helmat", "headwear_blasthelm", "headwear_teleport" };

static string FOOTWEAR_NAME[ITEM_FOOTWEAR_COUNT] = { "footwear_none", "footwear_ballet", "footwear_winged", "footwear_lead", "footwear_hargreaves", "footwear_strength" };

static string CONSUMABLE_NAME[ITEM_CONSUMABLE_COUNT] = { "consumable_none", "consumable_apple", "consumable_cheese", "consumable_drumstick", "consumable_ham", "consumable_wardrum" };

static string HEART_NAME[ITEM_HEART_COUNT] = { "heart_none", "heart_filled", "heart_double_filled", "heart_empty", "heart_double_empty" };

static string COIN_NAME[ITEM_COIN_COUNT] = { "coin_none", "coin_1", "coin_2", "coin_3", "coin_4", "coin_5", "coin_6", "coin_7", "coin_8", "coin_9", "coin_10", "coin_25", "coin_35", "coin_50" };

static string BOMB_NAME[ITEM_BOMB_COUNT] = { "bomb_none", "bomb_X1", "bomb_X3" };




struct tagInvenInfo
{
	ITEM_SHOVEL		shovel;
	ITEM_WEAPON		weapon;
	ITEM_ARMOR		armor;
	ITEM_HEADWEAR	head;
	ITEM_FOOTWEAR	foot;
	ITEM_TORCH		torch;
	ITEM_CONSUMABLE	item;
	ITEM_BOMB		bomb;
};