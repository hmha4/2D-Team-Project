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
	HDC hdc = GetDC(g_hWnd); // �⺻������ HDC���� ��Ʈ�� �Ӽ��� ����=>�����޸��̱� ������
	
	backBuffer = new BackBufferInfo;
	backBuffer->hBackDC = CreateCompatibleDC(hdc); // �޸�DC����
	backBuffer->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height); // hdc�� ��Ʈ������ ����/��ȯ
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
	//������� DC�� �׷����� �͵��� ��DC�� ��Ӻ��� ���ִ� �Լ�
	BitBlt(hdc, 0, 0, backBuffer->width, backBuffer->height,
		backBuffer->hBackDC, 0, 0, SRCCOPY);
}

void BackBuffer::Release()
{
	if (backBuffer) // ����ۿ� ���� ������
	{
		SelectObject(backBuffer->hBackDC, backBuffer->hOldBit);
		DeleteObject(backBuffer->hBit);
		DeleteDC(backBuffer->hBackDC);
		
		delete backBuffer;
	}
}
