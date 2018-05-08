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
#include <p2sat.h>

p2Contact::p2Contact(p2Fixture* fxA, p2Fixture* fxB) : m_FixtureA(fxA), m_FixtureB(fxB)
{
	m_Manifold.bodyA = m_FixtureA->GetBody();
	m_Manifold.bodyB = m_FixtureB->GetBody();
}

void p2Contact::Update(p2ContactListener* listener)
{
	p2Manifold prev_Manifold = m_Manifold;
	m_Manifold.contact_count = 0;

	bool isTouching = false;
	bool wasTouching = m_IsTouching;

	bool sensorA = m_FixtureA->IsSensor();
	bool sensorB = m_FixtureB->IsSensor();
	bool sensor = sensorA || sensorB;

	p2SAT sat;
	sat.fixtureA = m_FixtureA;
	sat.fixtureB = m_FixtureB;

	sat.EvaluateSAT();
	isTouching = sat.areOverlapping;

	if (isTouching) {
		if (sensor) {
			m_Manifold.contact_count = 0;
		}
		else {
			/* Should use that function for real impulse based collision resolution but not working yet */
			//Evaluate()
			m_Manifold.contact_count = 1;
		}
	}
	

	std::cout << "isTouching: " << isTouching << "\n";

	if (isTouching && !wasTouching && listener) {
		listener->BeginContact(this);
	}
	if (!isTouching && wasTouching && listener) {
		listener->EndContact(this);
	}

	m_IsTouching = isTouching;
}

void p2Contact::ResolveCollision()
{
	m_Manifold.ResolveCollision();
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

/*
* From here are my attempts to make work impulse based collision and resolution
* It didn't go well...
*/

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
	p2Body* bodyA = fxA->GetBody();
	p2Body* bodyB = fxB->GetBody();
	p2Transform& tfA = bodyA->GetTransform();
	p2Transform& tfB = bodyB->GetTransform();
	p2CircleShape* shapeA = static_cast<p2CircleShape*>(fxA->GetShape());
	p2CircleShape* shapeB = static_cast<p2CircleShape*>(fxB->GetShape());
	m.contact_count = 0;

	p2Vec2 normal = tfB.pos - tfA.pos;

	float distanceSquared = normal.GetMagnitudeSquared();
	float radius = shapeA->GetRadius() + shapeB->GetRadius();

	// Distance greather than sum of radiuses then no contact
	if (distanceSquared > radius * radius) {
		m.contact_count = 0;
		return;
	}

	float distance = sqrt(distanceSquared);

	m.contact_count = 1;

	// Circles are pefectly overlapped
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
	p2Body* bodyA = fxA->GetBody();
	p2Body* bodyB = fxB->GetBody();
	p2Transform& tfA = bodyA->GetTransform();
	p2Transform& tfB = bodyB->GetTransform();
	p2CircleShape* shapeA = static_cast<p2CircleShape*>(fxA->GetShape());
	p2PolygonShape* shapeB = static_cast<p2PolygonShape*>(fxB->GetShape());
	float circleRadius = shapeA->GetRadius();
	m.contact_count = 0;

	// Center of circle in same 
	p2Vec2 center = bodyA->GetTransform().pos;
	center = bodyB->GetTransform().matrix.GetTranspose() * (center - bodyB->GetTransform().pos);

	// Find the edge with minimum penetration
	// Edge = two vertices
	float separation = -FLT_MAX;
	int faceNormalIndex = 0;
	for (int i = 0; i < shapeB->m_VerticesCount; i++) {
		float s = p2Vec2::Dot(shapeB->m_Normals[i], center - shapeB->m_Vertices[i]);

		if (s > circleRadius)
			return;

		if (s > separation) {
			separation = s;
			faceNormalIndex = i;
		}
	}

	// Now take the face vertices
	p2Vec2 v1 = shapeB->m_Vertices[faceNormalIndex];
	int index2 = faceNormalIndex + 1 < shapeB->m_VerticesCount ? faceNormalIndex + 1 : 0;
	p2Vec2 v2 = shapeB->m_Vertices[index2];

	// If the circle center is inside the polygon
	if (separation < FLT_EPSILON) {
		m.contact_count = 1;
		m.normal = (bodyB->GetTransform().matrix * shapeB->m_Normals[faceNormalIndex]) * -1;
		m.contacts[0] = m.normal * circleRadius + bodyA->GetPosition();
		m.penetration = circleRadius;
		return;
	}

	float dot1 = p2Vec2::Dot(center - v1, v2 - v1);
	float dot2 = p2Vec2::Dot(center - v2, v1 - v2);

	m.penetration = circleRadius - separation;

	if (dot1 <= 0.0f) {
		p2Vec2 distV = center - v1;
		float distanceSquared = p2Vec2::Dot(distV, distV);

		if (distanceSquared > circleRadius * circleRadius)
			return;

		m.contact_count = 1;
		p2Vec2 normal = v1 - center;
		normal = bodyB->GetTransform().matrix * normal;
		normal.Normalize();
		m.normal = normal;
		v1 = bodyB->GetTransform().matrix * v1 + bodyB->GetTransform().pos;
		m.contacts[0] = v1;
	}
	else if (dot2 <= 0.0f) {
		p2Vec2 distV = center - v2;
		float distanceSquared = p2Vec2::Dot(distV, distV);

		if (distanceSquared > circleRadius * circleRadius)
			return;

		m.contact_count = 1;
		p2Vec2 normal = v2 - center;
		normal = bodyB->GetTransform().matrix * normal;
		normal.Normalize();
		m.normal = normal;
		v2 = bodyB->GetTransform().matrix * v2 + bodyB->GetTransform().pos;
		m.contacts[0] = v2;
	}
	else {
		p2Vec2 n = shapeB->m_Normals[faceNormalIndex];

		if (p2Vec2::Dot(center - v1, n) > circleRadius)
			return;

		n = bodyB->GetTransform().matrix * n;
		n.Normalize();
		m.normal = n;
		m.contacts[0] = m.normal * circleRadius + bodyA->GetTransform().pos;
		m.contact_count = 1;
	}
}

void PolygonvsPolygon(p2Manifold& m, const p2Fixture* fxA, const p2Fixture* fxB)
{
}

void PolygonvsCircle(p2Manifold& m, const p2Fixture* fxA, const p2Fixture* fxB)
{
	CirclevsPolygon(m, fxB, fxA);
	m.normal = m.normal * -1; // inverse normal
}
