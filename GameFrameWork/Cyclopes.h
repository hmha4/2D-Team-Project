#pragma once
#include "Enemy.h"
class Cyclopes :public Enemy
{
private:

public:
	Cyclopes(ENEMYTYPE _eType);
	~Cyclopes();

	virtual HRESULT Init(int x, int y, ENEMYSTATE eState);

	virtual void Release();

	virtual void EnemyUpdate(PlayerManager*pm);

	virtual void DieEnemy();

	virtual void Damaged();
};

