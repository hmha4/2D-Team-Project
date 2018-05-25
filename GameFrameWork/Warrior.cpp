#include "stdafx.h"
#include "Warrior.h"


Warrior::Warrior()
{
}


Warrior::~Warrior()
{
}

HRESULT Warrior::Init(float x, float y, int player)
{
	Character::Init(x, y, player);

	// ======== 이미지 초기화 ======== //
	IMAGEMANAGER.addFrameImage("Warrior1", PathFile("image\\Character", "Warrior_Weapon_1").c_str(), 1200, 1400, 10, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER.addFrameImage("Warrior2", PathFile("image\\Character", "Warrior_Weapon_2").c_str(), 1200, 1400, 10, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER.addFrameImage("Warrior3", PathFile("image\\Character", "Warrior_Weapon_3").c_str(), 1200, 1400, 10, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER.addFrameImage("Warrior4", PathFile("image\\Character", "Warrior_Weapon_4").c_str(), 1200, 1400, 10, 7, true, RGB(255, 0, 255));
	_img = IMAGEMANAGER.findImage("Warrior1");
	// ============================== //

	// ======== 애니메이션 초기화 ======== //
	char * warrior = "Warrior1";

	//IDLE
	int rightIdle[] = { 0 };
	ANIMATIONKEY.addArrayFrameAnimation("WarriorRightIdle", warrior, rightIdle, 1, 5, true);
	int leftIdle[] = { 10 };
	ANIMATIONKEY.addArrayFrameAnimation("WarriorLeftIdle", warrior, leftIdle, 1, 5, true);
	//RUN
	int rightRun[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	ANIMATIONKEY.addArrayFrameAnimation("WarriorRightRun", warrior, rightRun, 8, 10, true);
	int leftRun[] = { 11, 12, 13, 14, 15, 16, 17, 18 };
	ANIMATIONKEY.addArrayFrameAnimation("WarriorLeftRun", warrior, leftRun, 8, 10, true);
	//JUMP
	int rightJump[] = { 20, 21 };
	ANIMATIONKEY.addArrayFrameAnimation("WarriorRightJump", warrior, rightJump, 2, 10, false);
	int leftJump[] = { 23, 24 };
	ANIMATIONKEY.addArrayFrameAnimation("WarriorLeftJump", warrior, leftJump, 2, 10, false);
	//FALL
	int rightFall[] = { 22 };
	ANIMATIONKEY.addArrayFrameAnimation("WarriorRightFall", warrior, rightFall, 1, 10, false);
	int leftFall[] = { 25 };
	ANIMATIONKEY.addArrayFrameAnimation("WarriorLeftFall", warrior, leftFall, 1, 10, false);
	//ATTACK
	int rightAttack[] = { 30, 31, 32 };
	ANIMATIONKEY.addArrayFrameAnimation("WarriorRightAttack", warrior, rightAttack, 3, 10, false);
	int leftAttack[] = { 33, 34, 35 };
	ANIMATIONKEY.addArrayFrameAnimation("WarriorLeftAttack", warrior, leftAttack, 3, 10, false);
	//JUMP ATTACK
	int rightJumpAttack[] = { 40, 41, 42 };
	ANIMATIONKEY.addArrayFrameAnimation("WarriorRightJumpAttack", warrior, rightJumpAttack, 3, 10, false);
	int leftJumpAttack[] = { 43, 44, 45 };
	ANIMATIONKEY.addArrayFrameAnimation("WarriorLeftJumpAttack", warrior, leftJumpAttack, 3, 10, false);
	//JUMP ATTACK
	int rightBlock[] = { 46 };
	ANIMATIONKEY.addArrayFrameAnimation("WarriorRightBlock", warrior, rightBlock, 1, 10, true);
	int leftBlock[] = { 47 };
	ANIMATIONKEY.addArrayFrameAnimation("WarriorLeftBlock", warrior, leftBlock, 1, 10, true);
	//GET HIT 1
	int rightHit1[] = { 50 };
	ANIMATIONKEY.addArrayFrameAnimation("WarriorRightHit1", warrior, rightHit1, 1, 10, true);
	int leftHit1[] = { 60 };
	ANIMATIONKEY.addArrayFrameAnimation("WarriorLeftHit1", warrior, leftHit1, 1, 10, true);
	//GET HIT 2
	int rightHit2[] = { 51 };
	ANIMATIONKEY.addArrayFrameAnimation("WarriorRightHit2", warrior, rightHit2, 1, 10, true);
	int leftHit2[] = { 61 };
	ANIMATIONKEY.addArrayFrameAnimation("WarriorLeftHit2", warrior, leftHit2, 1, 10, true);
	//DIE PHASE 1
	int rightDiePhase1[] = { 52 };
	ANIMATIONKEY.addArrayFrameAnimation("WarriorRightDie1", warrior, rightDiePhase1, 1, 10, true);
	int leftDiePhase1[] = { 62 };
	ANIMATIONKEY.addArrayFrameAnimation("WarriorLeftDie1", warrior, leftDiePhase1, 1, 10, true);
	//DIE PHASE 1(FIRE)
	int rightDiePhase1Fire[] = { 26, 27, 28 };
	ANIMATIONKEY.addArrayFrameAnimation("WarriorRightDie1Fire", warrior, rightDiePhase1Fire, 3, 10, true);
	int leftDiePhase1Fire[] = { 36, 37, 38 };
	ANIMATIONKEY.addArrayFrameAnimation("WarriorLeftDie1Fire", warrior, leftDiePhase1Fire, 3, 10, true);
	//DIE PHASE 1(ICE)
	int rightDiePhase1Ice[] = { 29 };
	ANIMATIONKEY.addArrayFrameAnimation("WarriorRightDie1Ice", warrior, rightDiePhase1Ice, 1, 1, false);
	int leftDiePhase1Ice[] = { 39 };
	ANIMATIONKEY.addArrayFrameAnimation("WarriorLeftDie1Ice", warrior, leftDiePhase1Ice, 1, 1, false);
	//DIE PHASE 2
	int rightDiePhase2[] = { 53 };
	ANIMATIONKEY.addArrayFrameAnimation("WarriorRightDie2", warrior, rightDiePhase2, 1, 10, true);
	int leftDiePhase2[] = { 63 };
	ANIMATIONKEY.addArrayFrameAnimation("WarriorLeftDie2", warrior, leftDiePhase2, 1, 10, true);
	//DIE PHASE 3
	int rightDiePhase3[] = { 54 };
	ANIMATIONKEY.addArrayFrameAnimation("WarriorRightDie3", warrior, rightDiePhase3, 1, 10, true);
	int leftDiePhase3[] = { 64 };
	ANIMATIONKEY.addArrayFrameAnimation("WarriorLeftDie3", warrior, leftDiePhase3, 1, 10, true);
	//DIE PHASE 4
	int rightDiePhase4[] = { 55, 56, 57 };
	ANIMATIONKEY.addArrayFrameAnimation("WarriorRightDie4", warrior, rightDiePhase4, 3, 10, false);
	int leftDiePhase4[] = { 65, 66, 67 };
	ANIMATIONKEY.addArrayFrameAnimation("WarriorLeftDie4", warrior, leftDiePhase4, 3, 10, false);
	//OTHER
	int rightOther[] = { 9 };
	ANIMATIONKEY.addArrayFrameAnimation("WarriorRightOther", warrior, rightOther, 1, 1, false);
	int leftDieOther[] = { 19 };
	ANIMATIONKEY.addArrayFrameAnimation("WarriorLeftOther", warrior, leftDieOther, 1, 1, false);


	_state = RIGHT_IDLE;
	_anim = ANIMATIONKEY.findAnimation("WarriorRightIdle");
	_anim->start();

	// ============================== //

	

	// 총알 초기화
	InitBullet();

	return S_OK;
}

void Warrior::Release()
{
	Character::Release();
}

void Warrior::Update()
{
	Character::Update();

	ChangeWeapon();

	//	점프
	if (KEYMANAGER.isOnceKeyDown(_mControl["Jump"]))
	{
		if (_state != RIGHT_HIT_1 && _state != LEFT_HIT_1 &&
			_state != RIGHT_HIT_2 && _state != LEFT_HIT_2 &&
			_state != RIGHT_DIE_P1 && _state != LEFT_DIE_P1 &&
			_state != RIGHT_DIE_P2 && _state != LEFT_DIE_P2 &&
			_state != RIGHT_DIE_P3 && _state != LEFT_DIE_P3 &&
			_state != RIGHT_DIE_P4 && _state != LEFT_DIE_P4 &&
			_state != RIGHT_BLOCK && _state != LEFT_BLOCK &&
			_state != RIGHT_OTHER && _state != LEFT_OTHER)
		{
			_jumpPower = 7;
			_gravity = 0.3f;
			_startY = _y;
			if (_state == RIGHT_IDLE || _state == RIGHT_RUN ||
				_state == RIGHT_UP_RUN || _state == RIGHT_DOWN_RUN)
				ChangeAnim((int)RIGHT_JUMP, "WarriorRightJump");
			else if (_state == LEFT_IDLE || _state == LEFT_RUN ||
				_state == LEFT_UP_RUN || _state == LEFT_DOWN_RUN)
				ChangeAnim((int)LEFT_JUMP, "WarriorLeftJump");
		}
	}

	//	공격
	if (KEYMANAGER.isOnceKeyDown(_mControl["Attack"]))
	{
		if (_state == RIGHT_IDLE || _state == RIGHT_RUN ||
			_state == RIGHT_JUMP || _state == RIGHT_FALL)
		{
			BULLET.Shot(_weaponEffectName, _colX + 40, _colY - 20, 0, 0, 2, 0);
			SOUNDMANAGER.play("23PlayerSwing");
		}
		else if (_state == LEFT_IDLE || _state == LEFT_RUN ||
			_state == LEFT_JUMP || _state == LEFT_FALL)
		{
			BULLET.Shot(_weaponEffectName, _colX - 40, _colY - 20, 0, 0, -2, 1);
			SOUNDMANAGER.play("23PlayerSwing");
		}

		if (_state == RIGHT_IDLE || _state == RIGHT_RUN)
			ChangeAnim((int)RIGHT_ATTACK, "WarriorRightAttack");
		else if (_state == LEFT_IDLE || _state == LEFT_RUN)
			ChangeAnim((int)LEFT_ATTACK, "WarriorLeftAttack");
		else if (_state == RIGHT_JUMP || _state == RIGHT_FALL)
			ChangeAnim((int)RIGHT_JUMP_ATTACK, "WarriorRightJumpAttack");
		else if (_state == LEFT_JUMP || _state == LEFT_FALL)
			ChangeAnim((int)LEFT_JUMP_ATTACK, "WarriorLeftJumpAttack");
	}

	//	방어
	if (KEYMANAGER.isOnceKeyDown(_mControl["Block"]))
	{
		if (_state == RIGHT_IDLE || _state == RIGHT_RUN)
			ChangeAnim((int)RIGHT_BLOCK, "WarriorRightBlock");
		else if (_state == LEFT_IDLE || _state == LEFT_RUN)
			ChangeAnim((int)LEFT_BLOCK, "WarriorLeftBlock");
	}

	//	죽었을 때 무적 시간
	if (_deadTime > 0)
	{
		_alphaCount += TIMEMANAGER.getElapsedTime();
		if (_alphaCount >= 0.02)
		{
			_alphaCount = 0;
			if (_alpha == 255)
				_alpha = 0;
			else _alpha = 255;
		}

		_deadTime -= TIMEMANAGER.getElapsedTime();
		if (_deadTime <= 0)
		{
			_alpha = 255;
			_deadTime = 0;
		}
	}

	//	워리어 FSM
	switch (_state)
	{
	case Warrior::RIGHT_IDLE:
		if (_hp <= 0)
		{
			_hp = 10;
			ChangeAnim((int)RIGHT_OTHER, "WarriorRightOther");
			SOUNDMANAGER.play("19PlayerRoar");
			break;
		}
		if (KEYMANAGER.isStayKeyDown(_mControl["Right"]))
		{
			_speedX = 3;
			ChangeAnim((int)RIGHT_RUN, "WarriorRightRun");
		}
		if (KEYMANAGER.isStayKeyDown(_mControl["Left"]))
		{
			_speedX = 3;
			ChangeAnim((int)LEFT_RUN, "WarriorLeftRun");
		}
		if (KEYMANAGER.isStayKeyDown(_mControl["Up"]))
		{
			_speedY = 1;
			ChangeAnim((int)RIGHT_UP_RUN, "WarriorRightRun");
		}
		if (KEYMANAGER.isStayKeyDown(_mControl["Down"]))
		{
			_speedY = 1;
			ChangeAnim((int)RIGHT_DOWN_RUN, "WarriorRightRun");
		}
		break;
	case Warrior::LEFT_IDLE:
		if (_hp <= 0)
		{
			_hp = 10;
			ChangeAnim((int)LEFT_OTHER, "WarriorLeftOther");
			SOUNDMANAGER.play("19PlayerRoar");
			break;
		}
		if (KEYMANAGER.isStayKeyDown(_mControl["Right"]))
		{
			_speedX = 3;
			ChangeAnim((int)RIGHT_RUN, "WarriorRightRun");
		}
		if (KEYMANAGER.isStayKeyDown(_mControl["Left"]))
		{
			_speedX = 3;
			ChangeAnim((int)LEFT_RUN, "WarriorLeftRun");
		}
		if (KEYMANAGER.isStayKeyDown(_mControl["Up"]))
		{
			_speedY = 1;
			ChangeAnim((int)LEFT_UP_RUN, "WarriorLeftRun");
		}
		if (KEYMANAGER.isStayKeyDown(_mControl["Down"]))
		{
			_speedY = 1;
			ChangeAnim((int)LEFT_DOWN_RUN, "WarriorLeftRun");
		}
		break;
	case Warrior::RIGHT_RUN:
		_speedX = 3;
		_x += _speedX;

		_speedY = 1;
		if (KEYMANAGER.isStayKeyDown(_mControl["Up"]))
			_y -= _speedY;
		else if (KEYMANAGER.isStayKeyDown(_mControl["Down"]))
			_y += _speedY;
		if (!KEYMANAGER.isStayKeyDown(_mControl["Right"]))
		{
			ChangeAnim((int)RIGHT_IDLE, "WarriorRightIdle");
		}
		break;
	case Warrior::LEFT_RUN:
		_speedX = 3;
		_x -= _speedX;

		_speedY = 1;
		if (KEYMANAGER.isStayKeyDown(_mControl["Up"]))
			_y -= _speedY;
		else if (KEYMANAGER.isStayKeyDown(_mControl["Down"]))
			_y += _speedY;
		if (!KEYMANAGER.isStayKeyDown(_mControl["Left"]))
		{
			ChangeAnim((int)LEFT_IDLE, "WarriorLeftIdle");
		}
		break;
	case Warrior::RIGHT_UP_RUN:
		_y -= _speedY;

		if (KEYMANAGER.isOnceKeyDown(_mControl["Left"]))
			ChangeAnim((int)LEFT_RUN, "WarriorLeftRun");
		else if (KEYMANAGER.isOnceKeyDown(_mControl["Right"]))
			ChangeAnim((int)RIGHT_RUN, "WarriorRightRun");

		if (KEYMANAGER.isStayKeyDown(_mControl["Left"]))
			_x -= _speedX;
		else if (KEYMANAGER.isStayKeyDown(_mControl["Right"]))
			_x += _speedX;
		if (!KEYMANAGER.isStayKeyDown(_mControl["Up"]))
		{
			ChangeAnim((int)RIGHT_IDLE, "WarriorRightIdle");
		}
		break;
	case Warrior::LEFT_UP_RUN:
		_y -= _speedY;

		if (KEYMANAGER.isOnceKeyDown(_mControl["Left"]))
			ChangeAnim((int)LEFT_RUN, "WarriorLeftRun");
		else if (KEYMANAGER.isOnceKeyDown(_mControl["Right"]))
			ChangeAnim((int)RIGHT_RUN, "WarriorRightRun");

		if (KEYMANAGER.isStayKeyDown(_mControl["Left"]))
			_x -= _speedX;
		else if (KEYMANAGER.isStayKeyDown(_mControl["Right"]))
			_x += _speedX;
		if (!KEYMANAGER.isStayKeyDown(_mControl["Up"]))
		{
			ChangeAnim((int)LEFT_IDLE, "WarriorLeftIdle");
		}
		break;
	case Warrior::RIGHT_DOWN_RUN:
		_y += _speedY;

		if (KEYMANAGER.isOnceKeyDown(_mControl["Left"]))
			ChangeAnim((int)LEFT_RUN, "WarriorLeftRun");
		else if (KEYMANAGER.isOnceKeyDown(_mControl["Right"]))
			ChangeAnim((int)RIGHT_RUN, "WarriorRightRun");

		if (KEYMANAGER.isStayKeyDown(_mControl["Left"]))
			_x -= _speedX;
		else if (KEYMANAGER.isStayKeyDown(_mControl["Right"]))
			_x += _speedX;
		if (KEYMANAGER.isOnceKeyUp(_mControl["Down"]))
		{
			ChangeAnim((int)RIGHT_IDLE, "WarriorRightIdle");
		}
		break;
	case Warrior::LEFT_DOWN_RUN:
		_y += _speedY;

		if (KEYMANAGER.isOnceKeyDown(_mControl["Left"]))
			ChangeAnim((int)LEFT_RUN, "WarriorLeftRun");
		else if (KEYMANAGER.isOnceKeyDown(_mControl["Right"]))
			ChangeAnim((int)RIGHT_RUN, "WarriorRightRun");

		if (KEYMANAGER.isStayKeyDown(_mControl["Left"]))
			_x -= _speedX;
		else if (KEYMANAGER.isStayKeyDown(_mControl["Right"]))
			_x += _speedX;
		if (KEYMANAGER.isOnceKeyUp(_mControl["Down"]))
		{
			ChangeAnim((int)LEFT_IDLE, "WarriorLeftIdle");
		}
		break;
	case Warrior::RIGHT_JUMP:
		if (_jumpPower <= 0)
			ChangeAnim((int)RIGHT_FALL, "WarriorRightFall");
		break;
	case Warrior::LEFT_JUMP:
		if (_jumpPower <= 0)
			ChangeAnim((int)LEFT_FALL, "WarriorLeftFall");
		break;
	case Warrior::RIGHT_FALL:
		if (_y >= _startY)
		{
			_y = _startY;
			_jumpPower = 0;
			_gravity = 0;
			ChangeAnim((int)RIGHT_IDLE, "WarriorRightIdle");
			SOUNDMANAGER.play("24PlayerLand");
		}
		break;
	case Warrior::LEFT_FALL:
		if (_y >= _startY)
		{
			_y = _startY;
			_jumpPower = 0;
			_gravity = 0;
			ChangeAnim((int)LEFT_IDLE, "WarriorLeftIdle");
			SOUNDMANAGER.play("24PlayerLand");
		}
		break;
	case Warrior::RIGHT_ATTACK:
		if (!_anim->isPlay())
		{
			ChangeAnim((int)RIGHT_IDLE, "WarriorRightIdle");
			BULLET.Destroy(_weaponEffectName, 0);
		}
		break;
	case Warrior::LEFT_ATTACK:
		if (!_anim->isPlay())
		{
			ChangeAnim((int)LEFT_IDLE, "WarriorLeftIdle");
			BULLET.Destroy(_weaponEffectName, 0);
		}
		break;
	case Warrior::RIGHT_JUMP_ATTACK:
		if (_y >= _startY)
		{
			_y = _startY;
			_jumpPower = 0;
			_gravity = 0;
			ChangeAnim((int)RIGHT_IDLE, "WarriorRightIdle");
			BULLET.Destroy(_weaponEffectName, 0);
			break;
		}
		if (!_anim->isPlay())
		{
			ChangeAnim((int)RIGHT_FALL, "WarriorRightFall");
			BULLET.Destroy(_weaponEffectName, 0);
		}
		break;
	case Warrior::LEFT_JUMP_ATTACK:
		if (_y >= _startY)
		{
			_y = _startY;
			_jumpPower = 0;
			_gravity = 0;
			ChangeAnim((int)LEFT_IDLE, "WarriorLeftIdle");
			BULLET.Destroy(_weaponEffectName, 0);
			break;
		}
		if (!_anim->isPlay())
		{
			ChangeAnim((int)LEFT_FALL, "WarriorLeftFall");
			BULLET.Destroy(_weaponEffectName, 0);
		}
		break;
	case Warrior::RIGHT_BLOCK:
		if (KEYMANAGER.isOnceKeyUp(_mControl["Block"]))
			ChangeAnim((int)RIGHT_IDLE, "WarriorRightIdle");
		break;
	case Warrior::LEFT_BLOCK:
		if (KEYMANAGER.isOnceKeyUp(_mControl["Block"]))
			ChangeAnim((int)LEFT_IDLE, "WarriorLeftIdle");
		break;
	case Warrior::RIGHT_HIT_1:
		_x -= _friction;
		_friction -= 0.3f;
		if (_friction <= 0)
		{
			_friction = 0;
			ChangeAnim((int)RIGHT_IDLE, "WarriorRightIdle");
		}
		break;
	case Warrior::LEFT_HIT_1:
		_x += _friction;
		_friction -= 0.3f;
		if (_friction <= 0)
		{
			_friction = 0;
			ChangeAnim((int)LEFT_IDLE, "WarriorLeftIdle");
		}
		break;
	case Warrior::RIGHT_HIT_2:
		_x -= _friction;
		_friction -= 0.3f;
		if (_friction <= 0)
		{
			_friction = 0;
			ChangeAnim((int)RIGHT_IDLE, "WarriorRightIdle");
		}
		break;
	case Warrior::LEFT_HIT_2:
		_x += _friction;
		_friction -= 0.3f;
		if (_friction <= 0)
		{
			_friction = 0;
			ChangeAnim((int)LEFT_IDLE, "WarriorLeftIdle");
		}
		break;
	case Warrior::RIGHT_DIE_P1:
		_x -= _friction;
		_friction -= 0.1f;

		if (_jumpPower <= 0)
			ChangeAnim((int)RIGHT_DIE_P2, "WarriorRightDie2");
		break;
	case Warrior::LEFT_DIE_P1:
		_x += _friction;
		_friction -= 0.1f;

		if (_jumpPower <= 0)
			ChangeAnim((int)LEFT_DIE_P2, "WarriorLeftDie2");
		break;
	case Warrior::RIGHT_DIE_PF:
		_x -= _friction;
		_friction -= 0.1f;

		if (_jumpPower <= 0)
			ChangeAnim((int)RIGHT_DIE_P2, "WarriorRightDie2");
		break;
	case Warrior::LEFT_DIE_PF:
		_x += _friction;
		_friction -= 0.1f;

		if (_jumpPower <= 0)
			ChangeAnim((int)LEFT_DIE_P2, "WarriorLeftDie2");
		break;
	case Warrior::RIGHT_DIE_PI:
		if (!_anim->isPlay())
		{
			_friction = 5;
			_jumpPower = 5;
			_gravity = 0.3f;
			_startY = _y;
			ChangeAnim((int)RIGHT_DIE_P1, "WarriorRightDie1");
		}
		break;
	case Warrior::LEFT_DIE_PI:
		if (!_anim->isPlay())
		{
			_friction = 5;
			_jumpPower = 5;
			_gravity = 0.3f;
			_startY = _y;
			ChangeAnim((int)LEFT_DIE_P1, "WarriorLeftDie1");
		}
		break;
	case Warrior::RIGHT_DIE_P2:
		_x -= _friction;
		_friction -= 0.1f;
		if (_friction <= 0) _friction = 0;

		if (_friction <= 0 && _y >= _startY)
		{
			_friction = 0;
			_jumpPower = 0;
			_gravity = 0;
			_y = _startY;
			ChangeAnim((int)RIGHT_DIE_P3, "WarriorRightDie3");
			SOUNDMANAGER.play("24PlayerLand");
		}
		else if (_friction > 0 && _y >= _startY)
		{
			_jumpPower = 2;
			_gravity = 0.3f;
			SOUNDMANAGER.play("24PlayerLand");
		}
		break;
	case Warrior::LEFT_DIE_P2:
		_x += _friction;
		_friction -= 0.1f;
		if (_friction <= 0) _friction = 0;

		if (_friction <= 0 && _y >= _startY)
		{
			_friction = 0;
			_jumpPower = 0;
			_gravity = 0;
			_y = _startY;
			ChangeAnim((int)LEFT_DIE_P3, "WarriorLeftDie3");
			SOUNDMANAGER.play("24PlayerLand");
		}
		else if (_friction > 0 && _y >= _startY)
		{
			SOUNDMANAGER.play("24PlayerLand");
			_jumpPower = 2;
			_gravity = 0.3f;
		}
		break;
	case Warrior::RIGHT_DIE_P3:
		_downCount += TIMEMANAGER.getElapsedTime();
		if (_downCount >= 1.0f)
		{
			_downCount = 0;
			ChangeAnim((int)RIGHT_DIE_P4, "WarriorRightDie4");
		}
		break;
	case Warrior::LEFT_DIE_P3:
		_downCount += TIMEMANAGER.getElapsedTime();
		if (_downCount >= 1.0f)
		{
			_downCount = 0;
			ChangeAnim((int)LEFT_DIE_P4, "WarriorLeftDie4");
		}
		break;
	case Warrior::RIGHT_DIE_P4:
		if (!_anim->isPlay())
		{
			ChangeAnim((int)RIGHT_IDLE, "WarriorRightIdle");
		}
		break;
	case Warrior::LEFT_DIE_P4:
		if (!_anim->isPlay())
		{
			ChangeAnim((int)LEFT_IDLE, "WarriorLeftIdle");
		}
		break;
	case Warrior::RIGHT_OTHER:
		if (!_anim->isPlay())
		{
			_deadTime = 2.0f;
			ChangeAnim((int)RIGHT_IDLE, "WarriorRightIdle");
		}
		break;
	case Warrior::LEFT_OTHER:
		if (!_anim->isPlay())
		{
			_deadTime = 2.0f;
			ChangeAnim((int)LEFT_IDLE, "WarriorLeftIdle");
		}
		break;
	}

	_y -= _jumpPower;
	_jumpPower -= _gravity;

	_colX = _x;
	_colY = _y + 32;

	_colRC = RectMakeCenter(_colX, _colY, 50, 100);
	if (_state != RIGHT_JUMP && _state != LEFT_JUMP &&
		_state != RIGHT_JUMP_ATTACK && _state != LEFT_JUMP_ATTACK &&
		_state != RIGHT_FALL && _state != LEFT_FALL)
		_shadow = RectMakeCenter(_x, _y + _img->GetFreamHeight() / 2 - 25, 50, 20);
}

void Warrior::Render()
{
	Character::Render();

	//Rectangle(getMemDC(), _colRC.left, _colRC.top, _colRC.right, _colRC.bottom);
}

void Warrior::ChangeWeapon()
{
	switch (Character::_weapon)
	{
	case Character::WEAPON_1:
		_img = IMAGEMANAGER.findImage("Warrior1");
		_weaponEffectName = "Warrior_Weapon_1_B";
		_hp = 10;
		_maxHp = 10;
		_atk = 1;
		break;
	case Character::WEAPON_2:
		_img = IMAGEMANAGER.findImage("Warrior2");
		_weaponEffectName = "Warrior_Weapon_2_B";
		_hp = 15;
		_maxHp = 15;
		_atk = 2;
		break;
	case Character::WEAPON_3:
		_img = IMAGEMANAGER.findImage("Warrior3");
		_weaponEffectName = "Warrior_Weapon_3_B";
		_hp = 20;
		_maxHp = 20;
		_atk = 3;
		break;
	case Character::WEAPON_4:
		_img = IMAGEMANAGER.findImage("Warrior4");
		_weaponEffectName = "Warrior_Weapon_4_B";
		_hp = 20;
		_maxHp = 20;
		_atk = 4;
		break;
	}
}

void Warrior::ChangeAnim(int state, string animKey)
{
	_state = (STATE)state;
	_anim = ANIMATIONKEY.findAnimation(animKey);
	_anim->start();
}

void Warrior::Collision(RECT rc)
{
	if (_state == RIGHT_HIT_1 || _state == LEFT_HIT_1 ||
		_state == RIGHT_HIT_2 || _state == LEFT_HIT_2 ||
		_state == RIGHT_DIE_P1 || _state == LEFT_DIE_P1 ||
		_state == RIGHT_DIE_P2 || _state == LEFT_DIE_P2 ||
		_state == RIGHT_DIE_P3 || _state == LEFT_DIE_P3 ||
		_state == RIGHT_DIE_P4 || _state == LEFT_DIE_P4 ||
		_state == RIGHT_BLOCK || _state == LEFT_BLOCK ||
		_state == RIGHT_OTHER || _state == LEFT_OTHER ||
		_state == RIGHT_JUMP || _state == LEFT_JUMP ||
		_state == RIGHT_FALL || _state == LEFT_FALL ||
		_state == RIGHT_JUMP_ATTACK || _state == LEFT_JUMP_ATTACK || _deadTime > 0) return;

	_hp -= 1;

	POINT pos = GetCenterPos(rc);

	bool isLeft = false;
	if (pos.x > _x) isLeft = false;
	else isLeft = true;

	if (_hp <= 0)
	{
		SOUNDMANAGER.play("22PlayerDie");
		_friction = 5;
		_jumpPower = 5;
		_gravity = 0.3f;
		_startY = _y;
		if (!isLeft)
			ChangeAnim((int)RIGHT_DIE_P1, "WarriorRightDie1");
		else if (isLeft)
			ChangeAnim((int)LEFT_DIE_P1, "WarriorLeftDie1");

		return;
	}

	_friction = 5;

	int rnd = RND.GetInt(2);

	if (rnd == 0)
	{
		SOUNDMANAGER.play("20PlayerHurt1");
		if (!isLeft)
			ChangeAnim((int)RIGHT_HIT_1, "WarriorRightHit1");
		else if (isLeft)
			ChangeAnim((int)LEFT_HIT_1, "WarriorLeftHit1");
	}
	else
	{
		SOUNDMANAGER.play("21PlayerHurt2");
		if (!isLeft)
			ChangeAnim((int)RIGHT_HIT_2, "WarriorRightHit2");
		else if (isLeft)
			ChangeAnim((int)LEFT_HIT_2, "WarriorLeftHit2");
	}
}

void Warrior::MovementRestrict(int stage)
{
	if (stage == 0)
	{
		if (_y > 0)
		{
			if (_x < WINSIZEX / 2)
				_x += 3;
		}
		else
		{
			_gravity = 0.3f;
			_startY = WINSIZEY / 2;
		}
	}
	else if (stage == 10)
	{
		_x += 3;
	}
	else if (stage == 11)
	{
		_gravity = 0.3f;
		_startY = WINSIZEY + 100;
	}
	else
	{
		if (_shadow.left < CAM.GetRC().left)
		{
			_x = CAM.GetRC().left + (_colRC.right - _colRC.left) / 2;
			_speedX = 0;
		}
		else if (_shadow.right > CAM.GetRC().right)
		{
			_x = CAM.GetRC().right - (_colRC.right - _colRC.left) / 2;
			_speedX = 0;
		}

		if (_shadow.top < WINSIZEY / 2 - 25)
		{
			_y = WINSIZEY / 2 - 25 + (_shadow.bottom - _shadow.top) - _img->GetFreamHeight() / 2 + 15;
			_speedY = 0;
		}
		else if (_shadow.bottom > 400)
		{
			_y = 400 - _img->GetFreamHeight() / 2 + 15;
			_speedY = 0;
		}
	}
}

void Warrior::InitBullet()
{
	IMAGEMANAGER.addFrameImage("Warrior_Weapon_1_B", PathFile("image\\Character", "Warrior_Weapon_1_Bullet").c_str(), 280, 160, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER.addFrameImage("Warrior_Weapon_2_B", PathFile("image\\Character", "Warrior_Weapon_2_Bullet").c_str(), 280, 160, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER.addFrameImage("Warrior_Weapon_4_B", PathFile("image\\Character", "Warrior_Weapon_4_Bullet").c_str(), 280, 160, 4, 2, true, RGB(255, 0, 255));
	//                  이름, 이미지, 갯수, 애니여부, 애니속도, Y인덱스 갯수
	BULLET.BulletSetting("Warrior_Weapon_1_B", IMAGEMANAGER.findImage("Warrior_Weapon_1_B"), 1, true, 10, 2);
	BULLET.BulletSetting("Warrior_Weapon_2_B", IMAGEMANAGER.findImage("Warrior_Weapon_2_B"), 1, true, 10, 2);
	BULLET.BulletSetting("Warrior_Weapon_3_B", IMAGEMANAGER.findImage("Warrior_Weapon_1_B"), 1, true, 10, 2);
	BULLET.BulletSetting("Warrior_Weapon_4_B", IMAGEMANAGER.findImage("Warrior_Weapon_4_B"), 1, true, 10, 2);

	BULLET.BulletShadowSetting("Warrior_Weapon_1_B", nullptr, RectMake(0, 0, 40, 15), 70);
	BULLET.BulletShadowSetting("Warrior_Weapon_2_B", nullptr, RectMake(0, 0, 40, 15), 70);
	BULLET.BulletShadowSetting("Warrior_Weapon_3_B", nullptr, RectMake(0, 0, 40, 15), 70);
	BULLET.BulletShadowSetting("Warrior_Weapon_4_B", nullptr, RectMake(0, 0, 40, 15), 70);

	ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("Warrior_Weapon_1_B")[0]);
	ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("Warrior_Weapon_2_B")[0]);
	ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("Warrior_Weapon_3_B")[0]);
	ZORDER.InputObj((gameNode*)BULLET.GetBulletVec("Warrior_Weapon_4_B")[0]);
}
