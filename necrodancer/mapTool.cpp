#include "stdafx.h"
#include "mapTool.h"
#include "parentObj.h"


mapTool::mapTool()
{
}


mapTool::~mapTool()
{
}

HRESULT mapTool::init()
{
	CAMERA->init(0, 0, 2400, 2400);					//카메라 초기설정

	//맵크기 설정
	_tileX = 40;
	_tileY = 40;

	SOUNDMANAGER->allSoundStop();

	_vvTile.clear();
	_vvRECT.clear();
	_vObj.clear();

	SOUNDMANAGER->play("mapTool");

	_selectObj.init("", 0, 0, OBJECT_TYPE_NONE);

	//==================================================



	//boolean
	_isTileClick = false;
	_isOnTheImg = false;
	_isEnter = false;

	_curImgNum = 0;									//현재 선택한 이미지번호
	_curMapNum = MAP_NAME_TEST;						//현재맵

	initButton();									//버튼 초기설정
	initSampleTile();								//샘플타일 초기설정
	initMapName();									//맵이름 초기설정
	setTile();										//타일 초기설정

	initMapLoad();


	return S_OK;
}

void mapTool::release()
{
}

void mapTool::update()
{
	CAMERA->mapToolMove();								//카메라이동
	choiceButton();										//버튼선택

	if (_isOnTheImg)									//샘플타일이 보여진다면
	{
		pickSampleTile();								//샘플타일에서 타일선택
		dragSampleTile();								//샘플타일창 이동
		additionOption();								//부가옵션
		drawTile();										//선택한 타일 그리기

		if (_eraseButton.curFrameY == 1) eraseTile();	//타일지우기
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F1))	this->mapSave(_curMapNum);
	if (KEYMANAGER->isOnceKeyDown(VK_F2))	this->mapLoad();
}

void mapTool::render()
{
	WCHAR str[128];

	//배경
	IMAGEMANAGER->findImage("maptoolbackground")->render(CAMERA->getPosX() + WINSIZEX - 240, CAMERA->getPosY() + 0, 0.8f);

	drawMap();				//맵출력
	drawUI();				//맵툴UI관련
	drawSample(_choiceNum);			//샘플타일
}

void mapTool::initButton()
{
	for (int i = 0; i < MAPTOOL_BUTTON_COUNT; i++)
	{

		if (i < MAPTOOL_BUTTON_PREV)					// i < 8		
			_button[i].rc = { (float)WINSIZEX - 240, (float)40 + (30 * i),		(float)WINSIZEX - 80,	(float)70 + (30 * i) };
		else if (i == MAPTOOL_BUTTON_PREV)				// i == 8  (왼쪽버튼)
			_button[i].rc = { (float)WINSIZEX - 240, (float)280,				(float)WINSIZEX - 210,	(float)310 };
		else if (i == MAPTOOL_BUTTON_NEXT)				// i == 9  (오른쪽버튼)
			_button[i].rc = { (float)WINSIZEX - 30,	 (float)280,				(float)WINSIZEX,		(float)310 };
		else if (i == MAPTOOL_BUTTON_SIZE_WIDTH_UP)		// i == 15 (가로사이즈 증가)
			_button[i].rc = { (float)WINSIZEX - 210, (float)490,				(float)WINSIZEX - 170,	(float)510 };
		else if (i == MAPTOOL_BUTTON_SIZE_WIDTH_DOWN)	// i == 16 (가로사이즈 감소)
			_button[i].rc = { (float)WINSIZEX - 70,  (float)490,				(float)WINSIZEX - 30,	(float)510 };
		else if (i == MAPTOOL_BUTTON_SIZE_HEIGHT_UP)	// i == 17 (세로사이즈 증가)
			_button[i].rc = { (float)WINSIZEX - 140, (float)470,				(float)WINSIZEX - 100,	(float)490 };
		else if (i == MAPTOOL_BUTTON_SIZE_HEIGHT_DOWN)	// i == 18 (세로사이즈 감소)
			_button[i].rc = { (float)WINSIZEX - 140, (float)510,				(float)WINSIZEX - 100,	(float)530 };
		else											// 그 외
			_button[i].rc = { (float)WINSIZEX - 240, (float)40 + (30 * i) - 30,	(float)WINSIZEX - 80,	(float)70 + (30 * i) - 30 };
		if (i != 0) _button[i].curFrameY = 0;
	}
	_curButtonNum = MAPTOOL_BUTTON_FLOOR;	//현재버튼은 '바닥놓기'
	_button[0].curFrameY = 1;				//현재버튼 프레임변경

	_button[0].img = IMAGEMANAGER->findImage(BUTTON_NAME[MAPTOOL_BUTTON_FLOOR]);				//매니저님 버튼이미지 추가해주세요^▽^
	_button[1].img = IMAGEMANAGER->findImage(BUTTON_NAME[MAPTOOL_BUTTON_WALL]);					//매니저님 버튼이미지 추가해주세요^▽^
	//_button[2].img = IMAGEMANAGER->findImage(BUTTON_NAME[MAPTOOL_BUTTON_CHEST]);				//매니저님 버튼이미지 추가해주세요^▽^
	_button[2].img = IMAGEMANAGER->findImage(BUTTON_NAME[MAPTOOL_BUTTON_ENEMY]);				//매니저님 버튼이미지 추가해주세요^▽^
	_button[3].img = IMAGEMANAGER->findImage(BUTTON_NAME[MAPTOOL_BUTTON_TRAP]);					//매니저님 버튼이미지 추가해주세요^▽^
	_button[4].img = IMAGEMANAGER->findImage(BUTTON_NAME[MAPTOOL_BUTTON_ITEM]);					//매니저님 버튼이미지 추가해주세요^▽^
	_button[5].img = IMAGEMANAGER->findImage(BUTTON_NAME[MAPTOOL_BUTTON_ETC]);					//매니저님 버튼이미지 추가해주세요^▽^
	_button[6].img = IMAGEMANAGER->findImage(BUTTON_NAME[MAPTOOL_BUTTON_NAME]);					//매니저님 버튼이미지 추가해주세요^▽^
	_button[7].img = IMAGEMANAGER->findImage(BUTTON_NAME[MAPTOOL_BUTTON_PREV]);					//매니저님 버튼이미지 추가해주세요^▽^
	_button[8].img = IMAGEMANAGER->findImage(BUTTON_NAME[MAPTOOL_BUTTON_NEXT]);					//매니저님 버튼이미지 추가해주세요^▽^
	_button[9].img = IMAGEMANAGER->findImage(BUTTON_NAME[MAPTOOL_BUTTON_SAVE]);				//매니저님 버튼이미지 추가해주세요^▽^
	_button[10].img = IMAGEMANAGER->findImage(BUTTON_NAME[MAPTOOL_BUTTON_LOAD]);				//매니저님 버튼이미지 추가해주세요^▽^
	_button[11].img = IMAGEMANAGER->findImage(BUTTON_NAME[MAPTOOL_BUTTON_PLAY]);				//매니저님 버튼이미지 추가해주세요^▽^
	_button[12].img = IMAGEMANAGER->findImage(BUTTON_NAME[MAPTOOL_BUTTON_LOBBY]);				//매니저님 버튼이미지 추가해주세요^▽^
	_button[13].img = IMAGEMANAGER->findImage(BUTTON_NAME[MAPTOOL_BUTTON_SIZE]);				//매니저님 버튼이미지 추가해주세요^▽^
	_button[14].img = IMAGEMANAGER->findImage(BUTTON_NAME[MAPTOOL_BUTTON_SIZE_WIDTH_UP]);		//매니저님 버튼이미지 추가해주세요^▽^
	_button[15].img = IMAGEMANAGER->findImage(BUTTON_NAME[MAPTOOL_BUTTON_SIZE_WIDTH_DOWN]);		//매니저님 버튼이미지 추가해주세요^▽^
	_button[16].img = IMAGEMANAGER->findImage(BUTTON_NAME[MAPTOOL_BUTTON_SIZE_HEIGHT_UP]);		//매니저님 버튼이미지 추가해주세요^▽^
	_button[17].img = IMAGEMANAGER->findImage(BUTTON_NAME[MAPTOOL_BUTTON_SIZE_HEIGHT_DOWN]);	//매니저님 버튼이미지 추가해주세요^▽^
}

