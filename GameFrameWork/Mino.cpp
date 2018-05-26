#include "stdafx.h"
#include "Mino.h"


Mino::Mino(ENEMYTYPE _eType)
	:Enemy(_eType)
{
	IMAGEMANAGER.addFrameImage("민호", PathFile("image\\Enemy", "전투소").c_str(), 4180, 320, 22, 2, true, RGB(255, 0, 255));
}


Mino::~Mino()
{
}

HRESULT Mino::Init(int x, int y, ENEMYSTATE eState)
{
	int leftIde[] = { 0 };
	ANIMATIONKEY.addArrayFrameAnimation("moLeftIdle", "민호", leftIde, 1, 2, true);

	int rightIdle[] = { 43 };
	ANIMATIONKEY.addArrayFrameAnimation("moRightIdle", "민호", rightIdle, 1, 2, true);

	int leftMove[] = { 1,2,3,4,5 };
	ANIMATIONKEY.addArrayFrameAnimation("moLeftMove", "민호", leftMove, 5, 6, true);

	int rightMove[] = { 42,41,40,39,38 };
	ANIMATIONKEY.addArrayFrameAnimation("moRightMove", "민호", rightMove, 5, 6, true);

	int leftAttack[] = { 6,7,8,9,10,11,12,6,7 };
	ANIMATIONKEY.addArrayFrameAnimation("moLeftAttack", "민호", leftAttack, 9, 10, false);

	int rightAttack[] = { 37,36,35,34,33,32,31,37,36 };
	ANIMATIONKEY.addArrayFrameAnimation("moRightAttack", "민호", rightAttack, 9, 10, false);

	int leftAttack2[] = { 16,17,18 };
	ANIMATIONKEY.addArrayFrameAnimation("moLeftAttack2", "민호", leftAttack2, 3, 8, true);

	int rightAttack2[] = { 25,26,27 };
	ANIMATIONKEY.addArrayFrameAnimation("moRightAttack2", "민호", rightAttack2, 3, 8, true);

	int leftDamage[] = { 13,14,15 };
	ANIMATIONKEY.addArrayFrameAnimation("moLeftDamage", "민호", leftDamage, 3, 6, false);

	int leftDamage2[] = { 14,15 };
	ANIMATIONKEY.addArrayFrameAnimation("moLeftDamage2", "민호", leftDamage2, 2, 6, true);

	int rightDamage[] = { 30,29,28 };
	ANIMATIONKEY.addArrayFrameAnimation("moRightDamage", "민호", rightDamage, 3, 6, false);

	int rightDamage2[] = { 29,28 };
	ANIMATIONKEY.addArrayFrameAnimation("moRightDamage2", "민호", rightDamage2, 2, 6, true);

	int leftDie[] = { 19,20,21 };
	ANIMATIONKEY.addArrayFrameAnimation("moLeftDie", "민호", leftDie, 3, 4, false);

	int rightDie[] = { 24,23,22 };
	ANIMATIONKEY.addArrayFrameAnimation("moRightDie", "민호", rightDie, 3, 4, false);

	img = IMAGEMANAGER.findImage("민호");
	Enemy::Init(x, y, eState);
	anim = new animation;

	if (eState == LEFT_IDLE)
		*anim = *ANIMATIONKEY.findAnimation("moLeftIdle");
	else if (eState == RIGHT_IDLE)
		*anim = *ANIMATIONKEY.findAnimation("moRightIdle");
	anim->start();

	isAttack = false;
	isAttack2 = false;
	atkWaitTime = 0;
	attack1Time = 0;
	damagedTime = 0;
	totalPower = 0;
	Friction = 0;
	getAlpha = 15;
	gravity = 0;
	dieTime = 0;
	hp = 20;
	rndValue = 0;
	attackSoundTime = 0;

	return S_OK;
}

void Mino::Release()
{
}

