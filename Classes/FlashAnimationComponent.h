#ifndef __FLASHANIMATIONCOMPONENT_H__
#define __FLASHANIMATIONCOMPONENT_H__

#include "cocos2d.h"
using namespace cocos2d;

/**
 * 点滅アニメーションコンポーネント
 */
class FlashAnimationComponent : public Node
{

public:

	// コンストラクタ
	FlashAnimationComponent();

	// デストラクタ
	virtual ~FlashAnimationComponent() {}

	// 初期化。
	virtual bool init() override;

	// 更新.
	virtual void update(float frame) override;

	// アニメーション速度を設定.
	void SetSpeed(int InSpeed) { Speed = InSpeed; }

	// おまじない
	CREATE_FUNC(FlashAnimationComponent);

private:

	// アルファ値
	int AlphaValue;

	// アニメーション速度.
	int Speed;

	// フェード
	enum class AnimMode
	{
		FadeIn,
		FadeOut,
	} CurrentAnimMode;

};

#endif		// #ifndef __FLASHANIMATIONCOMPONENT_H__
