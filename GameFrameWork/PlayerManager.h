#pragma once
#include "gameNode.h"
#include "Warrior.h"
#include "Magician.h"
#include "PlayUI.h"

class PlayerManager :
	public gameNode
{
private:
	enum PLAYER
	{
		PLAYER_1,
		PLAYER_2,
		DEFFAULT
	};
	enum CHARACTER
	{
		BOWMAN,
		MAGICIAN,
		WARRIOR,
		CLERIC,
		DWARF
	};

	Character * _player[2];
	PLAYER		_playerNum;
	CHARACTER	_character[2];

	PlayUI*		UI;
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
};

