#pragma once
#include "enemy.h"
class enemy_zombie : public enemy
{
private:
	DIRECTION _tempDir;

public:
	enemy_zombie();
	~enemy_zombie();


	HRESULT init(string imgName, int idxX, int idxY);
	void release();
	void update();
	void render();

	void aniSetUp();

	void aniPlay_Up();
	void aniPlay_Down();
	void aniPlay_Side();
	
	void jumpMoveEnemy();
};

