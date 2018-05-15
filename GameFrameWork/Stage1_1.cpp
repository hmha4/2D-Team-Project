#include "stdafx.h"
#include "Stage1_1.h"


Stage1_1::Stage1_1()
{
	IMAGEMANAGER.addImage("���̵�ƿ�", PathFile("image", "����ȭ��").c_str(), 800, 600, false, NULL);
	IMAGEMANAGER.addImage("1.1�չ��", PathFile("image", "1-1�չ��").c_str(), 3652, 400, true, RGB(255, 0, 255));
	IMAGEMANAGER.addImage("1.1�޹��", PathFile("image", "1-1�޹��").c_str(), 3652, 400, true, RGB(255, 0, 255));
	IMAGEMANAGER.addImage("1.1��������Ʈ", PathFile("image", "1-1��Ʈ����").c_str(), 2864, 80, true, RGB(255, 0, 255));
}


Stage1_1::~Stage1_1()
{
}

HRESULT Stage1_1::Init()
{	
	//�ʿ�����Ʈ ��Ʈ���� �߰�
	MapObject*mObj = new MapObject(IMAGEMANAGER.findImage("1.1��������Ʈ"));
	mObj->Init(0, 320);
	ZORDER.InputObj(mObj);


	//���� ����� ���γ־ �������� ó���ϸ��
	fadeOut = IMAGEMANAGER.findImage("���̵�ƿ�");
	offset = 255;
	s1State = OPENNING;

	return S_OK;
}


void Stage1_1::Render()
{
	IMAGEMANAGER.findImage("1.1�޹��")->LoopRender(getMemDC(),RectMake(0,0,GAMESIZEX,GAMESIZEY), CAM.GetX()/30,0);
	IMAGEMANAGER.findImage("1.1�չ��")->Render(getMemDC(), 0,0);
	fadeOut->alphaRender(getMemDC(), offset);
}


void Stage1_1::Update()
{
	switch (s1State)
	{
		case OPENNING:
		{
			offset -= 2;
			if (offset < 0)
			{
				s1State = FIRST_STAGE;
				offset = 0;
			}
		}
		break;
		case FIRST_STAGE:
		{

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
}
