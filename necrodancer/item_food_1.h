#pragma once
#include "item.h"
class item_food_1 : public item
{
private:


public:
	item_food_1();
	~item_food_1();

	HRESULT init(string imgName, int idxX, int idxY, ITEM_TYPE type);
	void release();
	void update();
	void render();

	void drawHint();
	bool useItem(int idxX, int idxY, int way);
};

