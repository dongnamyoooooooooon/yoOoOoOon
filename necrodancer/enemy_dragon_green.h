#pragma once
#include "enemy.h"
class enemy_dragon_green : public enemy
{
public:
	enemy_dragon_green();
	~enemy_dragon_green();

	HRESULT init(string imgName, int idxX, int idxY);
	void release();
	void update();
	void render();

	void aniSetUp();

	void aniPlay_Stand();

	void jumpMoveEnemy();
};

