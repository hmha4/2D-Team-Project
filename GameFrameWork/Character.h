#pragma once
#include "gameNode.h"
#include <map>

class Character :
    public gameNode
{
protected:
	typedef map<string, int>	mControl;

	mControl _mControl;
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
	string _weaponEffectName;

    RECT _colRC;
    float _colX, _colY;

	RECT _shadow;

    int _hp;
public:
    Character();
    ~Character();

    virtual HRESULT Init(float x, float y, int player);
    virtual void Release();
    virtual void Update();
    virtual void Render();
//베이스 클래스 함수
public:
    

//접근자 설정자
public:
	inline RECT GetRC() { return _colRC; }
    inline RECT&getRc() { return _shadow; }
    inline float GetX() { return _x; }
    inline float GetY() { return _y; }
//가상함수
public:
	virtual void MovementRestrict(int stage) = 0;
    virtual void ChangeWeapon() = 0;
    virtual void ChangeAnim(int state, string animKey) = 0;
    virtual void Collision() = 0;
};

