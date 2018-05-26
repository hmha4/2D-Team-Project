#pragma once
#include "gameNode.h"
#include "PlayerManager.h"
enum ENEMYTYPE
{
	WAREWOLF,
	SKELETON,
	MINO,
	DRAGONKNIGHT,
	BLACKARCHOR,
	CYCLOPSE,
	EVILMAGE,
	DRAGON
};
enum ENEMYSTATE
{
	LEFT_IDLE,
	RIGHT_IDLE,
	LEFT_ATTACK,
	RIGHT_ATTACK,
	LEFT_ATTACK2,
	RIGHT_ATTACK2,
	LEFT_ATTACK3,
	RIGHT_ATTACK3,
	LEFT_MOVE,
	RIGHT_MOVE,
	LEFT_DIE,
	RIGHT_DIE,
	LEFT_DAMAGE,
	RIGHT_DAMAGE,
	END
};
class Enemy :public gameNode
{
protected:
	ENEMYTYPE eType;
	ENEMYSTATE eState;

	image*img;
	animation*anim;

	image*shadowImg;
	bool isShadow;

	RECT rc;
	RECT shadowRc;
	RECT shadowColRc;

	float posX, posY;
	float angle;
	int hp;

	bool isDie;
	bool isShow;
	int alpha;
public:
	Enemy(ENEMYTYPE _eType);
	~Enemy();

	virtual HRESULT Init();
	virtual HRESULT Init(int x, int y, ENEMYSTATE eState);
	void Render();
	void Update(PlayerManager*pm);
	virtual void Release();

	virtual void DieEnemy() = 0;
	virtual void Damaged() = 0;
	virtual void EnemyUpdate(PlayerManager*pm) = 0;

	//용만쓸거임
	virtual void DragonRender();

	virtual inline RECT&getRc() { return shadowRc; }
	inline RECT&getColRc() { return rc; }
	inline ENEMYTYPE&getEnemyType() { return eType; }
	inline bool&getShowState() { return isShow; }
	inline bool&getDie() { return isDie; }
	inline int&getHp() { return hp; }
	inline RECT&getShadowColRc() { return shadowColRc; }
	virtual inline RECT&getDragonFootRc() { return RectMake(0, 0, 0, 0); }
};

