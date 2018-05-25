#pragma once
#include "gameNode.h"
#include "MapObject.h"
#include "PlayerManager.h"
#include "EnemyManager.h"

class Stage2_2 :
	public gameNode
{
private:
	enum STAGE2STATE
	{
		OPENNING,
		FIRST_STAGE,		//Àü¹Ý
		SECOND_STAGE,
		WIN_STAGE,
		NEXT_STAGE = 21
	};

private:
	STAGE2STATE s2State;

	MapObject*mObjfade;

	image*fadeOut;
	int offset;

	PlayerManager * _pm;
	EnemyManager*_em;
public:
	Stage2_2();
	~Stage2_2();

	HRESULT Init();
	void Render();
	void Update();
	void Release();

	void Save();
};

