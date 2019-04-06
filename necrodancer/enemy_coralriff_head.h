#pragma once
#include "enemy.h"
class enemy_coralriff_head : public enemy
{
private:
	bool  _isPlayerIn;

public:
	enemy_coralriff_head();
	~enemy_coralriff_head();

	HRESULT init(string imgName, int idxX, int idxY);
	void release();
	void update();
	void render();

	void aniSetUp();

	void aniPlay_Stand();

	bool aStarLoad();

	void hitEnemy(int damage);

	void createWall();

	void setFrame();
};

