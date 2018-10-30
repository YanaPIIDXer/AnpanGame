#include "AnpanSpawner.h"
#include "Anpan.h"

const int AnpanSpawner::DefaultScoreRate = 100;

// コンストラクタ
AnpanSpawner::AnpanSpawner()
	: bEnable(true)
	, ScriptScoreRate(1.0f)
{
}

// 初期化.
bool AnpanSpawner::init()
{
	if (!Layer::init()) { return false; }

	// タイマー
	CallbackTimer *pTimer = CallbackTimer::create(1.0f, this, true);
	addChild(pTimer);

	return true;
}

// タイマー経過.
void AnpanSpawner::OnTimer(CallbackTimer * pInstance)
{
	if (!bEnable) { return; }

	Anpan *pAnpan = Anpan::create();
	pAnpan->SetTouchCallback([this](int Score)
	{
		OnKilled(Score * DefaultScoreRate * ScriptScoreRate);
	});
	addChild(pAnpan);
}

// 殺した
void AnpanSpawner::OnKilled(int Score)
{
	if (KilledCallback != nullptr)
	{
		KilledCallback(Score);
	}
}
