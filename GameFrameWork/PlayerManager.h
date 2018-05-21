#pragma once
#include "gameNode.h"
#include "Warrior.h"
#include "Magician.h"

class PlayerManager :
	public gameNode
{
private:
	Character * _warrior;
	Character * _magician;

public:
	PlayerManager();
	~PlayerManager();

	HRESULT Init();
	void Render();
	void Update();
	void Release();

	inline Character* GetWarrior() { return _warrior; }
	inline Character* GetMagician() { return _magician; }
};

