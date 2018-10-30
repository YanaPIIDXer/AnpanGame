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

struct StartResponse;

/**
 * �V���b�v���.
 */
class ShopScene : public Scene
{

public:

	// ������.
	virtual bool init() override;
	
	// ���܂��Ȃ�
	CREATE_FUNC(ShopScene);

private:

	// �^�b�`�K�[�h
	TouchGuard *pTouchGuard;

	// �|�C���g�\���p���x��
	Label *pPointLabel;

	// �X�^�[�g�{�^��
	Button *pStartButton;

	// �V���b�v�A�C�e�����X�g
	std::vector<ShopItem *> ShopItemList;


	// �V���b�v��񃊃N�G�X�g
	void RequestShopData();

	// �V���b�v��񃊃N�G�X�g�R�[���o�b�N
	void OnResponseShopData(const std::vector<ShopItem *> &ItemList);

	// �V���b�v�A�C�e����I�������B
	void OnShopItemSelected();

	// �|�C���g�\���p���x�����X�V.
	void UpdatePointLabel(int Point);

	// �J�n�{�^���������ꂽ.
	void OnPressedStartButton(Ref *pSender);

	// �J�n�`�o�h�R�[���o�b�N
	void OnStartSuccess(const StartResponse &Response);

};

#endif		// #ifndef __SHOPSCENE_H__
