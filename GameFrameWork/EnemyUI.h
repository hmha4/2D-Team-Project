#pragma once
#include "gameNode.h"
#define	HP_SPEED 2
class EnemyUI :
	public gameNode
{
private:
	BOOL	_isDrawHP;
	BOOL	_isDrawGo;

	BOOL	_goBlink;
	int		_goCount;
	int		_goTimeCount;
	BOOL	_up;

	string	_name;
	int		_maxHP;
	int		_currentHP;
	int		_widthHP;
	int		_hpBar;
	int		_shadowBar;
	BOOL	_isDying;
	BOOL	_isBlink;
	int		_blinkCount;


	RECT	_background;
	RECT	_shadow;
	RECT	_hp;
	RECT	_zRC;

	int		_hpX, _hpY;
public:
	EnemyUI();
	~EnemyUI();

	HRESULT Init(int maxHP, int width, string name);
	void Release();
	void HpUpdate(int currentHP);
	void Update();
	void Render();

	void DrawHP(HDC hdc);
	void DrawName(HDC hdc, int right, int top, bool shadow = false);
	void MakeBlink();

	void DrawGo(HDC hdc, int right, int top, bool shadow = false, bool up = false);

	void SetDrawHP(BOOL draw) { _isDrawHP = draw; }
	void SetDrawGo(bool up = false);

	inline RECT &getRc() { return _zRC; }
};

