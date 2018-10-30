#ifndef __SHOPITEM_H__
#define __SHOPITEM_H__

#include "cocos2d.h"
using namespace cocos2d;

class JsonHelper;

/**
 * �V���b�v�A�C�e���f�[�^
 */
struct ShopItemData
{

public:

	// �R���X�g���N�^
	ShopItemData(const JsonHelper &Json);

	// Id
	int Id;

	// ���O.
	std::string Name;

	// �l�i.
	int Price;

};

/**
 * �V���b�v�A�C�e��
 */
class ShopItem : public Layer
{

public:

	// �R���X�g���N�^
	ShopItem(const ShopItemData &InItemData);

	// ������.
	virtual bool init() override;

	// �A�C�e�����擾.
	const ShopItemData &GetItemData() const { return ItemData; }

	// �I������Ă��邩�H
	bool IsSelected() const { return bSelected; }

	// �^�b�`�R�[���o�b�N��ݒ�.
	void SetTouchCallback(const std::function<void(void)> &InOnTouched) { OnTouched = InOnTouched; }

	// ���܂��Ȃ��W�J�֐�.
	static ShopItem *create(const JsonHelper &Json);

	// ����
	static const int Height;

private:

	// �A�C�e�����.
	ShopItemData ItemData;

	// �I������Ă��邩�H
	bool bSelected;

	// �X�v���C�g
	Sprite *pSprite;

	// �^�b�`���̃R�[���o�b�N
	std::function<void(void)> OnTouched;

	// �����F.
	static const Color3B DefaultColor;

	// �I�����̐F.
	static const Color3B SelectedColor;

};

#endif		// #ifndef __SHOPITEM_H__
