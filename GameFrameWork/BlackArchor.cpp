#include "stdafx.h"
#include "BlackArchor.h"


BlackArchor::BlackArchor(ENEMYTYPE _eType)
	:Enemy(_eType)
{
	IMAGEMANAGER.addFrameImage("블랙아처", PathFile("image\\Enemy", "블랙아처").c_str(), 1373, 220, 14, 2, true, RGB(255, 0, 255));
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

	int leftMove[] = {27,26,24};
	ANIMATIONKEY.addArrayFrameAnimation("baLeftMove", "블랙아처", leftMove, 3, 7, true);

	int rightMove[] = { 0,1,3 };
	ANIMATIONKEY.addArrayFrameAnimation("baRightMove", "블랙아처", rightMove, 3, 7, true);

	int leftAttack[] = { 22,21,20,19,18 };
	ANIMATIONKEY.addArrayFrameAnimation("baLeftAttack", "블랙아처", leftAttack, 5, 4, false);

	int rightAttack[] = {5,6,7,8,9};
	ANIMATIONKEY.addArrayFrameAnimation("baRightAttack", "블랙아처", rightAttack, 5, 7, false);

	int leftDie[] = {16,15,14};
	ANIMATIONKEY.addArrayFrameAnimation("baLeftDie", "블랙아처", rightAttack, 3, 7, false);
	
	int rightDie[] = {11,12,13};
	ANIMATIONKEY.addArrayFrameAnimation("baRightDie", "블랙아처", rightAttack, 3, 7, false);

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
					}
				}
			}
		}
		break;
		case RIGHT_ATTACK:
		{
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
				}
			}
		}
		break;
		case LEFT_MOVE:
		{
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
			}
		}
		break;
		case RIGHT_MOVE:
		{
			if (getDistance(pm->GetPlayer1()->GetX(), pm->GetPlayer1()->GetY(), posX, posY) > 300)
			{
				posX += cosf(0) * 2;
				rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
				shadowRc = RectMake(rc.right - 80, rc.bottom - img->GetFreamHeight() / 3 + 15, 40, img->GetFreamHeight() / 3);

				if (pm->GetPlayer1()->GetX() + 400 > posX)
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
			}
		}
		break;
		case LEFT_DIE:
		{

		}
		break;
		case RIGHT_DIE:
		{

		}
		break;
		case END:
		{

		}
		break;
	}
}

void BlackArchor::DieEnemy()
{
}

void BlackArchor::Damaged()
{
}
