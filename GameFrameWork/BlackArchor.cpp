#include "stdafx.h"
#include "BlackArchor.h"


BlackArchor::BlackArchor(ENEMYTYPE _eType)
	:Enemy(_eType)
{
	IMAGEMANAGER.addFrameImage("블랙아처", PathFile("image\\Enemy", "블랙아처").c_str(), 1747, 280, 14, 2, true, RGB(255, 0, 255));
}


BlackArchor::~BlackArchor()
{
}

HRESULT BlackArchor::Init(int x, int y, ENEMYSTATE eState)
{
	int leftIdle[] = { 23 };
	ANIMATIONKEY.addArrayFrameAnimation("baLeftIdle", "블랙아처", leftIdle, 1, 5, false);

	int rightIdle[] = { 4 };
	ANIMATIONKEY.addArrayFrameAnimation("baRightIdle", "블랙아처", leftIdle, 1, 5, false);

	int leftMove[] = { 27,26,24 };
	ANIMATIONKEY.addArrayFrameAnimation("baLeftMove", "블랙아처", leftMove, 3, 7, true);

	int rightMove[] = { 0,1,3 };
	ANIMATIONKEY.addArrayFrameAnimation("baRightMove", "블랙아처", rightMove, 3, 7, true);

	int leftAttack[] = { 22,21,20,19,18 };
	ANIMATIONKEY.addArrayFrameAnimation("baLeftAttack", "블랙아처", leftAttack, 5, 4, false);

	int rightAttack[] = { 5,6,7,8,9 };
	ANIMATIONKEY.addArrayFrameAnimation("baRightAttack", "블랙아처", rightAttack, 5, 4, false);

	int leftDie[] = { 16,15,14 };
	ANIMATIONKEY.addArrayFrameAnimation("baLeftDie", "블랙아처", leftDie, 3, 7, false);

	int rightDie[] = { 11,12,13 };
	ANIMATIONKEY.addArrayFrameAnimation("baRightDie", "블랙아처", rightDie, 3, 7, false);

	img = IMAGEMANAGER.findImage("블랙아처");

	anim = new animation;

	if (eState == LEFT_IDLE)
	{
		*anim = *ANIMATIONKEY.findAnimation("baLeftIdle");
	}
	else if (eState == RIGHT_IDLE)
	{
		*anim = *ANIMATIONKEY.findAnimation("baRightIdle");
	}
	anim->start();

	Enemy::Init(x, y, eState);

	attackTime = 0;
	attackTime2 = 0;
	initPosY = 0;
	gravity = 0;
	dieTime = 0;
	getAlpha = 15;
	hp = 3;
	shot = false;
	shotTime = 0;
	return S_OK;
}

void BlackArchor::Release()
{
}

