#ifndef __TERRAIN_TEST_H__
#define __TERRAIN_TEST_H__

#include "cocos2d.h"
#include "GameVars.h"
#include "b2WorldNode.h"


class TerrainTest : public cocos2d::Node
{
public:
	TerrainTest();
	~TerrainTest();
	cocos2d::CustomCommand _renderCmds[1];
private:
	//cocos2d::GLProgramState
};


#endif // !__TERRAIN_TEST_H__
