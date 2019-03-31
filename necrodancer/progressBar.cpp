#include "stdafx.h"
#include "progressBar.h"


progressBar::progressBar()
{
}


progressBar::~progressBar()
{
}

HRESULT progressBar::init(int x, int y, int width, int height)
{
	_x = x;
	_y = y;



	_progressBarTop = IMAGEMANAGER->addImage("frontBar", L"top.png", width, height);
	_progressBarBottom = IMAGEMANAGER->addImage("backBar", L"bottom.png", width, height);

	_rcProgress = { _x, _y, _x + _progressBarTop->GetWidth(), _y + _progressBarTop->GetHeight() };
	//���α׷��� �� �̹����� ũ�Ⱑ ����ũ�Ⱑ �ȴ�.
	_width = _progressBarBottom->GetWidth();

	return S_OK;
}

void progressBar::release()
{
}

void progressBar::update()
{
	_rcProgress = { _x, _y, _x + _progressBarTop->GetWidth(), _y + _progressBarTop->GetHeight() };
}

void progressBar::render()
{
	//������ �׷��ִ� ���� ������ �޴´�. �׷����� ������� ������ ���´�

	IMAGEMANAGER->render("backBar", 0,
		_rcProgress.top + _progressBarBottom->GetHeight() / 2,
		0, 0,
		_progressBarBottom->GetWidth(), _progressBarBottom->GetHeight());
	//�տ� �׷����� �������� ����ũ�⸦ �����Ѵ�.
	IMAGEMANAGER->render("frontBar",
		0,
		_y + _progressBarBottom->GetHeight() / 2, 0, 0,
		_width, _progressBarBottom->GetHeight());
}

void progressBar::setGauge(float currentGauge, float maxGauge)
{
	//��ġ�� ������ ������ش�.
	_width = (currentGauge / maxGauge) * _progressBarBottom->GetWidth();
}
