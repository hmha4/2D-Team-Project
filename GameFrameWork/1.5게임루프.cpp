#include "stdafx.h"
#include "PlayGround.h"
//��������
HINSTANCE g_hInstance;
HWND g_hWnd;
POINT g_mousePos;
LPSTR g_lpszName = TEXT("���ӷ���");

PlayGround pg;//���������� �����Ҵ��Ͽ� ���

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam,LPARAM lParam);
void setWindowSize(int x, int y, int width, int height);
//�������Լ�
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
		//������ �޽����� ������ ���� ����ؼ� ���ư���
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;
			TranslateMessage(&msg);	//Ű���� �Է� �� ���콺 Ŭ�� �޽����� ó�� ���ش�
			DispatchMessage(&msg);	//������ �߻��� �޽������� �������ִ� ���� 
		}
		else
		{
			TIMEMANAGER.update(60.0f); 
			// Ÿ�̸ӿ� tick()�Լ� ���ο��� ����ð��� 1/60�ʰ� �ɶ����� while���� ����
			// ������ 1/60�ʸ��� ���� ������Ʈ�� ������ �̷�� ����.
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
//Ŭ���̾�Ʈ ���� �������� ���� �Լ�
void setWindowSize(int x, int y, int width, int height)
{
	//������ ��Ʈ
	RECT winRect;

	winRect.left = 0;
	winRect.top = 0;
	winRect.right = width;
	winRect.bottom = height;

	//������ �������� ���������ִ� �Լ�
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, false);

	SetWindowPos(g_hWnd, NULL, x, y, (winRect.right - winRect.left),
		(winRect.bottom - winRect.top), SWP_NOZORDER | SWP_NOMOVE);
}
