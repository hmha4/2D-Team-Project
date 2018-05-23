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
	//	1p�̳� 2p�̳�
	enum PLAYER
	{
		PLAYER_1,
		PLAYER_2,
		DEFFAULT
	};
	//	� ĳ���͸� �����
	enum CHARACTER
	{
		BOWMAN,
		MAGICIAN,
		WARRIOR,
		CLERIC,
		DWARF
	};

	Character *		_player[2];			//	�÷��̾�
	PLAYER			_playerNum;			//	1p2p
	CHARACTER		_character[2];		//	� ĳ����

	PlayUI*			UI;					//	UI
	ItemBox*		_itemBox[2];		//  ������ �ڽ�
	PlayerSkill*	_skill[2];			//  ��ų

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

