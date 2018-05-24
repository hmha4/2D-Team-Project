#include "stdafx.h"
#include "ItemBox.h"


ItemBox::ItemBox()
:_distance(0), _change(false), _state(0)
,_angle(0), _checkAngle(0), _position(0)
{
	for (int ii = 0; ii < 4; ++ii)
	{
		_itemBox[ii] = BOX(ii);
		if (ii == 0) _itemBox[ii].img = IMAGEMANAGER.findImage("ITEM_ICE");
		else if (ii == 1) _itemBox[ii].img = IMAGEMANAGER.findImage("ITEM_FIRE");
		else if (ii == 2) _itemBox[ii].img = IMAGEMANAGER.findImage("ITEM_THUNDER");
		else if (ii == 3) _itemBox[ii].img = IMAGEMANAGER.findImage("ITEM_HEALTH");
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
	for (int ii = 0; ii < 3; ++ii)
	{
		_itemBox[ii].rc = RectMakeCenter(x + cosf(_itemBox[ii].angle) * _distance, y - sinf(_itemBox[ii].angle) * _distance, BOX_SIZE_NORMAL, BOX_SIZE_NORMAL);
		ChangePos(ii);
		_itemBox[ii].gauge += TIMEMANAGER.getElapsedTime();
	}

	ChangeState();

	if (KEYMANAGER.isOnceKeyDown('Q')) _state = 1;
	if (KEYMANAGER.isOnceKeyDown('W')) _change = true;
}

void ItemBox::Render()
{
	if (_state == 0) return;
	for (int ii = 0; ii < 3; ++ii)
	{
		if (_itemBox[ii].select == true) _itemBox[ii].img->Render(getMemDC(), _itemBox[ii].rc.left, _itemBox[ii].rc.top);
		else _itemBox[ii].img->alphaRender(getMemDC(), _itemBox[ii].rc.left, _itemBox[ii].rc.top, 100);
	}
	
}

void ItemBox::ChangePos(int num)
{
	if (_change)
	{
		_angle += ANGLE_SPEED;
		_checkAngle += ANGLE_SPEED;

		if (_checkAngle >= (PI / 3) * 2)
		{
			_change = false;
			_checkAngle = 0;
			_position++;
			_angle = ((PI / 3) * 2) * (_position % 3);
		}
	}

	if (num == 0)	_itemBox[num].angle = _angle - PI / 6;
	else _itemBox[num].angle = _itemBox[num - 1].angle - (PI / 3) * 2;

	if (num == (_position + 2) % 3)	_itemBox[num].select = true;
	else _itemBox[num].select = false;

}

void ItemBox::ChangeState()
{
	//상태에 따른 거리 결정
	if (_state == 0) _distance = 0;

	else if (_state == 1)
	{
		_distance += DISTANCE_SPEED;
		if (_distance >= DISTANCE_MAX)
		{
			_distance = DISTANCE_MAX;
			_state = 2;
		}
	}
}

void ItemBox::DrawSelectItem(HDC hdc, int x, int y)
{
	for (int ii = 0; ii < 4; ++ii)
	{
		if (_itemBox[ii].select != true) continue;
		_itemBox[ii].img->Render(hdc, x - _itemBox[ii].img->GetWidth() / 2, y - _itemBox[ii].img->GetHeight() / 2);
	}
}

