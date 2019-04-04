#pragma once
#include "enemy.h"
class enemy_skeleton_mage : public enemy
{
public:
	enemy_skeleton_mage();
	~enemy_skeleton_mage();

	HRESULT init(string imgName, int idxX, int idxY);
	void release();
	void update();
	void render();

	void aniSetUp();

	void aniPlay_Attack();
	void aniPlay_Stand();

	bool windMagic();

};

