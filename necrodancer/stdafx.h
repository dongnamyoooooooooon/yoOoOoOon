// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//
// D2D 사용을 위한 lib
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "WindowsCodecs.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "Comdlg32.lib")

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>
#include <assert.h>
#include <Commdlg.h>
#include <atlbase.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <set>

// d2d 헤더파일임ㅋ
#include <d2d1.h>
#include <d2d1helper.h>
#include <wincodec.h>
#include <dwrite.h>

using namespace std;
using namespace D2D1;

#include "utils.h"
using namespace TEAM_15DUCK_UTILL;

#include "timeManager.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "imageManager.h"
#include "resource.h"
#include "d2dManager.h"
#include "camera.h"
#include "txtData.h"
#include "sceneManager.h"
#include "iniDataManager.h"
#include "soundManager.h"
#include "keyAniManager.h"
#include "effectManager.h"
#include "objectManager.h"


//====================================
// ## 18.11.20 ## - 디파인문 -
//====================================

#define WINNAME (LPCTSTR)(TEXT("넷흐로댄수ㅎㅅㅎ/"))


#define MAPTOOLSCENE	FALSE	
// ==============================================
//					 설     정
// ==============================================

#define TILE_SIZE			52							//타일사이즈는 20
#define SAMPLETILE			6							//샘플타일은 6
#define TOTAL_SAMPLE_SIZE	TILE_SIZE * SAMPLETILE		//샘플 총 개수 = 타일사이즈 * 샘플개수
#define WALLHEIGHT			104							//벽높이는 96
#define ANISPEED			8

#if MAPTOOLSCENE
	#define WINSIZEX 1500		//윈도우 가로크기
	#define WINSIZEY 900		//윈도우 세로크기
	#define WINSTARTX 0		//윈도우 시작 X좌표 
	#define WINSTARTY 0		//윈도우 시작 Y좌표

#else
	#define WINSIZEX 960		//윈도우 가로크기
	#define WINSIZEY 540		//윈도우 세로크기
	#define WINSTARTX 100		//윈도우 시작 X좌표 
	#define WINSTARTY 100		//윈도우 시작 Y좌표

#endif



#define MAPSIZEX 1600
#define MAPSIZEY 1200
#define WINSTYLE WS_CAPTION | WS_SYSMENU

#define RND randomFunction::getSingleton()
#define CAMERA camera::getSingleton()
#define TXTDATA txtData::getSingleton()
#define D2DMANAGER d2dManager::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define KEYANIMANAGER keyAniManager::getSingleton()
#define SOUNDMANAGER soundManager::getSingleton()
#define INIDATAMANAGER iniDataManager::getSingleton()
#define EFFECTMANAGER effectManager::getSingleton()
#define OBJECTMANAGER objectManager::getSingleton()

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

#define SAFE_DELETE(p) {if(p) { delete(p); (p) = nullptr; }}
#define SAFE_DELETE_ARRAY(p) {if(p) { delete[](p); (p) = NULL;}}
#define SAFE_RELEASE(p) {if(p) {(p)->release();}}
#define SAFE_RELEASE2(p) {if(p) {(p)->Release();}}
extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINTF _ptMouse;