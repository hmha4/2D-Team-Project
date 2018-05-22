#pragma once
#include <vector>
#include <map>
#include "Warewolf.h"
#include "skeleton.h"
class EnemyManager:public gameNode
{
private:
	typedef vector<Enemy*>::iterator enemyIter;
	typedef map<ENEMYTYPE, vector<Enemy*>>::iterator enemyMapIter;
	typedef map<ENEMYTYPE, int>::iterator enemyMapIdxIter;
private:
	map<ENEMYTYPE, vector<Enemy*>> enemyMap;
	map<ENEMYTYPE, int> enemyIdxMap;

	int initEnemyNum;
	int enemyNum;
	int checkEnemyNum;
public:
	EnemyManager();
	~EnemyManager();

	void InputEnemy(ENEMYTYPE eType, int enemyNum);

	void Update(PlayerManager*pm);
	void Release();

	void ShowEnemy(ENEMYTYPE eType,float x,float y,ENEMYSTATE eState);
	int DieUpdate();

	inline vector<Enemy*>&GetEnemyVec(ENEMYTYPE eType) {
		return enemyMap.find(eType)->second;
	}
	inline int&GetEnemyNum() { return checkEnemyNum; }
};

