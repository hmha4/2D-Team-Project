#pragma once
struct BackBufferInfo
{
	HDC hBackDC; // ����� DC����
	HBITMAP hBit; // �� ��Ʈ�� �̹��� 
	HBITMAP hOldBit; // �õ� ��Ʈ��
	int width;
	int height;

	BackBufferInfo() // ����ü�� ������
	{
		hBackDC = NULL;
		hBit = NULL;
		hOldBit = NULL;
		width = 0;
		height = 0;
	}
};
class BackBuffer
{
private:
	BackBufferInfo*backBuffer; //����� ����ü ������
public:
	BackBuffer();
	~BackBuffer();

	HRESULT Init(int width, int height); // ����� �ʱ�ȭ
	void Render(HDC hdc); // �����->�չ��� ����
	void Release(); // �޸� ����

	//����� DC������ ������
	inline HDC GetBackDC() { return backBuffer->hBackDC; }
};

