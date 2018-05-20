#include "stdafx.h"
#include "Warrior.h"


Warrior::Warrior()
{
}


Warrior::~Warrior()
{
}

HRESULT Warrior::Init(float x, float y)
{
    Character::Init(x, y);

    IMAGEMANAGER.addFrameImage("Warrior1", "Warrior_Weapon_1.bmp", 1200, 1400, 10, 7, true, RGB(255, 0, 255));
    IMAGEMANAGER.addFrameImage("Warrior2", "Warrior_Weapon_2.bmp", 1200, 1400, 10, 7, true, RGB(255, 0, 255));
    IMAGEMANAGER.addFrameImage("Warrior3", "Warrior_Weapon_3.bmp", 1200, 1400, 10, 7, true, RGB(255, 0, 255));
    IMAGEMANAGER.addFrameImage("Warrior4", "Warrior_Weapon_4.bmp", 1200, 1400, 10, 7, true, RGB(255, 0, 255));
    _img = IMAGEMANAGER.findImage("Warrior1");

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

    _hp = 10;

    return S_OK;
}

void Warrior::Release()
{
    Character::Release();
}

void Warrior::Update()
{
    Character::Update();

    if (KEYMANAGER.isOnceKeyDown(VK_RIGHT))
    {
        _speedX = 3;
        ChangeAnim((int)RIGHT_IDLE, "WarriorRightIdle");
    }
    else if (KEYMANAGER.isOnceKeyDown(VK_LEFT))
    {
        _speedX = 3;
        ChangeAnim((int)LEFT_IDLE, "WarriorLeftIdle");
    }

    if (KEYMANAGER.isOnceKeyDown(VK_SPACE))
    {
        _jumpPower = 5;
        _gravity = 0.3f;
        _startY = _y;
        if (_state == RIGHT_IDLE || _state == RIGHT_RUN)
            ChangeAnim((int)RIGHT_JUMP, "WarriorRightJump");
        else if (_state == LEFT_IDLE || _state == LEFT_RUN)
            ChangeAnim((int)LEFT_JUMP, "WarriorLeftJump");
    }

    if (KEYMANAGER.isOnceKeyDown('Z'))
    {
        if (_state == RIGHT_IDLE || _state == RIGHT_RUN)
            ChangeAnim((int)RIGHT_ATTACK, "WarriorRightAttack");
        else if (_state == LEFT_IDLE || _state == LEFT_RUN)
            ChangeAnim((int)LEFT_ATTACK, "WarriorLeftAttack");
        else if (_state == RIGHT_JUMP || _state == RIGHT_FALL)
            ChangeAnim((int)RIGHT_JUMP_ATTACK, "WarriorRightJumpAttack");
        else if (_state == LEFT_JUMP || _state == LEFT_FALL)
            ChangeAnim((int)LEFT_JUMP_ATTACK, "WarriorLeftJumpAttack");
    }

    if (KEYMANAGER.isOnceKeyDown('X'))
    {
        if (_state == RIGHT_IDLE || _state == RIGHT_RUN)
            ChangeAnim((int)RIGHT_BLOCK, "WarriorRightBlock");
        else if (_state == LEFT_IDLE || _state == LEFT_RUN)
            ChangeAnim((int)LEFT_BLOCK, "WarriorLeftBlock");
    }
    if (KEYMANAGER.isOnceKeyDown('C'))
    {
        Collision();
    }

    switch (_state)
    {
    case Warrior::RIGHT_IDLE:
        if (_hp <= 0)
        {
            _hp = 10;
            ChangeAnim((int)RIGHT_OTHER, "WarriorRightOther");
            break;
        }
        if (KEYMANAGER.isStayKeyDown(VK_RIGHT))
        {
            _speedX = 3;
            ChangeAnim((int)RIGHT_RUN, "WarriorRightRun");
        }
        if (KEYMANAGER.isStayKeyDown(VK_LEFT))
        {
            _speedX = 3;
            ChangeAnim((int)LEFT_RUN, "WarriorLeftRun");
        }
        if (KEYMANAGER.isStayKeyDown(VK_UP))
        {
            _speedY = 1;
            ChangeAnim((int)RIGHT_UP_RUN, "WarriorRightRun");
        }
        if (KEYMANAGER.isStayKeyDown(VK_DOWN))
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
            break;
        }
        if (KEYMANAGER.isStayKeyDown(VK_RIGHT))
        {
            _speedX = 3;
            ChangeAnim((int)RIGHT_RUN, "WarriorRightRun");
        }
        if (KEYMANAGER.isStayKeyDown(VK_LEFT))
        {
            _speedX = 3;
            ChangeAnim((int)LEFT_RUN, "WarriorLeftRun");
        }
        if (KEYMANAGER.isStayKeyDown(VK_UP))
        {
            _speedY = 1;
            ChangeAnim((int)LEFT_UP_RUN, "WarriorLeftRun");
        }
        if (KEYMANAGER.isStayKeyDown(VK_DOWN))
        {
            _speedY = 1;
            ChangeAnim((int)LEFT_DOWN_RUN, "WarriorLeftRun");
        }
        break;
    case Warrior::RIGHT_RUN:
        _speedX = 3;
        _x += _speedX;

        _speedY = 1;
        if (KEYMANAGER.isStayKeyDown(VK_UP))
            _y -= _speedY;
        else if (KEYMANAGER.isStayKeyDown(VK_DOWN))
            _y += _speedY;
        if (KEYMANAGER.isOnceKeyUp(VK_RIGHT))
        {
            ChangeAnim((int)RIGHT_IDLE, "WarriorRightIdle");
        }
        break;
    case Warrior::LEFT_RUN:
        _speedX = 3;
        _x -= _speedX;

        _speedY = 1;
        if (KEYMANAGER.isStayKeyDown(VK_UP))
            _y -= _speedY;
        else if (KEYMANAGER.isStayKeyDown(VK_DOWN))
            _y += _speedY;
        if (KEYMANAGER.isOnceKeyUp(VK_LEFT))
        {
            ChangeAnim((int)LEFT_IDLE, "WarriorLeftIdle");
        }
        break;
    case Warrior::RIGHT_UP_RUN:
        _y -= _speedY;

        if (KEYMANAGER.isStayKeyDown(VK_LEFT))
            _x -= _speedX;
        else if (KEYMANAGER.isStayKeyDown(VK_RIGHT))
            _x += _speedX;
        if (KEYMANAGER.isOnceKeyUp(VK_UP))
        {
            ChangeAnim((int)RIGHT_IDLE, "WarriorRightIdle");
        }
        break;
    case Warrior::LEFT_UP_RUN:
        _y -= _speedY;

        if (KEYMANAGER.isStayKeyDown(VK_LEFT))
            _x -= _speedX;
        else if (KEYMANAGER.isStayKeyDown(VK_RIGHT))
            _x += _speedX;
        if (KEYMANAGER.isOnceKeyUp(VK_UP))
        {
            ChangeAnim((int)LEFT_IDLE, "WarriorLeftIdle");
        }
        break;
    case Warrior::RIGHT_DOWN_RUN:
        _y += _speedY;

        if (KEYMANAGER.isStayKeyDown(VK_LEFT))
            _x -= _speedX;
        else if (KEYMANAGER.isStayKeyDown(VK_RIGHT))
            _x += _speedX;
        if (KEYMANAGER.isOnceKeyUp(VK_DOWN))
        {
            ChangeAnim((int)RIGHT_IDLE, "WarriorRightIdle");
        }
        break;
    case Warrior::LEFT_DOWN_RUN:
        _y += _speedY;

        if (KEYMANAGER.isStayKeyDown(VK_LEFT))
            _x -= _speedX;
        else if (KEYMANAGER.isStayKeyDown(VK_RIGHT))
            _x += _speedX;
        if (KEYMANAGER.isOnceKeyUp(VK_DOWN))
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
        }
        break;
    case Warrior::LEFT_FALL:
        if (_y >= _startY)
        {
            _y = _startY;
            _jumpPower = 0;
            _gravity = 0;
            ChangeAnim((int)LEFT_IDLE, "WarriorLeftIdle");
        }
        break;
    case Warrior::RIGHT_ATTACK:
        if (!_anim->isPlay())
            ChangeAnim((int)RIGHT_IDLE, "WarriorRightIdle");
        break;
    case Warrior::LEFT_ATTACK:
        if (!_anim->isPlay())
            ChangeAnim((int)LEFT_IDLE, "WarriorLeftIdle");
        break;
    case Warrior::RIGHT_JUMP_ATTACK:
        if (_y >= _startY)
        {
            _y = _startY;
            _jumpPower = 0;
            _gravity = 0;
            ChangeAnim((int)RIGHT_IDLE, "WarriorRightIdle");
            break;
        }
        if (!_anim->isPlay())
            ChangeAnim((int)RIGHT_FALL, "WarriorRightFall");
        break;
    case Warrior::LEFT_JUMP_ATTACK:
        if (_y >= _startY)
        {
            _y = _startY;
            _jumpPower = 0;
            _gravity = 0;
            ChangeAnim((int)LEFT_IDLE, "WarriorLeftIdle");
            break;
        }
        if (!_anim->isPlay())
            ChangeAnim((int)LEFT_FALL, "WarriorLeftFall");
        break;
    case Warrior::RIGHT_BLOCK:
        if (KEYMANAGER.isOnceKeyUp('X'))
            ChangeAnim((int)RIGHT_IDLE, "WarriorRightIdle");
        break;
    case Warrior::LEFT_BLOCK:
        if (KEYMANAGER.isOnceKeyUp('X'))
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
        }
        else if (_friction > 0 && _y >= _startY)
        {
            _jumpPower = 2;
            _gravity = 0.3f;
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
        }
        else if (_friction > 0 && _y >= _startY)
        {
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
            ChangeAnim((int)RIGHT_IDLE, "WarriorRightIdle");
        }
        break;
    case Warrior::LEFT_OTHER:
        if (!_anim->isPlay())
        {
            ChangeAnim((int)LEFT_IDLE, "WarriorLeftIdle");
        }
        break;
    }

    _y -= _jumpPower;
    _jumpPower -= _gravity;

    _colX = _x;
    _colY = _y + 32;

    _colRC = RectMakeCenter(_colX, _colY, 50, 100);

    
    ANIMATIONKEY.update();
}

