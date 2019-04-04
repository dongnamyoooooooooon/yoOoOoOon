#pragma once
#include "enemy.h"
class enemy_skeleton_mage_yellow : public enemy
{
private:


public:
	enemy_skeleton_mage_yellow();
	~enemy_skeleton_mage_yellow();


	HRESULT init(string imgName, int idxX, int idxY);
	void release();
	void update();
	void render();

	void aniSetUp();

	void aniPlay_Attack();
	void aniPlay_Stand();

	bool windMagic();
};

