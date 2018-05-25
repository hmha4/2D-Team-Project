#include "stdafx.h"
#include "Stage2_2.h"


Stage2_2::Stage2_2()
{
	IMAGEMANAGER.addImage("2.2앞배경", PathFile("image", "2-2앞배경").c_str(), 2438, 400, true, RGB(255, 0, 255));
	IMAGEMANAGER.addImage("2.2뒷배경", PathFile("image", "2-2뒷배경").c_str(), 1829, 400, true, RGB(255, 0, 255));
}


Stage2_2::~Stage2_2()
{
}

HRESULT Stage2_2::Init()
{
	ZORDER.Release();
	CAM.SetPos(0, 0);

	mObjfade = new MapObject(IMAGEMANAGER.findImage("페이드아웃"));
	mObjfade->Init(0, 0, 500, 4, true);
	ZORDER.InputObj(mObjfade);

	_pm = new PlayerManager;
	_pm->Init();
	_pm->ChangeAnim(0, "RightRun");
	_pm->SetPlayerPos(-50, WINSIZEY / 2 - 50);

	//fadeOut = IMAGEMANAGER.findImage("페이드아웃");
	offset = 255;
	s2State = OPENNING;

	SOUNDMANAGER.play("15Stage2_2", 0.3f);
	return S_OK;
}

void Stage2_2::Render()
{
	IMAGEMANAGER.findImage("2.2뒷배경")->Render(getMemDC(), CAM.GetX(), CAM.GetY(), CAM.GetX() * 0.1, CAM.GetY(), WINSIZEX, GAMESIZEY);
	IMAGEMANAGER.findImage("2.2앞배경")->Render(getMemDC(), CAM.GetX(), CAM.GetY(), CAM.GetX(), CAM.GetY(), WINSIZEX, GAMESIZEY);

	_pm->Render();

	//fadeOut->alphaRender(getMemDC(), CAM.GetX(), CAM.GetY(), offset);
}

void Stage2_2::Update()
{
	_pm->MoveRestrict((int)s2State);

	switch (s2State)
	{
	case OPENNING:
	{
		_pm->Update();

		CAM.Update(WINSIZEX / 2, WINSIZEY / 2, 5, false);

		offset -= 2;
		if (offset < 0)
		{
			s2State = FIRST_STAGE;
			offset = 0;
			CAM.SetSize(2438, WINSIZEY);
			CAM.SetState("FOLLOW");
			_pm->ChangeAnim(0, "RightIdle");
		}
		mObjfade->Update(offset);
	}
	break;
	case FIRST_STAGE:
	{
		_pm->Update();
		CAM.Update(_pm->GetPlayer1()->GetX(), _pm->GetPlayer1()->GetY(), 5, false);

		if (KEYMANAGER.isOnceKeyDown(VK_SPACE))
		{
			s2State = WIN_STAGE;
			CAM.SetSize(GAMESIZEX, WINSIZEY);
			_pm->ChangeAnim(34, "RightOther");
		}
	}
	break;
	case WIN_STAGE:
		_pm->Update();
		CAM.Update(2438 - WINSIZEX / 2, WINSIZEY / 2, 5, false);

		if (_pm->GetPlayer1()->GetX() > 2438 - 250 && _pm->GetPlayer1()->GetX() < 2438 - 150 &&
			_pm->GetPlayer1()->GetY() <= WINSIZEY / 2 - 50)
		{
			s2State = NEXT_STAGE;
		}
		break;
	case NEXT_STAGE:
		CAM.Update(2438 - WINSIZEX / 2, WINSIZEY / 2, 5, false);
		offset += 2;
		if (offset > 255)
		{
			offset = 255;
			SCENEMANAGER.changeScene("스테이지2.3");
			SOUNDMANAGER.stop("15Stage2_2");
			break;
		}
		mObjfade->Update(offset);

		break;
	}
}

void Stage2_2::Release()
{
	_pm->Release();
	SAFE_DELETE(_pm);

	mObjfade->Release();
	SAFE_DELETE(mObjfade);
}
