#pragma once
#include "gameNode.h"

class button : public gameNode
{
private:
	enum BUTTONSTATE
	{
		BUTTON_DOWN,
		BUTTON_UP,
		BUTTON_NULL
	};
private:
	BUTTONSTATE bState;
	image*img;
	RECT rc;
	float x, y;

	int frameX;
	bool isOnceClick;
	bool isStayClick;
	int fontSize;

	string buttonName;
	string fontstyle;

public:
	button();
	~button();

	//��ư����ϱ� ���ؼ� �̸����������Ѵ�
	HRESULT Init(image*img, string bName, float x, float y, string fontStyle,int fontSize);
	void Render();
	void Update(int key, bool isUseCam);
	void Release();

	void ButtonNameDraw();

	inline bool&IsOnceClick() { return isOnceClick; }
	inline bool&IsStayClick() { return isStayClick; }
	inline RECT&GetRect() { return rc; }
};
