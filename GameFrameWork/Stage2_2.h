#pragma once
#include "gameNode.h"
#include "PlayerManager.h"

class Stage2_2 :
	public gameNode
{
private:
	enum STAGE2STATE
	{
		OPENNING,
		FIRST_STAGE,		//Àü¹Ý
		WIN_STAGE,
		NEXT_STAGE = 21
	};

private:
	STAGE2STATE s2State;

	image*fadeOut;
	int offset;

	PlayerManager * _pm;
public:
	Stage2_2();
	~Stage2_2();

	HRESULT Init();
	void Render();
	void Update();
	void Release();
};

