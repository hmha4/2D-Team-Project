#include "stdafx.h"
#include "Cyclopes.h"


Cyclopes::Cyclopes(ENEMYTYPE _eType)
	:Enemy(_eType)
{
	IMAGEMANAGER.addFrameImage("외눈거인", PathFile("image\\Enemy", "외눈거인").c_str(), 1617, 720, 11, 4, true, RGB(255, 0, 255));
}


Cyclopes::~Cyclopes()
{
}

HRESULT Cyclopes::Init(int x, int y, ENEMYSTATE eState)
{
	int leftIde[] = { 6 };
	ANIMATIONKEY.addArrayFrameAnimation("ccLeftIdle", "외눈거인", leftIde, 1, 2, false);

	int rightIdle[] = { 25 };
	ANIMATIONKEY.addArrayFrameAnimation("ccRightIdle", "외눈거인", rightIdle, 1, 2, false);

	int leftMove[] = {0, 1,2,3,4,5 };
	ANIMATIONKEY.addArrayFrameAnimation("ccLeftMove", "외눈거인", leftMove, 6, 6, true);

	int rightMove[] = { 31,30,29,28,27,26 };
	ANIMATIONKEY.addArrayFrameAnimation("ccRightMove", "외눈거인", rightMove, 6, 6, true);

	int leftAttack[] = { 6,7,8,9 };
	ANIMATIONKEY.addArrayFrameAnimation("ccLeftAttack", "외눈거인", leftAttack, 4, 10, false);

	int rightAttack[] = { 25,24,23,22 };
	ANIMATIONKEY.addArrayFrameAnimation("ccRightAttack", "외눈거인", rightAttack, 4, 10, false);

	int leftAttack2[] = { 14,16,18,19,20,21 };
	ANIMATIONKEY.addArrayFrameAnimation("ccLeftAttack2", "외눈거인", leftAttack2, 6, 8, false);

	int rightAttack2[] = { 40,38,36,35,34,33 };
	ANIMATIONKEY.addArrayFrameAnimation("ccRightAttack2", "외눈거인", rightAttack2, 6, 8, false);

	int leftDie[] = { 11,12,13 };
	ANIMATIONKEY.addArrayFrameAnimation("ccLeftDie", "외눈거인", leftDie, 3, 4, false);

	int rightDie[] = { 43,42,41 };
	ANIMATIONKEY.addArrayFrameAnimation("ccRightDie", "외눈거인", rightDie, 3, 4, false);

	img = IMAGEMANAGER.findImage("외눈거인");
	Enemy::Init(x, y, eState);
	anim = new animation;

	if (eState == LEFT_IDLE)
		*anim = *ANIMATIONKEY.findAnimation("ccLeftIdle");
	else if (eState == RIGHT_IDLE)
		*anim = *ANIMATIONKEY.findAnimation("ccRightIdle");
	anim->start();

	isAttack = false;
	isShot = false;
	atkWaitTime = 0;
	attack1Time = 0;
	gravity = 0;
	hp = 25;
	idx = 0;
	
	attack[0] = 1;
	attack[1] = 0;
	attack[2] = 1;
	attack[3] = 0;
	dieTime = 0;
	getAlpha = 15;
	return S_OK;
}

void Cyclopes::Release()
{
}

