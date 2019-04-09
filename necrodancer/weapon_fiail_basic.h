#pragma once
#include "item.h"
class weapon_fiail_basic : public item
{
public:
	weapon_fiail_basic();
	~weapon_fiail_basic();

	HRESULT init(string imgName, int idxX, int idxY, ITEM_TYPE type);
	void release();
	void update();
	void render();

	void drawHint();
	bool useItem(int idxX, int idxY, int way);
};

