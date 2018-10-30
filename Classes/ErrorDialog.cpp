#include "ErrorDialog.h"
#include "TouchGuard.h"
#include "TitleScene.h"
#include "cocos/ui/CocosGUI.h"
using namespace ui;

// �����x���őS�p�������g����悤�ɂ��邽�߂̂���
#pragma execution_character_set("utf-8")

// ������.
bool ErrorDialog::init()
{
	if (!Layer::init()) { return false; }

	// �^�b�`�K�[�h
	TouchGuard *pTouchGuard = TouchGuard::create();
	pTouchGuard->SetEnable(true);
	addChild(pTouchGuard);

	// ��ʂ̃T�C�Y
	Size ScreenSize = Director::getInstance()->getVisibleSize();

	// �g.
	Sprite *pRect = Sprite::create();
	pRect->setTextureRect(Rect(0, 0, 600, 400));
	pRect->setPosition(Vec2(ScreenSize.width * 0.5f, ScreenSize.height * 0.5f));
	pRect->setColor(Color3B(0, 0, 255));
	addChild(pRect);

	// �G���[����.
	Label *pLabel = Label::createWithTTF("�G���[���������܂����B\n�^�C�g���ɖ߂�܂��B", "fonts/msgothic.ttc", 48);
	pLabel->setPosition(Vec2(ScreenSize.width * 0.5f, ScreenSize.height * 0.5f + 150.0f));
	addChild(pLabel);

	// �{�^��.
	Button *pButton = Button::create("Button1.png");
	pButton->setTitleText("�^�C�g���ɖ߂�");
	pButton->setPosition(Vec2(ScreenSize.width * 0.5f, ScreenSize.height * 0.5f - 100.0f));
	pButton->setScale(0.8f);
	pButton->addClickEventListener([this](Ref *pSender)
	{
		// �^�C�g���ɖ߂�.
		TitleScene *pScene = TitleScene::create();
		Director::getInstance()->replaceScene(pScene);
	});
	addChild(pButton);

	return true;
}