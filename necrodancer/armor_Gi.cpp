#include "stdafx.h"
#include "armor_Gi.h"


armor_Gi::armor_Gi()
{
}


armor_Gi::~armor_Gi()
{
}

HRESULT armor_Gi::init(string imgName, int idxX, int idxY, ITEM_TYPE type)
{
	item::init(imgName, idxX, idxY, type);
	return S_OK;
}

void armor_Gi::release()
{
}

void armor_Gi::update()
{
	item::update();
}

void armor_Gi::render()
{
	item::render();
}

void armor_Gi::drawHint()
{
	IMAGEMANAGER->render("hint_armor_gi", _posX - 110, _posY - 26);
}
