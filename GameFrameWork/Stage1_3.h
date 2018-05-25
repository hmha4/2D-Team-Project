#pragma once
#include "gameNode.h"
#include "MapObject.h"
#include "PlayerManager.h"
#include "EnemyManager.h"
class Stage1_3 :public gameNode
{
private:
	enum STAGE3STATE
	{
		OPENNING,
		FIRST_STAGE,		//����
		SECOND_STAGE,		//�Ĺ�
		FINAL_STAGE,
		WIN_STAGE,
		NEXT_STAGE = 13
	};

private:
	STAGE3STATE s3State;

	MapObject*mObjfade;

	image*fadeOut;
	int offset;

	PlayerManager * _pm;
	EnemyManager*_em;

	float _time;
	float _totalTime;

	bool isOnceShow = false;
public:
	Stage1_3();
	~Stage1_3();

	HRESULT Init();
	void Render();
	void Update();
	void Release();

	void Save();
};

