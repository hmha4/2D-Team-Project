#include "stdafx.h"
#include "PlayUI.h"


PlayUI::PlayUI()
{
	_fighterFace = IMAGEMANAGER.addImage("UI_FIGHTER_FACE", PathFile("image", "UI_FIGHTER_FACE").c_str(), 80, 60, true, RGB(255, 0, 255));
	_fighterEquip = IMAGEMANAGER.addFrameImage("UI_FIGHTER_EQUIP", PathFile("image", "UI_FIGHTER_EQUIP").c_str(), 240, 120, 5, 2, false, NULL);
	_brick = IMAGEMANAGER.addImage("UI_BACKGROUND", PathFile("image", "UI_BACKGROUND").c_str(), 1047, 100, false, NULL);
	_UItitle = IMAGEMANAGER.addImage("UI_TITLE", PathFile("image", "UI_TITLE").c_str(), 155, 90, true, RGB(255,0,255));
	_hpGauge = IMAGEMANAGER.addImage("UI_HP", PathFile("image", "UI_HP").c_str(), 180, 15, true, RGB(255, 0, 255));
	_player1.level = 1;
	_player1.score = 12480;
	_player1.job = 0;
}


PlayUI::~PlayUI()
{
}

HRESULT PlayUI::init()
{
	return S_OK;
}

void PlayUI::release()
{
}

void PlayUI::update()
{
}

void PlayUI::render()
{
	_brick->Render(getMemDC(), CAM.GetX(), CAM.GetY() + 400);
	MakeTable(getMemDC(), 20, 0, _player1);

	_UItitle->Render(getMemDC(), CAM.GetX() + 400 - (_UItitle->GetWidth() / 2), CAM.GetY() + 450 - (_UItitle->GetHeight() / 2));
}

void PlayUI::MakeTable(HDC hdc, int x, int y, tagPlayerInfo player)
{
	int left = x + CAM.GetX();
	int top =  y + CAM.GetY() + 400;

	//플레이어 그림 및 장비, 체력 출력 렉트로 구역 나눔
	RECT p1 = RectMake(left, top + 30, 290, 60);
	RECT face = RectMake(p1.left, p1.top, _fighterFace->GetWidth(), _fighterFace->GetHeight());
	RECT hp = RectMake(face.right, face.top, 30, 17);
	RECT hpGauge = RectMake(hp.right, hp.top, 290 - _fighterFace->GetWidth() - 30, 15);
	RECT equip[3];
	RECT equipTitle[3];
	
	for (int ii = 0; ii < 3; ++ii)
	{
		equip[ii]		= RectMake(face.right + ii * 70, hp.bottom, 70, 43);
		equipTitle[ii]	= RectMake(equip[ii].right - 25, hp.bottom, 25, 43);
	}

	HPEN newPen = CreatePen(BS_SOLID, 1, RGB(255, 255, 255));
	HPEN oldPen = (HPEN)SelectObject(hdc, newPen);
	SelectObject(hdc, GetStockObject(BLACK_BRUSH));

	//배경 검은 도화지 깔기
	Rectangle(hdc, face.right, p1.top, p1.right, p1.bottom);

	//플레이어 얼굴 이미지 출력
	IMAGEMANAGER.findImage("UI_FIGHTER_FACE")->Render(hdc, p1.left, p1.top);
	//플레이어 장비 이미지 출력
	for (int ii = 0; ii < 2; ++ii)
	{
		_fighterEquip->frameRender(hdc
			, equip[ii].left
			, equip[ii].bottom - _fighterEquip->GetFreamHeight()
			, _player1.level, ii);
	}

	//HP 게이지 출력
	_hpGauge->Render(hdc, hpGauge.left - 3, hpGauge.top + 2);

	//렉트 배경 투명으로 다시 변경
	SelectObject(hdc, GetStockObject(NULL_BRUSH));

	//Rectangle(hdc, p1.left, p1.top, p1.right, p1.bottom);
	//Rectangle(hdc, face.left, face.top, face.right, face.bottom);
	//Rectangle(hdc, hp.left, hp.top, hp.right, hp.bottom);
	//Rectangle(hdc, hpGauge.left, hpGauge.top, hpGauge.right, hpGauge.bottom);
	for (int ii = 0; ii < 3; ++ii)
	{
		Rectangle(hdc, equip[ii].left, equip[ii].top, equip[ii].right, equip[ii].bottom);
	}

	//Rectangle(hdc, equipTitle[0].left, equipTitle[0].top, equipTitle[0].right, equipTitle[0].bottom);
	//Rectangle(hdc, equipTitle[1].left, equipTitle[1].top, equipTitle[1].right, equipTitle[1].bottom);
	//Rectangle(hdc, equipTitle[2].left, equipTitle[2].top, equipTitle[2].right, equipTitle[2].bottom);

	//직업, HP, 점수 출력
	DrawClass(hdc, (face.left + face.right) / 2, top + 5, player);
	DrawHP(hdc, (hp.left + hp.right) / 2, hp.top + 5);
	DrawScore(hdc, (hpGauge.left + hpGauge.right) / 2 + 10, top + 5, player.score);
	
	//장비 레벨 출력
	DrawLevel(hdc, (equipTitle[0].left + equipTitle[0].right) / 2, equipTitle[0].top + 5, player.level);
	DrawLevel(hdc, (equipTitle[1].left + equipTitle[1].right) / 2, equipTitle[1].top + 5, player.level);

	Rectangle(hdc, face.right, p1.top, p1.right, p1.bottom);

	SelectObject(hdc, GetStockObject(WHITE_BRUSH));
	SelectObject(hdc, oldPen);
	DeleteObject(newPen);
}

