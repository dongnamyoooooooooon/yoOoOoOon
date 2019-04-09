#include "stdafx.h"
#include "testMapScene.h"


testMapScene::testMapScene()
{
}


testMapScene::~testMapScene()
{
}

HRESULT testMapScene::init()
{

	load("map/zone2MapSize.map", "map/zone2MapData.map");

	_ii = 0;
	_jj = 0;
	_iiMax = 0;
	_jjMax = 0;

	OBJECTMANAGER->initBeat("sound/music/zone1.txt", "music_item");
	SOUNDMANAGER->setShopBgmKey("music_item");

	return S_OK;
}

void testMapScene::release()
{
}

void testMapScene::update()
{
	playerMgr();
	EFFECTMANAGER->update();
	CAMERA->move(_pos.x, _pos.y);
	OBJECTMANAGER->createBeat();
	OBJECTMANAGER->deleteBeat();
	OBJECTMANAGER->allObjectUpdate();
	OBJECTMANAGER->update();
	OBJECTMANAGER->weaponEff();
}

void testMapScene::render()
{
	OBJECTMANAGER->render();
	EFFECTMANAGER->render();

	player* tempPlayer = OBJECTMANAGER->getPlayer();

	if (tempPlayer->getIsUseShovel())
	{
		if (tempPlayer->getAttDir() == PLAYER_STATE_JUMP_LEFT)
			IMAGEMANAGER->findImage(tempPlayer->getPlayerShovel()->getImgName())->frameRender(tempPlayer->getPlayerPosX() - 78, tempPlayer->getPlayerPosY() - 46, 0, 0);
		else if (tempPlayer->getAttDir() == PLAYER_STATE_JUMP_RIGHT)
			IMAGEMANAGER->findImage(tempPlayer->getPlayerShovel()->getImgName())->frameRender(tempPlayer->getPlayerPosX() + 26, tempPlayer->getPlayerPosY() - 46, 0, 0);
		else if (tempPlayer->getAttDir() == PLAYER_STATE_JUMP_UP)
			IMAGEMANAGER->findImage(tempPlayer->getPlayerShovel()->getImgName())->frameRender(tempPlayer->getPlayerPosX() - 26, tempPlayer->getPlayerPosY() - 98, 0, 0);
		else if (tempPlayer->getAttDir() == PLAYER_STATE_JUMP_DOWN)
			IMAGEMANAGER->findImage(tempPlayer->getPlayerShovel()->getImgName())->frameRender(tempPlayer->getPlayerPosX() - 26, tempPlayer->getPlayerPosY(), 0, 0);
	}
}

void testMapScene::load(const char * size, const char * data)
{
	OBJECTMANAGER->vectorClear();

	for (int i = _tileY - 1; i >= 0; i--)
	{
		for (int j = _tileX - 1; j >= 0; j--)
		{
			if (_vvTile[i][j])
			{
				SAFE_DELETE(_vvTile[i][j]);
				_vvTile[i].pop_back();
			}
		}
		_vvTile.pop_back();
	}
	_vvTile.clear();


	HANDLE file;
	DWORD read;
	char mapSize[128] = { 0, };

	file = CreateFile(size, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, mapSize, 128, &read, NULL);
	CloseHandle(file);

	string mapX, mapY;
	mapX.clear();
	mapY.clear();
	bool x = true;
	for (int i = 0; i < strlen(mapSize); ++i)
	{
		if (mapSize[i] == '/')
		{
			x = false;
			continue;
		}
		if (mapSize[i] == NULL)
			break;
		if (x)
		{
			mapX += mapSize[i];
		}
		else
		{
			mapY += mapSize[i];
		}
	}

	_tileX = stoi(mapX);
	_tileY = stoi(mapY);
	_vvTile.resize(_tileY);

	for (UINT i = 0; i < _tileY; ++i)
	{
		_vvTile[i].resize(_tileX);
	}

	tagPack* pack = new tagPack[_tileX * _tileY];


	OBJECTMANAGER->setTileX(_tileX);
	OBJECTMANAGER->setTileY(_tileY);

	OBJECTMANAGER->init();

	HANDLE file2;
	DWORD read2;

	file2 = CreateFile(data, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file2, pack, sizeof(tagPack) * _tileX * _tileY, &read2, NULL);
	CloseHandle(file2);

	for (UINT i = 0; i < _tileY; ++i)
	{
		vector<D2D1_RECT_F> vRECT;
		for (UINT j = 0; j < _tileX; ++j)
		{
			_vvTile[i][j] = new tagTile;
			_vvTile[i][j]->makeLoad(&pack[j + i * _tileX]);

			if (_vvTile[i][j]->type_floor == OBJECT_TYPE_FLOOR)
				OBJECTMANAGER->objectPush(*_vvTile[i][j]->floor);
		}
	}

	for (UINT i = 0; i < _tileY; ++i)
	{
		for (int j = 0; j < _tileX; ++j)
		{
			if (_vvTile[i][j]->type_obj == OBJECT_TYPE_PLAYER)
			{
				OBJECTMANAGER->objectPush(*_vvTile[i][j]->player);
				_pos = { (LONG)j * TILE_SIZE, (LONG)i * TILE_SIZE };

			}
			else if (_vvTile[i][j]->type_obj == OBJECT_TYPE_WALL)
				OBJECTMANAGER->objectPush(*_vvTile[i][j]->wall);
			else if (_vvTile[i][j]->type_obj == OBJECT_TYPE_ITEM)
				OBJECTMANAGER->objectPush(*_vvTile[i][j]->item);
			else if (_vvTile[i][j]->type_obj == OBJECT_TYPE_ENEMY)
				OBJECTMANAGER->objectPush(*_vvTile[i][j]->enemy);
		}
	}
}

void testMapScene::playerMgr()
{
	_player = OBJECTMANAGER->getPlayer();

	_pos.x = _player->getPlayerPosX();
	_pos.y = _player->getPlayerPosY();

	_player->update();

	_vObj = OBJECTMANAGER->getVObj();
	_viObj = OBJECTMANAGER->getVIObj();


	_curPos.x = _player->getPlayerPosX();
	_curPos.y = _player->getPlayerPosY();

}