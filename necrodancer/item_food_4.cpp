#include "stdafx.h"
#include "item_food_4.h"


item_food_4::item_food_4()
{
}


item_food_4::~item_food_4()
{
}

HRESULT item_food_4::init(string imgName, int idxX, int idxY, ITEM_TYPE type)
{
	item::init(imgName, idxX, idxY, type);

	_appliedValue = 8;
	return S_OK;
}

void item_food_4::release()
{
}

void item_food_4::update()
{
	item::update();
}

void item_food_4::render()
{
	item::render();
}

void item_food_4::drawHint()
{
	IMAGEMANAGER->render("hint_food_4", _posX - 55, _posY - 26);
}

bool item_food_4::useItem(int idxX, int idxY, int way)
{
	player* tempPlayer = OBJECTMANAGER->getPlayer();
	SOUNDMANAGER->play("sound_item_food");
	tempPlayer->setHeart(_appliedValue);
	return true;
}
