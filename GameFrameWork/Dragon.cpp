#include "stdafx.h"
#include "Dragon.h"


Dragon::Dragon(ENEMYTYPE _eType)
	:Enemy(_eType)
{
	IMAGEMANAGER.addFrameImage("µå·¡°ï¸Ó¸®", PathFile("image\\Enemy", "¿ë¸Ó¸®").c_str(), 1888, 300, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER.addFrameImage("µå·¡°ïÆÈ", PathFile("image\\Enemy", "¿ëÆÈ").c_str(), 453, 350, 3, 1, true, RGB(255, 0, 255));
	EFFECTMANAGER.addEffect("¸¶Á×", PathFile("image\\Enemy", "¸¶¹ý»çÁ×À½").c_str(), 1425, 84, 95, 84, 60, 1, 40);
}


Dragon::~Dragon()
{
}

HRESULT Dragon::Init(int x, int y, ENEMYSTATE eState)
{
	//¿ë¸öÅë=>±âº»·»´õ·Î°£´Ù

	shadowImg = IMAGEMANAGER.findImage("¿ë±â»ç±×¸²ÀÚ");
	Enemy::Init(x, y, eState);

	//¿ë¸Ó¸®=>µû·Î·»´õ°£´Ù
	int dHeadIdle[] = { 0,1 };
	ANIMATIONKEY.addArrayFrameAnimation("dhIdle", "µå·¡°ï¸Ó¸®", dHeadIdle, 2, 5, true);

	int dHeadAttack1[] = { 2,3,4,5,6 };
	ANIMATIONKEY.addArrayFrameAnimation("dhAttack", "µå·¡°ï¸Ó¸®", dHeadAttack1, 5, 12, true);

	int ddie[] = { 7};
	ANIMATIONKEY.addArrayFrameAnimation("dhDie", "µå·¡°ï¸Ó¸®", ddie, 1, 12, false);

	dHead = IMAGEMANAGER.findImage("µå·¡°ï¸Ó¸®");
	dHeadAnim = new animation;
	*dHeadAnim = *ANIMATIONKEY.findAnimation("dhIdle");
	dHeadAnim->start();
	dHeadRc = RectMake(WINSIZEX / 2+150, -300, dHead->GetFrameWidth(), dHead->GetFreamHeight());
	headX = GetCenterPos(dHeadRc).x;
	headY= GetCenterPos(dHeadRc).y;
	initHeadX = headX;
	initHeadY = headY;

	//¿ëÆÈ->µû·Î·»´õ°£´Ù
	int dHandIdle[] = { 0 };
	ANIMATIONKEY.addArrayFrameAnimation("dhaIdle", "µå·¡°ïÆÈ", dHandIdle, 1, 5, false);

	int dHandAttack1[] = {0, 1,2 };
	ANIMATIONKEY.addArrayFrameAnimation("dhaAttack", "µå·¡°ïÆÈ", dHandAttack1, 3, 5, false);

	dHand = IMAGEMANAGER.findImage("µå·¡°ïÆÈ");
	dHandAnim = new animation;
	*dHandAnim = *ANIMATIONKEY.findAnimation("dhaIdle");
	dHandAnim->start();
	dHandRc = RectMake(WINSIZEX / 2-300, -200, dHand->GetFrameWidth(), dHand->GetFreamHeight());
	handX = GetCenterPos(dHandRc).x;
	handY = GetCenterPos(dHandRc).y;
	colRect = RectMakeCenter(handX, handY, dHand->GetFrameWidth()/2, dHand->GetFreamHeight()+60);
	initHandX = handX;
	initHandY = handY;

	showTime = 0;
	dAttack = HAND_FOLLOW;
	dieTime = 0;
	hp = 45;
	atkIdx = 0;
	return S_OK;
}

void Dragon::Release()
{
}

void Dragon::EnemyUpdate(PlayerManager * pm)
{
	dHeadAnim->frameUpdate(TIMEMANAGER.getElapsedTime());
	dHandAnim->frameUpdate(TIMEMANAGER.getElapsedTime());
	UpdateAttackArr();
	switch (eState)
	{
		case LEFT_IDLE:
		{
			DieEnemy();
			headX += cosf(3 * PI / 2) * 2;
			headY += -sinf(3 * PI / 2) * 2;
			dHeadRc = RectMakeCenter(headX, headY, dHead->GetFrameWidth(), dHead->GetFreamHeight());
			shadowRc = RectMake(dHeadRc.right - 220, WINSIZEY/2+40, 80, 60);

			isShadow = true;

			if (headY > 150)
			{
				eState = LEFT_MOVE;
				dHeadAnim->start();
			}
		}
		break;
		case LEFT_ATTACK:
		{
			DieEnemy();
			if (headY > 0)
			{
				headX += cosf(PI / 2) * 2;
				headY += -sinf(PI / 2) * 2;
				dHeadRc = RectMakeCenter(headX, headY, dHead->GetFrameWidth(), dHead->GetFreamHeight());
				shadowRc = RectMakeCenter(handX, WINSIZEY / 2 + 40, 80, 60);
				shadowX = GetCenterPos(shadowRc).x;
				shadowY = GetCenterPos(shadowRc).y;
				dAttack = HAND_FOLLOW;

			}
			
			switch (dAttack)
			{
				case HAND_FOLLOW:
				{
					isShadow = true;
					handAngle = getAngle(shadowX, shadowY, GetCenterPos(pm->GetPlayer(playerNumber)->getRc()).x, GetCenterPos(pm->GetPlayer(playerNumber)->getRc()).y);
					shadowX += cosf(handAngle) * 5;
					shadowY += -sinf(handAngle) * 5;
					shadowRc = RectMakeCenter(shadowX, shadowY, 80, 60);

					handX = GetCenterPos(shadowRc).x;
					handY = initHandY;
					dHandRc = RectMakeCenter(handX, handY , dHand->GetFrameWidth(), dHand->GetFreamHeight());
					colRect = RectMakeCenter(handX, handY, dHand->GetFrameWidth()/2, dHand->GetFreamHeight()+60);
					RECT temp;
					RECT rc = RectMakeCenter(shadowX, shadowY , 80, 2);
					if(IntersectRect(&temp,&rc,&pm->GetPlayer(playerNumber)->getRc()))
					{
						SOUNDMANAGER.stop("52DragonBreath");
						SOUNDMANAGER.play("53DragonHand");
						dAttack = HAND_DOWN;
					}
				}
				break;
				case HAND_DOWN:
				{
					handY += 6;
					dHandRc = RectMakeCenter(handX, handY , dHand->GetFrameWidth(), dHand->GetFreamHeight());
					colRect = RectMakeCenter(handX, handY, dHand->GetFrameWidth()/2, dHand->GetFreamHeight()+60);
					*dHandAnim = *ANIMATIONKEY.findAnimation("dhaAttack");
					if (!dHandAnim->isPlay())
						dHandAnim->start();

					if (handY > GetCenterPos(shadowRc).y-200)
					{
						SOUNDMANAGER.play("52DragonBreath");
						dAttack = HAND_UP;
					}
				}
				break;
				case HAND_UP:
				{
					//¼ÕÀÌ¶û ´ë°¡¸®¶û ¿øÀ§Ä¡½ÃÄÑ³ö
					static float waitTime = 0;
					waitTime += TIMEMANAGER.getElapsedTime();

					if (waitTime > 1)
					{
						isShadow = false;

						handAngle = getAngle(handX, handY, initHandX, initHandY);

						if (handX<initHandX - 20 || handX>initHandX + 20)
							handX += cosf(handAngle) * 3;
						if (handY<initHandY - 20 || handY>initHandY + 20)
							handY += -sinf(handAngle) * 3;
						dHandRc = RectMakeCenter(handX, handY, dHand->GetFrameWidth(), dHand->GetFreamHeight());
						colRect = RectMakeCenter(handX, handY, dHand->GetFrameWidth()/2, dHand->GetFreamHeight()+60);
					}
					if (waitTime > 2.5)
					{
						waitTime = 0;
						eState = LEFT_MOVE;
						*dHandAnim = *ANIMATIONKEY.findAnimation("dhaIdle");
						if (DATABASE.LoadData("1P2P") == 1)
							playerNumber = RND.GetFromTo(0, 2);
					}
				}
				break;
			}
		}
		break;
		case LEFT_ATTACK2:
		{
			DieEnemy();
			isShadow = true;
			
			static float ont = 0;
			ont += TIMEMANAGER.getElapsedTime();

			static float st = 0;
			st += TIMEMANAGER.getElapsedTime();
			
			if (st > 0.2)
			{
				BULLET.Shot("µåºê", headX - 225, headY+75, 0, 0, 0, 0);
				st = 0;
			}
			
			if (ont > 4)
			{
				SOUNDMANAGER.play("52DragonBreath");
				ont = 0;
				st = 0;
				eState = LEFT_MOVE;
				*dHeadAnim = *ANIMATIONKEY.findAnimation("dhIdle");
				dHeadAnim->start();
			}

		}
		break;
		case LEFT_ATTACK3:
		{
			DieEnemy();
			if (headY > 50)
			{
				headY -= 4;
				dHeadRc = RectMakeCenter(headX, headY, dHead->GetFrameWidth(), dHead->GetFreamHeight());
			}
			else
			{
				static float et = 0;
				et += TIMEMANAGER.getElapsedTime();

				if (et > 4)
				{
					SOUNDMANAGER.play("52DragonBreath");
					eState = LEFT_MOVE;
					*dHeadAnim = *ANIMATIONKEY.findAnimation("dhIdle");
					dHeadAnim->start();
					et = 0;
				}

				static float f = 0;
				f += TIMEMANAGER.getElapsedTime();
				if (f > 0.7)
				{
					SOUNDMANAGER.play("39DragonKnightKnife");
					f = 0;
					static float s1 = PI / 6;
					static float s2 = PI / 9;
					static float s3 = PI / 3;

					static int getNum = 25;
					BULLET.Shot("µåÃÑ", headX - 100, headY + 80, PI + s1, 0, 5, 0, headY + 200+ getNum);
					BULLET.Shot("µåÃÑ", headX - 100, headY + 80, PI + s2, 0, 5, 0, headY + 150+ getNum);
					BULLET.Shot("µåÃÑ", headX - 100, headY + 80, PI + s3, 0, 5, 0, headY + 250+ getNum);

					getNum *= -1;
					float temp = s1;
					s1 = s2;
					s2 = s3;
					s3 = temp;
				}
			}

		}
		break;
		case LEFT_MOVE:
		{
			DieEnemy();
			isShadow = true;
			dHeadRc = RectMakeCenter(headX, headY, dHead->GetFrameWidth(), dHead->GetFreamHeight());
			shadowRc = RectMake(dHeadRc.right - 220, WINSIZEY / 2+40, 80, 60);

			if (headY < 150)
				headY += 4;
			else
			{
				static float wTime = 0;
				wTime += TIMEMANAGER.getElapsedTime();

				if (wTime > 2)
				{
					if (atkArr[atkIdx] == 0)
					{
						RandomAttack(atkArr[atkIdx]);
						atkIdx++;
						if (atkIdx > 7)
							atkIdx = 0;
					}
					else if (atkArr[atkIdx] == 1)
					{
						RandomAttack(atkArr[atkIdx]);
						atkIdx++;
						if (atkIdx > 7)
								atkIdx = 0;
					}
					else
					{
						RandomAttack(atkArr[atkIdx]);
						atkIdx++;
						if (atkIdx > 7)
							atkIdx = 0;
					}
					wTime = 0;
				}
			}
		}
		break;
		case LEFT_DIE:
		{
			dieTime += TIMEMANAGER.getElapsedTime();

			static float dtime = 0;
			dtime += TIMEMANAGER.getElapsedTime();

			if (dtime > 0.1)
			{
				EFFECTMANAGER.play("¸¶Á×", WINSIZEX/2+RND.GetFromTo(-300,300),WINSIZEY/2+RND.GetFromTo(-200,100));
				EFFECTMANAGER.play("¸¶Á×", WINSIZEX / 2 + RND.GetFromTo(-300, 300), WINSIZEY / 2 + RND.GetFromTo(-200, 100));
				EFFECTMANAGER.play("¸¶Á×", WINSIZEX / 2 + RND.GetFromTo(-300, 300), WINSIZEY / 2 + RND.GetFromTo(-200, 100));
				dtime = 0;
			}
			if (dieTime > 5)
			{
				isDie = true;
				isShow = false;
				isShadow = false;
			}
		}
		break;
	}
}

void Dragon::DieEnemy()
{
	if (hp <= 0)
	{
		SOUNDMANAGER.stop("52DragonBreath");
		SOUNDMANAGER.play("56DragonDie");
		if (eState == LEFT_IDLE || eState == LEFT_ATTACK || eState == LEFT_MOVE || eState == LEFT_ATTACK3 || eState == LEFT_ATTACK2)
		{
			eState = LEFT_DIE;
			*dHeadAnim = *ANIMATIONKEY.findAnimation("dhDie");
			dHeadAnim->start();
		}
	}
}

void Dragon::Damaged()
{
	if(eState != LEFT_ATTACK&&eState != LEFT_ATTACK3&&eState!=LEFT_IDLE&&eState!=LEFT_ATTACK2)
		hp--;
}

void Dragon::RandomAttack(int num)
{
	if (num == 0)
	{
		eState = LEFT_ATTACK;
		*dHeadAnim = *ANIMATIONKEY.findAnimation("dhIdle");
		dHeadAnim->start();
		isShadow = false;
	}
	else if (num == 1)
	{
		SOUNDMANAGER.stop("52DragonBreath");
		SOUNDMANAGER.play("54DragonFire");
		eState = LEFT_ATTACK2;
		*dHeadAnim = *ANIMATIONKEY.findAnimation("dhAttack");
		dHeadAnim->start();
		isShadow = true;
	}
	else
	{
		SOUNDMANAGER.stop("52DragonBreath");
		SOUNDMANAGER.play("55DragonFire2");
		eState = LEFT_ATTACK3;
		*dHeadAnim = *ANIMATIONKEY.findAnimation("dhAttack");
		dHeadAnim->start();
		isShadow = false;
	}
}

void Dragon::UpdateAttackArr()
{
	if (hp > 30)
	{
		for (int i = 0; i < 2; i++)
			atkArr[i] = 0;
		atkArr[2] = 1;
		atkArr[3] = 0;
		for (int i = 4; i < 5; i++)
			atkArr[i] = 0;
		atkArr[5] = 1;
		atkArr[6] = 2;
		atkArr[7] = 1;
	}
	else if (hp <= 30 && hp > 15)
	{
		for (int i = 0; i < 2; i++)
			atkArr[i] = 0;
		atkArr[2] = 1;
		atkArr[3] = 0;
		atkArr[4] = 2;
		atkArr[5] = 0;
		atkArr[6] = 1;
		atkArr[7] = 2;
	}
	else
	{
		for (int i = 0; i < 1; i++)
			atkArr[i] = 0;
		atkArr[2] = 1;
		atkArr[2] = 2;
		atkArr[3] = 0;
		atkArr[4] = 2;
		atkArr[5] = 0;
		atkArr[6] = 2;
		atkArr[7] = 1;
	}
}

void Dragon::DragonRender()
{
	if (isShow && !isDie)
	{
		if (eState != END)
		{
			dHead->aniRender(getMemDC(), dHeadRc.left, dHeadRc.top, dHeadAnim);
			dHand->aniRender(getMemDC(), dHandRc.left, dHandRc.top, dHandAnim);
		}
		else
		{
			dHead->alphaAniRender(getMemDC(), dHeadRc.left, dHeadRc.top, dHeadAnim, alpha);
			dHand->alphaAniRender(getMemDC(), dHandRc.left, dHandRc.top, dHandAnim, alpha);
		}
	}
	//Rectangle(getMemDC(), colRect.left, colRect.top, colRect.right, colRect.bottom);
}
