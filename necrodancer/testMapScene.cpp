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

	load("map/testMapSize.map", "map/testMapData.map");

	_ii = 0;
	_jj = 0;
	_iiMax = 0;
	_jjMax = 0;

	OBJECTMANAGER->initBeat("sound/music/zone1.txt", "test_music");


	return S_OK;
}

void testMapScene::release()
{
}

void testMapScene::update()
{
	playerMgr();
	CAMERA->move(_pos.x, _pos.y);
	OBJECTMANAGER->createBeat();
	OBJECTMANAGER->deleteBeat();
	OBJECTMANAGER->allObjectUpdate();

}

void testMapScene::render()
{
	OBJECTMANAGER->render();
}

void testMapScene::load(const char * size, const char * data)
{
	OBJECTMANAGER->vectorClear();

	for (int i = _tiray - 1; i >= 0; i--)
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
	_tiray = stoi(mapY);
	_vvTile.resize(_tiray);

	for (UINT i = 0; i < _tiray; ++i)
	{
		_vvTile[i].resize(_tileX);
	}

	tagPack* pack = new tagPack[_tileX * _tiray];


	OBJECTMANAGER->setTileX(_tileX);
	OBJECTMANAGER->setTiray(_tiray);

	OBJECTMANAGER->init();

	HANDLE file2;
	DWORD read2;

	file2 = CreateFile(data, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file2, pack, sizeof(tagPack) * _tileX * _tiray, &read2, NULL);
	CloseHandle(file2);

	for (UINT i = 0; i < _tiray; ++i)
	{
		vector<D2D1_RECT_F> vRECT;
		for (UINT j = 0; j < _tileX; ++j)
		{
			_vvTile[i][j] = new tagTile;
			_vvTile[i][j]->makeLoad(&pack[i + j * _tileX]);

			if (_vvTile[i][j]->type_floor == OBJECT_TYPE_FLOOR)
				OBJECTMANAGER->objectPush(*_vvTile[i][j]->floor);
		}
	}

	for (UINT i = 0; i < _tiray; ++i)
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
