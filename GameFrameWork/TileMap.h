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
	//��ġ�� Ÿ�ϸ�
	TileInfo*buildTiles;
	//������ Ÿ��
	TileInfo*selectTile;
	//��ġ�� Ÿ�ϰ���
	TileInfo*showTiles;
	//��ư����:NONE,PLAYERSPAWN,ROAD,BLOCK
	button*buttons[4];
	//���̺��ư
	button*save;
	//�ε��ư
	button*load;
	//ī�޶� �����̰��� ��Ʈ
	RECT cam;
	//��Ÿ�ε���
	int metaIdx;
public:
	TileMap();
	~TileMap();

	HRESULT Init();
	void Render();
	void Update();
	void Release();

	//��ġ�� Ÿ�ϰ� ��ġ�� Ÿ�ϰ����ʱ�ȭ
	void TileInit();
	//��ġ�� Ÿ�ϸ� ����
	void BuildTileRender();
	//��ġ�� Ÿ�ϸ� ����
	void ShowTileRender();
	//��ư����
	void ButtonsRender();
	//��ư������Ʈ
	void ButtonsUpdate();
	//ī�޶� ����
	void ControlCam();
	//���콺�� Ÿ�ϼ��þ�����Ʈ
	void SelectTileMap();
	//Ÿ�ϼ�ġ
	void SettingTileMap();

	void SaveTileMap();
	void LoadTileMap();
	POINT TransCamMouse();
};

