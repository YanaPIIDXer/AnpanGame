#include "Anpan.h"

const float Anpan::BaseScaleRate = 0.2f;

// 初期化.
bool Anpan::init()
{
	if (!Layer::init()) { return false; }

	// 本体スプライト
	pMainSprite = Sprite::create("Anpan.png");
	
	// 初期座標.
	Vec2 ScreenSize = Director::getInstance()->getVisibleSize();
	Vec2 Pos(random<float>(0.0f, ScreenSize.x), random<float>(0.0f, ScreenSize.y));
	pMainSprite->setPosition(Pos);
	addChild(pMainSprite);

	// 炎上パーティクル先読み
	pFireParticle = ParticleSystemQuad::create("AnpanFire.plist");
	pFireParticle->setAutoRemoveOnFinish(true);
	pFireParticle->setScale(0.5f);
	pFireParticle->setPosition(pMainSprite->getPosition());
	// ↓初期化部分以外のところでコレをやると死ぬトラップがあるらしい。
	//   仕方ないのであらかじめaddChildしておいて非表示にしておく。
	addChild(pFireParticle);
	pFireParticle->stop();

	SpriteRect = Rect(0, 0, pMainSprite->getContentSize().width, pMainSprite->getContentSize().height);

	// タッチイベントリスナ
	auto TouchListener = EventListenerTouchOneByOne::create();
	TouchListener->setSwallowTouches(true);

	TouchListener->onTouchBegan = [this](Touch *pTouch, Event *pEvent)
	{
		if (!SpriteRect.containsPoint(pMainSprite->convertTouchToNodeSpace(pTouch))) { return false; }
		if (AliveState != EAliveState::Alive) { return false; }

		AliveState = EAliveState::Fire;
		MoveVec = Vec2::ZERO;
		pMainSprite->setVisible(false);
		pFireParticle->setPosition(pMainSprite->getPosition());
		pFireParticle->resetSystem();

		if (TouchCallback != nullptr)
		{
			TouchCallback(Level);
		}

		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(TouchListener, pMainSprite);

	Level = random<int>(1, 3);

	// 移動ベクトル
	MoveVec.x = random<float>(-1.0f, 1.0f);
	MoveVec.y = random<float>(-1.0f, 1.0f);
	MoveVec.normalize();
	MoveVec *= Level * 3;

	// サイズ
	float ScaleRate = BaseScaleRate - (Level * 0.02f);
	pMainSprite->setScale(ScaleRate);

	// ↓コイツを叩く事で毎フレームupdate関数が実行されるようになる。
	scheduleUpdate();

	return true;
}

// 更新.
void Anpan::update(float DeltaTime)
{
	Vec2 Pos = pMainSprite->getPosition();
	Vec2 ScreenSize = Director::getInstance()->getVisibleSize();

	// 反射.
	if (Pos.x < 0 || Pos.x > ScreenSize.x) { MoveVec.x *= -1; }
	if (Pos.y < 0 || Pos.y > ScreenSize.y) { MoveVec.y *= -1; }

	Pos += MoveVec;
	pMainSprite->setPosition(Pos);

	if (AliveState == EAliveState::Fire && pFireParticle->isFull())
	{
		// 燃え尽きた。
		AliveState = EAliveState::Dead;
		getParent()->removeChild(this);
	}
}
