#include "stdafx.h"
#include "MapObject.h"


MapObject::MapObject(image*img)
	:setX(0),setY(0)
{
	this->img = img;
}


MapObject::~MapObject()
{
}

HRESULT MapObject::Init()
{
	return S_OK;
}

HRESULT MapObject::Init(int x, int y, int amount)
{
	setX = x;
	setY = y;
    rc = RectMake(setX, setY, img->GetWidth(), img->GetHeight());
	shadowRc = RectMakeCenter(GetCenterPos(rc).x, GetCenterPos(rc).y + amount, img->GetWidth(), img->GetHeight());
	return S_OK;
}

void MapObject::Render()
{
	img->Render(getMemDC(), setX, setY);
}

void MapObject::Update()
{
}

void MapObject::Release()
{
}
