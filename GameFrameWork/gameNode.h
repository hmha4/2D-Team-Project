#pragma once
#include "image.h"

//�����=>���� �̰����� ������ �׸��� �׸�
static image* backBuffer = IMAGEMANAGER.addImage("backBuffer", GAMESIZEX, WINSIZEY);
class gameNode
{
private:
	HDC hdc; // ���� DC����
	bool _managerInit;
public:
	//HRESULT == MS���� 
	//S_OK, E_FAIL, SUCCEDED ���� ���â�� ǥ�����ش�
	virtual HRESULT Init();//�ʱ�ȭ
	virtual HRESULT init(bool managerInit);
	virtual void Render();//������
	virtual void Update();//������Ʈ
	virtual void Release();//�޸�����

	//����� ������=>����ۿ��� ���� DC������ ��Ӻ��� �ϱ�����
	image* getBackBuffer(void) { return backBuffer; }

	//������� DC������ ������
	HDC getMemDC() { return backBuffer->getMemDC(); } 

	//����DC������ ������
	HDC getHDC() { return hdc; } 

	//��¥�� ���Լ��� �������̵����� �������� ȣ��ȵǰ� �ҰŶ�
	virtual inline RECT&getRc() { return RectMake(0, 0, 0, 0); }

	//�����Լ��� ���ǵ� Render�� Update�� �̰����� ���ȴ�.
	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);

	gameNode();
	virtual ~gameNode();
};

