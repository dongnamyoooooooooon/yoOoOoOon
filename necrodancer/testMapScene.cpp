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

	return S_OK;
}

void testMapScene::release()
{
}

void testMapScene::update()
{
}

void testMapScene::render()
{
	OBJECTMANAGER->render();
}

void testMapScene::load(const char * size, const char * data)
{
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
			OBJECTMANAGER->objectPush(*(*(_vvTile[i])[j]).floor);
		}
	}
}
