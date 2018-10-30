#include "GameScene.h"
#include "AnpanSpawner.h"
#include "TouchGuard.h"
#include "UserData.h"
#include "JsonHelper.h"
#include "ResultScene.h"
#include "APIExecuter.h"
#include "ScriptObject.h"

// コンストラクタ
GameScene::GameScene()
	: TotalScore(0)
{
}

// 初期化.
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

	// タイマー関係.
	pTimer = CallbackTimer::create(Script.GetTime(), this, false);
	addChild(pTimer);
	pTimerLabel = Label::createWithTTF("", "fonts/Marker Felt.ttf", 24);
	pTimerLabel->setPosition(Vec2(600, 450));
	addChild(pTimerLabel);

	scheduleUpdate();
	return true;
}

// 更新.
void GameScene::update(float DeltaTime)
{
	int Time = (int)pTimer->GetLastTime();
	std::stringstream Stream;
	Stream << Time;
	pTimerLabel->setString(Stream.str());
}

// おまじない展開関数.
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


// スコアラベルの更新.
void GameScene::UpdateScoreLabel()
{
	std::stringstream Stream;
	Stream << "Score:" << TotalScore;
	pScoreLabel->setString(Stream.str());
}

// タイマー終了.
void GameScene::OnTimer(CallbackTimer * pInstance)
{
	// とりあえずタッチガード
	TouchGuard *pTouchGuard = TouchGuard::create();
	addChild(pTouchGuard);

	// アンパンの生成も停止.
	pSpawner->SetEnable(false);

	RequestResult();
}

// リザルト要求.
void GameScene::RequestResult()
{
	APIExecuter::Result(this, TotalScore, CC_CALLBACK_1(GameScene::OnResultSuccess, this));
}

// リザルト要求に成功した
void GameScene::OnResultSuccess(HttpResponse *pResponse)
{
	JsonHelper Json(pResponse->getResponseData());
	int AfterPoint = Json.GetInt("Point");
	int HighScore = Json.GetInt("HighScore");

	// リザルト画面に遷移.
	auto *pResultScene = ResultScene::create(TotalScore, AfterPoint, HighScore);
	TransitionFade *pFade = TransitionFade::create(1.5f, pResultScene);
	Director::getInstance()->replaceScene(pFade);
}
