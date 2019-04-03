#pragma once
#include "enemy.h"
class enemy_slime_green : public enemy
{
public:
	enemy_slime_green();
	~enemy_slime_green();

	HRESULT init(string imgName, int idxX, int idxY);
	void release();
	void update();
	void render();

	void aniSetUp();

	void aniPlay_Stand();
};

