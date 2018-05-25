#include "stdafx.h"
#include "Stage2_5.h"


Stage2_5::Stage2_5()
{
	IMAGEMANAGER.addImage("2.5앞배경", PathFile("image", "2-5앞배경").c_str(), 800, 400, true, RGB(255, 0, 255));
}


Stage2_5::~Stage2_5()
{
}

HRESULT Stage2_5::Init()
{
	ZORDER.Release();
	CAM.SetPos(0, 0);

	mObjfade = new MapObject(IMAGEMANAGER.findImage("페이드아웃"));
	mObjfade->Init(0, 0, 500, true);
	ZORDER.InputObj(mObjfade);

	_pm = new PlayerManager;
	_pm->Init();
	_pm->ChangeAnim(0, "RightRun");
	_pm->SetPlayerPos(-50, WINSIZEY / 2 - 50);

	//fadeOut = IMAGEMANAGER.findImage("페이드아웃");
	offset = 255;
	s5State = OPENNING;

	SOUNDMANAGER.play("18Stage2_5", 0.3f);

	return S_OK;
}

void Stage2_5::Render()
{
	IMAGEMANAGER.findImage("2.5앞배경")->Render(getMemDC(), CAM.GetX(), CAM.GetY(), CAM.GetX(), CAM.GetY(), WINSIZEX, GAMESIZEY);

	_pm->Render();

	//fadeOut->alphaRender(getMemDC(), CAM.GetX(), CAM.GetY(), offset);
}

void Stage2_5::Update()
{
	_pm->MoveRestrict((int)s5State);

	switch (s5State)
	{
	case OPENNING:
	{
		_pm->Update();

		CAM.Update(WINSIZEX / 2, WINSIZEY / 2, 5, false);

		offset -= 2;
		if (offset < 0)
		{
			s5State = FIRST_STAGE;
			offset = 0;
			CAM.SetSize(WINSIZEX, WINSIZEY);
			CAM.SetState("FOLLOW");
			_pm->ChangeAnim(0, "RightIdle");
		}
		mObjfade->Update(offset);
	}
	break;
	case FIRST_STAGE:
	{
		_pm->Update();
		CAM.Update(WINSIZEX / 2, WINSIZEY / 2, 5, false);

		if (KEYMANAGER.isOnceKeyDown(VK_SPACE))
		{
			s5State = WIN_STAGE;
			_pm->ChangeAnim(34, "RightOther");
		}
	}
	break;
	case WIN_STAGE:
	{
		_pm->Update();
		CAM.Update(WINSIZEX / 2, WINSIZEY / 2, 5, false);

		if (KEYMANAGER.isOnceKeyDown(VK_SPACE))
		{
			s5State = NEXT_STAGE;
		}
	}
	break;
	case NEXT_STAGE:
		CAM.Update(WINSIZEX / 2, WINSIZEY / 2, 5, false);
		offset += 2;
		if (offset > 255)
		{
			offset = 255;
			SCENEMANAGER.changeScene("StartScene");
			SOUNDMANAGER.stop("18Stage2_5");
			break;
		}
		mObjfade->Update(offset);

		break;
	}
}

void Stage2_5::Release()
{
	_pm->Release();
	SAFE_DELETE(_pm);

	mObjfade->Release();
	SAFE_DELETE(mObjfade);
}
