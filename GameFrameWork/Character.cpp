#include "stdafx.h"
#include "Character.h"


Character::Character() :
    _speedX(3), _speedY(1),
    _jumpPower(0), _gravity(0), _friction(0.3f)
{
}


Character::~Character()
{
}

HRESULT Character::Init(float x, float y)
{
    _x = x;
    _y = y;

    return S_OK;
}

void Character::Release()
{
    _x = 0;
    _y = 0;
    _rc = RectMake(0, 0, 0, 0);
    _img = NULL;
    _anim = NULL;
}

void Character::Update()
{
    _rc = RectMakeCenter(_x, _y, _img->GetFrameWidth(), _img->GetFreamHeight());
}

void Character::Render()
{
    _img->aniRender(getMemDC(), _rc.left, _rc.top, _anim);
}

