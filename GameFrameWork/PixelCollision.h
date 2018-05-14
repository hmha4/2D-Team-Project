#pragma once
//#include "gameNode.h"
class PixelCollision
{
private:
	//�ȼ��ݸ����� ����� ��ü�� �� Ŭ������ �ҷ��ͼ� ����ؾ���
	int proveWidth; // ���� Ž������
	int proveHeight; // ���� Ž������

	int x, y;
	float collisionDownY; // �浹����Ʈ�Ʒ�
	float collisionUpY; //�浹����Ʈ ����
public:
	PixelCollision();
	~PixelCollision();

	//�浹ó���� �̹����� �ʺ�� ���̼���
	HRESULT init(int _proveWidth, int _proveHeight);
	void Release();

	//�ǽð����� �浹��ǥ �ٲ��ִ� �Լ�
	void UpdatePosition(int _x, int _y);
	void render(HDC hdc);


	//=================�ȼ��浹 �Լ�=====================//
	//Y���� Ž���ϰ� ���� ������� ���������ʰ� �����ִ� �Լ�
	bool RayCastingUpY(HDC hdc, int rValue, int bValue, int gValue);
	bool RayCastingDownY(HDC hdc, int rValue, int bValue, int gValue);

	//X���� Ž���ϴ� �Լ� 
	bool RayCastingX(HDC hdc, float risAngle, int rValue, int bValue, int gValue);

	//����Ž���ϴ� �Լ�
	bool RayCastRange(HDC hdc, int rValue, int gValue, int bValue);

	//getter,setter
	inline void setPosDownY(float&_y) { _y = collisionDownY - proveHeight; }
	inline void setPosUpY(float&_y) { _y = collisionUpY + proveHeight; }
	inline int getX() { return x; }
	inline int getY() { return y; }
};

