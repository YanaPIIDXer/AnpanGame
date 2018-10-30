#ifndef __ANPAN_H__
#define __ANPAN_H__

#include "cocos2d.h"
using namespace cocos2d;

/**
 * アンパンクラス
 */
class Anpan : public Layer
{

public:

	// 初期化.
	virtual bool init() override;

	// 更新.
	virtual void update(float DeltaTime) override;

	// タッチ時のコールバックを設定.
	void SetTouchCallback(const std::function<void(int)> &InTouchCallback) { TouchCallback = InTouchCallback; }

	// おまじない
	CREATE_FUNC(Anpan);

private:

	// 拡縮率ベース値.
	static const float BaseScaleRate;

	// 本体スプライト
	Sprite *pMainSprite;

	// 炎上パーティクル
	ParticleSystemQuad *pFireParticle;

	// スプライトの矩形.
	Rect SpriteRect;

	// タッチ時のコールバック
	std::function<void(int)> TouchCallback;

	// 生存ステート。内部用。
	enum class EAliveState
	{
		// 生きている
		Alive,
		// 燃えている
		Fire,
		// 燃え尽きた
		Dead,
	} AliveState = EAliveState::Alive;

	// レベル
	int Level;

	// 移動ベクトル
	Vec2 MoveVec;

};

#endif		// #ifndef __ANPAN_H__

