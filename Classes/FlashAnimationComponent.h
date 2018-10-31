#ifndef __FLASHANIMATIONCOMPONENT_H__
#define __FLASHANIMATIONCOMPONENT_H__

#include "cocos2d.h"
using namespace cocos2d;

/**
 * �_�ŃA�j���[�V�����R���|�[�l���g
 */
class FlashAnimationComponent : public Component
{

public:

	// �R���X�g���N�^
	FlashAnimationComponent();

	// �f�X�g���N�^
	virtual ~FlashAnimationComponent() {}

	// addComponent���ꂽ�B
	virtual void onEnter() override;

	// �X�V.
	virtual void update(float frame) override;

	// �A�j���[�V�������x��ݒ�.
	void SetSpeed(int InSpeed) { Speed = InSpeed; }

	// ���܂��Ȃ�
	CREATE_FUNC(FlashAnimationComponent);

private:

	// �A���t�@�l
	int AlphaValue;

	// �A�j���[�V�������x.
	int Speed;

	// �t�F�[�h
	enum class AnimMode
	{
		FadeIn,
		FadeOut,
	} CurrentAnimMode;

};

#endif		// #ifndef __FLASHANIMATIONCOMPONENT_H__
