#pragma once


/*
					������ �������̛�

		1. ������ ���� ����
			1) �⺻
			2) ƼŸ��
			3) ����
			4) ��伮
			5) ��
			6) ũ����Ż
			7) Ȳ��				(������)

		2. ����
			���� ���ʺ��� ���� ����� ������ ȹ���ߴٸ� ������ ���� ����� ������ �������.

		3. ��伮�� �ǽð����� ���� ��� �޾ƿ;��Ѵ�.


*/



enum ITEM_TYPE
{
	ITEM_TYPE_SHOVEL,					//��
	ITEM_TYPE_WEAPON,					//����
	ITEM_TYPE_TORCH,					//ȶ��
	ITEM_TYPE_ARMOR,					//����
	ITEM_TYPE_HEADWEAR,					//����
	ITEM_TYPE_FOOTWEAR,					//�Ź�
	ITEM_TYPE_CONSUMABLE,				//�Ҹ�ǰ
	ITEM_TYPE_HEART,					//��Ʈ
	ITEM_TYPE_COIN,
	ITEM_TYPE_BOMB,

	ITEM_TYPE_NONE,
	ITEM_TYPE_COUNT = ITEM_TYPE_NONE
};

enum ITEM_SHOVEL
{
	//�������̸�, �ȼ��ִ� ��
	ITEM_SHOVEL_NONE,
	ITEM_SHOVEL_BASIC,						//�⺻��			(1)
	ITEM_SHOVEL_TITANIUM,					//ƼŸ����		(~2)
	ITEM_SHOVEL_GLASS,						//������			(~3)
	ITEM_SHOVEL_OBSIDIAN,					//��伮��		(���ι���� ���� 1~3)
	ITEM_SHOVEL_BLOOD,						//���ǻ�			(1 / 2~3�ܰ� ����� 0.5�� ������ ����)
	ITEM_SHOVEL_CRYSTAL,					//ũ����Ż��		(~3)
	ITEM_SHOVEL_GLASSSHARD,					//��������		(1)

	ITEM_SHOVEL_COUNT
};

enum ITEM_WEAPON
{
	//�������̸�,		������
	ITEM_WEAPON_NONE,
	//�ܰ�(���ݹ��� 1X1, �������з�: �Ϲ�, ������ ����)

	ITEM_WEAPON_DAGGER_BASIC,				//�⺻�ܰ�			 (1)
	ITEM_WEAPON_DAGGER_TITANIUM,			//ƼŸ���ܰ�			 (2)
	ITEM_WEAPON_DAGGER_GLASS,				//�����ܰ�			 (4, ������ ITEM_WEAPON_GLASSSHARD)
	ITEM_WEAPON_DAGGER_OBSIDIAN,			//��伮�ܰ�			 (���ι���� ���� 1~3)
	ITEM_WEAPON_DAGGER_BLOOD,				//���Ǵܰ�			 (1 / 10���� ���ϰ�� 0.5 ȸ��, �÷��̾��� ü���� 0.5�̸� ������ 999)
	ITEM_WEAPON_DAGGER_GOLD,				//Ȳ�ݴܰ�			 (1 / ���ֿ���¿��� ������ 999, ���� �� ��ȭ +1 ȹ��)



	//��ε�ҵ�(���ݹ��� 1X3, �������з�: �Ϲ�, �ѹ��� ��������, ������ �Ұ���)

	ITEM_WEAPON_BROADSWORD_BASIC,			//�⺻��ε�ҵ�		 (1)
	ITEM_WEAPON_BROADSWORD_TITANIUM,		//ƼŸ����ε�ҵ�	 (2)
	ITEM_WEAPON_BROADSWORD_GLASS,			//������ε�ҵ�		 (4, ������ ITEM_WEAPON_GLASSSHARD)
	ITEM_WEAPON_BROADSWORD_OBSIDIAN,		//��伮��ε�ҵ�	 (���ι���� ���� 1~3)
	ITEM_WEAPON_BROADSWORD_BLOOD,			//���Ǻ�ε�ҵ�		 (1 / 10���� ���ϰ�� 0.5 ȸ��, �÷��̾��� ü���� 0.5�̸� ������ 999)
	ITEM_WEAPON_BROADSWORD_GOLD,			//Ȳ�ݺ�ε�ҵ�		 (1 / ���ֿ���¿��� ������ 999, ���� �� ��ȭ +1 ȹ��)


