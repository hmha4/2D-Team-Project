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
	_warrior = new Warrior;
	_warrior->Init(WINSIZEX / 2, WINSIZEY / 2);

	ZORDER.InputObj(_warrior);

	//_magician = new Magician;
	//_magician->Init(WINSIZEX / 2, WINSIZEY / 2);
	//
	//ZORDER.InputObj(_magician);

	return S_OK;
}

void PlayerManager::Render()
{
}

void PlayerManager::Update()
{
	_warrior->Update();
	//_magician->Update();
}

void PlayerManager::Release()
{
	_warrior->Release();
	//_magician->Release();
}
