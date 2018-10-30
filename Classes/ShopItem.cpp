#include "ShopItem.h"
#include "JsonHelper.h"

const int ShopItem::Height = 70;
const Color3B ShopItem::DefaultColor = Color3B(255, 255, 255);
const Color3B ShopItem::SelectedColor = Color3B(255, 255, 0);

// コンストラクタ
ShopItem::ShopItem(const ShopItemData &InItemData)
	: ItemData(InItemData)
	, bSelected(false)
	, pSprite(nullptr)
{
}

// 初期化.
bool ShopItem::init()
{
	if (!Layer::init()) { return false; }
	
	// 外枠.
	Sprite *pOutRect = Sprite::create();
	pOutRect->setAnchorPoint(Vec2::ZERO);
	pOutRect->setTextureRect(Rect(0, 0, 420, Height + 20));
	pOutRect->setColor(Color3B(50, 50, 50));
	addChild(pOutRect);

	// スプライト
	pSprite = Sprite::create();
	pSprite->setAnchorPoint(Vec2::ZERO);
	pSprite->setTextureRect(Rect(0, 0, 400, Height));
	pSprite->setPosition(Vec2(10, 10));
	pSprite->setColor(DefaultColor);
	addChild(pSprite);

	// アイテム名.
	Label *pItemName = Label::createWithTTF(ItemData.Name, "fonts/Marker Felt.ttf", 24);
	pItemName->setAnchorPoint(Vec2::ZERO);
	pItemName->setPosition(20, Height * 0.5f);
	pItemName->setColor(Color3B(0, 0, 0));
	addChild(pItemName);

	// 値段.
	std::stringstream Stream;
	Stream << ItemData.Price << "Point";
	Label *pPriceLabel = Label::createWithTTF(Stream.str(), "fonts/Marker Felt.ttf", 24);
	pPriceLabel->setAnchorPoint(Vec2::ZERO);
	pPriceLabel->setPosition(300, Height * 0.5f);
	pPriceLabel->setColor(Color3B(0, 0, 0));
	addChild(pPriceLabel);

	// タッチイベント
	auto *pTouchEvent = EventListenerTouchOneByOne::create();
	pTouchEvent->setSwallowTouches(true);
	pTouchEvent->onTouchBegan = [this](Touch *pTouch, Event *pEvent)
	{
		Rect SpriteRect(0, 0, pSprite->getContentSize().width, pSprite->getContentSize().height);
		if (!SpriteRect.containsPoint(pSprite->convertTouchToNodeSpace(pTouch))) { return false; }

		bSelected = !bSelected;
		if (bSelected)
		{
			pSprite->setColor(SelectedColor);
		}
		else
		{
			pSprite->setColor(DefaultColor);
		}

		if (OnTouched)
		{
			OnTouched();
		}

		return true;
	};
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(pTouchEvent, pSprite);

	return true;
}

// おまじない展開関数.
ShopItem *ShopItem::create(const JsonHelper &Json)
{
	ShopItemData ItemData(Json);
	ShopItem *pRet = new ShopItem(ItemData);
	if (pRet != nullptr && pRet->init())
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

// ========== ShopItemData ==============

// コンストラクタ
ShopItemData::ShopItemData(const JsonHelper &Json)
{
	Id = Json.GetInt("Id");
	Name = Json.GetString("Name");
	Price = Json.GetInt("Price");
}