	//�����Ǿ�(���ݹ��� 2X1, �������з�: �Ϲ�, �ѹ��� �Ѹ�����, �ִ�Ÿ����� ���ݽ� 2�迡 �뽬, ������ �Ұ���)

	ITEM_WEAPON_RAPIER_BASIC,				//�⺻�����Ǿ�		 (1)
	ITEM_WEAPON_RAPIER_TITANIUM,			//ƼŸ�������Ǿ�		 (2)
	ITEM_WEAPON_RAPIER_GLASS,				//���������Ǿ�		 (4, ������ ITEM_WEAPON_GLASSSHARD)
	ITEM_WEAPON_RAPIER_OBSIDIAN,			//��伮�����Ǿ�		 (���ι���� ���� 1~3)
	ITEM_WEAPON_RAPIER_BLOOD,				//���Ƿ����Ǿ�		 (1 / 10���� ���ϰ�� 0.5 ȸ��, �÷��̾��� ü���� 0.5�̸� ������ 999)
	ITEM_WEAPON_RAPIER_GOLD,				//Ȳ�ݷ����Ǿ�		 (1 / ���ֿ���¿��� ������ 999, ���� �� ��ȭ +1 ȹ��)



	//â(���ݹ��� 2x1, �������з�: �Ϲ�, �ѹ��� �Ѹ�����, ������ ����)

	ITEM_WEAPON_SPEAR_BASIC,				//�⺻â				 (1)
	ITEM_WEAPON_SPEAR_TITANIUM,				//ƼŸ��â			 (2)
	ITEM_WEAPON_SPEAR_GLASS,				//����â				 (4, ������ ITEM_WEAPON_GLASSSHARD)
	ITEM_WEAPON_SPEAR_OBSIDIAN,				//��伮â			 (���ι���� ���� 1~3)
	ITEM_WEAPON_SPEAR_BLOOD,				//����â				 (1 / 10���� ���ϰ�� 0.5 ȸ��, �÷��̾��� ü���� 0.5�̸� ������ 999)
	ITEM_WEAPON_SPEAR_GOLD,					//Ȳ��â				 (1 / ���ֿ���¿��� ������ 999, ���� �� ��ȭ +1 ȹ��)



	//�ռҵ�(���ݹ��� 2X1, �������з�: �Ϲ�, �ѹ��� ������������, ������ �Ұ���)

	ITEM_WEAPON_LONGSWORD_BASIC,			//�⺻�ռҵ�			 (1)
	ITEM_WEAPON_LONGSWORD_TITANIUM,			//ƼŸ���ռҵ�		 (2)
	ITEM_WEAPON_LONGSWORD_GLASS,			//�����ռҵ�			 (4, ������ ITEM_WEAPON_GLASSSHARD)
	ITEM_WEAPON_LONGSWORD_OBSIDIAN,			//��伮�ռҵ�		 (���ι���� ���� 1~3)
	ITEM_WEAPON_LONGSWORD_BLOOD,			//���Ƿռҵ�			 (1 / 10���� ���ϰ�� 0.5 ȸ��, �÷��̾��� ü���� 0.5�̸� ������ 999)
	ITEM_WEAPON_LONGSWORD_GOLD,				//Ȳ�ݷռҵ�			 (1 / ���ֿ���¿��� ������ 999, ���� �� ��ȭ +1 ȹ��)



	//ä��(���ݹ��� 1X5, �������з�: �Ϲ�, �ѹ��� �Ѹ���, ������ �Ұ���)

