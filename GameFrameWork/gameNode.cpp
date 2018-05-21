#include "stdafx.h"
#include "gameNode.h"


HRESULT gameNode::Init()
{
    hdc = GetDC(g_hWnd);//실제 DC영역의 기능 받아옴
    _managerInit = false;

    return S_OK;
}
HRESULT gameNode::init(bool managerInit)
{
    hdc = GetDC(g_hWnd);//실제 DC영역의 기능 받아옴
    _managerInit = managerInit;

    if (_managerInit)
    {
        //SetTimer(g_hWnd, 1, 10, NULL);
        KEYMANAGER.init();
        IMAGEMANAGER.Init();
        TIMEMANAGER.init();
        EFFECTMANAGER.init();
        SOUNDMANAGER.init();
        TXT.init();
        ZORDER.init();
        ANIMATIONKEY.init();
        CAM.Init("backBuffer");
        CAM.SetPos(0, 0);
    }
    return S_OK;
}
void gameNode::Release()
{
    if (_managerInit)
    {
        //KillTimer(g_hWnd, 1);
        KEYMANAGER.ReleaseSingleton();
        IMAGEMANAGER.ReleaseSingleton();
        TIMEMANAGER.ReleaseSingleton();
        EFFECTMANAGER.ReleaseSingleton();
        SOUNDMANAGER.ReleaseSingleton();
        TXT.ReleaseSingleton();
        ZORDER.ReleaseSingleton();
        ANIMATIONKEY.ReleaseSingleton();
        CAM.ReleaseSingleton();
		DATABASE.Release();
		DATABASE.ReleaseSingleton();
    }
    ReleaseDC(g_hWnd, hdc);//종료될시 해제해줌
}

void gameNode::Render()
{
}

void gameNode::Update()
{
    InvalidateRect(g_hWnd, NULL, false);
}


LRESULT gameNode::MainProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch (msg)
    {
    case WM_CREATE:
    {

    }
    break;
    case WM_MOUSEMOVE:
        g_mousePos.x = LOWORD(lParam);
        g_mousePos.y = HIWORD(lParam);
        break;
    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            break;
        }
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return (DefWindowProc(hWnd, msg, wParam, lParam));
}

gameNode::gameNode()
{
}


gameNode::~gameNode()
{
}

