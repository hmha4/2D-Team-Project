#include "stdafx.h"
#include "Stage1_3.h"
#include "Bullet.h"

Stage1_3::Stage1_3()
{
	IMAGEMANAGER.addImage("1.3배경", PathFile("image", "1-3배경").c_str(), 800, 400, true, NULL);
}


Stage1_3::~Stage1_3()
{
}

HRESULT Stage1_3::Init()
{
	ZORDER.Release();

	CAM.SetPos(0, 0);
	CAM.SetSize(WINSIZEX, WINSIZEY);

	mObjfade = new MapObject(IMAGEMANAGER.findImage("페이드아웃"));
	mObjfade->Init(0, 0, 500, 2, true);
	ZORDER.InputObj(mObjfade);

	s3State = OPENNING;

	_pm = new PlayerManager;
	_pm->Init();
	_pm->SetPlayerPos(WINSIZEX / 2, -50);
	_pm->ChangeAnim(10, "RightFall");

	_em = new EnemyManager;
	_em->Init();
	_em->InputEnemy(DRAGONKNIGHT, 1);

	//fadeOut = IMAGEMANAGER.findImage("페이드아웃");
	offset = 255;

	_time = 0;
	_totalTime = 0;

	SOUNDMANAGER.play("09Stage1_Boss", 0.3f);

	return S_OK;
}

void Stage1_3::Render()
{
	IMAGEMANAGER.findImage("1.3배경")->Render(getMemDC(), CAM.GetX(), CAM.GetY(), CAM.GetX(), CAM.GetY(), WINSIZEX, GAMESIZEY);

	_pm->Render();

	//fadeOut->alphaRender(getMemDC(), CAM.GetX(), CAM.GetY(), offset);

	Rectangle(getMemDC(), _em->GetEnemyVec(DRAGONKNIGHT)[0]->getShadowColRc().left, _em->GetEnemyVec(DRAGONKNIGHT)[0]->getShadowColRc().top, _em->GetEnemyVec(DRAGONKNIGHT)[0]->getShadowColRc().right, _em->GetEnemyVec(DRAGONKNIGHT)[0]->getShadowColRc().bottom);
}

void Stage1_3::Update()
{
	_pm->MoveRestrict((int)s3State);

	RECT temp;
	if (IntersectRect(&temp, &_em->GetEnemyVec(DRAGONKNIGHT)[0]->getShadowColRc(), &_pm->GetPlayer1()->getRc()))
	{
		_pm->GetPlayer1()->Collision(_em->GetEnemyVec(DRAGONKNIGHT)[0]->getShadowColRc());
	}

	switch (s3State)
	{
	case OPENNING:
	{
		_pm->Update();
		CAM.Update(WINSIZEX / 2, WINSIZEY / 2, 5, false);

		if (!isOnceShow)
		{
			_em->ShowEnemy(DRAGONKNIGHT, WINSIZEX / 2 + 200, WINSIZEY / 2 + 30, LEFT_IDLE);
			isOnceShow = true;
		}

		offset -= 2;
		if (offset < 0)
		{
			offset = 0;
			s3State = FIRST_STAGE;
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
			SOUNDMANAGER.play("10Victory");
			_pm->ChangeWeapon(3);
		}
	}
	break;
	case WIN_STAGE:
		_pm->Update();
		CAM.Update(WINSIZEX / 2, WINSIZEY / 2, 5, false);

		_totalTime += TIMEMANAGER.getElapsedTime();
		if (_totalTime >= 2.0f)
		{
			_totalTime = 0;
			s3State = NEXT_STAGE;
			break;
		}
		break;
	case NEXT_STAGE:
		offset += 2;
		if (offset > 255)
		{
			offset = 255;
			Save();
			SOUNDMANAGER.stop("09Stage1_Boss");
			SCENEMANAGER.changeScene("스테이지2.1");
			break;
		}
		mObjfade->Update(offset);
		_pm->Update();
		CAM.Update(WINSIZEX / 2, WINSIZEY / 2, 5, false);

		break;
	}
}

void Stage1_3::Release()
{
	_pm->Release();
	SAFE_DELETE(_pm);

	mObjfade->Release();
	SAFE_DELETE(mObjfade);
}

void Stage1_3::Save()
{
	DATABASE.SaveData("1PWeapon", _pm->GetPlayer1()->GetWeaponLv());
	if (DATABASE.LoadData("1P2P") == 1)
	{
		DATABASE.SaveData("2PWeapon", _pm->GetPlayer2()->GetWeaponLv());
	}
}
