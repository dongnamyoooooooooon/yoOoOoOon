#pragma once
#include "enemy.h"
class enemy_shopkeeper : public enemy
{
public:
	enemy_shopkeeper();
	~enemy_shopkeeper();

	HRESULT init(string imgName, int idxX, int idxY);
	void release();
	void update();
	void render();

	void aniPlay();

	void aStarLoad();

	void initTile();
	void addOpenList();
	void addCloseList();
	void calculateH();
	void calculateF();
	void checkArrive();
};

