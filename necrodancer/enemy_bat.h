#pragma once
#include "enemy.h"
class enemy_bat : public enemy
{
public:
	enemy_bat();
	~enemy_bat();


	HRESULT init(string imgName, int idxX, int idxY);
	void release();
	void update();
	void render();

	void aniSetUp();
	void aniPlay_Stand();
};

