#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "itemInfomation.h"
#include "enemyInfomation.h"
#include <vector>
#include <assert.h>


//맵이름
enum MAP_NAME
{
	MAP_NAME_TEST,					//테스트맵
	MAP_NAME_LOBBY,					//로비
	MAP_NAME_TUTORIAL,				//튜토리얼
	MAP_NAME_ZONE1,					//존1
	MAP_NAME_ZONE2,					//존2
	MAP_NAME_BOSS,					//보스존

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

//버튼이름
static string BUTTON_NAME[MAPTOOL_BUTTON_COUNT] = { "button_floor",			"button_wall",			"button_enemy",
													"button_trap",			"button_shrine",		"button_container",		"button_name",
													"button_name_prev",		"button_name_next",		"button_save",			"button_load",
													"button_play",			"button_lobby",			"button_size",			"button_size_x_up",
													"button_size_x_down",	"button_size_y_up",		"button_size_y_down" };

//던전이름
static string MAP_NAME_INFO[MAP_NAME_COUNT] = { "test_Dungeon", "lobby_Dungeon", "tutorial_Dungeon",
												"zone1_Dungeon", "zone2_Dungeon", "boss_Dungeon" };



//샘플타일
struct tagSampleTile
{
	D2D1_RECT_F sampleRC;					//렉트
	int			frameX;						//프레임 X
	int			frameY;						//프레임 Y
};

//현재타일
struct tagCurrentTile
{
	bool		isObj = false;				//젤 먼저 찍을건 지형
	int			curX = 0;					//프레임 X
	int			curY = 0;					//프레임 Y
};

//기타
struct tagETC
{
	image*		img;						 //이미지
	D2D1_RECT_F rc;							 //렉트
	int			curFrameY;					 //프레임
};


class parentObj;

class mapTool : public gameNode
{
private:
	//샘플타일 배열
	tagSampleTile				_sampleTile[SAMPLETILE][SAMPLETILE];

	//현재 선택한 샘플타일
	tagCurrentTile				_curPickTile;

	//저장될 타일(mask용)
	tagTile						_saveTile;

	//버튼
	tagETC						_button[MAPTOOL_BUTTON_COUNT];			//버튼 배열
	tagETC						_sampleWindow;							//샘플타일 배경
	tagETC						_prevButton;							//샘플타일 이미지변경버튼
	tagETC						_nextButton;							//샘플타일 이미지변경버튼
	tagETC						_rendomButton;							//샘플타일 랜덤
	tagETC						_floorButton;							//바닥 그리기 설정
	tagETC						_eraseButton;							//지우기 버튼

	//버튼이름
	MAPTOOL_BUTTON				_buttonName;

	//이중벡터
	vector<vector<tagTile*>>	_vvTile;			//맵 내용 저장할 벡터
	vector<vector<D2D1_RECT_F>> _vvRECT;			//렉트 보여줄 벡터

	vector<parentObj>			_vObj;
	vector<parentObj>::iterator _viObj;

	//샘플배경이동용 포인트
	POINT						_curPoint;

	//UINT
	UINT						_tileX;				//맵크기X
	UINT						_tileY;				//맵크기Y
	UINT						_savePointX;		//드래그용 X
	UINT						_savePointY;		//드래그용 Y
	UINT						_saveSampleX;		//샘플드래그용 X
	UINT						_saveSampleY;		//샘플드래그용 Y
	UINT						_drawSampleX;		//샘플그리기(드래그)용 X
	UINT						_drawSampleY;		//샘플그리기(드래그)용 Y

	//int
	int							_curImgNum;			//현재 이미지 번호
	int							_curMapNum;			//현재 맵번호
	int							_curButtonNum;		//현재 버튼 번호
	int							_count;				//프레임카운트용
	int							_frameX;
	int							_frameY;

	//BOOLEAN
	bool						_isTileClick;		//타일클릭했니?
	bool						_isEnter;			//엔터쳤니?
	bool						_isOnTheImg;		//샘플이미지있니?
	bool						_isDrag;			//창 움직이고 있니?
	bool						_isClick;			//버튼 눌렀니?

	//세이브파일 스트링벡터
	map<MAP_NAME, string>		_mSizeMapNames;		//맵사이즈
	map<MAP_NAME, string>		_mDataMapNames;		//맵데이터


	//테슷흐용
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
//				버 튼
// ================================
	void initButton();				//버튼 초기설정
	void choiceButton();			//버튼 선택
	void activeButton(int num);		//버튼 눌렀을때 설정


	// ================================
	//			  샘 플 타 일
	// ================================
	void initSampleTile();			//샘플타일 초기설정
	void additionOption();			//샘플타일 이미지변경
	void pickSampleTile();			//샘플타일에서 타일선택
	void dragSampleTile();			//샘플타일 드래그


	// ================================
	//			  맵 & 타 일
	// ================================
	void setTile();					//타일세팅
	void drawTile();				//선택한 타일 그리기
	void drawTile_terrain();		//지형
	void drawTile_object_01();		//오브젝트
	void drawTile_object_02();		//횃불
	void mapSizeChange();			//맵사이즈 변경
	void loadSetTile();
	void eraseTile();


	// ================================
	//		  S A V E & L O A D
	// ================================	
	void mapSave(int mapNum);		//맵세이브
	void mapLoad();					//맵로드
	void initMapLoad();				//맵로드

	// ================================
	//			   맵 이 름
	// ================================	
	void initMapName();				//맵이름설정

	// ================================
	//			 R E N D E R
	// ================================
	void drawMap();						//맵출력
	void drawUI();						//맵툴UI관련
	void drawSample(int num);				//샘플타일

private:
	// ================================
	//			내 부 함 수
	// ================================



};

