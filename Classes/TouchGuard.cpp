#include "TouchGuard.h"

// コンストラクタ
TouchGuard::TouchGuard()
	: bEnable(true)
{
}

// 初期化.
bool TouchGuard::init()
{
	if (!Layer::init()) { return false; }

	LayerColor *pTouchGuard = LayerColor::create(Color4B(0, 0, 0, 0));

	auto *pTouchEvent = EventListenerTouchOneByOne::create();
	pTouchEvent->setSwallowTouches(true);
	pTouchEvent->onTouchBegan = [this](Touch *touch, Event *event)
	{
		return bEnable;
	};
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(pTouchEvent, pTouchGuard);
	
	addChild(pTouchGuard);
	return true;
}