void PlayUI::DrawClass(HDC hdc, int x, int y, tagPlayerInfo player)
{
	//직업 클래스 및 점수 출력
	HFONT font, oldFont;

	font = CreateFont(23, 0, 0, 0, 300, 0, 0, 0, DEFAULT_CHARSET,
		OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY,
		DEFAULT_PITCH | FF_SWISS, TEXT("Algerian"));

	oldFont = (HFONT)SelectObject(getMemDC(), font);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255));

	string tempClass;
	if (player.job == 0) tempClass = "FIGHTER";
	else tempClass = "MAGICIAN";

	const char* drawClass = tempClass.c_str();

	TextOut(hdc, x, y, drawClass, strlen(drawClass));
}

void PlayUI::DrawScore(HDC hdc, int x, int y, int score)
{
	//점수 출력
	HFONT font, oldFont;

	font = CreateFont(23, 0, 0, 0, 300, 0, 0, 0, DEFAULT_CHARSET,
		OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY,
		DEFAULT_PITCH | FF_SWISS, TEXT("Algerian"));

	oldFont = (HFONT)SelectObject(getMemDC(), font);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255));

	string zero;
	if (score < 10) zero = "000000";
	else if (score < 100 && score >= 10) zero = "00000";
	else if (score < 1000 && score >= 100) zero = "0000";
	else if (score < 10000 && score >= 1000) zero = "000";
	else if (score < 100000 && score >= 10000) zero = "00";
	else if (score < 1000000 && score >= 100000) zero = "0";
	string tempScore = "SCORE  : " + zero + to_string(score);
	const char* drawScore = tempScore.c_str();

	TextOut(hdc, x, y, drawScore, strlen(drawScore));
}

void PlayUI::DrawHP(HDC hdc, int x, int y)
{
	//HP 글자 출력
	HFONT font, oldFont;

	font = CreateFont(13, 0, 0, 0, 300, 0, 0, 0, DEFAULT_CHARSET,
		OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY,
		DEFAULT_PITCH | FF_SWISS, TEXT("휴먼매직체"));

	oldFont = (HFONT)SelectObject(getMemDC(), font);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255));
	SetTextAlign(hdc, TA_CENTER);

	string tempScore = "HP";
	const char* score = tempScore.c_str();

	TextOut(hdc, x, y, score, strlen(score));
}

void PlayUI::DrawLevel(HDC hdc, int x, int y, int level)
{
	//L글자 출력
	HFONT font, oldFont;

	font = CreateFont(12, 0, 0, 0, 100, 0, 0, 0, DEFAULT_CHARSET,
		OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY,
		DEFAULT_PITCH | FF_SWISS, TEXT("휴먼둥근헤드라인"));

	oldFont = (HFONT)SelectObject(getMemDC(), font);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255));
	SetTextAlign(hdc, TA_CENTER);

	string tempL = "Lv";
	const char* drawL = tempL.c_str();

	string tempLevel = to_string(level);
	const char* drawLevel = tempLevel.c_str();

	TextOut(hdc, x, y + 4, drawL, strlen(drawL));
	TextOut(hdc, x, y + 22, drawLevel, strlen(drawLevel));

}

void PlayUI::DrawItemStock(HDC hdc, int x, int y, int stock)
{
}

