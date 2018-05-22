#pragma once
#include "Character.h"
class Magician :
    public Character
{
private:
	//	마법사 상태 정보
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

    STATE _state;					//	마법사 상태
	float _startY;					//	마법사 점프 y좌표
	float _downCount = 0;			//	마법사 다운 카운트
public:
    Magician();
    ~Magician();

	//	Init(x좌표, y좌표, 1p인지2p인지);
    HRESULT Init(float x, float y, int player);
    void Release();
    void Update();
    void Render();

	//	캐릭터 무기 변경
    void ChangeWeapon();
	//	캐릭터 애니메이션 변경(상태, 애니메이션 이름)
    void ChangeAnim(int state, string animKey);
	//	캐릭터 충돌(RECT)
    void Collision(RECT rc);
	//	캐릭터 이동 제한(스테이지 번호)
	void MovementRestrict(int stage);
	//	캐릭터 상태
	int GetState() { return _state; }

	//	캐릭터 불릿 초기화
	void InitBullet();
};