void mapTool::choiceButton()
{
	if (!_isEnter)
	{
		//그리기에서 벗어났을때 움직였던 렉트들 초기화
		_isOnTheImg = false;
		_sampleWindow.rc = { 5,						475,						_sampleWindow.rc.left + 400, _sampleWindow.rc.top + 400 };
		_prevButton.rc = { _sampleWindow.rc.right, _sampleWindow.rc.top,		_sampleWindow.rc.right + 30, _sampleWindow.rc.top + 30 };
		_nextButton.rc = { _sampleWindow.rc.right, _sampleWindow.rc.top + 30, _sampleWindow.rc.right + 30, _sampleWindow.rc.top + 60 };
		_rendomButton.rc = { _sampleWindow.rc.right, _sampleWindow.rc.top + 60,	_sampleWindow.rc.right + 60, _sampleWindow.rc.top + 90 };
		_floorButton.rc = { _sampleWindow.rc.right, _sampleWindow.rc.top + 60,	_sampleWindow.rc.right + 70, _sampleWindow.rc.top + 90 };
		_eraseButton.rc = { _sampleWindow.rc.right, _sampleWindow.rc.top + 90,	_sampleWindow.rc.right + 40, _sampleWindow.rc.top + 120 };

		//아래방향키 눌렀을때
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_curButtonNum++;																				//현재버튼번호 증가
			for (int i = 0; i < MAPTOOL_BUTTON_COUNT; i++)
			{
				_button[_curButtonNum - 1].curFrameY = 0;													//이전버튼의 프레임은 0

				if (_curButtonNum == MAPTOOL_BUTTON_PREV || _curButtonNum == MAPTOOL_BUTTON_NEXT)			//현재버튼이 '왼쪽/오른쪽'버튼이면
					_curButtonNum = MAPTOOL_BUTTON_SAVE;													//'세이브'버튼으로 이동(왼/오는 마우스용)

				_button[_curButtonNum].curFrameY = 1;														//현재버튼의 프레임은 1

				if (_curButtonNum >= MAPTOOL_BUTTON_SIZE_WIDTH_UP)											//현재버튼이 '가로사이즈증가' 버튼이면
				{
					_curButtonNum = MAPTOOL_BUTTON_FLOOR;													//현재버튼은 다시 '바닥놓기'
					_button[MAPTOOL_BUTTON_SIZE_WIDTH_UP].curFrameY = 0;									//'가로사이즈증가'버튼 프레임은 0
					_button[_curButtonNum].curFrameY = 1;													//현재버튼의 프레임은 1
				}
			}
		}

		//위쪽방향키 눌렀을때
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_curButtonNum--;																				//현재버튼번호 감소
			for (int i = 0; i < MAPTOOL_BUTTON_COUNT; i++)
			{
				_button[_curButtonNum + 1].curFrameY = 0;													//이전버튼의 프레임은 0

				if (_curButtonNum == MAPTOOL_BUTTON_PREV || _curButtonNum == MAPTOOL_BUTTON_NEXT)			//현재버튼이 '왼쪽/오른쪽'버튼이면
					_curButtonNum = MAPTOOL_BUTTON_NAME;													//'던전이름'버튼으로 이동(왼/오는 마우스용)

				_button[_curButtonNum].curFrameY = 1;														//현재버튼의 프레임은 1

				if (_curButtonNum < MAPTOOL_BUTTON_FLOOR)													//현재버튼이 '바닥놓기'일때
				{
					_curButtonNum = MAPTOOL_BUTTON_SIZE;													//현재버튼은 '사이즈'버튼
					_button[_curButtonNum].curFrameY = 1;													//현재버튼의 프레임은 1
				}
			}
		}

		//엔터를 눌렀을때
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			_isEnter = true;																				//방향키 작동을 못하게 하도록 한다.
			if (_curButtonNum < MAPTOOL_BUTTON_NAME)
				_choiceNum = _curButtonNum;
			activeButton(_curButtonNum);																	//버튼을 눌렀을때 세팅해준다.

			//현재버튼이 '바닥놓기'에서부터 '던전이름'까지 이거나 '사이즈' 버튼에 있을때
			if ((_curButtonNum >= MAPTOOL_BUTTON_FLOOR && _curButtonNum < MAPTOOL_BUTTON_PREV) || _curButtonNum == MAPTOOL_BUTTON_SIZE)
				_button[_curButtonNum].curFrameY = 2;														//현재버튼의 프레임은 2
		}
	}
	else if (_isEnter && (_curButtonNum != MAPTOOL_BUTTON_SAVE || _curButtonNum != MAPTOOL_BUTTON_LOAD))	//엔터누른상태이고
	{																										//현재버튼이 '세이브','로드'가 아닐경우
		if (_curButtonNum == MAPTOOL_BUTTON_NAME)															//현재버튼이 '던전이름'에 있을때 던전이름 변경을 한다.													
		{																									//마우스로 조작
			if (PtInRect(&makeRECT(_button[MAPTOOL_BUTTON_PREV].rc), makePOINT_NoCamera(_ptMouse)))			//마우스가 '이전'버튼에 있는 상태에서
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))													//좌클릭하면
				{
					_curMapNum--;																			//현재 던전번호가 바뀌면서
					loadSetTile();																			//던전번호에 맞는 맵을 준비한다.
					_button[MAPTOOL_BUTTON_PREV].curFrameY = 1;												//누를때마다 '이전'버튼의 프레임 변경

					if (_curMapNum <= MAP_NAME_TEST)		_curMapNum = MAP_NAME_BOSS;						//값이탈방지
				}
				if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))	_button[MAPTOOL_BUTTON_PREV].curFrameY = 0;		//클릭아니면 프레임 변경
			}

			else if (PtInRect(&makeRECT(_button[MAPTOOL_BUTTON_NEXT].rc), makePOINT_NoCamera(_ptMouse)))	//마우스가 '다음'버튼에 있는 상태에서
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))													//좌클릭하면
				{
					_curMapNum++;																			//현재 던전번호가 바뀌면서
					loadSetTile();																			//던전번호에 맞는 맵을 준비한다.
					_button[MAPTOOL_BUTTON_NEXT].curFrameY = 1;												//누를때마다 '다음'버튼의 프레임 변경

					if (_curMapNum > MAP_NAME_BOSS)			_curMapNum = MAP_NAME_TEST;						//값이탈방지
				}
				if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))	_button[MAPTOOL_BUTTON_NEXT].curFrameY = 0;		//클릭아니면 프레임 변경
			}
		}
		else if (_curButtonNum == MAPTOOL_BUTTON_SIZE)		mapSizeChange();								//현재버튼이 '던전크기'에 있으면 던전크기 변경한다. 

		if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE) || KEYMANAGER->isOnceKeyDown(VK_RETURN))					//ESC나 다시 엔터를 눌렀을때
		{
			_isEnter = false;																				//이전으로 돌아간다.

			//현재버튼이 '바닥놓기'에서부터 '던전이름'까지 이거나 '사이즈' 버튼에 있을때
			if ((_curButtonNum >= MAPTOOL_BUTTON_FLOOR && _curButtonNum < MAPTOOL_BUTTON_PREV) || _curButtonNum == MAPTOOL_BUTTON_SIZE)
				_button[_curButtonNum].curFrameY = 1;														//현재버튼의 프레임은 1						
		}
	}
}

