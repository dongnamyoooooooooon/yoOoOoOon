#include "stdafx.h"
#include "item_food_3.h"


item_food_3::item_food_3()
{
}


item_food_3::~item_food_3()
{
}

HRESULT item_food_3::init(string imgName, int idxX, int idxY, ITEM_TYPE type)
{

	item::init(imgName, idxX, idxY, type);

	_appliedValue = 6;

	return S_OK;
}

void item_food_3::release()
{
}

void item_food_3::update()
{
	item::update();
}

void item_food_3::render()
{
	item::render();
}

void item_food_3::drawHint()
{
	IMAGEMANAGER->render("hint_food_3", _posX - 55, _posY - 26);
}

bool item_food_3::useItem(int idxX, int idxY, int way)
{
	player* tempPlayer = OBJECTMANAGER->getPlayer();
	SOUNDMANAGER->play("sound_item_food");
	tempPlayer->setHeart(_appliedValue);
	return true;
}
