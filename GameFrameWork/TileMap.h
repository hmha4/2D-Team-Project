#pragma once
#include "gameNode.h"
#include "button.h"

#define BUILDTILEX	13
#define BUILDTILEY	8

#define SHOWTILEX	28
#define SHOWTILEY	30

#define TILESIZEXY  50

struct TileInfo 
{
	enum TILETYPE
	{
		NONE,
		PLAYER_SPAWN,
		ROAD,
		BLOCK
	};
	string tileName;
	image*tileImg;
	RECT rc;
	int frameX;
	int frameY;
	TILETYPE tileType;

	TileInfo(){}
	TileInfo(string tName,image*img,TILETYPE type)
		:tileName(tName), tileImg(img),tileType(type)
	{
		frameX = 0;
		frameY = 0;
		rc = RectMake(frameX, frameY, TILESIZEXY, TILESIZEXY);
	}
};

class TileMap :public gameNode
{
private:
	//설치할 타일맵
	TileInfo*buildTiles;
	//선택한 타일
	TileInfo*selectTile;
	//설치될 타일공간
	TileInfo*showTiles;
	//버튼종류:NONE,PLAYERSPAWN,ROAD,BLOCK
	button*buttons[4];
	//세이브버튼
	button*save;
	//로드버튼
	button*load;
	//카메라 움직이게할 렉트
	RECT cam;
	//메타인덱스
	int metaIdx;
public:
	TileMap();
	~TileMap();

	HRESULT Init();
	void Render();
	void Update();
	void Release();

	//설치할 타일과 설치될 타일공간초기화
	void TileInit();
	//설치할 타일맵 렌더
	void BuildTileRender();
	//설치될 타일맵 렌더
	void ShowTileRender();
	//버튼렌더
	void ButtonsRender();
	//버튼업데이트
	void ButtonsUpdate();
	//카메라 조작
	void ControlCam();
	//마우스로 타일선택업데이트
	void SelectTileMap();
	//타일설치
	void SettingTileMap();

	void SaveTileMap();
	void LoadTileMap();
	POINT TransCamMouse();
};

