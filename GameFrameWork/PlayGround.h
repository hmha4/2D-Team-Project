#pragma once
#include "gameNode.h"
#include "Stage1_1.h"
#include "PlayUI.h"
class PlayGround:public gameNode
{
private:
	//���Ӱ��� ��ü���� ���ϴ�
	PlayUI*		_UI;

public:
	PlayGround();
	~PlayGround();
	
	virtual HRESULT Init();
	virtual void Render();
	virtual void Update();
	virtual void Release();

};

