#pragma once
#include "item.h"
class armor_leather : public item
{
public:
	armor_leather();
	~armor_leather();

	HRESULT init(string imgName, int idxX, int idxY, ITEM_TYPE type);
	void release();
	void update();
	void render();

	void drawHint();
};

