#include "stdafx.h"
#include "playGround.h"
//test

PlayGround::PlayGround()
{
}


PlayGround::~PlayGround()
{

}

//�ʱ�ȭ ���ִ� ����
HRESULT PlayGround::Init()
{
	gameNode::init(true);

	SOUNDMANAGER.addSound("00StartScene01", "sound\\StartScene_01.mp3", false, false);
	SOUNDMANAGER.addSound("01StartScene02", "sound\\StartScene_02.mp3", false, false);
	SOUNDMANAGER.addSound("02StartScene03", "sound\\StartScene_03.mp3", false, false);
	SOUNDMANAGER.addSound("03StartScene_Button", "sound\\StartScene_Button.mp3", false, false);
	SOUNDMANAGER.addSound("04ButtonSelect", "sound\\ButtonSelect.mp3", false, false);
	SOUNDMANAGER.addSound("05StartScene04", "sound\\StartScene_04.mp3", true, true);
	SOUNDMANAGER.addSound("06PlayerSelect", "sound\\PlayerSelect.mp3", true, true);
	SOUNDMANAGER.addSound("07Stage1_1", "sound\\Stage1_1.mp3", true, true);
	SOUNDMANAGER.addSound("08Stage1_2", "sound\\Stage1_2.mp3", true, true);
	SOUNDMANAGER.addSound("09Stage1_Boss", "sound\\Stage1_Boss.mp3", true, true);
	SOUNDMANAGER.addSound("10Victory", "sound\\Victory.mp3", false, false);

	IMAGEMANAGER.addImage("���̵�ƿ�", PathFile("image", "����ȭ��").c_str(), 800, 600, false, NULL);

	SCENEMANAGER.addScene("��������1.1", new Stage1_1);
	SCENEMANAGER.addScene("��������1.2", new Stage1_2);
	SCENEMANAGER.addScene("��������1.3", new Stage1_3);
	SCENEMANAGER.addScene("��������2.1", new Stage2_1);
	SCENEMANAGER.addScene("��������2.2", new Stage2_2);
	SCENEMANAGER.addScene("��������2.3", new Stage2_3);
	SCENEMANAGER.addScene("��������2.4", new Stage2_4);
	SCENEMANAGER.addScene("��������2.5", new Stage2_5);
	SCENEMANAGER.addScene("SelectScene", new SelectScene);
	SCENEMANAGER.addScene("StartScene", new StartScene);

	SCENEMANAGER.changeScene("StartScene");



	return S_OK;
}

//�޸� ���� (�����Ҵ� ������)
void PlayGround::Release()
{
	gameNode::Release();

}


//����
void PlayGround::Update()
{
	gameNode::Update();


	SCENEMANAGER.update();
	ZORDER.Update();
	BULLET.BulletUpdate();
	EFFECTMANAGER.update();
	ANIMATIONKEY.update();
	//CAM.Update(WINSIZEX / 2, WINSIZEY / 2, 5, true);
}

//�׷��ִ�
void PlayGround::Render()
{
	PatBlt(getMemDC(), 0, 0, GAMESIZEX, GAMESIZEY, BLACKNESS);


	SCENEMANAGER.render();//=>�̰� ������ ��Ʈ���� �Ⱦ��� �ֵ鷻��
	ZORDER.Render();//=>��Ʈ���������� ���⼭���ϱ� ������ ���� ������ʿ���� ��Ʈ������ ��ü�߰��� �ϸ��
	EFFECTMANAGER.render();

	CAM.Render(getHDC());
}
