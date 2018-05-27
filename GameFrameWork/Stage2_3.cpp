#include "stdafx.h"
#include "Stage2_3.h"


Stage2_3::Stage2_3()
{
	IMAGEMANAGER.addImage("2.3앞배경", PathFile("image", "2-3앞배경").c_str(), 800, 400, true, RGB(255, 0, 255));
}


Stage2_3::~Stage2_3()
{
}

HRESULT Stage2_3::Init()
{
	ZORDER.Release();
	CAM.SetPos(0, 0);

	mObjfade = new MapObject(IMAGEMANAGER.findImage("페이드아웃"));
	mObjfade->Init(0, 0, 500, 5, true);
	ZORDER.InputObj(mObjfade);

	_pm = new PlayerManager;
	_pm->Init();
	_pm->SetPlayerPos(WINSIZEX/2, -50);
	_pm->ChangeAnim(10, "RightFall");

	_em = new EnemyManager("Dark Mage");
	_em->InputEnemy(EVILMAGE, 1);
	//fadeOut = IMAGEMANAGER.findImage("페이드아웃");
	offset = 255;
	s3State = OPENNING;

	SOUNDMANAGER.play("16Stage2_3", 0.3f);
	return S_OK;
}

void Stage2_3::Render()
{
	IMAGEMANAGER.findImage("2.3앞배경")->Render(getMemDC(), CAM.GetX(), CAM.GetY(), CAM.GetX(), CAM.GetY(), WINSIZEX, GAMESIZEY);

	_pm->Render();

	//fadeOut->alphaRender(getMemDC(), CAM.GetX(), CAM.GetY(), offset);
}

void Stage2_3::Update()
{
	_pm->MoveRestrict((int)s3State);

	switch (s3State)
	{
	case OPENNING:
	{
		_pm->Update();

		CAM.Update(WINSIZEX / 2, WINSIZEY / 2, 5, false);

		offset -= 2;
		if (offset < 0)
		{
			s3State = FIRST_STAGE;
			offset = 0;
			CAM.SetSize(WINSIZEX, WINSIZEY);
			CAM.SetState("FOLLOW");
			_em->ShowEnemy(EVILMAGE, WINSIZEX / 2 + 200, -100, LEFT_IDLE);
			SOUNDMANAGER.play("48DarkMage");
		}
		mObjfade->Update(offset);
	}
	break;
	case FIRST_STAGE:
	{
		_pm->Update();
		_em->Update(_pm);
		CAM.Update(WINSIZEX / 2, WINSIZEY / 2, 5, false);

		if (_em->GetEnemyNum() == 0)
		{
			s3State = WIN_STAGE;
			_pm->ChangeAnim(34, "RightOther");
			_pm->ChangeWeapon(4);
		}
	}
	break;
	case WIN_STAGE:
	{
		_pm->Update();
		CAM.Update(WINSIZEX / 2, WINSIZEY / 2, 5, false);

		static float time = 0;
		time += TIMEMANAGER.getElapsedTime();

		if (time > 2)
		{
			time = 0;
			s3State = NEXT_STAGE;
		}
	}
		break;
	case NEXT_STAGE:
		CAM.Update(WINSIZEX / 2, WINSIZEY / 2, 5, false);
		offset += 2;
		if (offset > 255)
		{
			offset = 255;
			Save();
			SOUNDMANAGER.stop("16Stage2_3");
			SCENEMANAGER.changeScene("스테이지2.4");
			
			break;
		}
		mObjfade->Update(offset);

		break;
	}
}

void Stage2_3::Release()
{
	_pm->Release();
	SAFE_DELETE(_pm);

	mObjfade->Release();
	SAFE_DELETE(mObjfade);
}

void Stage2_3::Save()
{
	DATABASE.SaveData("1PWeapon", _pm->GetPlayer1()->GetWeaponLv());
	if (DATABASE.LoadData("1P2P") == 1)
	{
		DATABASE.SaveData("2PWeapon", _pm->GetPlayer2()->GetWeaponLv());
	}
}


