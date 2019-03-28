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

	_player = new player;
	_player->init(1, 1);
	_player->setObjType(OBJECT_TYPE_PLAYER);

	_ii = 0;
	_jj = 0;
	_iiMax = 0;
	_jjMax = 0;

	//OBJECTMANAGER->objectPush(*_player);

	return S_OK;
}

void testMapScene::release()
{
}

void testMapScene::update()
{
	//OBJECTMANAGER->allObjectUpdate();

	_ii = CAMERA->getPosY() / TILE_SIZE;
	if (_ii < 0) _ii = 0;
	_jj = CAMERA->getPosX() / TILE_SIZE;
	if (_jj < 0) _jj = 0;
	_iiMax = ((CAMERA->getPosY() + WINSIZEY) / TILE_SIZE) + 2;
	if (_iiMax >= _tileY) _iiMax = _tileY - 1;
	_jjMax = ((CAMERA->getPosX() + WINSIZEX) / TILE_SIZE) + 1;
	if (_jjMax >= _tileX) _jjMax = _tileX - 1;

	_player->update();
}

void testMapScene::render()
{
	for (; _ii < _iiMax; ++_ii)
	{
		for (; _jj < _jjMax; ++_jj)
		{
			_vvTile[_ii][_jj]->floor->render(_ii * TILE_SIZE, _jj * TILE_SIZE);
			_player->render();
		}
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
			_vvTile[i][j]->makeLoad(&pack[i + j * _tileX]);
			
		}
	}
}