void mapTool::activeButton(int num)
{
	_curImgNum = 0;
	_choiceNum = num;
	if (num == MAPTOOL_BUTTON_SAVE)					this->mapSave(_curMapNum);								//세이브한다.
	else if (num == MAPTOOL_BUTTON_LOAD)			this->mapLoad();										//로드한다.
	else if (num == MAPTOOL_BUTTON_PLAY)			SCENEMANAGER->changeScene("testMapScene");				//씬변경하는데 외않되?

	if (num >= MAPTOOL_BUTTON_NAME && num < MAPTOOL_BUTTON_PLAY)			return;							//작동하면 안되는 버튼이면
	if (num >= MAPTOOL_BUTTON_SIZE && num < MAPTOOL_BUTTON_NONE)			return;							//돌아가라

	_isOnTheImg = true;																					//샘플타일창을 킨다.
	_curPickTile.curX = 0;																				//현재선택한타일의 좌표 초기화
	_curPickTile.curY = 0;																				//현재선택한타일의 좌표 초기화
}

void mapTool::initSampleTile()
{
	/*
		순서대로
		1. 샘플타일배경			(_sampleWindow)
		2. 샘플타일 이미지 이전	(_prevButton)
		3. 샘플타일 이미지 다음	(_nextButton)
		4. 샘플타일 랜덤그리기	(_rendomButton)
		5. 바닥 그리기 설정		(_floorButton)
		6. 지우기				(_eraseButton)
	*/

	//이미지 초기설정
	_sampleWindow.img = IMAGEMANAGER->findImage("samplebackground");
	_prevButton.img = IMAGEMANAGER->findImage("mapTool_left");
	_nextButton.img = IMAGEMANAGER->findImage("mapTool_right");
	_rendomButton.img = IMAGEMANAGER->findImage("mapTool_rendom");
	_floorButton.img = IMAGEMANAGER->findImage("mapTool_floor_choice");
	_eraseButton.img = IMAGEMANAGER->findImage("mapTool_erase");


	//RECT 초기설정
	_sampleWindow.rc = { 5,						475,						405,						875 };
	_prevButton.rc = { _sampleWindow.rc.right, _sampleWindow.rc.top,		_sampleWindow.rc.right + 30, _sampleWindow.rc.top + 30 };
	_nextButton.rc = { _sampleWindow.rc.right, _sampleWindow.rc.top + 30,	_sampleWindow.rc.right + 30, _sampleWindow.rc.top + 60 };
	_rendomButton.rc = { _sampleWindow.rc.right, _sampleWindow.rc.top + 60,	_sampleWindow.rc.right + 60, _sampleWindow.rc.top + 90 };
	_floorButton.rc = { _sampleWindow.rc.right, _sampleWindow.rc.top + 60,	_sampleWindow.rc.right + 70, _sampleWindow.rc.top + 90 };
	_eraseButton.rc = { _sampleWindow.rc.right, _sampleWindow.rc.top + 90,	_sampleWindow.rc.right + 40, _sampleWindow.rc.top + 120 };

	//샘플타일 RECT생성
	for (int i = 0; i < SAMPLETILE; i++)
	{
		for (int j = 0; j < SAMPLETILE; j++)
		{
			_sampleTile[i][j].frameX = 0;																				//프레임 초기화
			_sampleTile[i][j].frameY = 0;																				//프레임 초기화
			_sampleTile[i][j].sampleRC = { (float)j * TILE_SIZE		,(float)i * TILE_SIZE								//RECT생성
										  ,(float)j + 1 * TILE_SIZE ,(float)i + 1 * TILE_SIZE };
		}
	}
}

void mapTool::additionOption()
{
	//현재버튼이 '바닥놓기','벽놓기','사원놓기','적놓기','기타놓기'일때
	if (_curButtonNum == MAPTOOL_BUTTON_ITEM || _curButtonNum == MAPTOOL_BUTTON_ENEMY)
	{
		if (PtInRect(&makeRECT(_prevButton.rc), makePOINT_NoCamera(_ptMouse)))																	//'왼쪽'에 마우스가 있고
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))																							//좌클릭하면
			{
				--_curImgNum;																													//현재이미지번호 변경
				_prevButton.curFrameY = 1;																										//프레임 변경

				if (_curButtonNum == MAPTOOL_BUTTON_ENEMY)							_curImgNum = 0;											//값이탈방지
				else if (_curButtonNum == MAPTOOL_BUTTON_ITEM && _curImgNum < 0)		_curImgNum = 0;											//값이탈방지
				//else if (_curButtonNum == MAPTOOL_BUTTON_ETC)							_curImgNum = 0;											//값이탈방지
			}
			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) _prevButton.curFrameY = 0;																	//클릭아니면 프레임 변경
		}

		else if (PtInRect(&makeRECT(_nextButton.rc), makePOINT_NoCamera(_ptMouse)))																//'오른쪽'에 마우스가 있고
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))																							//좌클릭하면
			{
				++_curImgNum;																													//현재이미지번호 변경
				_nextButton.curFrameY = 1;																										//프레임 변경

				if (_curButtonNum == MAPTOOL_BUTTON_ENEMY)							_curImgNum = 1;											//값이탈방지
				else if (_curButtonNum == MAPTOOL_BUTTON_ITEM && _curImgNum >= 4)		_curImgNum = 4;											//값이탈방지
				//else if (_curButtonNum == MAPTOOL_BUTTON_ETC)							_curImgNum = 1;											//값이탈방지
			}
			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) _nextButton.curFrameY = 0;																	//클릭아니면 프레임 변경
		}

		else if (PtInRect(&makeRECT(_eraseButton.rc), makePOINT_NoCamera(_ptMouse)))															//'지우기'에 마우스가 있고
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))																							//좌클릭하면
			{
				if (_eraseButton.curFrameY == 0) _eraseButton.curFrameY = 1;																//프레임이 0이면 1로
				else if (_eraseButton.curFrameY == 1) _eraseButton.curFrameY = 0;																//프레임이 1이면 0으로

			}
		}
	}
	if (_curButtonNum == MAPTOOL_BUTTON_WALL)																								//현재버튼이 '벽놓기'면
	{
		if (PtInRect(&makeRECT(_rendomButton.rc), makePOINT_NoCamera(_ptMouse)))															//'랜덤'에 마우스가 있고
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))																						//좌클릭하면
			{
				if (_rendomButton.curFrameY == 0) _rendomButton.curFrameY = 1;															//프레임이 0이면 1로
				else if (_rendomButton.curFrameY == 1) _rendomButton.curFrameY = 0;															//프레임이 1이면 0으로
			}
		}
	}
	else if (_curButtonNum == MAPTOOL_BUTTON_FLOOR)																							//현재버튼이 '바닥놓기'면
	{
		if (PtInRect(&makeRECT(_floorButton.rc), makePOINT_NoCamera(_ptMouse)))																//'바닥그리기'에 마우스가 있고
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))																						//좌클릭하면
			{
				if (_floorButton.curFrameY == 0) _floorButton.curFrameY = 1;															//프레임이 0이면 1로
				else if (_floorButton.curFrameY == 1) _floorButton.curFrameY = 2;															//프레임이 1이면 2으로
				else if (_floorButton.curFrameY == 2) _floorButton.curFrameY = 0;															//프레임이 2이면 0으로
			}
		}
	}
}

