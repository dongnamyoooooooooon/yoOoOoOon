#pragma once
#include "item.h"
class weapon_spear_basic : public item
{
private:
	bool _isThrow;
	bool _isLong;


public:
	weapon_spear_basic();
	~weapon_spear_basic();

	HRESULT init(string imgName, int idxX, int idxY, ITEM_TYPE type);
	void release();
	void update();
	void render();

	void drawHint();
	bool useItem(int idxX, int idxY, int way);


	bool getIsThrow() { return _isThrow; }

};

