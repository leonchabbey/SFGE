/*
MIT License

Copyright (c) 2017 SAE Institute Switzerland AG

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <p2contact.h>

p2Contact::p2Contact(p2Fixture* fxA, p2Fixture* fxB) : m_FixtureA(fxA), m_FixtureB(fxB)
{
	m_Manifold.bodyA = m_FixtureA->GetBody();
	m_Manifold.bodyB = m_FixtureB->GetBody();
}

void p2Contact::Update(p2ContactListener* listener)
{
	p2Manifold prev_Manifold = m_Manifold;

	bool isTouching = false;
	bool wasTouching = m_IsTouching;

	bool sensorA = m_FixtureA->IsSensor();
	bool sensorB = m_FixtureB->IsSensor();
	bool sensor = sensorA || sensorB;

	if (sensor) {

	}
	else {
		const p2Transform& tfA = m_FixtureA->GetBody()->GetTransform();
		const p2Transform& tfB = m_FixtureB->GetBody()->GetTransform();

		Evaluate(m_Manifold, tfA, tfB);
	}

	if (isTouching && !wasTouching && listener) {
		listener->BeginContact(this);
	}
	if (!isTouching && wasTouching && listener) {
		listener->EndContact(this);
	}

	m_IsTouching = isTouching;
}

p2Fixture * p2Contact::GetFixtureA() const
{
	return m_FixtureA;
}

p2Fixture * p2Contact::GetFixtureB() const
{
	return m_FixtureB;
}

bool p2Contact::IsTouching() const
{
	return m_IsTouching;
}

void p2Contact::Evaluate(p2Manifold & m, const p2Transform & tfA, const p2Transform & tfB)
{

}

p2ContactManager::p2ContactManager(const p2Vec2 & screenSize)
{
	m_QuadTree = new p2QuadTree({ p2Vec2(0.0f, screenSize.y),  p2Vec2(screenSize.x, 0.0f) });
}

p2ContactManager::~p2ContactManager()
{
	for (auto contact : m_ContactsList) {
		delete(contact);
	}
	m_ContactsList.clear();

	delete(m_QuadTree);
}

void p2ContactManager::DetectContacts(std::list<p2Body*> bodyList)
{
	m_QuadTree->Clear();

	for (auto b : bodyList) {
		m_QuadTree->Insert(b);
	}

	std::list<std::pair<p2Body*, p2Body*>> aabbContacts;
	m_QuadTree->Retrieve(&aabbContacts);

	// Add all possible contacts found with AABB
	for (auto contact : aabbContacts) {
		p2Body* bodyA = contact.first;
		p2Body* bodyB = contact.second;
		
		for (auto fA : bodyA->GetAttachedFixtures()) {
			for (auto fB : bodyB->GetAttachedFixtures()) {
				p2Contact* newContact = new p2Contact(fA, fB);
				m_ContactsList.push_back(newContact);
			}
		}
	}
	
	m_QuadTree->Update(); // Debug
	std::cout << "AabbContacts: " << aabbContacts.size() << "\n";
	Collide();
}

void p2ContactManager::Collide()
{
	auto contactItr = m_ContactsList.begin();
	while (contactItr != m_ContactsList.end()) {
		p2Contact* contact = *contactItr;
		
		// Remove contacts that were already not touching at last step
		if (!contact->IsTouching()) {
			contactItr = m_ContactsList.erase(contactItr);
			delete(contact);
			continue;
		}

		contact->Update(m_ContactListener);
		contactItr++;
	}
}

void p2ContactManager::Draw(sf::RenderWindow & window)
{
	m_QuadTree->Draw(window);
}
