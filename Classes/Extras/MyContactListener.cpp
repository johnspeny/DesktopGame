#include "MyContactListener.h"

MyContactListener::MyContactListener(): _contacts()
{

}

MyContactListener::~MyContactListener()
{
}

void MyContactListener::BeginContact(b2Contact* contact)
{
	// copy out the data because b2Contact passed in is resued
	ContactData Contact = { contact->GetFixtureA(), contact->GetFixtureB() };
	_contacts.push_back(Contact);
}

void MyContactListener::EndContact(b2Contact* contact)
{
	ContactData Contact = { contact->GetFixtureA(), contact->GetFixtureB() };
	std::vector<ContactData>::iterator pos;
	pos = std::find(_contacts.begin(), _contacts.end(), Contact);
	if (pos != _contacts.end())
	{
		_contacts.erase(pos);
	}
}

void MyContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
}

void MyContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
}
