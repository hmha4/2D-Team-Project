#include "stdafx.h"
#include "Stage1_2.h"
#include "Bullet.h"

Stage1_2::Stage1_2()
{
	IMAGEMANAGER.addImage("1.2¾Õ¹è°æ", PathFile("image", "1-2¾Õ¹è°æ").c_str(), 3048, 500, true, RGB(255, 0, 255));
	IMAGEMANAGER.addImage("1.2µÞ¹è°æ", PathFile("image", "1-2µÞ¹è°æ").c_str(), 1250, 264, true, RGB(255, 0, 255));
	IMAGEMANAGER.addImage("1.2¹è°æ¿ÀºêÁ§Æ®", PathFile("image", "1-2Á¦Æ®¿À´õ").c_str(), 143, 400, true, RGB(255, 0, 255));
	IMAGEMANAGER.addImage("1.2¶¥", PathFile("image", "1-2¶¥").c_str(), 762, 208, true, RGB(255, 0, 255));
	IMAGEMANAGER.addImage("1.2¶¥ºÎ¼­Áü", PathFile("image", "1-2¶¥ºÎ¼­Áü").c_str(), 762, 208, true, RGB(255, 0, 255));
	EFFECTMANAGER.addEffect("1.2¶¥ÀÌÆåÆ®", PathFile("image", "1-2¶¥ÀÌÆåÆ®").c_str(), 376, 92, 94, 92, 60, 0.5, 30);
}


Stage1_2::~Stage1_2()
{
}

HRESULT Stage1_2::Init()
{
	ZORDER.Release();

	MapObject*mObj = new MapObject(IMAGEMANAGER.findImage("1.2¹è°æ¿ÀºêÁ§Æ®"));
	mObj->Init(1357, 0, 200);
	ZORDER.InputObj(mObj);

	mObjfade = new MapObject(IMAGEMANAGER.findImage("ÆäÀÌµå¾Æ¿ô"));
	mObjfade->Init(0, 0, 500, 1, true);
	ZORDER.InputObj(mObjfade);

	_pm = new PlayerManager;
	_pm->Init();
	_pm->ChangeAnim(0, "RightRun");

	_em = new EnemyManager;
	_em->Init();
	_em->InputEnemy(MINO, 2);
	_em->InputEnemy(WAREWOLF, 4);
	_em->InputEnemy(SKELETON, 4);

	//fadeOut = IMAGEMANAGER.findImage("ÆäÀÌµå¾Æ¿ô");
	offset = 255;
	s2State = OPENNING;
	_time = 0;
	_totalTime = 0;
	changeView = false;

	SOUNDMANAGER.play("08Stage1_2", 0.3f);

	return S_OK;
}

void Stage1_2::Render()
{
	IMAGEMANAGER.findImage("1.2µÞ¹è°æ")->Render(getMemDC(), CAM.GetX(), CAM.GetY(), CAM.GetX() * 0.1, CAM.GetY(), WINSIZEX, 264);
	IMAGEMANAGER.findImage("1.2¾Õ¹è°æ")->Render(getMemDC(), CAM.GetX(), CAM.GetY(), CAM.GetX(), CAM.GetY() + 100, WINSIZEX, GAMESIZEY);

	if (s2State != WIN_STAGE && s2State != NEXT_STAGE)
		IMAGEMANAGER.findImage("1.2¶¥")->Render(getMemDC(), 3048 - 762, CAM.GetRC().bottom - 308);
	if (s2State == WIN_STAGE)
		IMAGEMANAGER.findImage("1.2¶¥ºÎ¼­Áü")->Render(getMemDC(), 3048 - 762, CAM.GetRC().bottom - 308);

	_pm->Render();

	//fadeOut->alphaRender(getMemDC(), CAM.GetX(), CAM.GetY(), offset);
}

