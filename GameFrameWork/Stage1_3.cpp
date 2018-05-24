#include "stdafx.h"
#include "Stage1_3.h"


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

	s3State = OPENNING;

	_pm = new PlayerManager;
	_pm->Init();
	_pm->SetPlayerPos(WINSIZEX / 2, -50);
	_pm->ChangeAnim(10, "RightFall");

	fadeOut = IMAGEMANAGER.findImage("페이드아웃");
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

	fadeOut->alphaRender(getMemDC(), CAM.GetX(), CAM.GetY(), offset);
}

void Stage1_3::Update()
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
			offset = 0;
			s3State = FIRST_STAGE;
		}
	}
	break;
	case FIRST_STAGE:
	{
		_pm->Update();
		CAM.Update(WINSIZEX / 2, WINSIZEY / 2, 5, false);

		if (KEYMANAGER.isOnceKeyDown(VK_SPACE))
		{
			s3State = WIN_STAGE;
			_pm->ChangeAnim(34, "RightOther");
			SOUNDMANAGER.play("10Victory");
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
			SOUNDMANAGER.stop("09Stage1_Boss");
		}
		_pm->Update();
		CAM.Update(WINSIZEX / 2, WINSIZEY / 2, 5, false);

		break;
	}
}

void Stage1_3::Release()
{
	_pm->Release();
	SAFE_DELETE(_pm);
}
