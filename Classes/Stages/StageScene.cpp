#include "StageScene.h"

cocos2d::Scene* StageScene::createScene()
{
	// add gamelayer as a scene in cocos
	Scene* scene = cocos2d::Scene::create();
	auto gameLayer = GameLayer::create();
	scene->addChild(gameLayer);
	return scene;
}

bool StageScene::init()
{
	if (!cocos2d::Scene::init())
	{
		return false;
	}
	return true;
}
