#ifndef __TIMER_H__
#define __TIMER_H__

#include "cocos2d.h"
using namespace cocos2d;

class CallbackTimer;

/**
 * タイマーコールバック
 */
class TimerDelegate
{

public:

	// デストラクタ
	virtual ~TimerDelegate() {}

	// タイマーで指定した時間が経過した。
	virtual void OnTimer(CallbackTimer *pInstance) = 0;

};

/**
 * タイマークラス
 */
class CallbackTimer : public Layer
{

public:

	// コンストラクタ
	CallbackTimer(float InTime, TimerDelegate *pInDelegate, bool bInRepeat);

	// 初期化.
	virtual bool init() override;

	// 更新.
	virtual void update(float DeltaTime) override;

	// 残り時間取得.
	float GetLastTime() const { return (Time >= 0.0f ? Time : 0.0f); }

	// おまじない展開関数.
	static CallbackTimer *create(float InTime, TimerDelegate *pInDelegate, bool bInRepeat = false);

private:

	// 残り時間.
	float Time;

	// 時間初期値.
	float DefaultTime;

	// コールバック
	TimerDelegate *pDelegate;

	// 繰り返しフラグ
	bool bRepeat;

	// 終了しているか？
	bool bFinished;

};

#endif		// #ifndef __TIMER_H__