#pragma once
#include "gameNode.h"
#include "MapObject.h"
#include "Warrior.h"
#include "Magician.h"

class Stage1_1:public gameNode
{
private:
	enum STAGE1STATE
	{
		OPENNING,
		FIRST_STAGE,		//전반
		SECOND_STAGE		//후반
	};

private:
	STAGE1STATE s1State;
	
	
	image*fadeOut;
	int offset;

    Character * _warrior;
	Character * _magician;
public:
	Stage1_1();
	~Stage1_1();

	HRESULT Init();
	void Render();
	void Update();
	void Release();
};

