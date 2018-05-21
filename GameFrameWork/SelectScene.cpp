#include "stdafx.h"
#include "SelectScene.h"


SelectScene::SelectScene()
{
}


SelectScene::~SelectScene()
{
}

HRESULT SelectScene::Init()
{
	CAM.SetPos(0, 0);
	IMAGEMANAGER.addImage("SelectSceneBackground", PathFile("image\\Scene", "SelectScene").c_str(), 800, 500, false, RGB(0, 0, 0));
	IMAGEMANAGER.addFrameImage("SelectBowman", PathFile("image\\Scene", "SelectBowman").c_str(), 270, 212, 3, 1, true, RGB(255, 0, 255));

	character[0] = SELECT("SelectBowman", CAM.GetX() + 100, CAM.GetY() + WINSIZEY / 2 + 100, 2, 0, false);


	return S_OK;
}

void SelectScene::Render()
{
	IMAGEMANAGER.findImage("SelectSceneBackground")->Render(getMemDC(), CAM.GetX(), CAM.GetY());

	character[0].img->frameRender(getMemDC(), character[0].rc.left, character[0].rc.top, character[0].frameX, 0);
}

void SelectScene::Update()
{
}

void SelectScene::Release()
{
	
}
