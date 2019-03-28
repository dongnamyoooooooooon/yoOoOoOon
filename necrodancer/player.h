#pragma once
#include "parentObj.h"

#define PLAYER_SPEED		250.0f
#define JUMPPOWER			250.0f
#define UNMOVEJUMP			350.0f
#define GRAVETY				1350.0f

#define ANISPEED			8


enum PLAYER_STATE
{
	PLAYER_STATE_IDLE,
	PLAYER_STATE_JUMP_LEFT,
	PLAYER_STATE_JUMP_RIGHT,
	PLAYER_STATE_JUMP_UP,
	PLAYER_STATE_JUMP_DOWN
};

struct tagInven
{
	POINTF pos;
	string UIKey;
	parentObj* object;
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
	UINT					_tileX;							//�÷��̾ �ִ� Ÿ��X
	UINT					_tileY;							//�÷��̾ �ִ� Ÿ��Y
	PLAYER_STATE			_playerState;					//�÷��̾� ����


	animation*				_playerHead_Ani;				//�ִϸ��̼�
	animation*				_playerBody_Ani;
	bool					_isLeft;						//���ʺ���?
	bool					_isMove;						//�����̴���?
	


	D2D1_RECT_F				_rc;
	float					_posX;							//�÷��̾���ġ
	float					_posY;							//�÷��̾���ġ
	float					_posZ;							//����
	float					_moveDistance;					//�̵��Ÿ�
	float					_jumpPower;						//��������
	float					_gravity;						//�߷�
	float					_speed;							//�ӵ�

	string					_playerHead;					//�÷��̾�Ű��
	string					_playerBody;					//�÷��̾�Ű��
	string					_curArmor;						//���簩��

	tagInven				_inven[9];						//�κ��丮
	tagPlayerStat			_playerStat;					//����

public:
	player();
	~player();

	HRESULT init(UINT idx_X, UINT idx_Y);
	void release();
	void update();
	void render();


	void playerAniSetUp();
	void playerAniStart_Head(string keyName);
	void playerAniStart_Body(string keyName);
	void drawBody();
	void drawHead();
};


