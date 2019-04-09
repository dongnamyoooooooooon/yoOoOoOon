#pragma once
#include "parentObj.h"

#define PLAYER_SPEED		250.0f
#define JUMPPOWER			250.0f
#define UNMOVEJUMP			350.0f
#define GRAVETY				1350.0f

#define ANISPEED			8


enum PLAYER_STATE
{
	PLAYER_STATE_NONE,
	PLAYER_STATE_JUMP_LEFT,
	PLAYER_STATE_JUMP_RIGHT,
	PLAYER_STATE_JUMP_UP,
	PLAYER_STATE_JUMP_DOWN
};

struct tagInven
{
	POINT pos;
	string UIKey;
	parentObj* object;
	bool isUse;
};

struct tagPlayerStat
{
	UINT heart		= 19;		//하트
	UINT maxHeart	= 20;		//최대하트
	UINT coin		= 0;		//돈
	UINT defence	= 0;		//방어력
	UINT attack		= 0;		//피해데미지
	UINT shovelPower = 0;		//삽데미지
	bool isLive = true;			//죽었니?
	int	 attackCount = 0;		//공격횟수(소리용)
	int	 torchLight = 2;		//밝기		
};


class player : public parentObj
{
private:
	UINT					_tempX;
	UINT					_tempY;
	PLAYER_STATE			_playerState;					//플레이어 상태
	PLAYER_STATE			_attDir;


	animation*				_playerHead_Ani;				//애니메이션
	animation*				_playerBody_Ani;
	bool					_isLeft;						//왼쪽보니?
	bool					_isMove;						//움직이는지?
	bool					_isPress;						//눌렀는지?
	bool					_isHit;							//맞았는지?
	bool					_isUseShovel;
	bool					_isQuakeCamera;
	bool					_isLong;
	int						_count;

	D2D1_RECT_F				_rc;
	int						_posX;							//플레이어위치
	int						_posY;							//플레이어위치
	int						_posZ;							//점프
	int						_moveDistance;					//이동거리
	float					_jumpPower;						//점프빠워
	float					_gravity;						//중력
	float					_speed;							//속도

	string					_playerHead;					//플레이어키값
	string					_playerBody;					//플레이어키값
	string					_playerLute;					//플레이어키값
	string					_curArmor;						//현재갑옷

	tagInven				_inven[9];						//인벤토리
	tagPlayerStat			_playerStat;					//스탯

	int						_heartBeat;						//플레이어 하트 두근두근
	int						_heartBeatCount;

	//플레이어 장착템
	parentObj*			_playerShovel;
	parentObj*			_playerWeapon;
	parentObj*			_playerArmor;
	parentObj*			_playerHeadWear;
	parentObj*			_playerFootWear;
	parentObj*			_playerTorch;
	parentObj*			_playerItem;
	parentObj*			_playerBomb;

	parentObj*			_putObj = nullptr;
	

	//레이캐스트용
	float				_playerX;
	float				_playerY;
	
	float				_layValue;
	float				_layMax;
	float				_radius;
	float				_angle;
	
	int					_subX;
	int					_subY;
	

public:
	player();
	~player();

	HRESULT init(UINT idx_X, UINT idx_Y);
	void release();
	void update();
	void render();

	void playerDead();	//플레이어 죽음
	void layCast();


	//=======================================
	//			 키 애 니 메 이 션
	//=======================================
	void playerAniSetUp();
	void playerAniStart_Head(string keyName);
	void playerAniStart_Body(string keyName);
	void playerAniStart_BodyLute(string keyName);
	void drawBody();
	void drawHead();
	void drawShadow();

	//=======================================
	//					키
	//=======================================
	void keyUpdate();
	void playerStateUpdate(bool check);
	void horizonSet();
	void verticalSet();
	bool checkMove();



	//=======================================
	//					U I
	//=======================================
	void initEquipUI();
	void setEquipUI(parentObj* obj);
	void brokenItemEquipUI();
	void drawPlayerUI();
	void drawEquipUI();
	void bounceHeart();


	//=======================================
	//				  아 이 템
	//=======================================
	void initItem();
	void putItem(parentObj* obj);	//아이템떨어짐
	void addInven(parentObj* obj);	//아이템 인벤으로
	void drawItemHint();
	void hitPlayer(int damage);		//맞았을때
	void equipUpdate();


	void setjump(PLAYER_STATE state)
	{
		_isMove = false;
		_playerState = state;
		_moveDistance = 52;
	}

	void setHeart(int heart)
	{
		int temp = _playerStat.heart + heart;
		if (temp > _playerStat.maxHeart) _playerStat.heart = _playerStat.maxHeart;
		else _playerStat.heart = temp;
	}

	int getPlayerPosX() { return _posX; }
	int getPlayerPosY() { return _posY; }

	void setPlayerPosX(int posX) { _posX = posX; }
	void setPlayerPosY(int posY) { _posY = posY; }
	void setPlayerPos(int posX, int posY) { _posX = posX, _posY = posY; }

	//bool getIsMove() { return _isMove; }
	void setIsMove(bool check) { _isMove = check; }

	bool getIsPress() { return _isPress; }
	void setIsPress(bool check) { _isPress = check; }

	PLAYER_STATE getPlayerState() { return _playerState; }
	void setPlayerState(PLAYER_STATE state) { _playerState = state; }

	bool getIsMove();

	int getMoveDistance() { return _moveDistance; }

	PLAYER_STATE getAttDir() { return _attDir; }
	void setAttDir(PLAYER_STATE state) { _attDir = state; }

	bool getIsHit() { return _isHit; }
	void setIsHit(bool check) { _isHit = check; }

	bool getIsUseShovel() { return _isUseShovel; }
	void setIsUseShovel(bool check) { _isUseShovel = check; }

	parentObj* getPlayerShovel() { return _playerShovel; }
	parentObj* getPlayerWeapon() { return _playerWeapon; }

	bool getIsQuakeCamera() { return _isQuakeCamera; }
	void setIsQuakeCamera(bool check) { _isQuakeCamera = check; }

	bool getIsLong() { return _isLong; }
	void setIsLong(bool check) { _isLong = check; }

};


