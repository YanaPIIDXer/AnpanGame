#ifndef __TOUCHGUARD_H__
#define __TOUCHGUARD_H__

#include "cocos2d.h"
using namespace cocos2d;

/**
 * �^�b�`�K�[�h�N���X
 */
class TouchGuard : public Layer
{

public:

	// �R���X�g���N�^
	TouchGuard();

	// ������.
	virtual bool init() override;

	// ���܂��Ȃ�
	CREATE_FUNC(TouchGuard);

	// �L���E�����̐ݒ�.
	void SetEnable(bool bInEnable) { bEnable = bInEnable; }

private:

	// �L�����H
	bool bEnable;

};

#endif		// #ifndef __TOUCHGUARD_H__
