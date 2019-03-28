#include "stdafx.h"
#include "timeManager.h"


timeManager::timeManager()
	: _timer(NULL)
{
}


timeManager::~timeManager()
{
}

HRESULT timeManager::init()
{
	_timer = new timer;
	_timer->init();

	return S_OK;
}

void timeManager::release()
{
	if (_timer != NULL) SAFE_DELETE(_timer);
}

void timeManager::update(float lockFPS)
{
	if (_timer != NULL)
	{
		_timer->tick(lockFPS);
	}
}

void timeManager::render()
{
	WCHAR str[128];

	//디버그 상태면
#ifdef _DEBUG
	{
		

		swprintf_s(str, L"framePerSec(FPS) : %d", _timer->getFrameRate());
		D2DMANAGER->drawText(str, CAMERA->getPosX() + 12, CAMERA->getPosY() + 12, 15, RGB(255, 0, 0));
		swprintf_s(str, L"worldTime : %f", _timer->getWorldTime());
		D2DMANAGER->drawText(str, CAMERA->getPosX() + 12, CAMERA->getPosY() + 32, 15, RGB(255, 0, 0));
		swprintf_s(str, L"elapsedTime : %f", _timer->getElapsedTime());
		D2DMANAGER->drawText(str, CAMERA->getPosX() + 12, CAMERA->getPosY() + 52, 15, RGB(255, 0, 0));
		swprintf_s(str, L"framePerSec(FPS) : %d", _timer->getFrameRate());
		D2DMANAGER->drawText(str, CAMERA->getPosX() + 10, CAMERA->getPosY() + 10, 15, RGB(0, 255, 255));
		swprintf_s(str, L"worldTime : %f", _timer->getWorldTime());
		D2DMANAGER->drawText(str, CAMERA->getPosX() + 10, CAMERA->getPosY() + 30, 15, RGB(0, 255, 255));
		swprintf_s(str, L"elapsedTime : %f", _timer->getElapsedTime());
		D2DMANAGER->drawText(str, CAMERA->getPosX() + 10, CAMERA->getPosY() + 50, 15, RGB(0, 255, 255));
	}
#else
	//릴리즈 상태면
	{

		swprintf_s(str, L"framePerSec(FPS) : %d", _timer->getFrameRate(), (float)(MAPSIZEX - WINSIZEX));
		D2DMANAGER->drawText(str, CAMERA->getPosX(), CAMERA->getPosY());
	}
#endif
}
