#pragma once
#include "enemy.h"
class enemy_skeleton : public enemy
{
private:

public:
	enemy_skeleton();
	~enemy_skeleton();

	HRESULT init(string imgName, int idxX, int idxY);
	void release();
	void update();
	void render();

	void aniPlay();
};

