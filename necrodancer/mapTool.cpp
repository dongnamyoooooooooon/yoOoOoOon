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
	CAMERA->init(0, 0, 2400, 2400);					//ī�޶� �ʱ⼳��

	//��ũ�� ����
	_tileX = 40;
	_tileY = 40;

	SOUNDMANAGER->allSoundStop();

	_vvTile.clear();
	_vvRECT.clear();
	_vObj.clear();

	//SOUNDMANAGER->play("mapTool");

	_selectObj.init("", 0, 0, OBJECT_TYPE_NONE, 0);

	//==================================================



	//boolean
	_isTileClick = false;
	_isOnTheImg = false;
	_isEnter = false;

	_curImgNum = 0;									//���� ������ �̹�����ȣ
	_curMapNum = MAP_NAME_TEST;						//�����

	initButton();									//��ư �ʱ⼳��
	initSampleTile();								//����Ÿ�� �ʱ⼳��
	initMapName();									//���̸� �ʱ⼳��
	setTile();										//Ÿ�� �ʱ⼳��

	//initMapLoad();


	return S_OK;
}

void mapTool::release()
{
}

void mapTool::update()
{
	OBJECTMANAGER->setTileX(_tileX);
	OBJECTMANAGER->setTileY(_tileY);

	CAMERA->mapToolMove();								//ī�޶��̵�
	choiceButton();										//��ư����

	if (_isOnTheImg)									//����Ÿ���� �������ٸ�
	{
		pickSampleTile();								//����Ÿ�Ͽ��� Ÿ�ϼ���
		dragSampleTile();								//����Ÿ��â �̵�
		additionOption();								//�ΰ��ɼ�
		drawTile();										//������ Ÿ�� �׸���
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F1))	this->mapSave(_curMapNum);
	if (KEYMANAGER->isOnceKeyDown(VK_F2))	this->mapLoad();
}

void mapTool::render()
{
	WCHAR str[128];

	//���
	IMAGEMANAGER->findImage("maptoolbackground")->render(CAMERA->getPosX() + WINSIZEX - 240, CAMERA->getPosY() + 0, 0.8f);

	drawMap();				//�����
	drawUI();				//����UI����
	drawSample(_choiceNum);			//����Ÿ��
}

void mapTool::initButton()
{
	for (int i = 0; i < MAPTOOL_BUTTON_COUNT; i++)
	{

		if (i < MAPTOOL_BUTTON_PREV)					// i < 8		
			_button[i].rc = { (float)WINSIZEX - 240, (float)40 + (30 * i),		(float)WINSIZEX - 80,	(float)70 + (30 * i) };
		else if (i == MAPTOOL_BUTTON_PREV)				// i == 8  (���ʹ�ư)
			_button[i].rc = { (float)WINSIZEX - 240, (float)250,				(float)WINSIZEX - 210,	(float)280 };
		else if (i == MAPTOOL_BUTTON_NEXT)				// i == 9  (�����ʹ�ư)
			_button[i].rc = { (float)WINSIZEX - 30,	 (float)250,				(float)WINSIZEX,		(float)280 };
		else if (i == MAPTOOL_BUTTON_SIZE_WIDTH_UP)		// i == 15 (���λ����� ����)
			_button[i].rc = { (float)WINSIZEX - 210, (float)490,				(float)WINSIZEX - 170,	(float)510 };
		else if (i == MAPTOOL_BUTTON_SIZE_WIDTH_DOWN)	// i == 16 (���λ����� ����)
			_button[i].rc = { (float)WINSIZEX - 70,  (float)490,				(float)WINSIZEX - 30,	(float)510 };
		else if (i == MAPTOOL_BUTTON_SIZE_HEIGHT_UP)	// i == 17 (���λ����� ����)
			_button[i].rc = { (float)WINSIZEX - 140, (float)470,				(float)WINSIZEX - 100,	(float)490 };
		else if (i == MAPTOOL_BUTTON_SIZE_HEIGHT_DOWN)	// i == 18 (���λ����� ����)
			_button[i].rc = { (float)WINSIZEX - 140, (float)510,				(float)WINSIZEX - 100,	(float)530 };
		else											// �� ��
			_button[i].rc = { (float)WINSIZEX - 240, (float)40 + (30 * i) - 30,	(float)WINSIZEX - 80,	(float)70 + (30 * i) - 30 };
		if (i != 0) _button[i].curFrameY = 0;
	}
	_curButtonNum = MAPTOOL_BUTTON_FLOOR;	//�����ư�� '�ٴڳ���'
	_button[0].curFrameY = 1;				//�����ư �����Ӻ���

	_button[0].img = IMAGEMANAGER->findImage(BUTTON_NAME[MAPTOOL_BUTTON_FLOOR]);				//�Ŵ����� ��ư�̹��� �߰����ּ���^��^
	_button[1].img = IMAGEMANAGER->findImage(BUTTON_NAME[MAPTOOL_BUTTON_WALL]);					//�Ŵ����� ��ư�̹��� �߰����ּ���^��^
	//_button[2].img = IMAGEMANAGER->findImage(BUTTON_NAME[MAPTOOL_BUTTON_CHEST]);				//�Ŵ����� ��ư�̹��� �߰����ּ���^��^
	_button[2].img = IMAGEMANAGER->findImage(BUTTON_NAME[MAPTOOL_BUTTON_ENEMY]);				//�Ŵ����� ��ư�̹��� �߰����ּ���^��^
	_button[3].img = IMAGEMANAGER->findImage(BUTTON_NAME[MAPTOOL_BUTTON_TRAP]);					//�Ŵ����� ��ư�̹��� �߰����ּ���^��^
	_button[4].img = IMAGEMANAGER->findImage(BUTTON_NAME[MAPTOOL_BUTTON_ITEM]);					//�Ŵ����� ��ư�̹��� �߰����ּ���^��^
	_button[5].img = IMAGEMANAGER->findImage(BUTTON_NAME[MAPTOOL_BUTTON_ETC]);					//�Ŵ����� ��ư�̹��� �߰����ּ���^��^
	_button[6].img = IMAGEMANAGER->findImage(BUTTON_NAME[MAPTOOL_BUTTON_NAME]);					//�Ŵ����� ��ư�̹��� �߰����ּ���^��^
	_button[7].img = IMAGEMANAGER->findImage(BUTTON_NAME[MAPTOOL_BUTTON_PREV]);					//�Ŵ����� ��ư�̹��� �߰����ּ���^��^
	_button[8].img = IMAGEMANAGER->findImage(BUTTON_NAME[MAPTOOL_BUTTON_NEXT]);					//�Ŵ����� ��ư�̹��� �߰����ּ���^��^
	_button[9].img = IMAGEMANAGER->findImage(BUTTON_NAME[MAPTOOL_BUTTON_SAVE]);				//�Ŵ����� ��ư�̹��� �߰����ּ���^��^
	_button[10].img = IMAGEMANAGER->findImage(BUTTON_NAME[MAPTOOL_BUTTON_LOAD]);				//�Ŵ����� ��ư�̹��� �߰����ּ���^��^
	_button[11].img = IMAGEMANAGER->findImage(BUTTON_NAME[MAPTOOL_BUTTON_PLAY]);				//�Ŵ����� ��ư�̹��� �߰����ּ���^��^
	_button[12].img = IMAGEMANAGER->findImage(BUTTON_NAME[MAPTOOL_BUTTON_LOBBY]);				//�Ŵ����� ��ư�̹��� �߰����ּ���^��^
	_button[13].img = IMAGEMANAGER->findImage(BUTTON_NAME[MAPTOOL_BUTTON_SIZE]);				//�Ŵ����� ��ư�̹��� �߰����ּ���^��^
	_button[14].img = IMAGEMANAGER->findImage(BUTTON_NAME[MAPTOOL_BUTTON_SIZE_WIDTH_UP]);		//�Ŵ����� ��ư�̹��� �߰����ּ���^��^
	_button[15].img = IMAGEMANAGER->findImage(BUTTON_NAME[MAPTOOL_BUTTON_SIZE_WIDTH_DOWN]);		//�Ŵ����� ��ư�̹��� �߰����ּ���^��^
	_button[16].img = IMAGEMANAGER->findImage(BUTTON_NAME[MAPTOOL_BUTTON_SIZE_HEIGHT_UP]);		//�Ŵ����� ��ư�̹��� �߰����ּ���^��^
	_button[17].img = IMAGEMANAGER->findImage(BUTTON_NAME[MAPTOOL_BUTTON_SIZE_HEIGHT_DOWN]);	//�Ŵ����� ��ư�̹��� �߰����ּ���^��^
}

