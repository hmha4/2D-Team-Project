#pragma once
#include "Enemy.h"
class BlackArchor:public Enemy
{
private:
	float attackTime;
public:
	BlackArchor(ENEMYTYPE _eType);
	~BlackArchor();

	virtual HRESULT Init(int x, int y, ENEMYSTATE eState);

	virtual void Release();

	virtual void EnemyUpdate(PlayerManager*pm);

	virtual void DieEnemy();

	virtual void Damaged();
};

