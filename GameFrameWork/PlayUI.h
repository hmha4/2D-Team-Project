#pragma once
#include "gameNode.h"

#define MAX_ICE 10
#define MAX_FIRE 20
#define MAX_THUNDER 60

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
		}
		maxGauge[0] = maxIce;
		maxGauge[1] = maxFire;
		maxGauge[2] = maxThunder;
		enterKeyTime = 0;
	}

	int selectSkill;
	float currentGauge[3];
	float maxGauge[3];
	float enterKeyTime;
};

struct tagPlayerInfo
{
	int		job;
	int		hp;
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

	RECT			_zRC;

	//��ų
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
	void ActiveSkillBox(int player);
	void ChangeSkillBox(int player);
	void SelectSkillBox(int player);
	void UseSkill(int player);

	void SetLvHp(int playerNum, int hp, int lv);
	void SetPlayerPos(int playerNum, float x, float y, int state);
	void SetPlayerClass(int playerNum, int job);

	void SetLinkItemBox1(ItemBox* address) { _itemBox[0] = address; }
	void SetLinkItemBox2(ItemBox* address) { _itemBox[1] = address; }

	

	//	Z-ORDER�� ���� RC
	inline RECT &getRc() { return _zRC; }
};

