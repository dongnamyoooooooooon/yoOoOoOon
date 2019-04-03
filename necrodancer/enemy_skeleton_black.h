#pragma once
#include "enemy.h"
class enemy_skeleton_black : public enemy
{
private:
	bool _isHeartOne;
	DIRECTION _skelDir;

public:
	enemy_skeleton_black();
	~enemy_skeleton_black();

	HRESULT init(string imgName, int idxX, int idxY);
	void release();
	void update();
	void render();

	void aniSetUp();

	void aniPlay_Attack();
	void aniPlay_Stand();
	void aniPlay_NoHead();

	void hitEnemy(int damage);
	void patternMove();
};

