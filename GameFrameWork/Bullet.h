#pragma once
#include "gameNode.h"
class Bullet:public gameNode
{
public:
	RECT		rc;				//�Ѿ� �浹�ڽ�
	image*		img;			//�Ѿ� �̹���
	animation*	anim;			//�Ѿ� ���ϸ��̼�
	string		bulletName;		//�Ѿ� �̸�
	PixelCollision*	pcol;

	int			speed;			//�Ѿ� ���ǵ�
	int			frameYidx;		//�Ѿ� y�̹��� �ε���

	float		x, y;			//�Ѿ� ������
	float		initX, initY;	//�Ѿ� ����������
	float		gravity;		//�Ѿ� �߷�
	float		addGravity;		//�������� �Ѿ� �߷�
	float		angle;			//�Ѿ� ����

	bool		isShot;			//�Ѿ� �߻翩��
	bool		isAnimation;	//���ϸ��̼��� �ִ� �Ѿ����� ����
	bool		useCollision;	//�浹����ϴ��� ����

	Bullet();
	~Bullet();

	void Render();
	
	virtual inline RECT&getRc() { return rc; }
};