void Mino::EnemyUpdate(PlayerManager * pm)
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
			*anim = *ANIMATIONKEY.findAnimation("moLeftMove");
			anim->start();
		}
	}
	break;
	case RIGHT_IDLE:
	{

	}
	break;
	case LEFT_MOVE:
	{
		if (!isAttack)
		{
			angle = getAngle(GetCenterPos(shadowRc).x, GetCenterPos(shadowRc).y,
				GetCenterPos(pm->GetPlayer1()->getRc()).x, GetCenterPos(pm->GetPlayer1()->getRc()).y);

			posX += cosf(angle) * 2;
			posY += -sinf(angle) * 2;
			rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
			shadowRc = RectMake(rc.right - 130, rc.bottom - img->GetFreamHeight() / 3 + 15, 60, img->GetFreamHeight() / 3);
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
			atkWaitTime += TIMEMANAGER.getElapsedTime();
			if (atkWaitTime > 0.5)
			{
				SOUNDMANAGER.play("33MinoAxe");
				rndValue = RND.GetFromTo(0, 10);
				atkWaitTime = 0;
				isAttack = false;
				eState = LEFT_ATTACK;
				*anim = *ANIMATIONKEY.findAnimation("moLeftAttack");
				anim->start();
				BULLET.Shot("민호검", posX , posY+20, 0, 0, 0, 0);
			}
		}
		DieEnemy();
	}
	break;
	case RIGHT_MOVE:
	{
		if (!isAttack)
		{
			angle = getAngle(GetCenterPos(shadowRc).x, GetCenterPos(shadowRc).y,
				GetCenterPos(pm->GetPlayer1()->getRc()).x, GetCenterPos(pm->GetPlayer1()->getRc()).y);

			posX += cosf(angle) * 2;
			posY += -sinf(angle) * 2;
			rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
			shadowRc = RectMake(rc.right - 130, rc.bottom - img->GetFreamHeight() / 3 + 15, 60, img->GetFreamHeight() / 3);
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
			atkWaitTime += TIMEMANAGER.getElapsedTime();
			if (atkWaitTime > 0.5)
			{
				SOUNDMANAGER.play("33MinoAxe");
				rndValue = RND.GetFromTo(0, 10);
				atkWaitTime = 0;
				isAttack = false;
				eState = RIGHT_ATTACK;
				*anim = *ANIMATIONKEY.findAnimation("moRightAttack");
				anim->start();
				BULLET.Shot("민호검", posX, posY+20,0,0,0,0);
			}
		}
		DieEnemy();
	}
	break;
	case LEFT_ATTACK:
	{
		attackSoundTime += TIMEMANAGER.getElapsedTime();
		if (attackSoundTime >= 0.5f)
		{
			attackSoundTime = 0;
			SOUNDMANAGER.play("33MinoAxe");
		}
		if (!anim->isPlay())
		{
			attackSoundTime = 0;
			for (int i = 0; i < BULLET.GetBulletVec("민호검").size(); i++)
				BULLET.Destroy("민호검", i);
			if (hp >= 11)
			{
				attack1Time += TIMEMANAGER.getElapsedTime();
				if (attack1Time > 1)
				{
					attack1Time = 0;
					//플레이어가 왼쪽에있으면
					if (pm->GetPlayer1()->GetX() < posX)
					{
						eState = LEFT_MOVE;
						*anim = *ANIMATIONKEY.findAnimation("moLeftMove");
						anim->start();
					}
					else//플레이어가 오른쪽에 있으면
					{
						eState = RIGHT_MOVE;
						*anim = *ANIMATIONKEY.findAnimation("moRightMove");
						anim->start();
					}
				}
			}
			else
			{
				attack1Time += TIMEMANAGER.getElapsedTime();
				if (attack1Time > 1)
				{
					attack1Time = 0;
					if (rndValue < 7)
					{
						eState = LEFT_ATTACK2;
						*anim = *ANIMATIONKEY.findAnimation("moLeftMove");
						anim->start();
						rndValue = 0;
					}
					else
					{
						//플레이어가 왼쪽에있으면
						if (pm->GetPlayer1()->GetX() < posX)
						{
							eState = LEFT_MOVE;
							*anim = *ANIMATIONKEY.findAnimation("moLeftMove");
							anim->start();
							rndValue = 0;
						}
						else//플레이어가 오른쪽에 있으면
						{
							eState = RIGHT_MOVE;
							*anim = *ANIMATIONKEY.findAnimation("moRightMove");
							anim->start();
							rndValue = 0;
						}
					}
				}
			}
		}
		DieEnemy();
	}
	break;
	case RIGHT_ATTACK:
	{
		attackSoundTime += TIMEMANAGER.getElapsedTime();
		if (attackSoundTime >= 0.5f)
		{
			attackSoundTime = 0;
			SOUNDMANAGER.play("33MinoAxe");
		}
		for (int i = 0; i < BULLET.GetBulletVec("민호검").size(); i++)
			BULLET.Destroy("민호검", i);
		if (!anim->isPlay())
		{
			attackSoundTime = 0;
			if (hp >= 11)
			{
				attack1Time += TIMEMANAGER.getElapsedTime();
				if (attack1Time > 1)
				{
					attack1Time = 0;
					//플레이어가 왼쪽에있으면
					if (pm->GetPlayer1()->GetX() < posX)
					{
						eState = LEFT_MOVE;
						*anim = *ANIMATIONKEY.findAnimation("moLeftMove");
						anim->start();
					}
					else//플레이어가 오른쪽에 있으면
					{
						eState = RIGHT_MOVE;
						*anim = *ANIMATIONKEY.findAnimation("moRightMove");
						anim->start();
					}
				}
			}
			else
			{
				attack1Time += TIMEMANAGER.getElapsedTime();
				if (attack1Time > 1)
				{
					attack1Time = 0;
					if (rndValue < 7)
					{
						eState = RIGHT_ATTACK2;
						*anim = *ANIMATIONKEY.findAnimation("moRightMove");
						anim->start();
						rndValue = 0;
					}
					else
					{
						//플레이어가 왼쪽에있으면
						if (pm->GetPlayer1()->GetX() < posX)
						{
							eState = LEFT_MOVE;
							*anim = *ANIMATIONKEY.findAnimation("moLeftMove");
							anim->start();
							rndValue = 0;
						}
						else//플레이어가 오른쪽에 있으면
						{
							eState = RIGHT_MOVE;
							*anim = *ANIMATIONKEY.findAnimation("moRightMove");
							anim->start();
							rndValue = 0;
						}
					}
				}
			}
		}
		DieEnemy();
	}
	break;
	case LEFT_ATTACK2:
	{
		if (!isAttack2)
		{
			if (CAM.GetRC().right - 50 > posX)
			{
				posX += 5;
				rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
				shadowRc = RectMake(rc.right - 80, rc.bottom - img->GetFreamHeight() / 3 + 15, 40, img->GetFreamHeight() / 3);
			}
			else
			{
				SOUNDMANAGER.play("35MinoHead");
				isAttack2 = true;
				*anim = *ANIMATIONKEY.findAnimation("moLeftAttack2");
			}
		}
		else
		{
			atkWaitTime += TIMEMANAGER.getElapsedTime();
			if (atkWaitTime > 0.8)
			{
				if(!anim->isPlay())
					anim->start();
				
				posX += cosf(angle) * 7;
				posY += -sinf(angle) * 7;
				rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
				shadowRc = RectMake(rc.right - 80, rc.bottom - img->GetFreamHeight() / 3 + 15, 40, img->GetFreamHeight() / 3);
				shadowColRc = RectMakeCenter(posX, posY + 40, img->GetFrameWidth(), img->GetFreamHeight() / 3);

				if (CAM.GetRC().left + 50 > posX||posY<200||posY>350)
				{
					eState = RIGHT_MOVE;
					*anim = *ANIMATIONKEY.findAnimation("moRightMove");
					anim->start();
					atkWaitTime = 0;
					isAttack2 = false;
					shadowColRc = RectMake(0, 0, 0, 0);
				}
			}
			else
				angle = getAngle(GetCenterPos(shadowRc).x, GetCenterPos(shadowRc).y, GetCenterPos(pm->GetPlayer1()->getRc()).x, GetCenterPos(pm->GetPlayer1()->getRc()).y);
		
		}
		
	}
	break;
	case RIGHT_ATTACK2:
	{
		if (!isAttack2)
		{
			if (CAM.GetRC().left + 50 < posX)
			{
				posX -= 5;
				rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
				shadowRc = RectMake(rc.right - 80, rc.bottom - img->GetFreamHeight() / 3 + 15, 40, img->GetFreamHeight() / 3);
			}
			else
			{
				SOUNDMANAGER.play("35MinoHead");
				isAttack2 = true;
				*anim = *ANIMATIONKEY.findAnimation("moRightAttack2");
			}
		}
		else
		{
			atkWaitTime += TIMEMANAGER.getElapsedTime();
			if (atkWaitTime > 0.8)
			{
				if (!anim->isPlay())
					anim->start();

				posX += cosf(angle) * 7;
				posY += -sinf(angle) * 7;
				rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
				shadowRc = RectMake(rc.right - 80, rc.bottom - img->GetFreamHeight() / 3 + 15, 40, img->GetFreamHeight() / 3);
				shadowColRc = RectMakeCenter(posX, posY + 30, img->GetFrameWidth(), img->GetFreamHeight() / 3);

				if (CAM.GetRC().right - 50 < posX || posY<200 || posY>350)
				{
					eState = LEFT_MOVE;
					*anim = *ANIMATIONKEY.findAnimation("moLeftMove");
					anim->start();
					atkWaitTime = 0;
					isAttack2 = false;
					shadowColRc = RectMake(0, 0, 0, 0);
				}
			}
			else
				angle = getAngle(GetCenterPos(shadowRc).x, GetCenterPos(shadowRc).y, GetCenterPos(pm->GetPlayer1()->getRc()).x, GetCenterPos(pm->GetPlayer1()->getRc()).y);

		}

	}
	break;
	case LEFT_DAMAGE:
	{
		if (Friction*(-1) < totalPower)
		{
			Friction -= 0.2;
			posX += cosf(0) * 6 + Friction;
			posY += -sinf(0) * 6;
			rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
			shadowRc = RectMake(rc.right - 80, rc.bottom - img->GetFreamHeight() / 3 + 15, 40, img->GetFreamHeight() / 3);
		}
		if (!anim->isPlay())
		{
			*anim = *ANIMATIONKEY.findAnimation("moLeftDamage2");
			anim->start();
		}
		damagedTime += TIMEMANAGER.getElapsedTime();
		if (damagedTime > 2)
		{
			totalPower = 0;
			Friction = 0;
			damagedTime = 0;
			if (pm->GetPlayer1()->GetX() < posX)
			{
				eState = LEFT_MOVE;
				*anim = *ANIMATIONKEY.findAnimation("moLeftMove");
				anim->start();
			}
			else//플레이어가 오른쪽에 있으면
			{
				eState = RIGHT_MOVE;
				*anim = *ANIMATIONKEY.findAnimation("moRightMove");
				anim->start();
			}
		}
	}
	break;
	case RIGHT_DAMAGE:
	{
		if (Friction*(-1) > totalPower)
		{
			Friction += 0.2;
			posX += cosf(PI) * 6 + Friction;
			posY += -sinf(PI) * 6;
			rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
			shadowRc = RectMake(rc.right - 80, rc.bottom - img->GetFreamHeight() / 3 + 15, 40, img->GetFreamHeight() / 3);
		}
		if (!anim->isPlay())
		{
			*anim = *ANIMATIONKEY.findAnimation("moRightDamage2");
			anim->start();
		}
		damagedTime += TIMEMANAGER.getElapsedTime();
		if (damagedTime > 2)
		{
			totalPower = 0;
			Friction = 0;
			damagedTime = 0;
			if (pm->GetPlayer1()->GetX() < posX)
			{
				eState = LEFT_MOVE;
				*anim = *ANIMATIONKEY.findAnimation("moLeftMove");
				anim->start();
			}
			else//플레이어가 오른쪽에 있으면
			{
				eState = RIGHT_MOVE;
				*anim = *ANIMATIONKEY.findAnimation("moRightMove");
				anim->start();
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
		posX += cosf(PI - 3 / PI) * 10;
		posY += -sinf(PI - 3 / PI) * 10 + gravity;
		rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
		shadowRc = RectMake(rc.right - 80, rc.bottom - img->GetFreamHeight() / 3 + 15, 40, img->GetFreamHeight() / 3);

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

		if (dieTime > 2.5)
		{
			isDie = true;
			isShow = false;
		}
	}
	break;
	}
}

