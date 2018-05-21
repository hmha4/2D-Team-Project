#pragma once
#include "gameNode.h"
#include "MapObject.h"
#include "PlayerManager.h"

class Stage1_1:public gameNode
{
private:
	enum STAGE1STATE
	{
		OPENNING,
		FIRST_STAGE,		//����
		SECOND_STAGE		//�Ĺ�
	};

private:
	STAGE1STATE s1State;
	
	
	image*fadeOut;
	int offset;

	PlayerManager * _pm;
public:
	Stage1_1();
	~Stage1_1();

	HRESULT Init();
	void Render();
	void Update();
	void Release();
};

