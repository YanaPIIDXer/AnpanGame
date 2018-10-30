#include "GameScene.h"
#include "AnpanSpawner.h"
#include "TouchGuard.h"
#include "UserData.h"
#include "JsonHelper.h"
#include "ResultScene.h"
#include "APIExecuter.h"
#include "ScriptObject.h"

// �R���X�g���N�^
GameScene::GameScene()
	: TotalScore(0)
{
}

// ������.
bool GameScene::init(const ScriptObject &Script)
{
	if (!Scene::init()) { return false; }

	pSpawner = AnpanSpawner::create();
	pSpawner->SetScriptScoreRate(Script.GetScoreRate());
	pSpawner->SetKilledCallback([this](int Score)
	{
		TotalScore += Score;
		UpdateScoreLabel();
	});
	addChild(pSpawner);

	pScoreLabel = Label::createWithTTF("Score:0", "fonts/Marker Felt.ttf", 24);
	pScoreLabel->setPosition(Vec2(100, 450));
	addChild(pScoreLabel);

	// �^�C�}�[�֌W.
	pTimer = CallbackTimer::create(Script.GetTime(), this, false);
	addChild(pTimer);
	pTimerLabel = Label::createWithTTF("", "fonts/Marker Felt.ttf", 24);
	pTimerLabel->setPosition(Vec2(600, 450));
	addChild(pTimerLabel);

	scheduleUpdate();
	return true;
}

// �X�V.
void GameScene::update(float DeltaTime)
{
	int Time = (int)pTimer->GetLastTime();
	std::stringstream Stream;
	Stream << Time;
	pTimerLabel->setString(Stream.str());
}

// ���܂��Ȃ��W�J�֐�.
GameScene *GameScene::create(const ScriptObject &Script)
{
	GameScene *pRet = new GameScene();
	if (pRet != nullptr && pRet->init(Script))
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


// �X�R�A���x���̍X�V.
void GameScene::UpdateScoreLabel()
{
	std::stringstream Stream;
	Stream << "Score:" << TotalScore;
	pScoreLabel->setString(Stream.str());
}

// �^�C�}�[�I��.
void GameScene::OnTimer(CallbackTimer * pInstance)
{
	// �Ƃ肠�����^�b�`�K�[�h
	TouchGuard *pTouchGuard = TouchGuard::create();
	addChild(pTouchGuard);

	// �A���p���̐�������~.
	pSpawner->SetEnable(false);

	RequestResult();
}

// ���U���g�v��.
void GameScene::RequestResult()
{
	APIExecuter::Result(this, TotalScore, CC_CALLBACK_1(GameScene::OnResultSuccess, this));
}

// ���U���g�v���ɐ�������
void GameScene::OnResultSuccess(HttpResponse *pResponse)
{
	JsonHelper Json(pResponse->getResponseData());
	int AfterPoint = Json.GetInt("Point");
	int HighScore = Json.GetInt("HighScore");

	// ���U���g��ʂɑJ��.
	auto *pResultScene = ResultScene::create(TotalScore, AfterPoint, HighScore);
	TransitionFade *pFade = TransitionFade::create(1.5f, pResultScene);
	Director::getInstance()->replaceScene(pFade);
}
