#include "stdafx.h"
#include "skeleton.h"


Skeleton::Skeleton(ENEMYTYPE _eType)
	:Enemy(_eType)
{
	IMAGEMANAGER.addFrameImage("½ºÄÌ·¹Åæ", PathFile("image\\Enemy", "½ºÄÌ·¹Åæ").c_str(), 2226, 194, 14, 2, true, RGB(255, 0, 255));
	EFFECTMANAGER.addEffect("ÇØ°ñÆø¹ß", PathFile("image\\Enemy", "»ý¹°Æø¹ß").c_str(), 1653, 90, 92, 90, 60, 1, 30);
}


Skeleton::~Skeleton()
{
}

HRESULT Skeleton::Init(int x, int y, ENEMYSTATE eState)
{

	int leftIdle[] = { 0,1,2 };
	ANIMATIONKEY.addArrayFrameAnimation("skLeftIdle", "½ºÄÌ·¹Åæ", leftIdle, 3, 5, false);

	int rightIdle[] = { 27,26,25 };
	ANIMATIONKEY.addArrayFrameAnimation("skRightIdle", "½ºÄÌ·¹Åæ", leftIdle, 3, 5, false);

	int leftMove[] = { 3,4,5,6,7,8 };
	ANIMATIONKEY.addArrayFrameAnimation("skLeftMove", "½ºÄÌ·¹Åæ", leftMove, 6, 7, true);

	int leftStop[] = { 3 };
	ANIMATIONKEY.addArrayFrameAnimation("skLeftStop", "½ºÄÌ·¹Åæ", leftStop, 1, 1, false);

	int rightStop[] = { 24 };
	ANIMATIONKEY.addArrayFrameAnimation("skRightStop", "½ºÄÌ·¹Åæ", rightStop, 1, 1, false);

	int rightMove[] = { 24,23,22,21,20,19 };
	ANIMATIONKEY.addArrayFrameAnimation("skRightMove", "½ºÄÌ·¹Åæ", rightMove, 6, 7, true);

	int leftAttack[] = { 9,10,11,12,13 };
	ANIMATIONKEY.addArrayFrameAnimation("skLeftAttack", "½ºÄÌ·¹Åæ", leftAttack, 5, 7, false);

	int rightAttack[] = { 18,17,16,15,14 };
	ANIMATIONKEY.addArrayFrameAnimation("skRightAttack", "½ºÄÌ·¹Åæ", rightAttack, 5, 7, false);

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

	speed = RND.GetFromTo(1, 4);
	attackTime = 0;
	Friction = 0;

	hp = 2;
	isAttack = false;
	Enemy::Init(x, y, eState);

	return S_OK;
}

void Skeleton::Release()
{
}

