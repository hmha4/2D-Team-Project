#pragma once
#include "gameNode.h"

class StartScene :
	public gameNode
{
private:
	enum STATE
	{
		STATE_01,
		STATE_02,
		STATE_03,
		STATE_04,
		STATE_05
	};

	struct tagButton
	{
		image * img;
		float x, y;
		RECT rc;
		int alpha;
		bool isClick;
		int frameY;

		tagButton() {}
		tagButton(float posX, float posY, int frameY)
			: x(posX), y(posY), alpha(255), isClick(false), frameY(frameY)
		{
			img = IMAGEMANAGER.findImage("StartScene_05_Button");
			rc = RectMakeCenter(x, y, img->GetFrameWidth(), img->GetFreamHeight());
		}
	};

	STATE _state;
	image * _img;
	animation * _anim;

	int _buttonIndex;
	tagButton _button[2];
	float _buttonCount;
public:
	StartScene();
	~StartScene();

	HRESULT Init();
	void Render();
	void Update();
	void Release();

	void ChangeAnim(STATE state, string name);
};

