#pragma once
#include "item.h"
class weapon_blunderbuss : public item
{
private:
	bool _isReload;
	int _knockBack;

public:
	weapon_blunderbuss();
	~weapon_blunderbuss();

	HRESULT init(string imgName, int idxX, int idxY, ITEM_TYPE type);
	void release();
	void update();
	void render();

	void drawHint();
	bool useItem(int idxX, int idxY, int way);
};

