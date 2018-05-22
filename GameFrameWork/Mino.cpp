#include "stdafx.h"
#include "Mino.h"


Mino::Mino(ENEMYTYPE _eType)
	:Enemy(_eType)
{
}


Mino::~Mino()
{
}

HRESULT Mino::Init(int x, int y, ENEMYSTATE eState)
{
	return E_NOTIMPL;
}

void Mino::Release()
{
}

void Mino::EnemyUpdate(PlayerManager * pm)
{
}

void Mino::DieEnemy()
{
}

void Mino::Damaged()
{
}
