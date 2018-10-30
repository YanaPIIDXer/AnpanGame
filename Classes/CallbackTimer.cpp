#include "CallbackTimer.h"

// �R���X�g���N�^
CallbackTimer::CallbackTimer(float InTime, TimerDelegate *pInDelegate, bool bInRepeat)
	: Time(InTime)
	, DefaultTime(InTime)
	, pDelegate(pInDelegate)
	, bRepeat(bInRepeat)
	, bFinished(false)
{
}

// ������.
bool CallbackTimer::init()
{
	if (!Layer::init()) { return false; }

	scheduleUpdate();
	return true;
}

// �X�V.
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

// ���܂��Ȃ��W�J�֐�.
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
