#pragma once
#include "enemy.h"
#include "enemyInfomation.h"
class enemy_slime_blue : public enemy
{
private:
	string _enemyAni;

public:
	enemy_slime_blue();
	~enemy_slime_blue();

	HRESULT init(string imgName, int idxX, int idxY);
	void release();
	void update();
	void render();

	void aniSetUp();

	void aniPlay_Attack();
	void aniPlay_Stand();
};

