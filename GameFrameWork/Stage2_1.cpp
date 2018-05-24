#include "stdafx.h"
#include "Stage2_1.h"


Stage2_1::Stage2_1()
{
	IMAGEMANAGER.addImage("2.1앞배경", PathFile("image", "2-1앞배경").c_str(), 3652, 400, true, RGB(255, 0, 255));
	IMAGEMANAGER.addImage("2.1뒷배경", PathFile("image", "2-1뒷배경").c_str(), 1114, 149, true, RGB(255, 0, 255));
	IMAGEMANAGER.addImage("2.1배경오브젝트", PathFile("image", "2-1제트오더").c_str(), 2614, 62, true, RGB(255, 0, 255));
}


Stage2_1::~Stage2_1()
{
}

HRESULT Stage2_1::Init()
{
	ZORDER.Release();

	MapObject*mObj = new MapObject(IMAGEMANAGER.findImage("2.1배경오브젝트"));
	mObj->Init(0, 350, 62);
	ZORDER.InputObj(mObj);

	_pm = new PlayerManager;
	_pm->Init();
	_pm->ChangeAnim(0, "RightRun");

	fadeOut = IMAGEMANAGER.findImage("페이드아웃");
	offset = 255;
	s1State = OPENNING;

	return S_OK;
}

void Stage2_1::Render()
{
	IMAGEMANAGER.findImage("2.1뒷배경")->Render(getMemDC(), CAM.GetX(), CAM.GetY(), CAM.GetX() * 0.1, CAM.GetY(), WINSIZEX, 149);
	IMAGEMANAGER.findImage("2.1앞배경")->Render(getMemDC(), CAM.GetX(), CAM.GetY(), CAM.GetX(), CAM.GetY(), WINSIZEX, GAMESIZEY);

	_pm->Render();

	fadeOut->alphaRender(getMemDC(), CAM.GetX(), CAM.GetY(), offset);
}

void Stage2_1::Update()
{
	_pm->MoveRestrict((int)s1State);

	switch (s1State)
	{
	case OPENNING:
	{
		_pm->Update();

		CAM.Update(WINSIZEX / 2, WINSIZEY / 2, 5, false);

		offset -= 2;
		if (offset < 0)
		{
			s1State = FIRST_STAGE;
			offset = 0;
			CAM.SetSize(1400, WINSIZEY);
			CAM.SetState("FOLLOW");
			_pm->ChangeAnim(0, "RightIdle");
		}
	}
	break;
	case FIRST_STAGE:
	{
		_pm->Update();
		CAM.Update(_pm->GetPlayer1()->GetX(), _pm->GetPlayer1()->GetY(), 5, false);
	
		if (KEYMANAGER.isOnceKeyDown(VK_SPACE))
		{
			s1State = SECOND_STAGE;
			CAM.SetSize(GAMESIZEX, WINSIZEY);
		}
	}
	break;
	case SECOND_STAGE:
	{
		_pm->Update();
		CAM.Update(_pm->GetPlayer1()->GetX(), _pm->GetPlayer1()->GetY(), 5, false);
	
		if (KEYMANAGER.isOnceKeyDown(VK_SPACE))
		{
			s1State = WIN_STAGE;
			CAM.SetSize(GAMESIZEX, WINSIZEY);
			_pm->ChangeAnim(34, "RightOther");
		}
	}
	break;
	case WIN_STAGE:
		_pm->Update();
		CAM.Update(3652 - WINSIZEX / 2, WINSIZEY / 2, 5, false);

		if (_pm->GetPlayer1()->GetX() > 3652 - WINSIZEX / 2 - 20 && _pm->GetPlayer1()->GetX() < 3652 - WINSIZEX / 2 + 20 &&
			_pm->GetPlayer1()->GetY() <= WINSIZEY / 2 - 50)
		{
			s1State = NEXT_STAGE;
		}
		break;
	case NEXT_STAGE:
		CAM.Update(3652 - WINSIZEX / 2, WINSIZEY / 2, 5, false);
		offset += 2;
		if (offset > 255)
		{
			offset = 255;
			break;
		}

		break;
	}
}

void Stage2_1::Release()
{
}
