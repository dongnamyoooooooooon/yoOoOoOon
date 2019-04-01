#pragma once
#include "item.h"
class weapon_broadsword_basic : public item
{
public:
	weapon_broadsword_basic();
	~weapon_broadsword_basic();

	HRESULT init(string imgName, int idxX, int idxY, ITEM_TYPE type);
	void release();
	void update();
	void render();

	void drawHint();
	bool useItem(int idxX, int idxY, int way);
};

