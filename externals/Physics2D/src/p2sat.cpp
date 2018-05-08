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

#include <p2sat.h>
#include <iostream>

void p2SAT::EvaluateSAT()
{
	p2Shape::Type shapeTypeA = fixtureA->GetShape()->GetType();
	p2Shape::Type shapeTypeB = fixtureB->GetShape()->GetType();

	switch (shapeTypeA) {
	case p2Shape::Type::POLYGON: {
		if (shapeTypeB == p2Shape::Type::CIRCLE)
			PolygonvsCircle();
		else
			PolygonvsPolygon();
		break;
	}
	case p2Shape::Type::CIRCLE: {
		if (shapeTypeB == p2Shape::Type::POLYGON)
			CirclevsPolygon();
		else
			CirclevsCircle();
		break;
	}
	}
}

void p2SAT::CirclevsCircle()
{
	p2Body* bodyA = fixtureA->GetBody();
	p2Body* bodyB = fixtureB->GetBody();
	p2CircleShape* circleA = static_cast<p2CircleShape*>(fixtureA->GetShape());
	p2CircleShape* circleB = static_cast<p2CircleShape*>(fixtureB->GetShape());

	p2Vec2 normal = bodyB->GetPosition() - bodyA->GetPosition();
	float disanceSqr = normal.GetMagnitudeSquared();
	float radius = circleA->GetRadius() + circleB->GetRadius();

	if (disanceSqr < radius * radius) {
		areOverlapping = true;
		return;
	}
		
	areOverlapping = false;
}

void p2SAT::CirclevsPolygon()
{
	p2CircleShape* shapeA = static_cast<p2CircleShape*>(fixtureA->GetShape());
	p2PolygonShape* shapeB = static_cast<p2PolygonShape*>(fixtureB->GetShape());

	// Vertices in world space
	p2Vec2 verticesB[MAX_POLYGON_VERTICES];
	RotateAndWorldSpaceVertices(shapeB, fixtureB->GetBody(), verticesB);

	float radius = shapeA->GetRadius();
	float radiusSqr = radius * radius;

	p2Vec2 circleCenter = fixtureA->GetBody()->GetPosition();

	p2Vec2 closestDistanceVector;

	// Get all polygon's axis
	int numOfAxis = shapeB->m_VerticesCount;
	p2Vec2 axes[MAX_POLYGON_VERTICES];
	GetAxis(shapeB, verticesB, axes);

	for (int i = 0; i < shapeB->m_VerticesCount; i++) {
		p2Vec2 v1 = verticesB[i];
		int i2 = i + 1 < shapeB->m_VerticesCount ? i + 1 : 0;
		p2Vec2 v2 = shapeB->m_Vertices[i2];

		p2Vec2 normal = circleCenter - v1;

		bool distance = normal.GetMagnitudeSquared() - radiusSqr;

		if (normal.GetMagnitudeSquared() < closestDistanceVector.GetMagnitudeSquared()) {
			closestDistanceVector = normal;
		}
		else if (i == 0) {
			closestDistanceVector = normal;
		}
	}

	axes[numOfAxis] = closestDistanceVector;
	numOfAxis++;

	for (int i = 0; i < numOfAxis; i++) {
		p2Vec2 axis = axes[i];

		p2Projection circleProj;
		ProjectOnAxisCircle(circleProj, axis, circleCenter, radius);
		p2Projection polyproj;
		ProjectOnAxis(polyproj, axis, shapeB->m_VerticesCount, verticesB);

		if (!circleProj.Overlap(polyproj)) {
			areOverlapping = false;
			return;
		}
	}

	areOverlapping = true;
}

