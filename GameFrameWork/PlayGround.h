#pragma once
#include "gameNode.h"
#include "Stage1_1.h"
#include "Stage1_2.h"
#include "Stage1_3.h"
#include "Stage2_1.h"
#include "Stage2_2.h"
#include "Stage2_3.h"
#include "Stage2_4.h"
#include "Stage2_5.h"
#include "SelectScene.h"
#include "StartScene.h"

class PlayGround :public gameNode
{
private:
	//게임관련 객체들이 들어갑니다


public:
	PlayGround();
	~PlayGround();

	virtual HRESULT Init();
	virtual void Render();
	virtual void Update();
	virtual void Release();

};

