#pragma once
#include "item.h"
class weapon_dagger_basic : public item
{
private:

	int _attackWay;
	int _effectX;
	int _effectY;
	int _drawX;
	int _drawY;
	int _effectCount;


public:
	weapon_dagger_basic();
	~weapon_dagger_basic();

	HRESULT init(string imgName, int idxX, int idxY, ITEM_TYPE type);
	void release();
	void update();
	void render();

	void drawHint();
	bool useItem(int idxX, int idxY, int way);
};

