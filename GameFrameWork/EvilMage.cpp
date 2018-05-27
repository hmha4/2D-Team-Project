#include "stdafx.h"
#include "EvilMage.h"
#include "Bullet.h"

EvilMage::EvilMage(ENEMYTYPE _eType)
	:Enemy(_eType)
{
	IMAGEMANAGER.addFrameImage("´ÙÅ©¸ÞÀÌÁö", PathFile("image\\Enemy", "¸¶¹ý»ç").c_str(), 1294, 720, 10, 6, true, RGB(255, 0, 255));
	EFFECTMANAGER.addEffect("¸¶Á×", PathFile("image\\Enemy", "¸¶¹ý»çÁ×À½").c_str(), 1425, 84, 95, 84, 60, 1, 40);
}


EvilMage::~EvilMage()
{
}

HRESULT EvilMage::Init(int x, int y, ENEMYSTATE eState)
{
	int Idle[] = { 0,1,2 };
	ANIMATIONKEY.addArrayFrameAnimation("emIdle", "´ÙÅ©¸ÞÀÌÁö", Idle, 3, 5, true);

	int leftMove[] = { 18,17,16 };
	ANIMATIONKEY.addArrayFrameAnimation("emLeftMove", "´ÙÅ©¸ÞÀÌÁö", leftMove, 3, 6, true);

	int rightMove[] = { 3,4,5 };
	ANIMATIONKEY.addArrayFrameAnimation("emRightMove", "´ÙÅ©¸ÞÀÌÁö", rightMove, 3, 6, true);

	int leftAttack[] = { 15,14,13,29,28,27,26,25 };
	ANIMATIONKEY.addArrayFrameAnimation("emLeftAttack", "´ÙÅ©¸ÞÀÌÁö", leftAttack, 8, 12, false);

	int rightAttack[] = { 6,7,8,20,21,22,23,24 };
	ANIMATIONKEY.addArrayFrameAnimation("emRightAttack", "´ÙÅ©¸ÞÀÌÁö", rightAttack, 8, 12, false);

	int leftAttack2[] = {15,14,13,48,47,46,45,44,43,42,41,40 };
	ANIMATIONKEY.addArrayFrameAnimation("emLeftAttack2", "´ÙÅ©¸ÞÀÌÁö", leftAttack2, 12,14, false);

	int rightAttack2[] = { 6,7,8,30,31,32,33,34,35,36,37,38 };
	ANIMATIONKEY.addArrayFrameAnimation("emRightAttack2", "´ÙÅ©¸ÞÀÌÁö", rightAttack2, 12, 14, false);

	int Attack3[] = { 50,51,52 };
	ANIMATIONKEY.addArrayFrameAnimation("emAttack3", "´ÙÅ©¸ÞÀÌÁö", Attack3, 3, 8, true);

	int leftDie[] = { 56,55 };
	ANIMATIONKEY.addArrayFrameAnimation("emLeftDie", "´ÙÅ©¸ÞÀÌÁö", leftDie, 2, 9, true);

	int rightDie[] = {53,54 };
	ANIMATIONKEY.addArrayFrameAnimation("emRightDie", "´ÙÅ©¸ÞÀÌÁö", rightDie, 2, 9, true);

	img = IMAGEMANAGER.findImage("´ÙÅ©¸ÞÀÌÁö");
	Enemy::Init(x, y, eState);
	anim = new animation;

	*anim = *ANIMATIONKEY.findAnimation("emIdle");
	anim->start();
	showTime = 0;
	atkIdx = 0;
	shot1Time = 0;
	setangle = 0;
	atk2Angle = 0;
	atk2X = 0;
	atk2Y = 0;
	shot2Time = 0;
	setangle2 = 0;
	hp = 30;
	shot3Time = 0;
	dieTime = 0;
	return S_OK;
}

void EvilMage::Release()
{
}

