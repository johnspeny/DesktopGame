#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

#include "cocos2d.h"
#include "GameVars.h"
#include "b2WorldNode.h"
#include "Entities/Player.h"
#include "Extras/MyContactListener.h"


class GameLayer : public cocos2d::Scene {
public:

	// override init
	virtual bool init();

	
	// b2d variable
	cocos2d::Sprite* ball; 
	b2WorldNode* _world;
	b2Body* _groundBody;
	b2Body* playerBody;

	// to help with keyboard
	std::vector<cocos2d::EventKeyboard::KeyCode> heldKeys;
	std::map<cocos2d::EventKeyboard::KeyCode, std::chrono::system_clock::time_point> heldKeysz;
	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);


	// keyboard events
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	

	// update the game world
	void update(float dt);

private:
	MyContactListener* myContactListener;
	Player* player;
	cocos2d::Point vel;
	cocos2d::Size visibleSize;

	void createPhysics();
	void updatePhysics(float dt);
};

#endif