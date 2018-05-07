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

#include <p2shape.h>
#include <assert.h>

#define PI 3.14159265359

p2Shape::Type p2Shape::GetType() const
{
	return m_Type;
}

void p2CircleShape::SetRadius(float radius)
{
	m_Radius = radius;
}

float p2CircleShape::GetRadius() const
{
	return m_Radius;
}

void p2CircleShape::ComputeMass(p2Body * body) const
{
	float mass = PI * m_Radius * m_Radius * body->GetDensity();
	float inertia = mass * m_Radius * m_Radius;
	body->SetMass(mass);
	body->SetInvMass(mass ? 1.0f / mass : 0.0f);
	body->SetInertia(inertia);
	body->SetInvInertia(inertia ? 1.0f / inertia : 0.0f);
}

void p2CircleShape::ComputeAABB(p2AABB * aabb, const p2Transform * tr) const
{
	p2Vec2 offset = p2Vec2(m_Radius, m_Radius);
	aabb->bottomLeft = tr->pos - offset;
	aabb->topRight = tr->pos + offset;
}

void p2PolygonShape::Set(const std::vector<p2Vec2>& vertices)
{
	assert(vertices.size() < 3 && "Polygons need to have more than 2 vertices");

	/*// Index of the farthest vertex on axis X
	int indexMostRightPoint = 0;
	float highestXCoord = vertices[0]->x;

	for (int i = 0; i < vertices.size(); i++) {
		float x = vertices[i]->x;

		if (x > highestXCoord) {
			highestXCoord = x;
			indexMostRightPoint = i;
		}
		else if (x == highestXCoord) {
			if (vertices[i]->y < vertices[indexMostRightPoint]->y) {
				indexMostRightPoint = i;
			}
		}
	}

	p2Vec2* */

	for (int i = 0; i < vertices.size(); i++) {
		auto v = vertices[i];
		m_Vertices[i] = v;

		int i2 = i + 1 < vertices.size() ? i + 1 : 0;
		p2Vec2 faceNormal = vertices[i2] - vertices[i];
		
		m_Normals[i] = faceNormal;
		m_Normals[i].Normalize();
	}
	m_VerticesCount = vertices.size();
}

void p2PolygonShape::SetAsBox(float hx, float hy)
{
	m_Vertices[0] = p2Vec2(-hx, hy); // bottomLeft
	m_Vertices[1] = p2Vec2(hx, hy); // bottomRight
	m_Vertices[2] = p2Vec2(hx, -hy); // topRight
	m_Vertices[3] = p2Vec2(-hx, -hy); // topLeft
	m_Normals[0] = p2Vec2(0.0f, 1.0f);
	m_Normals[1] = p2Vec2(1.0f, 0.0f);
	m_Normals[2] = p2Vec2(0.0f, -1.0f);
	m_Normals[3] = p2Vec2(-1.0f, 0.0f);
	m_VerticesCount = 4;
}

void p2PolygonShape::ComputeMass(p2Body * body) const
{
	// Center of the shape
	p2Vec2 centroid(0.0f, 0.0f);
	float area = 0.0f;
	float I = 0.0f;
	const float k_inv3 = 1.0f / 3.0f;

	// The idea here as I understood is to form triangles
	// from the center of the polygon to two vertices at a time
	// to compute mass and inertia and sum all of them to
	// get the total mass and inertia
	// -> This chunk of code is from the source of Box2D
	for (int i = 0; i < m_VerticesCount; i++) {
		p2Vec2 v1 = m_Vertices[i];
		int i2 = i2 + 1 < m_VerticesCount ? i + 1 : 0;
		p2Vec2 v2 = m_Vertices[i2];

		float D = p2Vec2::Cross(v1, v2);
		float triangleArea = 0.5f * D;
		area += triangleArea;

		// Use area to balance the centroid average
		centroid += (v1 + v2) * triangleArea * k_inv3;

		int intx2 = v1.x * v1.x + v2.x * v1.x + v2.x + v2.x;
		int inty2 = v1.y * v1.y + v2.y * v1.y + v2.y + v2.y;

		I += (0.25f * k_inv3 * D) * (intx2 + inty2);
	}

	centroid *= 1.0f / area;

	float density = body->GetDensity();
	float mass = density * area; // Total mass
	float inertia = I * density;
	body->SetMass(mass);
	body->SetInvMass(mass ? 1.0f / mass : 0.0f);
	body->SetInertia(inertia);
	body->SetInertia(inertia ? 1.0f / inertia : 0.0f);
}

void p2PolygonShape::ComputeAABB(p2AABB * aabb, const p2Transform * tr) const
{
	
	p2Vec2 min = p2ApplyRotation(*tr, m_Vertices[0]);
	p2Vec2 max = min;

	for (const p2Vec2& v : m_Vertices)
	{
		p2Vec2 new_V = p2ApplyRotation(*tr, v);
		if (new_V.x > max.x)
			max.x = new_V.x;
		if (new_V.y > max.y)
			max.y = new_V.y;
		if (new_V.x < min.x)
			min.x = new_V.x;
		if (new_V.y < min.y)
			min.y = new_V.y;
	}

	aabb->bottomLeft = min;
	aabb->topRight = max;
}

// Get the farthest point along a direction inside the polygon
p2Vec2 p2PolygonShape::GetSupport(const p2Vec2 & dir)
{
	float bestProjection = -FLT_MAX;
	p2Vec2 bestVertex;

	for (auto v : m_Vertices) {
		float projection = p2Vec2::Dot(v, dir);

		if (projection > bestProjection) {
			bestVertex = v;
			bestProjection = projection;
		}
	}

	return bestVertex;
}
