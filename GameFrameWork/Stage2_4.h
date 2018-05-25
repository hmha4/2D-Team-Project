#pragma once
#include "gameNode.h"
#include "MapObject.h"
#include "PlayerManager.h"

class Stage2_4 :
	public gameNode
{
private:
	enum STAGE4STATE
	{
		OPENNING,
		FIRST_STAGE,		//Àü¹Ý
		WIN_STAGE,
		NEXT_STAGE = 23
	};

private:
	STAGE4STATE s4State;

	MapObject*mObjfade;

	image*fadeOut;
	int offset;

	PlayerManager * _pm;

public:
	Stage2_4();
	~Stage2_4();

	HRESULT Init();
	void Render();
	void Update();
	void Release();
};