void mapTool::pickSampleTile()
{
	if (PtInRect(&makeRECT(_sampleWindow.rc), makePOINT_NoCamera(_ptMouse)))
	{
		int itemCount = 0;
		int count = 0;
		int width, height;
		_viObj = _vObj.begin();

		for (_viObj; _viObj != _vObj.end(); ++_viObj)
		{
			if (_viObj->getObjType() != _choiceNum) continue;
			if (_viObj->getImg() == NULL) continue;

			if (PtInRect(&makeRECT(_viObj->getRC()), makePOINT(_ptMouse)))
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					_isTileClick = true;
					_selectObj = *_viObj;
				}
			}

			count++;
			itemCount++;
		}
		//if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))																//우클릭할경우
		//{
		//	_isTileClick = true;																				//타일클릭은 트루

		//	//샘플드래그용
		//	_saveSampleX = indX;																				//마우스를 누른 순간의 좌표를 저장한다.
		//	_saveSampleY = indY;																				//마우스를 누른 순간의 좌표를 저장한다.

		//	if ((indX >= 0 && indX < SAMPLETILE) && (indY >= 0 && indY < SAMPLETILE))							//인덱스가 범위안에 있을때
		//	{
		//		_curPickTile.curX = indX;																		//현재선택한타일에 인덱스값 들어간다.
		//		_curPickTile.curY = indY;																		//현재선택한타일에 인덱스값 들어간다.
		//	}
		//	else																								//그게아니면
		//		_isTileClick = false;																			//타일클릭은 풜쓰
		//}

		////샘플드래그용
		//if (KEYMANAGER->isOnceKeyUp(VK_RBUTTON))																//우클릭을 뗐을때
		//{
		//	_drawSampleX = indX + 1;																			//드래그X는 인덱스 + 1
		//	if (_drawSampleX <= _saveSampleX) _drawSampleX = 1;													//그냥 선택했을때를 위해 예외처리
		//	_drawSampleY = indY + 1;																			//드래그Y는 인덱스 + 1
		//	if (_drawSampleY <= _saveSampleY) _drawSampleY = 1;													//그냥 선택했을때를 위해 예외처리
		//}
	}
}

void mapTool::dragSampleTile()
{
	//샘플타일창을 드래그할때
	if (PtInRect(&makeRECT(_sampleWindow.rc), makePOINT_NoCamera(_ptMouse)))
	{
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			_isDrag = true;																															//드래그온
			_sampleWindow.rc.left = _sampleWindow.rc.left + _ptMouse.x - _curPoint.x;																//클릭한 순간의 좌표와 이동중일때의 좌표를
			_sampleWindow.rc.top = _sampleWindow.rc.top + _ptMouse.y - _curPoint.y;																//계산해서 샘플타일창을
			_sampleWindow.rc.right = _sampleWindow.rc.left + 400;																					//이동시켜준다.
			_sampleWindow.rc.bottom = _sampleWindow.rc.top + 400;
			_prevButton.rc = { _sampleWindow.rc.right, _sampleWindow.rc.top,		_sampleWindow.rc.right + 30, _sampleWindow.rc.top + 30 };		//창의 위치에 따라 같이 이동
			_nextButton.rc = { _sampleWindow.rc.right, _sampleWindow.rc.top + 30, _sampleWindow.rc.right + 30, _sampleWindow.rc.top + 60 };		//창의 위치에 따라 같이 이동
			_rendomButton.rc = { _sampleWindow.rc.right, _sampleWindow.rc.top + 60,	_sampleWindow.rc.right + 60, _sampleWindow.rc.top + 90 };		//창의 위치에 따라 같이 이동
			_floorButton.rc = { _sampleWindow.rc.right, _sampleWindow.rc.top + 60,	_sampleWindow.rc.right + 70, _sampleWindow.rc.top + 90 };		//창의 위치에 따라 같이 이동
			_eraseButton.rc = { _sampleWindow.rc.right, _sampleWindow.rc.top + 90,	_sampleWindow.rc.right + 40, _sampleWindow.rc.top + 120 };		//창의 위치에 따라 같이 이동
		}
	}
	else
		_isDrag = false;																															//아니면 드래그오프
	_curPoint.x = _ptMouse.x;																														//클릭한 순간의 좌표 기억
	_curPoint.y = _ptMouse.y;																														//클릭한 순간의 좌표 기억
}

void mapTool::setTile()
{
	//맵크기설정한 만큼 렉트와 타일세팅을 해준다.
	for (UINT i = 0; i < _tileY; i++)
	{
		//처음에는 vTile과 vRECT에 초기화한 값들을 넣어주고
		//그담에 이중벡터인 vvTile과 vvRECT에 넣어준다.

		vector<tagTile*> vTile;
		vector<D2D1_RECT_F> vRECT;
		for (UINT j = 0; j < _tileX; j++)
		{
			tagTile* tempTile = new tagTile;
			D2D1_RECT_F* tempRECT = new D2D1_RECT_F;
			parentObj* floor = new parentObj;

			if ((j % 2 == 1 && i % 2 == 0) || (j % 2 == 0 && i % 2 == 1))						//y->홀 x->짝 / y->짝 x->홀 일때
			{
				tempTile->floorName = "floor_01";
				tempTile->terrain_frameX = 1;
				tempTile->terrain_frameY = 0;
				tempTile->type_floor = OBJECT_TYPE_FLOOR;
				tempTile->floorPosX = j;
				tempTile->floorPosY = i;
				tempTile->floor = floor;
			}
			else if ((i % 2 == 0 && j % 2 == 0) || (i % 2 == 1 && j % 2 == 1))					//y->짝 x->짝 / y->홀 x->홀 일때
			{
				tempTile->floorName = "floor_01";
				tempTile->terrain_frameX = 0;
				tempTile->terrain_frameY = 0;
				tempTile->type_floor = OBJECT_TYPE_FLOOR;
				tempTile->floorPosX = j;
				tempTile->floorPosY = i;
				tempTile->floor = floor;
			}
			tempTile->wall = nullptr;
			tempTile->item = nullptr;
			tempTile->enemy = nullptr;
			tempTile->player = nullptr;
			tempTile->objETC = nullptr;
			tempTile->trap = nullptr;
			tempTile->objName = "";
			tempTile->objPosX = j;
			tempTile->objPosY = i;
			tempTile->type_obj = OBJECT_TYPE_NONE;

			tempTile->object_frameX = NULL;
			tempTile->object_frameY = NULL;
			tempTile->isTorch = false;

			*tempRECT = { (float)j * TILE_SIZE,			(float)i * TILE_SIZE,
						  (float)(j + 1) * TILE_SIZE,	(float)(i + 1) * TILE_SIZE };

			vTile.push_back(tempTile);
			vRECT.push_back(*tempRECT);
		}
		_vvTile.push_back(vTile);
		_vvRECT.push_back(vRECT);
	}

	{
		parentObj object;

		for (int i = 0; i < 8; i++)
		{
			object.init(IMAGE_NAME[i], 0, 0, OBJECT_TYPE_FLOOR);
			_vObj.push_back(object);
		}

		for (int i = 8; i < 20; i++)
		{
			object.init(IMAGE_NAME[i], 0, 0, OBJECT_TYPE_WALL);
			_vObj.push_back(object);
		}

		object.init(IMAGE_NAME[IMAGE_NAME_CHEST], 0, 0, OBJECT_TYPE_ITEM);
		_vObj.push_back(object);

		//object.init(IMAGE_NAME[IMAGE_NAME_SHRINE_01], 0, 0, OBJECT_TYPE_ETC);
		//_vObj.push_back(object);

		//object.init(IMAGE_NAME[IMAGE_NAME_SHRINE_02], 0, 0, OBJECT_TYPE_ETC);
		//_vObj.push_back(object);

		//object.init(IMAGE_NAME[IMAGE_NAME_SHRINE_03], 0, 0, OBJECT_TYPE_ETC);
		//_vObj.push_back(object);

		//object.init(IMAGE_NAME[IMAGE_NAME_SHRINE_04], 0, 0, OBJECT_TYPE_ETC);
		//_vObj.push_back(object);

		//object.init(IMAGE_NAME[IMAGE_NAME_SHRINE_05], 0, 0, OBJECT_TYPE_ETC);
		//_vObj.push_back(object);

		//object.init(IMAGE_NAME[IMAGE_NAME_SHRINE_06], 0, 0, OBJECT_TYPE_ETC);
		//_vObj.push_back(object);

		object.init(IMAGE_NAME[IMAGE_NAME_ETC_01], 0, 0, OBJECT_TYPE_ETC);
		_vObj.push_back(object);

		for (const string& elem : ENEMY_NAME)
		{
			object.init(elem, -1, -1, OBJECT_TYPE_ENEMY);
			_vObj.push_back(object);
		}

		for (const string& elem : ARMOR_NAME)
		{
			object.init(elem, -1, -1, OBJECT_TYPE_ITEM);
			_vObj.push_back(object);
		}

		for (const string& elem : SHOVEL_NAME)
		{
			object.init(elem, -1, -1, OBJECT_TYPE_ITEM);
			_vObj.push_back(object);
		}

		for (const string& elem : TORCH_NAME)
		{
			object.init(elem, -1, -1, OBJECT_TYPE_ITEM);
			_vObj.push_back(object);
		}

		for (const string& elem : WEAPON_NAME)
		{
			object.init(elem, -1, -1, OBJECT_TYPE_ITEM);
			_vObj.push_back(object);
		}

		for (const string& elem : HEADWEAR_NAME)
		{
			object.init(elem, -1, -1, OBJECT_TYPE_ITEM);
			_vObj.push_back(object);
		}

		for (const string& elem : FOOTWEAR_NAME)
		{
			object.init(elem, -1, -1, OBJECT_TYPE_ITEM);
			_vObj.push_back(object);
		}

		for (const string& elem : CONSUMABLE_NAME)
		{
			object.init(elem, -1, -1, OBJECT_TYPE_ITEM);
			_vObj.push_back(object);
		}

		for (const string& elem : HEART_NAME)
		{
			object.init(elem, -1, -1, OBJECT_TYPE_ITEM);
			_vObj.push_back(object);
		}

		for (const string& elem : COIN_NAME)
		{
			object.init(elem, -1, -1, OBJECT_TYPE_ITEM);
			_vObj.push_back(object);
		}

		for (const string& elem : BOMB_NAME)
		{
			object.init(elem, -1, -1, OBJECT_TYPE_ITEM);
			_vObj.push_back(object);
		}
	}
}

