#pragma once
#include "item.h"
class shovel_crystal : public item
{
private:
	int _shovelPower;

public:
	shovel_crystal();
	~shovel_crystal();

	HRESULT init(string imgName, int idxX, int idxY, ITEM_TYPE type);
	void release();
	void update();
	void render();

	void drawHint();

	bool useItem(int idxX, int idxY, int way);
};

