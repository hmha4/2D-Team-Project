#include "stdafx.h"
#include "InGame.h"


InGame::InGame()
{
	IMAGEMANAGER.addFrameImage("≈∏¿œ∏ ", PathFile("image", "≈∏¿œ≈ı").c_str(), 650, 400, 13, 8, false, RGB(255, 0, 255));
}


InGame::~InGame()
{
}

HRESULT InGame::Init()
{
	rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 10, 10);
	CAM.CamInit(CENTER_CAMERA, GetCenterPos(rc).x, GetCenterPos(rc).y, WINSIZEX, WINSIZEY, 5);
	gameMap = new TileInfo[SHOWTILEX*SHOWTILEY];
	for (int i = 0; i < SHOWTILEX*SHOWTILEY; i++)
		gameMap[i].tileImg = IMAGEMANAGER.findImage("≈∏¿œ∏ ");

	LoadGameMap();
	return S_OK;
}

void InGame::Render()
{
	for (int i = 0; i < SHOWTILEY; i++)
	{
		for (int j = 0; j < SHOWTILEX; j++)
		{
			if (gameMap[j + i*SHOWTILEX].tileType != TileInfo::NONE)
			{
				gameMap[j + i*SHOWTILEX].tileImg->frameRender(getMemDC(),
					gameMap[j + i*SHOWTILEX].rc.left,
					gameMap[j + i*SHOWTILEX].rc.top,
					gameMap[j + i*SHOWTILEX].frameX,
					gameMap[j + i*SHOWTILEX].frameY);
			}
		}
	}
}

void InGame::Update()
{
	if (KEYMANAGER.isOnceKeyDown(VK_RETURN))
		SCENEMANAGER.changeScene("∏ º¬∆√");

	if (KEYMANAGER.isStayKeyDown(VK_LEFT))
	{
		rc.left -= 5;
		rc.right -= 5;
	}
	if (KEYMANAGER.isStayKeyDown(VK_RIGHT))
	{
		rc.left += 5;
		rc.right += 5;
	}
	if (KEYMANAGER.isStayKeyDown(VK_UP))
	{
		rc.top -= 5;
		rc.bottom -= 5;
	}
	if (KEYMANAGER.isStayKeyDown(VK_DOWN))
	{
		rc.top += 5;
		rc.bottom += 5;
	}
	CAM.CamUpdate(rc, 0, 2000, 0, 1500);
}

void InGame::Release()
{
}

void InGame::LoadGameMap()
{
	FILE*fp;
	fopen_s(&fp, "≈∏¿œ∏ µ•¿Ã≈Õ.txt", "r");

	char name[256];
	int type;
	int x;
	int y;
	int frameX;
	int frameY;
	
	while (true)
	{
		fscanf_s(fp, "%s", name, sizeof(name));
		if (string(name).find("frameY", 0) != string::npos)
			break;
	}

	while (true)
	{
		fscanf_s(fp, "%s", name, sizeof(name));
		if (name[0] == '@')break;

		fscanf_s(fp, "%d%d%d%d%d",&type, &x, &y, &frameX, &frameY);
		
		gameMap[x / TILESIZEXY + y / TILESIZEXY*SHOWTILEX].tileType = (TileInfo::TILETYPE)type;
		gameMap[x / TILESIZEXY + y / TILESIZEXY*SHOWTILEX].rc = RectMake(x, y, TILESIZEXY, TILESIZEXY);
		gameMap[x / TILESIZEXY + y / TILESIZEXY*SHOWTILEX].frameX = frameX;
		gameMap[x / TILESIZEXY + y / TILESIZEXY*SHOWTILEX].frameY = frameY;
	}
	fclose(fp);
}
