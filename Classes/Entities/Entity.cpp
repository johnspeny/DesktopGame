#include "Entity.h"

Entity::Entity() {

}

Entity::~Entity() {

}

void Entity::setBatchNode(cocos2d::SpriteBatchNode* batchNode) {
	this->batchNode = batchNode;
}

cocos2d::SpriteBatchNode* Entity::getBatchNode() {
	return batchNode;
}

cocos2d::Sprite* Entity::getSprite()
{
	return sprite;
}

int Entity::getDirection() {
	return direction;
}

int Entity::getState()
{
	return state;
}

int Entity::getTag()
{
	return 0;
}
