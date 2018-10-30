#ifndef __ANPANMANAGER_H__
#define __ANPANMANAGER_H__

#include "cocos2d.h"
using namespace cocos2d;

#include "CallbackTimer.h"

/**
 * �A���p������.
 */
class AnpanSpawner : public Layer, public TimerDelegate
{

public:

	// �R���X�g���N�^
	AnpanSpawner();

	// ������.
	virtual bool init() override;

	// �L���E�����̐ݒ�.
	void SetEnable(bool bInEnable) { bEnable = bInEnable; }

	// �X�N���v�g�Őݒ肳���X�R�A�{����ݒ�.
	void SetScriptScoreRate(float InScriptScoreRate) { ScriptScoreRate = InScriptScoreRate; }

	// �E�����Ƃ��̃R�[���o�b�N���w��.
	void SetKilledCallback(const std::function<void(int)> &InKilledCallback) { KilledCallback = InKilledCallback; }

	// TimerDelegate ����Čp������܂���
	virtual void OnTimer(CallbackTimer * pInstance) override;

	// ���܂��Ȃ�
	CREATE_FUNC(AnpanSpawner);

private:

	// �X�R�A�̔{���f�t�H���g�l.
	static const int DefaultScoreRate;

	// �X�N���v�g�Őݒ肳���X�R�A�{��.
	float ScriptScoreRate;

	// �E�����Ƃ��̃R�[���o�b�N
	std::function<void(int)> KilledCallback;

	// �L�����H
	bool bEnable;


	// �E����
	void OnKilled(int Score);

};

#endif		// #ifndef __ANPANMANAGER_H__
