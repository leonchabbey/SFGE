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
#include <p2body.h>

p2Body::p2Body(const p2BodyDef * def)
{
	m_Type = def->type;
	m_Transform = p2Transform(def->position);
	m_LinearVelocity = def->linearVelocity;
	m_AngularVelocity = def->angularVelocity;
	m_GravityScale = def->gravityScale;
	m_Mass = def->mass;
}

p2Fixture * p2Body::CreateFixture(const p2FixtureDef * def)
{
	p2Fixture* fixture = new p2Fixture(this, def);
	m_FixtureList.push_back(fixture);
	return fixture;
}

void p2Body::AddForce(const p2Vec2 & velocity)
{
	m_LinearVelocity += velocity;
}

void p2Body::SetLinearVelocity(const p2Vec2 & velocity)
{
	m_LinearVelocity = velocity;
}

void p2Body::SetAngularVelocity(const float & angVelocity)
{
	m_AngularVelocity = angVelocity;
}

float p2Body::GetAngularVelocity() const
{
	return m_AngularVelocity;
}

const p2Vec2 & p2Body::GetLinearVelocity() const
{
	return m_LinearVelocity;
}

const p2Transform & p2Body::GetTransform() const
{
	return m_Transform;
}

void p2Body::GetFatAABB(p2AABB * aabb) const
{
	for (auto it = m_FixtureList.begin(); it != m_FixtureList.end(); it++) {
		p2Fixture* fixture = (*it);
		
		p2AABB fixAabb;
		p2Body* fixBody = fixture->GetBody();
		p2Transform fixTransform = fixBody->GetTransform();
		fixture->GetShape()->ComputeAABB(&fixAabb, &fixTransform);

		if (fixAabb.bottomLeft.x < aabb->bottomLeft.x) {
			aabb->bottomLeft.x = fixAabb.bottomLeft.x;
		}
		if (fixAabb.bottomLeft.y < aabb->bottomLeft.y) {
			aabb->bottomLeft.y = fixAabb.bottomLeft.y;
		}
		if (fixAabb.topRight.x > aabb->topRight.x) {
			aabb->topRight.x = fixAabb.topRight.x;
		}
		if (fixAabb.topRight.y > aabb->topRight.y) {
			aabb->topRight.y = fixAabb.topRight.y;
		}
	}
}

p2Body::~p2Body()
{
}
