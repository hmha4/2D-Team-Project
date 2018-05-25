#include "stdafx.h"
#include "PlayUI.h"
#include "ItemBox.h"
#include "SkillThunder.h"
#include "SkillWarrior.h"
#include "SkillIce.h"
#include "SkillFire.h"

PlayUI::PlayUI()
	:_insertCoinCount(0)
{
	_fighterFace = IMAGEMANAGER.addImage("UI_FIGHTER_FACE", PathFile("image\\UI", "UI_FIGHTER_FACE").c_str(), 80, 60, true, RGB(255, 0, 255));
	_fighterEquip = IMAGEMANAGER.addFrameImage("UI_FIGHTER_EQUIP", PathFile("image\\UI", "UI_FIGHTER_EQUIP").c_str(), 240, 120, 5, 2, false, NULL);
	_wizardFace = IMAGEMANAGER.addImage("UI_WIZARD_FACE", PathFile("image\\UI", "UI_WIZARD_FACE").c_str(), 80, 60, true, RGB(255, 0, 255));
	_wizardEquip = IMAGEMANAGER.addFrameImage("UI_WIZARD_EQUIP", PathFile("image\\UI", "UI_WIZARD_EQUIP").c_str(), 240, 120, 5, 2, false, NULL);
	_brick = IMAGEMANAGER.addImage("UI_BACKGROUND", PathFile("image\\UI", "UI_BACKGROUND").c_str(), 1047, 100, false, NULL);
	_UItitle = IMAGEMANAGER.addImage("UI_TITLE", PathFile("image\\UI", "UI_TITLE").c_str(), 155, 90, true, RGB(255,0,255));
	_hpGauge = IMAGEMANAGER.addImage("UI_HP", PathFile("image\\UI", "UI_HP").c_str(), 180, 15, true, RGB(255, 0, 255));
	_skillGauge = IMAGEMANAGER.addImage("UI_SKILLGAUGE", PathFile("image\\UI", "UI_SKILLGAUGE").c_str(), 25, 43, true, RGB(255, 0, 255));
}


PlayUI::~PlayUI()
{
}

HRESULT PlayUI::Init(int playerNum)
{
	_playerNum = playerNum;

	if (_playerNum == 0)
	{
		_itemBox[0] = new ItemBox;
		_skill[0] = tagSkill(MAX_ICE, MAX_FIRE, MAX_THUNDER);
	}
	else
	{
		_itemBox[0] = new ItemBox;
		_itemBox[1] = new ItemBox;
		_skill[0] = tagSkill(MAX_ICE, MAX_FIRE, MAX_THUNDER);
		_skill[1] = tagSkill(MAX_ICE, MAX_FIRE, MAX_THUNDER);
	}

	//스킬 이펙트 클래스 상속
	_warrior = new SkillWarrior;
	ZORDER.InputObj(_warrior);

	_ice = new SkillIce;
	ZORDER.InputObj(_ice);

	for (int ii = 0; ii < 8; ++ii)
	{
		_fire[ii] = new SkillFire;
		ZORDER.InputObj(_fire[ii]);
	}

	//색상 정보
	_red = RGB(255, 0, 0);
	_orange = RGB(255, 100, 0);
	_yellow = RGB(255, 255, 0);
	_green = RGB(0, 255, 0);
	_rnd = RGB(0, 0, 0);

	return S_OK;
}

void PlayUI::Release()
{
	_warrior->Release();
	SAFE_DELETE(_warrior);
	SAFE_DELETE(_ice);
	for (int ii = 0; ii < 8; ++ii)
	{
		SAFE_DELETE(_fire[ii]);
	}
}

void PlayUI::Update()
{
	if (KEYMANAGER.isOnceKeyDown('E'))	MakeSkillThunder();
	if (KEYMANAGER.isOnceKeyDown('R'))	MakeSkillFire();
	if (KEYMANAGER.isOnceKeyDown('T'))	MakeSkillIce();

	if (KEYMANAGER.isStayKeyDown('Q'))	ActiveSkillBox(0);
	if (KEYMANAGER.isOnceKeyDown('Q'))  ChangeSkillBox(0);
	if (KEYMANAGER.isOnceKeyUp('Q'))	_skill[0].enterKeyTime = 0;
	if (KEYMANAGER.isOnceKeyDown('W'))	SelectSkillBox(0);

	//UI Z-ORDER를 위한 렉트 업데이트
	_zRC = RectMake(CAM.GetX(), CAM.GetY() + 600, 800, 100);

	//스킬 클래스 업데이트
	_warrior->Update();
	_ice->Update();
	for (int ii = 0; ii < 8; ++ii)
	{
		_fire[ii]->Update();
	}
	ChargeSkillGauge(_playerNum);
}

