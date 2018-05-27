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
	CAM.SetPos(0, 0);

	MapObject*mObj = new MapObject(IMAGEMANAGER.findImage("2.1배경오브젝트"));
	mObj->Init(0, 350, 62);
	ZORDER.InputObj(mObj);

	mObjfade = new MapObject(IMAGEMANAGER.findImage("페이드아웃"));
	mObjfade->Init(0, 0, 500, 3, true);
	ZORDER.InputObj(mObjfade);

	_pm = new PlayerManager;
	_pm->Init();
	_pm->ChangeAnim(0, "RightRun");

	_em = new EnemyManager;
	_em->InputEnemy(BLACKARCHOR, 3);
	_em->InputEnemy(SKELETON, 6);
	_em->InputEnemy(MINO, 2);


	//fadeOut = IMAGEMANAGER.findImage("페이드아웃");
	offset = 255;
	s1State = OPENNING;
	changeView = false;
	isLast = false;
	SOUNDMANAGER.play("14Stage2_1", 0.3f);
	return S_OK;
}

void Stage2_1::Render()
{
	IMAGEMANAGER.findImage("2.1뒷배경")->Render(getMemDC(), CAM.GetX(), CAM.GetY(), CAM.GetX() * 0.1, CAM.GetY(), WINSIZEX, 149);
	IMAGEMANAGER.findImage("2.1앞배경")->Render(getMemDC(), CAM.GetX(), CAM.GetY(), CAM.GetX(), CAM.GetY(), WINSIZEX, GAMESIZEY);

	_pm->Render();

	//fadeOut->alphaRender(getMemDC(), CAM.GetX(), CAM.GetY(), offset);
}

