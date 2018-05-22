#pragma once
#include "Enemy.h"
class Mino:public Enemy
{
private:

public:
	Mino(ENEMYTYPE _eType);
	~Mino();

	virtual HRESULT Init(int x, int y, ENEMYSTATE eState);

	virtual void Release();

	virtual void EnemyUpdate(PlayerManager*pm);

	virtual void DieEnemy();

	virtual void Damaged();
};

