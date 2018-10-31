#include "FlashAnimationComponent.h"

// �R���X�g���N�^
FlashAnimationComponent::FlashAnimationComponent()
	: AlphaValue(255)
	, Speed(5)
	, CurrentAnimMode(AnimMode::FadeOut)
{
}

// addComponent���ꂽ�B
void FlashAnimationComponent::onEnter()
{
	Component::onEnter();

	getOwner()->scheduleUpdate();
}

// �X�V.
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
