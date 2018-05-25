#include "stdafx.h"
#include "StartScene.h"


StartScene::StartScene()
{
}


StartScene::~StartScene()
{
}

HRESULT StartScene::Init()
{
	CAM.SetPos(0, 0);
	ZORDER.Release();

	IMAGEMANAGER.addFrameImage("StartScene_01", PathFile("image\\Scene", "StartScene_01").c_str(), 800, 500, 1, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER.addFrameImage("StartScene_02", PathFile("image\\Scene", "StartScene_02").c_str(), 8800, 500, 11, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER.addFrameImage("StartScene_03", PathFile("image\\Scene", "StartScene_03").c_str(), 16800, 500, 21, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER.addFrameImage("StartScene_04", PathFile("image\\Scene", "StartScene_04").c_str(), 4800, 500, 6, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER.addFrameImage("StartScene_05", PathFile("image\\Scene", "StartScene_05").c_str(), 800, 500, 1, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER.addFrameImage("StartScene_05_Button", PathFile("image\\Scene", "StartScene_05_Button").c_str(), 276, 38, 1, 2, false, RGB(255, 0, 255));

	ANIMATIONKEY.addDefaultFrameAnimation("StartScene_01", "StartScene_01", 1, false, false);
	ANIMATIONKEY.addDefaultFrameAnimation("StartScene_02", "StartScene_02", 5, false, false);
	ANIMATIONKEY.addDefaultFrameAnimation("StartScene_03", "StartScene_03", 5, false, false);
	ANIMATIONKEY.addDefaultFrameAnimation("StartScene_04", "StartScene_04", 5, false, true);
	ANIMATIONKEY.addDefaultFrameAnimation("StartScene_05", "StartScene_05", 1, false, true);

	_state = STATE_01;
	_img = IMAGEMANAGER.findImage("StartScene_01");
	_anim = ANIMATIONKEY.findAnimation("StartScene_01");
	_anim->start();

	for (int i = 0; i < 2; i++)
		_button[i] = tagButton(WINSIZEX / 2 + 50, 170 + WINSIZEY / 2 + (i*30), i);
	
	_buttonIndex = 0;

	SOUNDMANAGER.play("00StartScene01", 1.0f);

	_fade = IMAGEMANAGER.findImage("ÆäÀÌµå¾Æ¿ô");
	_offSet = 0;
	_changeScene = false;

	return S_OK;
}

void StartScene::Render()
{
	_img->aniRender(getMemDC(), CAM.GetX(), CAM.GetY(), _anim);

	if (_state == STATE_05)
	{
		for (int i = 0; i < 2; i++)
			_button[i].img->alphaFrameRender(getMemDC(), _button[i].rc.left, _button[i].rc.top,
				0, _button[i].frameY, _button[i].alpha);
	}

	_fade->alphaRender(getMemDC(), CAM.GetRC().left, CAM.GetRC().top, _offSet);
}

void StartScene::Update()
{
	switch (_state)
	{
	case StartScene::STATE_01:
		if (KEYMANAGER.isOnceKeyDown(VK_RETURN))
			ChangeAnim(STATE_02, "StartScene_02");
		if (!_anim->isPlay())
			ChangeAnim(STATE_02, "StartScene_02");
		break;
	case StartScene::STATE_02:
		if (KEYMANAGER.isOnceKeyDown(VK_RETURN))
		{
			SOUNDMANAGER.stop("00StartScene01");
			SOUNDMANAGER.play("01StartScene02", 0.3f);
			ChangeAnim(STATE_03, "StartScene_03");
		}
		if (!_anim->isPlay())
		{
			SOUNDMANAGER.play("01StartScene02", 0.3f);
			ChangeAnim(STATE_03, "StartScene_03");
		}
		break;
	case StartScene::STATE_03:
		if (KEYMANAGER.isOnceKeyDown(VK_RETURN))
			ChangeAnim(STATE_04, "StartScene_04");
		if (!_anim->isPlay())
			ChangeAnim(STATE_04, "StartScene_04");
		break;
	case StartScene::STATE_04:
		if (KEYMANAGER.isOnceKeyDown(VK_RETURN))
		{
			SOUNDMANAGER.stop("01StartScene02");
			SOUNDMANAGER.play("02StartScene03", 1.0f);
			SOUNDMANAGER.play("05StartScene04", 0.3f);
			ChangeAnim(STATE_05, "StartScene_05");
		}
		break;
	case StartScene::STATE_05:
		if (KEYMANAGER.isOnceKeyDown(VK_DOWN))
		{
			SOUNDMANAGER.play("03StartScene_Button", 1.0f);
			_button[_buttonIndex].alpha = 255;
			_buttonIndex++;
			if (_buttonIndex > 1) _buttonIndex = 0;
		}
		else if (KEYMANAGER.isOnceKeyDown(VK_UP))
		{
			SOUNDMANAGER.play("03StartScene_Button", 1.0f);
			_button[_buttonIndex].alpha = 255;
			_buttonIndex--;
			if (_buttonIndex < 0) _buttonIndex = 1;
		}

		if (KEYMANAGER.isOnceKeyDown(VK_RETURN))
		{
			SOUNDMANAGER.play("04ButtonSelect", 1.0f);
			_changeScene = true;
			
		}

		_buttonCount += TIMEMANAGER.getElapsedTime();
		if (_buttonCount >= 0.02)
		{
			_buttonCount = 0;
			if(_button[_buttonIndex].alpha == 255)
				_button[_buttonIndex].alpha = 0;
			else _button[_buttonIndex].alpha = 255;
		}

		if (_changeScene)
		{
			_offSet += 4;
			if (_offSet > 255)
			{
				_offSet = 255;
				DATABASE.SaveData("1P2P", _buttonIndex);
				SCENEMANAGER.changeScene("SelectScene");
				SOUNDMANAGER.stop("05StartScene04");
			}
		}

		break;
	}
	CAM.Update(WINSIZEX / 2, WINSIZEY / 2, 0, false);
}

void StartScene::Release()
{
}

void StartScene::ChangeAnim(STATE state, string name)
{
	_state = state;
	_img = IMAGEMANAGER.findImage(name);
	_anim = ANIMATIONKEY.findAnimation(name);
	_anim->start();
}
