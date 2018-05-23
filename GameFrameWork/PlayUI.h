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

class ItemBox;

class PlayUI :	public gameNode
{
private:
	tagPlayerInfo	 _player1;
	tagPlayerInfo	 _player2;

	ItemBox*		_itemBox[2];

	image*			_fighterFace;
	image*			_fighterEquip;
	image*			_brick;
	image*			_UItitle;
	image*			_hpGauge;

	RECT			_zRC;

public:
	PlayUI();
	~PlayUI();

	HRESULT Init();
	void Release();
	void Update();
	void Render();

	void MakeTable(HDC hdc, int x, int y, tagPlayerInfo player, int itemNum);
	void DrawClass(HDC hdc, int x, int y, tagPlayerInfo player);
	void DrawScore(HDC hdc, int x, int y, int score);
	void DrawHP(HDC hdc, int x, int y);
	void DrawLevel(HDC hdc, int x, int y, int level);
	void DrawItemStock(HDC hdc, int x, int y, int stock);
	void SetLinkItemBox1(ItemBox* address) { _itemBox[0] = address; }
	void SetLinkItemBox2(ItemBox* address) { _itemBox[1] = address; }

	//	Z-ORDER¸¦ À§ÇÑ RC
	inline RECT &getRc() { return _zRC; }
};