void mapTool::choiceButton()
{
	if (!_isEnter)
	{
		//�׸��⿡�� ������� �������� ��Ʈ�� �ʱ�ȭ
		_isOnTheImg = false;
		_sampleWindow.rc = { 5,						475,						_sampleWindow.rc.left + 400, _sampleWindow.rc.top + 400 };
		_prevButton.rc = { _sampleWindow.rc.right, _sampleWindow.rc.top,		_sampleWindow.rc.right + 30, _sampleWindow.rc.top + 30 };
		_nextButton.rc = { _sampleWindow.rc.right, _sampleWindow.rc.top + 30, _sampleWindow.rc.right + 30, _sampleWindow.rc.top + 60 };
		_rendomButton.rc = { _sampleWindow.rc.right, _sampleWindow.rc.top + 60,	_sampleWindow.rc.right + 60, _sampleWindow.rc.top + 90 };
		_floorButton.rc = { _sampleWindow.rc.right, _sampleWindow.rc.top + 60,	_sampleWindow.rc.right + 70, _sampleWindow.rc.top + 90 };
		_eraseButton.rc = { _sampleWindow.rc.right, _sampleWindow.rc.top + 90,	_sampleWindow.rc.right + 40, _sampleWindow.rc.top + 120 };
		int size = _vObj.size();
		D2D1_RECT_F rc;
		for (int i = 0; i < size; i++)
		{
			rc = { 0,0,0,0 };
			_vObj[i].setRC(rc);
		}

		//�Ʒ�����Ű ��������
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_curButtonNum++;																				//�����ư��ȣ ����
			for (int i = 0; i < MAPTOOL_BUTTON_COUNT; i++)
			{
				_button[_curButtonNum - 1].curFrameY = 0;													//������ư�� �������� 0

				if (_curButtonNum == MAPTOOL_BUTTON_PREV || _curButtonNum == MAPTOOL_BUTTON_NEXT)			//�����ư�� '����/������'��ư�̸�
					_curButtonNum = MAPTOOL_BUTTON_SAVE;													//'���̺�'��ư���� �̵�(��/���� ���콺��)

				_button[_curButtonNum].curFrameY = 1;														//�����ư�� �������� 1

				if (_curButtonNum >= MAPTOOL_BUTTON_SIZE_WIDTH_UP)											//�����ư�� '���λ���������' ��ư�̸�
				{
					_curButtonNum = MAPTOOL_BUTTON_FLOOR;													//�����ư�� �ٽ� '�ٴڳ���'
					_button[MAPTOOL_BUTTON_SIZE_WIDTH_UP].curFrameY = 0;									//'���λ���������'��ư �������� 0
					_button[_curButtonNum].curFrameY = 1;													//�����ư�� �������� 1
				}
			}
		}

		//���ʹ���Ű ��������
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_curButtonNum--;																				//�����ư��ȣ ����
			for (int i = 0; i < MAPTOOL_BUTTON_COUNT; i++)
			{
				_button[_curButtonNum + 1].curFrameY = 0;													//������ư�� �������� 0

				if (_curButtonNum == MAPTOOL_BUTTON_PREV || _curButtonNum == MAPTOOL_BUTTON_NEXT)			//�����ư�� '����/������'��ư�̸�
					_curButtonNum = MAPTOOL_BUTTON_NAME;													//'�����̸�'��ư���� �̵�(��/���� ���콺��)

				_button[_curButtonNum].curFrameY = 1;														//�����ư�� �������� 1

				if (_curButtonNum < MAPTOOL_BUTTON_FLOOR)													//�����ư�� '�ٴڳ���'�϶�
				{
					_curButtonNum = MAPTOOL_BUTTON_SIZE;													//�����ư�� '������'��ư
					_button[_curButtonNum].curFrameY = 1;													//�����ư�� �������� 1
				}
			}
		}

		//���͸� ��������
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			_isEnter = true;																				//����Ű �۵��� ���ϰ� �ϵ��� �Ѵ�.
			if (_curButtonNum < MAPTOOL_BUTTON_NAME)
				_choiceNum = _curButtonNum;
			activeButton(_curButtonNum);																	//��ư�� �������� �������ش�.

			//�����ư�� '�ٴڳ���'�������� '�����̸�'���� �̰ų� '������' ��ư�� ������
			if ((_curButtonNum >= MAPTOOL_BUTTON_FLOOR && _curButtonNum < MAPTOOL_BUTTON_PREV) || _curButtonNum == MAPTOOL_BUTTON_SIZE)
				_button[_curButtonNum].curFrameY = 2;														//�����ư�� �������� 2
		}
	}
	else if (_isEnter && (_curButtonNum != MAPTOOL_BUTTON_SAVE || _curButtonNum != MAPTOOL_BUTTON_LOAD))	//���ʹ��������̰�
	{																										//�����ư�� '���̺�','�ε�'�� �ƴҰ��
		if (_curButtonNum == MAPTOOL_BUTTON_NAME)															//�����ư�� '�����̸�'�� ������ �����̸� ������ �Ѵ�.													
		{																									//���콺�� ����
			if (PtInRect(&makeRECT(_button[MAPTOOL_BUTTON_PREV].rc), makePOINT_NoCamera(_ptMouse)))			//���콺�� '����'��ư�� �ִ� ���¿���
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))													//��Ŭ���ϸ�
				{
					_curMapNum--;																			//���� ������ȣ�� �ٲ�鼭
					loadSetTile();																			//������ȣ�� �´� ���� �غ��Ѵ�.
					_button[MAPTOOL_BUTTON_PREV].curFrameY = 1;												//���������� '����'��ư�� ������ ����

					if (_curMapNum <= MAP_NAME_TEST)		_curMapNum = MAP_NAME_BOSS;						//����Ż����
				}
				if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))	_button[MAPTOOL_BUTTON_PREV].curFrameY = 0;		//Ŭ���ƴϸ� ������ ����
			}

			else if (PtInRect(&makeRECT(_button[MAPTOOL_BUTTON_NEXT].rc), makePOINT_NoCamera(_ptMouse)))	//���콺�� '����'��ư�� �ִ� ���¿���
			{
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))													//��Ŭ���ϸ�
				{
					_curMapNum++;																			//���� ������ȣ�� �ٲ�鼭
					loadSetTile();																			//������ȣ�� �´� ���� �غ��Ѵ�.
					_button[MAPTOOL_BUTTON_NEXT].curFrameY = 1;												//���������� '����'��ư�� ������ ����

					if (_curMapNum > MAP_NAME_BOSS)			_curMapNum = MAP_NAME_TEST;						//����Ż����
				}
				if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))	_button[MAPTOOL_BUTTON_NEXT].curFrameY = 0;		//Ŭ���ƴϸ� ������ ����
			}
		}
		else if (_curButtonNum == MAPTOOL_BUTTON_SIZE)		mapSizeChange();								//�����ư�� '����ũ��'�� ������ ����ũ�� �����Ѵ�. 

		if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE) || KEYMANAGER->isOnceKeyDown(VK_RETURN))					//ESC�� �ٽ� ���͸� ��������
		{
			_isEnter = false;																				//�������� ���ư���.

			//�����ư�� '�ٴڳ���'�������� '�����̸�'���� �̰ų� '������' ��ư�� ������
			if ((_curButtonNum >= MAPTOOL_BUTTON_FLOOR && _curButtonNum < MAPTOOL_BUTTON_PREV) || _curButtonNum == MAPTOOL_BUTTON_SIZE)
				_button[_curButtonNum].curFrameY = 1;														//�����ư�� �������� 1						
		}
	}
}

void mapTool::activeButton(int num)
{
	_curImgNum = 0;
	_choiceNum = num;
	if (num == MAPTOOL_BUTTON_SAVE)					this->mapSave(_curMapNum);								//���̺��Ѵ�.
	else if (num == MAPTOOL_BUTTON_LOAD)			this->mapLoad();										//�ε��Ѵ�.
	else if (num == MAPTOOL_BUTTON_PLAY)			SCENEMANAGER->changeScene("testMapScene");				//�������ϴµ� �ܾʵ�?

	if (num >= MAPTOOL_BUTTON_NAME && num < MAPTOOL_BUTTON_PLAY)			return;							//�۵��ϸ� �ȵǴ� ��ư�̸�
	if (num >= MAPTOOL_BUTTON_SIZE && num < MAPTOOL_BUTTON_NONE)			return;							//���ư���

	_isOnTheImg = true;																					//����Ÿ��â�� Ų��.
	_curPickTile.curX = 0;																				//���缱����Ÿ���� ��ǥ �ʱ�ȭ
	_curPickTile.curY = 0;																				//���缱����Ÿ���� ��ǥ �ʱ�ȭ
}

