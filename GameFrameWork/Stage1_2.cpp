#include "stdafx.h"
#include "Stage1_2.h"


Stage1_2::Stage1_2()
{
	IMAGEMANAGER.addImage("ÆäÀÌµå¾Æ¿ô", PathFile("image", "°ËÀºÈ­¸é").c_str(), 800, 600, false, NULL);
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
	MapObject*mObj = new MapObject(IMAGEMANAGER.findImage("1.2¹è°æ¿ÀºêÁ§Æ®"));
	mObj->Init(1357, 0, 200);
	ZORDER.InputObj(mObj);

	_pm = new PlayerManager;
	_pm->Init();

	fadeOut = IMAGEMANAGER.findImage("ÆäÀÌµå¾Æ¿ô");
	offset = 255;
	s2State = OPENNING;
	_time = 0;
	_totalTime = 0;
	_playerNum = DATABASE.LoadData("1P2P");

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

	fadeOut->alphaRender(getMemDC(), CAM.GetX(), CAM.GetY(), offset);

	_pm->Render();
}

void Stage1_2::Update()
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
			CAM.SetSize(1400, WINSIZEY);
			CAM.SetState("FOLLOW");
			_pm->GetPlayer1()->ChangeAnim(0, "WarriorRightIdle");
		}
	}
	break;
	case FIRST_STAGE:
	{
		_pm->Update();
		CAM.Update(_pm->GetPlayer1()->GetX(), _pm->GetPlayer1()->GetY(), 5, false);

		if (KEYMANAGER.isOnceKeyDown(VK_SPACE))
		{
			s2State = SECOND_STAGE;
			CAM.SetSize(3048, WINSIZEY);
		}
	}
	break;
	case SECOND_STAGE:
	{
		_pm->Update();
		CAM.Update(_pm->GetPlayer1()->GetX(), _pm->GetPlayer1()->GetY(), 5, false);

		if (KEYMANAGER.isOnceKeyDown(VK_SPACE))
		{
			s2State = FINAL_STAGE;
		}
	}
	break;
	case FINAL_STAGE:
		_pm->Update();
		CAM.Update(3048 - WINSIZEX / 2, WINSIZEY / 2, 5, false);

		if (KEYMANAGER.isOnceKeyDown(VK_SPACE))
		{
			s2State = WIN_STAGE;
			if (_pm->GetPlayer1()->GetState() == 0)
				_pm->GetPlayer1()->ChangeAnim(34, "WarriorRightOther");
			else
				_pm->GetPlayer1()->ChangeAnim(35, "WarriorLeftOther");
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
			if (_pm->GetPlayer1()->GetState() == 0)
				_pm->GetPlayer1()->ChangeAnim(10, "WarriorRightFall");
			else
				_pm->GetPlayer1()->ChangeAnim(11, "WarriorLeftFall");
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
				offset = 255;
			}
		}
		_pm->Update();
		CAM.Update(3048 - WINSIZEX / 2, WINSIZEY / 2, 5, false);

		break;
	}
}

void Stage1_2::Release()
{
	_pm->Release();

	ZORDER.Release();
}
