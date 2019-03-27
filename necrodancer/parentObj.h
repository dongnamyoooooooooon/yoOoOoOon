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
	image*			_img;			//�̹���					
	string			_imgName;		//�̹���Ű��
	OBJECT_TYPE		_objType;		//������ƮŸ��
	POINTF			_pos;			//������ġ
	D2D1_RECT_F		_rc;			//��Ʈ

	
	int				_frameX;
	int				_frameY;
	int				_count = 0;
	int				_appValue;		//���밪
	int				_idxX;
	int				_idxY;

	bool			_isTorch;		//ȶ�� �������ִ���?
	bool			_isBeat;		//��Ʈ�� �������?
	bool			_hasLight;		//�Һ��� ������ �ִ���?
	bool			_isSight;		//�÷��̾� �þ� �ȿ� �ִ���?
	bool			_isSaw;			//�÷��̾�� ����������?
	




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

