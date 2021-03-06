#pragma once
#include "gameNode.h"
class Bullet:public gameNode
{
public:
	RECT		shadowRc;		//총알 그림자 충돌박스
	image*		shadowImg;		//총알 그림자 이미지

	RECT		rc;				//총알 충돌박스
	image*		img;			//총알 이미지
	animation*	anim;			//총알 에니메이션
	string		bulletName;		//총알 이름
	PixelCollision*	pcol;

	int			speed;			//총알 스피드
	int			frameYidx;		//총알 y이미지 인덱스

	float		x, y;			//총알 포지션
	float		initX, initY;	//총알 시작포지션
	float		gravity;		//총알 중력
	float		addGravity;		//더해지는 총알 중력
	float		angle;			//총알 각도
	float		ShadowSetY;		//총알그림자 Y위치 차이

	bool		isShot;			//총알 발사여부
	bool		isAnimation;	//에니메이션이 있는 총알인지 여부
	bool		useCollision;	//충돌사용하는지 여부
	bool		useShadow;		//그림자 사용하는지 여부

	float shadowWidth;
	float shadowHeight;

	Bullet();
	~Bullet();

	void Render();
	
	virtual inline RECT&getRc() { return shadowRc; }
	
	void Release();
};