void PlayUI::Render()
{
	_brick->Render(getMemDC(), CAM.GetX(), CAM.GetY() + 400);
	if (_playerNum == 0)
	{
		MakeTable(getMemDC(), 20, 0, _player1, 0);
		DrawInserCoin(getMemDC());
	}
	else
	{
		MakeTable(getMemDC(), 20, 0, _player1, 0);
		MakeTable(getMemDC(), 420 + _UItitle->GetWidth() / 2, 0, _player2, 1);
	}

	_UItitle->Render(getMemDC(), CAM.GetX() + 400 - (_UItitle->GetWidth() / 2), CAM.GetY() + 450 - (_UItitle->GetHeight() / 2));
}

void PlayUI::MakeTable(HDC hdc, int x, int y, tagPlayerInfo player, int playerNum)
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
	if (player.job == 1)
	{
		_wizardFace->Render(hdc, p1.left, p1.top);
		for (int ii = 0; ii < 2; ++ii)
		{
			_wizardEquip->frameRender(hdc
				, equip[ii].left
				, equip[ii].bottom - _wizardEquip->GetFreamHeight()
				, _player1.level - 1, ii);
		}
	}
	else 
	{ 
		_fighterFace->Render(hdc, p1.left, p1.top);
		for (int ii = 0; ii < 2; ++ii)
		{
			_fighterEquip->frameRender(hdc
				, equip[ii].left
				, equip[ii].bottom - _fighterEquip->GetFreamHeight()
				, _player1.level - 1, ii);
		}
	}
	//플레이어 장비 이미지 출력

	//선택된 스킬 출력
	_itemBox[playerNum]->DrawSelectItem(hdc, (equip[2].left + equipTitle[2].left) / 2, (equip[2].top + equip[2].bottom) / 2, _skill[playerNum].selectSkill);

	//HP 게이지 출력
	DrawHPgauge(hdc, hpGauge.left - 3, hpGauge.top + 2, player.hp);
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

	//스킬 게이지 출력
	DrawSkillGauge(hdc, equipTitle[2], playerNum, _skill[playerNum].selectSkill);

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
	if (player.job == 1) tempClass = "MAGICIAN";
	else tempClass = "FIGHTER";

	const char* drawClass = tempClass.c_str();

	TextOut(hdc, x, y, drawClass, strlen(drawClass));

	SelectObject(hdc, oldFont);
	DeleteObject(font);
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

	SelectObject(hdc, oldFont);
	DeleteObject(font);
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

	SelectObject(hdc, oldFont);
	DeleteObject(font);
}

void PlayUI::DrawHPgauge(HDC hdc, int x, int y, int hp)
{
	RECT hpRC;
	RECT blackRC;
	HBRUSH brush, oldBrush;

	int red = (10 - hp) * 25;
	int green = hp * 25;

	hpRC = RectMake(x, y, 180, 15);
	blackRC = RectMake(x + 180 - (10 - hp) * 18, y, (10 - hp) * 18, 15);

	brush = CreateSolidBrush(RGB(red, green, 0));
	oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);

	Rectangle(getMemDC(), hpRC.left, hpRC.top, hpRC.right, hpRC.bottom);

	SelectObject(getMemDC(), oldBrush);
	DeleteObject(brush);

	SelectObject(hdc, GetStockObject(BLACK_BRUSH));
	Rectangle(getMemDC(), blackRC.left, blackRC.top, blackRC.right, blackRC.bottom);
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

	SelectObject(hdc, oldFont);
	DeleteObject(font);
}

void PlayUI::DrawSkillGauge(HDC hdc, RECT rc, int player, int selectSkill)
{
	HBRUSH brush, oldBrush;

	int height;
	
	for (int ii = 0; ii < 3; ++ii)
	{
		if (ii != selectSkill) continue;
		height = (_skill[player].currentGauge[ii] / _skill[player].maxGauge[ii]) * (rc.bottom - rc.top);
	}

	COLORREF color;
	if (height < (rc.bottom - rc.top) / 4) color = _red;
	else if (height < (rc.bottom - rc.top) / 2 && height > (rc.bottom - rc.top) / 4) color = _orange;
	else if (height < (rc.bottom - rc.top) / 4 * 3 && height > (rc.bottom - rc.top) / 2) color = _yellow;
	else if (height < (rc.bottom - rc.top) / 1 && height > (rc.bottom - rc.top) / 4 * 3) color = _green;
	else if (height >= (rc.bottom - rc.top))	color = RGB(RND.GetInt(255), RND.GetInt(255), RND.GetInt(255));

	brush = CreateSolidBrush(color);
	oldBrush = (HBRUSH)SelectObject(hdc, brush);

	Rectangle(hdc, rc.left, rc.bottom - height, rc.right, rc.bottom);

	SelectObject(hdc, oldBrush);
	DeleteObject(brush);

	_skillGauge->Render(hdc, rc.left, rc.top);

	//char status[128];
	//sprintf_s(status, "count_ice : %f, count_fire : %f, count_thunder : %f"
	//	, _skill[0].currentGauge[0], _skill[0].currentGauge[1], _skill[0].currentGauge[2]);
	//TextOut(hdc, CAM.GetX() + 200, CAM.GetY() + 100, status, strlen(status));
}

