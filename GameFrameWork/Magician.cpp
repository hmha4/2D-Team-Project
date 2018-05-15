#include "stdafx.h"
#include "Magician.h"


Magician::Magician()
{
}


Magician::~Magician()
{
}

HRESULT Magician::Init(float x, float y)
{
    Character::Init(x, y);

    IMAGEMANAGER.addFrameImage("Magician1", "Magician_Weapon_1.bmp", 1200, 1400, 10, 7, true, RGB(255, 0, 255));
    IMAGEMANAGER.addFrameImage("Magician2", "Magician_Weapon_2.bmp", 1200, 1400, 10, 7, true, RGB(255, 0, 255));
    IMAGEMANAGER.addFrameImage("Magician3", "Magician_Weapon_3.bmp", 1200, 1400, 10, 7, true, RGB(255, 0, 255));
    IMAGEMANAGER.addFrameImage("Magician4", "Magician_Weapon_4.bmp", 1200, 1400, 10, 7, true, RGB(255, 0, 255));
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
    int leftJump[] = { 23, 24 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianLeftJump", magician, leftJump, 2, 10, false);
    //FALL
    int rightFall[] = { 22 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianRightFall", magician, rightFall, 1, 10, false);
    int leftFall[] = { 25 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianLeftFall", magician, leftFall, 1, 10, false);
    //ATTACK
    int rightAttack[] = { 30, 31, 32 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianRightAttack", magician, rightAttack, 3, 10, false);
    int leftAttack[] = { 33, 34, 35 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianLeftAttack", magician, leftAttack, 3, 10, false);
    //JUMP ATTACK
    int rightJumpAttack[] = { 40, 41, 42 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianRightJumpAttack", magician, rightJumpAttack, 3, 10, false);
    int leftJumpAttack[] = { 43, 44, 45 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianLeftJumpAttack", magician, leftJumpAttack, 3, 10, false);
    //JUMP ATTACK
    int rightBlock[] = { 46 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianRightBlock", magician, rightBlock, 1, 10, true);
    int leftBlock[] = { 47 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianLeftBlock", magician, leftBlock, 1, 10, true);
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
    int rightDiePhase1Fire[] = { 26, 27, 28 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianRightDie1Fire", magician, rightDiePhase1Fire, 3, 10, true);
    int leftDiePhase1Fire[] = { 36, 37, 38 };
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
    int rightDiePhase4[] = { 55, 56, 57 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianRightDie4", magician, rightDiePhase4, 3, 10, false);
    int leftDiePhase4[] = { 65, 66, 67 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianLeftDie4", magician, leftDiePhase4, 3, 10, false);
    //OTHER
    int rightOther[] = { 9 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianRightOther", magician, rightOther, 1, 1, false);
    int leftDieOther[] = { 19 };
    ANIMATIONKEY.addArrayFrameAnimation("MagicianLeftOther", magician, leftDieOther, 1, 1, false);


    _state = RIGHT_IDLE;
    _anim = ANIMATIONKEY.findAnimation("WarriorRightIdle");
    _anim->start();

    _hp = 10;

    return S_OK;
}

void Magician::Release()
{
    Character::Release();
}

void Magician::Update()
{
    Character::Update();
}

void Magician::Render()
{
    Character::Render();
}

void Magician::ChangeWeapon()
{
    if (Character::_weapon == Character::WEAPON_1)
        _img = IMAGEMANAGER.findImage("Magician1");
    else if (Character::_weapon == Character::WEAPON_2)
        _img = IMAGEMANAGER.findImage("Magician2");
    else if (Character::_weapon == Character::WEAPON_3)
        _img = IMAGEMANAGER.findImage("Magician3");
    else if (Character::_weapon == Character::WEAPON_4)
        _img = IMAGEMANAGER.findImage("Magician4");
}

void Magician::ChangeAnim(int state, string animKey)
{
    _state = (STATE)state;
    _anim = ANIMATIONKEY.findAnimation(animKey);
    _anim->start();
}

void Magician::Collision()
{
}
