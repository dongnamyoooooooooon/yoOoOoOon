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
	UINT heart		= 19;		//��Ʈ
	UINT maxHeart	= 20;		//�ִ���Ʈ
	UINT coin		= 0;		//��
	UINT defence	= 0;		//����
	UINT attack		= 0;		//���ص�����
	UINT shovelPower = 0;		//�𵥹���
	bool isLive = true;			//�׾���?
	int	 attackCount = 0;		//����Ƚ��(�Ҹ���)
	int	 torchLight = 2;		//���		
};


class player : public parentObj
{
private:
	UINT					_tempX;
	UINT					_tempY;
	PLAYER_STATE			_playerState;					//�÷��̾� ����
	PLAYER_STATE			_attDir;


	animation*				_playerHead_Ani;				//�ִϸ��̼�
	animation*				_playerBody_Ani;
	bool					_isLeft;						//���ʺ���?
	bool					_isMove;						//�����̴���?
	bool					_isPress;						//��������?
	bool					_isHit;							//�¾Ҵ���?
	bool					_isUseShovel;
	bool					_isQuakeCamera;
	bool					_isLong;
	int						_count;

	D2D1_RECT_F				_rc;
	int						_posX;							//�÷��̾���ġ
	int						_posY;							//�÷��̾���ġ
	int						_posZ;							//����
	int						_moveDistance;					//�̵��Ÿ�
	float					_jumpPower;						//��������
	float					_gravity;						//�߷�
	float					_speed;							//�ӵ�

	string					_playerHead;					//�÷��̾�Ű��
	string					_playerBody;					//�÷��̾�Ű��
	string					_playerLute;					//�÷��̾�Ű��
	string					_curArmor;						//���簩��

	tagInven				_inven[9];						//�κ��丮
	tagPlayerStat			_playerStat;					//����

	int						_heartBeat;						//�÷��̾� ��Ʈ �αٵα�
	int						_heartBeatCount;

	//�÷��̾� ������
	parentObj*			_playerShovel;
	parentObj*			_playerWeapon;
	parentObj*			_playerArmor;
	parentObj*			_playerHeadWear;
	parentObj*			_playerFootWear;
	parentObj*			_playerTorch;
	parentObj*			_playerItem;
	parentObj*			_playerBomb;

	parentObj*			_putObj = nullptr;
	

	//����ĳ��Ʈ��
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

	void playerDead();	//�÷��̾� ����
	void layCast();


	//=======================================
	//			 Ű �� �� �� �� ��
	//=======================================
	void playerAniSetUp();
	void playerAniStart_Head(string keyName);
	void playerAniStart_Body(string keyName);
	void playerAniStart_BodyLute(string keyName);
	void drawBody();
	void drawHead();
	void drawShadow();

	//=======================================
	//					Ű
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
	//				  �� �� ��
	//=======================================
	void initItem();
	void putItem(parentObj* obj);	//�����۶�����
	void addInven(parentObj* obj);	//������ �κ�����
	void drawItemHint();
	void hitPlayer(int damage);		//�¾�����
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


