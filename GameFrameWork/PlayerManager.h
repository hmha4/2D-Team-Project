#pragma once
#include "gameNode.h"
#include "Warrior.h"
#include "Magician.h"

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
public:
	PlayerManager();
	~PlayerManager();

	HRESULT Init();
	void Render();
	void Update();
	void Release();

	inline Character* GetPlayer() { return _player[0]; }
	void MoveRestrict(int stage);
};

