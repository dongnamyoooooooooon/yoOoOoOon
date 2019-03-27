#pragma once
#include "gameNode.h"

enum OBJECT_TYPE
{
	OBJECT_TYPE_FLOOR,
	OBJECT_TYPE_WALL,
	OBJECT_TYPE_ENEMY,
	OBJECT_TYPE_TRAP,
	OBJECT_TYPE_ITEM,
	OBJECT_TYPE_ETC,
	OBJECT_TYPE_PLAYER,

	OBJECT_TYPE_NONE,
	
	OBJECT_TYPE_COUNT = OBJECT_TYPE_NONE
};


class parentObj : public gameNode
{
protected:
	image*			_img;			//이미지					
	string			_imgName;		//이미지키값
	OBJECT_TYPE		_objType;		//오브젝트타입
	POINTF			_pos;			//실제위치
	D2D1_RECT_F		_rc;			//렉트

	
	int				_frameX;
	int				_frameY;
	int				_count = 0;
	int				_appValue;		//적용값
	int				_idxX;
	int				_idxY;

	bool			_isTorch;		//횃불 가지고있는지?
	bool			_isBeat;		//비트에 맞췄는지?
	bool			_hasLight;		//불빛을 가지고 있는지?
	bool			_isSight;		//플레이어 시야 안에 있는지?
	bool			_isSaw;			//플레이어에게 보여졌는지?
	




public:
	parentObj();
	~parentObj();

	virtual HRESULT init(string imgName, int idx_X, int idx_Y, OBJECT_TYPE type);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void render(float x, float y);

	
	//=======================================
	//			  g e t & s e t
	//=======================================

	bool getTorch() { return _isTorch; }
	void setTorch(bool check) { _isTorch = check; }

	OBJECT_TYPE getObjType() { return _objType; }
	void setObjType(OBJECT_TYPE type) { _objType = type; }

	string getImgName() { return _imgName; }
	void setImgName(string name) { _imgName = name; }

	D2D1_RECT_F getRC() { return _rc; }
	void setRC(D2D1_RECT_F rc) { _rc = rc; }

	image* getImg() { return _img; }
	void setImg(image* img) { _img = img; }

	int getIdxX() { return _idxX; }
	void setIdxX(int idxX) { _idxX = idxX; }

	int getidxY() { return _idxY; }
	void setIdY(int idxY) { _idxY = idxY; }

};