void Skeleton::EnemyUpdate(PlayerManager * pm)
{
	DieEnemy();
	anim->frameUpdate(TIMEMANAGER.getElapsedTime());
	switch (eState)
	{
		DieEnemy();
	case LEFT_IDLE:
	{
		if (!anim->isPlay())
		{
			if (pm->GetPlayer(playerNumber)->GetX() < posX)
			{
				eState = LEFT_MOVE;
				*anim = *ANIMATIONKEY.findAnimation("skLeftMove");
				anim->start();
			}
			else
			{
				eState = RIGHT_MOVE;
				*anim = *ANIMATIONKEY.findAnimation("skRightMove");
				anim->start();
			}
		}
	}
	break;
	case RIGHT_IDLE:
	{
		if (!anim->isPlay())
		{
			if (pm->GetPlayer(playerNumber)->GetX() < posX)
			{
				eState = LEFT_MOVE;
				*anim = *ANIMATIONKEY.findAnimation("skLeftMove");
				anim->start();
			}
			else
			{
				eState = RIGHT_MOVE;
				*anim = *ANIMATIONKEY.findAnimation("skRightMove");
				anim->start();
			}
		}
	}
	break;
	case LEFT_MOVE:
	{
		if (pm->GetPlayer(playerNumber)->GetX() > posX)
		{
			eState = RIGHT_MOVE;
			*anim = *ANIMATIONKEY.findAnimation("skRightMove");
			anim->start();
		}
		angle = getAngle(GetCenterPos(shadowRc).x, GetCenterPos(shadowRc).y,
			GetCenterPos(pm->GetPlayer(playerNumber)->getRc()).x, GetCenterPos(pm->GetPlayer(playerNumber)->getRc()).y);

		posX += cosf(angle) * speed;
		posY += -sinf(angle) * speed;
		rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
		shadowRc = RectMake(rc.right - 80, rc.bottom - img->GetFreamHeight() / 3 + 15, 40, img->GetFreamHeight() / 3);

		RECT temp;
		RECT temp2 = RectMakeCenter(GetCenterPos(shadowRc).x, GetCenterPos(shadowRc).y, 10, 10);
		if (IntersectRect(&temp, &temp2, &pm->GetPlayer(playerNumber)->getRc()))
		{
			eState = LEFT_ATTACK;

			*anim = *ANIMATIONKEY.findAnimation("skLeftAttack");
			anim->start();
		}

	}
	break;
	case RIGHT_MOVE:
	{
		if (pm->GetPlayer(playerNumber)->GetX() < posX)
		{
			eState = LEFT_MOVE;
			*anim = *ANIMATIONKEY.findAnimation("skLeftMove");
			anim->start();
		}

		angle = getAngle(GetCenterPos(shadowRc).x, GetCenterPos(shadowRc).y,
			GetCenterPos(pm->GetPlayer(playerNumber)->getRc()).x, GetCenterPos(pm->GetPlayer(playerNumber)->getRc()).y);

		posX += cosf(angle) * speed;
		posY += -sinf(angle) * speed;
		rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
		shadowRc = RectMake(rc.right - 80, rc.bottom - img->GetFreamHeight() / 3 + 15, 40, img->GetFreamHeight() / 3);

		RECT temp;
		RECT temp2 = RectMakeCenter(GetCenterPos(shadowRc).x, GetCenterPos(shadowRc).y, 10, 10);
		if (IntersectRect(&temp, &temp2, &pm->GetPlayer(playerNumber)->getRc()))
		{
			eState = RIGHT_ATTACK;

			*anim = *ANIMATIONKEY.findAnimation("skRightAttack");
		}

	}
	break;
	case LEFT_ATTACK:
	{
		attackTime += TIMEMANAGER.getElapsedTime();

		if (attackTime < 0.3f)
		{
			anim->start();
		}
		else
		{
			if (!isAttack)
			{
				SOUNDMANAGER.play("36SkeletonAttack");
				BULLET.Shot("½ºÄÌ°Ë", posX-30, posY, PI, 0, 0, 0);
				isAttack = true;
			}
			if (!anim->isPlay())
			{
				if (DATABASE.LoadData("1P2P") == 1)
					playerNumber = RND.GetFromTo(0, 2);
				if (pm->GetPlayer(playerNumber)->GetX() < posX)
				{
					eState = LEFT_MOVE;
					*anim = *ANIMATIONKEY.findAnimation("skLeftMove");
					anim->start();
					attackTime = 0;
					isAttack = false;
					for (int i = 0; i < BULLET.GetBulletVec("½ºÄÌ°Ë").size(); i++)
						BULLET.Destroy("½ºÄÌ°Ë", i);
				}
				else
				{
					eState = RIGHT_MOVE;
					*anim = *ANIMATIONKEY.findAnimation("skRightMove");
					anim->start();
					attackTime = 0;
					isAttack = false;
					for (int i = 0; i < BULLET.GetBulletVec("½ºÄÌ°Ë").size(); i++)
						BULLET.Destroy("½ºÄÌ°Ë", i);
				}
			}
		}
	}
	break;
	case RIGHT_ATTACK:
	{
		attackTime += TIMEMANAGER.getElapsedTime();

		if (attackTime < 0.8f)
		{
			anim->start();
		}
		else
		{
			if (!isAttack)
			{
				SOUNDMANAGER.play("36SkeletonAttack");
				BULLET.Shot("½ºÄÌ°Ë", posX+30, posY, 0, 0, 0, 0);
				isAttack = true;
			}
			if (!anim->isPlay())
			{
				if (DATABASE.LoadData("1P2P") == 1)
					playerNumber = RND.GetFromTo(0, 2);
				if (pm->GetPlayer(playerNumber)->GetX() < posX)
				{
					eState = LEFT_MOVE;
					*anim = *ANIMATIONKEY.findAnimation("skLeftMove");
					anim->start();
					attackTime = 0;
					isAttack = false;
					for (int i = 0; i < BULLET.GetBulletVec("½ºÄÌ°Ë").size(); i++)
						BULLET.Destroy("½ºÄÌ°Ë", i);
				}
				else
				{
					eState = RIGHT_MOVE;
					*anim = *ANIMATIONKEY.findAnimation("skRightMove");
					anim->start();
					attackTime = 0;
					isAttack = false;
					for (int i = 0; i < BULLET.GetBulletVec("½ºÄÌ°Ë").size(); i++)
						BULLET.Destroy("½ºÄÌ°Ë", i);
				}
			}
		}
	}
	break;
	case LEFT_DAMAGE:
	{
		Friction -= 0.2;
		posX += cosf(0) * 6 + Friction;
		posY += -sinf(0) * 6;
		rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
		shadowRc = RectMake(rc.right - 80, rc.bottom - img->GetFreamHeight() / 3 + 15, 40, img->GetFreamHeight() / 3);


		if (Friction*(-1) > totalPower)
		{
			totalPower = 0;
			Friction = 0;
			if (DATABASE.LoadData("1P2P") == 1)
				playerNumber = RND.GetFromTo(0, 2);
			if (pm->GetPlayer(playerNumber)->GetX() < posX)
			{
				eState = LEFT_MOVE;
				*anim = *ANIMATIONKEY.findAnimation("skLeftMove");
				anim->start();
				attackTime = 0;
			}
			else
			{
				eState = RIGHT_MOVE;
				*anim = *ANIMATIONKEY.findAnimation("skRightMove");
				anim->start();
				attackTime = 0;
			}
		}
	}
	break;
	case RIGHT_DAMAGE:
	{
		Friction += 0.2;
		posX += cosf(PI) * 6 + Friction;
		posY += -sinf(PI) * 6;
		rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
		shadowRc = RectMake(rc.right - 80, rc.bottom - img->GetFreamHeight() / 3 + 15, 40, img->GetFreamHeight() / 3);

		if (Friction*(-1) < totalPower)
		{
			totalPower = 0;
			Friction = 0;
			if (DATABASE.LoadData("1P2P") == 1)
				playerNumber = RND.GetFromTo(0, 2);
			if (pm->GetPlayer(playerNumber)->GetX() < posX)
			{
				eState = LEFT_MOVE;
				*anim = *ANIMATIONKEY.findAnimation("skLeftMove");
				anim->start();
				attackTime = 0;
			}
			else
			{
				eState = RIGHT_MOVE;
				*anim = *ANIMATIONKEY.findAnimation("skRightMove");
				anim->start();
				attackTime = 0;
			}
		}
	}
	break;
	}
}

void Skeleton::DieEnemy()
{
	if (hp <= 0)
	{
		SOUNDMANAGER.play("30SkeletonDie");
		EFFECTMANAGER.play("ÇØ°ñÆø¹ß", posX, posY);
		isDie = true;
		isShow = false;
	}
}

void Skeleton::Damaged()
{
	hp--;

	if (eState == LEFT_MOVE || eState == LEFT_ATTACK)
	{
		eState = LEFT_DAMAGE;
		*anim = *ANIMATIONKEY.findAnimation("skLeftStop");
		anim->start();
		totalPower = cosf(0) * 6;
	}
	else if (eState == RIGHT_MOVE || eState == RIGHT_ATTACK)
	{
		eState = RIGHT_DAMAGE;
		*anim = *ANIMATIONKEY.findAnimation("skRightStop");
		anim->start();
		totalPower = cosf(PI) * 6;
	}
}