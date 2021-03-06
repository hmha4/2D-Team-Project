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

HRESULT Character::Init(float x, float y, int player)
{
    _x = x;
    _y = y;
	_alpha = 255;
	_alphaCount = 0;
	_deadTime = 0;


	//	1p, 2p 입력 키 조정
	if (player == 0)
	{
		_mControl.insert(make_pair("Attack", 'A'));
		_mControl.insert(make_pair("Jump", 'S'));
		_mControl.insert(make_pair("Block", 'D'));
		_mControl.insert(make_pair("Up", 'Y'));
		_mControl.insert(make_pair("Down", 'H'));
		_mControl.insert(make_pair("Left", 'G'));
		_mControl.insert(make_pair("Right", 'J'));
		int weaponlv = DATABASE.LoadData("1PWeapon");
		_weapon = (WEAPON)(weaponlv - 1);
	}
	else if (player == 1)
	{
		_mControl.insert(make_pair("Attack", VK_NUMPAD4));
		_mControl.insert(make_pair("Jump", VK_NUMPAD5));
		_mControl.insert(make_pair("Block", VK_NUMPAD6));
		_mControl.insert(make_pair("Up", VK_UP));
		_mControl.insert(make_pair("Down", VK_DOWN));
		_mControl.insert(make_pair("Left", VK_LEFT));
		_mControl.insert(make_pair("Right", VK_RIGHT));
		_weapon = (WEAPON)(DATABASE.LoadData("2PWeapon") - 1);
	}
    return S_OK;
}

void Character::Release()
{
	//	딱히 해줄 필요는 없음
    _x = 0;
    _y = 0;
    _rc = RectMake(0, 0, 0, 0);
    //_img = NULL;
    //_anim = NULL;
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
    _img->alphaAniRender(getMemDC(), _rc.left, _rc.top, _anim, _alpha);
	//Rectangle(getMemDC(), _shadow.left, _shadow.top, _shadow.right, _shadow.bottom);
}
