#pragma once
#include "gameNode.h"
#include "infomation.h"




class parentObj : public gameNode
{
protected:
	image*			_img;			//�̹���					
	string			_imgName;		//�̹���Ű��
	OBJECT_TYPE		_objType;		//������ƮŸ��
	ITEM_TYPE		_itemKind;		//����������

	POINTF			_pos;			//������ġ(�Ⱦ���)
	D2D1_RECT_F		_rc;			//��Ʈ

	UINT			_imgKey;
	UINT			_itemType;
	UINT			_itemSubType;

	int				_posX;
	int				_posY;

	UINT			_tileX;
	UINT			_tileY;

	int				_appliedValue;
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
	
	bool			_isCurInven;
	bool			_isMoveInven;



public:
	parentObj();
	~parentObj();

	virtual HRESULT init(string imgName, int idx_X, int idx_Y, OBJECT_TYPE type, UINT key);
	virtual HRESULT init(string imgName, int idx_X, int idx_Y, OBJECT_TYPE type, UINT key, ITEM_TYPE itemtype);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void render(float x, float y, int frameX = 0);

	//���̺�ε��
	tagTilePack makeSave();
	void makeLoad(tagTilePack* pack);

	//������
	virtual bool useItem(int idxX, int idxY, int dir) { return false; }
	virtual void setXY(int x, int y) { this->_posX = x; this->_posY = y; }
	virtual void setIsCurInven(bool check) { _isCurInven = check; }
	virtual void setIsMoveInven(bool check) { _isMoveInven = check; }
	virtual void setItemInven(int x, int y) {};	//�ٴڿ��� �κ�����
	virtual void drawHint() {};

	/*string makeSaveInfo();
	void loadSaveInfo(string* data);*/

	
	//=======================================
	//			  g e t & s e t
	//=======================================

	int getPosX() { return _posX; }
	int getPosY() { return _posY; }


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

	int getIdxY() { return _idxY; }
	void setIdxY(int idxY) { _idxY = idxY; }

	UINT getImgKey() { return _imgKey; }
	void setImgKey(UINT key) { _imgKey = key; }

	UINT getItemType() {return _itemType;}
	void setItemType(UINT type) { _itemType = type; }

	POINTF getPos() { return _pos; }
	void setPos(POINTF pos) { _pos = pos; }

	ITEM_TYPE getItemKind() { return _itemKind; }
	void setItemKind(ITEM_TYPE type) { _itemKind = type; }

	void setTileX(UINT x) { _tileX = x; }
	void setTileY(UINT y) { _tileY = y; }

	int getFrameX() { return _frameX; }
	void setFrameX(int frameX) { _frameX = frameX; }

	int getFrameY() { return _frameY; }
	void setFrameY(int frameY) { _frameY = frameY; }

	void setHasLight(bool check) { _hasLight = check; }
	void setIsSight(bool check) { _isSight = check; }
	void setIsSaw() { _isSaw = true; }
	bool getIsSight() { return _isSight; }

	int getAppliedValue() { return _appliedValue; }

};

