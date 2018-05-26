#pragma once
#include "Enemy.h"
class Mino :public Enemy
{
private:
	bool isAttack;
	float atkWaitTime;
	float attack1Time;
	float damagedTime;

	float totalPower;
	float Friction;

	float initPosY;
	float getAlpha;
	float gravity;

	float dieTime;
	int rndValue;
	
	bool isAttack2;
	
	float attackSoundTime;
public:
	Mino(ENEMYTYPE _eType);
	~Mino();

	virtual HRESULT Init(int x, int y, ENEMYSTATE eState);

	virtual void Release();

	virtual void EnemyUpdate(PlayerManager*pm);

	virtual void DieEnemy();

	virtual void Damaged();
};

