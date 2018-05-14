#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}

void Bullet::Render()
{
	if (!isShot)return;

	if(isAnimation)
		img->aniRender(getMemDC(), rc.left, rc.top, &anim[frameYidx]);
	else
		img->frameRender(getMemDC(), rc.left, rc.top, 0, frameYidx);
}
