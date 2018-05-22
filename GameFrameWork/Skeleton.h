#pragma once
#include "Enemy.h"
class Skeleton:public Enemy
{
private:
	float totalPower;
	float Friction;
	float attackTime;

	int speed;
public:
	Skeleton(ENEMYTYPE _eType);
	~Skeleton();

	virtual HRESULT Init(int x, int y, ENEMYSTATE eState);

	virtual void Release();

	virtual void EnemyUpdate(PlayerManager*pm);

	virtual void DieEnemy();

	virtual void Damaged();
};

