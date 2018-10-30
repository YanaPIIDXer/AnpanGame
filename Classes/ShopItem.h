#ifndef __SHOPITEM_H__
#define __SHOPITEM_H__

#include "cocos2d.h"
using namespace cocos2d;

class JsonHelper;

/**
 * ショップアイテムデータ
 */
struct ShopItemData
{

public:

	// コンストラクタ
	ShopItemData(const JsonHelper &Json);

	// Id
	int Id;

	// 名前.
	std::string Name;

	// 値段.
	int Price;

};

/**
 * ショップアイテム
 */
class ShopItem : public Layer
{

public:

	// コンストラクタ
	ShopItem(const ShopItemData &InItemData);

	// 初期化.
	virtual bool init() override;

	// アイテム情報取得.
	const ShopItemData &GetItemData() const { return ItemData; }

	// 選択されているか？
	bool IsSelected() const { return bSelected; }

	// タッチコールバックを設定.
	void SetTouchCallback(const std::function<void(void)> &InOnTouched) { OnTouched = InOnTouched; }

	// おまじない展開関数.
	static ShopItem *create(const JsonHelper &Json);

	// 高さ
	static const int Height;

private:

	// アイテム情報.
	ShopItemData ItemData;

	// 選択されているか？
	bool bSelected;

	// スプライト
	Sprite *pSprite;

	// タッチ時のコールバック
	std::function<void(void)> OnTouched;

	// 初期色.
	static const Color3B DefaultColor;

	// 選択時の色.
	static const Color3B SelectedColor;

};

#endif		// #ifndef __SHOPITEM_H__
