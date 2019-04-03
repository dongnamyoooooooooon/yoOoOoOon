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

	int _heart;						//체력
	int _maxHeart;					//최대체력
	int _damage;					//공격력
	int _count;						//프레임용 카운트
	int _isLeft;					//왼쪽보고있는지?

	int _gravity;					//중력값
	int _jumpPower;					//점프빠워
	float _speed;

	int _maxFrameX;					//최대프레임X
	int _maxFrameY;					//최대프레임Y

	int _posX;
	int _posY;
	float _posZ;
	int _subX;						//위치보정용X
	int _subY;						//위치보정용Y
	int _moveLoad;					//다음위치
	int _moveDistance;				//이동카운트

	int _moveBeat;					//움직임가능비트
	int _curMoveBeat;				//현재비트

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

