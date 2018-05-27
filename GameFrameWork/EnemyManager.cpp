#include "stdafx.h"
#include "EnemyManager.h"
#include "Bullet.h"
#include "SkillIce.h"
#include "SkillWarrior.h"
#include "SkillFire.h"

EnemyManager::EnemyManager()
	:enemyNum(0)
{
	IMAGEMANAGER.addImage("용기사그림자", PathFile("image\\Enemy", "용기사그림자").c_str(), 80, 40, true, RGB(255, 0, 255));
	checkEnemyNum = 1;

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
	BULLET.BulletSetting("용기사검", IMAGEMANAGER.findImage("용기사검"), 30, true, 40, 1);
	BULLET.BulletShadowSetting("용기사검", IMAGEMANAGER.findImage("웨어총알그림자"), RectMake(0, 0, 60, 10), 70);

	IMAGEMANAGER.addFrameImage("블랙아처화살", PathFile("image\\Enemy", "블랙아처화살").c_str(), 80, 52, 1, 2, true, RGB(255, 0, 255));
	BULLET.BulletSetting("블랙아처화살", IMAGEMANAGER.findImage("블랙아처화살"), 30, 0, 0, 2);
	BULLET.BulletShadowSetting("블랙아처화살", IMAGEMANAGER.findImage("웨어총알그림자"), RectMake(0, 0, 60, 10), 50);

	IMAGEMANAGER.addFrameImage("외눈거인돌", PathFile("image\\Enemy", "외눈거인돌").c_str(), 60, 83, 1, 2, true, RGB(255, 0, 255));
	BULLET.BulletSetting("외돌", IMAGEMANAGER.findImage("외눈거인돌"), 30, 0, 0, 2);
	BULLET.BulletShadowSetting("외돌", IMAGEMANAGER.findImage("웨어총알그림자"), RectMake(0, 0, 60, 10), 50);

	IMAGEMANAGER.addFrameImage("마총1", PathFile("image\\Enemy", "마법사총1").c_str(), 209, 60, 4, 1, true, RGB(255, 0, 255));
	BULLET.BulletSetting("마총1", IMAGEMANAGER.findImage("마총1"), 30, true, 20, 1);
	BULLET.BulletShadowSetting("마총1", IMAGEMANAGER.findImage("웨어총알그림자"), RectMake(0, 0, 60, 10), 70);

	IMAGEMANAGER.addFrameImage("마총2", PathFile("image\\Enemy", "마법사총2").c_str(), 187, 140, 5, 1, true, RGB(255, 0, 255));
	BULLET.BulletSetting("마총2", IMAGEMANAGER.findImage("마총2"), 30, true, 10, 1,false);
	BULLET.BulletShadowSetting("마총2", NULL, RectMake(0, 0, 60, 10), 70);

	IMAGEMANAGER.addFrameImage("마총3", PathFile("image\\Enemy", "마법사총3").c_str(), 180, 60, 3, 1, true, RGB(255, 0, 255));
	BULLET.BulletSetting("마총3", IMAGEMANAGER.findImage("마총3"), 30, true, 10, 1);
	BULLET.BulletShadowSetting("마총3", IMAGEMANAGER.findImage("웨어총알그림자"), RectMake(0, 0, 60, 10), 70);

	IMAGEMANAGER.addFrameImage("드브", PathFile("image\\Enemy", "드래곤브레스").c_str(), 1200, 132, 4, 1, true, RGB(255, 0, 255));
	BULLET.BulletSetting("드브", IMAGEMANAGER.findImage("드브"), 30, true, 20, 1,false);
	BULLET.BulletShadowSetting("드브", NULL, RectMake(0, 0, 300, 80), 60);

	IMAGEMANAGER.addFrameImage("드총", PathFile("image\\Enemy", "드래곤총").c_str(), 240, 60, 4, 1, true, RGB(255, 0, 255));
	BULLET.BulletSetting("드총", IMAGEMANAGER.findImage("드총"), 30, true, 60, 1);
	BULLET.BulletShadowSetting("드총", IMAGEMANAGER.findImage("웨어총알그림자"), RectMake(0, 0, 60, 10), 70);

	EFFECTMANAGER.addEffect("마3폭", PathFile("image\\Enemy", "마총3폭발").c_str(), 400, 60, 80, 60, 30, 1, 20);
	EFFECTMANAGER.addEffect("돌폭발", PathFile("image\\Enemy", "돌폭발이펙트").c_str(), 420, 100, 84, 100, 20, 1, 20);
	for (int i = 0; i < 30; i++)
	{
		ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("웨어화살")[i]);
		ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("스켈검")[i]);
		ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("용기사검")[i]);
		ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("용기사검0")[i]);
		ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("블랙아처화살")[i]);
		ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("외돌")[i]);
		ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("마총1")[i]);
		ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("마총2")[i]);
		ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("마총3")[i]);
		ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("드브")[i]);
		ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("드총")[i]);
	}

	_enemyUI = new EnemyUI;
	//보스체력 초기화
	//			maxHP, 에너지바 너비, 이름 입력
	_enemyUI->Init(90, 400, "enemy");
	ZORDER.InputObj(_enemyUI);

	//보스체력 활성화
	_enemyUI->SetDrawHP(true);
}

