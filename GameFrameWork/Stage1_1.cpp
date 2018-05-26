#include "stdafx.h"
#include "Stage1_1.h"
#include "Bullet.h"

Stage1_1::Stage1_1()
{
	IMAGEMANAGER.addImage("1.1�չ��", PathFile("image", "1-1�չ��").c_str(), 3652, 400, true, RGB(255, 0, 255));
	IMAGEMANAGER.addImage("1.1�޹��", PathFile("image", "1-1�޹��").c_str(), 3652, 400, true, RGB(255, 0, 255));
	IMAGEMANAGER.addImage("1.1��������Ʈ", PathFile("image", "1-1��Ʈ����").c_str(), 2864, 80, true, RGB(255, 0, 255));
	EFFECTMANAGER.addEffect("����", "��������.bmp", 1653, 90, 1653 / 18, 90, 60, 1, 30);
}


Stage1_1::~Stage1_1()
{
}

HRESULT Stage1_1::Init()
{
	ZORDER.Release();
	CAM.SetPos(0, 0);

	//�ʿ�����Ʈ ��Ʈ���� �߰�
	MapObject*mObj = new MapObject(IMAGEMANAGER.findImage("1.1��������Ʈ"));
	mObj->Init(0, 320, 40);
	ZORDER.InputObj(mObj);

	mObjfade = new MapObject(IMAGEMANAGER.findImage("���̵�ƿ�"));
	mObjfade->Init(0, 0, 500, 0, true);
	ZORDER.InputObj(mObjfade);

	_pm = new PlayerManager;
	_pm->Init();
	_pm->ChangeAnim(0, "RightRun");

	_em = new EnemyManager;
	_em->InputEnemy(MINO, 1);
	_em->InputEnemy(WAREWOLF, 3);
	_em->InputEnemy(SKELETON, 3);

	//���� ����� ���γ־ �������� ó���ϸ��
	//fadeOut = IMAGEMANAGER.findImage("���̵�ƿ�");
	offset = 255;
	s1State = OPENNING;
	changeView = false;

	SOUNDMANAGER.play("07Stage1_1", 0.3f);

	return S_OK;
}


void Stage1_1::Render()
{
	IMAGEMANAGER.findImage("1.1�޹��")->Render(getMemDC(), CAM.GetX(), CAM.GetY(), CAM.GetX() * 0.01, CAM.GetY(), WINSIZEX, GAMESIZEY);
	IMAGEMANAGER.findImage("1.1�չ��")->Render(getMemDC(), CAM.GetX(), CAM.GetY(), CAM.GetX(), CAM.GetY(), WINSIZEX, GAMESIZEY);

	_pm->Render();
	//fadeOut->alphaRender(getMemDC(), CAM.GetRC().left, CAM.GetRC().top, offset);
}


void Stage1_1::Update()
{
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
				_pm->ChangeAnim(34, "RightOther");
				s1State = FIRST_STAGE;
				offset = 0;
				CAM.SetSize(GAMESIZEX / 2, WINSIZEY);
				CAM.SetState("FOLLOW");
				for (int i = 0; i<3; i++)
					_em->ShowEnemy(SKELETON, _pm->GetPlayer1()->GetX() + RND.GetFromTo(-300, 301), RND.GetFromTo(200, 350), LEFT_IDLE);
			}

			mObjfade->Update(offset);
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
					_em->GetUI()->SetDrawGo(false);
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
						for (int i = 0; i < 2; i++)
							_em->ShowEnemy(SKELETON, _pm->GetPlayer1()->GetX() + RND.GetFromTo(-600, 601), RND.GetFromTo(200, 350), LEFT_IDLE);
						for (int i = 0; i < 2; i++)
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
				if(_em->GetEnemyNum()==0)
					_em->GetUI()->SetDrawGo(false);
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
			_pm->Update();
			offset += 2;
			if (offset > 255)
			{
				Save();
				offset = 0;
				SOUNDMANAGER.stop("07Stage1_1");
				SCENEMANAGER.changeScene("��������1.2");
				break;
			}
			mObjfade->Update(offset);
		}
		break;
	}
}

void Stage1_1::Release()
{
	_pm->Release();
	SAFE_DELETE(_pm);
	_em->Release();
	SAFE_DELETE(_em);

	mObjfade->Release();
	SAFE_DELETE(mObjfade);
}

void Stage1_1::Save()
{
	DATABASE.SaveData("1PWeapon", _pm->GetPlayer1()->GetWeaponLv());
	if (DATABASE.LoadData("1P2P") == 1)
	{
		DATABASE.SaveData("2PWeapon", _pm->GetPlayer2()->GetWeaponLv());
	}
}
