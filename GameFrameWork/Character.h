#pragma once
#include "gameNode.h"
class Character :
    public gameNode
{
protected:
    enum WEAPON
    {
        WEAPON_1,
        WEAPON_2,
        WEAPON_3,
        WEAPON_4
    };

    image * _img;
    animation * _anim;
    RECT _rc;
    float _x, _y;
    float _speedX;
    float _speedY;
    float _jumpPower;
    float _gravity;
    float _friction;

    WEAPON _weapon;

    RECT _colRC;
    float _colX, _colY;

    int _hp;
public:
    Character();
    ~Character();

    virtual HRESULT Init(float x, float y);
    virtual void Release();
    virtual void Update();
    virtual void Render();

public:
    inline RECT&getRc() { return _colRC; }
    inline float GetX() { return _x; }
    inline float GetY() { return _y; }

public:
    virtual void ChangeWeapon() = 0;
    virtual void ChangeAnim(int state, string animKey) = 0;
    virtual void Collision() = 0;
};

