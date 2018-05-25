#include "stdafx.h"
#include "EnemyManager.h"
#include "Bullet.h"

EnemyManager::EnemyManager()
	:enemyNum(0)
{
	IMAGEMANAGER.addImage("용기사그림자", PathFile("image\\Enemy", "용기사그림자").c_str(), 80, 40, true, RGB(255, 0, 255));
	checkEnemyNum = 1;
	EFFECTMANAGER.addEffect("에너미피격", PathFile("image\\Enemy", "에너미피격").c_str(), 484, 55, 60, 55, 30, 1, 30);

	IMAGEMANAGER.addFrameImage("웨어울프화살", PathFile("image\\Enemy", "웨어울프화살").c_str(), 60, 20, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER.addFrameImage("웨어총알그림자", PathFile("image\\Enemy", "웨어총알그림자").c_str(), 60, 10, 1, 1, true, RGB(255, 0, 255));
	BULLET.BulletSetting("웨어화살", IMAGEMANAGER.findImage("웨어울프화살"), 30, false, 0, 2);
	BULLET.BulletShadowSetting("웨어화살", IMAGEMANAGER.findImage("웨어총알그림자"), RectMake(0, 0, 60, 10), 50);

	IMAGEMANAGER.addFrameImage("스켈레톤검", PathFile("image\\Enemy", "스켈레톤검").c_str(), 60, 60, 1, 1, true, RGB(255, 0, 255));
	BULLET.BulletSetting("스켈검", IMAGEMANAGER.findImage("스켈레톤검"), 30, false, 0, 1);
	BULLET.BulletShadowSetting("스켈검", NULL, RectMake(0, 0, 40, 10), 50);

	BULLET.BulletSetting("민호검", IMAGEMANAGER.findImage("스켈레톤검"), 30, false, 0, 1);
	BULLET.BulletShadowSetting("민호검", NULL, RectMake(0, 0, 120, 20), 50);

	BULLET.BulletSetting("용기사검0", IMAGEMANAGER.findImage("스켈레톤검"), 30, false, 0, 1);
	BULLET.BulletShadowSetting("용기사검0", NULL, RectMake(0, 0, 200, 20), 50);

	IMAGEMANAGER.addFrameImage("용기사검", PathFile("image\\Enemy", "용기사칼").c_str(), 1136, 70, 16, 1, true, RGB(255, 0, 255));
	BULLET.BulletSetting("용기사검", IMAGEMANAGER.findImage("용기사검"), 30, true, 20, 1);
	BULLET.BulletShadowSetting("용기사검", IMAGEMANAGER.findImage("웨어총알그림자"), RectMake(0, 0, 60, 10), 70);

	for (int i = 0; i < 30; i++)
	{
		ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("웨어화살")[i]);
		ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("스켈검")[i]);
		ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("용기사검")[i]);
		ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("용기사검0")[i]);
	}
}


EnemyManager::~EnemyManager()
{
}

void EnemyManager::InputEnemy(ENEMYTYPE eType, int enemyNum)
{
	vector<Enemy*>	enemyVec;

	for (int i = 0; i < enemyNum; i++)
	{
		switch (eType)
		{
		case WAREWOLF:
		{
			Enemy*enemy = new Warewolf(eType);
			enemy->Init();
			enemyVec.push_back(enemy);

		}
		break;
		case SKELETON:
		{
			Enemy*enemy = new Skeleton(eType);
			enemy->Init();
			enemyVec.push_back(enemy);
		}
		break;
		case MINO:
		{
			Enemy*enemy = new Mino(eType);
			enemy->Init();
			enemyVec.push_back(enemy);
		}
		break;
		case DRAGONKNIGHT:
		{
			Enemy*enemy = new DragonKnight(eType);
			enemy->Init();
			enemyVec.push_back(enemy);
		}
		break;
		case BLACKARCHOR:
		{
			Enemy*enemy = new BlackArchor(eType);
			enemy->Init();
			enemyVec.push_back(enemy);
		}
		break;
		}
	}
	enemyMap[eType] = enemyVec;
	enemyIdxMap[eType] = 0;

	enemyMapIter emIter = enemyMap.begin();
	for (; emIter != enemyMap.end(); emIter++)
	{
		for (int i = 0; i<emIter->second.size(); i++)
		{
			ZORDER.InputObj(emIter->second[i]);
		}
	}
}


