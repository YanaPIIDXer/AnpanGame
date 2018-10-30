#include "AnpanSpawner.h"
#include "Anpan.h"

const int AnpanSpawner::DefaultScoreRate = 100;

// �R���X�g���N�^
AnpanSpawner::AnpanSpawner()
	: bEnable(true)
	, ScriptScoreRate(1.0f)
{
}

// ������.
bool AnpanSpawner::init()
{
	if (!Layer::init()) { return false; }

	// �^�C�}�[
	CallbackTimer *pTimer = CallbackTimer::create(1.0f, this, true);
	addChild(pTimer);

	return true;
}

// �^�C�}�[�o��.
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

// �E����
void AnpanSpawner::OnKilled(int Score)
{
	if (KilledCallback != nullptr)
	{
		KilledCallback(Score);
	}
}
