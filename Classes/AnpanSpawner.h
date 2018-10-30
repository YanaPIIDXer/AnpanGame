#ifndef __ANPANMANAGER_H__
#define __ANPANMANAGER_H__

#include "cocos2d.h"
using namespace cocos2d;

#include "CallbackTimer.h"

/**
 * アンパン生成.
 */
class AnpanSpawner : public Layer, public TimerDelegate
{

public:

	// コンストラクタ
	AnpanSpawner();

	// 初期化.
	virtual bool init() override;

	// 有効・無効の設定.
	void SetEnable(bool bInEnable) { bEnable = bInEnable; }

	// スクリプトで設定されるスコア倍率を設定.
	void SetScriptScoreRate(float InScriptScoreRate) { ScriptScoreRate = InScriptScoreRate; }

	// 殺したときのコールバックを指定.
	void SetKilledCallback(const std::function<void(int)> &InKilledCallback) { KilledCallback = InKilledCallback; }

	// TimerDelegate を介して継承されました
	virtual void OnTimer(CallbackTimer * pInstance) override;

	// おまじない
	CREATE_FUNC(AnpanSpawner);

private:

	// スコアの倍率デフォルト値.
	static const int DefaultScoreRate;

	// スクリプトで設定されるスコア倍率.
	float ScriptScoreRate;

	// 殺したときのコールバック
	std::function<void(int)> KilledCallback;

	// 有効か？
	bool bEnable;


	// 殺した
	void OnKilled(int Score);

};

#endif		// #ifndef __ANPANMANAGER_H__
