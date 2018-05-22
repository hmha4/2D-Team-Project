#pragma once
#include "Enemy.h"
class Warewolf :public Enemy
{
private:
	float initPosY;//죽을때 필요해서
	float delayTime;
	float gravity;
	float dieTime;
	int getAlpha;

	int attackDistance;
	int delayCount;

	float speed;
public:
	Warewolf(ENEMYTYPE _eType);
	~Warewolf();

	virtual HRESULT Init(int x, int y, ENEMYSTATE eState);

	virtual void Release();

	virtual void EnemyUpdate(PlayerManager*pm);

	virtual void DieEnemy();

	virtual void Damaged() { hp--; }
};