void mapTool::initSampleTile()
{
	/*
		�������
		1. ����Ÿ�Ϲ��			(_sampleWindow)
		2. ����Ÿ�� �̹��� ����	(_prevButton)
		3. ����Ÿ�� �̹��� ����	(_nextButton)
		4. ����Ÿ�� �����׸���	(_rendomButton)
		5. �ٴ� �׸��� ����		(_floorButton)
		6. �����				(_eraseButton)
	*/

	//�̹��� �ʱ⼳��
	_sampleWindow.img = IMAGEMANAGER->findImage("samplebackground");
	_prevButton.img = IMAGEMANAGER->findImage("mapTool_left");
	_nextButton.img = IMAGEMANAGER->findImage("mapTool_right");
	_rendomButton.img = IMAGEMANAGER->findImage("mapTool_rendom");
	_floorButton.img = IMAGEMANAGER->findImage("mapTool_floor_choice");
	_eraseButton.img = IMAGEMANAGER->findImage("mapTool_erase");


	//RECT �ʱ⼳��
	_sampleWindow.rc = { 5,						475,						405,						875 };
	_prevButton.rc = { _sampleWindow.rc.right, _sampleWindow.rc.top,		_sampleWindow.rc.right + 30, _sampleWindow.rc.top + 30 };
	_nextButton.rc = { _sampleWindow.rc.right, _sampleWindow.rc.top + 30,	_sampleWindow.rc.right + 30, _sampleWindow.rc.top + 60 };
	_rendomButton.rc = { _sampleWindow.rc.right, _sampleWindow.rc.top + 60,	_sampleWindow.rc.right + 60, _sampleWindow.rc.top + 90 };
	_floorButton.rc = { _sampleWindow.rc.right, _sampleWindow.rc.top + 60,	_sampleWindow.rc.right + 70, _sampleWindow.rc.top + 90 };
	_eraseButton.rc = { _sampleWindow.rc.right, _sampleWindow.rc.top + 90,	_sampleWindow.rc.right + 40, _sampleWindow.rc.top + 120 };

	//����Ÿ�� RECT����
	for (int i = 0; i < SAMPLETILE; i++)
	{
		for (int j = 0; j < SAMPLETILE; j++)
		{
			_sampleTile[i][j].frameX = 0;																				//������ �ʱ�ȭ
			_sampleTile[i][j].frameY = 0;																				//������ �ʱ�ȭ
			_sampleTile[i][j].sampleRC = { (float)j * TILE_SIZE		,(float)i * TILE_SIZE								//RECT����
										  ,(float)j + 1 * TILE_SIZE ,(float)i + 1 * TILE_SIZE };
		}
	}
}

void mapTool::additionOption()
{
	//�����ư�� '�ٴڳ���','������','�������','������','��Ÿ����'�϶�
	if (_curButtonNum == MAPTOOL_BUTTON_ITEM || _curButtonNum == MAPTOOL_BUTTON_ENEMY)
	{
		if (PtInRect(&makeRECT(_prevButton.rc), makePOINT_NoCamera(_ptMouse)))																	//'����'�� ���콺�� �ְ�
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))																							//��Ŭ���ϸ�
			{
				--_curImgNum;																													//�����̹�����ȣ ����
				_prevButton.curFrameY = 1;																										//������ ����

				if (_curButtonNum == MAPTOOL_BUTTON_ENEMY)							_curImgNum = 0;											//����Ż����
				else if (_curButtonNum == MAPTOOL_BUTTON_ITEM && _curImgNum < 0)		_curImgNum = 0;											//����Ż����
				//else if (_curButtonNum == MAPTOOL_BUTTON_ETC)							_curImgNum = 0;											//����Ż����
			}
			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) _prevButton.curFrameY = 0;																	//Ŭ���ƴϸ� ������ ����
		}

		else if (PtInRect(&makeRECT(_nextButton.rc), makePOINT_NoCamera(_ptMouse)))																//'������'�� ���콺�� �ְ�
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))																							//��Ŭ���ϸ�
			{
				++_curImgNum;																													//�����̹�����ȣ ����
				_nextButton.curFrameY = 1;																										//������ ����

				if (_curButtonNum == MAPTOOL_BUTTON_ENEMY)							_curImgNum = 1;											//����Ż����
				else if (_curButtonNum == MAPTOOL_BUTTON_ITEM && _curImgNum >= 4)		_curImgNum = 4;											//����Ż����
				//else if (_curButtonNum == MAPTOOL_BUTTON_ETC)							_curImgNum = 1;											//����Ż����
			}
			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) _nextButton.curFrameY = 0;																	//Ŭ���ƴϸ� ������ ����
		}
	}
	if (_curButtonNum == MAPTOOL_BUTTON_WALL)																								//�����ư�� '������'��
	{
		if (PtInRect(&makeRECT(_rendomButton.rc), makePOINT_NoCamera(_ptMouse)))															//'����'�� ���콺�� �ְ�
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))																						//��Ŭ���ϸ�
			{
				if (_rendomButton.curFrameY == 0) _rendomButton.curFrameY = 1;															//�������� 0�̸� 1��
				else if (_rendomButton.curFrameY == 1) _rendomButton.curFrameY = 0;															//�������� 1�̸� 0����
			}
		}
	}
	else if (_curButtonNum == MAPTOOL_BUTTON_FLOOR)																							//�����ư�� '�ٴڳ���'��
	{
		if (PtInRect(&makeRECT(_floorButton.rc), makePOINT_NoCamera(_ptMouse)))																//'�ٴڱ׸���'�� ���콺�� �ְ�
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))																						//��Ŭ���ϸ�
			{
				if (_floorButton.curFrameY == 0) _floorButton.curFrameY = 1;															//�������� 0�̸� 1��
				else if (_floorButton.curFrameY == 1) _floorButton.curFrameY = 2;															//�������� 1�̸� 2����
				else if (_floorButton.curFrameY == 2) _floorButton.curFrameY = 0;															//�������� 2�̸� 0����
			}
		}
	}

	if (PtInRect(&makeRECT(_eraseButton.rc), makePOINT_NoCamera(_ptMouse)))															//'�����'�� ���콺�� �ְ�
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))																							//��Ŭ���ϸ�
		{
			if (_eraseButton.curFrameY == 0) _eraseButton.curFrameY = 1;																//�������� 0�̸� 1��
			else if (_eraseButton.curFrameY == 1) _eraseButton.curFrameY = 0;																//�������� 1�̸� 0����

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
	}
}

void mapTool::dragSampleTile()
{
	//����Ÿ��â�� �巡���Ҷ�
	if (PtInRect(&makeRECT(_sampleWindow.rc), makePOINT_NoCamera(_ptMouse)))
	{
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			_isDrag = true;																															//�巡�׿�
			_sampleWindow.rc.left = _sampleWindow.rc.left + _ptMouse.x - _curPoint.x;																//Ŭ���� ������ ��ǥ�� �̵����϶��� ��ǥ��
			_sampleWindow.rc.top = _sampleWindow.rc.top + _ptMouse.y - _curPoint.y;																//����ؼ� ����Ÿ��â��
			_sampleWindow.rc.right = _sampleWindow.rc.left + 400;																					//�̵������ش�.
			_sampleWindow.rc.bottom = _sampleWindow.rc.top + 400;
			_prevButton.rc = { _sampleWindow.rc.right, _sampleWindow.rc.top,		_sampleWindow.rc.right + 30, _sampleWindow.rc.top + 30 };		//â�� ��ġ�� ���� ���� �̵�
			_nextButton.rc = { _sampleWindow.rc.right, _sampleWindow.rc.top + 30, _sampleWindow.rc.right + 30, _sampleWindow.rc.top + 60 };		//â�� ��ġ�� ���� ���� �̵�
			_rendomButton.rc = { _sampleWindow.rc.right, _sampleWindow.rc.top + 60,	_sampleWindow.rc.right + 60, _sampleWindow.rc.top + 90 };		//â�� ��ġ�� ���� ���� �̵�
			_floorButton.rc = { _sampleWindow.rc.right, _sampleWindow.rc.top + 60,	_sampleWindow.rc.right + 70, _sampleWindow.rc.top + 90 };		//â�� ��ġ�� ���� ���� �̵�
			_eraseButton.rc = { _sampleWindow.rc.right, _sampleWindow.rc.top + 90,	_sampleWindow.rc.right + 40, _sampleWindow.rc.top + 120 };		//â�� ��ġ�� ���� ���� �̵�
		}
	}
	else
		_isDrag = false;																															//�ƴϸ� �巡�׿���
	_curPoint.x = _ptMouse.x;																														//Ŭ���� ������ ��ǥ ���
	_curPoint.y = _ptMouse.y;																														//Ŭ���� ������ ��ǥ ���
}

