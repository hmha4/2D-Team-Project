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

	void SetState(BOOL state) { _state = state; }
};

