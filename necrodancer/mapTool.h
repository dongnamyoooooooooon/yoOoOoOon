#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "itemInfomation.h"
#include "enemyInfomation.h"
#include <vector>
#include <assert.h>


//���̸�
enum MAP_NAME
{
	MAP_NAME_TEST,					//�׽�Ʈ��
	MAP_NAME_LOBBY,					//�κ�
	MAP_NAME_TUTORIAL,				//Ʃ�丮��
	MAP_NAME_ZONE1,					//��1
	MAP_NAME_ZONE2,					//��2
	MAP_NAME_BOSS,					//������

	MAP_NAME_NONE,
	MAP_NAME_COUNT = MAP_NAME_NONE
};

enum MAPTOOL_BUTTON
{
	MAPTOOL_BUTTON_FLOOR,
	MAPTOOL_BUTTON_WALL,
	MAPTOOL_BUTTON_ENEMY,
	MAPTOOL_BUTTON_TRAP,
	MAPTOOL_BUTTON_ITEM,
	MAPTOOL_BUTTON_ETC,
	MAPTOOL_BUTTON_NAME,
	MAPTOOL_BUTTON_PREV,
	MAPTOOL_BUTTON_NEXT,
	MAPTOOL_BUTTON_SAVE,
	MAPTOOL_BUTTON_LOAD,
	MAPTOOL_BUTTON_PLAY,
	MAPTOOL_BUTTON_LOBBY,
	MAPTOOL_BUTTON_SIZE,
	MAPTOOL_BUTTON_SIZE_WIDTH_UP,
	MAPTOOL_BUTTON_SIZE_WIDTH_DOWN,
	MAPTOOL_BUTTON_SIZE_HEIGHT_UP,
	MAPTOOL_BUTTON_SIZE_HEIGHT_DOWN,

	MAPTOOL_BUTTON_NONE,
	MAPTOOL_BUTTON_COUNT = MAPTOOL_BUTTON_NONE

};

//��ư�̸�
static string BUTTON_NAME[MAPTOOL_BUTTON_COUNT] = { "button_floor",			"button_wall",			"button_enemy",
													"button_trap",			"button_shrine",		"button_container",		"button_name",
													"button_name_prev",		"button_name_next",		"button_save",			"button_load",
													"button_play",			"button_lobby",			"button_size",			"button_size_x_up",
													"button_size_x_down",	"button_size_y_up",		"button_size_y_down" };

//�����̸�
static string MAP_NAME_INFO[MAP_NAME_COUNT] = { "test_Dungeon", "lobby_Dungeon", "tutorial_Dungeon",
												"zone1_Dungeon", "zone2_Dungeon", "boss_Dungeon" };



//����Ÿ��
struct tagSampleTile
{
	D2D1_RECT_F sampleRC;					//��Ʈ
	int			frameX;						//������ X
	int			frameY;						//������ Y
};

//����Ÿ��
struct tagCurrentTile
{
	bool		isObj = false;				//�� ���� ������ ����
	int			curX = 0;					//������ X
	int			curY = 0;					//������ Y
};

//��Ÿ
struct tagETC
{
	image*		img;						 //�̹���
	D2D1_RECT_F rc;							 //��Ʈ
	int			curFrameY;					 //������
};


class parentObj;

class mapTool : public gameNode
{
private:
	//����Ÿ�� �迭
	tagSampleTile				_sampleTile[SAMPLETILE][SAMPLETILE];

	//���� ������ ����Ÿ��
	tagCurrentTile				_curPickTile;

	//����� Ÿ��(mask��)
	tagTile						_saveTile;

	//��ư
	tagETC						_button[MAPTOOL_BUTTON_COUNT];			//��ư �迭
	tagETC						_sampleWindow;							//����Ÿ�� ���
	tagETC						_prevButton;							//����Ÿ�� �̹��������ư
	tagETC						_nextButton;							//����Ÿ�� �̹��������ư
	tagETC						_rendomButton;							//����Ÿ�� ����
	tagETC						_floorButton;							//�ٴ� �׸��� ����
	tagETC						_eraseButton;							//����� ��ư

	//��ư�̸�
	MAPTOOL_BUTTON				_buttonName;

	//���ߺ���
	vector<vector<tagTile*>>	_vvTile;			//�� ���� ������ ����
	vector<vector<D2D1_RECT_F>> _vvRECT;			//��Ʈ ������ ����

	vector<parentObj>			_vObj;
	vector<parentObj>::iterator _viObj;

	//���ù���̵��� ����Ʈ
	POINT						_curPoint;

	//UINT
	UINT						_tileX;				//��ũ��X
	UINT						_tileY;				//��ũ��Y
	UINT						_savePointX;		//�巡�׿� X
	UINT						_savePointY;		//�巡�׿� Y
	UINT						_saveSampleX;		//���õ巡�׿� X
	UINT						_saveSampleY;		//���õ巡�׿� Y
	UINT						_drawSampleX;		//���ñ׸���(�巡��)�� X
	UINT						_drawSampleY;		//���ñ׸���(�巡��)�� Y

	//int
	int							_curImgNum;			//���� �̹��� ��ȣ
	int							_curMapNum;			//���� �ʹ�ȣ
	int							_curButtonNum;		//���� ��ư ��ȣ
	int							_count;				//������ī��Ʈ��
	int							_frameX;
	int							_frameY;

	//BOOLEAN
	bool						_isTileClick;		//Ÿ��Ŭ���ߴ�?
	bool						_isEnter;			//�����ƴ�?
	bool						_isOnTheImg;		//�����̹����ִ�?
	bool						_isDrag;			//â �����̰� �ִ�?
	bool						_isClick;			//��ư ������?

	//���̺����� ��Ʈ������
	map<MAP_NAME, string>		_mSizeMapNames;		//�ʻ�����
	map<MAP_NAME, string>		_mDataMapNames;		//�ʵ�����


	//�׽����
	bool						_isTest;
	parentObj					_selectObj;
	int							_choiceNum;

public:
	mapTool();
	~mapTool();

	HRESULT init();
	void release();
	void update();
	void render();


	// ================================
//				�� ư
// ================================
	void initButton();				//��ư �ʱ⼳��
	void choiceButton();			//��ư ����
	void activeButton(int num);		//��ư �������� ����


	// ================================
	//			  �� �� Ÿ ��
	// ================================
	void initSampleTile();			//����Ÿ�� �ʱ⼳��
	void additionOption();			//����Ÿ�� �̹�������
	void pickSampleTile();			//����Ÿ�Ͽ��� Ÿ�ϼ���
	void dragSampleTile();			//����Ÿ�� �巡��


	// ================================
	//			  �� & Ÿ ��
	// ================================
	void setTile();					//Ÿ�ϼ���
	void drawTile();				//������ Ÿ�� �׸���
	void drawTile_terrain();		//����
	void drawTile_object_01();		//������Ʈ
	void drawTile_object_02();		//ȶ��
	void mapSizeChange();			//�ʻ����� ����
	void loadSetTile();
	void eraseTile();


	// ================================
	//		  S A V E & L O A D
	// ================================	
	void mapSave(int mapNum);		//�ʼ��̺�
	void mapLoad();					//�ʷε�
	void initMapLoad();				//�ʷε�

	// ================================
	//			   �� �� ��
	// ================================	
	void initMapName();				//���̸�����

	// ================================
	//			 R E N D E R
	// ================================
	void drawMap();						//�����
	void drawUI();						//����UI����
	void drawSample(int num);				//����Ÿ��

private:
	// ================================
	//			�� �� �� ��
	// ================================



};

