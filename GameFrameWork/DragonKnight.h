#pragma once
#include "Enemy.h"
class DragonKnight:public Enemy
{
private:
	enum SHOWSTATE
	{
		CHANGE_BEGIN,
		CHANGE_END,
		LEFT_JUMP,
		LEFT_JUMPATTACK,
		RIGHT_JUMP,
		RIGHT_JUMPATTACK
	};
	SHOWSTATE sState;
	float startTime;
	float attackTime;
	float setAngle;

	float setShadowY;

	float dieTime;
	float initPosY;
	float gravity;
	float angle;


public:
	DragonKnight(ENEMYTYPE _eType);
	~DragonKnight();

	virtual HRESULT Init(int x, int y, ENEMYSTATE eState);

	virtual void Release();

	virtual void EnemyUpdate(PlayerManager*pm);

	virtual void DieEnemy();

	virtual void Damaged();

	void RandomAttack(int num);
};