void p2SAT::PolygonvsPolygon()
{
	p2PolygonShape* shapeA = static_cast<p2PolygonShape*>(fixtureA->GetShape());
	p2PolygonShape* shapeB = static_cast<p2PolygonShape*>(fixtureB->GetShape());

	// Get the world point of vertices with rotation
	p2Vec2 verticesA[MAX_POLYGON_VERTICES];
	RotateAndWorldSpaceVertices(shapeA, fixtureA->GetBody(), verticesA);
	p2Vec2 verticesB[MAX_POLYGON_VERTICES];
	RotateAndWorldSpaceVertices(shapeB, fixtureB->GetBody(), verticesB);

	// Get projection axis for both shapes
	p2Vec2 axisA[MAX_POLYGON_VERTICES];
	GetAxis(shapeA, verticesA, axisA);
	p2Vec2 axisB[MAX_POLYGON_VERTICES];
	GetAxis(shapeB, verticesB, axisB);

	for (int i = 0; i < shapeA->m_VerticesCount; i++) {
		p2Vec2 axis = axisA[i];

		p2Projection projA;
		ProjectOnAxis(projA, axis, shapeA->m_VerticesCount, verticesA);
		p2Projection projB;
		ProjectOnAxis(projB, axis, shapeB->m_VerticesCount, verticesB);

		if (!projA.Overlap(projB)) {
			areOverlapping = false;
			return;
		}
	}

	for (int i = 0; i < shapeB->m_VerticesCount; i++) {
		p2Vec2 axis = axisB[i];

		p2Projection projA;
		ProjectOnAxis(projA, axis, shapeA->m_VerticesCount, verticesA);
		p2Projection projB;
		ProjectOnAxis(projB, axis, shapeB->m_VerticesCount, verticesB);

		if (!projA.Overlap(projB)) {
			areOverlapping = false;
			return;
		}
	}

	areOverlapping = true;
}

void p2SAT::PolygonvsCircle()
{
	// Switch fixtures
	p2Fixture* tempFixture = fixtureA;
	fixtureA = fixtureB;
	fixtureB = tempFixture;
	CirclevsPolygon();
}

bool IsPolygonCounterClockwise(p2PolygonShape * s)
{
	float numOfVertices = s->m_VerticesCount;
	float total = 0.0f;
	for (int i = 0; i < numOfVertices; i++) {
		p2Vec2 v1 = s->m_Vertices[i];
		int i2 = i + 1 < numOfVertices ? i + 1 : 0;
		p2Vec2 v2 = s->m_Vertices[i2];

		total += (v2.x - v1.x) * (v2.y + v1.y);
	}

	return total < 0;
}

void GetAxis(p2PolygonShape * s, p2Vec2(&vertices)[MAX_POLYGON_VERTICES], p2Vec2(&axis)[MAX_POLYGON_VERTICES])
{
	bool counterclock = IsPolygonCounterClockwise(s);
	for (int i = 0; i < s->m_VerticesCount; i++) {
		p2Vec2 v1 = s->m_Vertices[i];
		int i2 = i + 1 < s->m_VerticesCount ? i + 1 : 0;
		p2Vec2 v2 = s->m_Vertices[i2];

		p2Vec2 edge = v2 - v1;
		p2Vec2 normal = counterclock ? p2Vec2(edge.y, -edge.x) : p2Vec2(-edge.y, edge.x);
		normal.Normalize();
		axis[i] = normal;
	}
}

void ProjectOnAxis(p2Projection & proj, const p2Vec2 & axis, int verticesCount, p2Vec2 (&vertices)[MAX_POLYGON_VERTICES])
{
	float min = p2Vec2::Dot(axis, vertices[0]);
	float max = min;

	for (int i = 0; i < verticesCount; i++) {
		float dot = p2Vec2::Dot(axis, vertices[i]);
		if (dot < min) {
			min = dot;
		}
		if (dot > max) {
			max = dot;
		}
	}

	proj.max = max;
	proj.min = min;
}

void ProjectOnAxisCircle(p2Projection & proj, const p2Vec2 & axis, const p2Vec2& center, float radius)
{
	float dot = p2Vec2::Dot(axis, center);
	proj.max = dot + radius;
	proj.min = dot - radius;
}

void RotateAndWorldSpaceVertices(p2PolygonShape * s, p2Body * b, p2Vec2(&v)[MAX_POLYGON_VERTICES])
{
	p2Transform bTr = b->GetTransform();
	for (int i = 0; i < s->m_VerticesCount; i++) {
		p2Vec2 v1 = s->m_Vertices[i];
		v1 = bTr.matrix * v1 + bTr.pos;
		v[i] = v1;
	}
}

bool p2Projection::Overlap(p2Projection & b)
{
	return !(min > b.max || b.min > max);
}
