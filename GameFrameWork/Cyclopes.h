#pragma once
#include "Enemy.h"
class Cyclopes :public Enemy
{
private:
	bool isAttack;
	float atkWaitTime;
	float attack1Time;

	int state;
	float initY;
	float gravity;

	bool isShot;
	int attack[4];
	int idx;

	float dieTime;
	int getAlpha;
public:
	Cyclopes(ENEMYTYPE _eType);
	~Cyclopes();

	virtual HRESULT Init(int x, int y, ENEMYSTATE eState);

	virtual void Release();

	virtual void EnemyUpdate(PlayerManager*pm);

	virtual void DieEnemy();

	virtual void Damaged();
};

