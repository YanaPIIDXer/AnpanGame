#ifndef __TOUCHGUARD_H__
#define __TOUCHGUARD_H__

#include "cocos2d.h"
using namespace cocos2d;

/**
 * タッチガードクラス
 */
class TouchGuard : public Layer
{

public:

	// コンストラクタ
	TouchGuard();

	// 初期化.
	virtual bool init() override;

	// おまじない
	CREATE_FUNC(TouchGuard);

	// 有効・無効の設定.
	void SetEnable(bool bInEnable) { bEnable = bInEnable; }

private:

	// 有効か？
	bool bEnable;

};

#endif		// #ifndef __TOUCHGUARD_H__