	ITEM_WEAPON_WHIP_BASIC,					//�⺻ä��			 (1)
	ITEM_WEAPON_WHIP_TITANIUM,				//ƼŸ��ä��			 (2)
	ITEM_WEAPON_WHIP_GLASS,					//����ä��			 (4, ������ ITEM_WEAPON_GLASSSHARD)
	ITEM_WEAPON_WHIP_OBSIDIAN,				//��伮ä��			 (���ι���� ���� 1~3)
	ITEM_WEAPON_WHIP_BLOOD,					//����ä��			 (1 / 10���� ���ϰ�� 0.5 ȸ��, �÷��̾��� ü���� 0.5�̸� ������ 999)
	ITEM_WEAPON_WHIP_GOLD,					//Ȳ��ä��			 (1 / ���ֿ���¿��� ������ 999, ���� �� ��ȭ +1 ȹ��)



	//Ȱ (���ݹ��� 3x1, �������з�: �Ϲ�, �ѹ��� �Ѹ���, ������ �Ұ���)

	ITEM_WEAPON_BOW_BASIC,					//�⺻Ȱ				 (1)
	ITEM_WEAPON_BOW_TITANIUM,				//ƼŸ��Ȱ			 (2)
	ITEM_WEAPON_BOW_GLASS,					//����Ȱ				 (4, ������ ITEM_WEAPON_GLASSSHARD)
	ITEM_WEAPON_BOW_OBSIDIAN,				//��伮Ȱ			 (���ι���� ���� 1~3)
	ITEM_WEAPON_BOW_BLOOD,					//����Ȱ				 (1 / 10���� ���ϰ�� 0.5 ȸ��, �÷��̾��� ü���� 0.5�̸� ������ 999)
	ITEM_WEAPON_BOW_GOLD,					//Ȳ��Ȱ				 (1 / ���ֿ���¿��� ������ 999, ���� �� ��ȭ +1 ȹ��)



	//��� (���ݹ��� 4X1, �������з�: ����, �ѹ��� �Ѹ���, ������ �Ұ���, �������ʿ�)

	ITEM_WEAPON_CROSSBOW_BASIC,				//�⺻���			 (1)	
	ITEM_WEAPON_CROSSBOW_TITANIUM,			//ƼŸ�����			 (2),
	ITEM_WEAPON_CROSSBOW_GLASS,				//�������			 (4, ������ ITEM_WEAPON_GLASSSHARD),
	ITEM_WEAPON_CROSSBOW_OBSIDIAN,			//��伮���			 (���ι���� ���� 1~3),
	ITEM_WEAPON_CROSSBOW_BLOOD,				//���Ǽ��			 (1 / 10���� ���ϰ�� 0.5 ȸ��, �÷��̾��� ü���� 0.5�̸� ������ 999)
	ITEM_WEAPON_CROSSBOW_GOLD,				//Ȳ�ݼ��			 (1 / ���ֿ���¿��� ������ 999, ���� �� ��ȭ +1 ȹ��)



	//��ȩ��������� (���ݹ��� 2x3(�÷��̾���ġ����), �������з�: �Ϲ�, �ѹ��� �Ѹ���, ������ �Ұ���)

	ITEM_WEAPON_NINETAILS_BASIC,			//�⺻��ȩ���������	 (1)
	ITEM_WEAPON_NINETAILS_TITANIUM,			//ƼŸ����ȩ��������� (2),
	ITEM_WEAPON_NINETAILS_GLASS,			//������ȩ���������	 (4, ������ ITEM_WEAPON_GLASSSHARD),
	ITEM_WEAPON_NINETAILS_OBSIDIAN,			//��伮��ȩ��������� (���ι���� ���� 1~3),
	ITEM_WEAPON_NINETAILS_BLOOD,			//���Ǿ�ȩ���������	 (1 / 10���� ���ϰ�� 0.5 ȸ��, �÷��̾��� ü���� 0.5�̸� ������ 999)
	ITEM_WEAPON_NINETAILS_GOLD,				//Ȳ�ݾ�ȩ���������	 (1 / ���ֿ���¿��� ������ 999, ���� �� ��ȭ +1 ȹ��)



