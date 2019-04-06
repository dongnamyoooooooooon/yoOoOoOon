#pragma once
#include "enemy.h"
class enemy_armadillo : public enemy
{
private: 
	bool _isStun;
	bool _isStop;

public:
	enemy_armadillo();
	~enemy_armadillo();

	HRESULT init(string imgName, int idxX, int idxY);
	void release();
	void update();
	void render();

	void aniSetUp();
	
	void aniPlay_Stand();
	void aniPlay_Stun();
	void aniPlay_Horizon();
	void aniPlay_Vertical();

	void jumpMoveEnemy();

	void hitEnemy(int damage);
};

