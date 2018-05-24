#include "stdafx.h"
#include "DragonKnight.h"


DragonKnight::DragonKnight(ENEMYTYPE _eType)
	:Enemy(_eType)
{
	IMAGEMANAGER.addFrameImage("����", PathFile("image\\Enemy", "����").c_str(), 4230, 2100, 10, 14, true, RGB(255, 0, 255));
	IMAGEMANAGER.addImage("����׸���", PathFile("image\\Enemy", "����׸���").c_str(), 80, 40,true, RGB(255, 0, 255));
	EFFECTMANAGER.addEffect("����", PathFile("image\\Enemy", "�Ĺ�����").c_str(), 1470, 80, 82, 80, 60, 1, 30);
}


DragonKnight::~DragonKnight()
{
}

HRESULT DragonKnight::Init(int x, int y, ENEMYSTATE eState)
{
	int show[]= { 0,1,2,3};
	ANIMATIONKEY.addArrayFrameAnimation("dkShow", "����", show, 4,4, false);

	int leftIde[] = { 4 };
	ANIMATIONKEY.addArrayFrameAnimation("dkLeftIdle", "����", leftIde, 1, 2, false);

	int rightIdle[] = { 75 };
	ANIMATIONKEY.addArrayFrameAnimation("dkRightIdle", "����", rightIdle, 1, 2, false);

	int leftMove[] = { 5,6,7,8,9,10,11};
	ANIMATIONKEY.addArrayFrameAnimation("dkLeftMove", "����", leftMove, 7, 9, true);

	int rightMove[] = { 74,73,72,71,70,89,88 };
	ANIMATIONKEY.addArrayFrameAnimation("dkRightMove", "����", rightMove, 7, 9, true);

	int leftAttack[] = { 12,13,14,15,16,17,18,19,20,21,22,23 };
	ANIMATIONKEY.addArrayFrameAnimation("dkLeftAttack", "����", leftAttack, 12, 10, false);

	int rightAttack[] = {87,86,85,84,83,82,81,80,99,98,97,96 };
	ANIMATIONKEY.addArrayFrameAnimation("dkRightAttack", "����", rightAttack, 12, 10, false);

	int leftAttack2[] = { 31,32,33,34,35,36,37,38,39,40,41,42,43};
	ANIMATIONKEY.addArrayFrameAnimation("dkLeftAttack2", "����", leftAttack2, 13, 32, true);

	int rightAttack2[] = { 108,107,106,105,104,103,102,101,100,119,118,117,116 };
	ANIMATIONKEY.addArrayFrameAnimation("dkRightAttack2", "����", rightAttack2, 13, 32, true);

	int leftAttack3[] = { 56,57,58,59,60 };
	ANIMATIONKEY.addArrayFrameAnimation("dkLeftAttack3", "����", leftAttack3, 5, 8, false);

	int rightAttack3[] = {123,122,121,120,139};
	ANIMATIONKEY.addArrayFrameAnimation("dkRightAttack3", "����", rightAttack3, 5, 8, false);

	int leftJump[] = {44,45,46,47,48,49,50,51,52,53,54,55};
	ANIMATIONKEY.addArrayFrameAnimation("dkLeftJump", "����", leftJump, 12, 20, true);

	int rightJump[] = {115,114,113,112,111,110,129,128,127,126,125,124};
	ANIMATIONKEY.addArrayFrameAnimation("dkRightJump", "����", rightJump, 12, 8, true);

	int leftDie[] = { 61,62,63,64,65,66,67,68,69 };
	ANIMATIONKEY.addArrayFrameAnimation("dkLeftDie", "����", leftDie, 9, 9, false);

	int leftDie2[] = {68,69};
	ANIMATIONKEY.addArrayFrameAnimation("dkLeftDie2", "����", leftDie2, 2, 9, true);

	int rightDie[] = {138,137,136,135,134,133,132,131,130 };
	ANIMATIONKEY.addArrayFrameAnimation("dkRightDie", "����", rightDie, 9, 9, false);

	int rightDie2[] = {131,130 };
	ANIMATIONKEY.addArrayFrameAnimation("dkRightDie2", "����", rightDie2, 2, 9, true);

	img = IMAGEMANAGER.findImage("����");
	Enemy::Init(x, y, eState);
	anim = new animation;

	*anim = *ANIMATIONKEY.findAnimation("dkShow");
	anim->start();

	shadowImg = IMAGEMANAGER.findImage("����׸���");
	startTime = 0;
	sState = CHANGE_BEGIN;
	attackTime = 0;
	hp = 30;
	dieTime = 0;
	initPosY = rc.bottom - img->GetFreamHeight() / 3 + 15;
	return S_OK;
}

