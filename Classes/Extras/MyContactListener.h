#ifndef __MY_CONTACTLISTENER_H__
#define __MY_CONTACTLISTENER_H__

#include "cocos2d.h"
#include "box2d/box2d.h"
#include "b2WorldNode.h"
#include <vector>
#include "GameVars.h"

struct ContactData
{
	b2Fixture* fixtureA;
	b2Fixture* fixtureB;
	bool operator==(const ContactData& other) const {
		return (fixtureA == other.fixtureA) && (fixtureB == other.fixtureB);
	}

};

class MyContactListener : public b2ContactListener {

public:
	MyContactListener();
	~MyContactListener();

	std::vector<ContactData> _contacts;

	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

};

#endif // !__MY_CONTACTLISTENER_H__
