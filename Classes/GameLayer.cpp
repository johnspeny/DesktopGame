#include "GameLayer.h"

/*
cocos2d::Scene* GameLayer::createScene()
{
	// add gamelayer as a scene in cocos
	Scene* scene = cocos2d::Scene::create();
	//auto layer = GameLayer::create();
	//scene->addChild(layer);
	return scene;
}
*/

bool GameLayer::init() {
	if (!cocos2d::Scene::init()) {
		return false;
	}
	vel.x = 0;
	vel.y = 0;



	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();
	auto winSize = cocos2d::Director::getInstance()->getWinSize();

	// game vars
	GameVars::initVars();

	// create physics
	createPhysics();

	// add player
	player = new Player();
	player->init(_world);
	addChild(player->getBatchNode());
	//cocos2d::log("%d", player->getBatchNode());


	
	// art
	/*ball = cocos2d::Sprite::create("HelloWorld.png");
	ball->setPosition(cocos2d::Vec2(0, 0));
	this->addChild(ball);*/

	float playfield_width = visibleSize.width * 2.0f; // make the x-boundry 2 times the screen width
	float playfield_height = visibleSize.height * 2.0f; // make the y-boundry 2 times the screen height

	// camera follow the player	
	this->runAction(cocos2d::Follow::create(player->getSprite(), cocos2d::Rect(0, 0, playfield_width, playfield_height)));
	//this->runAction(cocos2d::Follow::create(player->getSprite(), cocos2d::Rect((visibleSize.width * 0.5f + origin.x) - playfield_width * 0.5f, (visibleSize.height * 0.5f + origin.y) - playfield_height * 0.5f, playfield_width, playfield_height)));

	// keyboard event listener
	auto listener = cocos2d::EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(GameLayer::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(GameLayer::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	// update
	scheduleUpdate();

	return true;
}


void GameLayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_BACKSPACE:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_RETURN:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		vel.x = -1;
		//player->updateVelocity(vel);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		vel.x = 1;
		//player->updateVelocity(vel);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_S:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_W:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_BAR:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_ENTER:
		break;
	default:
		break;
	}
	cocos2d::log("Key with keycode %d pressed", keyCode);
}

void GameLayer::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_BACKSPACE:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_RETURN:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		vel.x = 0;
		player->updateVelocity(vel);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		vel.x = 0;
		player->updateVelocity(vel);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_S:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_W:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_BAR:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_ENTER:
		break;
	default:
		break;
	}
	cocos2d::log("Key with keycode %d released", keyCode);
}

void GameLayer::update(float dt) {

	// update physics
	updatePhysics(dt);

	// update player
	if (player)
	{
		player->update(dt);
		if (vel.x == 1 || vel.x == -1)
		{
			player->updateVelocity(vel);
		}

	}

	
	//for (b2Body* b = _world->getb2World()->GetBodyList(); b; b = b->GetNext())
	//{
	//	//cocos2d::log("updating");
	//	/*
	//	if (b->GetUserData() != nullptr) {
	//		Sprite* sprite = (Sprite*)b->GetUserData();
	//		sprite->setPosition(Vec2(b->GetPosition().x *
	//			GameVars::PTM_Ratio, b->GetPosition().y * GameVars::PTM_Ratio));
	//		sprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
	//	}*/
	//}

}

void GameLayer::createPhysics()
{
	// create a b2d world
	b2Vec2 gravity;
	gravity.Set(0.0f, -9.8f);

	//create the world
	_world = b2WorldNode::create(gravity.x, gravity.y, GameVars::metersHeight);

	// added world here
	this->addChild(_world, -1);

	/*

	// w= 7.5m, h=5.0m
	// player
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(1.0f, 8.0f);
	//bodyDef.fixedRotation = true;
	playerBody = _world->getb2World()->CreateBody(&bodyDef);

	b2CircleShape dynamicCircle;
	dynamicCircle.m_radius = 0.5f;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicCircle;
	fixtureDef.density = 1.0f;
	fixtureDef.restitution = 0.1f;
	fixtureDef.friction = 0.0f;

	playerBody->CreateFixture(&fixtureDef);

	*/

	// bridge
	b2BodyDef bridgeDef;
	bridgeDef.position.Set(0.0f, 5.0f);
	b2Body* bridgeBody = _world->getb2World()->CreateBody(&bridgeDef);


	float x1 = 0, y1 = 2 * cosf(x1 / 5.0f * b2_pi), x2 = 1.0, y2 = 0;
	b2Vec2 v1(x1, y1);
	b2Vec2 v2(x2, y2);

	//cocos2d::log("Angle ==== %f", cos(90));


	for (size_t i = 0; i < 80; i++)
	{
		b2EdgeShape edge;
		v2.x = v1.x + (2 * 7.5f / 80.0f);
		v2.y = 2 * cosf(v2.x / 5.0f * b2_pi);
		edge.SetTwoSided(v1, v2);
		bridgeBody->CreateFixture(&edge, 0.0f);
		v1.x = v2.x;
		v1.y = v2.y;
	}

}

void GameLayer::updatePhysics(float dt)
{
	_world->getb2World()->Step(dt, 6, 2);
}
