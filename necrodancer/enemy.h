#pragma once
#include "parentObj.h"

enum DIRECTION
{
	DIRECITON_NONE,
	DIRECTION_LEFT,
	DIRECTION_RIGHT,
	DIRECTION_UP,
	DIRECTION_DOWN
};

enum TILE_MOVE_WAY
{
	TILE_MOVE_WAY_NONE,
	TILE_MOVE_WAY_START,
	TILE_MOVE_WAY_END,
	TILE_MOVE_WAY_WALL
};

enum ASTAR_STATE
{
	ASTAR_STATE_SEARCHING,
	ASTAR_STATE_FOUND,
	ASTAR_STATE_NOWAY,
	ASTAR_STATE_END
};

typedef struct tagAStarTile
{
	D2D1_RECT_F rc;
	bool isWalk;
	bool listOn;
	int i;
	int j;
	int F;
	int G; 
	int H;
	char str[128];
	tagAStarTile* parent;
	TILE_MOVE_WAY moveWay;
}aStarTile;

class enemy : public parentObj
{
protected:

	vector<vector<aStarTile>> _vvTile;	
	vector<aStarTile*> _openList;
	vector<aStarTile*> _closeList;

	ASTAR_STATE _aStarState;
	TILE_MOVE_WAY _tileMoveWay;
	DIRECTION _direction;
	DIRECTION _move;

	animation* _ani;

	int _heart;						//ü��
	int _maxHeart;					//�ִ�ü��
	int _damage;					//���ݷ�
	int _count;						//�����ӿ� ī��Ʈ
	int _isLeft;					//���ʺ����ִ���?

	int _gravity;					//�߷°�
	int _jumpPower;					//��������
	float _speed;

	int _maxFrameX;					//�ִ�������X
	int _maxFrameY;					//�ִ�������Y

	int _posX;
	int _posY;
	float _posZ;
	int _subX;						//��ġ������X
	int _subY;						//��ġ������Y
	int _moveLoad;					//������ġ
	int _moveDistance;				//�̵�ī��Ʈ

	int _moveBeat;					//�����Ӱ��ɺ�Ʈ
	int _curMoveBeat;				//�����Ʈ

	int _startX;
	int _startY;
	int _endX;
	int _endY;
	int _lastIndex;

	bool _isDrawHP;
	bool _isHalfMove;

	bool _startPoint; 
	bool _endPoint; 

	int _closeI;
	int _closeJ;
	int _closeGoal;




public:
	enemy();
	~enemy();


	HRESULT init(string imgName, int idxX, int idxY); 
	void release();					   
	void update();					   
	void render();					   

	//=======================================================

	void aniEnemy();
	void moveEnemy();
	void attackEnemy(DIRECTION dir);
	void hitEnemy(int damage);
	void dieEnemy();
	void jumpMoveEnemy();

	void rendomMove();
	void patternMove();
	bool aStarLoad();

	void initTile();
	void addOpenList();
	void addCloseList();
	void calculateH();
	void calculateF();
	void checkArrive();

	void soundAtt();
	void soundHit();
	void soundCry();
	void soundDie();

	void horizonSet();
	void verticalSet();

	virtual void setIsSaw() {

		if (_isSaw == false)
		{
			soundCry();
			_isSaw = true;
		}
	}
};

