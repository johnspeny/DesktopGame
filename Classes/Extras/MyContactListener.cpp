#include "MyContactListener.h"

MyContactListener::MyContactListener(): _contacts()
{
	numFootContacts = 0;
}

MyContactListener::~MyContactListener()
{
}

void MyContactListener::BeginContact(b2Contact* contact)
{
	// copy out the data because b2Contact passed in is resued
	ContactData Contact = { contact->GetFixtureA(), contact->GetFixtureB() };
	_contacts.push_back(Contact);


	// fixture collision detection
	int fixtureUserData = Contact.fixtureA->GetUserData().pointer;
	int fixtureUserData2 = Contact.fixtureB->GetUserData().pointer;
	int* p = &fixtureUserData;
	if (*p == 3)
	{
		numFootContacts++;
	}

	p = &fixtureUserData2;
	if (*p == 3)
	{
		numFootContacts++;
	}

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



	//fixture data

	// fixture collision detection
	int fixtureUserData = Contact.fixtureA->GetUserData().pointer;
	int fixtureUserData2 = Contact.fixtureB->GetUserData().pointer;
	int* p = &fixtureUserData;
	if (*p == 3)
	{
		numFootContacts--;
	}

	p = &fixtureUserData2;
	if (*p == 3)
	{
		numFootContacts--;
	}

	
}

void MyContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
}

void MyContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
}
