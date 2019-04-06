#pragma once
#include "enemy.h"
class enemy_banshee : public enemy
{
private:


public:
	enemy_banshee();
	~enemy_banshee();

	HRESULT init(string imgName, int idxX, int idxY);
	void release();
	void update();
	void render();

	void aniSetUp();

	void aniPlay_Stand();
	void aniPlay_Attack();

	void hitEnemy(int damage);
};