void Mino::DieEnemy()
{
	if (hp <= 0)
	{
		SOUNDMANAGER.play("32MinoDie");
		initPosY = posY;

		if (eState == LEFT_IDLE || eState == LEFT_ATTACK || eState == LEFT_MOVE)
		{
			eState = LEFT_DIE;
			*anim = *ANIMATIONKEY.findAnimation("moLeftDie");
		}
		else if (eState == RIGHT_IDLE || eState == RIGHT_ATTACK || eState == RIGHT_MOVE)
		{
			eState = RIGHT_DIE;
			*anim = *ANIMATIONKEY.findAnimation("moRightDie");
		}
		anim->start();
	}
}

void Mino::Damaged()
{
	if (eState != LEFT_ATTACK2&&eState != RIGHT_ATTACK2
		&&eState != LEFT_DAMAGE&&eState != RIGHT_DAMAGE)
		hp--;
	if (hp % 4 == 0 && hp != 0)
	{
		SOUNDMANAGER.play("34MinoDeezy");
		if (eState == LEFT_IDLE || eState == LEFT_MOVE || eState == LEFT_ATTACK)
		{
			eState = LEFT_DAMAGE;
			*anim = *ANIMATIONKEY.findAnimation("moLeftDamage");
			anim->start();
			totalPower = cosf(0) * 6;
		}
		else if (eState == RIGHT_IDLE || eState == RIGHT_MOVE || eState == RIGHT_ATTACK)
		{
			eState = RIGHT_DAMAGE;
			*anim = *ANIMATIONKEY.findAnimation("moRightDamage");
			anim->start();
			totalPower = cosf(PI) * 6;
		}
	}
}
