#pragma once
#include "gameNode.h"

class PlayGround:public gameNode
{
private:
	//���Ӱ��� ��ü���� ���ϴ�
	
public:
	PlayGround();
	~PlayGround();
	
	virtual HRESULT Init();
	virtual void Render();
	virtual void Update();
	virtual void Release();

};

