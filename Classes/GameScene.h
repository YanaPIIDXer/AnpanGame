#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
using namespace cocos2d;
#include "CallbackTimer.h"
class AnpanSpawner;

#include "network/HttpClient.h"
using namespace cocos2d::network;

class ScriptObject;

/**
 * �Q�[�����.
 */
class GameScene : public Scene, public TimerDelegate
{

public:

	// �R���X�g���N�^
	GameScene();

	// ������.
	//virtual bool init() override;
	bool init(const ScriptObject &Script);

	// �X�V.
	virtual void update(float DeltaTime) override;

	// ���܂��Ȃ�
	//CREATE_FUNC(GameScene);
	// ���܂��Ȃ��W�J�֐�.
	static GameScene *create(const ScriptObject &Script);

	// TimerDelegate ����Čp������܂���
	virtual void OnTimer(CallbackTimer * pInstance) override;

private:

	// �X�R�A
	int TotalScore;

	// �X�R�A���x��
	Label *pScoreLabel;

	// �^�C�}�[
	CallbackTimer *pTimer;

	// �^�C�}�[���x��
	Label *pTimerLabel;

	// �A���p������.
	AnpanSpawner *pSpawner;


	// �X�R�A���x���̍X�V.
	void UpdateScoreLabel();

	// ���U���g�v��.
	void RequestResult();

	// ���U���g�v���ɐ�������
	void OnResultSuccess(HttpResponse *pResponse);

};

#endif		// #ifndef __GAMESCENE_H__
