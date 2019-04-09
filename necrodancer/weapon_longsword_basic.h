#pragma once
#include "item.h"
class weapon_longsword_basic : public item
{
private:
	bool _isLong;

public:
	weapon_longsword_basic();
	~weapon_longsword_basic();

	HRESULT init(string imgName, int idxX, int idxY, ITEM_TYPE type);
	void release();
	void update();
	void render();

	void drawHint();
	bool useItem(int idxX, int idxY, int way);
};

