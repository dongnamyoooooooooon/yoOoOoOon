#pragma once
#include "item.h"
class armor_platemail : public item
{
public:
	armor_platemail();
	~armor_platemail();

	HRESULT init(string imgName, int idxX, int idxY, ITEM_TYPE type);
	void release();
	void update();
	void render();

	void drawHint();

};

