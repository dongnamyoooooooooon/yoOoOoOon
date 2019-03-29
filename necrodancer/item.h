#pragma once
#include "parentObj.h"
class item : public parentObj
{
protected:
	
	ITEM_TYPE _itemType;

	bool _isMoveInven;
	bool _isEffectUse;
	bool _isThrow;

	float _gravity;
	float _jumpPower;

	int _floatCount;
	int _moveX;
	int _moveY;
	int _attackWay;
	int _effectX;
	int _effectY;
	int _drawX;
	int _drawY;
	int _effectCount;

public:
	item();
	~item();


	HRESULT init(string keyName, int idxX, int idxY, ITEM_TYPE type);
	void release();
	void update();
	void render();


	//=========================================
	
	void itemInven(int moveX, int moveY);
	void setMoveXY(int moveX, int moveY)
	{
		if (_isCurInven)
		{
			this->_moveX = moveX;
			this->_moveY = moveY;
		}
	}

	void drawFloorItem();
	void moveItem();

	virtual void setIsCurInven(bool check) { _isCurInven = check; }

};