void BlackArchor::EnemyUpdate(PlayerManager * pm)
{
	anim->frameUpdate(TIMEMANAGER.getElapsedTime());
	switch (eState)
	{
	case LEFT_IDLE:
	{
		DieEnemy();
		if (!anim->isPlay())
		{
			if (pm->GetPlayer1()->GetX() < posX)
			{
				eState = LEFT_MOVE;
				*anim = *ANIMATIONKEY.findAnimation("baLeftMove");
				anim->start();
			}
			else
			{
				eState = RIGHT_MOVE;
				*anim = *ANIMATIONKEY.findAnimation("baRightMove");
				anim->start();
			}
		}
	}
	break;
	case RIGHT_IDLE:
	{
		DieEnemy();
		if (!anim->isPlay())
		{
			if (pm->GetPlayer1()->GetX() < posX)
			{
				eState = LEFT_MOVE;
				*anim = *ANIMATIONKEY.findAnimation("baLeftMove");
				anim->start();
			}
			else
			{
				eState = RIGHT_MOVE;
				*anim = *ANIMATIONKEY.findAnimation("baRightMove");
				anim->start();
			}
		}
	}
	break;
	case LEFT_ATTACK:
	{
		DieEnemy();

		shotTime += TIMEMANAGER.getElapsedTime();

		if (shotTime > 0.8)
		{
			if (!shot)
			{
				BULLET.Shot("블랙아처화살", posX, posY, PI, 0, 9, 1);
				shot = true;
			}
		}
		if (!anim->isPlay())
		{
			//총알발사
			attackTime += TIMEMANAGER.getElapsedTime();

			if (attackTime > 1.3)
			{
				if (!anim->isPlay())
				{
					if (pm->GetPlayer1()->GetX() < posX)
					{
						eState = LEFT_MOVE;
						*anim = *ANIMATIONKEY.findAnimation("baLeftMove");
						anim->start();
					}
					else
					{
						eState = RIGHT_MOVE;
						*anim = *ANIMATIONKEY.findAnimation("baRightMove");
						anim->start();
					}
					attackTime = 0;
					shotTime = 0;
					shot = false;
				}
			}
		}
	}
	break;
	case RIGHT_ATTACK:
	{
		DieEnemy();

		shotTime += TIMEMANAGER.getElapsedTime();

		if (shotTime > 0.8)
		{
			if (!shot)
			{
				BULLET.Shot("블랙아처화살", posX, posY, 0, 0, 9, 0);
				shot = true;
			}
		}

		if (!anim->isPlay())
		{
			//총알발사
			attackTime += TIMEMANAGER.getElapsedTime();

			if (attackTime > 1.3)
			{
				if (pm->GetPlayer1()->GetX() < posX)
				{
					eState = LEFT_MOVE;
					*anim = *ANIMATIONKEY.findAnimation("baLeftMove");
					anim->start();
				}
				else
				{
					eState = RIGHT_MOVE;
					*anim = *ANIMATIONKEY.findAnimation("baRightMove");
					anim->start();
				}
				attackTime = 0;
				shotTime = 0;
				shot = false;
			}
		}
	}
	break;
	case LEFT_MOVE:
	{
		DieEnemy();
		if (getDistance(pm->GetPlayer1()->GetX(), pm->GetPlayer1()->GetY(), posX, posY) > 300)
		{
			posX += cosf(PI) * 2;
			rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
			shadowRc = RectMake(rc.right - 80, rc.bottom - img->GetFreamHeight() / 3 + 15, 40, img->GetFreamHeight() / 3);

			if (pm->GetPlayer1()->GetX() + 400 > posX)
			{
				eState = LEFT_ATTACK;
				*anim = *ANIMATIONKEY.findAnimation("baLeftAttack");
				anim->start();
			}
		}
		else
		{
			posX += cosf(0) * 2;
			rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
			shadowRc = RectMake(rc.right - 80, rc.bottom - img->GetFreamHeight() / 3 + 15, 40, img->GetFreamHeight() / 3);
			//몆초뒤에공격하게

			attackTime2 += TIMEMANAGER.getElapsedTime();
			if (attackTime2 > 1)
			{
				attackTime2 = 0;
				eState = LEFT_ATTACK;
				*anim = *ANIMATIONKEY.findAnimation("baLeftAttack");
				anim->start();
			}
		}
	}
	break;
	case RIGHT_MOVE:
	{
		DieEnemy();
		if (getDistance(pm->GetPlayer1()->GetX(), pm->GetPlayer1()->GetY(), posX, posY) > 300)
		{
			posX += cosf(0) * 2;
			rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
			shadowRc = RectMake(rc.right - 80, rc.bottom - img->GetFreamHeight() / 3 + 15, 40, img->GetFreamHeight() / 3);

			if (pm->GetPlayer1()->GetX() - 400 < posX)
			{
				eState = RIGHT_ATTACK;
				*anim = *ANIMATIONKEY.findAnimation("baRightAttack");
				anim->start();
			}
		}
		else
		{
			posX += cosf(PI) * 2;
			rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
			shadowRc = RectMake(rc.right - 80, rc.bottom - img->GetFreamHeight() / 3 + 15, 40, img->GetFreamHeight() / 3);

			attackTime2 += TIMEMANAGER.getElapsedTime();
			if (attackTime2 > 1)
			{
				attackTime2 = 0;
				eState = RIGHT_ATTACK;
				*anim = *ANIMATIONKEY.findAnimation("baRightAttack");
				anim->start();
			}
		}
	}
	break;
	case LEFT_DIE:
	{
		gravity += 0.5f;
		posX += cosf(3 / PI) * 8;
		posY += -sinf(3 / PI) * 8 + gravity;
		rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
		shadowRc = RectMake(rc.right - img->GetFrameWidth(), rc.bottom - img->GetFreamHeight() / 3 + 15, img->GetFrameWidth(), img->GetFreamHeight() / 3);

		if (posY > initPosY)
		{
			gravity = 0;
			eState = END;
		}
	}
	break;
	case RIGHT_DIE:
	{
		gravity += 0.5f;
		posX += cosf(PI - 3 / PI) * 8;
		posY += -sinf(PI - 3 / PI) * 8 + gravity;
		rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
		shadowRc = RectMake(rc.right - img->GetFrameWidth(), rc.bottom - img->GetFreamHeight() / 3 + 15, img->GetFrameWidth(), img->GetFreamHeight() / 3);

		if (posY > initPosY)
		{
			gravity = 0;
			eState = END;
		}
	}
	break;
	case END:
	{
		dieTime += TIMEMANAGER.getElapsedTime();

		alpha += getAlpha;
		if (alpha > 150 || alpha<1)
			getAlpha *= -1;

		if (dieTime > 1.5)
		{
			isDie = true;
			isShow = false;
			dieTime = 0;
		}
	}
	break;
	}
}

void BlackArchor::DieEnemy()
{
	if (hp <= 0)
	{
		initPosY = posY;

		if (eState == LEFT_IDLE || eState == LEFT_ATTACK || eState == LEFT_MOVE)
		{
			eState = LEFT_DIE;
			*anim = *ANIMATIONKEY.findAnimation("baLeftDie");
		}
		else if (eState == RIGHT_IDLE || eState == RIGHT_ATTACK || eState == RIGHT_MOVE)
		{
			eState = RIGHT_DIE;
			*anim = *ANIMATIONKEY.findAnimation("baRightDie");
		}
		anim->start();
	}
}

void BlackArchor::Damaged()
{
	hp--;
}
