#pragma once
#include "gameNode.h"
class Bullet:public gameNode
{
public:
	RECT		shadowRc;		//�Ѿ� �׸��� �浹�ڽ�
	image*		shadowImg;		//�Ѿ� �׸��� �̹���

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
	float		ShadowSetY;		//�Ѿ˱׸��� Y��ġ ����

	bool		isShot;			//�Ѿ� �߻翩��
	bool		isAnimation;	//���ϸ��̼��� �ִ� �Ѿ����� ����
	bool		useCollision;	//�浹����ϴ��� ����
	bool		useShadow;		//�׸��� ����ϴ��� ����

	float shadowWidth;
	float shadowHeight;

	Bullet();
	~Bullet();

	void Render();
	
	virtual inline RECT&getRc() { return shadowRc; }
	
	void Release();
};