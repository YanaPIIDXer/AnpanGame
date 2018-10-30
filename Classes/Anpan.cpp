#include "Anpan.h"

const float Anpan::BaseScaleRate = 0.2f;

// ������.
bool Anpan::init()
{
	if (!Layer::init()) { return false; }

	// �{�̃X�v���C�g
	pMainSprite = Sprite::create("Anpan.png");
	
	// �������W.
	Vec2 ScreenSize = Director::getInstance()->getVisibleSize();
	Vec2 Pos(random<float>(0.0f, ScreenSize.x), random<float>(0.0f, ScreenSize.y));
	pMainSprite->setPosition(Pos);
	addChild(pMainSprite);

	// ����p�[�e�B�N����ǂ�
	pFireParticle = ParticleSystemQuad::create("AnpanFire.plist");
	pFireParticle->setAutoRemoveOnFinish(true);
	pFireParticle->setScale(0.5f);
	pFireParticle->setPosition(pMainSprite->getPosition());
	// �������������ȊO�̂Ƃ���ŃR�������Ǝ��ʃg���b�v������炵���B
	//   �d���Ȃ��̂ł��炩����addChild���Ă����Ĕ�\���ɂ��Ă����B
	addChild(pFireParticle);
	pFireParticle->stop();

	SpriteRect = Rect(0, 0, pMainSprite->getContentSize().width, pMainSprite->getContentSize().height);

	// �^�b�`�C�x���g���X�i
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

	// �ړ��x�N�g��
	MoveVec.x = random<float>(-1.0f, 1.0f);
	MoveVec.y = random<float>(-1.0f, 1.0f);
	MoveVec.normalize();
	MoveVec *= Level * 3;

	// �T�C�Y
	float ScaleRate = BaseScaleRate - (Level * 0.02f);
	pMainSprite->setScale(ScaleRate);

	// ���R�C�c��@�����Ŗ��t���[��update�֐������s�����悤�ɂȂ�B
	scheduleUpdate();

	return true;
}

// �X�V.
void Anpan::update(float DeltaTime)
{
	Vec2 Pos = pMainSprite->getPosition();
	Vec2 ScreenSize = Director::getInstance()->getVisibleSize();

	// ����.
	if (Pos.x < 0 || Pos.x > ScreenSize.x) { MoveVec.x *= -1; }
	if (Pos.y < 0 || Pos.y > ScreenSize.y) { MoveVec.y *= -1; }

	Pos += MoveVec;
	pMainSprite->setPosition(Pos);

	if (AliveState == EAliveState::Fire && pFireParticle->isFull())
	{
		// �R���s�����B
		AliveState = EAliveState::Dead;
		getParent()->removeChild(this);
	}
}
