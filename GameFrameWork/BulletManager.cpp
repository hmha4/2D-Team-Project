#include "stdafx.h"
#include "BulletManager.h"
#include "Bullet.h"

BulletManager::BulletManager()
{
}


BulletManager::~BulletManager()
{
}

void BulletManager::Release()
{
	bulletMapIter bmIter = bMap.begin();

	for (; bmIter != bMap.end(); bmIter++)
	{
		for (int i = 0; i < bmIter->second.size(); i++)
		{
			bmIter->second[i]->Release();
			SAFE_DELETE(bmIter->second[i]);
		}
	}
	bMap.clear();
	bIdxMap.clear();
}

//이미지메니저로 미리만든 이미지삽입해야함
void BulletManager::BulletSetting(string bulletName, image * img, int bulletNum, bool isAnim, int animSpeed, int frameYnum, bool onceAnim)
{
	bulletVec bVec;
	if (isAnim)//에니메이션 총알이미지일때
	{
		for (int i = 0; i < bulletNum; i++)
		{
			Bullet*bullet = new Bullet;
			bullet->rc = { 0,0,0,0 };
			bullet->img = img;

			bullet->anim = new animation[frameYnum];
			int*animArr;

			for (int j = 0; j < frameYnum; j++)
			{
				bullet->anim[j].init(img->GetWidth(), (img->GetHeight() / frameYnum)+j*img->GetFreamHeight(), img->GetFrameWidth(), img->GetFreamHeight());
				bullet->anim[j].setFPS(animSpeed);

				animArr = new int[img->GetWidth() / img->GetFrameWidth()];
				for (int k = 0; k < img->GetWidth() / img->GetFrameWidth(); k++)
				{
					animArr[k] = k + j*img->GetWidth() / img->GetFrameWidth();
				}
				bullet->anim[j].setPlayFrame(animArr, img->GetWidth() / img->GetFrameWidth(), onceAnim);
				bullet->anim[j].stop();
			}

			bullet->bulletName = bulletName;
			bullet->speed = 0;
			bullet->gravity = 0;
			bullet->addGravity = 0;
			bullet->isShot = false;
			bullet->isAnimation = isAnim;
			bullet->useCollision = false;
			bullet->useShadow = false;

			bVec.push_back(bullet);
		}
	}
	else//단일 총알이미지일때
	{
		for (int i = 0; i < bulletNum; i++)
		{
			Bullet*bullet = new Bullet;
			bullet->rc = { 0,0,0,0 };
			bullet->img = img;
			bullet->img->SetFrameX(0);
			bullet->bulletName = bulletName;
			bullet->speed = 0;
			bullet->gravity = 0;
			bullet->addGravity = 0;
			bullet->isShot = false;
			bullet->isAnimation = isAnim;
			bullet->useCollision = false;
			bullet->useShadow = false;

			bVec.push_back(bullet);
		}
	}

	bulletMapIter bMapIter = bMap.find(bulletName);
	if (bMapIter != bMap.end())
		return;
	bMap.insert(pair<string, bulletVec>(bulletName, bVec));
	bIdxMap.insert(pair<string, int>(bulletName, 0));
}

void BulletManager::BulletShadowSetting(string bulletName,image*shadowImg, const RECT & shadowRc,float setY)
{
	bulletMapIter bMapIter = bMap.find(bulletName);
	bulletIter	  bIter;
	
	bIter = bMapIter->second.begin();

	for (; bIter != bMapIter->second.end(); bIter++)
	{
		(*bIter)->useShadow = true;
		(*bIter)->shadowRc = shadowRc;
		(*bIter)->ShadowSetY = setY;
		(*bIter)->shadowImg = shadowImg;
		(*bIter)->shadowWidth = shadowRc.right - shadowRc.left;
		(*bIter)->shadowHeight = shadowRc.bottom - shadowRc.top;
	}
	
}

