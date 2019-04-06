#pragma once
#include "enemy.h"
class enemy_coralriff_keytar :
	public enemy
{
public:
	enemy_coralriff_keytar();
	~enemy_coralriff_keytar();

	HRESULT init(string imgName, int idxX, int idxY);
	void release();
	void update();
	void render();

	void aniSetUp();

	void aniPlay_Stand();
};

