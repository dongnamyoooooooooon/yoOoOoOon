#include "stdafx.h"
#include "item_food_2.h"


item_food_2::item_food_2()
{
}


item_food_2::~item_food_2()
{
}

HRESULT item_food_2::init(string imgName, int idxX, int idxY, ITEM_TYPE type)
{

	item::init(imgName, idxX, idxY, type);

	_appliedValue = 4;
	return E_NOTIMPL;
}

void item_food_2::release()
{
}

void item_food_2::update()
{
	item::update();
}

void item_food_2::render()
{
	item::render();
}

void item_food_2::drawHint()
{
	IMAGEMANAGER->render("hint_food_2", _posX - 55, _posY - 26);
}

bool item_food_2::useItem(int idxX, int idxY, int way)
{
	player* tempPlayer = OBJECTMANAGER->getPlayer();
	SOUNDMANAGER->play("sound_item_food");
	tempPlayer->setHeart(_appliedValue);
	return true;
}
