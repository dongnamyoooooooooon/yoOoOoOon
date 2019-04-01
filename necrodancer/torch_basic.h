#pragma once
#include "item.h"
class torch_basic : public item
{
public:
	torch_basic();
	~torch_basic();

	HRESULT init(string imgName, int idxX, int idxY, ITEM_TYPE type);
	void release();
	void update();
	void render();

	void drawHint();
};

