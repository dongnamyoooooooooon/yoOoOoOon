#pragma once
#include "item.h"
class torch_luminious : public item
{
private:

public:
	torch_luminious();
	~torch_luminious();

	HRESULT init(string imgName, int idxX, int idxY, ITEM_TYPE type);
	void release();
	void update();
	void render();

	void drawHint();
};

