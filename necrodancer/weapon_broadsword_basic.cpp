#include "stdafx.h"
#include "weapon_broadsword_basic.h"


weapon_broadsword_basic::weapon_broadsword_basic()
{
}


weapon_broadsword_basic::~weapon_broadsword_basic()
{
}

HRESULT weapon_broadsword_basic::init(string imgName, int idxX, int idxY, ITEM_TYPE type)
{
	item::init(imgName, idxX, idxY, type);

	_appliedValue = 1;

	return S_OK;
}

void weapon_broadsword_basic::release()
{
}

void weapon_broadsword_basic::update()
{
	item::update();
}

void weapon_broadsword_basic::render()
{
	item::render();
}

void weapon_broadsword_basic::drawHint()
{
	IMAGEMANAGER->render("hint_broadsword_basic", _posX - 45, _posY - 26);
}

bool weapon_broadsword_basic::useItem(int idxX, int idxY, int way)
{
	parentObj* tempObj[3];

	_posX = OBJECTMANAGER->getPlayer()->getPosX();
	_posY = OBJECTMANAGER->getPlayer()->getPosY();

	switch (way)
	{
	case 2:
		tempObj[0] = OBJECTMANAGER->getCheckObj(idxX - 1, idxY + 1);
		tempObj[1] = OBJECTMANAGER->getCheckObj(idxX, idxY + 1);
		tempObj[2] = OBJECTMANAGER->getCheckObj(idxX + 1, idxY + 1);

		_posX -= 52;
		_posY += 52;
		break;

	case 4:
		tempObj[0] = OBJECTMANAGER->getCheckObj(idxX, idxY - 1);
		tempObj[1] = OBJECTMANAGER->getCheckObj(idxX, idxY);
		tempObj[2] = OBJECTMANAGER->getCheckObj(idxX, idxY + 1);

		_posX -= 52;
		_posY -= 52;
		break;

	case 6:
		tempObj[0] = OBJECTMANAGER->getCheckObj(idxX + 1, idxY - 1);
		tempObj[1] = OBJECTMANAGER->getCheckObj(idxX + 1, idxY);
		tempObj[2] = OBJECTMANAGER->getCheckObj(idxX + 1, idxY + 1);

		_posX += 52;
		_posY -= 52;
		break;

	case 8:
		tempObj[0] = OBJECTMANAGER->getCheckObj(idxX - 1, idxY - 1);
		tempObj[1] = OBJECTMANAGER->getCheckObj(idxX, idxY - 1);
		tempObj[2] = OBJECTMANAGER->getCheckObj(idxX + 1, idxY - 1);

		_posX -= 52;
		_posY -= 52;
		break;
	}

	bool haveObj = false;

	for (int i = 0; i < 3; i++)
	{
		if (tempObj[i] != NULL && tempObj[i]->getObjType() == OBJECT_TYPE_ENEMY)
		{
			_attackWay = way;
			//이펙트방향 설정

			tempObj[i]->hitEnemy(_appliedValue);
			//이펙트 나감?
			haveObj = true;
		}
	}

	return haveObj;
}
