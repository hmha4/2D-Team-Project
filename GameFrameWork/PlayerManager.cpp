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
	//������ �ڽ� �̹���
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

		//�÷��̾� ���� UI�� ����
		UI->SetPlayerClass(i, (int)_character[i]);
	}




	return S_OK;
}

void PlayerManager::Render()
{
	_itemBox[0]->Render();
}

void PlayerManager::Update()
{
	UI->Update();
	//�÷��̾� ����, ü�� �����̷� ����
	for (int i = 0; i < _playerNum + 1; i++)
	{
		Collision("����ȭ��", i);
		Collision("���̰�", i);
		Collision("��ȣ��", i);
		Collision("�����", i);
		Collision("�����0", i);
		_player[i]->Update();
		//�÷��̾� ü��, ���� UI�� ����
		UI->SetLvHp(i, _player[i]->GetHP(), _player[i]->GetWeaponLv());
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
			_player[playerNum]->Collision(BULLET.GetBulletVec(bulletName)[j]->getRc());
			BULLET.Destroy(bulletName, j);
			break;
		}
	}
}
