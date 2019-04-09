#pragma once
#include "item.h"
class weapon_golden_lute : public item
{
public:
	weapon_golden_lute();
	~weapon_golden_lute();

	HRESULT init(string imgName, int idxX, int idxY, ITEM_TYPE type);
	void release();
	void update();
	void render();

	void drawHint();
	bool useItem(int idxX, int idxY, int way);
};

