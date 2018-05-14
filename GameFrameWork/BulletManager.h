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
	bulletMap bMap;			//	�Ѿ˸�
	bulletIdxMap bIdxMap;	//	�Ѿ��ε�����
public:
	BulletManager();
	~BulletManager();

	//�Ѿ� �����Լ�
	void BulletSetting(string bulletName, image*img, int bulletNum, bool isAnim = false, int animSpeed = 60, int frameYnum = 1);

	//�Ѿ� ������Ʈ �Լ�
	void BulletUpdate();

	//�Ѿ� �����Լ�
	void BulletRender();

	//�Ѿ� �߻��Լ�
	void Shot(string bulletName, float x, float y, float angle, float gravity, int speed,int frameYidx=0);

	//�Ѿ� �ı��Լ�
	void Destroy(string bulletName, int bulletIdx);

	//�Ѿ��� �ٴڰ� �浹�ߴ��� ����
	void UseCollision(string bulletName, int proveX, int proveY);
	bool IsCollision(string bulletName, int*bulletPosX, int*bulletPosY, bool isMapCollision, HDC hdc, RECT rc);

	//�Ѿ� ������
	inline bulletVec&GetBulletVec(string bulletName) {
		return bMap.find(bulletName)->second;
	}
};

