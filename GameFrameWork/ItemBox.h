#pragma once
#include "gameNode.h"
#define BOX_SIZE_NORMAL	30
#define BOX_SIZE_SELECT 30
#define ANGLE_SPEED 0.03
#define DISTANCE_SPEED 1.5

typedef struct tagItemBox
{
	tagItemBox()
	{
	}

	tagItemBox(int x, int y, float angle, float distance)
	{
		rc = RectMakeCenter(x + cosf(angle) * distance, y - sinf(angle) * distance, BOX_SIZE_NORMAL, BOX_SIZE_NORMAL);
	}

	tagItemBox(int _type)
	{
		type = (ITEM_TYPE)_type;
		angle = (PI / 2) * (float)_type;
		stock = 0;
		select = false;
	}

	enum ITEM_TYPE
	{
		ITEM_ICE,
		ITEM_FIRE,
		ITEM_THUNDER,
		ITEM_PORTION
	};
	
	RECT		rc;
	ITEM_TYPE	type;
	int			stock;
	float		angle;
	BOOL		select;
	image*		img;

}BOX;

class ItemBox :
	public gameNode
{
private:
	BOX			_itemBox[4];


	//아이템 창 상태
	// 0 : 비활성 (숨겨져 있음)
	// 1 : 활성 시작
	// 2 : 활성 완료
	int			_state;

	//중점(플레이어에서 받아올 것)
	float		_x;
	float		_y;

	//거리
	float		_distance;

	//박스 위치 변경
	BOOL		_change;
	float		_angle;
	UINT		_position;
	float		_checkAngle;


public:
	ItemBox();
	~ItemBox();

	HRESULT Init();
	void Release();
	void Update(float x, float y);
	void Render();

	void ChangePos(int num);
	void ChangeState();

	void SetState(BOOL state) { _state = state; }
};