void mapTool::drawTile()
{
	parentObj tempObj;

	tempObj.init("", -1, -1, OBJECT_TYPE_NONE);

	if (_ptMouse.x - CAMERA->getPosX() > WINSIZEX - TOTAL_SAMPLE_SIZE + TILE_SIZE)	return;								//샘플타일쪽 그리면 안돼
	if (_ptMouse.x > _vvRECT[0][_tileX - 1].right)									return;								//맵 제일 오른쪽 안돼
	if (_ptMouse.x < _vvRECT[0][0].left)											return;								//맵 제일 왼쪽 안돼
	if (_ptMouse.y > _vvRECT[_tileY - 1][0].bottom)									return;								//맵 제일 아래쪽 안돼
	if (_ptMouse.y < _vvRECT[0][0].top)												return;								//맵 제일 윗쪽 안돼
	if (_isDrag)																	return;								//드래그중일때 안돼
	if (!_isEnter)																	return;								//샘플타일창이 없을때도 안돼
	if (PtInRect(&makeRECT(_prevButton.rc), makePOINT_NoCamera(_ptMouse)))			return;								//마우스가 왼쪽버튼에 있을때 안돼
	if (PtInRect(&makeRECT(_nextButton.rc), makePOINT_NoCamera(_ptMouse)))			return;								//마우스가 오른쪽버튼에 있을때 안돼
	if (PtInRect(&makeRECT(_rendomButton.rc), makePOINT_NoCamera(_ptMouse)))		return;								//마우스가 랜덤버튼에 있을때 안돼
	if (PtInRect(&makeRECT(_floorButton.rc), makePOINT_NoCamera(_ptMouse)))			return;								//마우스가 바닥그리기에 있을때 안돼
	if (PtInRect(&makeRECT(_eraseButton.rc), makePOINT_NoCamera(_ptMouse)))			return;								//마우스가 지우개버튼에 있을때 안돼
	if (PtInRect(&makeRECT(_sampleWindow.rc), makePOINT_NoCamera(_ptMouse)))		return;								//마우스가 샘플타일창에 있을때 안돼

	if (_isEnter)
	{
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				for (UINT i = 0; i < _tileY; i++)
				{
					for (UINT j = 0; j < _tileX; j++)
					{
						if (PtInRect(&makeRECT(_vvRECT[i][j]), makePOINT(_ptMouse)))
						{
							_savePointX = j;
							_savePointY = i;
						}
					}
				}
			}

			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
			{
				int savePointX2;
				int savePointY2;

				for (UINT i = 0; i < _tileY; i++)
				{
					for (UINT j = 0; j < _tileX; j++)
					{
						if (PtInRect(&makeRECT(_vvRECT[i][j]), makePOINT(_ptMouse)))
						{
							savePointX2 = j;
							savePointY2 = i;
						}
					}
				}
				savePointX2++;
				savePointY2++;

				if (savePointX2 < _savePointX) return;
				if (savePointY2 < _savePointY) return;

				for (int i = _savePointY; i < savePointY2; i++)
				{
					for (int j = _savePointX; j < savePointX2; j++)
					{
						drawobject(i, j);
					}
				}
			}
		}
	}
}

