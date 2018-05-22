#pragma once
#include "gameNode.h"
#include <map>

class Character :
    public gameNode
{
protected:
	//	1P, 2P ���� Ű�� ���� map
	//	�÷��̾� Ű �Է��� map�� �����ؼ� 
	//	�ڵ带 ���̱� ���ؼ�
	typedef map<string, int>	mControl;

	mControl _mControl;
protected:
	//	ĳ���� ���� ���� ������
    enum WEAPON
    {
        WEAPON_1,
        WEAPON_2,
        WEAPON_3,
        WEAPON_4
    };

    image * _img;				//	ĳ���� �̹���
    animation * _anim;			//	ĳ���� �ִϸ��̼�
    RECT _rc;					//	ĳ���� ��� RECT
    float _x, _y;				//	ĳ���� ��ǥ
    float _speedX;				//	ĳ���� �¿� �ӵ�
    float _speedY;				//	ĳ���� ���� �ӵ�
    float _jumpPower;			//	ĳ���� ���� ��(7.0f)
    float _gravity;				//	ĳ���� �߷�(0.3f)
    float _friction;			//	ĳ���� ����(5���� �����ؼ� 0���� 0.3��)

    WEAPON _weapon;				//	ĳ���� ���� ����
	string _weaponEffectName;	//	ĳ���� �Ҹ� �̸�

    RECT _colRC;				//	ĳ���� �浹 RECT
    float _colX, _colY;			//	ĳ���� �浹 ��ǥ

	RECT _shadow;				//	ĳ���� �׸��� RECT

    int _hp;					//	ĳ���� hp

	int _alpha;					//	ĳ���� ���İ�(�׾�����)
	float _alphaCount;			//	���İ� ���� ī��Ʈ(0.2f)
	float _deadTime;			//	ĳ���� ���� �ð�(2.0f)
public:
    Character();
    ~Character();

	//	Init(x��ǥ, y��ǥ, 1p����2p����);
    virtual HRESULT Init(float x, float y, int player);
    virtual void Release();
    virtual void Update();
    virtual void Render();
//	���̽� Ŭ���� �Լ�
public:
    

//	������ ������
public:
	//	ĳ���� �浹 RECT
	inline RECT GetColRC() { return _colRC; }
	//	ĳ���� �׸��� RECT
    inline RECT&getRc() { return _shadow; }
	//	ĳ���� x��ǥ
    inline float GetX() { return _x; }
	//	ĳ���� y��ǥ
    inline float GetY() { return _y; }
	//	ĳ���� hp
	inline int GetHP() { return _hp; }
	//	ĳ���� ���� ����
	inline int GetWeaponLv() { return _weapon + 1; }
	//	ĳ���� ���� ������(���� ����)
	void SetWeaponLv(int weaponLv) { _weapon = (WEAPON)(weaponLv - 1); }

//	�����Լ�
public:
	//	ĳ���� �̵� ����(�����Լ�)
	virtual void MovementRestrict(int stage) = 0;
	//	ĳ���� ���� ����(�����Լ�)
    virtual void ChangeWeapon() = 0;
	//	ĳ���� �ִϸ��̼� ����(�����Լ�)
    virtual void ChangeAnim(int state, string animKey) = 0;
	//	ĳ���� �浹(�����Լ�)
    virtual void Collision(RECT rc) = 0;
	//	ĳ���� ����(�����Լ�)
	virtual int GetState() = 0;
};

