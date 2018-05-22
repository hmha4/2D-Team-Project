#include "stdafx.h"
#include "ItemBox.h"


ItemBox::ItemBox()
:_distance(0), _change(false), _state(0)
,_angle(0), _checkAngle(0), _position(0)
{
	for (int ii = 0; ii < 4; ++ii)
	{
		_itemBox[ii] = BOX(ii);
	}
}


ItemBox::~ItemBox()
{
}

HRESULT ItemBox::Init()
{
	return S_OK;
}

void ItemBox::Release()
{
}

void ItemBox::Update(float x, float y)
{
	for (int ii = 0; ii < 4; ++ii)
	{
		_itemBox[ii].rc = RectMakeCenter(x + cosf(_itemBox[ii].angle) * _distance, y - sinf(_itemBox[ii].angle) * _distance, BOX_SIZE_NORMAL, BOX_SIZE_NORMAL);
		ChangePos(ii);
	}

	ChangeState();

	if (KEYMANAGER.isOnceKeyDown('Q')) _state = 1;
	if (KEYMANAGER.isOnceKeyDown('W')) _change = true;
}

void ItemBox::Render()
{
	if (_state == 1) return;
	for (int ii = 0; ii < 4; ++ii)
	{
		Rectangle(getMemDC(), _itemBox[ii].rc.left, _itemBox[ii].rc.top, _itemBox[ii].rc.right, _itemBox[ii].rc.bottom);
	}
}

void ItemBox::ChangePos(int num)
{
	if (_change)
	{
		_angle += ANGLE_SPEED;
		_checkAngle += ANGLE_SPEED;

		if (_checkAngle >= PI / 2)
		{
			_change = false;
			_checkAngle = 0;
			_position++;
			_angle = (PI / 2) * (_position % 4);
		}
	}

	if (num == 0)	_itemBox[num].angle = _angle;
	else _itemBox[num].angle = _itemBox[num - 1].angle - PI / 2;
}

void ItemBox::ChangeState()
{
	//상태에 따른 거리 결정
	if (_state == 0) _distance = 0;

	else if (_state == 1)
	{
		_distance += DISTANCE_SPEED;
		if (_distance >= 45)
		{
			_distance = 45;
			_state = 2;
		}
	}
}

