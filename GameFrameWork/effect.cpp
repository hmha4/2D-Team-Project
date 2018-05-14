#include "stdafx.h"
#include "effect.h"

effect::effect()
	:_effectImg(NULL),
	_effectAnim(NULL),
	_isRunning(false),
	_x(0),_y(0)
{
}

effect::~effect()
{
}

HRESULT effect::init(image * effectImage, int frameW, int frameH,
								int fps, float elapsedTime)
{
	if (!effectImage)return E_FAIL;

	_isRunning = false;
	_effectImg = effectImage;
	_elapsedTime = elapsedTime;

	if (!_effectAnim)
		_effectAnim = new animation;

	_effectAnim->init(_effectImg->GetWidth(), _effectImg->GetHeight(),
		frameW, frameH);
	_effectAnim->setDefPlayFrame();
	_effectAnim->setFPS(fps);
	_effectAnim->stop();

	return S_OK;
}

void effect::release()
{
	_effectImg = NULL;
	SAFE_DELETE(_effectAnim);
}

void effect::update()
{
	//실행중이지 않으면 밑으로 내려갈수 없다
	if (!_isRunning)return;

	//여기까지 프로세스가 왔다면 실행시켜준다
	_effectAnim->frameUpdate(TIMEMANAGER.getElapsedTime()*_elapsedTime);

	if (!_effectAnim->isPlay())killEffect();
}

void effect::render()
{
	if (!_isRunning)return;
	_effectImg->aniRender(getMemDC(), _x, _y, _effectAnim);
}

void effect::startEffect(int x, int y)
{
	//에니메이션이나 이미지가 없다면 내려갈수 없다
	if (!_effectAnim || !_effectImg)return;

	//중점으로 보정하는 과정
	_x = x - (_effectAnim->getFrameWidth() / 2);
	_y = y - (_effectAnim->getFrameHeight() / 2);

	_isRunning = true;
	_effectAnim->start();
}

void effect::killEffect()
{
	_isRunning = false;
}
