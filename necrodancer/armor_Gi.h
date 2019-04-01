#pragma once
#include "item.h"
class armor_Gi : public item
{
public:
	armor_Gi();
	~armor_Gi();

	HRESULT init(string imgName, int idxX, int idxY, ITEM_TYPE type);
	void release();
	void update();
	void render();

	void drawHint();
};

