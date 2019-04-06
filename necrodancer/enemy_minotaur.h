#pragma once
#include "enemy.h"

enum MINOTAUR_STATE
{
	MINOTAUR_STATE_IDLE,
	MINOTAUR_STATE_RUN,
	MINOTAUR_STATE_STUN
};

class enemy_minotaur : public enemy
{
private:
	MINOTAUR_STATE _minoState;
	int _count;

public:
	enemy_minotaur();
	~enemy_minotaur();

	HRESULT init(string imgName, int idxX, int idxY);
	void release();
	void update();
	void render();

	void aniSetUp();

	void aniPlay_Stand();
	void aniPlay_Run();
	void aniPlay_Stun();

	bool searchTarget();
	void run();
	void stun();

	void jumpMoveEnemy();
};

