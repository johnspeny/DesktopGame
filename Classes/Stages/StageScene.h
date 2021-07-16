#ifndef __STAGESCENE_H__
#define __STAGESCENE_H__

#include "../Classes/GameLayer.h"

class StageScene : public cocos2d::Scene {
public:
	// add this to cocos scene
	static cocos2d::Scene* createScene();

	// override init
	virtual bool init();
};

#endif // !__STAGESCENE_H__