void mapTool::drawobject(int i, int j)
{
	parentObj* tempObj = new parentObj;
	tempObj->init("", -1, -1, OBJECT_TYPE_NONE);

	parentObj* obj = new parentObj;

	if (_eraseButton.curFrameY == 0)
	{
		switch (_selectObj.getObjType())
		{
		case OBJECT_TYPE_FLOOR:
		{
			obj = new parentObj;
			obj->init(_selectObj.getImgName(), j, i, _selectObj.getObjType());
			_vvTile[i][j]->floor = obj;
			_vvTile[i][j]->floorName = _selectObj.getImgName();
			_vvTile[i][j]->type_floor = _selectObj.getObjType();
			_vvTile[i][j]->floorPosX = j;
			_vvTile[i][j]->floorPosY = i;

			break;
		}
		case OBJECT_TYPE_WALL:
		{
			obj = new parentObj;
			obj->init(_selectObj.getImgName(), j, i, _selectObj.getObjType());
			_vvTile[i][j]->wall = obj;
			_vvTile[i][j]->item = nullptr;
			_vvTile[i][j]->enemy = nullptr;
			_vvTile[i][j]->trap = nullptr;
			_vvTile[i][j]->objName = _selectObj.getImgName();
			_vvTile[i][j]->type_obj = _selectObj.getObjType();
			_vvTile[i][j]->objPosX = j;
			_vvTile[i][j]->objPosY = i;

			break;
		}
		case OBJECT_TYPE_ENEMY:
		{
			obj = new parentObj;
			obj->init(_selectObj.getImgName(), j, i, _selectObj.getObjType());
			_vvTile[i][j]->wall = nullptr;
			_vvTile[i][j]->item = nullptr;
			_vvTile[i][j]->enemy = obj;
			_vvTile[i][j]->trap = nullptr;
			_vvTile[i][j]->objName = _selectObj.getImgName();
			_vvTile[i][j]->type_obj = _selectObj.getObjType();
			_vvTile[i][j]->objPosX = j;
			_vvTile[i][j]->objPosY = i;

			break;
		}
		case OBJECT_TYPE_TRAP:
		{
			obj = new parentObj;
			obj->init(_selectObj.getImgName(), j, i, _selectObj.getObjType());
			_vvTile[i][j]->wall = nullptr;
			_vvTile[i][j]->item = nullptr;
			_vvTile[i][j]->enemy = nullptr;
			_vvTile[i][j]->trap = obj;
			_vvTile[i][j]->objName = _selectObj.getImgName();
			_vvTile[i][j]->type_obj = _selectObj.getObjType();
			_vvTile[i][j]->objPosX = j;
			_vvTile[i][j]->objPosY = i;

			break;
		}
		case OBJECT_TYPE_ITEM:
		{
			obj = new parentObj;
			obj->init(_selectObj.getImgName(), j, i, _selectObj.getObjType());
			_vvTile[i][j]->wall = nullptr;
			_vvTile[i][j]->item = obj;
			_vvTile[i][j]->enemy = nullptr;
			_vvTile[i][j]->trap = nullptr;
			_vvTile[i][j]->objName = _selectObj.getImgName();
			_vvTile[i][j]->type_obj = _selectObj.getObjType();
			_vvTile[i][j]->objPosX = j;
			_vvTile[i][j]->objPosY = i;

			break;
		}
		case OBJECT_TYPE_ETC:
		{
			obj = new parentObj;
			obj->init(_selectObj.getImgName(), _selectObj.getIdxX(), _selectObj.getidxY(), _selectObj.getObjType());

			if (obj->getImgName() == IMAGE_NAME[IMAGE_NAME_ETC_01])
			{
				if (_vvTile[i][j]->type_obj == OBJECT_TYPE_WALL)
				{
					_vvTile[i][j]->isTorch = true;
				}
			}

			break;
		}
		}
	}
	else if (_eraseButton.curFrameY == 1)
	{
		switch (_selectObj.getObjType())
		{
		case OBJECT_TYPE_FLOOR:
		{
			_vvTile[i][j]->floor = nullptr;
			_vvTile[i][j]->floorName = "";
			_vvTile[i][j]->type_floor = OBJECT_TYPE_NONE;
			_vvTile[i][j]->floorPosX = -1;
			_vvTile[i][j]->floorPosY = -1;

			break;
		}
		default:
		{
			_vvTile[i][j]->wall = nullptr;
			_vvTile[i][j]->item = nullptr;
			_vvTile[i][j]->enemy = nullptr;
			_vvTile[i][j]->trap = nullptr;
			_vvTile[i][j]->objName = "";
			_vvTile[i][j]->type_obj = OBJECT_TYPE_NONE;
			_vvTile[i][j]->objPosX = -1;
			_vvTile[i][j]->objPosY = -1;

			break;
		}
		}
	}
}

void mapTool::mapSizeChange()
{
}

void mapTool::loadSetTile()
{
}

void mapTool::eraseTile()
{
}

void mapTool::mapSave(int mapNum)
{
}

void mapTool::mapLoad()
{
}

void mapTool::initMapLoad()
{
	for (int i = _tileY - 1; i >= 0; i--)
	{
		for (int j = _tileX - 1; j >= 0; j--)
		{
			if (_vvTile[i][j])
			{
				SAFE_DELETE(_vvTile[i][j]);
				_vvTile[i].pop_back();
			}
		}
		_vvTile.pop_back();
	}
	_vvTile.clear();

	HANDLE file;
	DWORD read;
	char mapSize[128] = { 0, };

	file = CreateFile(_mSizeMapNames[(MAP_NAME)_curMapNum].c_str(), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, mapSize, 128, &read, NULL);
	CloseHandle(file);

	string mapX, mapY;
	mapX.clear();
	mapY.clear();
	bool x = true;
	for (int i = 0; i < strlen(mapSize); ++i)
	{
		if (mapSize[i] == '/')
		{
			x = false;
			continue;
		}
		if (mapSize[i] == NULL)
			break;
		if (x)
		{
			mapX += mapSize[i];
		}
		else
		{
			mapY += mapSize[i];
		}
	}

	_tileX = stoi(mapX);
	_tileY = stoi(mapY);
	_vvTile.resize(_tileY);

	for (int i = 0; i < _tileY; ++i)
	{
		_vvTile[i].resize(_tileX);
	}

	tagTile* tile = (tagTile*)malloc(sizeof(tagTile) * _tileX * _tileY);
	ZeroMemory(tile, sizeof(tagTile) * (_tileX * _tileY));

	HANDLE file2;
	DWORD read2;

	file2 = CreateFile(_mDataMapNames[(MAP_NAME)_curMapNum].c_str(), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file2, tile, sizeof(tagTile) * _tileX * _tileY, &read2, NULL);

	CloseHandle(file2);

	for (int i = 0; i < _tileY; ++i)
	{
		for (int j = 0; j < _tileX; ++j)
		{
			_vvTile[i][j] = new tagTile;
			_vvTile[i][j]->setTile();
		}
	}
}

void mapTool::initMapName()
{
	_mSizeMapNames.insert(make_pair(MAP_NAME_TEST, "map/testMapSize.map"));
	_mDataMapNames.insert(make_pair(MAP_NAME_TEST, "map/testMapData.map"));
	_mSizeMapNames.insert(make_pair(MAP_NAME_LOBBY, "map/lobbyMapSize.map"));
	_mDataMapNames.insert(make_pair(MAP_NAME_LOBBY, "map/lobbyMapData.map"));
	_mSizeMapNames.insert(make_pair(MAP_NAME_TUTORIAL, "map/tutorialMapSize.map"));
	_mDataMapNames.insert(make_pair(MAP_NAME_TUTORIAL, "map/tutorialMapData.map"));
	_mSizeMapNames.insert(make_pair(MAP_NAME_ZONE1, "map/zone1MapSize.map"));
	_mDataMapNames.insert(make_pair(MAP_NAME_ZONE1, "map/zone1MapData.map"));
	_mSizeMapNames.insert(make_pair(MAP_NAME_ZONE2, "map/zone2MapSize.map"));
	_mDataMapNames.insert(make_pair(MAP_NAME_ZONE2, "map/zone2MapData.map"));
	_mSizeMapNames.insert(make_pair(MAP_NAME_BOSS, "map/bossMapSize.map"));
	_mDataMapNames.insert(make_pair(MAP_NAME_BOSS, "map/bossMapData.map"));
}

void mapTool::drawMap()
{
	for (int i = 0; i < _tileY; i++)
	{
		for (int j = 0; j < _tileX; j++)
		{
			if (_vvTile[i][j]->floor != NULL)
			{
				if (_vvTile[i][j]->floor->getObjType() != OBJECT_TYPE_NONE && _vvTile[i][j]->floorName != "")
				{
					_vvTile[i][j]->floor->render();
				}
			}
		}
	}

}

