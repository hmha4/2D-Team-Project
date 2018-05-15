#include "stdafx.h"
#include "Stage1_1.h"


Stage1_1::Stage1_1()
{
	IMAGEMANAGER.addImage("페이드아웃", PathFile("image", "검은화면").c_str(), 800, 600, false, NULL);
	IMAGEMANAGER.addImage("1.1앞배경", PathFile("image", "1-1앞배경").c_str(), 3652, 400, true, RGB(255, 0, 255));
	IMAGEMANAGER.addImage("1.1뒷배경", PathFile("image", "1-1뒷배경").c_str(), 3652, 400, true, RGB(255, 0, 255));
	IMAGEMANAGER.addImage("1.1배경오브젝트", PathFile("image", "1-1제트오더").c_str(), 2864, 80, true, RGB(255, 0, 255));
}


Stage1_1::~Stage1_1()
{
}

HRESULT Stage1_1::Init()
{	
	//맵오브젝트 제트오더 추가
	MapObject*mObj = new MapObject(IMAGEMANAGER.findImage("1.1배경오브젝트"));
	mObj->Init(0, 320);
	ZORDER.InputObj(mObj);

    _warrior = new Warrior;
    _warrior->Init(WINSIZEX/2, WINSIZEY/2);

    ZORDER.InputObj(_warrior);

	//정적 배경은 따로넣어서 렌더에서 처리하면됨
	fadeOut = IMAGEMANAGER.findImage("페이드아웃");
	offset = 255;
	s1State = OPENNING;

	return S_OK;
}


void Stage1_1::Render()
{
	IMAGEMANAGER.findImage("1.1뒷배경")->LoopRender(getMemDC(),RectMake(0,0,GAMESIZEX,GAMESIZEY), CAM.GetX()/30,0);
	IMAGEMANAGER.findImage("1.1앞배경")->Render(getMemDC(), 0,0);
	fadeOut->alphaRender(getMemDC(), offset);
}


void Stage1_1::Update()
{
	switch (s1State)
	{
		case OPENNING:
		{
            _warrior->Update();
            CAM.Update(_warrior->GetX(), _warrior->GetY(), 5, false);
			offset -= 2;
			if (offset < 0)
			{
				s1State = FIRST_STAGE;
				offset = 0;
                CAM.SetSize(GAMESIZEX/2, WINSIZEY);
                CAM.SetState("FOLLOW");
			}
		}
		break;
		case FIRST_STAGE:
		{
            _warrior->Update();
            CAM.Update(_warrior->GetX(), _warrior->GetY(), 5, true);
		}
		break;
		case SECOND_STAGE:
		{

		}
		break;
	}
}

void Stage1_1::Release()
{
    _warrior->Release();
}
