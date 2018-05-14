#include "stdafx.h"
#include "interAction.h"


interAction::interAction()
{
}


interAction::~interAction()
{

}

HRESULT interAction::init()
{
	_worldTimeCount = 0;
	_isMoving = false;

	return S_OK;
}

void interAction::release()
{

}

void interAction::update()
{
	moving();
}

void interAction::render()
{

}


void interAction::moveTo(image* image, float endX, float endY, 
						float time)
{
	if (!_isMoving)
	{
		_image = image;

		_endX = endX;
		_endY = endY;

		_startX = image->GetX();
		_startY = image->GetY();

		_travelRange = getDistance(_startX, _startY, _endX, _endY);

		_angle = getAngle(_startX, _startY, _endX, _endY);

		_worldTimeCount = TIMEMANAGER.getWorldTime();

		_time = time;

		_isMoving = true;
	}
}


void interAction::moving(void)
{
	//움직이는 상태가 아니면 반환
	if (!_isMoving) return;

	float elapsedTime = TIMEMANAGER.getElapsedTime();

	float moveSpeed = (elapsedTime / _time) * _travelRange;

	_image->SetX(_image->GetX() + cosf(_angle) * moveSpeed);
	_image->SetY(_image->GetY() + -sinf(_angle) * moveSpeed);

	if (_time + _worldTimeCount <= TIMEMANAGER.getWorldTime())
	{
		_worldTimeCount = TIMEMANAGER.getWorldTime();

		_image->SetX(_endX);
		_image->SetY(_endY);

		_isMoving = false;
	}
}
