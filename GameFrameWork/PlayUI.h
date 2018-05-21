#pragma once
#include "gameNode.h"

struct tagPlayerInfo
{
	int job;
	int hp;
	int level;
	int skill;
	int score;
};

class PlayUI :	public gameNode
{
private:
	tagPlayerInfo _player1;
	tagPlayerInfo _player2;

	image*	_fighterFace;
	image*	_fighterEquip;
	image*	_brick;
	image*	_UItitle;
	image*	_hpGauge;

public:
	PlayUI();
	~PlayUI();

	HRESULT init();
	void release();
	void update();
	void render();

	void MakeTable(HDC hdc, int x, int y, tagPlayerInfo player);
	void DrawClass(HDC hdc, int x, int y, tagPlayerInfo player);
	void DrawScore(HDC hdc, int x, int y, int score);
	void DrawHP(HDC hdc, int x, int y);
	void DrawLevel(HDC hdc, int x, int y, int level);
	void DrawItemStock(HDC hdc, int x, int y, int stock);
};