void BulletManager::BulletUpdate()
{
	bulletMapIter bMapIter = bMap.begin();
	bulletIter	  bIter;

	for (; bMapIter != bMap.end(); bMapIter++)
	{
		bIter = bMapIter->second.begin();
		for (; bIter != bMapIter->second.end(); bIter++)
		{
			if (!(*bIter)->isShot)continue;

			(*bIter)->gravity += (*bIter)->addGravity;

			(*bIter)->x += cosf((*bIter)->angle)*(*bIter)->speed;
			(*bIter)->y += -sinf((*bIter)->angle)*(*bIter)->speed + (*bIter)->gravity;

			if ((*bIter)->isAnimation)
			{
				(*bIter)->rc = RectMakeCenter((*bIter)->x, (*bIter)->y, (*bIter)->img->GetFrameWidth(), (*bIter)->img->GetFreamHeight());
				(*bIter)->anim[(*bIter)->frameYidx].frameUpdate(TIMEMANAGER.getElapsedTime());
				if (!(*bIter)->anim[(*bIter)->frameYidx].isPlay())
				{
					(*bIter)->isShot = false;
					(*bIter)->rc = { 0,0,0,0 };
					(*bIter)->gravity = 0;
					(*bIter)->addGravity = 0;
				}
			}
			else
				(*bIter)->rc = RectMakeCenter((*bIter)->x, (*bIter)->y, (*bIter)->img->GetWidth(), (*bIter)->img->GetHeight());

			if ((*bIter)->useShadow)
			{
				if ((*bIter)->shadowImg != NULL)
				{
					if ((*bIter)->initY == 0)
						(*bIter)->shadowRc = RectMakeCenter((*bIter)->x, (*bIter)->y + (*bIter)->ShadowSetY, (*bIter)->shadowWidth, (*bIter)->shadowHeight);
					else
						(*bIter)->shadowRc = RectMakeCenter((*bIter)->x, (*bIter)->initY + (*bIter)->ShadowSetY, (*bIter)->shadowWidth, (*bIter)->shadowHeight);
				}
				else
				{
					if ((*bIter)->initY == 0)
						(*bIter)->shadowRc = RectMakeCenter((*bIter)->x, (*bIter)->y + (*bIter)->ShadowSetY, (*bIter)->shadowWidth, (*bIter)->shadowHeight);
					else
						(*bIter)->shadowRc = RectMakeCenter((*bIter)->x, (*bIter)->initY + (*bIter)->ShadowSetY, (*bIter)->shadowWidth, (*bIter)->shadowHeight);
				}
			}
				

			if ((*bIter)->useCollision)
				(*bIter)->pcol->UpdatePosition((*bIter)->x, (*bIter)->y);
		}
	}
}

void BulletManager::BulletRender()
{
	bulletMapIter bMapIter = bMap.begin();
	bulletIter	  bIter;

	for (; bMapIter != bMap.end(); bMapIter++)
	{
		bIter = bMapIter->second.begin();
		for (; bIter != bMapIter->second.end(); bIter++)
		{
			(*bIter)->Render();
		}
	}
}

