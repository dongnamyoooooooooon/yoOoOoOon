#pragma once
#include "item.h"
class torch_bright : public item
{
public:
	torch_bright();
	~torch_bright();

	HRESULT init(string imgName, int idxX, int idxY, ITEM_TYPE type);
	void release();
	void update();
	void render();

	void drawHint();
};

