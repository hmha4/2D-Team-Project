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
	EFFECTMANAGER.addEffect("���ʹ��ǰ�", PathFile("image\\Enemy", "���ʹ��ǰ�").c_str(), 484, 55, 60, 55, 30, 1, 30);
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
	SOUNDMANAGER.addSound("11Thunder", "sound\\SKILL_THUNDER.mp3", false, false);
	SOUNDMANAGER.addSound("12Fire", "sound\\SKILL_FIRE.mp3", false, false);
	SOUNDMANAGER.addSound("13Ice", "sound\\SKILL_ICE.mp3", false, false);
	SOUNDMANAGER.addSound("14Stage2_1", "sound\\Stage2_1.mp3", true, true);
	SOUNDMANAGER.addSound("15Stage2_2", "sound\\Stage2_2.mp3", true, true);
	SOUNDMANAGER.addSound("16Stage2_3", "sound\\Stage2_3.mp3", true, true);
	SOUNDMANAGER.addSound("17Stage2_4", "sound\\Stage2_4.mp3", true, true);
	SOUNDMANAGER.addSound("18Stage2_5", "sound\\Stage2_5.mp3", true, true);
	SOUNDMANAGER.addSound("19PlayerRoar", "sound\\PlayerRoar.mp3", false, false);
	SOUNDMANAGER.addSound("20PlayerHurt1", "sound\\PlayerHurt1.mp3", false, false);
	SOUNDMANAGER.addSound("21PlayerHurt2", "sound\\PlayerHurt2.mp3", false, false);
	SOUNDMANAGER.addSound("22PlayerDie", "sound\\PlayerDie.mp3", false, false);
	SOUNDMANAGER.addSound("23PlayerSwing", "sound\\PlayerSwing.mp3", false, false);
	SOUNDMANAGER.addSound("24PlayerLand", "sound\\PlayerLand.mp3", false, false);
	SOUNDMANAGER.addSound("25EndingScene", "sound\\EndingScene.mp3", false, false);
	SOUNDMANAGER.addSound("26Skeleton", "sound\\Skeleton.mp3", false, false);
	SOUNDMANAGER.addSound("27WareWolf", "sound\\WareWolf.mp3", false, false);
	SOUNDMANAGER.addSound("28Hit", "sound\\Hit.mp3", false, false);
	SOUNDMANAGER.addSound("29Mino", "sound\\Mino.mp3", false, false);
	SOUNDMANAGER.addSound("30SkeletonDie", "sound\\SkeletonDie.mp3", false, false);
	SOUNDMANAGER.addSound("31WareWolfDie", "sound\\WareWolfDie.mp3", false, false);
	SOUNDMANAGER.addSound("32MinoDie", "sound\\MinoDie.mp3", false, false);
	SOUNDMANAGER.addSound("33MinoAxe", "sound\\MinoAxeAttack.mp3", false, false);
	SOUNDMANAGER.addSound("34MinoDeezy", "sound\\MinoDeezy.mp3", false, false);
	SOUNDMANAGER.addSound("35MinoHead", "sound\\MinoHead.mp3", false, false);
	SOUNDMANAGER.addSound("36SkeletonAttack", "sound\\SkeletonAttack.mp3", false, false);
	SOUNDMANAGER.addSound("37ArrowShoot", "sound\\ArrowShoot.mp3", false, false);
	SOUNDMANAGER.addSound("38DragonKnightChain", "sound\\DragonKnightChain.mp3", false, false);
	SOUNDMANAGER.addSound("39DragonKnightKnife", "sound\\DragonKnightKnife.mp3", false, false);
	SOUNDMANAGER.addSound("40DragonKnight", "sound\\DragonKnight.mp3", false, false);
	SOUNDMANAGER.addSound("41DragonKnightDie", "sound\\DragonKnightDie.mp3", false, false);
	SOUNDMANAGER.addSound("42DragonKnightFly", "sound\\DragonKnightFly.mp3", false, false);
	SOUNDMANAGER.addSound("43DragonKnightWoman", "sound\\DragonKnightWoman.mp3", false, false);
	SOUNDMANAGER.addSound("44DragonKnightChange", "sound\\DragonKnightChange.mp3", false, false);

	IMAGEMANAGER.addImage("���̵�ƿ�", PathFile("image", "����ȭ��").c_str(), 800, 600, false, NULL);
	IMAGEMANAGER.addFrameImage("STAGE_NUM", PathFile("image", "STAGE_NUM").c_str(), 247, 512, 1, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER.addFrameImage("UI_DIRECTION", PathFile("image\\UI", "UI_DIRECTION").c_str(), 66, 132, 1, 2, true, RGB(255, 0, 255));

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
	SCENEMANAGER.addScene("EndingScene", new EndingScene);

	SCENEMANAGER.changeScene("StartScene");

	DATABASE.SaveData("1PWeapon", 1);
	DATABASE.SaveData("2PWeapon", 1);

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
