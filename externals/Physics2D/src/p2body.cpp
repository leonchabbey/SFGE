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
	m_Transform = p2Transform(def->position, def->angle);
	m_LinearVelocity = def->linearVelocity;
	m_AngularVelocity = def->angularVelocity;
	m_GravityScale = def->gravityScale;
	m_Density = def->density;
}

p2Fixture * p2Body::CreateFixture(const p2FixtureDef * def)
{
	p2Fixture* fixture = new p2Fixture(this, def);
	m_FixtureList.push_back(fixture);
	return fixture;
}

p2BodyType p2Body::GetType() const
{
	return m_Type;
}

float p2Body::GetGravityScale() const
{
	return m_GravityScale;
}

void p2Body::AddForce(const p2Vec2 & velocity)
{
	m_LinearVelocity += velocity;
}

void p2Body::SetLinearVelocity(const p2Vec2 & velocity)
{
	m_LinearVelocity = velocity;
}

const p2Vec2 & p2Body::GetLinearVelocity() const
{
	return m_LinearVelocity;
}

void p2Body::SetAngularVelocity(const float & angVelocity)
{
	m_AngularVelocity = angVelocity;
}

float p2Body::GetAngularVelocity() const
{
	return m_AngularVelocity;
}

void p2Body::SetTransform(const p2Vec2 & pos, float angle)
{
	m_Transform.pos = pos;
	m_Transform.eulerAngle = angle;
}

p2Transform & p2Body::GetTransform()
{
	return m_Transform;
}

void p2Body::SetPosition(const p2Vec2 & pos)
{
	m_Transform.pos = pos;
}

p2Vec2 p2Body::GetPosition() const
{
	return m_Transform.pos;
}

void p2Body::SetRotation(const float & f)
{
	m_Transform.SetRotation(f);
}

float p2Body::GetRotation() const
{
	return m_Transform.eulerAngle;
}

void p2Body::SetDensity(const float & d)
{
	m_Density = d;
}

float p2Body::GetDensity()
{
	return m_Density;
}

void p2Body::SetMass(const float & m)
{
	m_Mass = m;
}

float p2Body::GetMass()
{
	return m_Mass;
}

void p2Body::SetInvMass(const float & invM)
{
	m_InvMass = invM;
}

float p2Body::GetInvMass()
{
	return m_InvMass;
}

void p2Body::SetInertia(const float & i)
{
	m_Inertia = i;
}

float p2Body::GetInertia()
{
	return m_Inertia;
}

void p2Body::SetInvInertia(const float & invI)
{
	m_InvInertia = invI;
}

float p2Body::GetInvInertia()
{
	return m_InvInertia;
}

void p2Body::ApplyForce(const p2Vec2 & f)
{
	m_Force += f;
}

void p2Body::ApplyImpulse(const p2Vec2 & impulse, const p2Vec2 & contactVector)
{
	m_LinearVelocity += impulse * m_InvMass;
	m_AngularVelocity += p2Vec2::Cross(contactVector, impulse) * m_InvInertia;
}

void p2Body::GetFatAABB(p2AABB * aabb) const
{
	for (auto it = m_FixtureList.begin(); it != m_FixtureList.end(); it++) {
		p2Fixture* fixture = (*it);
		
		p2AABB fixAabb;
		p2Body* fixBody = fixture->GetBody();
		p2Transform fixTransform = fixBody->GetTransform();
		fixture->GetShape()->ComputeAABB(&fixAabb, &fixTransform);

		if (it == m_FixtureList.begin()) {
			aabb->bottomLeft = fixAabb.bottomLeft;
			aabb->topRight = fixAabb.topRight;
			continue;
		}

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

std::list<p2Fixture*> p2Body::GetAttachedFixtures() const
{
	return m_FixtureList;
}

p2Body::~p2Body()
{
}
