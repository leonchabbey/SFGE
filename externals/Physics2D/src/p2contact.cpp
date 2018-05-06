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
		Evaluate();

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

void p2Contact::Evaluate()
{
	p2Shape::Type shapeTypeA = m_FixtureA->GetShape()->GetType();
	p2Shape::Type shapeTypeB = m_FixtureB->GetShape()->GetType();

	switch (shapeTypeA) {
	case p2Shape::Type::POLYGON: {
		if (shapeTypeB == p2Shape::Type::CIRCLE)
			PolygonvsCircle(m_Manifold, m_FixtureA, m_FixtureB);
		else
			PolygonvsPolygon(m_Manifold, m_FixtureA, m_FixtureB);
		break;
	}
	case p2Shape::Type::CIRCLE: {
		if (shapeTypeB == p2Shape::Type::POLYGON)
			CirclevsPolygon(m_Manifold, m_FixtureA, m_FixtureB);
		else
			CirclevsCircle(m_Manifold, m_FixtureA, m_FixtureB);
		break;
	}
	}
}

void CirclevsCircle(p2Manifold& m, const p2Fixture* fxA, const p2Fixture* fxB)
{
	const p2Body* bodyA = fxA->GetBody();
	const p2Body* bodyB = fxB->GetBody();
	const p2Transform& tfA = bodyA->GetTransform();
	const p2Transform& tfB = bodyB->GetTransform();
	p2CircleShape* shapeA = static_cast<p2CircleShape*>(fxA->GetShape());
	p2CircleShape* shapeB = static_cast<p2CircleShape*>(fxB->GetShape());

	p2Vec2 normal = tfB.pos - tfA.pos;

	float distanceSquared = normal.GetMagnitudeSquared();
	float radius = shapeA->GetRadius() - shapeB->GetRadius();

	if (distanceSquared > radius * radius) {
		m.contact_count = 0;
		return;
	}

	float distance = sqrt(distanceSquared);

	if (distance == 0.0f) {
		m.penetration = shapeA->GetRadius();
		m.normal = p2Vec2(1.0f, 0.0f);
		m.contacts[0] = tfA.pos;
	}
	else {
		m.penetration = radius - distance;
		m.normal = normal / distance;
		m.contacts[0] = m.normal * shapeA->GetRadius() + tfA.pos;
	}
}

void CirclevsPolygon(p2Manifold& m, const p2Fixture* fxA, const p2Fixture* fxB)
{

}

void PolygonvsPolygon(p2Manifold& m, const p2Fixture* fxA, const p2Fixture* fxB)
{
}

void PolygonvsCircle(p2Manifold& m, const p2Fixture* fxA, const p2Fixture* fxB)
{
	CirclevsPolygon(m, fxB, fxA);
	m.normal = m.normal * -1; // inverse normal
}