void Stage2_1::Update()
{
	_pm->MoveRestrict((int)s1State);

	RECT temp;
	if (IntersectRect(&temp, &_em->GetEnemyVec(MINO)[0]->getShadowColRc(), &_pm->GetPlayer1()->getRc()))
	{
		_pm->GetPlayer1()->Collision(_em->GetEnemyVec(MINO)[0]->getShadowColRc(), "normal");
	}
	RECT temp2;
	if (IntersectRect(&temp2, &_em->GetEnemyVec(MINO)[1]->getShadowColRc(), &_pm->GetPlayer1()->getRc()))
	{
		_pm->GetPlayer1()->Collision(_em->GetEnemyVec(MINO)[1]->getShadowColRc(), "normal");
	}

	if (DATABASE.LoadData("1P2P") == 1)
	{
		RECT temp3;
		if (IntersectRect(&temp3, &_em->GetEnemyVec(MINO)[0]->getShadowColRc(), &_pm->GetPlayer2()->getRc()))
		{
			_pm->GetPlayer2()->Collision(_em->GetEnemyVec(MINO)[0]->getShadowColRc(), "normal");
		}
		RECT temp4;
		if (IntersectRect(&temp4, &_em->GetEnemyVec(MINO)[1]->getShadowColRc(), &_pm->GetPlayer2()->getRc()))
		{
			_pm->GetPlayer2()->Collision(_em->GetEnemyVec(MINO)[1]->getShadowColRc(), "normal");
		}
	}

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
			_pm->ChangeAnim(34, "RightOther");
			for (int i = 0; i < 3; i++)
				_em->ShowEnemy(SKELETON, _pm->GetPlayer1()->GetX() + RND.GetFromTo(-300, 301), RND.GetFromTo(200, 350), LEFT_IDLE);
			for (int i = 0; i < 3; i++)
				_em->ShowEnemy(BLACKARCHOR, WINSIZEX, 210 + i * 70, LEFT_IDLE);
			SOUNDMANAGER.play("26Skeleton");
			SOUNDMANAGER.play("45BlackArcher");
		}
		mObjfade->Update(offset);
	}
	break;
	case FIRST_STAGE:
	{
		_pm->Update();
		_em->Update(_pm);
		CAM.Update(_pm->GetPlayer1()->GetX(), _pm->GetPlayer1()->GetY(), 5, false);

		if (_pm->GetPlayer1()->GetX() > 500 && _pm->GetPlayer1()->GetX() <1000)
		{
			if (_em->GetEnemyNum() == 0 && !changeView)
			{
				static float showTime = 0;
				showTime += TIMEMANAGER.getElapsedTime();

				if (showTime > 2)
				{
					for (int i = 0; i < 6; i++)
						_em->ShowEnemy(SKELETON, _pm->GetPlayer1()->GetX() + RND.GetFromTo(-300, 301), RND.GetFromTo(200, 350), LEFT_IDLE);
					SOUNDMANAGER.play("26Skeleton");
					int rndNum = RND.GetFromTo(-1, 2);
					if (rndNum == 0)
						rndNum = 1;
					for (int i = 0; i<3; i++)
						_em->ShowEnemy(BLACKARCHOR, _pm->GetPlayer1()->GetX() + 500 * rndNum, 210 + i * 70, LEFT_IDLE);
					SOUNDMANAGER.play("45BlackArcher");
					showTime = 0;
				}
			}
		}
		else if (1000 <= _pm->GetPlayer1()->GetX())
		{
			changeView = true;
			if (_em->GetEnemyNum() == 0)
			{
				static float showTime1 = 0;
				showTime1 += TIMEMANAGER.getElapsedTime();
				_em->GetUI()->SetDrawGo(false);
				if (showTime1 > 3.5)
				{
					s1State = SECOND_STAGE;
					CAM.SetSize(2800, WINSIZEY);
					showTime1 = 0;
					changeView = false;
				}
			}
		}
	}
	break;
	case SECOND_STAGE:
	{
		_pm->Update();
		_em->Update(_pm);

		if (_pm->GetPlayer1()->GetX() < 1600)
		{
			CAM.Update(_pm->GetPlayer1()->GetX(), _pm->GetPlayer1()->GetY(), 5, false);
		}
		else if (_pm->GetPlayer1()->GetX() > 1600 && _pm->GetPlayer1()->GetX() <2400)
		{
			CAM.Update(_pm->GetPlayer1()->GetX(), _pm->GetPlayer1()->GetY(), 5, false);
			if (_em->GetEnemyNum() == 0 && !changeView)
			{
				static float showTime = 0;
				showTime += TIMEMANAGER.getElapsedTime();

				if (showTime > 2)
				{
					for (int i = 0; i < 6; i++)
						_em->ShowEnemy(SKELETON, _pm->GetPlayer1()->GetX() + RND.GetFromTo(-300, 301), RND.GetFromTo(200, 350), LEFT_IDLE);
					SOUNDMANAGER.play("26Skeleton");
					int rndNum = RND.GetFromTo(-1, 2);
					if (rndNum == 0)
						rndNum = 1;
					for (int i = 0; i<3; i++)
						_em->ShowEnemy(BLACKARCHOR, _pm->GetPlayer1()->GetX() + 500 * rndNum, 210 + i * 70, LEFT_IDLE);
					SOUNDMANAGER.play("45BlackArcher");
					showTime = 0;
				}
			}
		}
		else if (2400 <= _pm->GetPlayer1()->GetX() && _pm->GetPlayer1()->GetX()<2800 && _em->GetEnemyNum() == 0)
		{
			CAM.Update(_pm->GetPlayer1()->GetX(), _pm->GetPlayer1()->GetY(), 5, false);
			if (_em->GetEnemyNum() == 0 && !changeView)
			{
				_em->ShowEnemy(MINO, 3400, 220, LEFT_IDLE);
				_em->ShowEnemy(MINO, 3400, 300, LEFT_IDLE);
				_em->GetUI()->SetDrawGo(false);
				changeView = true;
				SOUNDMANAGER.play("29Mino");
			}
		}
		else if (_pm->GetPlayer1()->GetX() >= 2700 && _em->GetEnemyNum() != 0 && changeView)
		{
			CAM.SetSize(GAMESIZEX, WINSIZEY);
			CAM.Update(GAMESIZEX - WINSIZEX / 2, WINSIZEY / 2, 0, false);
			isLast = true;
		}
		else if (_pm->GetPlayer1()->GetX() >= 2700 && isLast)
		{
			CAM.SetSize(GAMESIZEX, WINSIZEY);
			CAM.Update(GAMESIZEX - WINSIZEX / 2, WINSIZEY / 2, 0, false);
			if (_em->GetEnemyNum() == 0)
			{
				static float showTime1 = 0;
				showTime1 += TIMEMANAGER.getElapsedTime();

				if (showTime1 > 1.5)
				{
					s1State = WIN_STAGE;
					CAM.SetSize(GAMESIZEX, WINSIZEY);
					_pm->ChangeAnim(34, "RightOther");
					showTime1 = 0;
					changeView = false;
					_em->GetUI()->SetDrawGo(true);
				}
			}
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
			Save();
			SOUNDMANAGER.stop("14Stage2_1");
			SCENEMANAGER.changeScene("스테이지2.2");
			break;
		}
		mObjfade->Update(offset);

		break;
	}
}

void Stage2_1::Release()
{
	_pm->Release();
	SAFE_DELETE(_pm);

	mObjfade->Release();
	SAFE_DELETE(mObjfade);
}

void Stage2_1::Save()
{
	DATABASE.SaveData("1PWeapon", _pm->GetPlayer1()->GetWeaponLv());
	if (DATABASE.LoadData("1P2P") == 1)
	{
		DATABASE.SaveData("2PWeapon", _pm->GetPlayer2()->GetWeaponLv());
	}
}
