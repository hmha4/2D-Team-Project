#include "stdafx.h"
#include "Stage1_1.h"
#include "Bullet.h"

Stage1_1::Stage1_1()
{
	IMAGEMANAGER.addImage("페이드아웃", PathFile("image", "검은화면").c_str(), 800, 600, false, NULL);
	IMAGEMANAGER.addImage("1.1앞배경", PathFile("image", "1-1앞배경").c_str(), 3652, 400, true, RGB(255, 0, 255));
	IMAGEMANAGER.addImage("1.1뒷배경", PathFile("image", "1-1뒷배경").c_str(), 3652, 400, true, RGB(255, 0, 255));
	IMAGEMANAGER.addImage("1.1배경오브젝트", PathFile("image", "1-1제트오더").c_str(), 2864, 80, true, RGB(255, 0, 255));
	EFFECTMANAGER.addEffect("폭발", "생물폭발.bmp", 1653, 90, 1653 / 18, 90, 60, 1, 30);
}


Stage1_1::~Stage1_1()
{
}

HRESULT Stage1_1::Init()
{
	//맵오브젝트 제트오더 추가
	MapObject*mObj = new MapObject(IMAGEMANAGER.findImage("1.1배경오브젝트"));
	mObj->Init(0, 320, 40);
	ZORDER.InputObj(mObj);

	_pm = new PlayerManager;
	_pm->Init();
	_pm->ChangeAnim(0, "RightRun");

	_em = new EnemyManager;
	_em->InputEnemy(MINO, 1);
	_em->InputEnemy(WAREWOLF, 3);
	_em->InputEnemy(SKELETON, 3);

	//정적 배경은 따로넣어서 렌더에서 처리하면됨
	fadeOut = IMAGEMANAGER.findImage("페이드아웃");
	offset = 255;
	s1State = OPENNING;
	changeView = false;

	return S_OK;
}


void Stage1_1::Render()
{
	IMAGEMANAGER.findImage("1.1뒷배경")->Render(getMemDC(), CAM.GetX(), CAM.GetY(), CAM.GetX() * 0.01, CAM.GetY(), WINSIZEX, GAMESIZEY);
	IMAGEMANAGER.findImage("1.1앞배경")->Render(getMemDC(), CAM.GetX(), CAM.GetY(), CAM.GetX(), CAM.GetY(), WINSIZEX, GAMESIZEY);
	fadeOut->alphaRender(getMemDC(), CAM.GetRC().left, CAM.GetRC().top, offset);

	_pm->Render();

}


void Stage1_1::Update()
{
	printf("%f ", _pm->GetPlayer1()->GetX());
	_pm->MoveRestrict((int)s1State);

	switch (s1State)
	{
		case OPENNING:
		{
			_pm->Update();
			CAM.Update(_pm->GetPlayer1()->GetX(), _pm->GetPlayer1()->GetY(), 5, false);

			offset -= 2;
			if (offset < 0)
			{
				s1State = FIRST_STAGE;
				offset = 0;
				CAM.SetSize(GAMESIZEX / 2, WINSIZEY);
				CAM.SetState("FOLLOW");
				for (int i = 0; i<3; i++)
					_em->ShowEnemy(SKELETON, _pm->GetPlayer1()->GetX() + RND.GetFromTo(-300, 301), RND.GetFromTo(200, 350), LEFT_IDLE);
			}

		}
		break;
		case FIRST_STAGE:
		{
			if (_pm->GetPlayer1()->GetX() > 500 && _pm->GetPlayer1()->GetX() <1500)
			{
				if (_em->GetEnemyNum() == 0&& !changeView)
				{
					static float showTime = 0;
					showTime += TIMEMANAGER.getElapsedTime();

					if (showTime > 2)
					{
						for (int i = 0; i < 3; i++)
							_em->ShowEnemy(SKELETON, _pm->GetPlayer1()->GetX() + RND.GetFromTo(-300, 301), RND.GetFromTo(200, 350), LEFT_IDLE);

						showTime = 0;
					}
				}
			}
			else if (1500 <= _pm->GetPlayer1()->GetX())
			{
				changeView = true;
				if (_em->GetEnemyNum() == 0)
				{
					static float showTime1 = 0;
					showTime1 += TIMEMANAGER.getElapsedTime();

					if (showTime1 > 3.5)
					{
						//_em->AllDieInit();
						s1State = SECOND_STAGE;
						CAM.SetSize(GAMESIZEX, WINSIZEY);
						showTime1 = 0;
						changeView = false;
					}
				}
			}
			_em->Update(_pm);
			_pm->Update();
			CAM.Update(_pm->GetPlayer1()->GetX(), _pm->GetPlayer1()->GetY(), 5, false);
		}
		break;
		case SECOND_STAGE:
		{
			if (_pm->GetPlayer1()->GetX() > 2000 && _pm->GetPlayer1()->GetX() < 3200)
			{
				if (_em->GetEnemyNum() == 0&& !changeView)
				{
					static float showTime2 = 0;
					showTime2 += TIMEMANAGER.getElapsedTime();

					if (showTime2 > 2)
					{
						for (int i = 0; i < 3; i++)
							_em->ShowEnemy(SKELETON, _pm->GetPlayer1()->GetX() + RND.GetFromTo(-600, 601), RND.GetFromTo(200, 350), LEFT_IDLE);
						for (int i = 0; i < 3; i++)
						{
							int rndNum = RND.GetFromTo(-1, 2);
							if (rndNum == 0)
								rndNum = 1;
							_em->ShowEnemy(WAREWOLF, _pm->GetPlayer1()->GetX() + 800 * rndNum, RND.GetFromTo(200, 350), LEFT_IDLE);
						}
						showTime2 = 0;
					}
				}
			}
			else if (_pm->GetPlayer1()->GetX() >= 3200&& _pm->GetPlayer1()->GetX()<3600)
			{
				changeView = true;
			}
			else if (_pm->GetPlayer1()->GetX()>=3600)
			{
				if (_em->GetEnemyNum() == 0)
				{
					s1State = NEXT_STAGE;
					changeView = false;
				}
			}
			_em->Update(_pm);
			_pm->Update();
			CAM.Update(_pm->GetPlayer1()->GetX(), _pm->GetPlayer1()->GetY(), 5, false);
		}
		break;
		case NEXT_STAGE:
		{
			offset += 2;
			if (offset > 255)
			{
				SCENEMANAGER.changeScene("스테이지1.2");
				offset = 0;
			}
		}
		break;
	}
}

void Stage1_1::Release()
{
	_pm->Release();
	_em->Release();

	ZORDER.Release();
}
