#pragma once
#include "gameNode.h"
#include "infomation.h"




class parentObj : public gameNode
{
protected:
	image*			_img;			//이미지					
	string			_imgName;		//이미지키값
	OBJECT_TYPE		_objType;		//오브젝트타입
	ITEM_TYPE		_itemKind;		//아이템종류

	POINTF			_pos;			//실제위치(안쓴다)
	D2D1_RECT_F		_rc;			//렉트

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
	int				_appValue;		//적용값
	int				_idxX;
	int				_idxY;

	bool			_isTorch;		//횃불 가지고있는지?
	bool			_isBeat;		//비트에 맞췄는지?
	bool			_hasLight;		//불빛을 가지고 있는지?
	bool			_isSight;		//플레이어 시야 안에 있는지?
	bool			_isSaw;			//플레이어에게 보여졌는지?
	
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

	//세이브로드용
	tagTilePack makeSave();
	void makeLoad(tagTilePack* pack);

	//아이템
	virtual bool useItem(int idxX, int idxY, int dir) { return false; }
	virtual void setXY(int x, int y) { this->_posX = x; this->_posY = y; }
	virtual void setIsCurInven(bool check) { _isCurInven = check; }
	virtual void setIsMoveInven(bool check) { _isMoveInven = check; }
	virtual void setItemInven(int x, int y) {};	//바닥에서 인벤으로
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

