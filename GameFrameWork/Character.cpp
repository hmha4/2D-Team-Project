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
	_weapon = WEAPON_1;
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
	if (KEYMANAGER.isOnceKeyDown('1'))
		_weapon = WEAPON_1;
	else if (KEYMANAGER.isOnceKeyDown('2'))
		_weapon = WEAPON_2;
	else if (KEYMANAGER.isOnceKeyDown('3'))
		_weapon = WEAPON_3;
	else if (KEYMANAGER.isOnceKeyDown('4'))
		_weapon = WEAPON_4;

    _rc = RectMakeCenter(_x, _y, _img->GetFrameWidth(), _img->GetFreamHeight());
}

void Character::Render()
{
    _img->aniRender(getMemDC(), _rc.left, _rc.top, _anim);
}

void Character::MovementRestrict(int stage)
{
    if (stage == 0)
    {
        _speedX = 0;
        _speedY = 0;
    }
    else if (stage == 1)
    {
        if (_colRC.left < CAM.GetRC().left)
        {
            _x = CAM.GetRC().left + (_colRC.right - _colRC.left) / 2;
            _speedX = 0;
        }
        else if (_colRC.right > CAM.GetRC().right)
        {
            _x = CAM.GetRC().right - (_colRC.right - _colRC.left) / 2;
            _speedX = 0;
        }

        if (_colRC.top < WINSIZEY/2 - 100)
        {
            _y = WINSIZEY / 2 - 100 + (_colRC.bottom - _colRC.top) / 2 - 32;
            _speedY = 0;
        }
        else if (_colRC.bottom > 400)
        {
            _y = 400 - (_colRC.bottom - _colRC.top) / 2 - 32;
            _speedY = 0;
        }
    }
    else if (stage == 2)
    {

    }
}

