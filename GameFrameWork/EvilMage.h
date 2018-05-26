#pragma once
#include "Enemy.h"
class EvilMage:public Enemy
{
private:
	float showTime;
	float shot1Time;
	float shot2Time;
	float shot3Time;

	int atkArr[8];
	int atkIdx;

	float setangle;
	float setangle2;
	float atk2Angle;

	float atk2X;
	float atk2Y;

	float dieTime;

public:
	EvilMage(ENEMYTYPE _eType);
	~EvilMage();

	virtual HRESULT Init(int x, int y, ENEMYSTATE eState);

	virtual void Release();

	virtual void EnemyUpdate(PlayerManager*pm);

	virtual void DieEnemy();

	virtual void Damaged();

	void RandomAttack(int num);

	void UpdateAttackArr();
};