void BulletManager::Shot(string bulletName, float x, float y, float angle, float gravity, int speed, int frameYidx,float shadowY)
{
	bulletMapIter bMapIter = bMap.find(bulletName);
	bulletIdxMapIter bIdxMapIter = bIdxMap.find(bulletName);

	if (bMapIter->second[bIdxMapIter->second]->isAnimation)
	{
		bMapIter->second[bIdxMapIter->second]->x = x;
		bMapIter->second[bIdxMapIter->second]->y = y;
		bMapIter->second[bIdxMapIter->second]->initX = x;
		bMapIter->second[bIdxMapIter->second]->initY = shadowY;

		bMapIter->second[bIdxMapIter->second]->rc = RectMakeCenter(x, y,
			bMapIter->second[bIdxMapIter->second]->img->GetFrameWidth(),
			bMapIter->second[bIdxMapIter->second]->img->GetFreamHeight());

		bMapIter->second[bIdxMapIter->second]->speed = speed;
		bMapIter->second[bIdxMapIter->second]->angle = angle;
		bMapIter->second[bIdxMapIter->second]->addGravity = gravity;
		bMapIter->second[bIdxMapIter->second]->gravity = 0;
		bMapIter->second[bIdxMapIter->second]->isShot = true;
		bMapIter->second[bIdxMapIter->second]->frameYidx = frameYidx;
		bMapIter->second[bIdxMapIter->second]->anim[frameYidx].start();
	}
	else
	{
		bMapIter->second[bIdxMapIter->second]->frameYidx=frameYidx;

		bMapIter->second[bIdxMapIter->second]->x = x;
		bMapIter->second[bIdxMapIter->second]->y = y;
		bMapIter->second[bIdxMapIter->second]->initX = x;
		bMapIter->second[bIdxMapIter->second]->initY = shadowY;


		bMapIter->second[bIdxMapIter->second]->rc = RectMakeCenter(x, y,
			bMapIter->second[bIdxMapIter->second]->img->GetWidth(),
			bMapIter->second[bIdxMapIter->second]->img->GetHeight());

		bMapIter->second[bIdxMapIter->second]->speed = speed;
		bMapIter->second[bIdxMapIter->second]->angle = angle;
		bMapIter->second[bIdxMapIter->second]->addGravity = gravity;
		bMapIter->second[bIdxMapIter->second]->gravity = 0;
		bMapIter->second[bIdxMapIter->second]->isShot = true;
	}

	bIdxMapIter->second++;
	if (bIdxMapIter->second > bMapIter->second.size() - 1)
		bIdxMapIter->second = 0;
}

void BulletManager::Destroy(string bulletName, int bulletIdx)
{
	bulletMapIter bMapIter = bMap.find(bulletName);

	bMapIter->second[bulletIdx]->isShot = false;
	bMapIter->second[bulletIdx]->rc = { 0,0,0,0 };
	bMapIter->second[bulletIdx]->gravity = 0;
	bMapIter->second[bulletIdx]->addGravity = 0;
}

void BulletManager::UseCollision(string bulletName, int proveX, int proveY)
{
	bulletMapIter bMapIter = bMap.find(bulletName);
	if (bMapIter != bMap.end())
		return;

	bulletIter bIter = bMapIter->second.begin();
	for (;bIter != bMapIter->second.end(); bIter++)
	{
		(*bIter)->useCollision = true;
		(*bIter)->pcol = new PixelCollision;
		(*bIter)->pcol->init(proveX, proveY);

	}
}

bool BulletManager::IsCollision(string bulletName, int*bulletPosX, int*bulletPosY, bool isMapCollision, HDC hdc, RECT rc)
{
	bulletMapIter bMapIter = bMap.find(bulletName);

	if (isMapCollision)
	{
		for (int i = 0; i < bMapIter->second.size(); i++)
		{
			if (!bMapIter->second[i]->isShot)continue;
			if (bMapIter->second[i]->pcol->RayCastRange(hdc, 255, 0, 0))
			{
				*bulletPosX = GetCenterPos(bMapIter->second[i]->rc).x;
				*bulletPosY = GetCenterPos(bMapIter->second[i]->rc).y;
				Destroy(bulletName, i);
				return true;
			}
		}
	}
	else
	{
		RECT temp;
		for (int i = 0; i < bMapIter->second.size(); i++)
		{
			if (!bMapIter->second[i]->isShot)continue;
			if (IntersectRect(&temp, &bMapIter->second[i]->rc, &rc))
			{
				*bulletPosX = GetCenterPos(bMapIter->second[i]->rc).x;
				*bulletPosY = GetCenterPos(bMapIter->second[i]->rc).y;
				Destroy(bulletName, i);
				return true;
			}
		}
	}
	return false;
}


