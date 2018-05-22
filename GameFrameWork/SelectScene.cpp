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
	//ĳ����
	IMAGEMANAGER.addImage("SelectSceneBackground", PathFile("image\\Scene", "SelectScene").c_str(), 800, 500, false, RGB(0, 0, 0));
	IMAGEMANAGER.addFrameImage("SelectBowman", PathFile("image\\Scene", "SelectBowman").c_str(), 270, 212, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER.addFrameImage("SelectMagician", PathFile("image\\Scene", "SelectMagician").c_str(), 270, 190, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER.addFrameImage("SelectWarrior", PathFile("image\\Scene", "SelectWarrior").c_str(), 276, 212, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER.addFrameImage("SelectCleric", PathFile("image\\Scene", "SelectCleric").c_str(), 288, 220, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER.addFrameImage("SelectDwerf", PathFile("image\\Scene", "SelectDwerf").c_str(), 270, 186, 3, 1, true, RGB(255, 0, 255));
	//ĳ���� �̸�
	IMAGEMANAGER.addFrameImage("SelectName", PathFile("image\\Scene", "SelectName").c_str(), 100, 150, 1, 5, true, RGB(255, 0, 255));
	//����Ʈ ����Ʈ
	IMAGEMANAGER.addFrameImage("Select1P2P", PathFile("image\\Scene", "Select1P2P").c_str(), 128, 48, 2, 1, true, RGB(255, 0, 255));

	float num = WINSIZEX / 5;

	character[0] = SELECT("SelectBowman", CAM.GetX() + num * 0 + 80, CAM.GetY() + WINSIZEY / 2 + 0, 2, 0, false);
	character[1] = SELECT("SelectMagician", CAM.GetX() + num * 1 + 80, CAM.GetY() + WINSIZEY / 2 + 60, 0, 1, false);
	character[2] = SELECT("SelectWarrior", CAM.GetX() + num * 2 + 80, CAM.GetY() + WINSIZEY / 2 + 100, 0, 2, false);
	character[3] = SELECT("SelectCleric", CAM.GetX() + num * 3 + 80, CAM.GetY() + WINSIZEY / 2 + 50, 2, 3, false);
	character[4] = SELECT("SelectDwerf", CAM.GetX() + num * 4 + 80, CAM.GetY() + WINSIZEY / 2 + 20, 2, 4, false);

	_sel1Index = 2;
	_sel2Index = 1;
	_sel[0] = SELECT("Select1P2P", character[_sel1Index].x, character[_sel1Index].y, 0, 0, true);
	_sel[1] = SELECT("Select1P2P", character[_sel2Index].x, character[_sel2Index].y, 1, 0, true);

	return S_OK;
}

void SelectScene::Render()
{
	IMAGEMANAGER.findImage("SelectSceneBackground")->Render(getMemDC(), CAM.GetX(), CAM.GetY());

	for (int i = 0; i < 5; i++)
	{
		character[i].img->frameRender(getMemDC(), character[i].rc.left, character[i].rc.top, character[i].frameX, 0);

		character[i].imgName->frameRender(getMemDC(), character[i].rc.left, character[i].rc.bottom - 10, 0, character[i].frameY);
	}

	for (int i = 0; i < 2; i++)
		_sel[i].img->frameRender(getMemDC(), _sel[i].rc.left, _sel[i].rc.top, _sel[i].frameX, _sel[i].frameY);
}

void SelectScene::Update()
{
	if (KEYMANAGER.isOnceKeyDown('J'))
	{
		if(_sel1Index < 4)
			_sel1Index++;
		if (_sel2Index == _sel1Index)
			_sel1Index++;
		if (_sel1Index > 4)
			_sel1Index -= 2;
		ChangeCharacter(0, _sel1Index);
	}
	else if (KEYMANAGER.isOnceKeyDown('G'))
	{
		if (_sel1Index > 0)
			_sel1Index--;
		if (_sel2Index == _sel1Index)
			_sel1Index--;
		if (_sel1Index < 0)
			_sel1Index += 2;
		ChangeCharacter(0, _sel1Index);
	}

	if (KEYMANAGER.isOnceKeyDown(VK_NUMPAD6))
	{
		if (_sel2Index < 4)
			_sel2Index++;
		if (_sel2Index == _sel1Index)
			_sel2Index++;
		if (_sel2Index > 4)
			_sel2Index -= 2;
		ChangeCharacter(1, _sel2Index);
	}
	else if (KEYMANAGER.isOnceKeyDown(VK_NUMPAD4))
	{
		if (_sel2Index > 0)
			_sel2Index--;
		if (_sel2Index == _sel1Index)
			_sel2Index--;
		if (_sel2Index < 0)
			_sel2Index += 2;
		ChangeCharacter(1, _sel2Index);
	}

	if (KEYMANAGER.isOnceKeyDown(VK_RETURN))
	{
		DATABASE.SaveData("1P2P", 1);
		DATABASE.SaveData("1PCharacter", _sel1Index);
		DATABASE.SaveData("2PCharacter", _sel2Index);
		SCENEMANAGER.changeScene("��������1.1");
	}


	CAM.Update(WINSIZEX / 2, WINSIZEY / 2, 0, false);
}

void SelectScene::Release()
{

}

void SelectScene::ChangeCharacter(int p1p2, int index)
{
	_sel[p1p2].x = character[index].x;
	_sel[p1p2].y = character[index].y;
	_sel[p1p2].rc = RectMakeCenter(_sel[p1p2].x, _sel[p1p2].y, _sel[p1p2].img->GetFrameWidth(), _sel[p1p2].img->GetFreamHeight());
}