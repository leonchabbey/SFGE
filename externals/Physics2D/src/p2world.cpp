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
	p2AABB quadAabb;
	quadAabb.bottomLeft = p2Vec2(-screenSize.x / 2, -screenSize.y / 2);
	quadAabb.topRight = p2Vec2(screenSize.x / 2, screenSize.y / 2);
	m_Quadtree = new p2QuadTree(quadAabb);
}

p2World::~p2World()
{
	for (p2Body* body : m_BodyList) {
		delete(body);
	}
	m_BodyList.clear();
}

float test = 1;

void p2World::Step(const float& dt)
{ 
	m_Quadtree->Clear();

	for (p2Body* body : m_BodyList) {
		/*if (test == 1) {
			body->AddForce(p2Vec2(1, 1));
		}*/
		
		p2Vec2 awd = body->GetLinearVelocity();
		body->SetTransform(body->GetTransform().pos + awd * dt, 0);

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

		m_Quadtree->Insert(body);
	}

	test++;
	std::list<std::pair<p2Body*, p2Body*>> aabbContacts;
	m_Quadtree->Retrieve(&aabbContacts);
	m_Quadtree->Update();
	std::cout << "AabbContacts: " << aabbContacts.size() << "\n";
}

void p2World::Debug(sf::RenderWindow & window)
{
	m_Quadtree->Draw(window);
}

p2Body * p2World::CreateBody(const p2BodyDef& bodyDef)
{
	p2Body* body = new p2Body(&bodyDef);
	m_BodyList.push_back(body);
	return body;
}

void p2World::SetContactListener(p2ContactListener * contactListener)
{
}
