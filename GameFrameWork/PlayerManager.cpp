#include "stdafx.h"
#include "PlayerManager.h"
#include "Bullet.h"

PlayerManager::PlayerManager()
{

}


PlayerManager::~PlayerManager()
{
}

HRESULT PlayerManager::Init()
{
	//아이템 박스 이미지
	IMAGEMANAGER.addImage("ITEM_HEALTH", PathFile("image\\Itembox", "ITEMBOX_HEALTH").c_str(), 40, 40, false, NULL);
	IMAGEMANAGER.addImage("ITEM_ICE", PathFile("image\\Itembox", "ITEMBOX_ICE").c_str(), 40, 40, false, NULL);
	IMAGEMANAGER.addImage("ITEM_THUNDER", PathFile("image\\Itembox", "ITEMBOX_THUNDER").c_str(), 40, 40, false, NULL);
	IMAGEMANAGER.addImage("ITEM_FIRE", PathFile("image\\Itembox", "ITEMBOX_FIRE").c_str(), 40, 40, false, NULL);


	_playerNum = (PLAYER)DATABASE.LoadData("1P2P");
	if (_playerNum == 0)
	{
		_character[0] = (CHARACTER)DATABASE.LoadData("1PCharacter");
		_itemBox[0] = new ItemBox;
	}
	else if (_playerNum == 1)
	{
		_character[0] = (CHARACTER)DATABASE.LoadData("1PCharacter");
		_character[1] = (CHARACTER)DATABASE.LoadData("2PCharacter");
		_itemBox[0] = new ItemBox;
		_itemBox[1] = new ItemBox;
	}

	UI = new PlayUI;
	UI->Init((int)_playerNum);
	UI->SetLinkItemBox1(_itemBox[0]);
	UI->SetLinkItemBox2(_itemBox[1]);
	ZORDER.InputObj(UI);

	for (int i = 0; i < _playerNum + 1; i++)
	{
		if (_character[i] == 1)
		{
			_player[i] = new Magician;
			_player[i]->Init(-50, WINSIZEY / 2, i);
		}
		else if (_character[i] == 2)
		{
			_player[i] = new Warrior;
			_player[i]->Init(-50, WINSIZEY / 2, i);
		}
		ZORDER.InputObj(_player[i]);

		//플레이어 직업 UI에 전달
		UI->SetPlayerClass(i, (int)_character[i]);
	}




	return S_OK;
}

void PlayerManager::Render()
{
	_itemBox[0]->Render();
	if (_playerNum == 1) _itemBox[1]->Render();
}

void PlayerManager::Update()
{
	UI->Update();
	//플레이어 레벨, 체력 유아이로 전송
	for (int i = 0; i < _playerNum + 1; i++)
	{
		Collision("웨어화살", i);
		Collision("스켈검", i);
		Collision("민호검", i);
		Collision("용기사검", i);
		Collision("용기사검0", i);
		Collision("블랙아처화살", i);
		Collision("외돌", i);
		Collision("마총1", i);
		Collision("마총2", i);
		Collision("마총3", i);
		Collision("드총", i);
		Collision("드브", i);
		_player[i]->Update();
		//플레이어 체력, 레벨 UI로 전달
		UI->SetLvHp(i, _player[i]->GetMaxHP(), _player[i]->GetHP(), _player[i]->GetWeaponLv());
		UI->SetPlayerPos(i, _player[i]->GetX(), _player[i]->GetY(), (int)_player[i]->GetState());

		_itemBox[i]->Update(_player[i]->GetX(), _player[i]->GetY());
		//_skill[i]->Update(_player[i]->GetX(), _player[i]->GetY());
	}
}

void PlayerManager::Release()
{
	for (int i = 0; i < _playerNum + 1; i++)
	{
		_player[i]->Release();
		SAFE_DELETE(_player[i]);
		SAFE_DELETE(_itemBox[i]);
	}
	SAFE_DELETE(UI);
}

Character * PlayerManager::GetPlayer(string player)
{
	CHARACTER playerName;

	if (player == "warrior") playerName = WARRIOR;
	else if (player == "magician") playerName = MAGICIAN;

	for (int i = 0; i < _playerNum + 1; i++)
	{
		if (_character[i] == playerName)
		{
			return _player[i];
		}
	}
}

Character * PlayerManager::GetPlayer(int playerNum)
{
	return _player[playerNum];
}

void PlayerManager::SetPlayerPos(float x, float y)
{
	for (int i = 0; i < _playerNum + 1; i++)
	{
		if (_character[i] == 1)
		{
			_player[i]->SetPos(x, y);
		}
		else if (_character[i] == 2)
		{
			_player[i]->SetPos(x, y);
		}
	}
}

void PlayerManager::ChangeAnim(int state, string anim)
{
	string warrior = "Warrior";
	string magician = "Magician";

	warrior.append(anim);
	magician.append(anim);

	for (int i = 0; i < _playerNum + 1; i++)
	{
		if (_character[i] == 1)
		{
			_player[i]->ChangeAnim(state, magician);
		}
		else if (_character[i] == 2)
		{
			_player[i]->ChangeAnim(state, warrior);
		}
	}
}

void PlayerManager::MoveRestrict(int stage)
{
	for (int i = 0; i < _playerNum + 1; i++)
		_player[i]->MovementRestrict(stage);
}

void PlayerManager::Collision(string bulletName, int playerNum)
{
	for (int j = 0; j < BULLET.GetBulletVec(bulletName).size(); j++)
	{
		if (!BULLET.GetBulletVec(bulletName)[j]->isShot) continue;
		RECT rc;
		if (IntersectRect(&rc, &_player[playerNum]->getRc(), &BULLET.GetBulletVec(bulletName)[j]->getRc()))
		{
			if(bulletName == "드브")
				_player[playerNum]->Collision(BULLET.GetBulletVec(bulletName)[j]->getRc(), "fire", "left");
			else if(bulletName == "드총")
				_player[playerNum]->Collision(BULLET.GetBulletVec(bulletName)[j]->getRc(), "fire");
			else
				_player[playerNum]->Collision(BULLET.GetBulletVec(bulletName)[j]->getRc(), "normal");
			
			if(bulletName!= "드브"&&bulletName != "마총2")
				BULLET.Destroy(bulletName, j);
			break;
		}
	}
}

void PlayerManager::ChangeWeapon(int num)
{
	for (int i = 0; i < _playerNum + 1; i++)
	{
		_player[i]->SetWeaponLv(num);
	}
}
