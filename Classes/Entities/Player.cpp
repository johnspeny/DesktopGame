#include "Player.h"

Player::Player()
{
	direction = 2; // 1 = left, 2 = right
	state = 1;
}

Player::~Player()
{
	_body = NULL;
	actionStateDefault->release();
	actionStateMoving->release();
}

bool Player::init(b2WorldNode* _playerWorld) {
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	// game physics constants
	// game vars
	GameVars::initVars();

	// node and sprite
	batchNode = cocos2d::SpriteBatchNode::create("character/man/Man.pvr.ccz");

	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile("character/man/Man.plist");
	sprite = cocos2d::Sprite::createWithSpriteFrameName("player_stand.png");
	

	
	sprite->setPosition(cocos2d::Vec2(visibleSize.width * 0.5f + origin.x, visibleSize.height * 0.8f + origin.y));
	sprite->setTag(1);

	// animation for default state
	animationDefault = cocos2d::Animation::create();
	
	animationDefault->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("player_idle.png"));
	animationDefault->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("player_stand.png"));
	animationDefault->setDelayPerUnit(1.0 / 1);
	animationDefault->setRestoreOriginalFrame(true);

	animateDefault = cocos2d::Animate::create(animationDefault);
	actionStateDefault = RepeatForever::create(animateDefault);
	actionStateDefault->retain();

	// animation for moving state
	animationMoving = cocos2d::Animation::create();

	for (size_t i = 1; i < 3; i++)
	{
		char szImageFileName[128] = { 0 };
		sprintf(szImageFileName, "player_walk%i.png", i);
		animationMoving->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(szImageFileName));
	}
		
	animationMoving->setDelayPerUnit(0.5f);
	animationMoving->setRestoreOriginalFrame(true);

	animateMoving = cocos2d::Animate::create(animationMoving);
	actionStateMoving = RepeatForever::create(animateMoving);
	actionStateMoving->retain();


	// create physics
	this->_world = _playerWorld;
	b2BodyDef playerBodyDef;
	playerBodyDef.type = b2_dynamicBody;
	playerBodyDef.position.Set(sprite->getPositionX() / GameVars::PTM_Ratio, sprite->getPositionY() / GameVars::PTM_Ratio);
	playerBodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
	playerBodyDef.fixedRotation = true;
	_body = _world->getb2World()->CreateBody(&playerBodyDef);


	b2PolygonShape dynamicCircle;
	dynamicCircle.SetAsBox(sprite->getContentSize().width*0.25f / GameVars::PTM_Ratio, sprite->getContentSize().height*0.5f / GameVars::PTM_Ratio);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicCircle;
	fixtureDef.density = 1.0f;
	fixtureDef.restitution = 0.1f;
	fixtureDef.friction = 0.0f;

	_body->CreateFixture(&fixtureDef);

	// set default state
	setStateDefault();
	changeDirection(direction);

	batchNode->addChild(sprite);

	return true;
}

void Player::changeDirection(int _playerDirection) {
	// turn left
	if (_playerDirection == 1 && this->direction != _playerDirection)
	{
		sprite->setFlippedX(true);
		this->direction = _playerDirection;
	}
	// turn right
	else if (_playerDirection == 2 && this->direction != _playerDirection)
	{
		sprite->setFlippedX(false);
		this->direction = _playerDirection;
	}

}

void Player::move(cocos2d::Point velocity)
{
	b2Vec2 impulse;

	// move forward
	if (velocity.x == 1)
	{
		setStateMoving();
		changeDirection(2);
		//impulse = b2Vec2(0.25f * _body->GetMass(), 0.0f);
		//_body->ApplyLinearImpulse(impulse, _body->GetWorldCenter(), true);
		_body->SetLinearVelocity(b2Vec2(5.0f, _body->GetLinearVelocity().y));
	}
	else if (velocity.x == -1)
	{
		setStateMoving();
		changeDirection(1);
		//impulse = b2Vec2(-0.25f * _body->GetMass(), 0.0f);
		//_body->ApplyLinearImpulse(impulse, _body->GetWorldCenter(), true);
		_body->SetLinearVelocity(b2Vec2(-5.0f, _body->GetLinearVelocity().y));
	}
	else if (velocity.x == 0)
	{
		//float xSpeed = _body->GetLinearVelocity().x;
		//_body->SetLinearVelocity(b2Vec2_zero);
		//b2Vec2 velocity = _body->GetLinearVelocity();
		//velocity.x = 0;
		_body->SetLinearVelocity(b2Vec2(0.0f, _body->GetLinearVelocity().y));
		setStateDefault();
		//_body->SetLinearDamping();
	}
}

void Player::updateVelocity(cocos2d::Point velocity)
{
	move(velocity);
}

void Player::update(float dt)
{
	if (_world) {
		for (b2Body* b = _world->getb2World()->GetBodyList(); b ; b=b->GetNext())
		{
			//uintptr_t* p = &b->GetUserData().pointer;
						
			if (b->GetUserData().pointer != NULL) {
				Player* userData = (Player*)b->GetUserData().pointer;
				
				
				// if ball is going too fast, turn on damping
				if (userData->sprite->getTag() == 1) {
					static int maxSpeed = 3.0f;

					b2Vec2 velocity = b->GetLinearVelocity();
					float speed = velocity.Length();

				

					if (speed > maxSpeed) {
						//b->SetLinearDamping(1.5f);
					}
					else if (speed < maxSpeed) {
						//b->SetLinearDamping(1.5f);
					}

				}
				
				
				userData->sprite->setPosition(cocos2d::Vec2(b->GetPosition().x * GameVars::PTM_Ratio, b->GetPosition().y * GameVars::PTM_Ratio));
				userData->sprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
			}
		}
	}
}



void Player::setStateDefault()
{
	if (state == 2)
	{
		state = 1;
		sprite->stopAllActions();
		sprite->runAction(actionStateDefault);
	}
}

void Player::setStateMoving()
{
	if (state == 1)
	{
		state = 2;
		sprite->stopAllActions();
		sprite->runAction(actionStateMoving);
	}
}

int Player::getTag()
{
	return Entity::TAG_PLAYER;
}

void Player::jumpOnPress()
{
	_body->ApplyLinearImpulse(b2Vec2(0, _body->GetMass() * 1), _body->GetWorldCenter(), true);
}
