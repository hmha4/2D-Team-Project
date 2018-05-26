#include "stdafx.h"
#include "Stage2_4.h"


Stage2_4::Stage2_4()
{
	IMAGEMANAGER.addImage("2.4앞배경", PathFile("image", "2-4앞배경").c_str(), 3652, 400, true, RGB(255, 0, 255));
	IMAGEMANAGER.addImage("2.4뒷배경", PathFile("image", "2-4뒷배경").c_str(), 1829, 400, true, RGB(255, 0, 255));
	IMAGEMANAGER.addImage("2.4배경오브젝트", PathFile("image", "2-4제트오더").c_str(), 179, 400, true, RGB(255, 0, 255));
}


Stage2_4::~Stage2_4()
{
}

HRESULT Stage2_4::Init()
{
	ZORDER.Release();
	CAM.SetPos(0, 0);

	MapObject*mObj = new MapObject(IMAGEMANAGER.findImage("2.4배경오브젝트"));
	mObj->Init(2555, 0, 400);
	ZORDER.InputObj(mObj);

	mObjfade = new MapObject(IMAGEMANAGER.findImage("페이드아웃"));
	mObjfade->Init(0, 0, 500, 6, true);
	ZORDER.InputObj(mObjfade);

	_pm = new PlayerManager;
	_pm->Init();
	_pm->ChangeAnim(0, "RightRun");
	_pm->SetPlayerPos(-50, WINSIZEY / 2 - 50);

	//fadeOut = IMAGEMANAGER.findImage("페이드아웃");
	offset = 255;
	s4State = OPENNING;

	SOUNDMANAGER.play("17Stage2_4", 0.3f);

	return S_OK;
}

void Stage2_4::Render()
{
	IMAGEMANAGER.findImage("2.4뒷배경")->Render(getMemDC(), CAM.GetX(), CAM.GetY(), CAM.GetX() * 0.1, CAM.GetY(), WINSIZEX, GAMESIZEY);
	IMAGEMANAGER.findImage("2.4앞배경")->Render(getMemDC(), CAM.GetX(), CAM.GetY(), CAM.GetX(), CAM.GetY(), WINSIZEX, GAMESIZEY);

	_pm->Render();

	//fadeOut->alphaRender(getMemDC(), CAM.GetX(), CAM.GetY(), offset);
}

void Stage2_4::Update()
{
	_pm->MoveRestrict((int)s4State);

	switch (s4State)
	{
	case OPENNING:
	{
		_pm->Update();

		CAM.Update(WINSIZEX / 2, WINSIZEY / 2, 5, false);

		offset -= 2;
		if (offset < 0)
		{
			s4State = FIRST_STAGE;
			offset = 0;
			CAM.SetSize(GAMESIZEX, WINSIZEY);
			CAM.SetState("FOLLOW");
			_pm->ChangeAnim(34, "RightOther");
		}
		mObjfade->Update(offset);
	}
	break;
	case FIRST_STAGE:
	{
		_pm->Update();
		CAM.Update(_pm->GetPlayer1()->GetX(), _pm->GetPlayer1()->GetY(), 5, false);

		if (_pm->GetPlayer1()->GetX() > GAMESIZEX - 60)
		{
			s4State = NEXT_STAGE;
		}
	}
	break;
	case NEXT_STAGE:
		CAM.Update(3652 - WINSIZEX / 2, WINSIZEY / 2, 5, false);
		offset += 2;
		if (offset > 255)
		{
			offset = 255;
			Save();
			SCENEMANAGER.changeScene("스테이지2.5");
			SOUNDMANAGER.stop("17Stage2_4");
			break;
		}
		mObjfade->Update(offset);

		break;
	}
}

void Stage2_4::Release()
{
	_pm->Release();
	SAFE_DELETE(_pm);

	mObjfade->Release();
	SAFE_DELETE(mObjfade);
}

void Stage2_4::Save()
{
	DATABASE.SaveData("1PWeapon", _pm->GetPlayer1()->GetWeaponLv());
	if (DATABASE.LoadData("1P2P") == 1)
	{
		DATABASE.SaveData("2PWeapon", _pm->GetPlayer2()->GetWeaponLv());
	}
}
