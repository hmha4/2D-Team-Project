#include "stdafx.h"
#include "PlayerManager.h"


PlayerManager::PlayerManager()
{
}


PlayerManager::~PlayerManager()
{
}

HRESULT PlayerManager::Init()
{
	_playerNum = (PLAYER)DATABASE.LoadData("1P2P");
	if(_playerNum == 0)
		_character[0] = (CHARACTER)DATABASE.LoadData("1PCharacter");
	else if (_playerNum == 1)
	{
		_character[0] = (CHARACTER)DATABASE.LoadData("1PCharacter");
		_character[1] = (CHARACTER)DATABASE.LoadData("2PCharacter");
	}

	for (int i = 0; i < _playerNum + 1; i++)
	{
		if (_character[i] == 1)
		{
			_player[i] = new Magician;
			_player[i]->Init(WINSIZEX / 2, WINSIZEY / 2, i);

			ZORDER.InputObj(_player[i]);
		}
		else if (_character[i] == 2)
		{
			_player[i] = new Warrior;
			_player[i]->Init(WINSIZEX / 2, WINSIZEY / 2, i);

			ZORDER.InputObj(_player[i]);
		}
	}
	return S_OK;
}

void PlayerManager::Render()
{
}

void PlayerManager::Update()
{
	for (int i = 0; i < _playerNum + 1; i++)
		_player[i]->Update();
}

void PlayerManager::Release()
{
	for (int i = 0; i < _playerNum + 1; i++)
		_player[i]->Release();
}

void PlayerManager::MoveRestrict(int stage)
{
	for(int i = 0; i < _playerNum + 1; i++)
		_player[i]->MovementRestrict(stage);
}
