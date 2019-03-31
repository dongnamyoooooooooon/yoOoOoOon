#pragma once
#include "gameNode.h"
class progressBar : public gameNode
{

private:
	D2D1_RECT_F _rcProgress;		//���α׷��� �� ��Ʈ
	float _x, _y;			//���α׷��� �� ��ǥ
	float _width;			//����ũ��

	image* _progressBarTop;
	image* _progressBarBottom;



public:
	progressBar();
	~progressBar();


	HRESULT init(int x, int y, int width, int height);
	void release();
	void update();
	void render();

	void setGauge(float currentGauge, float maxGauge);

	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }

	inline RECT makeRECT(D2D1_RECT_F rc)
	{
		return RECT{ (LONG)rc.left, (LONG)rc.top, (LONG)rc.right, (LONG)rc.bottom };
	}

	D2D1_RECT_F getRC() { return _rcProgress; }
	float getWidth() { return _width; }
};

