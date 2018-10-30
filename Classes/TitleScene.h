#ifndef __TITLESCENE_H__
#define __TITLESCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

#include "network/HttpClient.h"
using namespace cocos2d::network;

class FlashAnimationComponent;
struct AuthResponse;

/**
 * �^�C�g�����
 */
class TitleScene : public Scene
{

public:

	// ������.
	virtual bool init() override;

	// ���܂��Ȃ�
	CREATE_FUNC(TitleScene);

private:

	// �F�؂����N�G�X�g.
	void RequestAuth();

	// �F�؂ɐ�������
	void OnAuthSuccess(const AuthResponse &Response);

	// ���̃V�[���ɑJ��.
	void MoveToNextScene();


	// TouchToStart�̕�����.
	Label *pTouchToStart;

	// �_�ŃA�j���[�V����
	FlashAnimationComponent *pFlash;

	// �^�b�`�C�x���g
	EventListenerTouchOneByOne *pTouchEvent;

};

#endif		// #ifndef __TITLESCENE_H__
