#pragma once
#include "item.h"
class armor_glass : public item
{
public:
	armor_glass();
	~armor_glass();

	HRESULT init(string imgName, int idxX, int idxY, ITEM_TYPE type);
	void release();
	void update();
	void render();

	void drawHint();
};

