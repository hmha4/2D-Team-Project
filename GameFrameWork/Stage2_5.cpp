#include "stdafx.h"
#include "Stage2_5.h"


Stage2_5::Stage2_5()
{
	IMAGEMANAGER.addFrameImage("µå·¡°ï¸öÅë", PathFile("image\\Enemy", "µå·¡°ï¸öÅë").c_str(), 5600, 282, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER.addFrameImage("¿ëÁ×À½", PathFile("image\\Enemy", "¿ëÁ×À½").c_str(), 700, 266, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER.addImage("2.5¾Õ¹è°æ", PathFile("image", "2-5¾Õ¹è°æ").c_str(), 800, 400, true, RGB(255, 0, 255));
}


Stage2_5::~Stage2_5()
{
}

HRESULT Stage2_5::Init()
{
	int dBodyIdle[] = { 0,2,3,4,5,6,7 };
	ANIMATIONKEY.addArrayFrameAnimation("drIdle", "µå·¡°ï¸öÅë", dBodyIdle, 7, 7, true);

	img = IMAGEMANAGER.findImage("µå·¡°ï¸öÅë");
	anim = new animation;
	anim = ANIMATIONKEY.findAnimation("drIdle");
	anim->start();

	ZORDER.Release();
	CAM.SetPos(0, 0);

	mObjfade = new MapObject(IMAGEMANAGER.findImage("ÆäÀÌµå¾Æ¿ô"));
	mObjfade->Init(0, 0, 500, 7, true);
	ZORDER.InputObj(mObjfade);

	_pm = new PlayerManager;
	_pm->Init();
	_pm->ChangeAnim(0, "RightRun");
	_pm->SetPlayerPos(-50, WINSIZEY / 2 - 50);

	_em = new EnemyManager("Red Dragon");
	_em->InputEnemy(DRAGON, 1);
	
	//fadeOut = IMAGEMANAGER.findImage("ÆäÀÌµå¾Æ¿ô");
	offset = 255;
	s5State = OPENNING;

	SOUNDMANAGER.play("18Stage2_5", 0.3f);

	return S_OK;
}

void Stage2_5::Render()
{
	IMAGEMANAGER.findImage("2.5¾Õ¹è°æ")->Render(getMemDC(), CAM.GetX(), CAM.GetY(), CAM.GetX(), CAM.GetY(), WINSIZEX, GAMESIZEY);
	if (s5State != WIN_STAGE)
		img->aniRender(getMemDC(), WINSIZEX / 2 - 400, WINSIZEY / 2 - 250, anim);
	else if(s5State == WIN_STAGE|| s5State == NEXT_STAGE)
		img->Render(getMemDC(), WINSIZEX / 2 - 400, WINSIZEY / 2 - 250);
	_pm->Render();
	
	//fadeOut->alphaRender(getMemDC(), CAM.GetX(), CAM.GetY(), offset);
}

void Stage2_5::Update()
{
	RECT temp;
	if (IntersectRect(&temp, &_em->GetEnemyVec(DRAGON)[0]->getDragonFootRc(), &_pm->GetPlayer1()->getRc()))
	{
		_pm->GetPlayer1()->Collision(_em->GetEnemyVec(DRAGON)[0]->getDragonFootRc(), "normal");
	}

	_pm->MoveRestrict((int)s5State);

	switch (s5State)
	{
	case OPENNING:
	{
		_pm->Update();
		CAM.Update(WINSIZEX / 2, WINSIZEY / 2, 5, false);

		static bool isOnce = false;

		if (!isOnce)
		{
			_em->ShowEnemy(DRAGON, WINSIZEX / 2-100, WINSIZEY / 2-120, LEFT_IDLE);
			SOUNDMANAGER.play("51Dragon");
			isOnce = true;
		}

		offset -= 2;
		if (offset < 0)
		{
			SOUNDMANAGER.play("52DragonBreath");
			s5State = FIRST_STAGE;
			offset = 0;
			CAM.SetSize(WINSIZEX, WINSIZEY);
			CAM.SetState("FOLLOW");
			_pm->ChangeAnim(34, "RightOther");
		}
		mObjfade->Update(offset);
	}
	break;
	case FIRST_STAGE:
	{
		_em->Update(_pm);
		_pm->Update();
		CAM.Update(WINSIZEX / 2, WINSIZEY / 2, 5, false);

		if (_em->GetEnemyNum() == 0)
		{
			offset += 2;
			mObjfade->Update(offset);

			if (offset > 255)
			{
				offset = 255;
				s5State = WIN_STAGE;
				img = IMAGEMANAGER.findImage("¿ëÁ×À½");
			}
		}
	}
	break;
	case WIN_STAGE:
	{
		offset -= 2;
		if (offset < 0)
			offset = 0;
		
		_pm->Update();
		CAM.Update(WINSIZEX / 2, WINSIZEY / 2, 5, false);

		static float nextTime = 0;
		nextTime += TIMEMANAGER.getElapsedTime();

		if (nextTime > 4)
		{
			SOUNDMANAGER.stop("18Stage2_5");
			SOUNDMANAGER.play("10Victory", 0.3f);
			_pm->ChangeAnim(34, "RightOther");
			s5State = NEXT_STAGE;
			nextTime = 0;
		}
	}
	break;
	case NEXT_STAGE:
		CAM.Update(WINSIZEX / 2, WINSIZEY / 2, 5, false);
		offset += 1;
		if (offset > 255)
		{
			offset = 255;
			SCENEMANAGER.changeScene("EndingScene");
			break;
		}
		mObjfade->Update(offset);

		break;
	}
}

void Stage2_5::Release()
{
	_pm->Release();
	SAFE_DELETE(_pm);

	mObjfade->Release();
	SAFE_DELETE(mObjfade);
}
