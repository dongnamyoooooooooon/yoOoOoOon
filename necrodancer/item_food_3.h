#pragma once
#include "item.h"
class item_food_3 : public item
{
public:
	item_food_3();
	~item_food_3();

	HRESULT init(string imgName, int idxX, int idxY, ITEM_TYPE type);
	void release();
	void update();
	void render();

	void drawHint();
	bool useItem(int idxX, int idxY, int way);
};

