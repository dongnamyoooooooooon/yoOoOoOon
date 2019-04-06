#pragma once
#include "item.h"
class item_coin : public item
{
public:
	item_coin();
	~item_coin();

	HRESULT init(string keyName, int idxX, int idxY, ITEM_TYPE type);
	void release();
	void update();
	void render();
};

