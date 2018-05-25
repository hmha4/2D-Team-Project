#pragma once
#include "gameNode.h"
#include "MapObject.h"
#include "PlayerManager.h"
#include "EnemyManager.h"

class Stage1_1 :public gameNode
{
private:
	enum STAGE1STATE
	{
		OPENNING,
		FIRST_STAGE,		//����
		SECOND_STAGE,		//�Ĺ�
		NEXT_STAGE = 10
	};

private:
	STAGE1STATE s1State;

	MapObject*mObjfade;

	image*fadeOut;
	int offset;

	PlayerManager * _pm;
	EnemyManager*_em;

	bool changeView;
public:
	Stage1_1();
	~Stage1_1();

	HRESULT Init();
	void Render();
	void Update();
	void Release();
};

