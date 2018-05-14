#pragma once
#include "TileMap.h"
#include "gameNode.h"
class InGame:public gameNode
{
private:
	TileInfo*gameMap;

	RECT rc;
public:
	InGame();
	~InGame();

	HRESULT Init();
	void Render();
	void Update();
	void Release();

	void LoadGameMap();
};