void EnemyManager::Update(PlayerManager*pm)
{
	enemyMapIter emIter = enemyMap.begin();
	for (; emIter != enemyMap.end(); emIter++)
	{
		for (int i = 0; i<emIter->second.size(); i++)
		{
			if (emIter->second[i]->getShowState() && !emIter->second[i]->getDie())
			{
				emIter->second[i]->Update(pm);
			}
		}
	}
	checkEnemyNum = DieUpdate();
	EnemyCollision();
}

void EnemyManager::Release()
{
	enemyMapIter emIter = enemyMap.begin();
	for (; emIter != enemyMap.end(); emIter++)
	{
		for (int i = 0; i<emIter->second.size(); i++)
		{
			if (emIter->second[i]->getShowState())
			{
				emIter->second[i]->Release();
				SAFE_DELETE(emIter->second[i]);
			}
		}
		emIter->second.clear();
	}
	enemyMap.clear();
	enemyNum = 0;
}

void EnemyManager::ShowEnemy(ENEMYTYPE eType, float x, float y, ENEMYSTATE eState)
{
	AllDieInit();
	enemyMapIter emIter = enemyMap.find(eType);

	emIter->second[enemyIdxMap[eType]]->Init(x, y, eState);
	emIter->second[enemyIdxMap[eType]]->getShowState() = true;
	emIter->second[enemyIdxMap[eType]]->getDie() = false;

	enemyIdxMap[eType]++;
	enemyNum++;
	initEnemyNum = enemyNum;

	if (enemyIdxMap[eType] > emIter->second.size() - 1)
		enemyIdxMap[eType] = 0;
}

int EnemyManager::DieUpdate()
{
	enemyNum = initEnemyNum;
	enemyMapIter emIter = enemyMap.begin();
	for (; emIter != enemyMap.end(); emIter++)
	{
		for (int i = 0; i<emIter->second.size(); i++)
		{
			if (emIter->second[i]->getDie())
			{
				enemyNum--;
			}
		}
	}
	return enemyNum;
}

void EnemyManager::EnemyCollision()
{
	enemyMapIter emIter = enemyMap.begin();

	for (; emIter != enemyMap.end(); emIter++)
	{
		for (int i = 0; i < emIter->second.size(); i++)
		{
			if (!emIter->second[i]->getShowState() || emIter->second[i]->getDie())continue;

			for (int j = 0; j < BULLET.GetBulletVec("Warrior_Weapon_1_B").size(); j++)
			{
				if (!BULLET.GetBulletVec("Warrior_Weapon_1_B")[j]->isShot)continue;
				RECT rc;
				if (IntersectRect(&rc, &emIter->second[i]->getRc(), &BULLET.GetBulletVec("Warrior_Weapon_1_B")[j]->getRc()))
				{
					int randomSet = RND.GetFromTo(-10, 11);
					EFFECTMANAGER.play("에너미피격", GetCenterPos(emIter->second[i]->getRc()).x + randomSet, GetCenterPos(emIter->second[i]->getRc()).y -40);
					emIter->second[i]->Damaged();
					BULLET.Destroy("Warrior_Weapon_1_B", j);
					break;
				}
			}
		}
	}
}

void EnemyManager::AllDieInit()
{
	enemyMapIter emIter = enemyMap.begin();
	for (; emIter != enemyMap.end(); emIter++)
	{
		for (int i = 0; i<emIter->second.size(); i++)
		{
			if (!emIter->second[i]->getDie())continue;

			emIter->second[i]->getDie() = false;
		}
	}
}

