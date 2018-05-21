#pragma once
#include "gameNode.h"

class SelectScene : public gameNode
{
private:
	//게임관련 객체들이 들어갑니다
	typedef struct tagSELECT
	{
		image * img;
		float x, y;
		int frameX;
		int frameY;
		RECT rc;
		bool isSelect;

		tagSELECT() {}
		tagSELECT(string name, float x, float y,
			int frameX, int frameY, bool select)
			: x(x), y(y), frameX(frameX), frameY(frameY), isSelect(select)
		{
			img = IMAGEMANAGER.findImage("SelectBowman");
			rc = RectMakeCenter(x, y, img->GetFrameWidth(), img->GetFreamHeight());
		}
	} SELECT;

private:
	SELECT character[5];
	SELECT * _sel;

public:
	SelectScene();
	~SelectScene();

	HRESULT Init();
	void Render();
	void Update();
	void Release();
};

