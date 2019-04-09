#include "stdafx.h"
#include "item_food_1.h"


item_food_1::item_food_1()
{
}


item_food_1::~item_food_1()
{
}

HRESULT item_food_1::init(string imgName, int idxX, int idxY, ITEM_TYPE type)
{
	item::init(imgName, idxX, idxY, type);

	_appliedValue = 2;

	return S_OK;
}

void item_food_1::release()
{
}

void item_food_1::update()
{
	item::update();
}

void item_food_1::render()
{
	item::render();
}

void item_food_1::drawHint()
{
	IMAGEMANAGER->render("hint_food_1", _posX - 55, _posY - 26);
}

bool item_food_1::useItem(int idxX, int idxY, int way)
{
	player* tempPlayer = OBJECTMANAGER->getPlayer();
	SOUNDMANAGER->play("sound_item_food");
	tempPlayer->setHeart(_appliedValue);
	return true;
}
