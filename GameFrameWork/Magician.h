#pragma once
#include "Character.h"
class Magician :
    public Character
{
private:
	//	������ ���� ����
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

    STATE _state;					//	������ ����
	float _startY;					//	������ ���� y��ǥ
	float _downCount = 0;			//	������ �ٿ� ī��Ʈ
public:
    Magician();
    ~Magician();

	//	Init(x��ǥ, y��ǥ, 1p����2p����);
    HRESULT Init(float x, float y, int player);
    void Release();
    void Update();
    void Render();

	//	ĳ���� ���� ����
    void ChangeWeapon();
	//	ĳ���� �ִϸ��̼� ����(����, �ִϸ��̼� �̸�)
    void ChangeAnim(int state, string animKey);
	//	ĳ���� �浹(RECT)
    void Collision(RECT rc);
	//	ĳ���� �̵� ����(�������� ��ȣ)
	void MovementRestrict(int stage);
	//	ĳ���� ����
	int GetState() { return _state; }

	//	ĳ���� �Ҹ� �ʱ�ȭ
	void InitBullet();
};

