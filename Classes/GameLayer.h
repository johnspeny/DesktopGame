#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

#include "cocos2d.h"
#include "GameVars.h"
#include "b2WorldNode.h"
#include "Entities/Player.h"


class GameLayer : public cocos2d::Scene {
public:

	// add this to cocos scene
	//static cocos2d::Scene* createScene();

	// override init
	virtual bool init();

	
	// b2d variable
	cocos2d::Sprite* ball; 
	b2WorldNode* _world;
	b2Body* _groundBody;
	b2Body* playerBody;

	// keyboard events
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	

	// update the game world
	void update(float dt);

private:
	Player* player;
	cocos2d::Point vel;

	void createPhysics();
	void updatePhysics(float dt);
};

#endif