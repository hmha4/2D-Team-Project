#pragma once
#include "Enemy.h"
class BlackArchor :public Enemy
{
private:
	float attackTime;

	float attackTime2;

	float initPosY;

	float gravity;

	float dieTime;

	float getAlpha;

	bool shot;
	float shotTime;
public:
	BlackArchor(ENEMYTYPE _eType);
	~BlackArchor();

	virtual HRESULT Init(int x, int y, ENEMYSTATE eState);

	virtual void Release();

	virtual void EnemyUpdate(PlayerManager*pm);

	virtual void DieEnemy();

	virtual void Damaged();
};

