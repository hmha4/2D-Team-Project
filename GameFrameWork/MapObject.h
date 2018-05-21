#pragma once
#include "gameNode.h"
class MapObject:public gameNode
{
private:
	image*img;
	int setX, setY;
    RECT rc;
	RECT shadowRc;
public:
	MapObject(image*img);
	~MapObject();

	HRESULT Init();
	HRESULT Init(int x,int y);
	void Render();
	void Update();
	void Release();

    virtual inline RECT&getRc() { return shadowRc; }
};

