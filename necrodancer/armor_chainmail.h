#pragma once
#include "item.h"
class armor_chainmail : public item
{
public:
	armor_chainmail();
	~armor_chainmail();

	HRESULT init(string imgName, int idxX, int idxY, ITEM_TYPE type);
	void release();
	void update();
	void render();

	void drawHint();
};

