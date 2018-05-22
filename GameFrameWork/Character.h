#pragma once
#include "gameNode.h"
#include <map>

class Character :
    public gameNode
{
protected:
	//	1P, 2P 조종 키에 관한 map
	//	플레이어 키 입력을 map에 저장해서 
	//	코드를 줄이기 위해서
	typedef map<string, int>	mControl;

	mControl _mControl;
protected:
	//	캐릭터 무기 레벨 열거형
    enum WEAPON
    {
        WEAPON_1,
        WEAPON_2,
        WEAPON_3,
        WEAPON_4
    };

    image * _img;				//	캐릭터 이미지
    animation * _anim;			//	캐릭터 애니메이션
    RECT _rc;					//	캐릭터 출력 RECT
    float _x, _y;				//	캐릭터 좌표
    float _speedX;				//	캐릭터 좌우 속도
    float _speedY;				//	캐릭터 상하 속도
    float _jumpPower;			//	캐릭터 점프 힘(7.0f)
    float _gravity;				//	캐릭터 중력(0.3f)
    float _friction;			//	캐릭터 마찰(5에서 시작해서 0까지 0.3씩)

    WEAPON _weapon;				//	캐릭터 무기 레벨
	string _weaponEffectName;	//	캐릭터 불릿 이름

    RECT _colRC;				//	캐릭터 충돌 RECT
    float _colX, _colY;			//	캐릭터 충돌 좌표

	RECT _shadow;				//	캐릭터 그림자 RECT

    int _hp;					//	캐릭터 hp

	int _alpha;					//	캐릭터 알파값(죽었을때)
	float _alphaCount;			//	알파값 조절 카운트(0.2f)
	float _deadTime;			//	캐릭터 알파 시간(2.0f)
public:
    Character();
    ~Character();

	//	Init(x좌표, y좌표, 1p인지2p인지);
    virtual HRESULT Init(float x, float y, int player);
    virtual void Release();
    virtual void Update();
    virtual void Render();
//	베이스 클래스 함수
public:
    

//	접근자 설정자
public:
	//	캐릭터 충돌 RECT
	inline RECT GetColRC() { return _colRC; }
	//	캐릭터 그림자 RECT
    inline RECT&getRc() { return _shadow; }
	//	캐릭터 x좌표
    inline float GetX() { return _x; }
	//	캐릭터 y좌표
    inline float GetY() { return _y; }
	//	캐릭터 hp
	inline int GetHP() { return _hp; }
	//	캐릭터 무리 레벨
	inline int GetWeaponLv() { return _weapon + 1; }
	//	캐릭터 무기 설정자(무기 레벨)
	void SetWeaponLv(int weaponLv) { _weapon = (WEAPON)(weaponLv - 1); }

//	가상함수
public:
	//	캐릭터 이동 제한(가상함수)
	virtual void MovementRestrict(int stage) = 0;
	//	캐릭터 무기 변경(가상함수)
    virtual void ChangeWeapon() = 0;
	//	캐릭터 애니메이션 변경(가상함수)
    virtual void ChangeAnim(int state, string animKey) = 0;
	//	캐릭터 충돌(가상함수)
    virtual void Collision(RECT rc) = 0;
	//	캐릭터 상태(가상함수)
	virtual int GetState() = 0;
};

