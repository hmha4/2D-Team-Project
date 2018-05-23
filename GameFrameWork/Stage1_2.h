#pragma once
#include "gameNode.h"
#include "MapObject.h"
#include "PlayerManager.h"
#include "EnemyManager.h"

class Stage1_2 :
	public gameNode
{
private:
	enum STAGE2STATE
	{
		OPENNING,
		FIRST_STAGE,		//전반
		SECOND_STAGE,		//후반
		FINAL_STAGE,
		WIN_STAGE,
		NEXT_STAGE = 11
	};

private:
	STAGE2STATE s2State;

	image*fadeOut;
	int offset;

	PlayerManager * _pm;
	EnemyManager*_em;

	bool changeView;
	float _time;
	float _totalTime;
public:
	Stage1_2();
	~Stage1_2();

	HRESULT Init();
	void Render();
	void Update();
	void Release();
};

