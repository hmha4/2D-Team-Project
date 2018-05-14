#pragma once
#include "TileMap.h"
#include "gameNode.h"
class MapSetting:public gameNode
{
private:
	TileMap*tm;
public:
	MapSetting();
	~MapSetting();

	HRESULT Init();
	void Render();
	void Release();
	void Update();
};

