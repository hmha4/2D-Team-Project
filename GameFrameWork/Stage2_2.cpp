#include "stdafx.h"
#include "Stage2_2.h"
#include "Bullet.h"

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

	_em = new EnemyManager;
	_em->InputEnemy(BLACKARCHOR, 3);
	_em->InputEnemy(WAREWOLF, 4);
	_em->InputEnemy(SKELETON, 5);
	_em->InputEnemy(CYCLOPSE, 1);
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
			_pm->ChangeAnim(34, "RightOther");
			for (int i = 0; i < 4; i++)
				_em->ShowEnemy(WAREWOLF, WINSIZEX +200, 120 + i * 60, LEFT_IDLE);
			for (int i = 0; i < 2; i++)
				_em->ShowEnemy(BLACKARCHOR, WINSIZEX+200, 180 + i * 60, LEFT_IDLE);
			SOUNDMANAGER.play("27WareWolf");
			SOUNDMANAGER.play("45BlackArcher");
		}
		mObjfade->Update(offset);
	}
	break;
	case FIRST_STAGE:
	{
		CAM.SetSize(1800, WINSIZEY);
		_em->Update(_pm);
		_pm->Update();
		CAM.Update(_pm->GetPlayer1()->GetX(), _pm->GetPlayer1()->GetY(), 5, false);
		if (_em->GetEnemyNum() == 0)
			_em->GetUI()->SetDrawGo(false);
		if (_em->GetEnemyNum() == 0&&_pm->GetPlayer1()->GetX()>1700)
		{
			s2State = SECOND_STAGE;
			CAM.SetSize(GAMESIZEX, WINSIZEY);
			
			for (int i = 0; i < 5; i++)
				_em->ShowEnemy(SKELETON, _pm->GetPlayer1()->GetX() + RND.GetFromTo(200, 400), RND.GetFromTo(200, 350), LEFT_IDLE);
			for (int i = 0; i < 1; i++)
				_em->ShowEnemy(CYCLOPSE, 2200, 220, LEFT_IDLE);
			SOUNDMANAGER.play("26Skeleton");
			SOUNDMANAGER.play("46Cyclopse");
		}
	}
	break;
	case SECOND_STAGE:
	{
		CAM.Update(2438 - WINSIZEX / 2, WINSIZEY / 2, 5, false);
		_pm->Update();
		_em->Update(_pm);

		if (_em->GetEnemyNum() == 0)
		{
			s2State = WIN_STAGE;
			CAM.SetSize(GAMESIZEX, WINSIZEY);
			_pm->ChangeAnim(34, "RightOther");
			_em->GetUI()->SetDrawGo(true);
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
			Save();
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

void Stage2_2::Save()
{
	DATABASE.SaveData("1PWeapon", _pm->GetPlayer1()->GetWeaponLv());
	if (DATABASE.LoadData("1P2P") == 1)
	{
		DATABASE.SaveData("2PWeapon", _pm->GetPlayer2()->GetWeaponLv());
	}
}
