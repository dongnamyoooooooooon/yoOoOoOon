#pragma once
#include "item.h"
class shovel_titanium : public item
{
private:
	int _shovelPower;

	
public:
	shovel_titanium();
	~shovel_titanium();

	HRESULT init(string imgName, int idxX, int idxY, ITEM_TYPE type);
	void release();
	void update();
	void render();

	void drawHint();

	bool useItem(int idxX, int idxY, int way);
};