void mapTool::setTile()
{
	//��ũ�⼳���� ��ŭ ��Ʈ�� Ÿ�ϼ����� ���ش�.
	for (UINT i = 0; i < _tileY; i++)
	{
		//ó������ vTile�� vRECT�� �ʱ�ȭ�� ������ �־��ְ�
		//�״㿡 ���ߺ����� vvTile�� vvRECT�� �־��ش�.

		vector<tagTile*> vTile;
		vector<D2D1_RECT_F> vRECT;
		for (UINT j = 0; j < _tileX; j++)
		{
			tagTile* tempTile = new tagTile;
			D2D1_RECT_F* tempRECT = new D2D1_RECT_F;
			parentObj* floor = new parentObj;
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

		for (int i = 0; i < 6; i++)
		{
			object.init(IMAGE_NAME[i], 0, 0, OBJECT_TYPE_FLOOR, i);
			_vObj.push_back(object);
		}

		for (int i = 8; i < 21; i++)
		{
			object.init(IMAGE_NAME[i], 0, 0, OBJECT_TYPE_WALL, i);
			_vObj.push_back(object);
		}

		object.init(IMAGE_NAME[IMAGE_NAME_CHEST], 0, 0, OBJECT_TYPE_ITEM, IMAGE_NAME_CHEST);
		_vObj.push_back(object);

		object.init(IMAGE_NAME[IMAGE_NAME_STAIRS_01], 0, 0, OBJECT_TYPE_ETC, IMAGE_NAME_STAIRS_01);
		_vObj.push_back(object);

		object.init(IMAGE_NAME[IMAGE_NAME_STAIRS_02], 0, 0, OBJECT_TYPE_ETC, IMAGE_NAME_STAIRS_02);
		_vObj.push_back(object);

		object.init(IMAGE_NAME[IMAGE_NAME_TRAP_BOUNCE], 0, 0, OBJECT_TYPE_TRAP, IMAGE_NAME_TRAP_BOUNCE);
		_vObj.push_back(object);

		object.init(IMAGE_NAME[IMAGE_NAME_TRAP_SLOWDOWN], 0, 0, OBJECT_TYPE_TRAP, IMAGE_NAME_TRAP_SLOWDOWN);
		_vObj.push_back(object);

		object.init(IMAGE_NAME[IMAGE_NAME_TRAP_SPEEDUP], 0, 0, OBJECT_TYPE_TRAP, IMAGE_NAME_TRAP_SPEEDUP);
		_vObj.push_back(object);

		object.init(IMAGE_NAME[IMAGE_NAME_TRAP_SPIKE], 0, 0, OBJECT_TYPE_TRAP, IMAGE_NAME_TRAP_SPIKE);
		_vObj.push_back(object);

		object.init(IMAGE_NAME[IMAGE_NAME_ETC_01], 0, 0, OBJECT_TYPE_ETC, IMAGE_NAME_ETC_01);
		_vObj.push_back(object);

		for (int i = 21; i < 44; i++)
		{
			object.init(IMAGE_NAME[i], -1, -1, OBJECT_TYPE_ENEMY, i);
			_vObj.push_back(object);
		}

		for (int i = 0; i < ITEM_ARMOR_COUNT; i++)
		{
			object.init(ARMOR_NAME[i], -1, -1, OBJECT_TYPE_ITEM, i, ITEM_TYPE_ARMOR);
			_vObj.push_back(object);
		}

		for (int i = 0; i < ITEM_SHOVEL_COUNT; i++)
		{
			object.init(SHOVEL_NAME[i], -1, -1, OBJECT_TYPE_ITEM, i, ITEM_TYPE_SHOVEL);
			_vObj.push_back(object);
		}

		for (int i = 0; i < ITEM_TORCH_COUNT; i++)
		{
			object.init(TORCH_NAME[i], -1, -1, OBJECT_TYPE_ITEM, i, ITEM_TYPE_TORCH);
			_vObj.push_back(object);
		}

		for (int i = 0; i < ITEM_WEAPON_COUNT; i++)
		{
			object.init(WEAPON_NAME[i], -1, -1, OBJECT_TYPE_ITEM, i, ITEM_TYPE_WEAPON);
			_vObj.push_back(object);
		}

		for (int i = 0; i < ITEM_HEADWEAR_COUNT; i++)
		{
			object.init(HEADWEAR_NAME[i], -1, -1, OBJECT_TYPE_ITEM, i, ITEM_TYPE_HEADWEAR);
			_vObj.push_back(object);
		}

		for (int i = 0; i < ITEM_FOOTWEAR_COUNT; i++)
		{
			object.init(FOOTWEAR_NAME[i], -1, -1, OBJECT_TYPE_ITEM, i, ITEM_TYPE_FOOTWEAR);
			_vObj.push_back(object);
		}

		for (int i = 0; i < ITEM_CONSUMABLE_COUNT; i++)
		{
			object.init(CONSUMABLE_NAME[i], -1, -1, OBJECT_TYPE_ITEM, i, ITEM_TYPE_CONSUMABLE);
			_vObj.push_back(object);
		}

		for (int i = 0; i < ITEM_HEART_COUNT; i++)
		{
			object.init(HEART_NAME[i], -1, -1, OBJECT_TYPE_ITEM, i, ITEM_TYPE_HEART);
			_vObj.push_back(object);
		}

		for (int i = 0; i < ITEM_COIN_COUNT; i++)
		{
			object.init(COIN_NAME[i], -1, -1, OBJECT_TYPE_ITEM, i, ITEM_TYPE_COIN);
			_vObj.push_back(object);
		}

		for (int i = 0; i < ITEM_BOMB_COUNT; i++)
		{
			object.init(BOMB_NAME[i], -1, -1, OBJECT_TYPE_ITEM, i, ITEM_TYPE_BOMB);
			_vObj.push_back(object);
		}
	}
}

void mapTool::drawTile()
{
	parentObj tempObj;

	tempObj.init("", -1, -1, OBJECT_TYPE_NONE, 0);

	if (_ptMouse.x - CAMERA->getPosX() > WINSIZEX - TOTAL_SAMPLE_SIZE + TILE_SIZE)	return;								//����Ÿ���� �׸��� �ȵ�
	if (_ptMouse.x > _vvRECT[0][_tileX - 1].right)									return;								//�� ���� ������ �ȵ�
	if (_ptMouse.x < _vvRECT[0][0].left)											return;								//�� ���� ���� �ȵ�
	if (_ptMouse.y > _vvRECT[_tileY - 1][0].bottom)									return;								//�� ���� �Ʒ��� �ȵ�
	if (_ptMouse.y < _vvRECT[0][0].top)												return;								//�� ���� ���� �ȵ�
	if (_isDrag)																	return;								//�巡�����϶� �ȵ�
	if (!_isEnter)																	return;								//����Ÿ��â�� �������� �ȵ�
	if (PtInRect(&makeRECT(_prevButton.rc), makePOINT_NoCamera(_ptMouse)))			return;								//���콺�� ���ʹ�ư�� ������ �ȵ�
	if (PtInRect(&makeRECT(_nextButton.rc), makePOINT_NoCamera(_ptMouse)))			return;								//���콺�� �����ʹ�ư�� ������ �ȵ�
	if (PtInRect(&makeRECT(_rendomButton.rc), makePOINT_NoCamera(_ptMouse)))		return;								//���콺�� ������ư�� ������ �ȵ�
	if (PtInRect(&makeRECT(_floorButton.rc), makePOINT_NoCamera(_ptMouse)))			return;								//���콺�� �ٴڱ׸��⿡ ������ �ȵ�
	if (PtInRect(&makeRECT(_eraseButton.rc), makePOINT_NoCamera(_ptMouse)))			return;								//���콺�� ���찳��ư�� ������ �ȵ�
	if (PtInRect(&makeRECT(_sampleWindow.rc), makePOINT_NoCamera(_ptMouse)))		return;								//���콺�� ����Ÿ��â�� ������ �ȵ�

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
		else if (KEYMANAGER->isStayKeyDown(VK_CONTROL))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				for (int i = 0; i < _tileY; i++)
				{
					for (int j = 0; j < _tileX; j++)
					{
						if (PtInRect(&makeRECT(_vvRECT[i][j]), makePOINT(_ptMouse)))
						{
							_saveTile.floor = _vvTile[i][j]->floor;
							_saveTile.floorName = _vvTile[i][j]->floorName;
							_saveTile.floorPosX = _vvTile[i][j]->floorPosX;
							_saveTile.floorPosY = _vvTile[i][j]->floorPosY;
							_saveTile.type_floor = _vvTile[i][j]->type_floor;
							{
								drawobject(i, j);
							}
						}
					}
				}
			}

			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
			{
				for (int i = 0; i < _tileY; i++)
				{
					for (int j = 0; j < _tileX; j++)
					{
						if (_saveTile.floorName == _vvTile[i][j]->floorName &&
							_saveTile.type_floor == _vvTile[i][j]->type_floor)
						{
							drawobject(i, j);
						}
					}
				}
			}
		}
		else
		{
			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			{
				for (int i = 0; i < _tileY; i++)
				{
					for (int j = 0; j < _tileX; j++)
					{
						if (PtInRect(&makeRECT(_vvRECT[i][j]), makePOINT(_ptMouse)))
						{
							drawobject(i, j);
						}
					}
				}
			}
		}
	}
}

