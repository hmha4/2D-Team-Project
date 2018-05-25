#include "stdafx.h"
#include "BlackArchor.h"


BlackArchor::BlackArchor(ENEMYTYPE _eType)
	:Enemy(_eType)
{
	//IMAGEMANAGER.addFrameImage("")
}


BlackArchor::~BlackArchor()
{
}

HRESULT BlackArchor::Init(int x, int y, ENEMYSTATE eState)
{
	int leftIdle[] = { 23 };
	ANIMATIONKEY.addArrayFrameAnimation("skLeftIdle", "½ºÄÌ·¹Åæ", leftIdle, 3, 5, false);

	int rightIdle[] = { 4 };
	ANIMATIONKEY.addArrayFrameAnimation("skRightIdle", "½ºÄÌ·¹Åæ", leftIdle, 3, 5, false);

	int leftMove[] = {27,26,24};
	ANIMATIONKEY.addArrayFrameAnimation("skLeftMove", "½ºÄÌ·¹Åæ", leftMove, 6, 7, true);

	int rightMove[] = { 0,1,3 };
	ANIMATIONKEY.addArrayFrameAnimation("skRightMove", "½ºÄÌ·¹Åæ", rightMove, 6, 7, true);

	int leftAttack[] = { 22,21,20,19,18 };
	ANIMATIONKEY.addArrayFrameAnimation("skLeftAttack", "½ºÄÌ·¹Åæ", leftAttack, 5, 7, false);

	int rightAttack[] = {5,6,7,8,9};
	ANIMATIONKEY.addArrayFrameAnimation("skRightAttack", "½ºÄÌ·¹Åæ", rightAttack, 5, 7, false);

	int leftDie[] = {16,15,14};
	ANIMATIONKEY.addArrayFrameAnimation("skLeftDie", "½ºÄÌ·¹Åæ", rightAttack, 5, 7, false);
	
	int rightDie[] = {11,12,13};
	ANIMATIONKEY.addArrayFrameAnimation("skRightDie", "½ºÄÌ·¹Åæ", rightAttack, 5, 7, false);

	img = IMAGEMANAGER.findImage("½ºÄÌ·¹Åæ");

	anim = new animation;

	if (eState == LEFT_IDLE)
	{
		*anim = *ANIMATIONKEY.findAnimation("skLeftIdle");
	}
	else if (eState == RIGHT_IDLE)
	{
		*anim = *ANIMATIONKEY.findAnimation("skRightIdle");
	}
	anim->start();

	Enemy::Init(x, y, eState);
	return S_OK;
}

void BlackArchor::Release()
{
}

void BlackArchor::EnemyUpdate(PlayerManager * pm)
{
}

void BlackArchor::DieEnemy()
{
}

void BlackArchor::Damaged()
{
}
