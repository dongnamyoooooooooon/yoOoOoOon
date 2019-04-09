#pragma once
#include "item.h"
class shovel_glass_shard : public item
{
private:
	int _shovelPower;

public:
	shovel_glass_shard();
	~shovel_glass_shard();

	HRESULT init(string imgName, int idxX, int idxY, ITEM_TYPE type);
	void release();
	void update();
	void render();

	void drawHint();

	bool useItem(int idxX, int idxY, int way);
};

