#pragma once
#include "enemy.h"
class enemy_bat_boss : public enemy
{
public:
	enemy_bat_boss();
	~enemy_bat_boss();

	HRESULT init(string imgName, int idxX, int idxY);
	void release();
	void update();
	void render();

	void aniSetUp();
	void aniPlay_Stand();


};

