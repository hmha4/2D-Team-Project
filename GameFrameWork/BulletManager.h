#pragma once
#include "SingleTonBase.h"
#include "PixelCollision.h"
#include <vector>
#include <map>

class Bullet;

class BulletManager :public SingleTonBase<BulletManager>
{
private:
	typedef vector<Bullet*>				bulletVec;
	typedef vector<Bullet*>::iterator	bulletIter;

	typedef map<string, bulletVec>					bulletMap;
	typedef map<string, bulletVec>::iterator		bulletMapIter;

	typedef map<string, int>				bulletIdxMap;
	typedef map<string, int>::iterator		bulletIdxMapIter;
private:
	bulletMap bMap;			//	ÃÑ¾Ë¸Ê
	bulletIdxMap bIdxMap;	//	ÃÑ¾ËÀÎµ¦½º¸Ê
public:
	BulletManager();
	~BulletManager();

	//ÃÑ¾Ë »ðÀÔÇÔ¼ö
	void BulletSetting(string bulletName, image*img, int bulletNum, bool isAnim = false, int animSpeed = 60, int frameYnum = 1);

	//ÃÑ¾Ë ¾÷µ¥ÀÌÆ® ÇÔ¼ö
	void BulletUpdate();

	//ÃÑ¾Ë ·£´õÇÔ¼ö
	void BulletRender();

	//ÃÑ¾Ë ¹ß»çÇÔ¼ö
	void Shot(string bulletName, float x, float y, float angle, float gravity, int speed,int frameYidx=0);

	//ÃÑ¾Ë ÆÄ±«ÇÔ¼ö
	void Destroy(string bulletName, int bulletIdx);

	//ÃÑ¾ËÀÌ ¹Ù´Ú°ú Ãæµ¹Çß´ÂÁö ¿©ºÎ
	void UseCollision(string bulletName, int proveX, int proveY);
	bool IsCollision(string bulletName, int*bulletPosX, int*bulletPosY, bool isMapCollision, HDC hdc, RECT rc);

	//ÃÑ¾Ë Á¢±ÙÀÚ
	inline bulletVec&GetBulletVec(string bulletName) {
		return bMap.find(bulletName)->second;
	}
};

