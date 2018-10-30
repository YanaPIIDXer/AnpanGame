#include "ResultScene.h"
#include "TouchGuard.h"
#include "ShopScene.h"
#include "UserData.h"

// ������.
bool ResultScene::init(int Score, int AfterPoint, int HighScore)
{
	if (!Scene::init()) { return false; }

	Label *pTopLabel = Label::createWithTTF("Result", "fonts/msgothic.ttc", 80);
	pTopLabel->setPosition(Vec2(350, 400));
	addChild(pTopLabel);

	// �X�R�A
	{
		std::stringstream Stream;
		Stream << "Score:" << Score;

		Label *pLabel = Label::createWithTTF(Stream.str(), "fonts/msgothic.ttc", 60);
		pLabel->setPosition(Vec2(330, 300));
		addChild(pLabel);
	}

	// �|�C���g
	{
		std::stringstream Stream;
		Stream << "Point;" << UserData::GetPoint();
		Stream << " -> " << AfterPoint;

		Label *pLabel = Label::createWithTTF(Stream.str(), "fonts/msgothic.ttc", 60);
		pLabel->setPosition(Vec2(330, 200));
		addChild(pLabel);
	}

	// �n�C�X�R�A
	{
		std::stringstream Stream;
		Stream << "HighScore:" << HighScore;
		
		Label *pLabel = Label::createWithTTF(Stream.str(), "fonts/msgothic.ttc", 60);
		pLabel->setPosition(Vec2(330, 100));
		addChild(pLabel);
	}

	// �^�b�`�K�[�h
	pTouchGuard = TouchGuard::create();
	pTouchGuard->SetEnable(false);
	addChild(pTouchGuard);

	// �^�b�`�C�x���g
	auto *pTouchEvent = EventListenerTouchOneByOne::create();
	pTouchEvent->setSwallowTouches(true);
	pTouchEvent->onTouchBegan = [this](Touch *touch, Event *event)
	{
		pTouchGuard->SetEnable(true);

		// �V���b�v��ʂɖ߂�B
		auto *pShopScene = ShopScene::create();
		TransitionFade *pFade = TransitionFade::create(1.5f, pShopScene);
		Director::getInstance()->replaceScene(pFade);
		return true;
	};
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(pTouchEvent, this);

	// �F�X�ƃ��[�U�f�[�^�ɔ��f.
	UserData::SetPoint(AfterPoint);
	UserData::SetHighScore(HighScore);

	return true;
}

// ���܂��Ȃ��W�J�֐�.
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
