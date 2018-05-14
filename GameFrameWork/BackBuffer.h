#pragma once
struct BackBufferInfo
{
	HDC hBackDC; // 백버퍼 DC영역
	HBITMAP hBit; // 빈 비트맵 이미지 
	HBITMAP hOldBit; // 올드 비트맵
	int width;
	int height;

	BackBufferInfo() // 구조체의 생성자
	{
		hBackDC = NULL;
		hBit = NULL;
		hOldBit = NULL;
		width = 0;
		height = 0;
	}
};
class BackBuffer
{
private:
	BackBufferInfo*backBuffer; //백버퍼 구조체 포인터
public:
	BackBuffer();
	~BackBuffer();

	HRESULT Init(int width, int height); // 백버퍼 초기화
	void Render(HDC hdc); // 백버퍼->앞버퍼 복사
	void Release(); // 메모리 해제

	//백버퍼 DC영역에 접근자
	inline HDC GetBackDC() { return backBuffer->hBackDC; }
};

