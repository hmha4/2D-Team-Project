#pragma once
#include "image.h"

//백버퍼=>실제 이곳에다 앞으로 그림을 그림
static image* backBuffer = IMAGEMANAGER.addImage("backBuffer", GAMESIZEX, WINSIZEY);
class gameNode
{
private:
	HDC hdc; // 실제 DC영역
	bool _managerInit;
public:
	//HRESULT == MS전용 
	//S_OK, E_FAIL, SUCCEDED 등을 출력창에 표시해준다
	virtual HRESULT Init();//초기화
	virtual HRESULT init(bool managerInit);
	virtual void Render();//렌더링
	virtual void Update();//업데이트
	virtual void Release();//메모리해제

	//백버퍼 접근자=>백버퍼에서 실제 DC영역에 고속복사 하기위해
	image* getBackBuffer(void) { return backBuffer; }

	//백버퍼의 DC영역에 접근자
	HDC getMemDC() { return backBuffer->getMemDC(); } 

	//실제DC영역에 접근자
	HDC getHDC() { return hdc; } 

	//어짜피 이함수는 오버라이딩으로 가려져서 호출안되게 할거라
	virtual inline RECT&getRc() { return RectMake(0, 0, 0, 0); }

	//가상함수로 정의된 Render와 Update가 이곳에서 사용된다.
	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);

	gameNode();
	virtual ~gameNode();
};

