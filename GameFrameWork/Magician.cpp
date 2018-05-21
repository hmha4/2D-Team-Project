#include "stdafx.h"
#include "Magician.h"
#include "Bullet.h"

Magician::Magician()
{
}


Magician::~Magician()
{
}

HRESULT Magician::Init(float x, float y)
{
    Character::Init(x, y);

    IMAGEMANAGER.addFrameImage("Magician1", PathFile("image\\Character", "Magician_Weapon_1").c_str(), 1500, 1050, 10, 7, true, RGB(255, 0, 255));
    IMAGEMANAGER.addFrameImage("Magician2", PathFile("image\\Character", "Magician_Weapon_2").c_str(), 1500, 1050, 10, 7, true, RGB(255, 0, 255));
    IMAGEMANAGER.addFrameImage("Magician3", PathFile("image\\Character", "Magician_Weapon_3").c_str(), 1500, 1050, 10, 7, true, RGB(255, 0, 255));
    IMAGEMANAGER.addFrameImage("Magician4", PathFile("image\\Character", "Magician_Weapon_4").c_str(), 1500, 1050, 10, 7, true, RGB(255, 0, 255));
    _img = IMAGEMANAGER.findImage("Magician1");

    char * magician = "Magician1";

    //IDLE
    int rightIdle[] = { 0 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianRightIdle", magician, rightIdle, 1, 5, true);
    int leftIdle[] = { 10 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianLeftIdle", magician, leftIdle, 1, 5, true);
    //RUN
    int rightRun[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianRightRun", magician, rightRun, 8, 10, true);
    int leftRun[] = { 11, 12, 13, 14, 15, 16, 17, 18 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianLeftRun", magician, leftRun, 8, 10, true);
    //JUMP
    int rightJump[] = { 20, 21 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianRightJump", magician, rightJump, 2, 10, false);
    int leftJump[] = { 24, 25 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianLeftJump", magician, leftJump, 2, 10, false);
    //FALL
    int rightFall[] = { 22, 23 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianRightFall", magician, rightFall, 2, 10, false);
    int leftFall[] = { 26, 27 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianLeftFall", magician, leftFall, 2, 10, false);
    //ATTACK
    int rightAttack[] = { 30, 31, 32 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianRightAttack", magician, rightAttack, 3, 10, false);
    int leftAttack[] = { 33, 34, 35 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianLeftAttack", magician, leftAttack, 3, 10, false);
    //JUMP ATTACK
    int rightJumpAttack[] = { 40 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianRightJumpAttack", magician, rightJumpAttack, 1, 10, false);
    int leftJumpAttack[] = { 41 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianLeftJumpAttack", magician, leftJumpAttack, 1, 10, false);
    //GET HIT 1
    int rightHit1[] = { 50 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianRightHit1", magician, rightHit1, 1, 10, true);
    int leftHit1[] = { 60 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianLeftHit1", magician, leftHit1, 1, 10, true);
    //GET HIT 2
    int rightHit2[] = { 51 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianRightHit2", magician, rightHit2, 1, 10, true);
    int leftHit2[] = { 61 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianLeftHit2", magician, leftHit2, 1, 10, true);
    //DIE PHASE 1
    int rightDiePhase1[] = { 52 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianRightDie1", magician, rightDiePhase1, 1, 10, true);
    int leftDiePhase1[] = { 62 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianLeftDie1", magician, leftDiePhase1, 1, 10, true);
    //DIE PHASE 1(FIRE)
    int rightDiePhase1Fire[] = { 42, 43, 44 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianRightDie1Fire", magician, rightDiePhase1Fire, 3, 10, true);
    int leftDiePhase1Fire[] = { 45, 46, 47 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianLeftDie1Fire", magician, leftDiePhase1Fire, 3, 10, true);
    //DIE PHASE 1(ICE)
    int rightDiePhase1Ice[] = { 29 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianRightDie1Ice", magician, rightDiePhase1Ice, 1, 1, false);
    int leftDiePhase1Ice[] = { 39 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianLeftDie1Ice", magician, leftDiePhase1Ice, 1, 1, false);
    //DIE PHASE 2
    int rightDiePhase2[] = { 53 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianRightDie2", magician, rightDiePhase2, 1, 10, true);
    int leftDiePhase2[] = { 63 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianLeftDie2", magician, leftDiePhase2, 1, 10, true);
    //DIE PHASE 3
    int rightDiePhase3[] = { 54 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianRightDie3", magician, rightDiePhase3, 1, 10, true);
    int leftDiePhase3[] = { 64 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianLeftDie3", magician, leftDiePhase3, 1, 10, true);
    //DIE PHASE 4
    int rightDiePhase4[] = { 55, 56 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianRightDie4", magician, rightDiePhase4, 2, 10, false);
    int leftDiePhase4[] = { 65, 66 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianLeftDie4", magician, leftDiePhase4, 2, 10, false);
    //OTHER
    int rightOther[] = { 9 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianRightOther", magician, rightOther, 1, 1, false);
    int leftDieOther[] = { 19 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianLeftOther", magician, leftDieOther, 1, 1, false);


    _state = RIGHT_IDLE;
    _anim = ANIMATIONKEY.findAnimation("MagicianRightIdle");
    _anim->start();

    _hp = 10;

	InitBullet();

    return S_OK;
}

void Magician::Release()
{
    Character::Release();
}

void Magician::Update()
{
    Character::Update();

	ChangeWeapon();
	
	if (KEYMANAGER.isOnceKeyDown(VK_RIGHT))
	{
		_speedX = 3;
		ChangeAnim((int)RIGHT_IDLE, "MagicianRightIdle");
	}
	else if (KEYMANAGER.isOnceKeyDown(VK_LEFT))
	{
		_speedX = 3;
		ChangeAnim((int)LEFT_IDLE, "MagicianLeftIdle");
	}

	if (KEYMANAGER.isOnceKeyDown(VK_SPACE))
	{
		_jumpPower = 7;
		_gravity = 0.3f;
		_startY = _y;
		if (_state == RIGHT_IDLE || _state == RIGHT_RUN)
			ChangeAnim((int)RIGHT_JUMP, "MagicianRightJump");
		else if (_state == LEFT_IDLE || _state == LEFT_RUN)
			ChangeAnim((int)LEFT_JUMP, "MagicianLeftJump");
	}

	if (KEYMANAGER.isOnceKeyDown('Z'))
	{
		if (_state == RIGHT_IDLE || _state == RIGHT_RUN ||
			_state == RIGHT_JUMP || _state == RIGHT_FALL)
			BULLET.Shot(_weaponEffectName, _colX + 40, _colY - 20, 0, 0, 7, 0);
		else if (_state == LEFT_IDLE || _state == LEFT_RUN ||
				 _state == LEFT_JUMP || _state == LEFT_FALL)
			BULLET.Shot(_weaponEffectName, _colX - 40, _colY - 20, 0, 0, -7, 1);

		if (_state == RIGHT_IDLE || _state == RIGHT_RUN)
			ChangeAnim((int)RIGHT_ATTACK, "MagicianRightAttack");
		else if (_state == LEFT_IDLE || _state == LEFT_RUN)
			ChangeAnim((int)LEFT_ATTACK, "MagicianLeftAttack");
		else if (_state == RIGHT_JUMP || _state == RIGHT_FALL)
			ChangeAnim((int)RIGHT_JUMP_ATTACK, "MagicianRightJumpAttack");
		else if (_state == LEFT_JUMP || _state == LEFT_FALL)
			ChangeAnim((int)LEFT_JUMP_ATTACK, "MagicianLeftJumpAttack");

		if (_state == RIGHT_JUMP || _state == RIGHT_FALL ||
			_state == LEFT_JUMP || _state == LEFT_FALL)
			BULLET.GetBulletVec(_weaponEffectName)[0]->ShadowSetY = WINSIZEY/2;
	}

	if (KEYMANAGER.isOnceKeyDown('C'))
	{
		Collision();
	}

	switch (_state)
	{
	case Magician::RIGHT_IDLE:
		if (_hp <= 0)
		{
			_hp = 10;
			ChangeAnim((int)RIGHT_OTHER, "MagicianRightOther");
			break;
		}
		if (KEYMANAGER.isStayKeyDown(VK_RIGHT))
		{
			_speedX = 3;
			ChangeAnim((int)RIGHT_RUN, "MagicianRightRun");
		}
		if (KEYMANAGER.isStayKeyDown(VK_LEFT))
		{
			_speedX = 3;
			ChangeAnim((int)LEFT_RUN, "MagicianLeftRun");
		}
		if (KEYMANAGER.isStayKeyDown(VK_UP))
		{
			_speedY = 1;
			ChangeAnim((int)RIGHT_UP_RUN, "MagicianRightRun");
		}
		if (KEYMANAGER.isStayKeyDown(VK_DOWN))
		{
			_speedY = 1;
			ChangeAnim((int)RIGHT_DOWN_RUN, "MagicianRightRun");
		}
		break;
	case Magician::LEFT_IDLE:
		if (_hp <= 0)
		{
			_hp = 10;
			ChangeAnim((int)LEFT_OTHER, "MagicianLeftOther");
			break;
		}
		if (KEYMANAGER.isStayKeyDown(VK_RIGHT))
		{
			_speedX = 3;
			ChangeAnim((int)RIGHT_RUN, "MagicianRightRun");
		}
		if (KEYMANAGER.isStayKeyDown(VK_LEFT))
		{
			_speedX = 3;
			ChangeAnim((int)LEFT_RUN, "MagicianLeftRun");
		}
		if (KEYMANAGER.isStayKeyDown(VK_UP))
		{
			_speedY = 1;
			ChangeAnim((int)LEFT_UP_RUN, "MagicianLeftRun");
		}
		if (KEYMANAGER.isStayKeyDown(VK_DOWN))
		{
			_speedY = 1;
			ChangeAnim((int)LEFT_DOWN_RUN, "MagicianLeftRun");
		}
		break;
	case Magician::RIGHT_RUN:
		_speedX = 3;
		_x += _speedX;

		_speedY = 1;
		if (KEYMANAGER.isStayKeyDown(VK_UP))
			_y -= _speedY;
		else if (KEYMANAGER.isStayKeyDown(VK_DOWN))
			_y += _speedY;
		if (KEYMANAGER.isOnceKeyUp(VK_RIGHT))
		{
			ChangeAnim((int)RIGHT_IDLE, "MagicianRightIdle");
		}
		break;
	case Magician::LEFT_RUN:
		_speedX = 3;
		_x -= _speedX;

		_speedY = 1;
		if (KEYMANAGER.isStayKeyDown(VK_UP))
			_y -= _speedY;
		else if (KEYMANAGER.isStayKeyDown(VK_DOWN))
			_y += _speedY;
		if (KEYMANAGER.isOnceKeyUp(VK_LEFT))
		{
			ChangeAnim((int)LEFT_IDLE, "MagicianLeftIdle");
		}
		break;
	case Magician::RIGHT_UP_RUN:
		_y -= _speedY;

		if (KEYMANAGER.isStayKeyDown(VK_LEFT))
			_x -= _speedX;
		else if (KEYMANAGER.isStayKeyDown(VK_RIGHT))
			_x += _speedX;
		if (KEYMANAGER.isOnceKeyUp(VK_UP))
		{
			ChangeAnim((int)RIGHT_IDLE, "MagicianRightIdle");
		}
		break;
	case Magician::LEFT_UP_RUN:
		_y -= _speedY;

		if (KEYMANAGER.isStayKeyDown(VK_LEFT))
			_x -= _speedX;
		else if (KEYMANAGER.isStayKeyDown(VK_RIGHT))
			_x += _speedX;
		if (KEYMANAGER.isOnceKeyUp(VK_UP))
		{
			ChangeAnim((int)LEFT_IDLE, "MagicianLeftIdle");
		}
		break;
	case Magician::RIGHT_DOWN_RUN:
		_y += _speedY;

		if (KEYMANAGER.isStayKeyDown(VK_LEFT))
			_x -= _speedX;
		else if (KEYMANAGER.isStayKeyDown(VK_RIGHT))
			_x += _speedX;
		if (KEYMANAGER.isOnceKeyUp(VK_DOWN))
		{
			ChangeAnim((int)RIGHT_IDLE, "MagicianRightIdle");
		}
		break;
	case Magician::LEFT_DOWN_RUN:
		_y += _speedY;

		if (KEYMANAGER.isStayKeyDown(VK_LEFT))
			_x -= _speedX;
		else if (KEYMANAGER.isStayKeyDown(VK_RIGHT))
			_x += _speedX;
		if (KEYMANAGER.isOnceKeyUp(VK_DOWN))
		{
			ChangeAnim((int)LEFT_IDLE, "MagicianLeftIdle");
		}
		break;
	case Magician::RIGHT_JUMP:
		if (_jumpPower <= 0)
			ChangeAnim((int)RIGHT_FALL, "MagicianRightFall");
		break;
	case Magician::LEFT_JUMP:
		if (_jumpPower <= 0)
			ChangeAnim((int)LEFT_FALL, "MagicianLeftFall");
		break;
	case Magician::RIGHT_FALL:
		if (_y >= _startY)
		{
			_y = _startY;
			_jumpPower = 0;
			_gravity = 0;
			ChangeAnim((int)RIGHT_IDLE, "MagicianRightIdle");
			BULLET.Destroy(_weaponEffectName, 0);
		}
		break;
	case Magician::LEFT_FALL:
		if (_y >= _startY)
		{
			_y = _startY;
			_jumpPower = 0;
			_gravity = 0;
			ChangeAnim((int)LEFT_IDLE, "MagicianLeftIdle");
			BULLET.Destroy(_weaponEffectName, 0);
		}
		break;
	case Magician::RIGHT_ATTACK:
		if (!_anim->isPlay())
		{
			ChangeAnim((int)RIGHT_IDLE, "MagicianRightIdle");
			BULLET.Destroy(_weaponEffectName, 0);
		}
		break;
	case Magician::LEFT_ATTACK:
		if (!_anim->isPlay())
		{
			ChangeAnim((int)LEFT_IDLE, "MagicianLeftIdle");
			BULLET.Destroy(_weaponEffectName, 0);
		}
		break;
	case Magician::RIGHT_JUMP_ATTACK:
		if (_y >= _startY)
		{
			_y = _startY;
			_jumpPower = 0;
			_gravity = 0;
			ChangeAnim((int)RIGHT_IDLE, "MagicianRightIdle");
			BULLET.Destroy(_weaponEffectName, 0);
			break;
		}
		if (!_anim->isPlay())
		{
			ChangeAnim((int)RIGHT_FALL, "MagicianRightFall");
		}
		break;
	case Magician::LEFT_JUMP_ATTACK:
		if (_y >= _startY)
		{
			_y = _startY;
			_jumpPower = 0;
			_gravity = 0;
			ChangeAnim((int)LEFT_IDLE, "MagicianLeftIdle");
			BULLET.Destroy(_weaponEffectName, 0);
			break;
		}
		if (!_anim->isPlay())
		{
			ChangeAnim((int)LEFT_FALL, "MagicianLeftFall");
		}
		break;
	case Magician::RIGHT_HIT_1:
		_x -= _friction;
		_friction -= 0.3f;
		if (_friction <= 0)
		{
			_friction = 0;
			ChangeAnim((int)RIGHT_IDLE, "MagicianRightIdle");
		}
		break;
	case Magician::LEFT_HIT_1:
		_x += _friction;
		_friction -= 0.3f;
		if (_friction <= 0)
		{
			_friction = 0;
			ChangeAnim((int)LEFT_IDLE, "MagicianLeftIdle");
		}
		break;
	case Magician::RIGHT_HIT_2:
		_x -= _friction;
		_friction -= 0.3f;
		if (_friction <= 0)
		{
			_friction = 0;
			ChangeAnim((int)RIGHT_IDLE, "MagicianRightIdle");
		}
		break;
	case Magician::LEFT_HIT_2:
		_x += _friction;
		_friction -= 0.3f;
		if (_friction <= 0)
		{
			_friction = 0;
			ChangeAnim((int)LEFT_IDLE, "MagicianLeftIdle");
		}
		break;
	case Magician::RIGHT_DIE_P1:
		_x -= _friction;
		_friction -= 0.1f;

		if (_jumpPower <= 0)
			ChangeAnim((int)RIGHT_DIE_P2, "MagicianRightDie2");
		break;
	case Magician::LEFT_DIE_P1:
		_x += _friction;
		_friction -= 0.1f;

		if (_jumpPower <= 0)
			ChangeAnim((int)LEFT_DIE_P2, "MagicianLeftDie2");
		break;
	case Magician::RIGHT_DIE_PF:
		_x -= _friction;
		_friction -= 0.1f;

		if (_jumpPower <= 0)
			ChangeAnim((int)RIGHT_DIE_P2, "MagicianRightDie2");
		break;
	case Magician::LEFT_DIE_PF:
		_x += _friction;
		_friction -= 0.1f;

		if (_jumpPower <= 0)
			ChangeAnim((int)LEFT_DIE_P2, "MagicianLeftDie2");
		break;
	case Magician::RIGHT_DIE_PI:
		if (!_anim->isPlay())
		{
			_friction = 5;
			_jumpPower = 5;
			_gravity = 0.3f;
			_startY = _y;
			ChangeAnim((int)RIGHT_DIE_P1, "MagicianRightDie1");
		}
		break;
	case Magician::LEFT_DIE_PI:
		if (!_anim->isPlay())
		{
			_friction = 5;
			_jumpPower = 5;
			_gravity = 0.3f;
			_startY = _y;
			ChangeAnim((int)LEFT_DIE_P1, "MagicianLeftDie1");
		}
		break;
	case Magician::RIGHT_DIE_P2:
		_x -= _friction;
		_friction -= 0.1f;
		if (_friction <= 0) _friction = 0;

		if (_friction <= 0 && _y >= _startY)
		{
			_friction = 0;
			_jumpPower = 0;
			_gravity = 0;
			_y = _startY;
			ChangeAnim((int)RIGHT_DIE_P3, "MagicianRightDie3");
		}
		else if (_friction > 0 && _y >= _startY)
		{
			_jumpPower = 2;
			_gravity = 0.3f;
		}
		break;
	case Magician::LEFT_DIE_P2:
		_x += _friction;
		_friction -= 0.1f;
		if (_friction <= 0) _friction = 0;

		if (_friction <= 0 && _y >= _startY)
		{
			_friction = 0;
			_jumpPower = 0;
			_gravity = 0;
			_y = _startY;
			ChangeAnim((int)LEFT_DIE_P3, "MagicianLeftDie3");
		}
		else if (_friction > 0 && _y >= _startY)
		{
			_jumpPower = 2;
			_gravity = 0.3f;
		}
		break;
	case Magician::RIGHT_DIE_P3:
		_downCount += TIMEMANAGER.getElapsedTime();
		if (_downCount >= 1.0f)
		{
			_downCount = 0;
			ChangeAnim((int)RIGHT_DIE_P4, "MagicianRightDie4");
		}
		break;
	case Magician::LEFT_DIE_P3:
		_downCount += TIMEMANAGER.getElapsedTime();
		if (_downCount >= 1.0f)
		{
			_downCount = 0;
			ChangeAnim((int)LEFT_DIE_P4, "MagicianLeftDie4");
		}
		break;
	case Magician::RIGHT_DIE_P4:
		if (!_anim->isPlay())
		{
			ChangeAnim((int)RIGHT_IDLE, "MagicianRightIdle");
		}
		break;
	case Magician::LEFT_DIE_P4:
		if (!_anim->isPlay())
		{
			ChangeAnim((int)LEFT_IDLE, "MagicianLeftIdle");
		}
		break;
	case Magician::RIGHT_OTHER:
		if (!_anim->isPlay())
		{
			ChangeAnim((int)RIGHT_IDLE, "MagicianRightIdle");
		}
		break;
	case Magician::LEFT_OTHER:
		if (!_anim->isPlay())
		{
			ChangeAnim((int)LEFT_IDLE, "MagicianLeftIdle");
		}
		break;
	}

	_y -= _jumpPower;
	_jumpPower -= _gravity;

	_colX = _x;
	_colY = _y + 32;

	_colRC = RectMakeCenter(_colX, _colY, 50, 100);
}

void Magician::Render()
{
    Character::Render();
}

void Magician::ChangeWeapon()
{
	switch (Character::_weapon)
	{
	case Character::WEAPON_1:
		_img = IMAGEMANAGER.findImage("Magician1");
		_weaponEffectName = "Magician_Weapon_1_B";
		break;
	case Character::WEAPON_2:
		_img = IMAGEMANAGER.findImage("Magician2");
		_weaponEffectName = "Magician_Weapon_2_B";
		break;
	case Character::WEAPON_3:
		_img = IMAGEMANAGER.findImage("Magician3");
		_weaponEffectName = "Magician_Weapon_3_B";
		break;
	case Character::WEAPON_4:
		_img = IMAGEMANAGER.findImage("Magician4");
		_weaponEffectName = "Magician_Weapon_4_B";
		break;
	}
}

void Magician::ChangeAnim(int state, string animKey)
{
    _state = (STATE)state;
    _anim = ANIMATIONKEY.findAnimation(animKey);
    _anim->start();
}

void Magician::Collision()
{
	if (_state == RIGHT_HIT_1 || _state == LEFT_HIT_1 ||
		_state == RIGHT_HIT_2 || _state == LEFT_HIT_2 ||
		_state == RIGHT_DIE_P1 || _state == LEFT_DIE_P1 ||
		_state == RIGHT_DIE_P2 || _state == LEFT_DIE_P2 ||
		_state == RIGHT_DIE_P3 || _state == LEFT_DIE_P3 ||
		_state == RIGHT_DIE_P4 || _state == LEFT_DIE_P4 ||
		_state == RIGHT_OTHER || _state == LEFT_OTHER) return;

	_hp -= 10;

	if (_hp <= 0)
	{
		_friction = 5;
		_jumpPower = 5;
		_gravity = 0.3f;
		_startY = _y;
		if (_state == RIGHT_IDLE || _state == RIGHT_RUN || _state == RIGHT_ATTACK)
			ChangeAnim((int)RIGHT_DIE_P1, "MagicianRightDie1");
		else if (_state == LEFT_IDLE || _state == LEFT_RUN || _state == LEFT_ATTACK)
			ChangeAnim((int)LEFT_DIE_P1, "MagicianLeftDie1");

		return;
	}

	_friction = 5;

	int rnd = RND.GetInt(2);

	if (rnd == 0)
	{
		if (_state == RIGHT_IDLE || _state == RIGHT_RUN || _state == RIGHT_ATTACK)
			ChangeAnim((int)RIGHT_HIT_1, "MagicianRightHit1");
		else if (_state == LEFT_IDLE || _state == LEFT_RUN || _state == LEFT_ATTACK)
			ChangeAnim((int)LEFT_HIT_1, "MagicianLeftHit1");
	}
	else
	{
		if (_state == RIGHT_IDLE || _state == RIGHT_RUN || _state == RIGHT_ATTACK)
			ChangeAnim((int)RIGHT_HIT_2, "MagicianRightHit2");
		else if (_state == LEFT_IDLE || _state == LEFT_RUN || _state == LEFT_ATTACK)
			ChangeAnim((int)LEFT_HIT_2, "MagicianLeftHit2");
	}
}

void Magician::InitBullet()
{
	IMAGEMANAGER.addFrameImage("Magician_Weapon_1_B", PathFile("image\\Character", "Magician_Weapon_1_Bullet").c_str(), 342, 114, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER.addFrameImage("Magician_Weapon_2_B", PathFile("image\\Character", "Magician_Weapon_2_Bullet").c_str(), 78, 124, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER.addFrameImage("Magician_Weapon_3_B", PathFile("image\\Character", "Magician_Weapon_3_Bullet").c_str(), 144, 48, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER.addFrameImage("Magician_Weapon_4_B", PathFile("image\\Character", "Magician_Weapon_4_Bullet").c_str(), 1190, 64, 7, 2, true, RGB(255, 0, 255));
	//                  이름, 이미지, 갯수, 애니여부, 애니속도, Y인덱스 갯수
	BULLET.BulletSetting("Magician_Weapon_1_B", IMAGEMANAGER.findImage("Magician_Weapon_1_B"), 1, true, 17, 2);
	BULLET.BulletSetting("Magician_Weapon_2_B", IMAGEMANAGER.findImage("Magician_Weapon_2_B"), 1, true, 15, 2);
	BULLET.BulletSetting("Magician_Weapon_3_B", IMAGEMANAGER.findImage("Magician_Weapon_3_B"), 1, true, 15, 2);
	BULLET.BulletSetting("Magician_Weapon_4_B", IMAGEMANAGER.findImage("Magician_Weapon_4_B"), 1, true, 20, 2);
	
	IMAGEMANAGER.addImage("Magician_Weapon_1_B_Shandow", PathFile("image\\Character", "Magician_Weapon_1_B_Shandow").c_str(), 24, 12, true, RGB(255, 0, 255));

	BULLET.BulletShadowSetting("Magician_Weapon_1_B", IMAGEMANAGER.findImage("Magician_Weapon_1_B_Shandow"), RectMake(0, 0, 40, 40), 55);
	BULLET.BulletShadowSetting("Magician_Weapon_2_B", IMAGEMANAGER.findImage("Magician_Weapon_1_B_Shandow"), RectMake(0, 0, 40, 40), 55);
	BULLET.BulletShadowSetting("Magician_Weapon_3_B", IMAGEMANAGER.findImage("Magician_Weapon_1_B_Shandow"), RectMake(0, 0, 40, 40), 55);
	BULLET.BulletShadowSetting("Magician_Weapon_4_B", IMAGEMANAGER.findImage("Magician_Weapon_1_B_Shandow"), RectMake(0, 0, 40, 40), 55);

	ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("Magician_Weapon_1_B")[0]);
	ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("Magician_Weapon_2_B")[0]);
	ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("Magician_Weapon_3_B")[0]);
	ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("Magician_Weapon_4_B")[0]);

	EFFECTMANAGER.addEffect("Magician_Weapon_1_Effect", "Magician_Weapon_1_Effect", 312, 52, 52, 52, 1, 5, 1);
}
