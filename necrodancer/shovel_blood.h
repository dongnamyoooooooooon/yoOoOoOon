#pragma once
#include "item.h"
class shovel_blood : public item
{
private:
	int _shovelPower;


public:
	shovel_blood();
	~shovel_blood();


	HRESULT init(string imgName, int idxX, int idxY, ITEM_TYPE type);
	void release();
	void update();
	void render();

	void drawHint();

	bool useItem(int idxX, int idxY, int way);
};

