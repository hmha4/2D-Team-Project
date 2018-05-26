#pragma once
#include "Enemy.h"
class Dragon:public Enemy
{
private:
	enum DRAGONATTACK
	{
		HAND_FOLLOW,
		HAND_DOWN,
		HAND_UP
	};
private:
	image*dHead;
	animation*dHeadAnim;
	RECT dHeadRc;
	RECT colRect;
	float headX;
	float headY;
	float initHeadX;
	float initHeadY;

	image*dHand;
	animation*dHandAnim;
	RECT dHandRc;
	float handX;
	float handY;
	float initHandX;
	float initHandY;
	float handAngle;

	float shadowX;
	float shadowY;

	float showTime;
	DRAGONATTACK dAttack;
	float dieTime;

	int atkArr[8];
	int atkIdx;
public:
	Dragon(ENEMYTYPE _eType);
	~Dragon();

	virtual HRESULT Init(int x, int y, ENEMYSTATE eState);

	virtual void Release();

	virtual void EnemyUpdate(PlayerManager*pm);

	virtual void DieEnemy();

	virtual void Damaged();

	void RandomAttack(int num);

	void UpdateAttackArr();

	virtual void DragonRender();

	virtual inline RECT&getDragonFootRc() {
		return colRect;
	}
};

