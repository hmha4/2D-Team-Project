#include "stdafx.h"
#include "EnemyManager.h"


EnemyManager::EnemyManager()
	:enemyNum(0)
{
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
		}
	}
	enemyMap[eType] = enemyVec;
	enemyIdxMap[eType] = 0;
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
	enemyMapIter emIter = enemyMap.find(eType);

	emIter->second[enemyIdxMap[eType]]->Init(x, y, eState);
	emIter->second[enemyIdxMap[eType]]->getShowState() = true;
	ZORDER.InputObj(emIter->second[enemyIdxMap[eType]]);

	enemyIdxMap[eType]++;
	enemyNum++;
	initEnemyNum = enemyNum;
	checkEnemyNum = 1;

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

