#pragma once
#include "gameNode.h"
#include "PlayerManager.h"

class Stage2_5 :
	public gameNode
{
private:
	enum STAGE5STATE
	{
		OPENNING,
		FIRST_STAGE,		//Àü¹Ý
		WIN_STAGE,
		NEXT_STAGE = 23
	};

private:
	STAGE5STATE s5State;

	image*fadeOut;
	int offset;

	PlayerManager * _pm;

public:
	Stage2_5();
	~Stage2_5();

	HRESULT Init();
	void Render();
	void Update();
	void Release();
};

