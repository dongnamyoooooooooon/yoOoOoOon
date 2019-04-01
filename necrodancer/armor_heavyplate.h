#pragma once
#include "item.h"
class armor_heavyplate : public item
{
public:
	armor_heavyplate();
	~armor_heavyplate();

	HRESULT init(string imgName, int idxX, int idxY, ITEM_TYPE type);
	void release();
	void update();
	void render();

	void drawHint();
};