void Warrior::Render()
{
    Character::Render();

    Rectangle(getMemDC(), _colRC.left, _colRC.top, _colRC.right, _colRC.bottom);
}

void Warrior::ChangeWeapon()
{
    if (Character::_weapon == Character::WEAPON_1)
        _img = IMAGEMANAGER.findImage("Warrior1");
    else if (Character::_weapon == Character::WEAPON_2)
        _img = IMAGEMANAGER.findImage("Warrior2");
    else if (Character::_weapon == Character::WEAPON_3)
        _img = IMAGEMANAGER.findImage("Warrior3");
    else if (Character::_weapon == Character::WEAPON_4)
        _img = IMAGEMANAGER.findImage("Warrior4");
}

void Warrior::ChangeAnim(int state, string animKey)
{
    _state = (STATE)state;
    _anim = ANIMATIONKEY.findAnimation(animKey);
    _anim->start();
}

void Warrior::Collision()
{
    if (_state == RIGHT_HIT_1 || _state == LEFT_HIT_1 ||
        _state == RIGHT_HIT_2 || _state == LEFT_HIT_2 ||
        _state == RIGHT_DIE_P1 || _state == LEFT_DIE_P1 ||
        _state == RIGHT_DIE_P2 || _state == LEFT_DIE_P2 ||
        _state == RIGHT_DIE_P3 || _state == LEFT_DIE_P3 ||
        _state == RIGHT_DIE_P4 || _state == LEFT_DIE_P4 ||
        _state == RIGHT_BLOCK || _state == LEFT_BLOCK ||
        _state == RIGHT_OTHER || _state == LEFT_OTHER) return;

    _hp -= 1;

    if (_hp <= 0)
    {
        _friction = 5;
        _jumpPower = 5;
        _gravity = 0.3f;
        _startY = _y;
        if (_state == RIGHT_IDLE || _state == RIGHT_RUN || _state == RIGHT_ATTACK)
            ChangeAnim((int)RIGHT_DIE_P1, "WarriorRightDie1");
        else if (_state == LEFT_IDLE || _state == LEFT_RUN || _state == LEFT_ATTACK)
            ChangeAnim((int)LEFT_DIE_P1, "WarriorLeftDie1");

        return;
    }

    _friction = 5;
    
    int rnd = RND.GetInt(2);

    if (rnd == 0)
    {
        if (_state == RIGHT_IDLE || _state == RIGHT_RUN || _state == RIGHT_ATTACK)
            ChangeAnim((int)RIGHT_HIT_1, "WarriorRightHit1");
        else if (_state == LEFT_IDLE || _state == LEFT_RUN || _state == LEFT_ATTACK)
            ChangeAnim((int)LEFT_HIT_1, "WarriorLeftHit1");
    }
    else
    {
        if (_state == RIGHT_IDLE || _state == RIGHT_RUN || _state == RIGHT_ATTACK)
            ChangeAnim((int)RIGHT_HIT_2, "WarriorRightHit2");
        else if (_state == LEFT_IDLE || _state == LEFT_RUN || _state == LEFT_ATTACK)
            ChangeAnim((int)LEFT_HIT_2, "WarriorLeftHit2");
    }
}
