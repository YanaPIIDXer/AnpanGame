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
 * ゲーム画面.
 */
class GameScene : public Scene, public TimerDelegate
{

public:

	// コンストラクタ
	GameScene();

	// 初期化.
	//virtual bool init() override;
	bool init(const ScriptObject &Script);

	// 更新.
	virtual void update(float DeltaTime) override;

	// おまじない
	//CREATE_FUNC(GameScene);
	// おまじない展開関数.
	static GameScene *create(const ScriptObject &Script);

	// TimerDelegate を介して継承されました
	virtual void OnTimer(CallbackTimer * pInstance) override;

private:

	// スコア
	int TotalScore;

	// スコアラベル
	Label *pScoreLabel;

	// タイマー
	CallbackTimer *pTimer;

	// タイマーラベル
	Label *pTimerLabel;

	// アンパン生成.
	AnpanSpawner *pSpawner;


	// スコアラベルの更新.
	void UpdateScoreLabel();

	// リザルト要求.
	void RequestResult();

	// リザルト要求に成功した
	void OnResultSuccess(HttpResponse *pResponse);

};

#endif		// #ifndef __GAMESCENE_H__
