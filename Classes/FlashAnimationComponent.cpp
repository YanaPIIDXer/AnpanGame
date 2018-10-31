#include "FlashAnimationComponent.h"

// コンストラクタ
FlashAnimationComponent::FlashAnimationComponent()
	: AlphaValue(255)
	, Speed(5)
	, CurrentAnimMode(AnimMode::FadeOut)
{
}

// addComponentされた。
void FlashAnimationComponent::onEnter()
{
	Component::onEnter();

	getOwner()->scheduleUpdate();
}

// 更新.
void FlashAnimationComponent::update(float frame)
{
	if (CurrentAnimMode == AnimMode::FadeIn)
	{
		AlphaValue += Speed;
		if (AlphaValue >= 255)
		{
			AlphaValue = 255;
			CurrentAnimMode = AnimMode::FadeOut;
		}
	}
	else
	{
		AlphaValue -= Speed;
		if (AlphaValue <= 0)
		{
			AlphaValue = 0;
			CurrentAnimMode = AnimMode::FadeIn;
		}
	}
	getOwner()->setOpacity(AlphaValue);
}
