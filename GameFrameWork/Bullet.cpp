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

	if (isAnimation)
	{
		img->aniRender(getMemDC(), rc.left, rc.top, &anim[frameYidx]);
		
		if (useShadow)
		{
			if(shadowImg!=NULL)
				shadowImg->Render(getMemDC(), shadowRc.left, shadowRc.top);
		}
	}
	else
	{
		img->frameRender(getMemDC(), rc.left, rc.top, 0, frameYidx);

		if (useShadow)
		{
			if (shadowImg != NULL)
				shadowImg->Render(getMemDC(), shadowRc.left, shadowRc.top);
		}
	}
}
