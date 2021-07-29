#include "GameLayer.h"
#include <iostream>

bool GameLayer::init() {
	if (!cocos2d::Scene::init()) {
		return false;
	}
	vel.x = 0;
	vel.y = 0;


	visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
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
	

	float playfield_width = visibleSize.width * 2.0f; // make the x-boundry 2 times the screen width
	float playfield_height = visibleSize.height * 2.0f; // make the y-boundry 2 times the screen height

	// camera follow the player	
	this->runAction(cocos2d::Follow::create(player->getSprite(), cocos2d::Rect(0, 0, playfield_width, playfield_height * 0.5f)));
	
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
	/*if (std::find(heldKeysz.begin(), heldKeysz.end(), keyCode) == heldKeysz.end())
		{
			heldKeysz[keyCode] = std::chrono::system_clock::now();
			//std::cout << "Number of keys" << heldKeysz.size() << std::endl;
		}*/	
	if (heldKeysz.find(keyCode) == heldKeysz.end())
	{
		heldKeysz[keyCode] = std::chrono::system_clock::now();
		cocos2d::log("Number of keys %i", heldKeysz.size());
		
	}
}

void GameLayer::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	// heldKeys.erase(std::remove(heldKeys.begin(), heldKeys.end(), keyCode), heldKeys.end());	
	/*if (heldKeysz.find(cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW) != heldKeysz.end())
	{
		std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - heldKeysz[cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW];
		//std::cout << "Key code " << int(keyCode) << " was down for " << elapsed_seconds.count() << "s" << std::endl;
		cocos2d::log("Key code for %f seconds", elapsed_seconds.count());
	}*/

	heldKeysz.erase(keyCode);
	vel.x = 0;
	player->jumpOnPress(0, false);
}

void GameLayer::update(float dt) {

	// update physics
	updatePhysics(dt);

	// update player
	if (player)
	{
		player->update(dt);
		
		// moving left and right
		
		if (isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW))
		{
			vel.x = -1;
			cocos2d::log("left pressed");
		}
		

		if (isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW))
		{
			vel.x = 1;
			cocos2d::log("Right pressed");
		}

		player->updateVelocity(cocos2d::Point(vel.x, 0));
		
		cocos2d::log("number foot %d", myContactListener->numFootContacts);


		// jumping
		if (isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW))
		{
			std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - heldKeysz[cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW];
			if (elapsed_seconds.count() > 0.1f)
			{
				player->jumpOnPress(0, false);
			}
			else
			{
				cocos2d::log("Up pressed for %f seconds", elapsed_seconds.count());
				cocos2d::log("number foot %d", myContactListener->numFootContacts);
				if (myContactListener->numFootContacts < 1) return;
				player->jumpOnPress(1, true);
			}
		}

	}

	// check contacts and update collisions
	std::vector<ContactData>::iterator pos;
	for (pos = myContactListener->_contacts.begin(); pos != myContactListener->_contacts.end(); ++pos)
	{
		ContactData contact = *pos;

		// get the box2d bodies for each object
		b2Body* bodyA = contact.fixtureA->GetBody();
		b2Body* bodyB = contact.fixtureB->GetBody();

		if (bodyA->GetUserData().pointer != NULL && bodyB->GetUserData().pointer != NULL)
		{
			Entity* entityA = (Entity*)bodyA->GetUserData().pointer;
			Entity* entityB = (Entity*)bodyB->GetUserData().pointer;

			int bTagA = entityA->getTag();
			int bTagB = entityB->getTag();

			if (bTagA == Entity::TAG_PLAYER)
			{

			}

			else if (bTagB == Entity::TAG_PLAYER)
			{

			}

			// check sprite tags


		}
	}

}

void GameLayer::createPhysics()
{
	// create a b2d world
	b2Vec2 gravity;
	gravity.Set(0.0f, -9.8f);

	// create the world
	_world = b2WorldNode::create(gravity.x, gravity.y, GameVars::metersHeight);

	// contact listener
	myContactListener = new MyContactListener();
	_world->getb2World()->SetContactListener(myContactListener);

	// added world here
	this->addChild(_world, -1);

	// bridge
	b2BodyDef bridgeDef;
	bridgeDef.type = b2_staticBody;
	bridgeDef.position.Set(0.0f, visibleSize.height * 0.1f / GameVars::PTM_Ratio);
	b2Body* bridgeBody = _world->getb2World()->CreateBody(&bridgeDef);

	// bridge shape
	b2PolygonShape bridgeShape;
	bridgeShape.SetAsBox((float)(visibleSize.width / GameVars::PTM_Ratio), 0.5f);

	// connect body to shape
	bridgeBody->CreateFixture(&bridgeShape, 0.0f);

	
}

void GameLayer::updatePhysics(float dt)
{
	_world->getb2World()->Step(dt, 6, 2);
}


bool GameLayer::isKeyPressed(cocos2d::EventKeyboard::KeyCode code)
{
	if (heldKeysz.find(code) != heldKeysz.end())
		return true;
	return false;
}
