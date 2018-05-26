#include "stdafx.h"
#include "DragonKnight.h"


DragonKnight::DragonKnight(ENEMYTYPE _eType)
	:Enemy(_eType)
{
	IMAGEMANAGER.addFrameImage("용기사", PathFile("image\\Enemy", "용기사").c_str(), 4230, 2100, 10, 14, true, RGB(255, 0, 255));
	EFFECTMANAGER.addEffect("변신", PathFile("image\\Enemy", "식물폭발").c_str(), 1470, 80, 82, 80, 60, 1, 30);
}


DragonKnight::~DragonKnight()
{
}

HRESULT DragonKnight::Init(int x, int y, ENEMYSTATE eState)
{
	int show[]= { 0,1,2,3};
	ANIMATIONKEY.addArrayFrameAnimation("dkShow", "용기사", show, 4,4, false);

	int leftIde[] = { 4 };
	ANIMATIONKEY.addArrayFrameAnimation("dkLeftIdle", "용기사", leftIde, 1, 2, false);

	int rightIdle[] = { 75 };
	ANIMATIONKEY.addArrayFrameAnimation("dkRightIdle", "용기사", rightIdle, 1, 2, false);

	int leftMove[] = { 5,6,7,8,9,10,11};
	ANIMATIONKEY.addArrayFrameAnimation("dkLeftMove", "용기사", leftMove, 7, 9, true);

	int rightMove[] = { 74,73,72,71,70,89,88 };
	ANIMATIONKEY.addArrayFrameAnimation("dkRightMove", "용기사", rightMove, 7, 9, true);

	int leftAttack[] = { 12,13,14,15,16,17,18,19,20,21,22,23 };
	ANIMATIONKEY.addArrayFrameAnimation("dkLeftAttack", "용기사", leftAttack, 12, 10, false);

	int rightAttack[] = {87,86,85,84,83,82,81,80,99,98,97,96 };
	ANIMATIONKEY.addArrayFrameAnimation("dkRightAttack", "용기사", rightAttack, 12, 10, false);

	int leftAttack2[] = { 31,32,33,34,35,36,37,38,39,40,41,42,43};
	ANIMATIONKEY.addArrayFrameAnimation("dkLeftAttack2", "용기사", leftAttack2, 13, 32, true);

	int rightAttack2[] = { 108,107,106,105,104,103,102,101,100,119,118,117,116 };
	ANIMATIONKEY.addArrayFrameAnimation("dkRightAttack2", "용기사", rightAttack2, 13, 32, true);

	int leftAttack3[] = { 56,57,58,59,60 };
	ANIMATIONKEY.addArrayFrameAnimation("dkLeftAttack3", "용기사", leftAttack3, 5, 8, false);

	int rightAttack3[] = {123,122,121,120,139};
	ANIMATIONKEY.addArrayFrameAnimation("dkRightAttack3", "용기사", rightAttack3, 5, 8, false);

	int leftJump[] = {44,45,46,47,48,49,50,51,52,53,54,55};
	ANIMATIONKEY.addArrayFrameAnimation("dkLeftJump", "용기사", leftJump, 12, 20, true);

	int rightJump[] = {115,114,113,112,111,110,129,128,127,126,125,124};
	ANIMATIONKEY.addArrayFrameAnimation("dkRightJump", "용기사", rightJump, 12, 8, true);

	int leftDie[] = { 61,62,63,64,65,66,67,68,69 };
	ANIMATIONKEY.addArrayFrameAnimation("dkLeftDie", "용기사", leftDie, 9, 9, false);

	int leftDie2[] = {68,69};
	ANIMATIONKEY.addArrayFrameAnimation("dkLeftDie2", "용기사", leftDie2, 2, 9, true);

	int rightDie[] = {138,137,136,135,134,133,132,131,130 };
	ANIMATIONKEY.addArrayFrameAnimation("dkRightDie", "용기사", rightDie, 9, 9, false);

	int rightDie2[] = {131,130 };
	ANIMATIONKEY.addArrayFrameAnimation("dkRightDie2", "용기사", rightDie2, 2, 9, true);

	img = IMAGEMANAGER.findImage("용기사");
	Enemy::Init(x, y, eState);
	anim = new animation;

	*anim = *ANIMATIONKEY.findAnimation("dkShow");
	anim->start();

	shadowImg = IMAGEMANAGER.findImage("용기사그림자");
	startTime = 0;
	sState = CHANGE_BEGIN;
	attackTime = 0;
	hp = 30;
	dieTime = 0;
	initPosY = rc.bottom - img->GetFreamHeight() / 3 + 15;
	setShadowY = 0;
	chainAttackSound = false;
	return S_OK;
}

