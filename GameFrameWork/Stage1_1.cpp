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

	_pm = new PlayerManager;
	_pm->Init();

	_em = new EnemyManager;
	_em->InputEnemy(WAREWOLF, 20);

	//���� ����� ���γ־ �������� ó���ϸ��
	fadeOut = IMAGEMANAGER.findImage("���̵�ƿ�");
	offset = 255;
	s1State = OPENNING;

	return S_OK;
}


void Stage1_1::Render()
{
	IMAGEMANAGER.findImage("1.1�޹��")->Render(getMemDC(), CAM.GetX(), CAM.GetY(), CAM.GetX() * 0.01, CAM.GetY(), WINSIZEX, GAMESIZEY);
	IMAGEMANAGER.findImage("1.1�չ��")->Render(getMemDC(), CAM.GetX(), CAM.GetY(), CAM.GetX(), CAM.GetY(), WINSIZEX, GAMESIZEY);
	fadeOut->alphaRender(getMemDC(), offset);

	_pm->Render();
}


void Stage1_1::Update()
{
	_pm->MoveRestrict((int)s1State);
	//_pm->GetMagician()->MovementRestrict((int)s1State);

	switch (s1State)
	{
	case OPENNING:
	{
		_pm->Update();
		CAM.Update(_pm->GetPlayer1()->GetX(), _pm->GetPlayer1()->GetY(), 5, false);

		offset -= 2;
		if (offset < 0)
		{
			for (int i = 0; i < 3; i++)
				_em->ShowEnemy(WAREWOLF, WINSIZEX / 2 + 250, 200 + i * 50, LEFT_IDLE);
			s1State = FIRST_STAGE;
			offset = 0;
			CAM.SetSize(GAMESIZEX / 2, WINSIZEY);
			CAM.SetState("FOLLOW");
		}
	}
	break;
	case FIRST_STAGE:
	{
		_em->Update(_pm);
		_pm->Update();
		CAM.Update(_pm->GetPlayer1()->GetX(), _pm->GetPlayer1()->GetY(), 5, false);

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
	_pm->Release();
	_em->Release();

	ZORDER.Release();
}
