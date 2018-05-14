#include "stdafx.h"
#include "PlayGround.h"
//전역변수
HINSTANCE g_hInstance;
HWND g_hWnd;
POINT g_mousePos;
LPSTR g_lpszName = TEXT("게임루프");

PlayGround pg;//전역변수로 정적할당하여 사용

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam,LPARAM lParam);
void setWindowSize(int x, int y, int width, int height);
//윈메인함수
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpszCmdParam, int cmdShow)
{
	WNDCLASS wnd;

	g_hInstance = hInstance;

	wnd.cbClsExtra = 0;
	wnd.cbWndExtra = 0;
	wnd.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
	wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wnd.hInstance = g_hInstance;
	wnd.lpfnWndProc = WndProc;
	wnd.lpszClassName = g_lpszName;
	wnd.lpszMenuName = NULL;
	wnd.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wnd);

	g_hWnd = CreateWindow(g_lpszName, g_lpszName, WS_OVERLAPPEDWINDOW, WINPOSX, WINPOSY, WINSIZEX, WINSIZEY, 
		NULL, NULL, hInstance, NULL);

	setWindowSize(WINSIZEX, WINSIZEY, WINSIZEX, WINSIZEY);

	ShowWindow(g_hWnd, cmdShow);
	if (FAILED(pg.Init()))
	{
		return 0;
	}
	MSG msg;

	while (true)
	{
		//윈도우 메시지가 들어오던 말던 계속해서 돌아간다
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;
			TranslateMessage(&msg);	//키보드 입력 및 마우스 클릭 메시지를 처리 해준다
			DispatchMessage(&msg);	//실제로 발생한 메시지들을 전달해주는 역할 
		}
		else
		{
			TIMEMANAGER.update(60.0f); 
			// 타이머에 tick()함수 내부에서 경과시간이 1/60초가 될때까지 while문이 돌기
			// 때문에 1/60초마다 실제 업데이트와 렌더가 이루어 진다.
			pg.Update();
			pg.Render();
		}
	}
	pg.Release();
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return pg.MainProc(hWnd, msg, wParam, lParam);	
}
//클라이언트 영역 재조정을 위한 함수
void setWindowSize(int x, int y, int width, int height)
{
	//윈도우 렉트
	RECT winRect;

	winRect.left = 0;
	winRect.top = 0;
	winRect.right = width;
	winRect.bottom = height;

	//윈도우 실제영역 재조정해주는 함수
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, false);

	SetWindowPos(g_hWnd, NULL, x, y, (winRect.right - winRect.left),
		(winRect.bottom - winRect.top), SWP_NOZORDER | SWP_NOMOVE);
}
