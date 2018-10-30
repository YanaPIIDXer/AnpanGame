#ifndef __SHOPSCENE_H__
#define __SHOPSCENE_H__

#include "cocos2d.h"
using namespace cocos2d;
class TouchGuard;
class ShopItem;

#include "network/HttpClient.h"
using namespace cocos2d::network;

#include "ui/CocosGUI.h"
using namespace ui;

/**
 * ショップ画面.
 */
class ShopScene : public Scene
{

public:

	// 初期化.
	virtual bool init() override;
	
	// おまじない
	CREATE_FUNC(ShopScene);

private:

	// タッチガード
	TouchGuard *pTouchGuard;

	// ポイント表示用ラベル
	Label *pPointLabel;

	// スタートボタン
	Button *pStartButton;

	// ショップアイテムリスト
	std::vector<ShopItem *> ShopItemList;


	// ショップ情報リクエスト
	void RequestShopData();

	// ショップ情報リクエストコールバック
	void OnResponseShopData(HttpResponse *pResponse);

	// ショップアイテムを選択した。
	void OnShopItemSelected();

	// ポイント表示用ラベルを更新.
	void UpdatePointLabel(int Point);

	// 開始ボタンが押された.
	void OnPressedStartButton(Ref *pSender);

	// 開始ＡＰＩコールバック
	void OnStartSuccess(HttpResponse *pResponse);

};

#endif		// #ifndef __SHOPSCENE_H__
