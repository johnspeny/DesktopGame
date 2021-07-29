#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "cocos2d.h"
#include "GameVars.h"
#include "b2WorldNode.h"

class Player : public Entity {

public:
	Player();
	virtual ~Player();
	const int x = 6;
	virtual bool init(b2WorldNode* _playerWorld);
	
	void changeDirection(int _playerDirection);
	void move(cocos2d::Point velocity);
	void updateVelocity(cocos2d::Point velocity);
	void update(float dt);


	void setStateDefault();
	void setStateMoving();
	int getTag();

	void jumpOnPress(int acc, bool isJ);
	int m_jumpTimeout;
};

#endif // !__PLAYER_H__
