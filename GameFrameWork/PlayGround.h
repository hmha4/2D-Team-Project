#pragma once
#include "gameNode.h"
#include "Stage1_1.h"
class PlayGround:public gameNode
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

