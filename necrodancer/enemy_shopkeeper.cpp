#include "stdafx.h"
#include "enemy_shopkeeper.h"


enemy_shopkeeper::enemy_shopkeeper()
{
}


enemy_shopkeeper::~enemy_shopkeeper()
{
}

HRESULT enemy_shopkeeper::init(string imgName, int idxX, int idxY)
{
	enemy::init(imgName, idxX, idxY);

	_moveBeat = 1;
	_subX = 22;
	_subY = 40;

	_damage = 20;
	_heart = 18;
	_maxHeart = 18;

	_frameX = 0;
	_frameY = 0;

	_isLeft = false;


	return S_OK;
}

void enemy_shopkeeper::release()
{
}

void enemy_shopkeeper::update()
{
	_count++;
	if (_count % 10 == 0)
	{
		aniPlay();
		if (_count >= 1000) _count = 0;
	}

	if (_isBeat)
	{
		_curMoveBeat++;
		if (_moveBeat == _curMoveBeat)
		{
			_curMoveBeat = 0;
			aStarLoad();
		}
		_isBeat = false;
	}
}

void enemy_shopkeeper::render()
{
	enemy::render();
}

void enemy_shopkeeper::aniPlay()
{
	float beatThresholdVolume = 0.75f;    // 비트를 인식할 수 있는 값
	int beatThresholdBar = 0;             // 검사할 볼륨 분포 막대
	UINT beatPostIgnore = 5000;			  // 비트 이후의 트랙을 무시하는 ms수

	int beatLastTick = 0;                // 마지막 비트가 발생한 시간

	bool beatDetected = false;

	// 볼륨 초과 테스트(현재 트랙을 무시하지 않는 경우)
	if (SOUNDMANAGER->getSpec()[beatThresholdBar] >= beatThresholdVolume && beatLastTick == 0)
	{
		beatLastTick = TIMEMANAGER->getElapsedTime();
		beatDetected = true;
	}

	if (beatDetected)
	{
		_frameX++;
		if (_frameX >= 4) _frameX = 0;
	}
	else
	{
		_frameX++;
		if (_frameX >= 7) _frameX = 4;
	}

	//비트 다시 테스트
	if (GetTickCount() - beatLastTick >= beatPostIgnore)
		beatLastTick = 0;
}

void enemy_shopkeeper::aStarLoad()
{
	player* tempPlayer = OBJECTMANAGER->getPlayer();
	_startPoint = false;
	_endPoint = false;


	for (int i = 0; i < _tileY; i++)
	{
		for (int j = 0; j < _tileX; j++)
		{
			_vvTile[i][j].moveWay = TILE_MOVE_WAY_NONE;
			_vvTile[i][j].parent = NULL;
			_vvTile[i][j].F = 5000;
			_vvTile[i][j].H = 0;
			_vvTile[i][j].i = i;
			_vvTile[i][j].j = j;
		}
	}

	_closeList.clear();
	_openList.clear();

	initTile();

	while (1)
	{

		if (_aStarState == ASTAR_STATE_FOUND)
		{

			float size = (float)_closeList.size();

			if (size < 13)
			{
				string song = SOUNDMANAGER->getShopBgmKey();

				float volume = SOUNDMANAGER->getVolume();

				volume = SOUNDMANAGER->getVolume() * ((13.0f - volume) / 12.0f / size);

				SOUNDMANAGER->ShopVolume(song, volume);

				if (size < 5)
				{
					volume = 1.0f;
					SOUNDMANAGER->ShopVolume(song, volume);
				}

			}
			else
			{
				string song = SOUNDMANAGER->getShopBgmKey();
				SOUNDMANAGER->ShopVolume(song, 0);
			}

			return;
		}
		else if (_aStarState == ASTAR_STATE_NOWAY)
		{

			// 여기다가는 무식하게 플레이어와의 위치를 구해서 성량 측정
			string song = SOUNDMANAGER->getShopBgmKey();
			int idxX = tempPlayer->getIdxX();
			int idxY = tempPlayer->getIdxY();

			int posX = idxX % _tileX;
			int posY = idxY / _tileY;

			int posX2 = _idxX % _tileX;
			int posY2 = _idxY / _tileY;

			if (posX2 - 12 < posX && posX2 + 12 > posX)
			{
				if (posY2 - 12 < posY && posY2 + 12 > posY)
				{
					string song = SOUNDMANAGER->getShopBgmKey();
					float volume = SOUNDMANAGER->getVolume();

					volume = SOUNDMANAGER->getVolume() * ((13.0f - volume) / 12.0f);

					SOUNDMANAGER->ShopVolume(song, volume / 2.0f);

				}
				else
					SOUNDMANAGER->ShopVolume(song, 0);
			}
			else
				SOUNDMANAGER->ShopVolume(song, 0);
			return;
		}

		addOpenList(); 
		calculateH(); 
		calculateF(); 
		addCloseList();
		checkArrive(); 
	}
}

