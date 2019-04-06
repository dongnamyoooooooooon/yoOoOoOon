#pragma once
#include "enemy.h"
class enemy_coralriff_strings : public enemy
{
public:
	enemy_coralriff_strings();
	~enemy_coralriff_strings();

	HRESULT init(string imgName, int idxX, int idxY);
	void release();
	void update();
	void render();

	void aniSetUp();

	void aniPlay_Stand();
};

