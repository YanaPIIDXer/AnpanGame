#include "ShopScene.h"
#include "TouchGuard.h"
#include "GameScene.h"
#include "UserData.h"
#include "APIExecuter.h"
#include "ShopItem.h"
#include "ScriptObject.h"
#include "GameConfig.h"
#include "APIResponse.h"

// ↓ラベルで全角文字を使えるようにするためのもの
#pragma execution_character_set("utf-8")

// 初期化.
bool ShopScene::init()
{
	if (!Scene::init()) { return false; }

	// ポイント表示ラベル
	pPointLabel = Label::createWithTTF("Point:0", GameConfig::FontPath, 24);
	pPointLabel->setPosition(Vec2(500, 450));
	UpdatePointLabel(UserData::GetPoint());
	addChild(pPointLabel);

	// ハイスコア表示ラベル
	std::stringstream Stream;
	Stream << "HighScore:" << UserData::GetHighScore();
	Label *pHighScoreLabel = Label::createWithTTF(Stream.str(), GameConfig::FontPath, 24);
	pHighScoreLabel->setPosition(Vec2(100, 450));
	addChild(pHighScoreLabel);

	// 開始ボタン
	pStartButton = Button::create("Button1.png");
	pStartButton->setTitleText("ゲーム開始");
	pStartButton->setTitleFontSize(60.0f);
	pStartButton->setPosition(Vec2(300, 100));
	pStartButton->setScale(0.8f);
	pStartButton->addClickEventListener(CC_CALLBACK_1(ShopScene::OnPressedStartButton, this));
	addChild(pStartButton);

	// タッチガード
	pTouchGuard = TouchGuard::create();
	pTouchGuard->SetEnable(false);
	addChild(pTouchGuard);

	// ショップ情報をリクエスト
	RequestShopData();
	return true;
}


// ショップ情報リクエスト
void ShopScene::RequestShopData()
{
	APIExecuter::ShopData(this, CC_CALLBACK_1(ShopScene::OnResponseShopData, this));
}

// ショップ情報リクエストコールバック
void ShopScene::OnResponseShopData(const std::vector<ShopItem *> &ItemList)
{
	int ScreenHeight = Director::getInstance()->getVisibleSize().height;
	for (int i = 0; i < ItemList.size(); i++)
	{
		ShopItem *pItem = ItemList[i];
		pItem->setPosition(Vec2(100, 320 - ((ShopItem::Height + 20) * i)));
		pItem->SetTouchCallback(CC_CALLBACK_0(ShopScene::OnShopItemSelected, this));
		addChild(pItem);

		ShopItemList.push_back(pItem);
	}
}

// ショップアイテムを選択した。
void ShopScene::OnShopItemSelected()
{
	int TotalPrice = 0;
	for (int i = 0; i < ShopItemList.size(); i++)
	{
		auto *pItem = ShopItemList[i];
		if (pItem->IsSelected())
		{
			TotalPrice += pItem->GetItemData().Price;
		}
	}

	int Point = UserData::GetPoint() - TotalPrice;
	UpdatePointLabel(Point);
	pStartButton->setEnabled((Point >= 0));
}

// ポイント表示用ラベルを更新.
void ShopScene::UpdatePointLabel(int Point)
{
	std::stringstream Stream;
	Stream << "Point:" << Point;
	pPointLabel->setString(Stream.str());

	if (Point < 0)
	{
		pPointLabel->setColor(Color3B(255, 0, 0));
	}
	else
	{
		pPointLabel->setColor(Color3B(255, 255, 255));
	}
}

// 開始ボタンが押された
void ShopScene::OnPressedStartButton(Ref *pSender)
{
	pTouchGuard->SetEnable(true);

	// API
	std::vector<int> ItemIds;
	for (int i = 0; i < ShopItemList.size(); i++)
	{
		auto *pItem = ShopItemList[i];
		if (pItem->IsSelected())
		{
			ItemIds.push_back(pItem->GetItemData().Id);
		}
	}
	APIExecuter::Start(this, ItemIds, CC_CALLBACK_1(ShopScene::OnStartSuccess, this));
}

// 開始ＡＰＩコールバック
void ShopScene::OnStartSuccess(const StartResponse &Response)
{	
	// ポイントを反映.
	UserData::SetPoint(Response.Point);

	// スクリプト実行.
	ScriptObject Obj;
	if (Response.Script != "")
	{
		Obj = ScriptObject::Execute(Response.Script);
	}

	// シーン遷移.
	auto *pGameScene = GameScene::create(Obj);
	TransitionFade *pFade = TransitionFade::create(1.5f, pGameScene);
	Director::getInstance()->replaceScene(pFade);
}