void mapTool::drawobject(int i, int j)
{
	parentObj* tempObj = new parentObj;
	tempObj->init("", -1, -1, OBJECT_TYPE_NONE, 0);

	parentObj* obj = new parentObj;

	if (_eraseButton.curFrameY == 0)
	{
		switch (_selectObj.getObjType())
		{
		case OBJECT_TYPE_FLOOR:
		{
			obj = new parentObj;
			obj->init(_selectObj.getImgName(), j, i, _selectObj.getObjType(), _selectObj.getImgKey());
			_vvTile[i][j]->floor = obj;
			_vvTile[i][j]->floorName = _selectObj.getImgName();
			_vvTile[i][j]->type_floor = _selectObj.getObjType();
			_vvTile[i][j]->floorPosX = j;
			_vvTile[i][j]->floorPosY = i;
			_vvTile[i][j]->imgKey = _selectObj.getImgKey();

			break;
		}
		case OBJECT_TYPE_WALL:
		{
			obj = new parentObj;
			obj->init(_selectObj.getImgName(), j, i, _selectObj.getObjType(), _selectObj.getImgKey());
			_vvTile[i][j]->wall = obj;
			_vvTile[i][j]->item = nullptr;
			_vvTile[i][j]->enemy = nullptr;
			_vvTile[i][j]->trap = nullptr;
			_vvTile[i][j]->objName = _selectObj.getImgName();
			_vvTile[i][j]->type_obj = _selectObj.getObjType();
			_vvTile[i][j]->objPosX = j;
			_vvTile[i][j]->objPosY = i;
			_vvTile[i][j]->imgKey = _selectObj.getImgKey();
			_vvTile[i][j]->terrain_frameX = RND->getInt(15);

			break;
		}
		case OBJECT_TYPE_ENEMY:
		{
			obj = new parentObj;
			obj->init(_selectObj.getImgName(), j, i, _selectObj.getObjType(), _selectObj.getImgKey());
			_vvTile[i][j]->wall = nullptr;
			_vvTile[i][j]->item = nullptr;
			_vvTile[i][j]->enemy = obj;
			_vvTile[i][j]->trap = nullptr;
			_vvTile[i][j]->objName = _selectObj.getImgName();
			_vvTile[i][j]->type_obj = _selectObj.getObjType();
			_vvTile[i][j]->objPosX = j;
			_vvTile[i][j]->objPosY = i;
			_vvTile[i][j]->imgKey = _selectObj.getImgKey();

			break;
		}
		case OBJECT_TYPE_TRAP:
		{
			obj = new parentObj;
			obj->init(_selectObj.getImgName(), j, i, _selectObj.getObjType(), _selectObj.getImgKey());
			_vvTile[i][j]->wall = nullptr;
			_vvTile[i][j]->item = nullptr;
			_vvTile[i][j]->enemy = nullptr;
			_vvTile[i][j]->trap = obj;
			_vvTile[i][j]->objName = _selectObj.getImgName();
			_vvTile[i][j]->type_obj = _selectObj.getObjType();
			_vvTile[i][j]->objPosX = j;
			_vvTile[i][j]->objPosY = i;
			_vvTile[i][j]->imgKey = _selectObj.getImgKey();

			break;
		}
		case OBJECT_TYPE_ITEM:
		{
			obj = new parentObj;
			obj->init(_selectObj.getImgName(), j, i, _selectObj.getObjType(), _selectObj.getImgKey(), (ITEM_TYPE)_selectObj.getItemType());
			_vvTile[i][j]->wall = nullptr;
			_vvTile[i][j]->item = obj;
			_vvTile[i][j]->enemy = nullptr;
			_vvTile[i][j]->trap = nullptr;
			_vvTile[i][j]->objName = _selectObj.getImgName();
			_vvTile[i][j]->type_obj = _selectObj.getObjType();
			_vvTile[i][j]->objPosX = j;
			_vvTile[i][j]->objPosY = i;
			_vvTile[i][j]->imgKey = _selectObj.getImgKey();

			break;
		}
		case OBJECT_TYPE_ETC:
		{
			obj = new parentObj;
			obj->init(_selectObj.getImgName(), _selectObj.getIdxX(), _selectObj.getidxY(), _selectObj.getObjType(), _selectObj.getImgKey());

			if (obj->getImgName() == IMAGE_NAME[IMAGE_NAME_ETC_01])
			{
				if (_vvTile[i][j]->type_obj == OBJECT_TYPE_WALL)
				{
					_vvTile[i][j]->isTorch = true;
				}
			}
			else if (obj->getImgName() == IMAGE_NAME[IMAGE_NAME_STAIRS_01] || obj->getImgName() == IMAGE_NAME[IMAGE_NAME_STAIRS_02])
			{
				_vvTile[i][j]->objETC = obj;
				_vvTile[i][j]->wall = nullptr;
				_vvTile[i][j]->item = nullptr;
				_vvTile[i][j]->enemy = nullptr;
				_vvTile[i][j]->trap = nullptr;
				_vvTile[i][j]->objName = _selectObj.getImgName();
				_vvTile[i][j]->type_obj = _selectObj.getObjType();
				_vvTile[i][j]->objPosX = j;
				_vvTile[i][j]->objPosY = i;
				_vvTile[i][j]->imgKey = _selectObj.getImgKey();
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
	// ���λ����� ����
	if (PtInRect(&makeRECT(_button[MAPTOOL_BUTTON_SIZE_WIDTH_DOWN].rc), makePOINT_NoCamera(_ptMouse)) && _tileX > 1)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_button[MAPTOOL_BUTTON_SIZE_WIDTH_DOWN].curFrameY = 1;
			for (int i = _tileY - 1; i >= 0; i--)
			{
				tagTile* target = _vvTile[i].back();
				_vvTile[i].pop_back();

				D2D1_RECT_F targetRC = _vvRECT[i].back();
				_vvRECT[i].pop_back();
				SAFE_DELETE(target);
			}
			_tileX--;
		}
	}

	// ���λ����� ����
	if (PtInRect(&makeRECT(_button[MAPTOOL_BUTTON_SIZE_WIDTH_UP].rc), makePOINT_NoCamera(_ptMouse)) && _tileX <= 100)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_button[MAPTOOL_BUTTON_SIZE_WIDTH_UP].curFrameY = 1;
			for (int i = 0; i < _tileY; i++)
			{
				tagTile* tempTile = new tagTile;
				parentObj* floor = new parentObj;
				tempTile->wall = nullptr;
				tempTile->item = nullptr;
				tempTile->enemy = nullptr;
				tempTile->player = nullptr;
				tempTile->objETC = nullptr;
				tempTile->trap = nullptr;
				tempTile->objName = "";
				tempTile->type_obj = OBJECT_TYPE_NONE;

				tempTile->object_frameX = NULL;
				tempTile->object_frameY = NULL;
				tempTile->isTorch = false;

				D2D1_RECT_F tempRECT = { (float)_vvRECT[i].back().left + TILE_SIZE		,(float)_vvRECT[i].back().top
										,(float)_vvRECT[i].back().right + TILE_SIZE		,(float)_vvRECT[i].back().bottom };

				_vvTile[i].push_back(tempTile);
				_vvRECT[i].push_back(tempRECT);
			}
			++_tileX;
		}
	}
	// ���λ����� ����
	if (PtInRect(&makeRECT(_button[MAPTOOL_BUTTON_SIZE_HEIGHT_DOWN].rc), makePOINT_NoCamera(_ptMouse)))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && _tileY > 1)
		{
			_button[MAPTOOL_BUTTON_SIZE_HEIGHT_DOWN].curFrameY = 1;
			for (int i = _tileX - 1; i >= 0; i--)
			{
				tagTile* tile = _vvTile.back()[i];
				_vvTile.back().pop_back();
				_vvRECT.back().pop_back();

				delete tile;
				tile = nullptr;
			}
			_vvTile.pop_back();
			_vvRECT.pop_back();
			_tileY--;
		}
	}

	// ���λ����� ����
	if (PtInRect(&makeRECT(_button[MAPTOOL_BUTTON_SIZE_HEIGHT_UP].rc), makePOINT_NoCamera(_ptMouse)) && _tileY <= 100)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_button[MAPTOOL_BUTTON_SIZE_HEIGHT_UP].curFrameY = 1;
			vector<tagTile*> vTile;
			vector<D2D1_RECT_F> vRECT;
			vTile.clear();
			vRECT.clear();
			for (int i = 0; i < _tileX; i++)
			{
				tagTile* tempTile = new tagTile;
				parentObj* floor = new parentObj;
				tempTile->wall = nullptr;
				tempTile->item = nullptr;
				tempTile->enemy = nullptr;
				tempTile->player = nullptr;
				tempTile->objETC = nullptr;
				tempTile->trap = nullptr;
				tempTile->objName = "";
				tempTile->type_obj = OBJECT_TYPE_NONE;

				tempTile->object_frameX = NULL;
				tempTile->object_frameY = NULL;
				tempTile->isTorch = false;

				D2D1_RECT_F tempRECT = { (float)_vvRECT.back()[i].left		,(float)_vvRECT.back()[i].top + TILE_SIZE
										,(float)_vvRECT.back()[i].right		,(float)_vvRECT.back()[i].bottom + TILE_SIZE };

				vTile.push_back(tempTile);
				vRECT.push_back(tempRECT);
			}
			_vvTile.push_back(vTile);
			_vvRECT.push_back(vRECT);

			_tileY++;
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		for (int i = MAPTOOL_BUTTON_SIZE_WIDTH_UP; i <= MAPTOOL_BUTTON_SIZE_HEIGHT_DOWN; i++)
		{
			_button[i].curFrameY = 0;
		}
	}

}