void enemy_shopkeeper::initTile()
{
	parentObj* tempObj;

	for (int i = 0; i < _tileY; i++)
	{
		for (int j = 0; j < _tileX; j++)
		{
			tempObj = OBJECTMANAGER->getCheckObj(j, i);

			if (tempObj == NULL)
			{
				_vvTile[i][j].isWalk = true;
				_vvTile[i][j].listOn = false;
			}
			else
			{
				OBJECT_TYPE objType = tempObj->getObjType();
				if (objType == OBJECT_TYPE_WALL)
				{
					_vvTile[i][j].isWalk = false;
					_vvTile[i][j].listOn = false;
				}
				else if (objType == OBJECT_TYPE_ITEM)
				{
					_vvTile[i][j].isWalk = false;
					_vvTile[i][j].listOn = false;
				}
				else if (objType == OBJECT_TYPE_ENEMY)
				{
					if (tempObj->getIdxX() == _idxX && tempObj->getIdxY() == _idxY)
					{
						_vvTile[i][j].isWalk = true;
						_vvTile[i][j].listOn = true;
						_closeList.push_back(&_vvTile[i][j]);
						_startPoint = true;
						_startX = j;
						_startY = i;
					}
					else
					{
						_vvTile[i][j].isWalk = false;
						_vvTile[i][j].listOn = false;
					}
				}
				else if (objType == OBJECT_TYPE_PLAYER)
				{
					_vvTile[i][j].isWalk = true;
					_vvTile[i][j].listOn = false;
					_endX = j;
					_endY = i;
				}
			}
		}
	}
	_aStarState = ASTAR_STATE_SEARCHING;
	_lastIndex = 0;
}

void enemy_shopkeeper::addOpenList()
{
	_closeI = _closeList[_lastIndex]->i;
	_closeJ = _closeList[_lastIndex]->j;
	_closeGoal = _closeList[_lastIndex]->G;


	if (_vvTile[_closeI - 1][_closeJ].isWalk)
	{
		if (!_vvTile[_closeI - 1][_closeJ].listOn)
		{
			_vvTile[_closeI - 1][_closeJ].listOn = true;
			_vvTile[_closeI - 1][_closeJ].G = _closeGoal + 10;
			_vvTile[_closeI - 1][_closeJ].parent = _closeList[_lastIndex];
			_openList.push_back(&_vvTile[_closeI - 1][_closeJ]);
		}
		else
		{
			if (_closeGoal + 10 < _vvTile[_closeI - 1][_closeJ].G)
			{
				_vvTile[_closeI - 1][_closeJ].G = _closeGoal + 10;
				_vvTile[_closeI - 1][_closeJ].parent = _closeList[_lastIndex];
			}
		}
	}

	if (_vvTile[_closeI + 1][_closeJ].isWalk)
	{
		if (!_vvTile[_closeI + 1][_closeJ].listOn)
		{
			_vvTile[_closeI + 1][_closeJ].listOn = true;
			_vvTile[_closeI + 1][_closeJ].G = _closeGoal + 10;
			_vvTile[_closeI + 1][_closeJ].parent = _closeList[_lastIndex];
			_openList.push_back(&_vvTile[_closeI + 1][_closeJ]);
		}
		else
		{
			if (_closeGoal + 10 < _vvTile[_closeI + 1][_closeJ].G)
			{
				_vvTile[_closeI + 1][_closeJ].G = _closeGoal + 10;
				_vvTile[_closeI + 1][_closeJ].parent = _closeList[_lastIndex];
			}
		}
	}

	if (_vvTile[_closeI][_closeJ - 1].isWalk)
	{
		if (!_vvTile[_closeI][_closeJ - 1].listOn)
		{
			_vvTile[_closeI][_closeJ - 1].listOn = true;
			_vvTile[_closeI][_closeJ - 1].G = _closeGoal + 10;
			_vvTile[_closeI][_closeJ - 1].parent = _closeList[_lastIndex];
			_openList.push_back(&_vvTile[_closeI][_closeJ - 1]);
		}
		else
		{
			if (_closeGoal + 10 < _vvTile[_closeI][_closeJ - 1].G)
			{
				_vvTile[_closeI][_closeJ - 1].G = _closeGoal + 10;
				_vvTile[_closeI][_closeJ - 1].parent = _closeList[_lastIndex];
			}
		}
	}

	if (_vvTile[_closeI][_closeJ + 1].isWalk)
	{
		if (!_vvTile[_closeI][_closeJ + 1].listOn)
		{
			_vvTile[_closeI][_closeJ + 1].listOn = true;
			_vvTile[_closeI][_closeJ + 1].G = _closeGoal + 10;
			_vvTile[_closeI][_closeJ + 1].parent = _closeList[_lastIndex];
			_openList.push_back(&_vvTile[_closeI][_closeJ + 1]);
		}
		else
		{
			if (_closeGoal + 10 < _vvTile[_closeI][_closeJ + 1].G)
			{
				_vvTile[_closeI][_closeJ + 1].G = _closeGoal + 10;
				_vvTile[_closeI][_closeJ + 1].parent = _closeList[_lastIndex];
			}
		}
	}
}

void enemy_shopkeeper::addCloseList()
{
	if (_openList.size() == 0)
	{
		_aStarState = ASTAR_STATE_NOWAY; return;
	}

	int index = 0;
	int lowest = 5000;
	for (int i = 0; i < _openList.size(); i++)
	{
		if (_openList[i]->F < lowest)
		{
			lowest = _openList[i]->F;
			index = i;
		}
	}
	_closeList.push_back(_openList[index]);
	_openList.erase(_openList.begin() + index);

	_lastIndex++;
}

void enemy_shopkeeper::calculateH()
{
	for (int i = 0; i < _openList.size(); i++)
	{
		int vertical = (_endX - _openList[i]->j) * 10;
		int horizontal = (_endY - _openList[i]->i) * 10;

		if (vertical < 0)	vertical *= -1;
		if (horizontal < 0) horizontal *= -1;

		_openList[i]->H = vertical + horizontal;
	}
}

void enemy_shopkeeper::calculateF()
{
	for (int i = 0; i < _openList.size(); i++)
	{
		_openList[i]->F = _openList[i]->G + _openList[i]->H;
	}
}

void enemy_shopkeeper::checkArrive()
{
	if (_closeList[_lastIndex]->i == _endY && _closeList[_lastIndex]->j == _endX)
		_aStarState = ASTAR_STATE_FOUND;
}
