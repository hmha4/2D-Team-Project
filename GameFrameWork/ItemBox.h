#pragma once
#include "gameNode.h"
#define BOX_SIZE_NORMAL	40
#define BOX_SIZE_SELECT 30
#define ANGLE_SPEED 0.03
#define DISTANCE_SPEED 6.5
#define DISTANCE_MAX 55

typedef struct tagItemBox
{
	tagItemBox()
	{
	}

	tagItemBox(int _type)
	{
		type = (ITEM_TYPE)_type;
		angle = (PI / 2) * (float)_type;
		gauge = 0;
		select = false;
		fullCharge = false;
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
	float		gauge;
	float		angle;
	BOOL		select;
	BOOL		fullCharge;
	image*		img;

}BOX;

class ItemBox :
	public gameNode
{
private:
	BOX			_itemBox[4];


	//������ â ����
	// 0 : ��Ȱ�� (������ ����)
	// 1 : Ȱ�� ����
	// 2 : Ȱ�� �Ϸ�
	int			_state;

	//����(�÷��̾�� �޾ƿ� ��)
	float		_x;
	float		_y;

	//�Ÿ�
	float		_distance;

	//�ڽ� ��ġ ����
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
	void DrawSelectItem(HDC hdc, int x, int y);

	void SetState(BOOL state) { _state = state; }
};