	//ö�� (���ݹ��� 2X3, �������з�: �Ϲ�, �ѹ��� ��������, ������ �Ұ���, ���ݽ� ���� ��ĭ�� �˹�)

	ITEM_WEAPON_FIAIL_BASIC,				//�⺻ö��			 (1)	
	ITEM_WEAPON_FIAIL_TITANIUM,				//ƼŸ��ö��			 (2),
	ITEM_WEAPON_FIAIL_GLASS,				//����ö��			 (4, ������ ITEM_WEAPON_GLASSSHARD),
	ITEM_WEAPON_FIAIL_OBSIDIAN,				//��伮ö��			 (���ι���� ���� 1~3),
	ITEM_WEAPON_FIAIL_BLOOD,				//����ö��			 (1 / 10���� ���ϰ�� 0.5 ȸ��, �÷��̾��� ü���� 0.5�̸� ������ 999)
	ITEM_WEAPON_FIAIL_GOLD,					//Ȳ��ö��			 (1 / ���ֿ���¿��� ������ 999, ���� �� ��ȭ +1 ȹ��)



	//������ (���ݹ��� ���ȸ��, �������з�: �Ϲ�, �ѹ��� ��������, ������ �Ұ���, �������ʿ�,	ĳ���� �˹�)
	ITEM_WEAPON_BLUNDERBUSS,				//������				 (2)



	//������ (���ݹ��� ��x1, �������з�: ����, �ѹ��� ��������, ������ �Ұ���, �������ʿ�, 3�߱��� �����ʿ�, ĳ���� �˹�)
	ITEM_WEAPON_RIFLE,						//������				 (3)



	//�������� (���ݹ��� 1x1, �������з�: �Ϲ�, �ѹ��� �Ѹ���, ������ ����, ��� ��������� ������ ������������)
	ITEM_WEAPON_GLASSSHARD,					//��������			 (1)



	//�����ܰ� (���ݹ��� 1x1, �������з�: �Ϲ�, �ѹ��� �Ѹ���, ������ ����)
	ITEM_WEAPON_JEWELEDDAGGER,				//�����ܰ�			 (5)



	//Ȳ�ݷ�Ʈ (���ݹ��� �̵��Ҷ����� �����¿�, �������з�: �Ϲ�, ������ �Ұ���, ���� ���ݶ����� ��ǥ����)
	ITEM_WEAPON_GOLDENLUTE,					//Ȳ�ݷ�Ʈ			 (1)


	ITEM_WEAPON_COUNT
};

enum ITEM_TORCH
{
	//�������̸�,	    ���
	ITEM_TORCH_NONE,
	ITEM_TORCH_BASIC,						//ȶ��			(1)
	ITEM_TORCH_BRIGHT,						//���� ȶ��		(2)
	ITEM_TORCH_LUMINIOUS,					//������ ȶ��		(3)
	ITEM_TORCH_GLASS,						//���� ȶ��		(3, ��� ���� NPC�� ����, ������ ������ �ļյ�)
	ITEM_TORCH_OBSIDIAN,					//��伮 ȶ��		(���� ����� ���� 1~3)
	ITEM_TORCH_INFERNAL,					//������ ȶ��		(1, ȶ���� �޸� �� �ı��Ұ�� ������ ����)
	ITEM_TORCH_FORESIGHT,					//������ ȶ��		(1, ������ �� ����)


	ITEM_TORCH_COUNT
};

