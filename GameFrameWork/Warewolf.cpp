#include "stdafx.h"
#include "Warewolf.h"


Warewolf::Warewolf(ENEMYTYPE _eType)
	:Enemy(_eType)
{
	IMAGEMANAGER.addFrameImage("�������", PathFile("image\\Enemy", "�������").c_str(), 840, 388, 7, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER.addFrameImage("�������ȭ��", PathFile("image\\Enemy", "�������ȭ��").c_str(), 60, 20, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER.addFrameImage("�����Ѿ˱׸���", PathFile("image\\Enemy", "�����Ѿ˱׸���").c_str(), 60, 10, 1, 1, true, RGB(255, 0, 255));
}


Warewolf::~Warewolf()
{
}

HRESULT Warewolf::Init(int x, int y, ENEMYSTATE eState)
{
	BULLET.BulletSetting("����ȭ��", IMAGEMANAGER.findImage("�������ȭ��"), 30, false, 0, 2);
	BULLET.BulletShadowSetting("����ȭ��", IMAGEMANAGER.findImage("�����Ѿ˱׸���"), RectMake(posX, posY, 60, 10), 50);

	for (int i = 0; i < 30; i++)
		ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("����ȭ��")[i]);
	int leftIde[] = { 0 };
	ANIMATIONKEY.addArrayFrameAnimation("wwLeftIdle", "�������", leftIde, 1, 2, true);

	int rightIdle[] = { 20 };
	ANIMATIONKEY.addArrayFrameAnimation("wwRightIdle", "�������", rightIdle, 1, 2, true);

	int leftMove[] = { 4,5,6,7,8 };
	ANIMATIONKEY.addArrayFrameAnimation("wwLeftMove", "�������", leftMove, 5,4 ,true);

	int rightMove[] = { 27,26,16,15,14 };
	ANIMATIONKEY.addArrayFrameAnimation("wwRightMove", "�������", rightMove, 5, 4, true);

	int leftAttack[] = { 1,3,2 };
	ANIMATIONKEY.addArrayFrameAnimation("wwLeftAttack", "�������", leftAttack, 3, 4, false);

	int rightAttack[] = { 19,17,18 };
	ANIMATIONKEY.addArrayFrameAnimation("wwRightAttack", "�������", rightAttack, 3, 4, false);

	int leftDie[] = { 10,11,12 };
	ANIMATIONKEY.addArrayFrameAnimation("wwLeftDie", "�������", leftDie, 3, 4, false);

	int rightDie[] = { 24,23,22 };
	ANIMATIONKEY.addArrayFrameAnimation("wwRightDie", "�������", rightDie, 3, 4, false);

	img = IMAGEMANAGER.findImage("�������");
	Enemy::Init(x, y, eState);

	anim = new animation;

	if (eState == LEFT_IDLE)
		anim = ANIMATIONKEY.findAnimation("wwLeftIdle");
	else if (eState == RIGHT_IDLE)
		anim = ANIMATIONKEY.findAnimation("wwRightIdle");
	anim->start();

	delayTime = 2;
	gravity = 0;
	dieTime = 0;
	hp = 3;
	getAlpha = 15;

	attackDistance = RND.GetFromTo(100, 600);
	delayCount = RND.GetFromTo(1, 4);
	return S_OK;
}

void Warewolf::Release()
{
}

void Warewolf::EnemyUpdate(PlayerManager*pm)
{
	switch (eState)
	{
		case LEFT_IDLE:
		{
			delayTime += TIMEMANAGER.getElapsedTime();
			
			if (delayTime > delayCount)
				//�÷��̾ ���ʹ��� ���ʿ� ������
			{
				if (pm->GetPlayer1()->GetX() < posX)
				{
					eState = LEFT_MOVE;
					anim = ANIMATIONKEY.findAnimation("wwLeftMove");
					anim->start();
					delayTime = 0;
				}
				else
				{
					eState = RIGHT_MOVE;
					anim = ANIMATIONKEY.findAnimation("wwRightMove");
					anim->start();
					delayTime = 0;
				}
			}
			DieEnemy();
		}
		break;
		case RIGHT_IDLE:
		{
			delayTime += TIMEMANAGER.getElapsedTime();

			if (delayTime > delayCount)
				//�÷��̾ ���ʹ��� �����ʿ� ������
			{
				if (pm->GetPlayer1()->GetX() > posX)
				{
					eState = RIGHT_MOVE;
					anim = ANIMATIONKEY.findAnimation("wwRightMove");
					anim->start();
					delayTime = 0;
				}
				else
				{
					eState = LEFT_MOVE;
					anim = ANIMATIONKEY.findAnimation("wwLeftMove");
					anim->start();
					delayTime = 0;
				}
			}
			DieEnemy();
		}
		break;
		case LEFT_ATTACK:
		{
			if (!anim->isPlay())
			{
				BULLET.Shot("����ȭ��", posX, posY, PI, 0, 5, 0);
				eState = LEFT_IDLE;
				anim = ANIMATIONKEY.findAnimation("wwLeftIdle");
				delayTime = 0;
			}
			
			DieEnemy();
		}
		break;
		case RIGHT_ATTACK:
		{
			if (!anim->isPlay())
			{
				BULLET.Shot("����ȭ��", posX, posY, 0, 0, 5, 1);
				eState = RIGHT_IDLE;
				anim = ANIMATIONKEY.findAnimation("wwRightIdle");
				delayTime = 0;
			}
			DieEnemy();
		}
		break;
		case LEFT_MOVE:
		{
			//�Ÿ��� �������� ���̸� �׳� �����ΰ�
			
			if (getDistance(pm->GetPlayer1()->GetX(), pm->GetPlayer1()->GetY(), posX, posY) > attackDistance)
			{
				posX -= 1.5;
				rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
				shadowRc = RectMake(rc.right - img->GetFrameWidth(), rc.bottom - img->GetFreamHeight() / 3+15, img->GetFrameWidth(), img->GetFreamHeight() / 3);
			}
			else
			{
				angle = getAngle(GetCenterPos(shadowRc).x, GetCenterPos(shadowRc).y, GetCenterPos(pm->GetPlayer1()->getRc()).x, GetCenterPos(pm->GetPlayer1()->getRc()).y);
				
				if (GetCenterPos(shadowRc).y > GetCenterPos(pm->GetPlayer1()->getRc()).y)
					posY -= 1.5;
				else
					posY += 1.5;

				rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
				shadowRc = RectMake(rc.right - img->GetFrameWidth(), rc.bottom - img->GetFreamHeight() / 3+15, img->GetFrameWidth(), img->GetFreamHeight() / 3);

				if (GetCenterPos(shadowRc).y>GetCenterPos(pm->GetPlayer1()->getRc()).y-5&&
					GetCenterPos(shadowRc).y<GetCenterPos(pm->GetPlayer1()->getRc()).y + 5)
				{
					eState = LEFT_ATTACK;
					anim = ANIMATIONKEY.findAnimation("wwLeftAttack");
					anim->start();
				}
			}
			DieEnemy();
		}
		break;
		case RIGHT_MOVE:
		{
			if (getDistance(pm->GetPlayer1()->GetX(), pm->GetPlayer1()->GetY(), posX, posY) > 300)
			{
				posX += 1.5;
				rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
				shadowRc = RectMake(rc.right - img->GetFrameWidth(), rc.bottom - img->GetFreamHeight() / 3 + 15, img->GetFrameWidth(), img->GetFreamHeight() / 3);
			}
			else
			{
				angle = getAngle(GetCenterPos(shadowRc).x, GetCenterPos(shadowRc).y, GetCenterPos(pm->GetPlayer1()->getRc()).x, GetCenterPos(pm->GetPlayer1()->getRc()).y);

				if (GetCenterPos(shadowRc).y > GetCenterPos(pm->GetPlayer1()->getRc()).y)
					posY -= 1.5;
				else
					posY += 1.5;

				rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
				shadowRc = RectMake(rc.right - img->GetFrameWidth(), rc.bottom - img->GetFreamHeight() / 3 + 15, img->GetFrameWidth(), img->GetFreamHeight() / 3);

				if (GetCenterPos(shadowRc).y>GetCenterPos(pm->GetPlayer1()->getRc()).y - 5 &&
					GetCenterPos(shadowRc).y<GetCenterPos(pm->GetPlayer1()->getRc()).y + 5)
				{
					eState = RIGHT_ATTACK;
					anim = ANIMATIONKEY.findAnimation("wwRightAttack");
					anim->start();
				}
			}
			DieEnemy();
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
			posX += cosf(PI-3 / PI) * 8;
			posY += -sinf(PI-3 / PI) * 8 + gravity;
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
			if (alpha > 150||alpha<1)
				getAlpha *= -1;
	
			if (dieTime > 1.5)
			{
				isDie = true;
			}
		}
		break;
	}
}

void Warewolf::DieEnemy()
{
	if (hp<0)
	{
		initPosY = posY;

		if (eState == LEFT_IDLE || eState == LEFT_ATTACK || eState == LEFT_MOVE)
		{
			eState = LEFT_DIE;
			anim = ANIMATIONKEY.findAnimation("wwLeftDie");
		}
		else if (eState == RIGHT_IDLE || eState == RIGHT_ATTACK || eState == RIGHT_MOVE)
		{
			eState = RIGHT_DIE;
			anim = ANIMATIONKEY.findAnimation("wwRightDie");
		}
		anim->start();
	}
}

