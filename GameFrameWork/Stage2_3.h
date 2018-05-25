#pragma once
#include "gameNode.h"
#include "MapObject.h"
#include "PlayerManager.h"

class Stage2_3 : 
	public gameNode
{
private:
	enum STAGE3STATE
	{
		OPENNING,
		FIRST_STAGE,		//Àü¹Ý
		WIN_STAGE,
		NEXT_STAGE = 22
	};

private:
	STAGE3STATE s3State;

	MapObject*mObjfade;

	image*fadeOut;
	int offset;

	PlayerManager * _pm;
public:
	Stage2_3();
	~Stage2_3();

	HRESULT Init();
	void Render();
	void Update();
	void Release();
};