enum ITEM_ARMOR
{
	//�������̸�,		����
	ITEM_ARMOR_NONE,
	ITEM_ARMOR_LEATHER,						//���װ���			 (0.5)
	ITEM_ARMOR_CHAINMAIL,					//�罽����			 (1)
	ITEM_ARMOR_PLATEMAIL,					//�Ǳݰ���			 (1.5)
	ITEM_ARMOR_HEAVYPLATE,					//�Ǳ��߰�			 (2, ������, �������� �ݵ��鿪, ȭ��ǥ�����鿪)
	ITEM_ARMOR_KARADE,						//���󵥵���			 ((���� ���ݷ� - ����) X 2, ���ݷ� -> ������ݷ� X2 + �߰� ������ ���ʽ�)
	ITEM_ARMOR_OBSIDIAN,					//��伮����			 (0.5)
	ITEM_ARMOR_OBSIDIAN_X2,					//��伮����			 (1.0 / Ű�ִϿ�, �������̹��������� �������� ���)
	ITEM_ARMOR_OBSIDIAN_X3,					//��伮����			 (1.5 / Ű�ִϿ�)
	ITEM_ARMOR_GLASS,						//��������			 (������ ��ȿȭ ��Ű�� �ļ�)

	ITEM_ARMOR_COUNT
};

enum ITEM_HEADWEAR
{
	//�������̸�,		Ư¡
	ITEM_HEADWEAR_NONE,

	ITEM_HEADWEAR_HELMAT,					//����				(���� 0.5)
	ITEM_HEADWEAR_BLASTHELM,				//��������			(��ź 3�� �ְ� ���ߵ����� �鿪, �������)
	ITEM_HEADWEAR_TELEPORT,					//�����̵��հ�		(������� ������ ��ȿȭ, �������� �̵�)

	ITEM_HEADWEAR_COUNT
};

enum ITEM_FOOTWEAR
{
	//�������̸�,		Ư¡
	ITEM_FOOTWEAR_NONE,
	ITEM_FOOTWEAR_BALLET,					//�߷�����			(�°ų� ������ ������ �ʴ��̻� ���ι�� �ȶ�����)
	ITEM_FOOTWEAR_WINGED,					//������ȭ			(���ƴٴ� �� ����, �������Ұ�)
	ITEM_FOOTWEAR_LEAD,						//¡������ȭ			(�� �ݵ�, ���� �� ��ġ��ȭ �鿪)
	ITEM_FOOTWEAR_HARGREAVES,				//�ϱ׷��̺���		(���� 0.5)
	ITEM_FOOTWEAR_STRENGTH,					//������ȭ			(������ݷ� 1����)

	ITEM_FOOTWEAR_COUNT
};

enum ITEM_CONSUMABLE
{
	//�������̸�,		Ư¡
	ITEM_CONSUMABLE_NONE,
	ITEM_CONSUMABLE_APPLE,					//���				(ü�� 1ȸ��)
	ITEM_CONSUMABLE_CHEESE,					//ġ��				(ü�� 2ȸ��)
	ITEM_CONSUMABLE_DRUMSTICK,				//�ߴٸ�				(ü�� 3ȸ��)
	ITEM_CONSUMABLE_HAM,					//��					(ü�� 4ȸ��)
	ITEM_CONSUMABLE_WARDRUM,				//�����Ǻ�			(���ڸ����� ���, 1~4 �ε帮�� ������ 2��, 5�� �ε帮�� ������ 3��)

	ITEM_CONSUMABLE_COUNT
};

enum ITEM_BOMB
{
	ITEM_BOMB_NONE,
	ITEM_BOMB_X1,				//��ź				(3���� �� 3X3���� ����, ���� 4������, ĳ���� 2������, 1~3�ܰ� ��, ������ �ı�, ��������, ��Ÿ�� ����, ������, ��� ����)
	ITEM_BOMB_X3,				//��źX3				(3���� �� 3X3���� ����, ���� 4������, ĳ���� 2������, 1~3�ܰ� ��, ������ �ı�, ��������, ��Ÿ�� ����, ������, ��� ����)

	ITEM_BOMB_COUNT
};

