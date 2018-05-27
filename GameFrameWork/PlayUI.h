#pragma once
#include "gameNode.h"

#define MAX_ICE 30.0f
#define MAX_FIRE 60.0f
#define MAX_THUNDER 120.0f

struct tagSkill
{
	tagSkill()
	{};

	tagSkill(float maxIce, float maxFire, float maxThunder)
	{
		selectSkill = 0;
		for (int ii = 0; ii < 3; ++ii)
		{
			currentGauge[ii] = 0;
			fullCharge[ii] = false;
		}
		maxGauge[0] = maxIce;
		maxGauge[1] = maxFire;
		maxGauge[2] = maxThunder;
		enterKeyTime = 0;
	}

	int		selectSkill;
	float	currentGauge[3];
	float	maxGauge[3];
	BOOL	fullCharge[3];
	float	enterKeyTime;
};

struct tagPlayerInfo
{
	int		job;
	int		hp;
	int		maxHp;
	int		level;
	int		skill;
	int		score;
	int		state;			//State�� 2,3,4,5,6,7 �� �ƴϸ� ��ų ��� �Ұ�
	float	x;
	float	y;
};

class ItemBox;
class SkillWarrior;
class SkillIce;
class SkillFire;
class EnemyUI;

class PlayUI :	public gameNode
{
private:
	//�÷��̾� 1p 2p ����
	tagPlayerInfo	_player1;
	tagPlayerInfo	_player2;
	//�÷��̾� 1p 2p ��ų ����
	tagSkill		_skill[2];
	//�÷��̾� �������
	int				_playerNum;
	//�������� ���� ī��Ʈ
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
	image*			_skillGauge;

	RECT			_zRC;

	//��ų
	SkillWarrior*	_warrior;
	SkillIce*		_ice;
	SkillFire*		_fire[8];

	COLORREF		_red;
	COLORREF		_orange;
	COLORREF		_yellow;
	COLORREF		_green;
	COLORREF		_rnd;
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
	void DrawHPgauge(HDC hdc, int x, int y, int hp, int maxHp);
	void DrawLevel(HDC hdc, int x, int y, int level);
	void DrawSkillGauge(HDC hdc, RECT rc, int player, int selectSkill);
	void DrawInserCoin(HDC hdc);

	void MakeSkillThunder(int player);
	void MakeSkillIce(int player);
	void MakeSkillFire(int player);
	void ActiveSkillBox(int player);
	void ChangeSkillBox(int player);
	void SelectSkillBox(int player);
	void UseSkill(int player);
	void ChargeSkillGauge(int playerNum);

	void SetLvHp(int playerNum, int maxhp, int hp, int lv);
	void SetPlayerPos(int playerNum, float x, float y, int state);
	void SetPlayerClass(int playerNum, int job);

	void SetLinkItemBox1(ItemBox* address) { _itemBox[0] = address; }
	void SetLinkItemBox2(ItemBox* address) { _itemBox[1] = address; }

	

	//	Z-ORDER�� ���� RC
	inline RECT &getRc() { return _zRC; }
};