void PlayUI::DrawInserCoin(HDC hdc)
{
	_insertCoinCount++;

	if (_insertCoinCount > 30)
	{
		_insertCoinCount = 0;
		_insertCoinHide++;
	}

	if (_insertCoinHide > 1) _insertCoinHide = 0;

	int left = CAM.GetX() + 635;
	int top = CAM.GetY() + 430;

	//코인 문구 입력
	HFONT font, oldFont;

	font = CreateFont(33, 0, 0, 0, 500, 0, 0, 0, DEFAULT_CHARSET,
		OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY,
		DEFAULT_PITCH | FF_SWISS, TEXT("Algerian"));

	oldFont = (HFONT)SelectObject(getMemDC(), font);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255));

	string coin = "Please Insert Coin";
	const char* drawCoin = coin.c_str();

	if (_insertCoinHide == 0)	TextOut(hdc, left, top, drawCoin, strlen(drawCoin));

	SelectObject(hdc, oldFont);
	DeleteObject(font);
}

void PlayUI::SetLvHp(int playerNum, int hp, int lv)
{
	if (playerNum == 0)
	{
		_player1.hp = hp;
		_player1.level = lv;
	}
	else
	{
		_player2.hp = hp;
		_player2.level = lv;
	}
}

void PlayUI::MakeSkillThunder()
{
	_warrior->StartSkill();
	SOUNDMANAGER.play("11Thunder", 1.0f);
}

void PlayUI::MakeSkillIce()
{
	_ice->StartSkill(_player1.x + 70, _player1.y + 90);
	SOUNDMANAGER.play("13Ice", 1.0f);
}

void PlayUI::MakeSkillFire()
{
	for (int ii = 0; ii < 8; ++ii)
	{
		int distance = 100;
		float angle = PI / 4;
		_fire[ii]->StartSkill(_player1.x - 23 + cosf(angle * ii) * distance, _player1.y + 75 - sinf(angle * ii) * distance / 4);
	}
	SOUNDMANAGER.play("12Fire", 1.0f);
}

void PlayUI::ActiveSkillBox(int player)
{
	if (_itemBox[player]->GetState() != 0) return;
	else
	{
		_skill[player].enterKeyTime += TIMEMANAGER.getElapsedTime();
		if (_skill[player].enterKeyTime > 1) _itemBox[player]->SetState(1);
	}
}

void PlayUI::ChangeSkillBox(int player)
{
	if (_itemBox[player]->GetState() != 2) return;
	_itemBox[player]->SetChange(true);
}

void PlayUI::SelectSkillBox(int player)
{
	if (_itemBox[player]->GetState() == 2 && !_itemBox[player]->GetChange())
	{
		_skill[player].selectSkill = _itemBox[player]->GetSelectSkill();
		_itemBox[player]->SetState(3);
	}
	else if (_itemBox[player]->GetState() == 0) UseSkill(player);
	else return;
}

void PlayUI::UseSkill(int player)
{
	if (!_skill[player].fullCharge[_skill[player].selectSkill]) return;
	if (_skill[player].selectSkill == 0)
	{
		MakeSkillIce();
	}
	else if (_skill[player].selectSkill == 1)
	{
		MakeSkillFire();
	}
	else if (_skill[player].selectSkill == 2)
	{
		MakeSkillThunder();
	}
	_skill[player].currentGauge[_skill[player].selectSkill] = 0;
	_skill[player].fullCharge[_skill[player].selectSkill] = false;
}


void PlayUI::ChargeSkillGauge(int playerNum)
{
	for (int ii = 0; ii < 3; ++ii)
	{
		if (_skill[playerNum].fullCharge[ii]) continue;
		_skill[playerNum].currentGauge[ii] += TIMEMANAGER.getElapsedTime();
		if (_skill[playerNum].currentGauge[ii] > _skill[playerNum].maxGauge[ii])
		{
			_skill[playerNum].fullCharge[ii] = true;
			_skill[playerNum].currentGauge[ii] = _skill[playerNum].maxGauge[ii];
		}
	}

}

void PlayUI::SetPlayerPos(int playerNum, float x, float y, int state)
{
	//State가 2,3,4,5,6,7 이 아니면 스킬 사용 불가
	if (playerNum == 0)
	{
		_player1.x = x;
		_player1.y = y;
		_player1.state = state;
	}
	else
	{
		_player2.x = x;
		_player2.y = y;
		_player2.state = state;
	}
}

void PlayUI::SetPlayerClass(int playerNum, int job)
{
	if (playerNum == 0)
	{
		_player1.job = job;
	}
	else _player2.job = job;
}

