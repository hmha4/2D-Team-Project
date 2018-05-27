#pragma once
#include "gameNode.h"
#include "Warrior.h"
#include "Magician.h"
#include "PlayUI.h"
#include "ItemBox.h"

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

public:
	PlayerManager();
	~PlayerManager();

	HRESULT Init();
	void Render();
	void Update();
	void Release();

	//	�÷��̾� 1
	inline Character* GetPlayer1() { return _player[0]; }
	//	�÷��̾� 2
	inline Character* GetPlayer2() { return _player[1]; }
	//	�̸����� �÷��̾� �ޱ�
	Character* GetPlayer(string player);
	//	�ε����� �÷��̾� �ޱ�(0:1, 1:2)
	Character* GetPlayer(int playerNum);
	void SetPlayerPos(float x, float y);
	void ChangeAnim(int state, string anim);
	void MoveRestrict(int stage);
	void Collision(string bulletName, int playerNum);
	void ChangeWeapon(int num);

	inline PlayUI*GetPlayUI() { return UI; }
};

