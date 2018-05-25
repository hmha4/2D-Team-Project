#pragma once
#include "gameNode.h"
#include "MapObject.h"
#include "PlayerManager.h"
#include "EnemyManager.h"

class Stage2_1 :
	public gameNode
{
private:
	enum STAGE1STATE
	{
		OPENNING,
		FIRST_STAGE,		//전반
		SECOND_STAGE,		//후반
		WIN_STAGE,
		NEXT_STAGE = 20
	};

private:
	STAGE1STATE s1State;

	MapObject*mObjfade;

	image*fadeOut;
	int offset;

	PlayerManager * _pm;
	EnemyManager*_em;

	bool changeView;
	bool isLast;
public:
	Stage2_1();
	~Stage2_1();

	HRESULT Init();
	void Render();
	void Update();
	void Release();

	void Save();
};

