#include "TitleScene.h"
#include "FlashAnimationComponent.h"
#include "ShopScene.h"
#include "JsonHelper.h"
#include "UserData.h"
#include "IdManager.h"
#include "APIExecuter.h"

// 初期化.
bool TitleScene::init()
{
	if (!Scene::init()) { return false; }

	LayerColor *pBg = LayerColor::create(Color4B(255, 255, 255, 255));
	addChild(pBg);

	Label *pTitleLabel = Label::createWithTTF("Anpan Game", "fonts/Marker Felt.ttf", 80);
	pTitleLabel->setColor(Color3B(0, 0, 0));
	pTitleLabel->setPosition(Vec2(350, 400));
	addChild(pTitleLabel);

	pTouchToStart = Label::createWithTTF("Touch to Start", "fonts/Marker Felt.ttf", 24);
	pTouchToStart->setColor(Color3B(0, 0, 0));
	pTouchToStart->setPosition(Vec2(350, 150));
	addChild(pTouchToStart);

	pFlash = FlashAnimationComponent::create();
	pTouchToStart->addChild(pFlash);

	// タッチイベント
	pTouchEvent = EventListenerTouchOneByOne::create();
	pTouchEvent->setSwallowTouches(true);
	pTouchEvent->onTouchBegan = [this](Touch *touch, Event *event)
	{
		pFlash->SetSpeed(20);
		getEventDispatcher()->removeEventListener(pTouchEvent);

		RequestAuth();
		return true;
	};

	getEventDispatcher()->addEventListenerWithSceneGraphPriority(pTouchEvent, this);

	return true;
}

// 認証をリクエスト
void TitleScene::RequestAuth()
{
	IdManager IdMgr;
	APIExecuter::Auth(IdMgr.GetId(), CC_CALLBACK_1(TitleScene::OnAuthSuccess, this));
}

// 認証に成功した。
void TitleScene::OnAuthSuccess(HttpResponse *pResponse)
{
	std::vector<char> *pBuffer = pResponse->getResponseData();
	JsonHelper Helper(pBuffer);
	std::string Id = Helper.GetString("Id");
	int Point = Helper.GetInt("Point");
	int HighScore = Helper.GetInt("HighScore");
	UserData::Set(Id, Point, HighScore);

	MoveToNextScene();
}

// 次のシーンに遷移.
void TitleScene::MoveToNextScene()
{
	auto *pShopScene = ShopScene::create();
	TransitionFade *pFade = TransitionFade::create(1.5f, pShopScene);
	Director::getInstance()->replaceScene(pFade);
}
