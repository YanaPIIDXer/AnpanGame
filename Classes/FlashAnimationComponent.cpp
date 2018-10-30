#include "FlashAnimationComponent.h"

// コンストラクタ
FlashAnimationComponent::FlashAnimationComponent()
	: AlphaValue(255)
	, Speed(5)
	, CurrentAnimMode(AnimMode::FadeOut)
{
}

bool FlashAnimationComponent::init()
{
	if (!Node::init()) { return false; }

	scheduleUpdate();
	return true;
}

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
	getParent()->setOpacity(AlphaValue);
}
