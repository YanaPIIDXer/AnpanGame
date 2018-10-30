#include "ResultScene.h"
#include "TouchGuard.h"
#include "ShopScene.h"
#include "UserData.h"

// 初期化.
bool ResultScene::init(int Score, int AfterPoint, int HighScore)
{
	if (!Scene::init()) { return false; }

	Label *pTopLabel = Label::createWithTTF("Result", "fonts/msgothic.ttc", 80);
	pTopLabel->setPosition(Vec2(350, 400));
	addChild(pTopLabel);

	// スコア
	{
		std::stringstream Stream;
		Stream << "Score:" << Score;

		Label *pLabel = Label::createWithTTF(Stream.str(), "fonts/msgothic.ttc", 60);
		pLabel->setPosition(Vec2(330, 300));
		addChild(pLabel);
	}

	// ポイント
	{
		std::stringstream Stream;
		Stream << "Point;" << UserData::GetPoint();
		Stream << " -> " << AfterPoint;

		Label *pLabel = Label::createWithTTF(Stream.str(), "fonts/msgothic.ttc", 60);
		pLabel->setPosition(Vec2(330, 200));
		addChild(pLabel);
	}

	// ハイスコア
	{
		std::stringstream Stream;
		Stream << "HighScore:" << HighScore;
		
		Label *pLabel = Label::createWithTTF(Stream.str(), "fonts/msgothic.ttc", 60);
		pLabel->setPosition(Vec2(330, 100));
		addChild(pLabel);
	}

	// タッチガード
	pTouchGuard = TouchGuard::create();
	pTouchGuard->SetEnable(false);
	addChild(pTouchGuard);

	// タッチイベント
	auto *pTouchEvent = EventListenerTouchOneByOne::create();
	pTouchEvent->setSwallowTouches(true);
	pTouchEvent->onTouchBegan = [this](Touch *touch, Event *event)
	{
		pTouchGuard->SetEnable(true);

		// ショップ画面に戻る。
		auto *pShopScene = ShopScene::create();
		TransitionFade *pFade = TransitionFade::create(1.5f, pShopScene);
		Director::getInstance()->replaceScene(pFade);
		return true;
	};
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(pTouchEvent, this);

	// 色々とユーザデータに反映.
	UserData::SetPoint(AfterPoint);
	UserData::SetHighScore(HighScore);

	return true;
}

// おまじない展開関数.
ResultScene *ResultScene::create(int Score, int AfterPoint, int HighScore)
{
	ResultScene *pRet = new ResultScene();
	if (pRet != nullptr && pRet->init(Score, AfterPoint, HighScore))
	{
		pRet->autorelease();
	}
	else
	{
		delete pRet;
		pRet = nullptr;
	}

	return pRet;
}
