#pragma once
#include "enemy.h"
class enemy_coralriff_horns : public enemy
{
private:
	int respawnX_left = -1;
	int respawnY_left = 1;

	int respawnX_right = 1;
	int respawnY_right = -1;



public:
	enemy_coralriff_horns();
	~enemy_coralriff_horns();

	HRESULT init(string imgName, int idxX, int idxY);
	void release();
	void update();
	void render();

	void aniSetUp();

	void aniPlay_Stand();

	void hitEnemy(int damage);
};

