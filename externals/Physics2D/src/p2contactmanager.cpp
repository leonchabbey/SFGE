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

#include <p2contactmanager.h>

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

bool p2ContactManager::IsContactExisting(p2Fixture* fA, p2Fixture* fB)
{
	for (auto contactItr = m_ContactsList.begin(); contactItr != m_ContactsList.end(); contactItr++) {
		p2Contact* c = *contactItr;

		if ((fA == c->GetFixtureA() || fA == c->GetFixtureB())
			&& (fB == c->GetFixtureA() || fB == c->GetFixtureB()))
		{
			return true;
		}
	}
	return false;
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
				if (!IsContactExisting(fA, fB)) {
					p2Contact* newContact = new p2Contact(fA, fB);
					m_ContactsList.push_back(newContact);
				}
			}
		}
	}

	m_QuadTree->Update(); // Debug
	std::cout << "AabbContacts: " << aabbContacts.size() << "\n";
	//Collide();
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
