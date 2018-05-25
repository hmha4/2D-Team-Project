#pragma once
#include "gameNode.h"

class SelectScene : public gameNode
{
private:
	//게임관련 객체들이 들어갑니다
	typedef struct tagSELECT
	{
		image * img;
		image * imgName;
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
			img = IMAGEMANAGER.findImage(name);
			imgName = IMAGEMANAGER.findImage("SelectName");
			rc = RectMakeCenter(x, y, img->GetFrameWidth(), img->GetFreamHeight());
		}

	} SELECT;

	enum STATE
	{
		FIRST,
		SECOND,
		LAST
	};
private:
	STATE _state;

	SELECT character[5];
	SELECT _sel[2];

	int _sel1Index;
	int _sel2Index;

	int _playerNum;

	image * _fade;
	int _offSet;
	bool _changeScene;

	image* _img;
	animation* _anim;
public:
	SelectScene();
	~SelectScene();

	HRESULT Init();
	void Render();
	void Update();
	void Release();

	void ChangeCharacter(int p1p2, int index);
};

