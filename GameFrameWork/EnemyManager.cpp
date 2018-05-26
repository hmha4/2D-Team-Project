#include "stdafx.h"
#include "EnemyManager.h"
#include "Bullet.h"

EnemyManager::EnemyManager()
	:enemyNum(0)
{
	IMAGEMANAGER.addImage("����׸���", PathFile("image\\Enemy", "����׸���").c_str(), 80, 40, true, RGB(255, 0, 255));
	checkEnemyNum = 1;

	IMAGEMANAGER.addFrameImage("�������ȭ��", PathFile("image\\Enemy", "�������ȭ��").c_str(), 60, 20, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER.addFrameImage("�����Ѿ˱׸���", PathFile("image\\Enemy", "�����Ѿ˱׸���").c_str(), 60, 10, 1, 1, true, RGB(255, 0, 255));
	BULLET.BulletSetting("����ȭ��", IMAGEMANAGER.findImage("�������ȭ��"), 30, false, 0, 2);
	BULLET.BulletShadowSetting("����ȭ��", IMAGEMANAGER.findImage("�����Ѿ˱׸���"), RectMake(0, 0, 60, 10), 50);

	IMAGEMANAGER.addFrameImage("���̷����", PathFile("image\\Enemy", "���̷����").c_str(), 60, 60, 1, 1, true, RGB(255, 0, 255));
	BULLET.BulletSetting("���̰�", IMAGEMANAGER.findImage("���̷����"), 30, false, 0, 1);
	BULLET.BulletShadowSetting("���̰�", NULL, RectMake(0, 0, 40, 10), 50);

	BULLET.BulletSetting("��ȣ��", IMAGEMANAGER.findImage("���̷����"), 30, false, 0, 1);
	BULLET.BulletShadowSetting("��ȣ��", NULL, RectMake(0, 0, 120, 20), 50);

	BULLET.BulletSetting("�����0", IMAGEMANAGER.findImage("���̷����"), 30, false, 0, 1);
	BULLET.BulletShadowSetting("�����0", NULL, RectMake(0, 0, 200, 20), 50);

	IMAGEMANAGER.addFrameImage("�����", PathFile("image\\Enemy", "����Į").c_str(), 1136, 70, 16, 1, true, RGB(255, 0, 255));
	BULLET.BulletSetting("�����", IMAGEMANAGER.findImage("�����"), 30, true, 40, 1);
	BULLET.BulletShadowSetting("�����", IMAGEMANAGER.findImage("�����Ѿ˱׸���"), RectMake(0, 0, 60, 10), 70);

	IMAGEMANAGER.addFrameImage("����óȭ��", PathFile("image\\Enemy", "����óȭ��").c_str(), 80, 52, 1, 2, true, RGB(255, 0, 255));
	BULLET.BulletSetting("����óȭ��", IMAGEMANAGER.findImage("����óȭ��"), 30, 0, 0, 2);
	BULLET.BulletShadowSetting("����óȭ��", IMAGEMANAGER.findImage("�����Ѿ˱׸���"), RectMake(0, 0, 60, 10), 50);

	IMAGEMANAGER.addFrameImage("�ܴ����ε�", PathFile("image\\Enemy", "�ܴ����ε�").c_str(), 60, 83, 1, 2, true, RGB(255, 0, 255));
	BULLET.BulletSetting("�ܵ�", IMAGEMANAGER.findImage("�ܴ����ε�"), 30, 0, 0, 2);
	BULLET.BulletShadowSetting("�ܵ�", IMAGEMANAGER.findImage("�����Ѿ˱׸���"), RectMake(0, 0, 60, 10), 50);

	IMAGEMANAGER.addFrameImage("����1", PathFile("image\\Enemy", "��������1").c_str(), 209, 60, 4, 1, true, RGB(255, 0, 255));
	BULLET.BulletSetting("����1", IMAGEMANAGER.findImage("����1"), 30, true, 20, 1);
	BULLET.BulletShadowSetting("����1", IMAGEMANAGER.findImage("�����Ѿ˱׸���"), RectMake(0, 0, 60, 10), 70);

	IMAGEMANAGER.addFrameImage("����2", PathFile("image\\Enemy", "��������2").c_str(), 187, 140, 5, 1, true, RGB(255, 0, 255));
	BULLET.BulletSetting("����2", IMAGEMANAGER.findImage("����2"), 30, true, 10, 1,false);
	BULLET.BulletShadowSetting("����2", NULL, RectMake(0, 0, 60, 10), 70);

	IMAGEMANAGER.addFrameImage("����3", PathFile("image\\Enemy", "��������3").c_str(), 180, 60, 3, 1, true, RGB(255, 0, 255));
	BULLET.BulletSetting("����3", IMAGEMANAGER.findImage("����3"), 30, true, 10, 1);
	BULLET.BulletShadowSetting("����3", IMAGEMANAGER.findImage("�����Ѿ˱׸���"), RectMake(0, 0, 60, 10), 70);

	EFFECTMANAGER.addEffect("��3��", PathFile("image\\Enemy", "����3����").c_str(), 400, 60, 80, 60, 30, 1, 20);
	EFFECTMANAGER.addEffect("������", PathFile("image\\Enemy", "����������Ʈ").c_str(), 420, 100, 84, 100, 20, 1, 20);
	for (int i = 0; i < 30; i++)
	{
		ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("����ȭ��")[i]);
		ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("���̰�")[i]);
		ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("�����")[i]);
		ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("�����0")[i]);
		ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("����óȭ��")[i]);
		ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("�ܵ�")[i]);
		ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("����1")[i]);
		ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("����2")[i]);
		ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("����3")[i]);
	}

	_enemyUI = new EnemyUI;
	//����ü�� �ʱ�ȭ
	//			maxHP, �������� �ʺ�, �̸� �Է�
	_enemyUI->Init(100, 400, "Red Dragon");
	ZORDER.InputObj(_enemyUI);
	//����ü�� Ȱ��ȭ
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
	//���� ü�� �Ǵ� ȭ��ǥ�׸��� ���� ������Ʈ �Լ�
	_enemyUI->Update();
	
	//										rawGo Ȱ��ȭ(true�� ȭ��ǥ ����)
	if (KEYMANAGER.isOnceKeyDown('E')) _enemyUI->SetDrawGo(true);
	if (KEYMANAGER.isOnceKeyDown('R')) _enemyUI->SetDrawGo(false);

	enemyMapIter emIter = enemyMap.begin();
	for (; emIter != enemyMap.end(); emIter++)
	{
		for (int i = 0; i<emIter->second.size(); i++)
		{
			if (emIter->second[i]->getShowState() && !emIter->second[i]->getDie())
			{
				emIter->second[i]->Update(pm);
				
				if(emIter->second[i]->getEnemyType()== DRAGONKNIGHT)
					_enemyUI->HpUpdate(emIter->second[i]->getHp()*3.333f);
			}
		}
	}
	checkEnemyNum = DieUpdate();
	EnemyCollision(pm);
	BulletShadowCollision();
	//����ü�� ����ȭ �Լ�
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

			for (int j = 0; j < BULLET.GetBulletVec("Warrior_Weapon_" + to_string(pm->GetPlayer1()->GetWeaponLv()) + "_B").size(); j++)
			{
				if (!BULLET.GetBulletVec("Warrior_Weapon_"+ to_string(pm->GetPlayer1()->GetWeaponLv()) +"_B")[j]->isShot)continue;
				RECT rc;
				if (IntersectRect(&rc, &emIter->second[i]->getRc(), &BULLET.GetBulletVec("Warrior_Weapon_" + to_string(pm->GetPlayer1()->GetWeaponLv()) + "_B")[j]->getRc()))
				{
					int randomSet = RND.GetFromTo(-10, 11);
					EFFECTMANAGER.play("���ʹ��ǰ�", GetCenterPos(emIter->second[i]->getRc()).x + randomSet, GetCenterPos(emIter->second[i]->getRc()).y - 40);
					emIter->second[i]->Damaged();
					BULLET.Destroy("Warrior_Weapon_" +to_string(pm->GetPlayer1()->GetWeaponLv())+ "_B", j);
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

void EnemyManager::BulletShadowCollision()
{
	for (int i = 0; i < BULLET.GetBulletVec("����3").size(); i++)
	{
		if (!BULLET.GetBulletVec("����3")[i]->isShot)continue;
		RECT temp;
		RECT rc = RectMakeCenter(GetCenterPos(BULLET.GetBulletVec("����3")[i]->shadowRc).x,
			GetCenterPos(BULLET.GetBulletVec("����3")[i]->shadowRc).y + 20,
			BULLET.GetBulletVec("����3")[i]->shadowWidth,
			BULLET.GetBulletVec("����3")[i]->shadowHeight);
		if (IntersectRect(&temp, &rc, &BULLET.GetBulletVec("����3")[i]->rc))
		{
			EFFECTMANAGER.play("��3��", GetCenterPos(rc).x, GetCenterPos(rc).y-40);
			BULLET.Destroy("����3", i);
		}
	}
	for (int i = 0; i < BULLET.GetBulletVec("�ܵ�").size(); i++)
	{
		if (!BULLET.GetBulletVec("�ܵ�")[i]->isShot)continue;
		RECT temp;
		RECT rc = RectMakeCenter(GetCenterPos(BULLET.GetBulletVec("�ܵ�")[i]->shadowRc).x,
			GetCenterPos(BULLET.GetBulletVec("�ܵ�")[i]->shadowRc).y + 40,
			BULLET.GetBulletVec("�ܵ�")[i]->shadowWidth,
			BULLET.GetBulletVec("�ܵ�")[i]->shadowHeight);
		if (IntersectRect(&temp, &rc, &BULLET.GetBulletVec("�ܵ�")[i]->rc))
		{
			EFFECTMANAGER.play("������", GetCenterPos(rc).x-30, GetCenterPos(rc).y-80);
			BULLET.Destroy("�ܵ�", i);
		}
	}
}