EnemyManager::EnemyManager(string bossName)
	:enemyNum(0)
{
	IMAGEMANAGER.addImage("용기사그림자", PathFile("image\\Enemy", "용기사그림자").c_str(), 80, 40, true, RGB(255, 0, 255));
	checkEnemyNum = 1;

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
	BULLET.BulletSetting("용기사검", IMAGEMANAGER.findImage("용기사검"), 30, true, 40, 1);
	BULLET.BulletShadowSetting("용기사검", IMAGEMANAGER.findImage("웨어총알그림자"), RectMake(0, 0, 60, 10), 70);

	IMAGEMANAGER.addFrameImage("블랙아처화살", PathFile("image\\Enemy", "블랙아처화살").c_str(), 80, 52, 1, 2, true, RGB(255, 0, 255));
	BULLET.BulletSetting("블랙아처화살", IMAGEMANAGER.findImage("블랙아처화살"), 30, 0, 0, 2);
	BULLET.BulletShadowSetting("블랙아처화살", IMAGEMANAGER.findImage("웨어총알그림자"), RectMake(0, 0, 60, 10), 50);

	IMAGEMANAGER.addFrameImage("외눈거인돌", PathFile("image\\Enemy", "외눈거인돌").c_str(), 60, 83, 1, 2, true, RGB(255, 0, 255));
	BULLET.BulletSetting("외돌", IMAGEMANAGER.findImage("외눈거인돌"), 30, 0, 0, 2);
	BULLET.BulletShadowSetting("외돌", IMAGEMANAGER.findImage("웨어총알그림자"), RectMake(0, 0, 60, 10), 50);

	IMAGEMANAGER.addFrameImage("마총1", PathFile("image\\Enemy", "마법사총1").c_str(), 209, 60, 4, 1, true, RGB(255, 0, 255));
	BULLET.BulletSetting("마총1", IMAGEMANAGER.findImage("마총1"), 30, true, 20, 1);
	BULLET.BulletShadowSetting("마총1", IMAGEMANAGER.findImage("웨어총알그림자"), RectMake(0, 0, 60, 10), 70);

	IMAGEMANAGER.addFrameImage("마총2", PathFile("image\\Enemy", "마법사총2").c_str(), 187, 140, 5, 1, true, RGB(255, 0, 255));
	BULLET.BulletSetting("마총2", IMAGEMANAGER.findImage("마총2"), 30, true, 10, 1, false);
	BULLET.BulletShadowSetting("마총2", NULL, RectMake(0, 0, 60, 10), 70);

	IMAGEMANAGER.addFrameImage("마총3", PathFile("image\\Enemy", "마법사총3").c_str(), 180, 60, 3, 1, true, RGB(255, 0, 255));
	BULLET.BulletSetting("마총3", IMAGEMANAGER.findImage("마총3"), 30, true, 10, 1);
	BULLET.BulletShadowSetting("마총3", IMAGEMANAGER.findImage("웨어총알그림자"), RectMake(0, 0, 60, 10), 70);

	IMAGEMANAGER.addFrameImage("드브", PathFile("image\\Enemy", "드래곤브레스").c_str(), 1200, 132, 4, 1, true, RGB(255, 0, 255));
	BULLET.BulletSetting("드브", IMAGEMANAGER.findImage("드브"), 30, true, 20, 1, false);
	BULLET.BulletShadowSetting("드브", NULL, RectMake(0, 0, 300, 80), 60);

	IMAGEMANAGER.addFrameImage("드총", PathFile("image\\Enemy", "드래곤총").c_str(), 240, 60, 4, 1, true, RGB(255, 0, 255));
	BULLET.BulletSetting("드총", IMAGEMANAGER.findImage("드총"), 30, true, 60, 1);
	BULLET.BulletShadowSetting("드총", IMAGEMANAGER.findImage("웨어총알그림자"), RectMake(0, 0, 60, 10), 70);

	EFFECTMANAGER.addEffect("마3폭", PathFile("image\\Enemy", "마총3폭발").c_str(), 400, 60, 80, 60, 30, 1, 20);
	EFFECTMANAGER.addEffect("돌폭발", PathFile("image\\Enemy", "돌폭발이펙트").c_str(), 420, 100, 84, 100, 20, 1, 20);
	for (int i = 0; i < 30; i++)
	{
		ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("웨어화살")[i]);
		ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("스켈검")[i]);
		ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("용기사검")[i]);
		ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("용기사검0")[i]);
		ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("블랙아처화살")[i]);
		ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("외돌")[i]);
		ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("마총1")[i]);
		ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("마총2")[i]);
		ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("마총3")[i]);
		ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("드브")[i]);
		ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("드총")[i]);
	}

	_enemyUI = new EnemyUI;
	//보스체력 초기화
	//			maxHP, 에너지바 너비, 이름 입력
	_enemyUI->Init(90, 400, bossName);
	ZORDER.InputObj(_enemyUI);

	//보스체력 활성화
	_enemyUI->SetDrawHP(true);
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
			case CYCLOPSE:
			{
				Enemy*enemy = new Cyclopes(eType);
				enemy->Init();
				enemyVec.push_back(enemy);
			}
			break;
			case EVILMAGE:
			{
				Enemy*enemy = new EvilMage(eType);
				enemy->Init();
				enemyVec.push_back(enemy);
			}
			case DRAGON:
			{
				Enemy*enemy = new Dragon(eType);
				enemy->Init();
				enemyVec.push_back(enemy);
			}
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
	//보스 체력 또는 화살표그리기 위한 업데이트 함수
	_enemyUI->Update();

	enemyMapIter emIter = enemyMap.begin();
	for (; emIter != enemyMap.end(); emIter++)
	{
		for (int i = 0; i<emIter->second.size(); i++)
		{
			if (emIter->second[i]->getShowState() && !emIter->second[i]->getDie())
			{
				emIter->second[i]->Update(pm);
				
				if(emIter->second[i]->getEnemyType()== DRAGONKNIGHT)
					_enemyUI->HpUpdate(emIter->second[i]->getHp()*2);
				if (emIter->second[i]->getEnemyType() == EVILMAGE)
					_enemyUI->HpUpdate(emIter->second[i]->getHp() * 2);
				if (emIter->second[i]->getEnemyType() == DRAGON)
					_enemyUI->HpUpdate(emIter->second[i]->getHp() * 2);
			}
		}
	}
	checkEnemyNum = DieUpdate();
	EnemyCollision(pm);
	BulletShadowCollision();
	//보스체력 동기화 함수
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

