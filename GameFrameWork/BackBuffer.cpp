#include "stdafx.h"
#include "BackBuffer.h"


BackBuffer::BackBuffer()
	:backBuffer(NULL)
{
}


BackBuffer::~BackBuffer()
{
}

HRESULT BackBuffer::Init(int width, int height)
{
	HDC hdc = GetDC(g_hWnd); // 기본적으로 HDC에는 비트맵 속성이 있음=>비디오메모리이기 때문에
	
	backBuffer = new BackBufferInfo;
	backBuffer->hBackDC = CreateCompatibleDC(hdc); // 메모리DC생성
	backBuffer->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height); // hdc의 비트맵정보 생성/반환
	backBuffer->hOldBit = (HBITMAP)SelectObject(backBuffer->hBackDC, backBuffer->hBit);
	backBuffer->width = width;
	backBuffer->height = height;

	if (backBuffer->hBit == NULL)
		return E_FAIL;

	ReleaseDC(g_hWnd, hdc);

	return S_OK;
}

void BackBuffer::Render(HDC hdc)
{
	//백버퍼의 DC에 그려지는 것들을 앞DC에 고속복사 해주는 함수
	BitBlt(hdc, 0, 0, backBuffer->width, backBuffer->height,
		backBuffer->hBackDC, 0, 0, SRCCOPY);
}

void BackBuffer::Release()
{
	if (backBuffer) // 백버퍼에 값이 있으면
	{
		SelectObject(backBuffer->hBackDC, backBuffer->hOldBit);
		DeleteObject(backBuffer->hBit);
		DeleteDC(backBuffer->hBackDC);
		
		delete backBuffer;
	}
}
