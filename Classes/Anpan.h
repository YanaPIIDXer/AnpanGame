#ifndef __ANPAN_H__
#define __ANPAN_H__

#include "cocos2d.h"
using namespace cocos2d;

/**
 * �A���p���N���X
 */
class Anpan : public Layer
{

public:

	// ������.
	virtual bool init() override;

	// �X�V.
	virtual void update(float DeltaTime) override;

	// �^�b�`���̃R�[���o�b�N��ݒ�.
	void SetTouchCallback(const std::function<void(int)> &InTouchCallback) { TouchCallback = InTouchCallback; }

	// ���܂��Ȃ�
	CREATE_FUNC(Anpan);

private:

	// �g�k���x�[�X�l.
	static const float BaseScaleRate;

	// �{�̃X�v���C�g
	Sprite *pMainSprite;

	// ����p�[�e�B�N��
	ParticleSystemQuad *pFireParticle;

	// �X�v���C�g�̋�`.
	Rect SpriteRect;

	// �^�b�`���̃R�[���o�b�N
	std::function<void(int)> TouchCallback;

	// �����X�e�[�g�B�����p�B
	enum class EAliveState
	{
		// �����Ă���
		Alive,
		// �R���Ă���
		Fire,
		// �R���s����
		Dead,
	} AliveState = EAliveState::Alive;

	// ���x��
	int Level;

	// �ړ��x�N�g��
	Vec2 MoveVec;

};

#endif		// #ifndef __ANPAN_H__

