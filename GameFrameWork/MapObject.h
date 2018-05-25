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

	bool isStageStart;
	bool startFadeIn;
	int minusAlpha;
	int stageNum;
	int stageAlpha;
public:
	MapObject(image*img);
	~MapObject();

	HRESULT Init();
	HRESULT Init(int x,int y, int amount, int _stageNum = 8, bool fade = false);
	void Render();
	void Update(int opaque);
	void Release();

    virtual inline RECT&getRc() { return shadowRc; }
};