void mapTool::loadSetTile()
{
	//��ũ�⼳���� ��ŭ ��Ʈ�� Ÿ�ϼ����� ���ش�.
	for (UINT i = 0; i < _tileY; i++)
	{
		//ó������ vTile�� vRECT�� �ʱ�ȭ�� ������ �־��ְ�
		//�״㿡 ���ߺ����� vvTile�� vvRECT�� �־��ش�.

		vector<tagTile*> vTile;
		vector<D2D1_RECT_F> vRECT;
		for (UINT j = 0; j < _tileX; j++)
		{
			tagTile* tempTile = new tagTile;
			D2D1_RECT_F* tempRECT = new D2D1_RECT_F;
			parentObj* floor = new parentObj;
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
}

void mapTool::mapSave(int mapNum)
{
	//�ʻ����� ����
	HANDLE file;
	DWORD write;

	char mapSize[128];
	sprintf_s(mapSize, "%d/%d", _tileX, _tileY);

	file = CreateFile(_mSizeMapNames[(MAP_NAME)mapNum].c_str(), GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, mapSize, strlen(mapSize), &write, NULL);

	CloseHandle(file);

	tagPack* pack = new tagPack[_tileX * _tileY];
	for (int i = 0; i < _tileY; i++)
	{
		for (int j = 0; j < _tileX; j++)
		{
			pack[i + j * _tileX] = _vvTile[i][j]->makeSave();
		}
	}

	HANDLE file2;
	DWORD write2;

	file2 = CreateFile(_mDataMapNames[(MAP_NAME)mapNum].c_str(), GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file2, pack, sizeof(tagPack) * _tileX * _tileY, &write2, NULL);

	CloseHandle(file2);
}

void mapTool::mapLoad()
{
	for (int i = _tileY - 1; i >= 0; i--)
	{
		for (int j = _tileX - 1; j >= 0; j--)
		{
			if (_vvTile[i][j])
			{
				//SAFE_DELETE(_vvTile[i][j]);
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

	tagPack* pack = new tagPack[_tileX * _tileY];

	HANDLE file2;
	DWORD read2;

	file2 = CreateFile(_mDataMapNames[(MAP_NAME)_curMapNum].c_str(), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file2, pack, sizeof(tagPack) * _tileX * _tileY, &read2, NULL);
	CloseHandle(file2);

	for (int i = 0; i < _tileY; ++i)
	{
		for (int j = 0; j < _tileX; ++j)
		{
			_vvTile[i][j] = new tagTile;
			_vvTile[i][j]->makeLoad(&pack[i + j * _tileX]);
		}
	}
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
	//tagTile* tile = new tagTile[_tileX * _tileY];
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
			_vvTile[i][j]->floor = tile[j + i * _tileX].floor;
			_vvTile[i][j]->enemy = tile[j + i * _tileX].enemy;
			_vvTile[i][j]->wall = tile[j + i * _tileX].wall;
			_vvTile[i][j]->objETC = tile[j + i * _tileX].objETC;
			_vvTile[i][j]->trap = tile[j + i * _tileX].trap;
			_vvTile[i][j]->item = tile[j + i * _tileX].item;
			_vvTile[i][j]->player = tile[j + i * _tileX].player;

			_vvTile[i][j] = &tile[j + i * _tileX];
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
			if (_vvRECT[i][j].left - (CAMERA->getPosX() - 10) < 0)			continue;
			if (_vvRECT[i][j].right - CAMERA->getPosX() > 13 * TILE_SIZE)	continue;


			D2DMANAGER->drawRectangle(RGB(0,255,255),_vvRECT[i][j].left, _vvRECT[i][j].top, _vvRECT[i][j].right, _vvRECT[i][j].bottom);
			if (_vvTile[i][j]->floor != NULL)
			{
				if (_vvTile[i][j]->floor->getObjType() != OBJECT_TYPE_NONE && _vvTile[i][j]->floorName != "")
				{
					_vvTile[i][j]->floor->render(_vvRECT[i][j].left, _vvRECT[i][j].top);
				}
			}
		}
	}

	for (int i = 0; i < _tileY; i++)
	{
		for (int j = 0; j < _tileX; j++)
		{
			if (_vvRECT[i][j].left - (CAMERA->getPosX() - 10) < 0)			continue;
			if (_vvRECT[i][j].right - CAMERA->getPosX() > 13 * TILE_SIZE)	continue;

			if (_vvTile[i][j]->objETC != NULL)
			{
				if (_vvTile[i][j]->objETC->getObjType() != OBJECT_TYPE_NONE && _vvTile[i][j]->objName != "")
				{
					_vvTile[i][j]->objETC->render(_vvRECT[i][j].left, _vvRECT[i][j].top);
				}
			}
		}

	}


	
	for (int i = 0; i < _tileY; i++)
	{
		for (int j = 0; j < _tileX; j++)
		{
			if (_vvRECT[i][j].left - (CAMERA->getPosX() - 10) < 0)			continue;
			if (_vvRECT[i][j].right - CAMERA->getPosX() > 13 * TILE_SIZE)	continue;

			if (_vvTile[i][j]->item != NULL)
			{
				if (_vvTile[i][j]->item->getObjType() != OBJECT_TYPE_NONE && _vvTile[i][j]->objName != "")
				{
					_vvTile[i][j]->item->render(_vvRECT[i][j].left, _vvRECT[i][j].top);
				}
			}
		}
	}

	for (int i = 0; i < _tileY; i++)
	{
		for (int j = 0; j < _tileX; j++)
		{
			if (_vvRECT[i][j].left - (CAMERA->getPosX() - 10) < 0)			continue;
			if (_vvRECT[i][j].right - CAMERA->getPosX() > 13 * TILE_SIZE)	continue;


			if (_vvTile[i][j]->trap != NULL)
			{
				if (_vvTile[i][j]->trap->getObjType() != OBJECT_TYPE_NONE && _vvTile[i][j]->objName != "")
				{
					_vvTile[i][j]->trap->render(_vvRECT[i][j].left + 12, _vvRECT[i][j].top + 10);
				}
			}
		}
	}

	for (int i = 0; i < _tileY; i++)
	{
		for (int j = 0; j < _tileX; j++)
		{
			if (_vvRECT[i][j].left - (CAMERA->getPosX() - 10) < 0)			continue;
			if (_vvRECT[i][j].right - CAMERA->getPosX() > 13 * TILE_SIZE)	continue;

			if (_vvTile[i][j]->wall != NULL)
			{
				if (_vvTile[i][j]->wall->getObjType() != OBJECT_TYPE_NONE && _vvTile[i][j]->objName != "")
				{
					if (_curButtonNum == MAPTOOL_BUTTON_WALL && _rendomButton.curFrameY == 1)
						_vvTile[i][j]->wall->render(_vvRECT[i][j].left, _vvRECT[i][j].top - 28, _vvTile[i][j]->terrain_frameX);
					else
						_vvTile[i][j]->wall->render(_vvRECT[i][j].left, _vvRECT[i][j].top - 28);
				}
				if (_vvTile[i][j]->isTorch)
					IMAGEMANAGER->frameRender(IMAGE_NAME[IMAGE_NAME_ETC_01], _vvRECT[i][j].left, _vvRECT[i][j].top - 46, 0, 0);
			}
		}
	}

	for (int i = 0; i < _tileY; i++)
	{
		for (int j = 0; j < _tileX; j++)
		{
			if (_vvRECT[i][j].left - (CAMERA->getPosX() - 10) < 0)			continue;
			if (_vvRECT[i][j].right - CAMERA->getPosX() > 13 * TILE_SIZE)	continue;

			if (_vvTile[i][j]->enemy != NULL)
			{
				if (_vvTile[i][j]->enemy->getObjType() != OBJECT_TYPE_NONE)
				{

					int correctX;
					int correctY;
					string imgName = _vvTile[i][j]->objName;

					if (imgName == ENEMY_NAME[ENEMY_TYPE_SKELETON] || imgName == ENEMY_NAME[ENEMY_TYPE_SKELETON_YELLOW]
						|| imgName == ENEMY_NAME[ENEMY_TYPE_SKELETON_BLACK] || imgName == ENEMY_NAME[ENEMY_TYPE_SKELETON_MAGE_WHITE]
						|| imgName == ENEMY_NAME[ENEMY_TYPE_SKELETON_MAGE_YELLOW] || imgName == ENEMY_NAME[ENEMY_TYPE_SKELETON_MAGE_BLACK])
					{
						_vvTile[i][j]->enemy->render(_vvRECT[i][j].left, _vvRECT[i][j].top - 26);
					}
					else if (imgName == ENEMY_NAME[ENEMY_TYPE_ARMADILLO])
					{
						_vvTile[i][j]->enemy->render(_vvRECT[i][j].left + 2, _vvRECT[i][j].top - 26);
					}
					else if (imgName == ENEMY_NAME[ENEMY_TYPE_SLIME_GREEN] || imgName == ENEMY_NAME[ENEMY_TYPE_SLIME_GREEN]
						|| imgName == ENEMY_NAME[ENEMY_TYPE_ZOMBIE] || imgName == ENEMY_NAME[ENEMY_TYPE_CLONE])
					{
						_vvTile[i][j]->enemy->render(_vvRECT[i][j].left, _vvRECT[i][j].top - 26);
					}
					else if (imgName == ENEMY_NAME[ENEMY_TYPE_BAT] || imgName == ENEMY_NAME[ENEMY_TYPE_BAT_RED])
					{
						_vvTile[i][j]->enemy->render(_vvRECT[i][j].left, _vvRECT[i][j].top - 26);
					}
					else if (imgName == ENEMY_NAME[ENEMY_TYPE_BAT_MINIBOSS])
					{
						_vvTile[i][j]->enemy->render(_vvRECT[i][j].left - 10, _vvRECT[i][j].top - 26);
					}
					else if (imgName == ENEMY_NAME[ENEMY_TYPE_BANSHEE])
					{
						_vvTile[i][j]->enemy->render(_vvRECT[i][j].left - 12, _vvRECT[i][j].top - 52);
					}
					else if (imgName == ENEMY_NAME[ENEMY_TYPE_DRAGON_GREEN])
					{
						_vvTile[i][j]->enemy->render(_vvRECT[i][j].left - 27, _vvRECT[i][j].top - 72);
					}
					else if (imgName == ENEMY_NAME[ENEMY_TYPE_MINOTAUR])
					{
						_vvTile[i][j]->enemy->render(_vvRECT[i][j].left - 24, _vvRECT[i][j].top - 72);
					}
					else if (imgName == ENEMY_NAME[ENEMY_TYPE_CORALRIFF_DRUMS])
					{
						_vvTile[i][j]->enemy->render(_vvRECT[i][j].left - 10, _vvRECT[i][j].top - 72);
					}
					else if (imgName == ENEMY_NAME[ENEMY_TYPE_CORALRIFF_HEAD])
					{
						_vvTile[i][j]->enemy->render(_vvRECT[i][j].left - 16, _vvRECT[i][j].top - 84);
					}
					else if (imgName == ENEMY_NAME[ENEMY_TYPE_CORALRIFF_HORNS])
					{
						_vvTile[i][j]->enemy->render(_vvRECT[i][j].left - 16, _vvRECT[i][j].top - 76);
					}
					else if (imgName == ENEMY_NAME[ENEMY_TYPE_CORALRIFF_KEYTAR])
					{
						_vvTile[i][j]->enemy->render(_vvRECT[i][j].left - 6, _vvRECT[i][j].top - 72);
					}
					else if (imgName == ENEMY_NAME[ENEMY_TYPE_CORALRIFF_STRINGS])
					{
						_vvTile[i][j]->enemy->render(_vvRECT[i][j].left - 30, _vvRECT[i][j].top - 72);
					}
					else if (imgName == ENEMY_NAME[ENEMY_TYPE_SHOPKEEPER])
					{
						_vvTile[i][j]->enemy->render(_vvRECT[i][j].left - 22, _vvRECT[i][j].top - 40);
					}
				}
			}
		}
	}


}

void mapTool::drawUI()
{
	WCHAR str[128];

	//���� ���̸� 
	swprintf_s(str, L"%S", MAP_NAME_INFO[_curMapNum].c_str());
	D2DMANAGER->drawText(str, CAMERA->getPosX() + 767, CAMERA->getPosY() + _button[MAPTOOL_BUTTON_NAME].rc.top + 30, 20, RGB(255, 0, 0));
	swprintf_s(str, L"%S", MAP_NAME_INFO[_curMapNum].c_str());
	D2DMANAGER->drawText(str, CAMERA->getPosX() + 765, CAMERA->getPosY() + _button[MAPTOOL_BUTTON_NAME].rc.top + 30, 20, RGB(0, 255, 255));

	//��ư���
	for (int i = 0; i < MAPTOOL_BUTTON_COUNT; i++)
	{
		if (i == MAPTOOL_BUTTON_PREV || i == MAPTOOL_BUTTON_NEXT)
			_button[i].img->frameRender(CAMERA->getPosX() + _button[i].rc.left, CAMERA->getPosY() + _button[i].rc.top, 0, _button[i].curFrameY);
		else if (i >= MAPTOOL_BUTTON_SIZE_WIDTH_UP && i <= MAPTOOL_BUTTON_SIZE_HEIGHT_DOWN)
			_button[i].img->frameRender(CAMERA->getPosX() + _button[i].rc.left - 5, CAMERA->getPosY() + _button[i].rc.top + 2, 0, _button[i].curFrameY);
		else
			_button[i].img->frameRender(CAMERA->getPosX() + _button[i].rc.left + 10, CAMERA->getPosY() + _button[i].rc.top, 0, _button[i].curFrameY);
	}

	//��ũ��
	swprintf_s(str, L"����ũ��");
	D2DMANAGER->drawText(str, CAMERA->getPosX() + (WINSIZEX - 240) / 2 + 2, CAMERA->getPosY() + 12, 30, RGB(255, 0, 0));
	swprintf_s(str, L"����ũ��");
	D2DMANAGER->drawText(str, CAMERA->getPosX() + (WINSIZEX - 240) / 2, CAMERA->getPosY() + 10, 30, RGB(0, 255, 255));

	swprintf_s(str, L" ����: %d / ���� : %d", _tileX, _tileY);
	D2DMANAGER->drawText(str, CAMERA->getPosX() + (WINSIZEX - 240) / 2 - 23, CAMERA->getPosY() + 41, 15, RGB(255, 0, 0));
	swprintf_s(str, L" ����: %d / ���� : %d", _tileX, _tileY);
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

	if (_isOnTheImg)
	{
		if (_curButtonNum == MAPTOOL_BUTTON_ENEMY)
		{
			for (int i = 0; i < size; i++)
			{
				rc = { 0,0,0,0 };
				_vObj[i].setRC(rc);
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
						rc = { CAMERA->getPosX() + _sampleWindow.rc.left + (60 * x) + 20,
								CAMERA->getPosY() + _sampleWindow.rc.top + (80 * y) + 70,
								CAMERA->getPosX() + _sampleWindow.rc.left + (60 * x) + 20 + width,
								CAMERA->getPosY() + _sampleWindow.rc.top + (80 * y) + 70 + height };

						_vObj[i].setRC(rc);
						count++;

						IMAGEMANAGER->findImage(imgName)->frameRender(rc.left, rc.top, 0, 0);

						itemCount++;
					}
				}
				else if (_curImgNum == 1)
				{
					rc = { 0,0,0,0 };
					_vObj[i].setRC(rc);
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
						rc = { CAMERA->getPosX() + _sampleWindow.rc.left + (90 * x) + 10,
								CAMERA->getPosY() + _sampleWindow.rc.top + (110 * y) + 70,
								CAMERA->getPosX() + _sampleWindow.rc.left + (90 * x) + 10 + width,
								CAMERA->getPosY() + _sampleWindow.rc.top + (110 * y) + 70 + height };
					else if (count == 16)
						rc = { CAMERA->getPosX() + _sampleWindow.rc.left + (80 * x) + 10,
								CAMERA->getPosY() + _sampleWindow.rc.top + (110 * y) + 70,
								CAMERA->getPosX() + _sampleWindow.rc.left + (80 * x) + 10 + width,
								CAMERA->getPosY() + _sampleWindow.rc.top + (110 * y) + 70 + height };
					else if (count == 22)
						rc = { CAMERA->getPosX() + _sampleWindow.rc.left + (80 * x) + 10,
								CAMERA->getPosY() + _sampleWindow.rc.top + (105 * y) + 70,
								CAMERA->getPosX() + _sampleWindow.rc.left + (80 * x) + 10 + width,
								CAMERA->getPosY() + _sampleWindow.rc.top + (105 * y) + 70 + height };
					else
						rc = { CAMERA->getPosX() + _sampleWindow.rc.left + (90 * x) + 10,
								CAMERA->getPosY() + _sampleWindow.rc.top + (100 * y) + 70,
								CAMERA->getPosX() + _sampleWindow.rc.left + (90 * x) + 10 + width,
								CAMERA->getPosY() + _sampleWindow.rc.top + (100 * y) + 70 + height };

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
				rc = { 0,0,0,0 };
				_vObj[i].setRC(rc);
				if (_curImgNum == 0)
				{
					if (count < 24)
					{
						rc = { 0,0,0,0 };
						_vObj[i].setRC(rc);
						if (_vObj[i].getObjType() != num) continue;
						if (_vObj[i].getImg() == nullptr) continue;

						int x = count % 6;
						int y = count / 6;
						string imgName = _vObj[i].getImgName();
						width = IMAGEMANAGER->findImage(imgName)->GetFrameWidth();
						height = IMAGEMANAGER->findImage(imgName)->GetFrameHeight();
						rc = { CAMERA->getPosX() + _sampleWindow.rc.left + (60 * x) + 20,
								CAMERA->getPosY() + _sampleWindow.rc.top + (80 * y) + 70,
								CAMERA->getPosX() + _sampleWindow.rc.left + (60 * x) + 20 + width,
								CAMERA->getPosY() + _sampleWindow.rc.top + (80 * y) + 70 + height };

						_vObj[i].setRC(rc);
						count++;

						IMAGEMANAGER->findImage(imgName)->frameRender(rc.left, rc.top, 0, 0);

						itemCount++;
					}
				}
				else if (_curImgNum == 1)
				{
					rc = { 0,0,0,0 };
					_vObj[i].setRC(rc);
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
						rc = { CAMERA->getPosX() + _sampleWindow.rc.left + (60 * x) + 20,
								CAMERA->getPosY() + _sampleWindow.rc.top + (80 * y) + 70,
								(float)CAMERA->getPosX() + _sampleWindow.rc.left + (60 * x) + 20 + width,
								(float)CAMERA->getPosY() + _sampleWindow.rc.top + (80 * y) + 70 + height };

						_vObj[i].setRC(rc);

						IMAGEMANAGER->findImage(imgName)->frameRender(rc.left, rc.top, 0, 0);

						itemCount++;
					}
				}
				else if (_curImgNum == 2)
				{
					rc = { 0,0,0,0 };
					_vObj[i].setRC(rc);
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
						rc = { CAMERA->getPosX() + _sampleWindow.rc.left + (60 * x) + 20,
								CAMERA->getPosY() + _sampleWindow.rc.top + (80 * y) + 70,
								(float)CAMERA->getPosX() + _sampleWindow.rc.left + (60 * x) + 20 + width,
								(float)CAMERA->getPosY() + _sampleWindow.rc.top + (80 * y) + 70 + height };

						_vObj[i].setRC(rc);

						IMAGEMANAGER->findImage(imgName)->frameRender(rc.left, rc.top, 0, 0);

						itemCount++;
					}
				}
				else if (_curImgNum == 3)
				{
					rc = { 0,0,0,0 };
					_vObj[i].setRC(rc);
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
						rc = { CAMERA->getPosX() + _sampleWindow.rc.left + (60 * x) + 20,
								CAMERA->getPosY() + _sampleWindow.rc.top + (80 * y) + 70,
								(float)CAMERA->getPosX() + _sampleWindow.rc.left + (60 * x) + 20 + width,
								(float)CAMERA->getPosY() + _sampleWindow.rc.top + (80 * y) + 70 + height };

						_vObj[i].setRC(rc);

						IMAGEMANAGER->findImage(imgName)->frameRender(rc.left, rc.top, 0, 0);

						itemCount++;
					}
				}
				else if (_curImgNum == 4)
				{
					rc = { 0,0,0,0 };
					_vObj[i].setRC(rc);
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
							rc = { CAMERA->getPosX() + _sampleWindow.rc.left + (55 * x) + 20,
									CAMERA->getPosY() + _sampleWindow.rc.top + (82 * y) + 70,
									(float)CAMERA->getPosX() + _sampleWindow.rc.left + (55 * x) + 20 + width,
									(float)CAMERA->getPosY() + _sampleWindow.rc.top + (82 * y) + 70 + height };
						else
							rc = { CAMERA->getPosX() + _sampleWindow.rc.left + (60 * x) + 20,
									CAMERA->getPosY() + _sampleWindow.rc.top + (80 * y) + 70,
									(float)CAMERA->getPosX() + _sampleWindow.rc.left + (60 * x) + 20 + width,
									(float)CAMERA->getPosY() + _sampleWindow.rc.top + (80 * y) + 70 + height };

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
				rc = { 0,0,0,0 };
				_vObj[i].setRC(rc);
				if (_vObj[i].getObjType() != num) continue;
				if (_vObj[i].getImg() == nullptr) continue;

				int x = count % 6;
				int y = count / 6;
				string imgName = _vObj[i].getImgName();
				width = IMAGEMANAGER->findImage(imgName)->GetFrameWidth();
				height = IMAGEMANAGER->findImage(imgName)->GetFrameHeight();
				rc = { CAMERA->getPosX() + _sampleWindow.rc.left + (60 * x) + 20,
					   CAMERA->getPosY() + _sampleWindow.rc.top + (110 * y) + 70,
					   (float)CAMERA->getPosX() + _sampleWindow.rc.left + (60 * x) + 20 + width,
					   (float)CAMERA->getPosY() + _sampleWindow.rc.top + (110 * y) + 70 + height };

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
				rc = { 0,0,0,0 };
				_vObj[i].setRC(rc);
				if (_vObj[i].getObjType() != num) continue;
				if (_vObj[i].getImg() == nullptr) continue;

				int x = count % 5;
				int y = count / 5;
				string imgName = _vObj[i].getImgName();
				width = IMAGEMANAGER->findImage(imgName)->GetFrameWidth();
				height = IMAGEMANAGER->findImage(imgName)->GetFrameHeight();
				rc = { CAMERA->getPosX() + _sampleWindow.rc.left + (50 * x) + 20,
						CAMERA->getPosY() + _sampleWindow.rc.top + (70 * y) + 70,
						CAMERA->getPosX() + _sampleWindow.rc.left + (50 * x) + 20 + width,
						CAMERA->getPosY() + _sampleWindow.rc.top + (70 * y) + 70 + height };

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
				rc = { 0,0,0,0 };
				_vObj[i].setRC(rc);
				if (_vObj[i].getObjType() != num) continue;
				if (_vObj[i].getImg() == nullptr) continue;

				int x = count % 6;
				int y = count / 6;
				string imgName = _vObj[i].getImgName();
				width = IMAGEMANAGER->findImage(imgName)->GetFrameWidth();
				height = IMAGEMANAGER->findImage(imgName)->GetFrameHeight();
				rc = { CAMERA->getPosX() + _sampleWindow.rc.left + (60 * x) + 20,
					   CAMERA->getPosY() + _sampleWindow.rc.top + (70 * y) + 70,
					   (float)CAMERA->getPosX() + _sampleWindow.rc.left + (60 * x) + 20 + width,
					   (float)CAMERA->getPosY() + _sampleWindow.rc.top + (70 * y) + 70 + height };

				_vObj[i].setRC(rc);
				count++;

					IMAGEMANAGER->findImage(imgName)->frameRender(rc.left, rc.top, 0, 0);

				itemCount++;
			}
		}
	}
}
