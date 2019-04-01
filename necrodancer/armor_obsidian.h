#pragma once
#include "item.h"
class armor_obsidian : public item
{
public:
	armor_obsidian();
	~armor_obsidian();

	HRESULT init(string imgName, int idxX, int idxY, ITEM_TYPE type);
	void release();
	void update();
	void render();

	void drawHint();
};

