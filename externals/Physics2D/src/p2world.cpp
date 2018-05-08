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
#include <p2world.h>
#include <iostream>

p2World::p2World(const p2Vec2& screenSize, const p2Vec2& gravity): m_Gravity(gravity)
{
	m_ContactManager = new p2ContactManager(screenSize);
}

p2World::~p2World()
{
	for (p2Body* body : m_BodyList) {
		delete(body);
	}
	m_BodyList.clear();

	delete(m_ContactManager);
}

float test = 1;

void p2World::Step(const float& dt)
{ 
	// Update velocities
	for (p2Body* body : m_BodyList) {
		/*if (test == 1) {
			body->AddForce(p2Vec2(1, 1));
		}*/
		
		p2Vec2 awd = body->GetLinearVelocity();
		body->SetPosition(body->GetTransform().pos + awd * dt);

		/*p2Vec2 pos = body->GetTransform().pos;
		p2Vec2 vel = body->GetLinearVelocity();
		if ((pos.x < 0.0f && vel.x < 0.0f) || (pos.x > 12.8f && vel.x > 0.0f))
		{
			body->SetLinearVelocity({ -vel.x, vel.y});
		}
		if ((pos.y < 0.0f && vel.y < 0.0f) || (pos.y > 7.2f && vel.y > 0.0f))
		{
			body->SetLinearVelocity({ vel.x, -vel.y });
		}*/
	}

	test++;

	// Compute all contacts
	m_ContactManager->DetectContacts(m_BodyList);
}

void p2World::Debug(sf::RenderWindow & window)
{
	m_ContactManager->Draw(window);
}

p2Body * p2World::CreateBody(const p2BodyDef& bodyDef)
{
	p2Body* body = new p2Body(&bodyDef);
	m_BodyList.push_back(body);
	return body;
}

void p2World::SetContactListener(p2ContactListener * contactListener)
{
	m_ContactManager->m_ContactListener = contactListener;
}
