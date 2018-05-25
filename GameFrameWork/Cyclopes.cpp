#include "stdafx.h"
#include "Cyclopes.h"


Cyclopes::Cyclopes(ENEMYTYPE _eType)
	:Enemy(_eType)
{
}


Cyclopes::~Cyclopes()
{
}

HRESULT Cyclopes::Init(int x, int y, ENEMYSTATE eState)
{
	return S_OK;
}

void Cyclopes::Release()
{
}

void Cyclopes::EnemyUpdate(PlayerManager * pm)
{
}

void Cyclopes::DieEnemy()
{
}

void Cyclopes::Damaged()
{
}