enum ITEM_HEART
{
	//�������̸�,		Ư¡
	ITEM_HEART_NONE,
	ITEM_HEART_FILLED,						//+1��Ʈ������		�ִ���Ʈ 1���� + ä��������
	ITEM_HEART_DOUBLE_FILLED,				//+2��Ʈ������		�ִ���Ʈ 2���� + ä��������
	ITEM_HEART_EMPTY,						//+1����Ʈ������		�ִ���Ʈ 1���� + �����
	ITEM_HEART_DOUBLE_EMPTY,				//+2����Ʈ������		�ִ���Ʈ 2���� + �����


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
	��Ʈ���迭!
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

// ==============================================
//					 ��     ��
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
	IMAGE_NAME_WALL_11,
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
	IMAGE_NAME_TRAP_BOUNCE,
	IMAGE_NAME_TRAP_SLOWDOWN,
	IMAGE_NAME_TRAP_SPEEDUP,
	IMAGE_NAME_TRAP_SPIKE,
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

enum OBJECT_TYPE
{
	OBJECT_TYPE_FLOOR,
	OBJECT_TYPE_WALL,
	OBJECT_TYPE_ENEMY,
	OBJECT_TYPE_TRAP,
	OBJECT_TYPE_ITEM,
	OBJECT_TYPE_ETC,
	OBJECT_TYPE_PLAYER,

	OBJECT_TYPE_NONE,

	OBJECT_TYPE_COUNT = OBJECT_TYPE_NONE
};

static string IMAGE_NAME[IMAGE_NAME_COUNT] = { "none","floor_01","floor_02","floor_03","floor_04","floor_05","stairs_01","stairs_02",
											"wall_01","wall_02","wall_03","wall_04","wall_05","wall_06","wall_07","wall_08","wall_09","wall_10","wall_11",
											"door_01","door_02","enemy_skeleton","enemy_skeleton_yellow","enemy_skeleton_black",
											"enemy_skeleton_mage_white","enemy_skeleton_mage_yellow","enemy_skeleton_mage_black",
											"enemy_armadillo","enemy_slime_green","enemy_slime_blue","enemy_zombie",
											"enemy_bat","enemy_bat_red","enemy_clone","enemy_bat_miniboss","enemy_banshee",
											"enemy_dragon_green","enemy_minotaur","enemy_coralriff_drums","enemy_coralriff_head","enemy_coralriff_horns","enemy_coralriff_keytar",
											"enemy_coralriff_strings","enemy_shopkeeper",
											"chest_01" ,"trap_bounce","trap_slowdown","trap_speedup","trap_spike","shrine_01","shrine_02" ,"shrine_03","shrine_04","shrine_05",
											"shrine_06","torch_01"
};


struct tagTilePack
{
	int	frameX;
	int frameY;
	int appValue;
	int idxX;
	int idxY;
	int pos_X;
	int pos_Y;

	int imgName;
	int itemType;
	int itemSubType;


	float posX;
	float posY;

	OBJECT_TYPE objType;
	D2D1_RECT_F rc;

	bool isTorch;
};

struct tagPack
{
	int floorName;
	int floorPosX;
	int floorPosY;
	OBJECT_TYPE type_floor;

	int objName;
	int objPosX;
	int objPosY;
	OBJECT_TYPE type_obj;
	ITEM_TYPE itemType;
	UINT imgKey;


	bool isTorch = false;

	//�ؿ� �ִ� �͵��� ù �ʱ�ȭ�� 0 / none���� �ʱ�ȭ
	UINT	terrain_frameX;										//Ÿ�������� X
	UINT	terrain_frameY;										//Ÿ�������� Y
	UINT	object_frameX;										//������Ʈ������ X
	UINT	object_frameY;										//������Ʈ������ Y

	tagTilePack	floor;
	tagTilePack wall;
	tagTilePack objETC;
	tagTilePack trap;
	tagTilePack item;
	tagTilePack enemy;
	tagTilePack player;

	

};