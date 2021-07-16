#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "cocos2d.h"
#include "box2d/box2d.h"
#include "b2WorldNode.h"
#include "GameVars.h"


class Entity {

public:
	Entity();
	virtual ~Entity();
	void setBatchNode(cocos2d::SpriteBatchNode* batchNode);
	cocos2d::SpriteBatchNode* getBatchNode();
	cocos2d::Sprite* getSprite();
	int getDirection();
	int getState();

protected:
	cocos2d::SpriteBatchNode* batchNode;
	b2WorldNode* _world;
	b2Body* _body;
	int direction;
	cocos2d::Sprite* sprite;
	
	cocos2d::Animation* animationDefault;
	cocos2d::Animate* animateDefault;
	cocos2d::RepeatForever* actionStateDefault;

	cocos2d::Animation* animationMoving;
	cocos2d::Animate* animateMoving;
	cocos2d::RepeatForever* actionStateMoving;

	int state; // 1 = default, 2 = moving, 3 = jumping 
};


#endif // !__ENTITY_H__
