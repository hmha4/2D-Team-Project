#pragma once
#include "SingleTonBase.h"
#include <map>

class animation;
class image;

class KeyAniManager:public SingleTonBase<KeyAniManager>
{
private:
	typedef map<string, animation*>				animMap;
	typedef map<string, animation*>::iterator	animMapIter;
private:
	animMap	totalAnim;
public:
	KeyAniManager();
	~KeyAniManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//����Ʈ �ִϸ��̼�
	void addDefaultFrameAnimation(string animationKeyName, char*imageKeyName, int fps, bool reverse, bool loop);
	void addDefaultFrameAnimation(string animationKeyName, char*imageKeyName, int fps, bool reverse, bool loop, void*cbFunction);
	void addDefaultFrameAnimation(string animationKeyName, char*imageKeyName, int fps, bool reverse, bool loop, void*cbFunction, void*obj);

	//�迭 �ִϸ��̼�
	void addArrayFrameAnimation(string animationKeyName, char*imageKeyName, int*arr, int arrLen, int fps, bool loop);
	void addArrayFrameAnimation(string animationKeyName, char*imageKeyName, int*arr, int arrLen, int fps, bool loop, void*cbFunction);
	void addArrayFrameAnimation(string animationKeyName, char*imageKeyName, int*arr, int arrLen, int fps, bool loop, void*cbFunction, void*obj);

	//���� �ִϸ��̼�
	void addCoordinateFrameAnimation(string animationKeyName, char*imageKeyName, int start, int end, int fps, bool reverse, bool loop);
	void addCoordinateFrameAnimation(string animationKeyName, char*imageKeyName, int start, int end, int fps, bool reverse, bool loop, void*cbFunction);
	void addCoordinateFrameAnimation(string animationKeyName, char*imageKeyName, int start, int end, int fps, bool reverse, bool loop, void*cbFunction, void*obj);

	void start(string animationKeyName);
	void stop(string animationKeyName);
	void pause(string animationKeyName);
	void resume(string animationKeyName);

	animation*findAnimation(string animationKeyName);
	void deleteAll();
};

