#pragma once
#include "item.h"
class shovel_basic : public item
{
private:
	int shovelPower;
	

public:
	shovel_basic();
	~shovel_basic();

	HRESULT init(string imgName, int idxX, int idxY, ITEM_TYPE type);
	void release();
	void update();
	void render();

	void drawHint();

	bool useItem(int idxX, int idxY, int way);
};