void mapTool::drawUI()
{
	WCHAR str[128];

	//현재 맵이름 
	swprintf_s(str, L"%S", MAP_NAME_INFO[_curMapNum].c_str());
	D2DMANAGER->drawText(str, CAMERA->getPosX() + 767, CAMERA->getPosY() + _button[MAPTOOL_BUTTON_NAME].rc.top + 30, 20, RGB(255, 0, 0));
	swprintf_s(str, L"%S", MAP_NAME_INFO[_curMapNum].c_str());
	D2DMANAGER->drawText(str, CAMERA->getPosX() + 765, CAMERA->getPosY() + _button[MAPTOOL_BUTTON_NAME].rc.top + 30, 20, RGB(0, 255, 255));

	//버튼출력
	for (int i = 0; i < MAPTOOL_BUTTON_COUNT; i++)
	{
		if (i == MAPTOOL_BUTTON_PREV || i == MAPTOOL_BUTTON_NEXT)
			_button[i].img->frameRender(CAMERA->getPosX() + _button[i].rc.left, CAMERA->getPosY() + _button[i].rc.top - 30, 0, _button[i].curFrameY);
		else if (i >= MAPTOOL_BUTTON_SIZE_WIDTH_UP && i <= MAPTOOL_BUTTON_SIZE_HEIGHT_DOWN)
			_button[i].img->frameRender(CAMERA->getPosX() + _button[i].rc.left - 5, CAMERA->getPosY() + _button[i].rc.top + 2, 0, _button[i].curFrameY);
		else
			_button[i].img->frameRender(CAMERA->getPosX() + _button[i].rc.left + 10, CAMERA->getPosY() + _button[i].rc.top, 0, _button[i].curFrameY);
	}

	//맵크기
	swprintf_s(str, L"던전크기");
	D2DMANAGER->drawText(str, CAMERA->getPosX() + (WINSIZEX - 240) / 2 + 2, CAMERA->getPosY() + 12, 30, RGB(255, 0, 0));
	swprintf_s(str, L"던전크기");
	D2DMANAGER->drawText(str, CAMERA->getPosX() + (WINSIZEX - 240) / 2, CAMERA->getPosY() + 10, 30, RGB(0, 255, 255));

	swprintf_s(str, L" 가로: %d / 세로 : %d", _tileX, _tileY);
	D2DMANAGER->drawText(str, CAMERA->getPosX() + (WINSIZEX - 240) / 2 - 23, CAMERA->getPosY() + 41, 15, RGB(255, 0, 0));
	swprintf_s(str, L" 가로: %d / 세로 : %d", _tileX, _tileY);
	D2DMANAGER->drawText(str, CAMERA->getPosX() + (WINSIZEX - 240) / 2 - 24, CAMERA->getPosY() + 40, 15, RGB(0, 255, 255));
}