void EvilMage::EnemyUpdate(PlayerManager * pm)
{
	UpdateAttackArr();
	anim->frameUpdate(TIMEMANAGER.getElapsedTime());
	switch (eState)
	{
		case LEFT_IDLE:
		{
			showTime += TIMEMANAGER.getElapsedTime();
			
			posX += cosf(3 * PI / 2) * 2;
			posY += -sinf(3 * PI / 2) * 2;
			rc = RectMakeCenter(posX , posY, img->GetFrameWidth(), img->GetFreamHeight());
			shadowRc = RectMake(rc.right - 105, rc.bottom - img->GetFreamHeight() / 3 + 15, 80, img->GetFreamHeight() / 3);

			if (showTime > 3)
			{
				eState = LEFT_MOVE;
				showTime = 0;
				*anim = *ANIMATIONKEY.findAnimation("emLeftMove");
				anim->start();
			}
		}
		break;
		case LEFT_ATTACK:
		{
			DieEnemy();
			showTime += TIMEMANAGER.getElapsedTime();
			if (!anim->isPlay())
			{
				shot1Time += TIMEMANAGER.getElapsedTime();
				static int ypos = 0;
				static int yvalue = 10;
				
				if (showTime < 4)
				{
					if (shot1Time > 0.3)
					{
						SOUNDMANAGER.play("39DragonKnightKnife");
						BULLET.Shot("¸¶ÃÑ1", posX, posY + ypos, PI, 0, 5, 0);
						BULLET.Shot("¸¶ÃÑ1", posX, posY + 70 + ypos, PI, 0, 5, 0);
						BULLET.Shot("¸¶ÃÑ1", posX, posY - 70 + ypos, PI, 0, 5, 0);
						shot1Time = 0;
						ypos += yvalue;

						if (ypos > 40 || ypos < -20)
							yvalue *= -1;
					}
				}
				else
				{
					ypos = 0;
					yvalue = 10;
				}
			}
			if (showTime > 6)
			{
				if (DATABASE.LoadData("1P2P") == 1)
					playerNumber = RND.GetFromTo(0, 2);
				if (GetCenterPos(pm->GetPlayer(playerNumber)->getRc()).x > GetCenterPos(shadowRc).x)
				{
					eState = RIGHT_MOVE;
					*anim = *ANIMATIONKEY.findAnimation("emRightMove");
					anim->start();
				}
				else
				{
					eState = LEFT_MOVE;
					*anim = *ANIMATIONKEY.findAnimation("emLeftMove");
					anim->start();
				}
				shot1Time = 0;
				showTime = 0;
			}
		}
		break;
		case RIGHT_ATTACK:
		{
			DieEnemy();
			showTime += TIMEMANAGER.getElapsedTime();
			if (!anim->isPlay())
			{
				shot1Time += TIMEMANAGER.getElapsedTime();
				static int ypos = 0;
				static int yvalue = 10;

				if (showTime < 4)
				{
					if (shot1Time > 0.3)
					{
						SOUNDMANAGER.play("39DragonKnightKnife");
						BULLET.Shot("¸¶ÃÑ1", posX, posY + ypos, 0, 0, 5, 0);
						BULLET.Shot("¸¶ÃÑ1", posX, posY + 70 + ypos, 0, 0, 5, 0);
						BULLET.Shot("¸¶ÃÑ1", posX, posY - 70 + ypos, 0, 0, 5, 0);
						shot1Time = 0;
						ypos += yvalue;

						if (ypos > 40 || ypos < -20)
							yvalue *= -1;
					}
				}
				else
				{
					ypos = 0;
					yvalue = 10;
				}
			}
			if (showTime > 6)
			{
				if (DATABASE.LoadData("1P2P") == 1)
					playerNumber = RND.GetFromTo(0, 2);
				if (GetCenterPos(pm->GetPlayer(playerNumber)->getRc()).x > GetCenterPos(shadowRc).x)
				{
					eState = RIGHT_MOVE;
					*anim = *ANIMATIONKEY.findAnimation("emRightMove");
					anim->start();
				}
				else
				{
					eState = LEFT_MOVE;
					*anim = *ANIMATIONKEY.findAnimation("emLeftMove");
					anim->start();
				}
				shot1Time = 0;
				showTime = 0;
			}
		}
		break;
		case LEFT_ATTACK2:
		{
			DieEnemy();
			if (posX < WINSIZEX / 2 + 200)
			{
				posX += cosf(setangle) * 4;
				posY += -sinf(setangle) * 4;
				rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
				shadowRc = RectMake(rc.right - 105, rc.bottom - img->GetFreamHeight() / 3 + 15, 80, img->GetFreamHeight() / 3);
				atk2X = shadowRc.left;
				atk2Y = shadowRc.top - 30;
			}
			else
			{
				shot2Time += TIMEMANAGER.getElapsedTime();

				if (shot2Time > 5)
				{
					static float wTime = 0;
					wTime += TIMEMANAGER.getElapsedTime();

					if (wTime > 2)
					{
						if (DATABASE.LoadData("1P2P") == 1)
							playerNumber = RND.GetFromTo(0, 2);
						if (GetCenterPos(pm->GetPlayer(playerNumber)->getRc()).x > GetCenterPos(shadowRc).x)
						{
							eState = RIGHT_MOVE;
							*anim = *ANIMATIONKEY.findAnimation("emRightMove");
							anim->start();
						}
						else
						{
							eState = LEFT_MOVE;
							*anim = *ANIMATIONKEY.findAnimation("emLeftMove");
							anim->start();
						}
						shot2Time = 0;
						wTime = 0;
					}
				}
				else
				{
					static float at2time = 0;
					at2time += TIMEMANAGER.getElapsedTime();

					if (at2time > 0.3)
					{
						for (int i = 0; i < BULLET.GetBulletVec("¸¶ÃÑ2").size(); i++)
						{
							if (!BULLET.GetBulletVec("¸¶ÃÑ2")[i]->isShot)continue;
							if (i == 0)
							{
								atk2Angle = getAngle(GetCenterPos(shadowRc).x, GetCenterPos(rc).y,
									GetCenterPos(pm->GetPlayer(playerNumber)->getRc()).x, GetCenterPos(pm->GetPlayer(playerNumber)->getRc()).y);
							}
							else
							{
								atk2Angle = getAngle(GetCenterPos(BULLET.GetBulletVec("¸¶ÃÑ2")[i]->shadowRc).x, GetCenterPos(BULLET.GetBulletVec("¸¶ÃÑ2")[i]->shadowRc).y,
									GetCenterPos(pm->GetPlayer(playerNumber)->getRc()).x, GetCenterPos(pm->GetPlayer(playerNumber)->getRc()).y);
							}
						}
						atk2X += cosf(atk2Angle) * 40;
						atk2Y += -sinf(atk2Angle) * 40;
						BULLET.Shot("¸¶ÃÑ2", atk2X, atk2Y, 0, 0, 0, 0);
						SOUNDMANAGER.play("39DragonKnightKnife");
						at2time = 0;
					}
				}
			}
		}
		break;
		case RIGHT_ATTACK2:
		{
			DieEnemy();
			if (posX > WINSIZEX / 2 - 200)
			{
				posX += cosf(setangle) * 4;
				posY += -sinf(setangle) * 4;
				rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
				shadowRc = RectMake(rc.right - 105, rc.bottom - img->GetFreamHeight() / 3 + 15, 80, img->GetFreamHeight() / 3);
				atk2X = shadowRc.right;
				atk2Y = shadowRc.top - 30;
			}
			else
			{
				shot2Time += TIMEMANAGER.getElapsedTime();

				if (shot2Time > 5)
				{
					static float wTime = 0;
					wTime += TIMEMANAGER.getElapsedTime();

					if (wTime > 2)
					{
						if (DATABASE.LoadData("1P2P") == 1)
							playerNumber = RND.GetFromTo(0, 2);
						if (GetCenterPos(pm->GetPlayer(playerNumber)->getRc()).x > GetCenterPos(shadowRc).x)
						{
							eState = RIGHT_MOVE;
							*anim = *ANIMATIONKEY.findAnimation("emRightMove");
							anim->start();
						}
						else
						{
							eState = LEFT_MOVE;
							*anim = *ANIMATIONKEY.findAnimation("emLeftMove");
							anim->start();
						}
						shot2Time = 0;
						wTime = 0;
					}
				}
				else
				{
					static float at2time = 0;
					at2time += TIMEMANAGER.getElapsedTime();

					if (at2time > 0.3)
					{
						for (int i = 0; i < BULLET.GetBulletVec("¸¶ÃÑ2").size(); i++)
						{
							if (!BULLET.GetBulletVec("¸¶ÃÑ2")[i]->isShot)continue;
							if (i == 0)
							{
								atk2Angle = getAngle(GetCenterPos(shadowRc).x, GetCenterPos(rc).y,
									GetCenterPos(pm->GetPlayer(playerNumber)->getRc()).x, GetCenterPos(pm->GetPlayer(playerNumber)->getRc()).y);
							}
							else
							{
								atk2Angle = getAngle(GetCenterPos(BULLET.GetBulletVec("¸¶ÃÑ2")[i]->shadowRc).x, GetCenterPos(BULLET.GetBulletVec("¸¶ÃÑ2")[i]->shadowRc).y,
									GetCenterPos(pm->GetPlayer(playerNumber)->getRc()).x, GetCenterPos(pm->GetPlayer(playerNumber)->getRc()).y);
							}
						}
						atk2X += cosf(atk2Angle) * 40;
						atk2Y += -sinf(atk2Angle) * 40;
						BULLET.Shot("¸¶ÃÑ2", atk2X, atk2Y, 0, 0, 0, 0);
						SOUNDMANAGER.play("39DragonKnightKnife");
						at2time = 0;
					}
				}
			}
		}
		break;
		case LEFT_ATTACK3:
		{
			DieEnemy();
			if (posY > 100)
			{
				if (shot3Time > 5)
				{
					static float exitTime = 0;
					exitTime += TIMEMANAGER.getElapsedTime();

					if (exitTime > 1)
					{
						if (DATABASE.LoadData("1P2P") == 1)
							playerNumber = RND.GetFromTo(0, 2);
						if (GetCenterPos(pm->GetPlayer(playerNumber)->getRc()).x > GetCenterPos(shadowRc).x)
						{
							eState = RIGHT_MOVE;
							*anim = *ANIMATIONKEY.findAnimation("emRightMove");
							anim->start();
						}
						else
						{
							eState = LEFT_MOVE;
							*anim = *ANIMATIONKEY.findAnimation("emLeftMove");
							anim->start();
						}
						exitTime = 0;
						shot3Time = 0;
					}
					posY += 3;
					rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
					shadowRc = RectMake(rc.right - 105, rc.bottom - img->GetFreamHeight() / 3 + 15, 80, img->GetFreamHeight() / 3);
				}
				else
				{
					posX += cosf(setangle2) * 4;
					posY += -sinf(setangle2) * 4;
					rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
					shadowRc = RectMake(rc.right - 105, rc.bottom - img->GetFreamHeight() / 3 + 15, 80, img->GetFreamHeight() / 3);
				}
			}
			else
			{
				shot3Time += TIMEMANAGER.getElapsedTime();

				if (shot3Time < 5)
				{
					static float t = 0;
					t += TIMEMANAGER.getElapsedTime();

					if (t > 0.8)
					{
						static int power1 = 100;
						static int power2 = 200;
						BULLET.Shot("¸¶ÃÑ3", posX, posY, 3 * PI / 2, 0, 10, 0, posY + power1);
						BULLET.Shot("¸¶ÃÑ3", posX, posY, 3 * PI / 2 + PI / 4, 0, 10, 0, posY + power2);
						BULLET.Shot("¸¶ÃÑ3", posX, posY, 3 * PI / 2 - PI / 4, 0, 10, 0, posY + power2);
						BULLET.Shot("¸¶ÃÑ3", posX, posY, 3 * PI / 2 + PI / 3, 0, 10, 0, posY + power1);
						BULLET.Shot("¸¶ÃÑ3", posX, posY, 3 * PI / 2 - PI / 3, 0, 10, 0, posY + power1);
						t = 0;
						int num = power1;
						power1 = power2;
						power2 = num;
					}
				}
				if (shot3Time > 5)
				{
					posY += 3;
					rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
					shadowRc = RectMake(rc.right - 105, rc.bottom - img->GetFreamHeight() / 3 + 15, 80, img->GetFreamHeight() / 3);
				}
			}
		}
		break;
		case RIGHT_ATTACK3:
		{
			DieEnemy();
			if (posY > 100)
			{
				if (shot3Time > 5)
				{
					static float exitTime = 0;
					exitTime += TIMEMANAGER.getElapsedTime();

					if (exitTime > 1)
					{
						if (DATABASE.LoadData("1P2P") == 1)
							playerNumber = RND.GetFromTo(0, 2);
						if (GetCenterPos(pm->GetPlayer(playerNumber)->getRc()).x > GetCenterPos(shadowRc).x)
						{
							eState = RIGHT_MOVE;
							*anim = *ANIMATIONKEY.findAnimation("emRightMove");
							anim->start();
						}
						else
						{
							eState = LEFT_MOVE;
							*anim = *ANIMATIONKEY.findAnimation("emLeftMove");
							anim->start();
						}
						exitTime = 0;
						shot3Time = 0;
					}
					posY += 3;
					rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
					shadowRc = RectMake(rc.right - 105, rc.bottom - img->GetFreamHeight() / 3 + 15, 80, img->GetFreamHeight() / 3);
				}
				else
				{
					posX += cosf(setangle2) * 4;
					posY += -sinf(setangle2) * 4;
					rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
					shadowRc = RectMake(rc.right - 105, rc.bottom - img->GetFreamHeight() / 3 + 15, 80, img->GetFreamHeight() / 3);
				}
			}
			else
			{
				shot3Time += TIMEMANAGER.getElapsedTime();

				if (shot3Time < 5)
				{
					static float t = 0;
					t += TIMEMANAGER.getElapsedTime();

					if (t > 0.8)
					{
						static int power1 = 100;
						static int power2 = 200;
						BULLET.Shot("¸¶ÃÑ3", posX, posY, 3 * PI / 2, 0, 10, 0, posY + power1);
						BULLET.Shot("¸¶ÃÑ3", posX, posY, 3 * PI / 2 + PI / 4, 0, 10, 0, posY + power2);
						BULLET.Shot("¸¶ÃÑ3", posX, posY, 3 * PI / 2 - PI / 4, 0, 10, 0, posY + power2);
						BULLET.Shot("¸¶ÃÑ3", posX, posY, 3 * PI / 2 + PI / 3, 0, 10, 0, posY + power1);
						BULLET.Shot("¸¶ÃÑ3", posX, posY, 3 * PI / 2 - PI / 3, 0, 10, 0, posY + power1);
						t = 0;
						int num = power1;
						power1 = power2;
						power2 = num;
					}
				}
				if (shot3Time > 5)
				{
					posY += 3;
					rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
					shadowRc = RectMake(rc.right - 105, rc.bottom - img->GetFreamHeight() / 3 + 15, 80, img->GetFreamHeight() / 3);
				}
			}
		}
		break;
		case LEFT_MOVE:
		{
			DieEnemy();
			angle = getAngle(GetCenterPos(shadowRc).x, GetCenterPos(shadowRc).y,
				GetCenterPos(pm->GetPlayer(playerNumber)->getRc()).x, GetCenterPos(pm->GetPlayer(playerNumber)->getRc()).y);

			posX += cosf(angle) * 2;
			posY += -sinf(angle) * 2;
			rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
			shadowRc = RectMake(rc.right - 105, rc.bottom - img->GetFreamHeight() / 3 + 15, 80, img->GetFreamHeight() / 3);

			if (GetCenterPos(pm->GetPlayer(playerNumber)->getRc()).x >= GetCenterPos(shadowRc).x)
			{
				eState = RIGHT_MOVE;
				*anim = *ANIMATIONKEY.findAnimation("emRightMove");
				anim->start();
			}

			if (GetCenterPos(pm->GetPlayer(playerNumber)->getRc()).y + 10>GetCenterPos(shadowRc).y&&
				GetCenterPos(pm->GetPlayer(playerNumber)->getRc()).y - 10<GetCenterPos(shadowRc).y)
			{
				if (atkArr[atkIdx] == 0)
				{
					if (getDistance(GetCenterPos(pm->GetPlayer(playerNumber)->getRc()).x, GetCenterPos(pm->GetPlayer(playerNumber)->getRc()).y,
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
					if (getDistance(GetCenterPos(pm->GetPlayer(playerNumber)->getRc()).x, GetCenterPos(pm->GetPlayer(playerNumber)->getRc()).y,
						GetCenterPos(shadowRc).x, GetCenterPos(shadowRc).y) < 100)
					{
						RandomAttack(atkArr[atkIdx]);
						atkIdx++;
						if (atkIdx > 7)
							atkIdx = 0;
					}
				}
				else
				{
					if (getDistance(GetCenterPos(pm->GetPlayer(playerNumber)->getRc()).x, GetCenterPos(pm->GetPlayer(playerNumber)->getRc()).y,
						GetCenterPos(shadowRc).x, GetCenterPos(shadowRc).y) < 70)
					{
						RandomAttack(atkArr[atkIdx]);
						atkIdx++;
						if (atkIdx > 7)
							atkIdx = 0;
					}
				}
			}
		}
		break;
		case RIGHT_MOVE:
		{
			DieEnemy();
			angle = getAngle(GetCenterPos(shadowRc).x, GetCenterPos(shadowRc).y,
				GetCenterPos(pm->GetPlayer(playerNumber)->getRc()).x, GetCenterPos(pm->GetPlayer(playerNumber)->getRc()).y);

			posX += cosf(angle) * 2;
			posY += -sinf(angle) * 2;
			rc = RectMakeCenter(posX, posY, img->GetFrameWidth(), img->GetFreamHeight());
			shadowRc = RectMake(rc.right - 105, rc.bottom - img->GetFreamHeight() / 3 + 15, 80, img->GetFreamHeight() / 3);

			if (GetCenterPos(pm->GetPlayer(playerNumber)->getRc()).x < GetCenterPos(shadowRc).x)
			{
				eState = LEFT_MOVE;
				*anim = *ANIMATIONKEY.findAnimation("emLeftMove");
				anim->start();
			}

			if (GetCenterPos(pm->GetPlayer(playerNumber)->getRc()).y + 10>GetCenterPos(shadowRc).y&&
				GetCenterPos(pm->GetPlayer(playerNumber)->getRc()).y - 10<GetCenterPos(shadowRc).y)
			{
				if (atkArr[atkIdx] == 0)
				{
					if (getDistance(GetCenterPos(pm->GetPlayer(playerNumber)->getRc()).x, GetCenterPos(pm->GetPlayer(playerNumber)->getRc()).y,
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
					if (getDistance(GetCenterPos(pm->GetPlayer(playerNumber)->getRc()).x, GetCenterPos(pm->GetPlayer(playerNumber)->getRc()).y,
						GetCenterPos(shadowRc).x, GetCenterPos(shadowRc).y) < 100)
					{
						RandomAttack(atkArr[atkIdx]);
						atkIdx++;
						if (atkIdx > 7)
							atkIdx = 0;
					}
				}
				else
				{
					if (getDistance(GetCenterPos(pm->GetPlayer(playerNumber)->getRc()).x, GetCenterPos(pm->GetPlayer(playerNumber)->getRc()).y,
						GetCenterPos(shadowRc).x, GetCenterPos(shadowRc).y) < 70)
					{
						RandomAttack(atkArr[atkIdx]);
						atkIdx++;
						if (atkIdx > 7)
							atkIdx = 0;
					}
				}
			}
		}
		break;
		case LEFT_DIE:
		{
			dieTime += TIMEMANAGER.getElapsedTime();
			if (dieTime > 3)
			{
				EFFECTMANAGER.play("¸¶Á×", posX, posY);
				isDie = true;
				isShow = false;
			}
		}
		break;
		case RIGHT_DIE:
		{
			dieTime += TIMEMANAGER.getElapsedTime();
			if (dieTime > 3)
			{
				EFFECTMANAGER.play("¸¶Á×", posX, posY);
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

void EvilMage::DieEnemy()
{
	if (hp <= 0)
	{
		SOUNDMANAGER.play("49DarkMageDie");
		if (eState == LEFT_IDLE || eState == LEFT_ATTACK || eState == LEFT_MOVE || eState == LEFT_ATTACK3 || eState == LEFT_ATTACK2)
		{
			eState = LEFT_DIE;
			*anim = *ANIMATIONKEY.findAnimation("emLeftDie");
			anim->start();
		}
		else if (eState == RIGHT_IDLE || eState == RIGHT_ATTACK || eState == RIGHT_MOVE || eState == RIGHT_ATTACK3 || eState == LEFT_ATTACK2)
		{
			eState = RIGHT_DIE;
			*anim = *ANIMATIONKEY.findAnimation("emRightDie");
			anim->start();
		}
		anim->start();
	}
}

void EvilMage::Damaged()
{
	hp--;
}

void EvilMage::UpdateAttackArr()
{
	if (hp > 20)
	{
		for (int i = 0; i < 3; i++)
			atkArr[i] = 0;
		atkArr[3] = 1;
		for (int i = 4; i < 6; i++)
			atkArr[i] = 0;
		atkArr[6] = 2;
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
void EvilMage::RandomAttack(int num)
{
	if (eState == LEFT_MOVE)
	{
		if (num == 0)
		{
			eState = LEFT_ATTACK;
			*anim = *ANIMATIONKEY.findAnimation("emLeftAttack");
			anim->start();
		}
		else if (num == 1)
		{
			eState = LEFT_ATTACK2;
			*anim = *ANIMATIONKEY.findAnimation("emLeftAttack2");
			anim->start();
			setangle = getAngle(posX, posY, WINSIZEX / 2 + 200, WINSIZEY / 2);
		}
		else
		{
			SOUNDMANAGER.play("50DarkMageFly");
			eState = LEFT_ATTACK3;
			*anim = *ANIMATIONKEY.findAnimation("emAttack3");
			anim->start();
			setangle2 = getAngle(posX, posY, WINSIZEX / 2, 100);
		}
	}
	else if (eState == RIGHT_MOVE)
	{
		if (num == 0)
		{
			eState = RIGHT_ATTACK;
			*anim = *ANIMATIONKEY.findAnimation("emRightAttack");
			anim->start();
		}
		else if (num == 1)
		{
			eState = RIGHT_ATTACK2;
			*anim = *ANIMATIONKEY.findAnimation("emRightAttack2");
			anim->start();
			setangle = getAngle(posX, posY, WINSIZEX / 2 - 200, WINSIZEY / 2);
		}
		else
		{
			SOUNDMANAGER.play("50DarkMageFly");
			eState = RIGHT_ATTACK3;
			*anim = *ANIMATIONKEY.findAnimation("emAttack3");
			anim->start();
			setangle2 = getAngle(posX, posY, WINSIZEX / 2, 100);
		}
	}
}