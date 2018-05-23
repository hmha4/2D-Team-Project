#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy(ENEMYTYPE _eType)
	:eType(_eType)
{
}


Enemy::~Enemy()
{
}

HRESULT Enemy::Init()
{
	isDie = false;
	isShow = false;
	alpha = 0;
	shadowColRc = RectMake(0, 0, 0, 0);
	return S_OK;
}

HRESULT Enemy::Init(int x, int y, ENEMYSTATE eState)
{
	rc = RectMakeCenter(x, y, img->GetFrameWidth(), img->GetFreamHeight());
	shadowRc = RectMake(rc.right - img->GetFrameWidth(), (rc.bottom - img->GetFreamHeight() / 3) + 15, img->GetFrameWidth(), img->GetFreamHeight() / 3);

	posX = GetCenterPos(rc).x;
	posY = GetCenterPos(rc).y;

	this->eState = eState;
	isDie = false;
	isShow = false;
	alpha = 0;
	return S_OK;
}

void Enemy::Render()
{
	if (isShow && !isDie)
	{
		if (eState != END)
			img->aniRender(getMemDC(), rc.left, rc.top, anim);
		else
			img->alphaAniRender(getMemDC(), rc.left, rc.top, anim, alpha);
	}
	//Rectangle(getMemDC(), shadowRc.left, shadowRc.top, shadowRc.right, shadowRc.bottom);
}

void Enemy::Update(PlayerManager*pm)
{
	EnemyUpdate(pm);
}

void Enemy::Release()
{
}

