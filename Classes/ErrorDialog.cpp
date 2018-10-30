#include "ErrorDialog.h"
#include "TouchGuard.h"
#include "TitleScene.h"
#include "cocos/ui/CocosGUI.h"
using namespace ui;

// ↓ラベルで全角文字を使えるようにするためのもの
#pragma execution_character_set("utf-8")

// 初期化.
bool ErrorDialog::init()
{
	if (!Layer::init()) { return false; }

	// タッチガード
	TouchGuard *pTouchGuard = TouchGuard::create();
	pTouchGuard->SetEnable(true);
	addChild(pTouchGuard);

	// 画面のサイズ
	Size ScreenSize = Director::getInstance()->getVisibleSize();

	// 枠.
	Sprite *pRect = Sprite::create();
	pRect->setTextureRect(Rect(0, 0, 300, 400));
	pRect->setPosition(Vec2(ScreenSize.width * 0.5f, ScreenSize.height * 0.5f));
	addChild(pRect);

	// エラー文言.
	Label *pLabel = Label::createWithTTF("エラーが発生しました。\nタイトルに戻ります。", "fonts/Marker Felt.ttf", 24);
	pLabel->setPosition(Vec2(ScreenSize.width * 0.5f, ScreenSize.height * 0.5f + 200.0f));
	addChild(pLabel);

	// ボタン.
	Button *pButton = Button::create("Button1.png");
	pButton->setTitleText("タイトルに戻る");
	pButton->setPosition(Vec2(ScreenSize.width * 0.5f, ScreenSize.height * 0.5f - 200.0f));
	pButton->addClickEventListener([this](Ref *pSender)
	{
		// タイトルに戻す.
		TitleScene *pScene = TitleScene::create();
		Director::getInstance()->replaceScene(pScene);
	});
	addChild(pButton);

	return true;
}
