#pragma once
#include "enemy.h"
class enemy_coralriff_strings : public enemy
{
private:
	int respawnX_left = 0;
	int respawnY_left = -1;

	int respawnX_right = 0;
	int respawnY_right = 1;

public:
	enemy_coralriff_strings();
	~enemy_coralriff_strings();

	HRESULT init(string imgName, int idxX, int idxY);
	void release();
	void update();
	void render();

	void aniSetUp();

	void aniPlay_Stand();

	void hitEnemy(int damage);
};

