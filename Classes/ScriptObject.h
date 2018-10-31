#ifndef __SCRIPTOBJECT_H__
#define __SCRIPTOBJECT_H__

#include "cocos2d.h"
using namespace cocos2d;

/**
 * スクリプトが参照するオブジェクト
 */
class ScriptObject : public CCObject
{

public:

	// コンストラクタ
	ScriptObject();

	// 時間追加.
	void AddTime(int AddTime);

	// スコア倍率を設定.
	void SetScoreRate(float InScoreRate) { ScoreRate = InScoreRate; }

	// 時間取得.
	int GetTime() const { return Time; }

	// スコア倍率取得.
	float GetScoreRate() const { return ScoreRate; }

	// 登録.
	static int Register(lua_State *pState);

	// スクリプト実行.
	static ScriptObject Execute(const std::string &Script);

private:

	// スクリプト上で実行する関数名.
	static const std::string ScriptFunctionName;

	// 時間.
	int Time;

	// スコア倍率
	float ScoreRate;

};


#endif		// #ifndef __SCRIPTOBJECT_H__
