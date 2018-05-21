// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.

//	��ó���� ���ǹ�
#ifdef _DEBUG
#pragma comment (linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <math.h>
#include <iostream>

// Windows ��� ����:
#include <windows.h>

using namespace std;

#include "mymecro.h"
#include "KeyManager.h"
#include "RandomManager.h"
#include "ImageManager.h"
#include "TimeManager.h"
#include "effectManager.h"
#include "soundManager.h"
#include "txtData.h"
#include "zOrderManager.h"
#include "KeyAniManager.h"
#include "CameraManager.h"
#include "BulletManager.h"
#include "sceneManager.h"
#include "DataBase.h"


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#define WINSIZEX 800
#define WINSIZEY 500
#define WINPOSX 400
#define WINPOSY 100
#define GAMESIZEX 3652
#define GAMESIZEY 400

#define KEYMANAGER KeyManager::GetInstance()
#define RND RandomManager::GetInstance()
#define IMAGEMANAGER ImageManager::GetInstance()
#define TIMEMANAGER TimeManager::GetInstance()
#define EFFECTMANAGER effectManager::GetInstance()
#define SOUNDMANAGER soundManager::GetInstance()
#define TXT	txtData::GetInstance()
#define ZORDER zOrderManager::GetInstance()
#define ANIMATIONKEY KeyAniManager::GetInstance()
#define CAM CameraManager::GetInstance()
#define BULLET BulletManager::GetInstance()
#define SCENEMANAGER sceneManager::GetInstance()
#define DATABASE DataBase::GetInstance()

#define SAFE_DELETE(p) {if(p) { delete(p); (p) = NULL;}}
#define SAFE_RELEASE(p) {if(p) {(p)->Release(); (p)=NULL;}}

#define PI 3.14

extern HWND g_hWnd;
extern POINT g_mousePos;
extern HINSTANCE g_hInstance;


