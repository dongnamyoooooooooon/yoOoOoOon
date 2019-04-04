#pragma once
#include "enemy.h"
class enemy_clone : public enemy
{
private:
	DIRECTION _attDir;


public:
	enemy_clone();
	~enemy_clone();

	HRESULT init(string imgName, int idxX, int idxY);
	void release();
	void update();
	void render();

	void aniSetUp();

	void aniPlay_Stand();

	void jumpMoveEnemy();

	//void attackEnemy(DIRECTION dir);
};

