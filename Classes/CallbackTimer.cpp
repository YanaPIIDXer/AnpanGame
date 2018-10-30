#include "CallbackTimer.h"

// コンストラクタ
CallbackTimer::CallbackTimer(float InTime, TimerDelegate *pInDelegate, bool bInRepeat)
	: Time(InTime)
	, DefaultTime(InTime)
	, pDelegate(pInDelegate)
	, bRepeat(bInRepeat)
	, bFinished(false)
{
}

// 初期化.
bool CallbackTimer::init()
{
	if (!Layer::init()) { return false; }

	scheduleUpdate();
	return true;
}

// 更新.
void CallbackTimer::update(float DeltaTime)
{
	if (bFinished) { return; }

	Time -= DeltaTime;
	if (Time <= 0.0f)
	{
		pDelegate->OnTimer(this);
		if (bRepeat)
		{
			Time += DefaultTime;
		}
		else
		{
			bFinished = true;
		}
	}
}

// おまじない展開関数.
CallbackTimer *CallbackTimer::create(float InTime, TimerDelegate *pInDelegate, bool bInRepeat)
{
	auto *pRet = new CallbackTimer(InTime, pInDelegate, bInRepeat);
	if (pRet != nullptr && pRet->init())
	{
		pRet->autorelease();
	}
	else
	{
		delete pRet;
		pRet = nullptr;
	}

	return pRet;
}
