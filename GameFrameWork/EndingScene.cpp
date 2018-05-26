#include "stdafx.h"
#include "EndingScene.h"


EndingScene::EndingScene()
{
	IMAGEMANAGER.addImage("EndingScene", PathFile("image\\Scene", "EndingScene").c_str(), 800, 500, false, RGB(255, 0, 255));
	IMAGEMANAGER.addFrameImage("EndingScenePlayer", PathFile("image\\Scene", "EndingScenePlayer").c_str(), 266, 207, 2, 1, true, RGB(255, 0, 255));
}


EndingScene::~EndingScene()
{
}

HRESULT EndingScene::Init()
{
	CAM.SetPos(0, 0);
	ZORDER.Release();

	_fade = IMAGEMANAGER.findImage("페이드아웃");
	_offSet = 255;

	_playerNum = DATABASE.LoadData("1P2P");
	if (_playerNum == 0)
	{
		_character[0] = (CHARACTER)DATABASE.LoadData("1PCharacter");
		if (_character[0] == WARRIOR)
			_frameX[0] = 0;
		else _frameX[0] = 1;
	}
	else if (_playerNum == 1)
	{
		_character[0] = (CHARACTER)DATABASE.LoadData("1PCharacter");
		_character[1] = (CHARACTER)DATABASE.LoadData("2PCharacter");

		if (_character[0] == WARRIOR)
			_frameX[0] = 0;
		else _frameX[0] = 1;

		if (_character[1] == WARRIOR)
			_frameX[1] = 0;
		else _frameX[1] = 1;
	}

	_state = STATE01;

	SOUNDMANAGER.play("25EndingScene", 0.3f);

	_y = WINSIZEY;
	_rc = RectMake(0, _y, WINSIZEX / 2 - 50, WINSIZEY + 200);
	_str = "감사합니다\n\n"
		   "The King Of Dragons\n\n"
		   "Team NONA\n\n"
		   "권준형\n"
		   "UI\n"
		   "Skill\n"
		   "Inventory\n\n"
		   "황도영\n"
		   "Enemy\n"
		   "Boss\n"
		   "Z-Order\n\n"
		   "강동훈\n"
		   "Player\n"
		   "Data\n"
		   "Scene\n"
		   "Camera\n"
		   "Sound\n";

	return S_OK;
}

void EndingScene::Render()
{
	IMAGEMANAGER.findImage("EndingScene")->Render(getMemDC(), CAM.GetX(), CAM.GetY());
	
	for (int i = 0; i < _playerNum + 1; i++)
	{
		if (i == 0)
			IMAGEMANAGER.findImage("EndingScenePlayer")->frameRender(getMemDC(), CAM.GetRC().right - 400, WINSIZEY / 2, _frameX[i], 0);
		else if(i == 1)
			IMAGEMANAGER.findImage("EndingScenePlayer")->frameRender(getMemDC(), CAM.GetRC().right - 300, WINSIZEY / 2 - 50, _frameX[i], 0);
	}

	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(0, 0, 0));
	SetTextAlign(getMemDC(), TA_LEFT);
	HFONT hFont = CreateFont(30, 0, 0, 0, 300, 0, 0, 0, DEFAULT_CHARSET,
		OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY,
		DEFAULT_PITCH | FF_SWISS, TEXT("휴먼매직체"));
	HFONT hOldFont = (HFONT)SelectObject(getMemDC(), hFont);
	DrawText(getMemDC(), _str.c_str(), -1, &_rc, DT_CENTER);
	SelectObject(getMemDC(), hOldFont);
	DeleteObject(hFont);

	_fade->alphaRender(getMemDC(), CAM.GetX(), CAM.GetY(), _offSet);
}

void EndingScene::Update()
{
	switch (_state)
	{
	case EndingScene::STATE01:
		_offSet -= 3;

		if (_offSet < 0)
			_offSet = 0;

		_y -= 1.5f;
		if (KEYMANAGER.isOnceKeyDown(VK_RETURN))
			_state = STATE02;
		if (_rc.bottom <= 0)
			_state = STATE02;
		break;
	case EndingScene::STATE02:
		_offSet += 3;

		if (_offSet > 255)
		{
			_offSet = 255;
			SOUNDMANAGER.stop("25EndingScene");
			SCENEMANAGER.changeScene("StartScene");
		}
		break;
	}
	_rc = RectMake(0, _y, WINSIZEX / 2 - 50, WINSIZEY + 200);
}

void EndingScene::Release()
{
}