void EnemyManager::EnemyCollision(PlayerManager*pm)
{
	enemyMapIter emIter = enemyMap.begin();

	for (; emIter != enemyMap.end(); emIter++)
	{
		for (int i = 0; i < emIter->second.size(); i++)
		{
			if (!emIter->second[i]->getShowState() || emIter->second[i]->getDie())continue;

			for (int k = 0; k < DATABASE.LoadData("1P2P") + 1; k++)
			{
				for (int j = 0; j < BULLET.GetBulletVec("Magician_Weapon_" + to_string(pm->GetPlayer(k)->GetWeaponLv()) + "_B").size(); j++)
				{
					if (!BULLET.GetBulletVec("Magician_Weapon_" + to_string(pm->GetPlayer(k)->GetWeaponLv()) + "_B")[j]->isShot)continue;
					RECT rc;
					if (IntersectRect(&rc, &emIter->second[i]->getRc(), &BULLET.GetBulletVec("Magician_Weapon_" + to_string(pm->GetPlayer(k)->GetWeaponLv()) + "_B")[j]->getRc()))
					{
						SOUNDMANAGER.play("28Hit");
						int randomSet = RND.GetFromTo(-10, 11);
						EFFECTMANAGER.play("에너미피격", GetCenterPos(emIter->second[i]->getRc()).x + randomSet, GetCenterPos(emIter->second[i]->getRc()).y - 40);
						emIter->second[i]->Damaged();
						BULLET.Destroy("Magician_Weapon_" + to_string(pm->GetPlayer(k)->GetWeaponLv()) + "_B", j);
						break;
					}
				}
				for (int j = 0; j < BULLET.GetBulletVec("Warrior_Weapon_" + to_string(pm->GetPlayer(k)->GetWeaponLv()) + "_B").size(); j++)
				{
					if (!BULLET.GetBulletVec("Warrior_Weapon_" + to_string(pm->GetPlayer(k)->GetWeaponLv()) + "_B")[j]->isShot)continue;
					RECT rc;
					if (IntersectRect(&rc, &emIter->second[i]->getRc(), &BULLET.GetBulletVec("Warrior_Weapon_" + to_string(pm->GetPlayer(k)->GetWeaponLv()) + "_B")[j]->getRc()))
					{
						SOUNDMANAGER.play("28Hit");
						int randomSet = RND.GetFromTo(-10, 11);
						EFFECTMANAGER.play("에너미피격", GetCenterPos(emIter->second[i]->getRc()).x + randomSet, GetCenterPos(emIter->second[i]->getRc()).y - 40);
						emIter->second[i]->Damaged();
						BULLET.Destroy("Warrior_Weapon_" + to_string(pm->GetPlayer(k)->GetWeaponLv()) + "_B", j);
						break;
					}
				}
			}
		}
	}

	enemyMapIter emIter1 = enemyMap.begin();

	for (; emIter1 != enemyMap.end(); emIter1++)
	{
		for (int i = 0; i < emIter1->second.size(); i++)
		{
			if (!emIter1->second[i]->getShowState() || emIter1->second[i]->getDie())continue;

			if (emIter1->second[i]->getEnemyType() == DRAGON || emIter1->second[i]->getEnemyType() == EVILMAGE || emIter1->second[i]->getEnemyType() == DRAGONKNIGHT)
				continue;
			
			RECT rc;
			if (IntersectRect(&rc, &pm->GetPlayUI()->GetSkill2()->getRc(), &emIter1->second[i]->getRc()))
			{
				emIter1->second[i]->getHp() -= 0.0001;
			}
			RECT rc2;
			if (IntersectRect(&rc2, &pm->GetPlayUI()->GetSkill1()->getRc(), &emIter1->second[i]->getRc()))
			{
				emIter1->second[i]->getHp() -= 0.0001;
			}

			for (int j = 0; j < 8; j++)
			{
				RECT rc3;
				if (IntersectRect(&rc3, &pm->GetPlayUI()->GetSkill3(j)->getRc(), &emIter1->second[i]->getRc()))
				{
					emIter1->second[i]->getHp() -= 0.0001;
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

void EnemyManager::BulletShadowCollision()
{
	for (int i = 0; i < BULLET.GetBulletVec("마총3").size(); i++)
	{
		if (!BULLET.GetBulletVec("마총3")[i]->isShot)continue;
		RECT temp;
		RECT rc = RectMakeCenter(GetCenterPos(BULLET.GetBulletVec("마총3")[i]->shadowRc).x,
			GetCenterPos(BULLET.GetBulletVec("마총3")[i]->shadowRc).y + 20,
			BULLET.GetBulletVec("마총3")[i]->shadowWidth,
			BULLET.GetBulletVec("마총3")[i]->shadowHeight);
		if (IntersectRect(&temp, &rc, &BULLET.GetBulletVec("마총3")[i]->rc))
		{
			EFFECTMANAGER.play("마3폭", GetCenterPos(rc).x, GetCenterPos(rc).y-40);
			BULLET.Destroy("마총3", i);
		}
	}
	for (int i = 0; i < BULLET.GetBulletVec("외돌").size(); i++)
	{
		if (!BULLET.GetBulletVec("외돌")[i]->isShot)continue;
		RECT temp;
		RECT rc = RectMakeCenter(GetCenterPos(BULLET.GetBulletVec("외돌")[i]->shadowRc).x,
			GetCenterPos(BULLET.GetBulletVec("외돌")[i]->shadowRc).y + 40,
			BULLET.GetBulletVec("외돌")[i]->shadowWidth,
			BULLET.GetBulletVec("외돌")[i]->shadowHeight);
		if (IntersectRect(&temp, &rc, &BULLET.GetBulletVec("외돌")[i]->rc))
		{
			EFFECTMANAGER.play("돌폭발", GetCenterPos(rc).x-30, GetCenterPos(rc).y-80);
			BULLET.Destroy("외돌", i);
		}
	}
	for (int i = 0; i < BULLET.GetBulletVec("드총").size(); i++)
	{
		if (!BULLET.GetBulletVec("드총")[i]->isShot)continue;
		RECT temp;
		RECT rc = RectMakeCenter(GetCenterPos(BULLET.GetBulletVec("드총")[i]->shadowRc).x,
			GetCenterPos(BULLET.GetBulletVec("드총")[i]->shadowRc).y + 20,
			BULLET.GetBulletVec("드총")[i]->shadowWidth,
			BULLET.GetBulletVec("드총")[i]->shadowHeight);
		if (IntersectRect(&temp, &rc, &BULLET.GetBulletVec("드총")[i]->rc))
		{
			EFFECTMANAGER.play("마3폭", GetCenterPos(rc).x, GetCenterPos(rc).y - 40);
			BULLET.Destroy("드총", i);
		}
	}
}