void Stage1_2::Update()
{
	_pm->MoveRestrict((int)s2State);

	RECT temp;
	if (IntersectRect(&temp, &_em->GetEnemyVec(MINO)[0]->getShadowColRc(), &_pm->GetPlayer1()->getRc()))
	{
		_pm->GetPlayer1()->Collision(_em->GetEnemyVec(MINO)[0]->getShadowColRc());
	}

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
			CAM.SetSize(1400, WINSIZEY);
			CAM.SetState("FOLLOW");
			_pm->ChangeAnim(0, "RightIdle");
			for (int i = 0; i < 3; i++)
				_em->ShowEnemy(SKELETON, _pm->GetPlayer1()->GetX() + RND.GetFromTo(-300, 301), RND.GetFromTo(200, 350), LEFT_IDLE);
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
					for (int i = 0; i < 4; i++)
						_em->ShowEnemy(SKELETON, _pm->GetPlayer1()->GetX() + RND.GetFromTo(-300, 301), RND.GetFromTo(200, 350), LEFT_IDLE);

					for (int i = 0; i < 2; i++)
					{
						int rndNum = RND.GetFromTo(-1, 2);
						if (rndNum == 0)
							rndNum = 1;
						_em->ShowEnemy(WAREWOLF, _pm->GetPlayer1()->GetX() + 800 * rndNum, RND.GetFromTo(200, 350), LEFT_IDLE);
					}

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

				if (showTime1 > 3.5)
				{
					s2State = SECOND_STAGE;
					CAM.SetSize(3048, WINSIZEY);
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
		CAM.Update(_pm->GetPlayer1()->GetX(), _pm->GetPlayer1()->GetY(), 5, false);

		if (_pm->GetPlayer1()->GetX() > 1800)
		{
			if (_em->GetEnemyNum() == 0 && !changeView)
			{
				for (int i = 0; i < 4; i++)
					_em->ShowEnemy(SKELETON, _pm->GetPlayer1()->GetX() + RND.GetFromTo(-600, 601), RND.GetFromTo(200, 350), LEFT_IDLE);
				changeView = true;
			}
		}
		if (_pm->GetPlayer1()->GetX() > 2300&& _em->GetEnemyNum() == 0)
		{
			s2State = FINAL_STAGE;
			changeView = false;
			_em->ShowEnemy(MINO, 2800,230, LEFT_IDLE);
		}
		
	}
	break;
	case FINAL_STAGE:
		_pm->Update();
		_em->Update(_pm);
		CAM.Update(3048 - WINSIZEX / 2, WINSIZEY / 2, 5, false);

		if (_em->GetEnemyNum()==0)
		{
			s2State = WIN_STAGE;
			_pm->ChangeAnim(34, "RightOther");
			_pm->ChangeWeapon(2);
		}

		break;
	case WIN_STAGE:
		_pm->Update();
		CAM.Update(3048 - WINSIZEX / 2, WINSIZEY / 2, 5, false);

		_totalTime += TIMEMANAGER.getElapsedTime();
		if (_totalTime >= 2.0f)
		{
			_totalTime = 0;
			s2State = NEXT_STAGE;
			
			_pm->ChangeAnim(10, "RightFall");

			break;
		}

		EFFECTMANAGER.play("1.2¶¥ÀÌÆåÆ®", RND.GetFromTo(CAM.GetX() + 100, CAM.GetRC().right), RND.GetFromTo(WINSIZEY / 2, WINSIZEY));

		break;
	case NEXT_STAGE:
		if (_pm->GetPlayer1()->GetY() > WINSIZEY)
		{
			offset += 2;
			if (offset > 255)
			{
				SOUNDMANAGER.stop("08Stage1_2");
				offset = 255;
				Save();
				SCENEMANAGER.changeScene("½ºÅ×ÀÌÁö1.3");
				break;
			}
			mObjfade->Update(offset);
		}
		_pm->Update();
		CAM.Update(3048 - WINSIZEX / 2, WINSIZEY / 2, 5, false);

		break;
	}
}

void Stage1_2::Release()
{
	_pm->Release();
	SAFE_DELETE(_pm);

	mObjfade->Release();
	SAFE_DELETE(mObjfade);
}

void Stage1_2::Save()
{
	DATABASE.SaveData("1PWeapon", _pm->GetPlayer1()->GetWeaponLv());
	if (DATABASE.LoadData("1P2P") == 1)
	{
		DATABASE.SaveData("2PWeapon", _pm->GetPlayer2()->GetWeaponLv());
	}
}
