#ifndef __TIMER_H__
#define __TIMER_H__

#include "cocos2d.h"
using namespace cocos2d;

class CallbackTimer;

/**
 * �^�C�}�[�R�[���o�b�N
 */
class TimerDelegate
{

public:

	// �f�X�g���N�^
	virtual ~TimerDelegate() {}

	// �^�C�}�[�Ŏw�肵�����Ԃ��o�߂����B
	virtual void OnTimer(CallbackTimer *pInstance) = 0;

};

/**
 * �^�C�}�[�N���X
 */
class CallbackTimer : public Layer
{

public:

	// �R���X�g���N�^
	CallbackTimer(float InTime, TimerDelegate *pInDelegate, bool bInRepeat);

	// ������.
	virtual bool init() override;

	// �X�V.
	virtual void update(float DeltaTime) override;

	// �c�莞�Ԏ擾.
	float GetLastTime() const { return (Time >= 0.0f ? Time : 0.0f); }

	// ���܂��Ȃ��W�J�֐�.
	static CallbackTimer *create(float InTime, TimerDelegate *pInDelegate, bool bInRepeat = false);

private:

	// �c�莞��.
	float Time;

	// ���ԏ����l.
	float DefaultTime;

	// �R�[���o�b�N
	TimerDelegate *pDelegate;

	// �J��Ԃ��t���O
	bool bRepeat;

	// �I�����Ă��邩�H
	bool bFinished;

};

#endif		// #ifndef __TIMER_H__