#pragma once
#include "Character.h"
class Warrior :
    public Character
{
private:
    enum STATE
    {
        RIGHT_IDLE, LEFT_IDLE,
        RIGHT_RUN, LEFT_RUN,
        RIGHT_UP_RUN, LEFT_UP_RUN,
        RIGHT_DOWN_RUN, LEFT_DOWN_RUN,
        RIGHT_JUMP, LEFT_JUMP,
        RIGHT_FALL, LEFT_FALL,
        RIGHT_ATTACK, LEFT_ATTACK,
        RIGHT_JUMP_ATTACK, LEFT_JUMP_ATTACK,
        RIGHT_BLOCK, LEFT_BLOCK,
        RIGHT_HIT_1, LEFT_HIT_1,
        RIGHT_HIT_2, LEFT_HIT_2,
        RIGHT_DIE_P1, LEFT_DIE_P1,
        RIGHT_DIE_PF, LEFT_DIE_PF,
        RIGHT_DIE_PI, LEFT_DIE_PI,
        RIGHT_DIE_P2, LEFT_DIE_P2,
        RIGHT_DIE_P3, LEFT_DIE_P3,
        RIGHT_DIE_P4, LEFT_DIE_P4,
        RIGHT_OTHER, LEFT_OTHER
    };

    STATE _state;
    float _startY;
    float _downCount = 0;
public:
    Warrior();
    ~Warrior();

    HRESULT Init(float x, float y);
    void Release();
    void Update();
    void Render();

    void ChangeWeapon();
    void ChangeAnim(int state, string animKey);
    void Collision();

	void InitBullet();
};

