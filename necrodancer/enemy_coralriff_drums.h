#pragma once
#include "enemy.h"
class enemy_coralriff_drums : public enemy
{
private:
	int respawnX_left = -1;
	int respawnY_left = -1;

	int respawnX_right = 1;
	int respawnY_right = 1;

public:
	enemy_coralriff_drums();
	~enemy_coralriff_drums();

	HRESULT init(string imgName, int idxX, int idxY);
	void release();
	void update();
	void render();

	void aniSetUp();

	void aniPlay_Stand();

	void hitEnemy(int damage);
};

