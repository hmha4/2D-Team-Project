#pragma once
#include "gameNode.h"

struct tagPlayerInfo
{
	int		job;
	int		hp;
	int		level;
	int		skill;
	int		score;
	float	x;
	float	y;
};

class ItemBox;
class SkillWarrior;
class SkillIce;
class SkillFire;

class PlayUI :	public gameNode
{
private:
	tagPlayerInfo	_player1;
	tagPlayerInfo	_player2;
	//플레이어 1p 2p 정보
	int				_playerNum;
	//깜빡임을 위한 카운트
	int				_insertCoinCount;
	int				_insertCoinHide;

	ItemBox*		_itemBox[2];

	image*			_fighterFace;
	image*			_fighterEquip;
	image*			_wizardFace;
	image*			_wizardEquip;
	image*			_brick;
	image*			_UItitle;
	image*			_hpGauge;

	RECT			_zRC;

	//스킬
	SkillWarrior*	_warrior;
	SkillIce*		_ice;
	SkillFire*		_fire[8];

public:
	PlayUI();
	~PlayUI();

	HRESULT Init(int playerNum);
	void Release();
	void Update();
	void Render();

	void MakeTable(HDC hdc, int x, int y, tagPlayerInfo player, int itemNum);
	void DrawClass(HDC hdc, int x, int y, tagPlayerInfo player);
	void DrawScore(HDC hdc, int x, int y, int score);
	void DrawHP(HDC hdc, int x, int y);
	void DrawHPgauge(HDC hdc, int x, int y, int hp);
	void DrawLevel(HDC hdc, int x, int y, int level);
	void DrawSkillGauge(HDC hdc, int x, int y, float gauge);
	void DrawInserCoin(HDC hdc);

	void MakeSkillThunder();
	void MakeSkillIce();
	void MakeSkillFire();

	void SetLvHp(int playerNum, int hp, int lv);
	void SetPlayerPos(int playerNum, float x, float y);
	void SetPlayerClass(int playerNum, int job);

	void SetLinkItemBox1(ItemBox* address) { _itemBox[0] = address; }
	void SetLinkItemBox2(ItemBox* address) { _itemBox[1] = address; }

	//	Z-ORDER를 위한 RC
	inline RECT &getRc() { return _zRC; }
};

