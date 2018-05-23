#pragma once
#include "gameNode.h"
#include "Warrior.h"
#include "Magician.h"
#include "PlayUI.h"
#include "ItemBox.h"
#include "PlayerSkill.h"

class PlayerManager :
	public gameNode
{
private:
	//	1p이냐 2p이냐
	enum PLAYER
	{
		PLAYER_1,
		PLAYER_2,
		DEFFAULT
	};
	//	어떤 캐릭터를 골랐냐
	enum CHARACTER
	{
		BOWMAN,
		MAGICIAN,
		WARRIOR,
		CLERIC,
		DWARF
	};

	Character *		_player[2];			//	플레이어
	PLAYER			_playerNum;			//	1p2p
	CHARACTER		_character[2];		//	어떤 캐릭터

	PlayUI*			UI;					//	UI
	ItemBox*		_itemBox[2];		//  아이템 박스
	PlayerSkill*	_skill[2];			//  스킬

public:
	PlayerManager();
	~PlayerManager();

	HRESULT Init();
	void Render();
	void Update();
	void Release();

	inline Character* GetPlayer1() { return _player[0]; }
	inline Character* GetPlayer2() { return _player[1]; }
	void MoveRestrict(int stage);

	void Collision(string bulletName, int playerNum);
};

