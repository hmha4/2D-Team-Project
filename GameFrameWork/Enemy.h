#pragma once
#include "gameNode.h"
#include "PlayerManager.h"
enum ENEMYTYPE
{
	WAREWOLF,
	SKELETON
};
enum ENEMYSTATE
{
	LEFT_IDLE,
	RIGHT_IDLE,
	LEFT_ATTACK,
	RIGHT_ATTACK,
	LEFT_MOVE,
	RIGHT_MOVE,
	LEFT_DIE,
	RIGHT_DIE,
	END
};
class Enemy :public gameNode
{
protected:
	ENEMYTYPE eType;
	ENEMYSTATE eState;

	image*img;
	animation*anim;

	RECT rc;
	RECT shadowRc;

	float posX, posY;
	float angle;
	int hp;

	bool isDie;
	bool isShow;
	int alpha;
public:
	Enemy(ENEMYTYPE _eType);
	~Enemy();

	virtual HRESULT Init(int x, int y,ENEMYSTATE eState);
	void Render();
	void Update(PlayerManager*pm);
	virtual void Release();

	virtual void DieEnemy() = 0;
	virtual void EnemyUpdate(PlayerManager*pm) = 0;


	virtual inline RECT&getRc() { return shadowRc; }
	inline RECT&getColRc() { return rc; }
	inline ENEMYTYPE&getEnemyType() { return eType; }
	inline bool&getShowState() { return isShow; }
	inline bool&getDie() { return isDie; }
	inline int&getHp() { return hp; }
};