void Cyclopes::EnemyUpdate(PlayerManager * pm)
{
	anim->frameUpdate(TIMEMANAGER.getElapsedTime());

	switch (eState)
	{
		case LEFT_IDLE:
		{
			if (getDistance(pm->GetPlayer1()->GetX(), pm->GetPlayer1()->GetY(),
				posX, posY) < 300)
			{
				eState = LEFT_MOVE;
				*anim = *ANIMATIONKEY.findAnimation("ccLeftMove");
				anim->start();
			}
			
		}
		break;
		case RIGHT_IDLE:
		{

		}
		break;
		case LEFT_ATTACK:
		{
			DieEnemy();
			if (!anim->isPlay())
			{
				for (int i = 0; i < BULLET.GetBulletVec("민호검").size(); i++)
					BULLET.Destroy("민호검", i);
				attack1Time += TIMEMANAGER.getElapsedTime();
				if (attack1Time > 1)
				{
					attack1Time = 0;
					//플레이어가 왼쪽에있으면
					if (pm->GetPlayer1()->GetX() < posX)
					{
						eState = LEFT_MOVE;
						*anim = *ANIMATIONKEY.findAnimation("ccLeftMove");
						anim->start();
					}
					else//플레이어가 오른쪽에 있으면
					{
						eState = RIGHT_MOVE;
						*anim = *ANIMATIONKEY.findAnimation("ccRightMove");
						anim->start();
					}
				}
			}
		}
		break;
		case RIGHT_ATTACK:
		{
			DieEnemy();
			if (!anim->isPlay())
			{
				for (int i = 0; i < BULLET.GetBulletVec("민호검").size(); i++)
					BULLET.Destroy("민호검", i);
				attack1Time += TIMEMANAGER.getElapsedTime();
				if (attack1Time > 1)
				{
					attack1Time = 0;
					//플레이어가 왼쪽에있으면
					if (pm->GetPlayer1()->GetX() < posX)
					{
						eState = LEFT_MOVE;
						*anim = *ANIMATIONKEY.findAnimation("ccLeftMove");
						anim->start();
					}
					else//플레이어가 오른쪽에 있으면
					{
						eState = RIGHT_MOVE;
						*anim = *ANIMATIONKEY.findAnimation("ccRightMove");
						anim->start();
					}
				}
			}
		}
		break;
		case LEFT_ATTACK2:
		{
			DieEnemy();
			if (posY < initY+5)
			{
				gravity += 0.2f;

				posX += cosf(PI / 3) * 7;
				posY += -sinf(PI / 3) * 7 + gravity;
				rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
				shadowRc = RectMake(rc.right - 100, rc.bottom - img->GetFreamHeight() / 3 + 15, 60, img->GetFreamHeight() / 3);
			}

			if (!anim->isPlay())
			{
				if (!isShot)
				{
					BULLET.Shot("외돌", posX, posY, PI, 0.2, 8, 0,posY+90);
					BULLET.Shot("외돌", posX, posY, PI, 0.2, 5, 0, posY+45);
					BULLET.Shot("외돌", posX, posY, PI-PI/12, 0.2, 8, 0,posY);
					isShot = true;
				}
				//플레이어가 왼쪽에있으면
				attack1Time += TIMEMANAGER.getElapsedTime();
				if (attack1Time > 1)
				{
					attack1Time = 0;
					//플레이어가 왼쪽에있으면
					if (pm->GetPlayer1()->GetX() < posX)
					{
						eState = LEFT_MOVE;
						*anim = *ANIMATIONKEY.findAnimation("ccLeftMove");
						anim->start();
					}
					else//플레이어가 오른쪽에 있으면
					{
						eState = RIGHT_MOVE;
						*anim = *ANIMATIONKEY.findAnimation("ccRightMove");
						anim->start();
					}
					gravity = 0;
					isShot = false;
				}
			}
		}
		break;
		case RIGHT_ATTACK2:
		{
			DieEnemy();
			if (posY < initY + 5)
			{
				gravity += 0.2f;

				posX += cosf(PI-PI / 3) * 7;
				posY += -sinf(PI-PI / 3) * 7 + gravity;
				rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
				shadowRc = RectMake(rc.right - 100, rc.bottom - img->GetFreamHeight() / 3 + 15, 60, img->GetFreamHeight() / 3);
			}

			if (!anim->isPlay())
			{
				if (!isShot)
				{
					BULLET.Shot("외돌", posX, posY, 0, 0.2, 8, 0,posY + 90);
					BULLET.Shot("외돌", posX, posY, 0, 0.2, 5, 0,posY + 45);
					BULLET.Shot("외돌", posX, posY, PI / 12, 0.2, 8, 0,posY);
					isShot = true;
				}
				//플레이어가 왼쪽에있으면
				attack1Time += TIMEMANAGER.getElapsedTime();
				if (attack1Time > 1)
				{
					attack1Time = 0;
					//플레이어가 왼쪽에있으면
					if (pm->GetPlayer1()->GetX() < posX)
					{
						eState = LEFT_MOVE;
						*anim = *ANIMATIONKEY.findAnimation("ccLeftMove");
						anim->start();
					}
					else//플레이어가 오른쪽에 있으면
					{
						eState = RIGHT_MOVE;
						*anim = *ANIMATIONKEY.findAnimation("ccRightMove");
						anim->start();
					}
					gravity = 0;
					isShot = false;
				}
			}
		}
		break;
		case LEFT_MOVE:
		{
			DieEnemy();
			if (!isAttack)
			{
				angle = getAngle(GetCenterPos(shadowRc).x, GetCenterPos(shadowRc).y,
					GetCenterPos(pm->GetPlayer1()->getRc()).x, GetCenterPos(pm->GetPlayer1()->getRc()).y);

				posX += cosf(angle) * 2;
				posY += -sinf(angle) * 2;
				rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
				shadowRc = RectMake(rc.right - 100, rc.bottom - img->GetFreamHeight() / 3 + 15, 60, img->GetFreamHeight() / 3);
			}

			RECT temp;
			RECT temp2 = RectMakeCenter(GetCenterPos(shadowRc).x, GetCenterPos(shadowRc).y, 80, 10);
			if (IntersectRect(&temp, &temp2, &pm->GetPlayer1()->getRc()))
			{
				isAttack = true;
				anim->stop();
			}

			if (isAttack)
			{
				switch (state)
				{
					case 0:
					{
						atkWaitTime += TIMEMANAGER.getElapsedTime();
						if (atkWaitTime > 0.5)
						{
							SOUNDMANAGER.play("47CyclopseAttack");
							atkWaitTime = 0;
							isAttack = false;
							eState = LEFT_ATTACK;
							*anim = *ANIMATIONKEY.findAnimation("ccLeftAttack");
							anim->start();
							BULLET.Shot("민호검", posX, posY+20, 0, 0, 0, 0);
						}
					}
					break;
					case 1:
					{
						if (attack[idx] == 0)
						{
							atkWaitTime += TIMEMANAGER.getElapsedTime();
							if (atkWaitTime > 0.5)
							{
								SOUNDMANAGER.play("47CyclopseAttack");
								atkWaitTime = 0;
								isAttack = false;
								eState = LEFT_ATTACK;
								*anim = *ANIMATIONKEY.findAnimation("ccLeftAttack");
								anim->start();
								BULLET.Shot("민호검", posX, posY+20, 0, 0, 0, 0);
								idx++;
								if (idx > 3)
									idx = 0;
							}
						}
						else
						{
							SOUNDMANAGER.play("46Cyclopse");
							initY = posY;
							isAttack = false;
							eState = LEFT_ATTACK2;
							*anim = *ANIMATIONKEY.findAnimation("ccLeftAttack2");
							anim->start();
							idx++;
							if (idx > 3)
								idx = 0;
						}
					}
					break;
				}
			}
		}
		break;
		case RIGHT_MOVE:
		{
			DieEnemy();
			if (!isAttack)
			{
				angle = getAngle(GetCenterPos(shadowRc).x, GetCenterPos(shadowRc).y,
					GetCenterPos(pm->GetPlayer1()->getRc()).x, GetCenterPos(pm->GetPlayer1()->getRc()).y);

				posX += cosf(angle) * 2;
				posY += -sinf(angle) * 2;
				rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
				shadowRc = RectMake(rc.right - 100, rc.bottom - img->GetFreamHeight() / 3 + 15, 60, img->GetFreamHeight() / 3);
			}

			RECT temp;
			RECT temp2 = RectMakeCenter(GetCenterPos(shadowRc).x, GetCenterPos(shadowRc).y, 80, 10);
			if (IntersectRect(&temp, &temp2, &pm->GetPlayer1()->getRc()))
			{
				isAttack = true;
				anim->stop();
			}

			if (isAttack)
			{
				switch (state)
				{
				case 0:
				{
					atkWaitTime += TIMEMANAGER.getElapsedTime();
					if (atkWaitTime > 0.5)
					{
						SOUNDMANAGER.play("47CyclopseAttack");
						atkWaitTime = 0;
						isAttack = false;
						eState = RIGHT_ATTACK;
						*anim = *ANIMATIONKEY.findAnimation("ccRightAttack");
						anim->start();
						BULLET.Shot("민호검", posX, posY + 20, 0, 0, 0, 0);
						idx++;
						if (idx > 3)
							idx = 0;
					}
				}
				break;
				case 1:
				{
					if (attack[idx]==0)
					{
						atkWaitTime += TIMEMANAGER.getElapsedTime();
						if (atkWaitTime > 0.5)
						{
							SOUNDMANAGER.play("47CyclopseAttack");
							atkWaitTime = 0;
							isAttack = false;
							eState = RIGHT_ATTACK;
							*anim = *ANIMATIONKEY.findAnimation("ccRightAttack");
							anim->start();
							BULLET.Shot("민호검", posX, posY + 20, 0, 0, 0, 0);
							idx++;
							if (idx > 3)
								idx = 0;
						}
					}
					else
					{
						SOUNDMANAGER.play("46Cyclopse");
						initY = posY;
						isAttack = false;
						eState = RIGHT_ATTACK2;
						*anim = *ANIMATIONKEY.findAnimation("ccRightAttack2");
						anim->start();
						idx++;
						if (idx > 3)
							idx = 0;
					}
				}
				break;
				}
			}
		}
		break;
		case LEFT_DIE:
		{
			gravity += 0.5f;
			posX += cosf(3 / PI) * 10;
			posY += -sinf(3 / PI) * 10 + gravity;
			rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
			shadowRc = RectMake(rc.right - 80, rc.bottom - img->GetFreamHeight() / 3 + 15, 40, img->GetFreamHeight() / 3);

			if (posY > initY)
			{
				gravity = 0;
				eState = END;
			}
		}
		break;
		case RIGHT_DIE:
		{
			gravity += 0.5f;
			posX += cosf(PI - 3 / PI) * 10;
			posY += -sinf(PI - 3 / PI) * 10 + gravity;
			rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
			shadowRc = RectMake(rc.right - 80, rc.bottom - img->GetFreamHeight() / 3 + 15, 40, img->GetFreamHeight() / 3);

			if (posY > initY)
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

			if (dieTime > 2.5)
			{
				isDie = true;
				isShow = false;
			}
		}
		break;
	}
}

void Cyclopes::DieEnemy()
{
	if (hp > 18)
		state = 0;
	else
		state = 1;

	if (hp <= 0)
	{
		SOUNDMANAGER.play("46Cyclopse");
		initY = posY;

		if (eState == LEFT_IDLE || eState == LEFT_ATTACK || eState == LEFT_MOVE)
		{
			eState = LEFT_DIE;
			*anim = *ANIMATIONKEY.findAnimation("ccLeftDie");
		}
		else if (eState == RIGHT_IDLE || eState == RIGHT_ATTACK || eState == RIGHT_MOVE)
		{
			eState = RIGHT_DIE;
			*anim = *ANIMATIONKEY.findAnimation("ccRightDie");
		}
		anim->start();
	}
}

void Cyclopes::Damaged()
{
	hp--;
}