void DragonKnight::Release()
{
}

void DragonKnight::EnemyUpdate(PlayerManager * pm)
{
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
						EFFECTMANAGER.play("����", posX + 70, posY+30);
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
				BULLET.Shot("�����0", posX - 80, posY, 0, 0, 0, 0);
				stime = 0;
			}
			if (!anim->isPlay())
			{
				for (int i = 0; i < BULLET.GetBulletVec("�����0").size(); i++)
					BULLET.Destroy("�����0", i);
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
				BULLET.Shot("�����0", posX + 170, posY, 0, 0, 0, 0);
				stime = 0;
			}

			if (!anim->isPlay())
			{
				for (int i = 0; i < BULLET.GetBulletVec("�����0").size(); i++)
					BULLET.Destroy("�����0", i);
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
				//�Ѿ˹߻�
				static float btime = 0;
				btime += TIMEMANAGER.getElapsedTime();
				
				if (btime > 0.3)
				{
					BULLET.Shot("�����", posX, posY, PI , 0, 5, 0);
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

				posX -= cosf(angle) * 3;
				posY += -sinf(angle) * 3;
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
				//�Ѿ˹߻�
				static float btime1 = 0;
				btime1 += TIMEMANAGER.getElapsedTime();

				if (btime1 > 0.3)
				{
					BULLET.Shot("�����", posX, posY, 0, 0, 5, 0);
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

				posX -= cosf(angle) * 3;
				posY += -sinf(angle) * 3;
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
						//���ʹ̱׸��ڿ� �÷��̾�׸����� ����
						setAngle = getAngle(GetCenterPos(shadowRc).x, GetCenterPos(shadowRc).y, GetCenterPos(pm->GetPlayer1()->getRc()).x, GetCenterPos(pm->GetPlayer1()->getRc()).y);
					}
				}
				break;
				case LEFT_JUMPATTACK:
				{
					//�ڱ�׸��ڶ� �浹������ �ؾ���
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
					//���ʹ̱׸��ڿ� �÷��̾�׸����� ����
					setAngle = getAngle(GetCenterPos(shadowRc).x, GetCenterPos(shadowRc).y, GetCenterPos(pm->GetPlayer1()->getRc()).x, GetCenterPos(pm->GetPlayer1()->getRc()).y);
				}
			}
			break;
			case RIGHT_JUMPATTACK:
			{
				//�ڱ�׸��ڶ� �浹������ �ؾ���
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
				if (getDistance(GetCenterPos(pm->GetPlayer1()->getRc()).x, GetCenterPos(pm->GetPlayer1()->getRc()).y,
					GetCenterPos(shadowRc).x, GetCenterPos(shadowRc).y) < 200)
				{
					int rndNum = RND.GetFromTo(0, 10);
					RandomAttack(rndNum);
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
				if (getDistance(GetCenterPos(pm->GetPlayer1()->getRc()).x, GetCenterPos(pm->GetPlayer1()->getRc()).y,
					GetCenterPos(shadowRc).x, GetCenterPos(shadowRc).y) < 200)
				{
					int rndNum = RND.GetFromTo(0, 10);
					RandomAttack(rndNum);
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
	if (hp > 20)
	{
		if (eState == LEFT_MOVE)
		{
			if (num>=0&&num<6)
			{
				eState = LEFT_ATTACK;
				*anim = *ANIMATIONKEY.findAnimation("dkLeftAttack");
				anim->start();
			}
			else if (num>=6&&num<8)
			{
				eState = LEFT_ATTACK2;
				*anim = *ANIMATIONKEY.findAnimation("dkLeftAttack2");
				anim->start();
			}
			else
			{
				eState = LEFT_ATTACK3;
				*anim = *ANIMATIONKEY.findAnimation("dkLeftJump");
				anim->start();
				sState = LEFT_JUMP;
			}
		}
		else if (eState == RIGHT_MOVE)
		{
			if (num >= 0 && num<6)
			{
				eState = RIGHT_ATTACK;
				*anim = *ANIMATIONKEY.findAnimation("dkRightAttack");
				anim->start();
			}
			else if (num >= 6 && num<8)
			{
				eState = RIGHT_ATTACK2;
				*anim = *ANIMATIONKEY.findAnimation("dkRightAttack2");
				anim->start();
			}
			else
			{
				eState = RIGHT_ATTACK3;
				*anim = *ANIMATIONKEY.findAnimation("dkRightJump");
				anim->start();
				sState = RIGHT_JUMP;
			}
		}
	}
	else if (hp > 10 && hp <= 20)
	{
		if (eState == LEFT_MOVE)
		{
			if (num>=0&&num<4)
			{
				eState = LEFT_ATTACK;
				*anim = *ANIMATIONKEY.findAnimation("dkLeftAttack");
				anim->start();
			}
			else if (num>=4&&num<6)
			{
				eState = LEFT_ATTACK2;
				*anim = *ANIMATIONKEY.findAnimation("dkLeftAttack2");
				anim->start();
			}
			else
			{
				eState = LEFT_ATTACK3;
				*anim = *ANIMATIONKEY.findAnimation("dkLeftJump");
				anim->start();
				sState = LEFT_JUMP;
			}
		}
		else if (eState == RIGHT_MOVE)
		{
			if (num >= 0 && num<4)
			{
				eState = RIGHT_ATTACK;
				*anim = *ANIMATIONKEY.findAnimation("dkRightAttack");
				anim->start();
			}
			else if (num >= 4 && num<6)
			{
				eState = RIGHT_ATTACK2;
				*anim = *ANIMATIONKEY.findAnimation("dkRightAttack2");
				anim->start();
			}
			else
			{
				eState = RIGHT_ATTACK3;
				*anim = *ANIMATIONKEY.findAnimation("dkRightJump");
				anim->start();
				sState = RIGHT_JUMP;
			}
		}
	}
	else
	{
		if (eState == LEFT_MOVE)
		{
			if (num>=0&&num<3)
			{
				eState = LEFT_ATTACK;
				*anim = *ANIMATIONKEY.findAnimation("dkLeftAttack");
				anim->start();
			}
			else if (num>=3&&num<7)
			{
				eState = LEFT_ATTACK2;
				*anim = *ANIMATIONKEY.findAnimation("dkLeftAttack2");
				anim->start();
			}
			else
			{
				eState = LEFT_ATTACK3;
				*anim = *ANIMATIONKEY.findAnimation("dkLeftJump");
				anim->start();
				sState = LEFT_JUMP;
			}
		}
		else if (eState == RIGHT_MOVE)
		{
			if (num >= 0 && num<3)
			{
				eState = RIGHT_ATTACK;
				*anim = *ANIMATIONKEY.findAnimation("dkRightAttack");
				anim->start();
			}
			else if (num >= 3 && num<7)
			{
				eState = RIGHT_ATTACK2;
				*anim = *ANIMATIONKEY.findAnimation("dkRightAttack2");
				anim->start();
			}
			else if (num == 2)
			{
				eState = RIGHT_ATTACK3;
				*anim = *ANIMATIONKEY.findAnimation("dkRightJump");
				anim->start();
				sState = RIGHT_JUMP;
			}
		}
	}
}
