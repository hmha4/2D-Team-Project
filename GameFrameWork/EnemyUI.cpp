#include "stdafx.h"
#include "EnemyUI.h"


EnemyUI::EnemyUI()
	:_isDrawGo(false), _isDrawHP(false), _goCount(0), _isDying(false)
	, _isBlink(false), _blinkCount(0)
	, _goBlink(false), _goTimeCount(0)
{
	_zRC = RectMake(CAM.GetX(), CAM.GetY() + 550, 10, 10);
}


EnemyUI::~EnemyUI()
{
}

HRESULT EnemyUI::Init(int maxHP, int width, string name)
{
	_hpX = CAM.GetX() + 775;
	_hpY = CAM.GetY() + 50;
	
	_name = name;
	_maxHP = maxHP;
	_currentHP = maxHP;
	_widthHP = _shadowBar = width;

	return S_OK;
}

void EnemyUI::Release()
{
}

void EnemyUI::HpUpdate(int currentHP)
{
	if (!_isDrawHP || _currentHP == 0) return;
	
	_currentHP = currentHP;
	_hpBar = _widthHP * ((float)_currentHP / (float)_maxHP);
	if (_hpBar < _shadowBar)
	{
		_shadowBar -= HP_SPEED;
		if (_shadowBar <= _hpBar) _shadowBar = _hpBar;
	}
	_background =	RectMake(CAM.GetX() + _hpX - _widthHP, CAM.GetY() + _hpY, _widthHP, 30);
	_shadow =		RectMake(CAM.GetX() + _hpX - _widthHP, CAM.GetY() + _hpY, _shadowBar, 30);
	_hp =			RectMake(CAM.GetX() + _hpX - _widthHP, CAM.GetY() + _hpY, _hpBar, 30);
}

void EnemyUI::Update()
{
	MakeBlink();
}

void EnemyUI::Render()
{
	if (_isDrawHP)
	{
		DrawHP(getMemDC());
		DrawName(getMemDC(), _background.right + 2, _background.top + 2, true);
		DrawName(getMemDC(), _background.right, _background.top);
	}
	if (_isDrawGo)
	{
		if (!_up)
		{
			DrawGo(getMemDC(), CAM.GetX() + 750 + 2, CAM.GetY() + 220 + 2, true, _up);
			DrawGo(getMemDC(), CAM.GetX() + 750, CAM.GetY() + 220, false, _up);
		}
		else
		{
			DrawGo(getMemDC(), CAM.GetX() + 730 + 2, CAM.GetY() + 220 + 2, true, _up);
			DrawGo(getMemDC(), CAM.GetX() + 730, CAM.GetY() + 220, false, _up);
		}
	}
}

void EnemyUI::DrawHP(HDC hdc)
{
	SelectObject(hdc, GetStockObject(GRAY_BRUSH));
	HPEN pen, oldPen;
	pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	oldPen = (HPEN)SelectObject(hdc, pen);
	
	Rectangle(hdc, _background.left, _background.top, _background.right, _background.bottom);
	
	SelectObject(hdc, oldPen);
	DeleteObject(pen);

	HBRUSH brush, oldBrush;
	brush = CreateSolidBrush(RGB(255, 0, 0));
	oldBrush = (HBRUSH)SelectObject(hdc, brush);
	pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	oldPen = (HPEN)SelectObject(hdc, pen);

	if (_currentHP > _maxHP / 5) Rectangle(hdc, _shadow.left, _shadow.top, _shadow.right, _shadow.bottom);

	SelectObject(hdc, oldPen);
	DeleteObject(pen);
	SelectObject(hdc, oldBrush);
	DeleteObject(brush);

	if (_currentHP <= _maxHP / 5)
	{
		_isDying = true;
		brush = CreateSolidBrush(RGB(255, 0, 0));
	}
	else brush = CreateSolidBrush(RGB(255, 255, 0));
	oldBrush = (HBRUSH)SelectObject(hdc, brush);
	pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	oldPen = (HPEN)SelectObject(hdc, pen);

	if (!_isBlink) Rectangle(hdc, _hp.left, _hp.top, _hp.right, _hp.bottom);

	SelectObject(hdc, oldPen);
	DeleteObject(pen);
	SelectObject(hdc, oldBrush);
	DeleteObject(brush);	
}

void EnemyUI::DrawName(HDC hdc, int right, int top, bool shadow)
{
	//보스 이름
	HFONT font, oldFont;

	font = CreateFont(30, 0, 0, 0, 300, 0, 0, 0, DEFAULT_CHARSET,
		OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY,
		DEFAULT_PITCH | FF_SWISS, TEXT("Algerian"));

	oldFont = (HFONT)SelectObject(getMemDC(), font);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextAlign(hdc, TA_RIGHT | TA_BOTTOM);
	if (shadow)	SetTextColor(hdc, RGB(0, 0, 0));
	else SetTextColor(hdc, RGB(255, 0, 0));

	const char* boss = _name.c_str();

	TextOut(hdc, right, top, boss, strlen(boss));

	SelectObject(hdc, oldFont);
	DeleteObject(font);
	SetTextAlign(hdc, TA_LEFT | TA_TOP);
}

void EnemyUI::MakeBlink()
{
	if (_isDying)
	{
		_blinkCount++;
		if (_blinkCount < 15)
		{
			_isBlink = true;
		}
		else if (_blinkCount > 15 && _blinkCount <= 30)
		{
			_isBlink = false;
		}
		else if (_blinkCount > 30)
		{
			_blinkCount = 0;
		}
	}

	if (_isDrawGo)
	{
		_goTimeCount++;
		if (_goTimeCount <= 30)
		{
			_goBlink = true;
		}
		else if (_goTimeCount > 30 && _goTimeCount <= 60)
		{
			_goBlink = false;
		}
		else if (_goTimeCount > 60)
		{
			_goTimeCount = 0;
			_goCount--;
		}
		if (_goCount <= 0)
		{
			_isDrawGo = false;
			_goCount = 0;
		}
	}
}

void EnemyUI::DrawGo(HDC hdc, int right, int top, bool shadow, bool up)
{
	//보스 이름
	HFONT font, oldFont;

	font = CreateFont(50, 0, 0, 0, 500, 0, 0, 0, DEFAULT_CHARSET,
		OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY,
		DEFAULT_PITCH | FF_SWISS, TEXT("Algerian"));

	oldFont = (HFONT)SelectObject(getMemDC(), font);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextAlign(hdc, TA_CENTER | TA_BOTTOM);
	string go = "Go";
	
	if (shadow)	SetTextColor(hdc, RGB(0, 0, 0));
	else SetTextColor(hdc, RGB(255, 0, 0));

	const char* gogogo = go.c_str();

	//RECT textBox = RectMakeCenter(right-100, top, 100, 100);
	//DrawText(hdc, gogogo, strlen(gogogo), &textBox, DT_CENTER | DT_VCENTER);
	if (_goBlink)
	{
		TextOut(hdc, right, top, gogogo, strlen(gogogo));
		if (!up) IMAGEMANAGER.findImage("UI_DIRECTION")->frameRender(hdc, right - 33, top - 27, 0, (int)up);
		else IMAGEMANAGER.findImage("UI_DIRECTION")->frameRender(hdc, right + 10, top - 58, 0, (int)up);
	}

	SelectObject(hdc, oldFont);
	DeleteObject(font);
	SetTextAlign(hdc, TA_LEFT | TA_TOP);	
}

void EnemyUI::SetDrawGo(bool up)
{
	_isDrawGo = true;
	_goCount = 3;
	_up = up;
}
