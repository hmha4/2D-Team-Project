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

public:
	PlayerManager();
	~PlayerManager();

	HRESULT Init();
	void Render();
	void Update();
	void Release();

	//	플레이어 1
	inline Character* GetPlayer1() { return _player[0]; }
	//	플레이어 2
	inline Character* GetPlayer2() { return _player[1]; }
	//	이름으로 플레이어 받기
	Character* GetPlayer(string player);
	//	인덱스로 플레이어 받기(0:1, 1:2)
	Character* GetPlayer(int playerNum);
	void SetPlayerPos(float x, float y);
	void ChangeAnim(int state, string anim);
	void MoveRestrict(int stage);
	void Collision(string bulletName, int playerNum);
	void ChangeWeapon(int num);

	inline PlayUI*GetPlayUI() { return UI; }
};