void DragonKnight::Release()
{
}

void DragonKnight::EnemyUpdate(PlayerManager * pm)
{
	UpdateAttackArr();
	anim->frameUpdate(TIMEMANAGER.getElapsedTime());
	switch (eState)
	{
		case LEFT_IDLE:
		{
			switch (sState)
			{
				case CHANGE_BEGIN:
				{
					startTime += TIMEMANAGER.getElapsedTime();

					if (startTime > 2)
					{
						SOUNDMANAGER.play("40DragonKnight");
						EFFECTMANAGER.play("변신", posX + 70, posY+30);
						startTime = 0;
						sState = CHANGE_END;
						*anim = *ANIMATIONKEY.findAnimation("dkLeftIdle");
						anim->start();
					}
				}
				break;
				case CHANGE_END:
				{
					startTime += TIMEMANAGER.getElapsedTime();
					if (startTime > 1)
					{
						startTime = 0;
						eState = LEFT_MOVE;
						*anim = *ANIMATIONKEY.findAnimation("dkLeftMove");
						anim->start();
					}
				}
				break;
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
			static float stime = 0;
			stime += TIMEMANAGER.getElapsedTime();
			
			if (stime > 0.3)
			{
				BULLET.Shot("용기사검0", posX - 80, posY, 0, 0, 0, 0);
				stime = 0;
				if (chainAttackSound)
				{
					SOUNDMANAGER.play("38DragonKnightChain", 0.5f);
					chainAttackSound = false;
				}
			}
			if (!anim->isPlay())
			{
				for (int i = 0; i < BULLET.GetBulletVec("용기사검0").size(); i++)
					BULLET.Destroy("용기사검0", i);
				attackTime += TIMEMANAGER.getElapsedTime();

				if (attackTime > 1)
				{
					if (GetCenterPos(pm->GetPlayer1()->getRc()).x > GetCenterPos(shadowRc).x)
					{
						eState = RIGHT_MOVE;
						*anim = *ANIMATIONKEY.findAnimation("dkRightMove");
						anim->start();
						rc = RectMakeCenter(posX + 150, posY, img->GetFrameWidth(), img->GetFreamHeight());
						shadowRc = RectMake(rc.right - 330, rc.bottom - img->GetFreamHeight() / 3 + 15, 80, img->GetFreamHeight() / 3);
					}
					else
					{
						eState = LEFT_MOVE;
						*anim = *ANIMATIONKEY.findAnimation("dkLeftMove");
						anim->start();
					}
					attackTime = 0;
					stime = 0;
				}
			}
		}
		break;
		case RIGHT_ATTACK:
		{
			DieEnemy();
			static float stime = 0;
			stime += TIMEMANAGER.getElapsedTime();

			if (stime > 0.3)
			{
				BULLET.Shot("용기사검0", posX + 170, posY, 0, 0, 0, 0);
				stime = 0;
				if (chainAttackSound)
				{
					SOUNDMANAGER.play("38DragonKnightChain", 0.5f);
					chainAttackSound = false;
				}
			}

			if (!anim->isPlay())
			{
				for (int i = 0; i < BULLET.GetBulletVec("용기사검0").size(); i++)
					BULLET.Destroy("용기사검0", i);
				attackTime += TIMEMANAGER.getElapsedTime();

				if (attackTime > 1)
				{
					if (GetCenterPos(pm->GetPlayer1()->getRc()).x > GetCenterPos(shadowRc).x)
					{
						eState = RIGHT_MOVE;
						*anim = *ANIMATIONKEY.findAnimation("dkRightMove");
						anim->start();
					}
					else
					{
						eState = LEFT_MOVE;
						*anim = *ANIMATIONKEY.findAnimation("dkLeftMove");
						anim->start();
						rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
						shadowRc = RectMake(rc.right - 180, rc.bottom - img->GetFreamHeight() / 3 + 15, 80, img->GetFreamHeight() / 3);
					}
					attackTime = 0;
					stime = 0;
				}
			}
		}
		break;
		case LEFT_ATTACK2:
		{
			DieEnemy();
			if (CAM.GetRC().right-80 < shadowRc.right)
			{
				attackTime += TIMEMANAGER.getElapsedTime();
				//총알발사
				static float btime = 0;
				btime += TIMEMANAGER.getElapsedTime();
				
				if (btime > 0.3)
				{
					SOUNDMANAGER.play("39DragonKnightKnife", 0.6f);
					BULLET.Shot("용기사검", posX, posY, PI , 0, 5, 0);
					btime = 0;
				}

				if (GetCenterPos(pm->GetPlayer1()->getRc()).y > GetCenterPos(shadowRc).y)
					angle = 3 * PI / 2;
				else
					angle = PI / 2;
				posY += -sinf(angle) * 1;
				rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
				shadowRc = RectMake(rc.right - 180, rc.bottom - img->GetFreamHeight() / 3 + 15, 80, img->GetFreamHeight() / 3);

				if (attackTime > 1.5)
				{
					attackTime = 0;
					btime = 0;
					eState = LEFT_MOVE;
					*anim = *ANIMATIONKEY.findAnimation("dkLeftMove");
					anim->start();
				}
			}
			else
			{
				angle = getAngle(GetCenterPos(shadowRc).x, GetCenterPos(shadowRc).y,
					GetCenterPos(pm->GetPlayer1()->getRc()).x, GetCenterPos(pm->GetPlayer1()->getRc()).y);

				posX -= cosf(angle) * 5;
				posY += -sinf(angle) * 5;
				rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
				shadowRc = RectMake(rc.right - 180, rc.bottom - img->GetFreamHeight() / 3 + 15, 80, img->GetFreamHeight() / 3);
			}
		}
		break;
		case RIGHT_ATTACK2:
		{
			DieEnemy();
			if (CAM.GetRC().left + 80 > shadowRc.left)
			{
				attackTime += TIMEMANAGER.getElapsedTime();
				//총알발사
				static float btime1 = 0;
				btime1 += TIMEMANAGER.getElapsedTime();

				if (btime1 > 0.3)
				{
					SOUNDMANAGER.play("39DragonKnightKnife", 0.6f);
					BULLET.Shot("용기사검", posX, posY, 0, 0, 5, 0);
					btime1 = 0;
				}

				if (GetCenterPos(pm->GetPlayer1()->getRc()).y > GetCenterPos(shadowRc).y)
					angle = 3 * PI / 2;
				else
					angle = PI / 2;
				posY += -sinf(angle) * 1;
				rc = RectMakeCenter(posX + 150, posY, img->GetFrameWidth(), img->GetFreamHeight());
				shadowRc = RectMake(rc.right - 330, rc.bottom - img->GetFreamHeight() / 3 + 15, 80, img->GetFreamHeight() / 3);

				if (attackTime > 1.5)
				{
					attackTime = 0;
					eState = RIGHT_MOVE;
					*anim = *ANIMATIONKEY.findAnimation("dkRightMove");
					anim->start();
				}
			}
			else
			{
				angle = getAngle(GetCenterPos(shadowRc).x, GetCenterPos(shadowRc).y,
					GetCenterPos(pm->GetPlayer1()->getRc()).x, GetCenterPos(pm->GetPlayer1()->getRc()).y);

				posX -= cosf(angle) * 5;
				posY += -sinf(angle) * 5;
				rc = RectMakeCenter(posX + 150, posY, img->GetFrameWidth(), img->GetFreamHeight());
				shadowRc = RectMake(rc.right - 330, rc.bottom - img->GetFreamHeight() / 3 + 15, 80, img->GetFreamHeight() / 3);
			}
		}
		break;
		case LEFT_ATTACK3:
		{
			DieEnemy();
			switch (sState)
			{
				case LEFT_JUMP:
				{
					isShadow = true;
					if (CAM.GetRC().right>shadowRc.right&&CAM.GetRC().top<rc.top)
					{
						angle = getAngle(GetCenterPos(shadowRc).x, GetCenterPos(shadowRc).y, CAM.GetRC().right, CAM.GetRC().top);
						posX += cosf(angle) * 3;
						posY += -sinf(angle) * 3;
						rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
						shadowRc = RectMake(rc.right - 180, initPosY, 80, img->GetFreamHeight() / 3);
					}
					else
					{
						angle = getAngle(GetCenterPos(shadowRc).x, GetCenterPos(rc).y,
							GetCenterPos(pm->GetPlayer1()->getRc()).x, GetCenterPos(pm->GetPlayer1()->getRc()).y);
						*anim = *ANIMATIONKEY.findAnimation("dkLeftAttack3");
						anim->stop();
						sState = LEFT_JUMPATTACK;
						//에너미그림자와 플레이어그림자의 각도
						setAngle = getAngle(GetCenterPos(shadowRc).x, GetCenterPos(shadowRc).y, GetCenterPos(pm->GetPlayer1()->getRc()).x, GetCenterPos(pm->GetPlayer1()->getRc()).y);
					}
				}
				break;
				case LEFT_JUMPATTACK:
				{
					//자기그림자랑 충돌했을때 해야함
					if (GetCenterPos(shadowRc).y-50 < posY)
					{
						isShadow = false;
						shadowColRc = RectMake(0, 0, 0, 0);
						if (!anim->isPlay())
						{
							anim->start();
						}
						attackTime += TIMEMANAGER.getElapsedTime();

						if (attackTime > 2)
						{
							if (GetCenterPos(pm->GetPlayer1()->getRc()).x > GetCenterPos(shadowRc).x)
							{
								eState = RIGHT_MOVE;
								*anim = *ANIMATIONKEY.findAnimation("dkRightMove");
								anim->start();
								rc = RectMakeCenter(posX + 150, posY, img->GetFrameWidth(), img->GetFreamHeight());
								shadowRc = RectMake(rc.right - 330, rc.bottom - img->GetFreamHeight() / 3 + 15, 80, img->GetFreamHeight() / 3);
							}
							else
							{
								eState = LEFT_MOVE;
								*anim = *ANIMATIONKEY.findAnimation("dkLeftMove");
								anim->start();
							}
							attackTime = 0;
							setShadowY = 0;
						}
					}
					else
					{
						shadowColRc = RectMakeCenter(GetCenterPos(shadowRc).x, GetCenterPos(shadowRc).y, 120, 60);
						isShadow = true;
						setShadowY += -sinf(setAngle)*5;

						posX += cosf(angle) * 5;
						posY += -sinf(angle) * 5;
						rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
						shadowRc = RectMake(rc.right - 180, initPosY+setShadowY, 80, img->GetFreamHeight() / 3);
					}
				}
				break;
			}
		}
		break;
		case RIGHT_ATTACK3:
		{
			DieEnemy();
			switch (sState)
			{
			case RIGHT_JUMP:
			{
				isShadow = true;
				if (CAM.GetRC().left<shadowRc.left&&CAM.GetRC().top<rc.top)
				{
					angle = getAngle(GetCenterPos(shadowRc).x, GetCenterPos(shadowRc).y, CAM.GetRC().left, CAM.GetRC().top);
					posX += cosf(angle) * 3;
					posY += -sinf(angle) * 3;
					rc = RectMakeCenter(posX + 150, posY, img->GetFrameWidth(), img->GetFreamHeight());
					shadowRc = RectMake(rc.right - 330, initPosY, 80, img->GetFreamHeight() / 3);
				}
				else
				{
					angle = getAngle(GetCenterPos(shadowRc).x, GetCenterPos(rc).y,
						GetCenterPos(pm->GetPlayer1()->getRc()).x, GetCenterPos(pm->GetPlayer1()->getRc()).y);
					*anim = *ANIMATIONKEY.findAnimation("dkRightAttack3");
					anim->stop();
					sState = RIGHT_JUMPATTACK;
					//에너미그림자와 플레이어그림자의 각도
					setAngle = getAngle(GetCenterPos(shadowRc).x, GetCenterPos(shadowRc).y, GetCenterPos(pm->GetPlayer1()->getRc()).x, GetCenterPos(pm->GetPlayer1()->getRc()).y);
				}
			}
			break;
			case RIGHT_JUMPATTACK:
			{
				//자기그림자랑 충돌했을때 해야함
				if (GetCenterPos(shadowRc).y - 50 < posY)
				{
					isShadow = false;
					shadowColRc = RectMake(0, 0, 0, 0);
					if (!anim->isPlay())
					{
						anim->start();
					}
					attackTime += TIMEMANAGER.getElapsedTime();

					if (attackTime > 2)
					{
						if (GetCenterPos(pm->GetPlayer1()->getRc()).x > GetCenterPos(shadowRc).x)
						{
							eState = RIGHT_MOVE;
							*anim = *ANIMATIONKEY.findAnimation("dkRightMove");
							anim->start();
						}
						else
						{
							eState = LEFT_MOVE;
							*anim = *ANIMATIONKEY.findAnimation("dkLeftMove");
							anim->start();
							rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
							shadowRc = RectMake(rc.right - 180, rc.bottom - img->GetFreamHeight() / 3 + 15, 80, img->GetFreamHeight() / 3);
						}
						attackTime = 0;
						setShadowY = 0;
					}
				}
				else
				{
					isShadow = true;
					setShadowY += -sinf(setAngle) * 5;

					posX += cosf(angle) * 5;
					posY += -sinf(angle) * 5;
					rc = RectMakeCenter(posX+ 150, posY, img->GetFrameWidth(), img->GetFreamHeight());
					shadowRc = RectMake(rc.right - 330, initPosY + setShadowY, 80, img->GetFreamHeight() / 3);
					shadowColRc = RectMakeCenter(GetCenterPos(shadowRc).x, GetCenterPos(shadowRc).y, 120, 60);
				}
			}
			break;
			}
		}
		break;
		case LEFT_MOVE:
		{
			DieEnemy();
			angle = getAngle(GetCenterPos(shadowRc).x, GetCenterPos(shadowRc).y,
				GetCenterPos(pm->GetPlayer1()->getRc()).x, GetCenterPos(pm->GetPlayer1()->getRc()).y);

			posX += cosf(angle) * 1;
			posY += -sinf(angle) * 1;
			rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
			shadowRc = RectMake(rc.right - 180, rc.bottom - img->GetFreamHeight() / 3 + 15, 80, img->GetFreamHeight() / 3);

			if (GetCenterPos(pm->GetPlayer1()->getRc()).y+10>GetCenterPos(shadowRc).y&&
				GetCenterPos(pm->GetPlayer1()->getRc()).y - 10<GetCenterPos(shadowRc).y)
			{
				if (atkArr[atkIdx] == 0)
				{
					if (getDistance(GetCenterPos(pm->GetPlayer1()->getRc()).x, GetCenterPos(pm->GetPlayer1()->getRc()).y,
						GetCenterPos(shadowRc).x, GetCenterPos(shadowRc).y) < 200)
					{
						RandomAttack(atkArr[atkIdx]);
						atkIdx++;
						if (atkIdx > 7)
							atkIdx = 0;
					}
				}
				else if (atkArr[atkIdx] == 1)
				{
					if (getDistance(GetCenterPos(pm->GetPlayer1()->getRc()).x, GetCenterPos(pm->GetPlayer1()->getRc()).y,
						GetCenterPos(shadowRc).x, GetCenterPos(shadowRc).y) < 300)
					{
						RandomAttack(atkArr[atkIdx]);
						atkIdx++;
						if (atkIdx > 7)
							atkIdx = 0;
					}
				}
				else
				{
					if (getDistance(GetCenterPos(pm->GetPlayer1()->getRc()).x, GetCenterPos(pm->GetPlayer1()->getRc()).y,
						GetCenterPos(shadowRc).x, GetCenterPos(shadowRc).y) < 50)
					{
						RandomAttack(atkArr[atkIdx]);
						atkIdx++;
						if (atkIdx > 7)
							atkIdx = 0;
					}
				}
			}

			if (GetCenterPos(pm->GetPlayer1()->getRc()).x > GetCenterPos(shadowRc).x)
			{
				eState = RIGHT_MOVE;
				*anim = *ANIMATIONKEY.findAnimation("dkRightMove");
				anim->start();
				rc = RectMakeCenter(posX + 150, posY, img->GetFrameWidth(), img->GetFreamHeight());
				shadowRc = RectMake(rc.right - 330, rc.bottom - img->GetFreamHeight() / 3 + 15, 80, img->GetFreamHeight() / 3);
			}
		}
		break;
		case RIGHT_MOVE:
		{
			DieEnemy();
			angle = getAngle(GetCenterPos(shadowRc).x, GetCenterPos(shadowRc).y,
				GetCenterPos(pm->GetPlayer1()->getRc()).x, GetCenterPos(pm->GetPlayer1()->getRc()).y);

			posX += cosf(angle) * 1;
			posY += -sinf(angle) * 1;
			rc = RectMakeCenter(posX+150, posY, img->GetFrameWidth(), img->GetFreamHeight());
			shadowRc = RectMake(rc.right - 330, rc.bottom - img->GetFreamHeight() / 3 + 15, 80, img->GetFreamHeight() / 3);

			if (GetCenterPos(pm->GetPlayer1()->getRc()).y + 10>GetCenterPos(shadowRc).y&&
				GetCenterPos(pm->GetPlayer1()->getRc()).y - 10<GetCenterPos(shadowRc).y)
			{
				if (atkArr[atkIdx] == 0)
				{
					if (getDistance(GetCenterPos(pm->GetPlayer1()->getRc()).x, GetCenterPos(pm->GetPlayer1()->getRc()).y,
						GetCenterPos(shadowRc).x, GetCenterPos(shadowRc).y) < 200)
					{
						RandomAttack(atkArr[atkIdx]);
						atkIdx++;
						if (atkIdx > 7)
							atkIdx = 0;
					}
				}
				else if (atkArr[atkIdx] == 1)
				{
					if (getDistance(GetCenterPos(pm->GetPlayer1()->getRc()).x, GetCenterPos(pm->GetPlayer1()->getRc()).y,
						GetCenterPos(shadowRc).x, GetCenterPos(shadowRc).y) < 300)
					{
						RandomAttack(atkArr[atkIdx]);
						atkIdx++;
						if (atkIdx > 7)
							atkIdx = 0;
					}
				}
				else
				{
					if (getDistance(GetCenterPos(pm->GetPlayer1()->getRc()).x, GetCenterPos(pm->GetPlayer1()->getRc()).y,
						GetCenterPos(shadowRc).x, GetCenterPos(shadowRc).y) < 50)
					{
						RandomAttack(atkArr[atkIdx]);
						atkIdx++;
						if (atkIdx > 7)
							atkIdx = 0;
					}
				}
			}

			if (GetCenterPos(pm->GetPlayer1()->getRc()).x < GetCenterPos(shadowRc).x)
			{
				eState = LEFT_MOVE;
				*anim = *ANIMATIONKEY.findAnimation("dkLeftMove");
				anim->start();
				rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
				shadowRc = RectMake(rc.right - 180, rc.bottom - img->GetFreamHeight() / 3 + 15, 80, img->GetFreamHeight() / 3);
			}
		}
		break;
		case LEFT_DIE:
		{
			dieTime += TIMEMANAGER.getElapsedTime();
			if (!anim->isPlay())
			{
				*anim = *ANIMATIONKEY.findAnimation("dkLeftDie2");
				anim->start();
			}
			if (dieTime > 4)
			{
				isDie = true;
				isShow = false;
			}
		}
		break;
		case RIGHT_DIE:
		{
			dieTime += TIMEMANAGER.getElapsedTime();
			if (!anim->isPlay())
			{
				*anim = *ANIMATIONKEY.findAnimation("dkRightDie2");
				anim->start();
			}
			if (dieTime > 4)
			{
				isDie = true;
				isShow = false;
			}
		}
		break;
		case END:
		{
		}
		break;
	}
}

void DragonKnight::DieEnemy()
{
	if (hp <= 0)
	{
		SOUNDMANAGER.play("41DragonKnightDie");
		if (eState == LEFT_IDLE || eState == LEFT_ATTACK || eState == LEFT_MOVE||eState==LEFT_ATTACK3||eState==LEFT_ATTACK2)
		{
			eState = LEFT_DIE;
			*anim = *ANIMATIONKEY.findAnimation("dkLeftDie");
			anim->start();
		}
		else if (eState == RIGHT_IDLE || eState == RIGHT_ATTACK || eState == RIGHT_MOVE||eState==RIGHT_ATTACK3||eState==LEFT_ATTACK2)
		{
			eState = RIGHT_DIE;
			*anim = *ANIMATIONKEY.findAnimation("dkRightDie");
			anim->start();
		}
		anim->start();
	}
}

void DragonKnight::Damaged()
{
	hp--;
}

void DragonKnight::RandomAttack(int num)
{
	if (eState == LEFT_MOVE)
	{
		if (num==0)
		{
			chainAttackSound = true;
			eState = LEFT_ATTACK;
			*anim = *ANIMATIONKEY.findAnimation("dkLeftAttack");
			anim->start();
		}
		else if (num==1)
		{
			eState = LEFT_ATTACK2;
			*anim = *ANIMATIONKEY.findAnimation("dkLeftAttack2");
			anim->start();
		}
		else
		{
			SOUNDMANAGER.play("42DragonKnightFly");
			eState = LEFT_ATTACK3;
			*anim = *ANIMATIONKEY.findAnimation("dkLeftJump");
			anim->start();
			sState = LEFT_JUMP;
		}
	}
	else if (eState == RIGHT_MOVE)
	{
		if (num==0)
		{
			chainAttackSound = true;
			eState = RIGHT_ATTACK;
			*anim = *ANIMATIONKEY.findAnimation("dkRightAttack");
			anim->start();
		}
		else if (num==1)
		{
			eState = RIGHT_ATTACK2;
			*anim = *ANIMATIONKEY.findAnimation("dkRightAttack2");
			anim->start();
		}
		else
		{
			SOUNDMANAGER.play("42DragonKnightFly");
			eState = RIGHT_ATTACK3;
			*anim = *ANIMATIONKEY.findAnimation("dkRightJump");
			anim->start();
			sState = RIGHT_JUMP;
		}
	}
}

void DragonKnight::UpdateAttackArr()
{
	if (hp > 20)
	{
		for (int i = 0; i < 3; i++)
			atkArr[i] = 0;
		atkArr[3] = 1;
		for (int i = 4; i < 7; i++)
			atkArr[i] = 0;
		atkArr[7] = 1;
	}
	else if (hp <= 20 && hp > 10)
	{
		for (int i = 0; i < 2; i++)
			atkArr[i] = 0;
		atkArr[2] = 2;
		atkArr[3] = 0;
		atkArr[4] = 1;
		atkArr[5] = 0;
		atkArr[6] = 2;
		atkArr[7] = 2;
	}
	else
	{
		for (int i = 0; i < 2; i++)
			atkArr[i] = 0;
		atkArr[2] = 1;
		atkArr[3] = 0;
		atkArr[4] = 1;
		atkArr[5] = 0;
		atkArr[6] = 2;
		atkArr[7] = 1;
	}
}
