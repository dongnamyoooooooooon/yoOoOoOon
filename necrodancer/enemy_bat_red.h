#pragma once
#include "enemy.h"
class enemy_bat_red : public enemy
{
private:


public:
	enemy_bat_red();
	~enemy_bat_red();

	HRESULT init(string imgName, int idxX, int idxY);
	void release();
	void update();
	void render();

	void aniSetUp();
	void aniPlay_Stand();
};