void mapTool::drawSample(int num)
{
	if (_isOnTheImg)
	{
		_sampleWindow.img->render(CAMERA->getPosX() + _sampleWindow.rc.left, CAMERA->getPosY() + _sampleWindow.rc.top, 0.8f);
		_eraseButton.img->frameRender(CAMERA->getPosX() + _eraseButton.rc.left, CAMERA->getPosY() + _eraseButton.rc.top, 0, _eraseButton.curFrameY);
		if (_curButtonNum == MAPTOOL_BUTTON_ITEM || _curButtonNum == MAPTOOL_BUTTON_ENEMY)
		{
			_nextButton.img->frameRender(CAMERA->getPosX() + _nextButton.rc.left, CAMERA->getPosY() + _nextButton.rc.top, 0, _nextButton.curFrameY);
			_prevButton.img->frameRender(CAMERA->getPosX() + _prevButton.rc.left, CAMERA->getPosY() + _prevButton.rc.top, 0, _prevButton.curFrameY);
		}
		else if (_curButtonNum == MAPTOOL_BUTTON_WALL)
		{
			_rendomButton.img->frameRender(CAMERA->getPosX() + _rendomButton.rc.left, CAMERA->getPosY() + _rendomButton.rc.top, 0, _rendomButton.curFrameY);
		}
		else if (_curButtonNum == MAPTOOL_BUTTON_FLOOR)
		{
			_floorButton.img->frameRender(CAMERA->getPosX() + _floorButton.rc.left, CAMERA->getPosY() + _floorButton.rc.top, 0, _floorButton.curFrameY);
		}
	}

	int itemCount = 0;
	int count = 0;
	int width, height;
	D2D1_RECT_F rc = {};
	int size = _vObj.size();
	for (int i = 0; i < size; i++)
	{
		D2DMANAGER->drawRectangle(RGB(0, 255, 255), _vObj[i].getRC().left,
			_vObj[i].getRC().top,
			_vObj[i].getRC().right,
			_vObj[i].getRC().bottom);
	}

	D2DMANAGER->drawRectangle(RGB(0, 255, 255), _sampleWindow.rc);

	if (_isOnTheImg)
	{
		if (_curButtonNum == MAPTOOL_BUTTON_ENEMY)
		{
			for (int i = 0; i < size; i++)
			{
				if (_curImgNum == 0)
				{
					if (_vObj[i].getObjType() != num) continue;
					if (_vObj[i].getImg() == nullptr) continue;

					if (count < 13)
					{
						int x = count % 6;
						int y = count / 6;
						string imgName = _vObj[i].getImgName();
						width = IMAGEMANAGER->findImage(imgName)->GetFrameWidth();
						height = IMAGEMANAGER->findImage(imgName)->GetFrameHeight();
						rc = { _sampleWindow.rc.left + (60 * x) + 20,
								_sampleWindow.rc.top + (80 * y) + 70,
								_sampleWindow.rc.left + (60 * x) + 20 + width,
								_sampleWindow.rc.top + (80 * y) + 70 + height };

						_vObj[i].setRC(rc);
						count++;

						IMAGEMANAGER->findImage(imgName)->frameRender(rc.left, rc.top, 0, 0);

						itemCount++;
					}
				}
				else if (_curImgNum == 1)
				{
					if (_vObj[i].getObjType() != num) continue;
					if (_vObj[i].getImg() == nullptr) continue;

					count++;
					if (count <= 13) continue;

					int x = (count - 14) % 4;
					int y = (count - 14) / 4;
					string imgName = _vObj[i].getImgName();
					width = IMAGEMANAGER->findImage(imgName)->GetFrameWidth();
					height = IMAGEMANAGER->findImage(imgName)->GetFrameHeight();
					if (count == 23)
						rc = { _sampleWindow.rc.left + (90 * x) + 20,
								_sampleWindow.rc.top + (110 * y) + 70,
								_sampleWindow.rc.left + (90 * x) + 20 + width,
								_sampleWindow.rc.top + (110 * y) + 70 + height };
					else
						rc = { _sampleWindow.rc.left + (90 * x) + 20,
								_sampleWindow.rc.top + (100 * y) + 70,
								_sampleWindow.rc.left + (90 * x) + 20 + width,
								_sampleWindow.rc.top + (100 * y) + 70 + height };

					_vObj[i].setRC(rc);


					IMAGEMANAGER->findImage(imgName)->frameRender(rc.left, rc.top, 0, 0);

					itemCount++;
				}
			}
		}
		else if (_curButtonNum == MAPTOOL_BUTTON_ITEM)
		{
			for (int i = 0; i < size; i++)
			{
				if (_curImgNum == 0)
				{
					if (count < 24)
					{
						if (_vObj[i].getObjType() != num) continue;
						if (_vObj[i].getImg() == nullptr) continue;

						int x = count % 6;
						int y = count / 6;
						string imgName = _vObj[i].getImgName();
						width = IMAGEMANAGER->findImage(imgName)->GetFrameWidth();
						height = IMAGEMANAGER->findImage(imgName)->GetFrameHeight();
						rc = { _sampleWindow.rc.left + (60 * x) + 20,
								_sampleWindow.rc.top + (80 * y) + 70,
								_sampleWindow.rc.left + (60 * x) + 20 + width,
								_sampleWindow.rc.top + (80 * y) + 70 + height };

						_vObj[i].setRC(rc);
						count++;

						IMAGEMANAGER->findImage(imgName)->frameRender(rc.left, rc.top, 0, 0);

						itemCount++;
					}
				}
				else if (_curImgNum == 1)
				{
					if (_vObj[i].getObjType() != num) continue;
					if (_vObj[i].getImg() == nullptr) continue;

					count++;
					if (count <= 24) continue;
					if (count >= 24 && count <= 48)
					{

						int x = (count - 25) % 6;
						int y = (count - 25) / 6;
						string imgName = _vObj[i].getImgName();
						width = IMAGEMANAGER->findImage(imgName)->GetFrameWidth();
						height = IMAGEMANAGER->findImage(imgName)->GetFrameHeight();
						rc = { _sampleWindow.rc.left + (60 * x) + 20,
								_sampleWindow.rc.top + (80 * y) + 70,
								(float)_sampleWindow.rc.left + (60 * x) + 20 + width,
								(float)_sampleWindow.rc.top + (80 * y) + 70 + height };

						_vObj[i].setRC(rc);

						IMAGEMANAGER->findImage(imgName)->frameRender(rc.left, rc.top, 0, 0);

						itemCount++;
					}
				}
				else if (_curImgNum == 2)
				{

					if (_vObj[i].getObjType() != num) continue;
					if (_vObj[i].getImg() == nullptr) continue;

					count++;
					if (count <= 48) continue;
					if (count >= 48 && count <= 72)
					{

						int x = (count - 49) % 6;
						int y = (count - 49) / 6;
						string imgName = _vObj[i].getImgName();
						width = IMAGEMANAGER->findImage(imgName)->GetFrameWidth();
						height = IMAGEMANAGER->findImage(imgName)->GetFrameHeight();
						rc = { _sampleWindow.rc.left + (60 * x) + 20,
								_sampleWindow.rc.top + (80 * y) + 70,
								(float)_sampleWindow.rc.left + (60 * x) + 20 + width,
								(float)_sampleWindow.rc.top + (80 * y) + 70 + height };

						_vObj[i].setRC(rc);

						IMAGEMANAGER->findImage(imgName)->frameRender(rc.left, rc.top, 0, 0);

						itemCount++;
					}
				}
				else if (_curImgNum == 3)
				{

					if (_vObj[i].getObjType() != num) continue;
					if (_vObj[i].getImg() == nullptr) continue;

					count++;
					if (count <= 72) continue;
					if (count >= 72 && count <= 96)
					{

						int x = (count - 73) % 6;
						int y = (count - 73) / 6;
						string imgName = _vObj[i].getImgName();
						width = IMAGEMANAGER->findImage(imgName)->GetFrameWidth();
						height = IMAGEMANAGER->findImage(imgName)->GetFrameHeight();
						rc = { _sampleWindow.rc.left + (60 * x) + 20,
								_sampleWindow.rc.top + (80 * y) + 70,
								(float)_sampleWindow.rc.left + (60 * x) + 20 + width,
								(float)_sampleWindow.rc.top + (80 * y) + 70 + height };

						_vObj[i].setRC(rc);

						IMAGEMANAGER->findImage(imgName)->frameRender(rc.left, rc.top, 0, 0);

						itemCount++;
					}
				}
				else if (_curImgNum == 4)
				{

					if (_vObj[i].getObjType() != num) continue;
					if (_vObj[i].getImg() == nullptr) continue;

					count++;
					if (count <= 96) continue;
					if (count >= 96 && count <= 120)
					{

						int x = (count - 97) % 6;
						int y = (count - 97) / 6;
						string imgName = _vObj[i].getImgName();
						width = IMAGEMANAGER->findImage(imgName)->GetFrameWidth();
						height = IMAGEMANAGER->findImage(imgName)->GetFrameHeight();
						if (count == 117)
							rc = { _sampleWindow.rc.left + (55 * x) + 20,
									_sampleWindow.rc.top + (82 * y) + 70,
									(float)_sampleWindow.rc.left + (55 * x) + 20 + width,
									(float)_sampleWindow.rc.top + (82 * y) + 70 + height };
						else
							rc = { _sampleWindow.rc.left + (60 * x) + 20,
									_sampleWindow.rc.top + (80 * y) + 70,
									(float)_sampleWindow.rc.left + (60 * x) + 20 + width,
									(float)_sampleWindow.rc.top + (80 * y) + 70 + height };

						_vObj[i].setRC(rc);

						IMAGEMANAGER->findImage(imgName)->frameRender(rc.left, rc.top, 0, 0);

						itemCount++;
					}
				}
			}
		}
		else if (_curButtonNum == MAPTOOL_BUTTON_WALL)
		{
			for (int i = 0; i < size; i++)
			{
				if (_vObj[i].getObjType() != num) continue;
				if (_vObj[i].getImg() == nullptr) continue;

				int x = count % 6;
				int y = count / 6;
				string imgName = _vObj[i].getImgName();
				width = IMAGEMANAGER->findImage(imgName)->GetFrameWidth();
				height = IMAGEMANAGER->findImage(imgName)->GetFrameHeight();
				rc = { _sampleWindow.rc.left + (60 * x) + 20,
					   _sampleWindow.rc.top + (110 * y) + 70,
					   (float)_sampleWindow.rc.left + (60 * x) + 20 + width,
					   (float)_sampleWindow.rc.top + (110 * y) + 70 + height };

				_vObj[i].setRC(rc);
				count++;

				IMAGEMANAGER->findImage(imgName)->frameRender(rc.left, rc.top, 0, 0);

				itemCount++;
			}
		}
		else if (_curButtonNum == MAPTOOL_BUTTON_ETC)
		{
		for (int i = 0; i < size; i++)
		{
			if (_vObj[i].getObjType() != num) continue;
			if (_vObj[i].getImg() == nullptr) continue;

			int x = count % 5;
			int y = count / 5;
			string imgName = _vObj[i].getImgName();
			width = IMAGEMANAGER->findImage(imgName)->GetFrameWidth();
			height = IMAGEMANAGER->findImage(imgName)->GetFrameHeight();
			rc = { _sampleWindow.rc.left + (50 * x) + 20,
					_sampleWindow.rc.top + (70 * y) + 70,
					_sampleWindow.rc.left + (50 * x) + 20 + width,
					_sampleWindow.rc.top + (70 * y) + 70 + height };

			_vObj[i].setRC(rc);
			count++;

			IMAGEMANAGER->findImage(imgName)->frameRender(rc.left, rc.top, 0, 0);

			itemCount++;
		}
		}
		else
		{
			for (int i = 0; i < size; i++)
			{
				if (_vObj[i].getObjType() != num) continue;
				if (_vObj[i].getImg() == nullptr) continue;

				int x = count % 6;
				int y = count / 6;
				string imgName = _vObj[i].getImgName();
				width = IMAGEMANAGER->findImage(imgName)->GetFrameWidth();
				height = IMAGEMANAGER->findImage(imgName)->GetFrameHeight();
				rc = { _sampleWindow.rc.left + (60 * x) + 20,
					   _sampleWindow.rc.top + (70 * y) + 70,
					   (float)_sampleWindow.rc.left + (60 * x) + 20 + width,
					   (float)_sampleWindow.rc.top + (70 * y) + 70 + height };

				_vObj[i].setRC(rc);
				count++;

				IMAGEMANAGER->findImage(imgName)->frameRender(rc.left, rc.top, 0, 0);

				itemCount++;
			}
		}
	}
	/*if (_isEnter)
	{
		if (_isTileClick)
			IMAGEMANAGER->findImage(_selectObj.getImgName())->frameRender(_ptMouse.x, _ptMouse.y, _ptMouse.x + _selectObj.getImg()->GetFrameWidth(), _ptMouse.y + _selectObj.getImg()->GetFrameHeight(), 0.5f);
	}*/
}
