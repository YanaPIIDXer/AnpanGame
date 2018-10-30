#include "ShopScene.h"
#include "TouchGuard.h"
#include "GameScene.h"
#include "UserData.h"
#include "APIExecuter.h"
#include "JsonHelper.h"
#include "ShopItem.h"
#include "ScriptObject.h"
#include "CCLuaEngine.h"

// �����x���őS�p�������g����悤�ɂ��邽�߂̂���
#pragma execution_character_set("utf-8")

// ������.
bool ShopScene::init()
{
	if (!Scene::init()) { return false; }

	// �|�C���g�\�����x��
	pPointLabel = Label::createWithTTF("Point:0", "fonts/Marker Felt.ttf", 24);
	pPointLabel->setPosition(Vec2(500, 450));
	UpdatePointLabel(UserData::GetPoint());
	addChild(pPointLabel);

	// �J�n�{�^��
	pStartButton = Button::create("Button1.png");
	pStartButton->setTitleText("�Q�[���J�n");
	pStartButton->setTitleFontSize(60.0f);
	pStartButton->setPosition(Vec2(300, 100));
	pStartButton->setScale(0.8f);
	pStartButton->addClickEventListener(CC_CALLBACK_1(ShopScene::OnPressedStartButton, this));
	addChild(pStartButton);

	// �^�b�`�K�[�h
	pTouchGuard = TouchGuard::create();
	pTouchGuard->SetEnable(false);
	addChild(pTouchGuard);

	// �V���b�v�������N�G�X�g
	RequestShopData();
	return true;
}


// �V���b�v��񃊃N�G�X�g
void ShopScene::RequestShopData()
{
	APIExecuter::ShopData(this, CC_CALLBACK_1(ShopScene::OnResponseShopData, this));
}

// �V���b�v��񃊃N�G�X�g�R�[���o�b�N
void ShopScene::OnResponseShopData(HttpResponse *pResponse)
{
	JsonHelper ShopInfo(pResponse->getResponseData());
	int Length = ShopInfo.GetArrayLength();
	int ScreenHeight = Director::getInstance()->getVisibleSize().height;
	for (int i = 0; i < Length; i++)
	{
		JsonHelper Item = ShopInfo[i];
		ShopItem *pItem = ShopItem::create(Item);
		pItem->setPosition(Vec2(100, 320 - ((ShopItem::Height + 20) * i)));
		pItem->SetTouchCallback(CC_CALLBACK_0(ShopScene::OnShopItemSelected, this));
		addChild(pItem);

		ShopItemList.push_back(pItem);
	}
}

// �V���b�v�A�C�e����I�������B
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

// �|�C���g�\���p���x�����X�V.
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

// �J�n�{�^���������ꂽ
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

// �J�n�`�o�h�R�[���o�b�N
void ShopScene::OnStartSuccess(HttpResponse *pResponse)
{
	JsonHelper Json(pResponse->getResponseData());
	
	// �|�C���g�𔽉f.
	int Point = Json.GetInt("Point");
	UserData::SetPoint(Point);

	// �X�N���v�g���s.
	std::string Script = Json.GetString("Script");
	ScriptObject Obj;
	if (Script != "")
	{
		LuaEngine *pEngine = LuaEngine::defaultEngine();
		pEngine->executeString(Script.c_str());

		lua_State *pState = pEngine->getLuaStack()->getLuaState();
		lua_getglobal(pState, "Execute");
		tolua_pushusertype(pState, &Obj, "ScriptObject");
		lua_pcall(pState, 1, 1, 0);
	}

	// �V�[���J��.
	auto *pGameScene = GameScene::create(Obj);
	TransitionFade *pFade = TransitionFade::create(1.5f, pGameScene);
	Director::getInstance()->replaceScene(pFade);
}
