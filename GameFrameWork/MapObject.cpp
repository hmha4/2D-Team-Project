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

HRESULT MapObject::Init(int x, int y, int amount, int _stageNum, bool fade)
{
	setX = x;
	setY = y;
    rc = RectMake(setX, setY, img->GetWidth(), img->GetHeight());
	shadowRc = RectMakeCenter(GetCenterPos(rc).x, GetCenterPos(rc).y + amount, img->GetWidth(), img->GetHeight());
	
	isFade = fade;
	alpha = 255;

	isStageStart = true;
	startFadeIn = false;
	stageNum = _stageNum;
	stageAlpha = 0;
	minusAlpha = 1;
	
	return S_OK;
}

void MapObject::Render()
{
	if (isFade)
	{
		img->alphaRender(getMemDC(), setX, setY, alpha);
		if (isStageStart)
		{
			if (alpha == 0) startFadeIn = true;
			if (!startFadeIn) return;
			IMAGEMANAGER.findImage("STAGE_NUM")->alphaFrameRender(getMemDC(), CAM.GetCenterX() - 123, CAM.GetY() + 80 - 32, 0, stageNum, stageAlpha);
			stageAlpha += 3 * minusAlpha;
				if (stageAlpha >= 255)
				{
					stageAlpha = 255;
					minusAlpha = -1;
				}
				if (stageAlpha < 0)
				{
					isStageStart = false;
				}
		}
	}
	else	img->Render(getMemDC(), setX, setY);

}

void MapObject::Update(int opaque)
{
	if (isFade)
	{
		setX = CAM.GetX();
		setY = CAM.GetY();

		alpha = opaque;
		//stageAlpha = alpha;
	}
}

void MapObject::Release()
{
}
