#ifndef __TITLESCENE_H__
#define __TITLESCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

#include "network/HttpClient.h"
using namespace cocos2d::network;

class FlashAnimationComponent;
struct AuthResponse;

/**
 * タイトル画面
 */
class TitleScene : public Scene
{

public:

	// 初期化.
	virtual bool init() override;

	// おまじない
	CREATE_FUNC(TitleScene);

private:

	// 認証をリクエスト.
	void RequestAuth();

	// 認証に成功した
	void OnAuthSuccess(const AuthResponse &Response);

	// 次のシーンに遷移.
	void MoveToNextScene();


	// TouchToStartの文字列.
	Label *pTouchToStart;

	// 点滅アニメーション
	FlashAnimationComponent *pFlash;

	// タッチイベント
	EventListenerTouchOneByOne *pTouchEvent;

};

#endif		// #ifndef __TITLESCENE_H__
