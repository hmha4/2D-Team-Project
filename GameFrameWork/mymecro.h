#pragma once
#include <math.h>

#define PI 3.14

//==============================================
// ## 18.02.07 ## - Macro Function - ##
//==============================================

//Line
inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

//Rect
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };

	return rc;
}

inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2) };

	return rc;
}

inline POINT GetCenterPos(const RECT&rect)
{
	POINT pos;
	pos.x = rect.left + (rect.right - rect.left) / 2;
	pos.y = rect.top + (rect.bottom - rect.top) / 2;
	return pos;
}

//Rectangle
//left, top �������� �簢���� �����Ǵ� �Լ� dc����, ������ǥ X, Y, ����ũ��, ����ũ��
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

//���� �������� �簢���� �����Ǵ� �Լ� dc����, ������ǥ X, Y, ����ũ��, ����ũ��
inline void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}

//Ellipse
//Left, top�������� ���� �����Ǵ� �Լ� (DC����, left, Top, ����ũ��, ����ũ��)
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

//���� �������� ���� �����Ǵ� �Լ� dc����, ������ǥ X, Y, ����ũ��, ����ũ��
inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}

//�Ÿ� ���ϴ� �Լ�
inline float getDistance(float x1, float y1, float x2, float y2)
{
	float x = x2 - x1;
	float y = y2 - y1;

	return sqrtf(x * x + y * y);
}

//���� ���ϴ� �Լ�
inline float getAngle(float startX, float startY, float endX, float endY)
{
	float x = endX - startX;
	float y = endY - startY;

	float distance = sqrtf(x * x + y * y);

	float angle = acosf(x / distance);

	if (endY - startY>0) // y�� ������ ����̹Ƿ� 180���� �Ѿ�� ������ 
	{                              // angle�� ��Ÿ���� �ִ� ��(0~180)�� ����Ƿ� 
								   // 360���� ���ش�
		angle = 2 * PI - angle;
		if (angle >= 2 * PI) angle -= 2 * PI;
	}

	return angle;
}

//���浹 �Լ�
inline bool CircleCollision(RECT&r1, RECT&r2)
{
	POINT cPos1 = GetCenterPos(r1); //r1�� ����
	POINT cPos2 = GetCenterPos(r2); //r2�� ����

	float r1Radius = (r1.right - r1.left) / 2; // r1�� ������
	float r2Radius = (r2.right - r2.left) / 2; // r2�� ������

	float distance = sqrtf(pow(cPos1.x - cPos2.x, 2) + pow(cPos1.y - cPos2.y, 2));

	//�ο��� �������� ���� ���� �߽ɰ��� �Ÿ����� Ŭ��
	if (r1Radius + r2Radius >= distance)
		return true;
	else
		return false;
}

//���� �簢���浹�Լ�
inline bool ColCircleToRect(RECT rect, RECT circle)
{
	POINT cPos = { GetCenterPos(circle).x,GetCenterPos(circle).y };//���� ����
	POINT rPos = { GetCenterPos(rect).x,GetCenterPos(rect).y };//�簢���� ����
	float radius = (circle.right - circle.left) / 2;//���� ������

	float halfRectWidth = (rect.right - rect.left) / 2;//�簢�� �������� ��
	float halfRectHeight = (rect.bottom - rect.top) / 2;//�簢�� ���̱����� ��

														//��Ʈ�� �浹�ϴ� ���������̸�ŭ �ø� �簢��
	RECT outRect = RectMakeCenter(GetCenterPos(rect).x, GetCenterPos(rect).y,
		(rect.right - rect.left) + 2 * radius, (rect.bottom - rect.top) + 2 * radius);
	//��Ʈ�� �ܺθ����δ� �簢���� ������
	float outRadius = sqrtf(powf(halfRectWidth, 2) + powf(halfRectHeight, 2));

	//Ȯ��簢���� ������ ���� ������ ������
	if (PtInRect(&outRect, cPos))
	{
		//��Ʈ�� ���δ� ���ǹ�����+���ǹ������� �Ÿ����� Ŀ����
		if (outRadius + radius >= sqrtf(powf(cPos.x - rPos.x, 2) + powf(cPos.y - rPos.y, 2)))
			return true;
		else
			return false;
	}
	else // Ȯ��簢���� ������ ���� ������ ������ ������
		return false;
}

inline void DrawRect(HDC hdc,RECT rc, int penSize, COLORREF color)
{
	HPEN pen, oldPen;
	pen = CreatePen(PS_SOLID, penSize, color);
	oldPen = (HPEN)SelectObject(hdc, pen);

	LineMake(hdc, rc.left, rc.top, rc.right, rc.top);
	LineMake(hdc, rc.left, rc.bottom, rc.right, rc.bottom);
	LineMake(hdc, rc.left, rc.top, rc.left, rc.bottom);
	LineMake(hdc, rc.right, rc.top, rc.right, rc.bottom);

	SelectObject(hdc, oldPen);
	DeleteObject(pen);
}

inline string PathFile(string folderName, string fileName)
{
	return folderName + "\\" + fileName + ".bmp";
}

