#pragma once
#include "gameNode.h"
#include "MapObject.h"
#include "PlayerManager.h"

class Stage1_2 :
	public gameNode
{
private:
	enum STAGE2STATE
	{
		OPENNING,
		FIRST_STAGE,		//����
		SECOND_STAGE,		//�Ĺ�
		FINAL_STAGE,
		WIN_STAGE,
		NEXT_STAGE = 11
	};

private:
	STAGE2STATE s2State;


	image*fadeOut;
	int offset;

	PlayerManager * _pm;

	float _time;
	float _totalTime;

	int _playerNum;
public:
	Stage1_2();
	~Stage1_2();

	HRESULT Init();
	void Render();
	void Update();
	void Release();
};

