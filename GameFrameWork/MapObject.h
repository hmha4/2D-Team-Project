#pragma once
#include "gameNode.h"
class MapObject:public gameNode
{
private:
	image*img;
	int setX, setY;
    RECT rc;
	RECT shadowRc;

	bool isFade;
	int alpha;
public:
	MapObject(image*img);
	~MapObject();

	HRESULT Init();
	HRESULT Init(int x,int y, int amount, bool fade = false);
	void Render();
	void Update(int opaque);
	void Release();

    virtual inline RECT&getRc() { return shadowRc; }
};

