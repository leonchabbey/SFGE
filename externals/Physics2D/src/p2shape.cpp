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

p2Shape::Type p2Shape::GetType() const
{
	return m_Type;
}


void p2CircleShape::SetRadius(float radius)
{
}

void p2PolygonShape::Set(const p2Vec2 points, int count)
{
	// TO DO
}

void p2PolygonShape::SetAsBox(float hx, float hy)
{
	m_Count = 4;
	m_Vertices[0] = p2Vec2(-hx, -hy);
	m_Vertices[1] = p2Vec2(hx, -hy);
	m_Vertices[2] = p2Vec2(hx, hy);
	m_Vertices[3] = p2Vec2(-hx, hy);
	m_Normals[0] = p2Vec2(0.0f, -1.0f);
	m_Normals[1] = p2Vec2(1.0f, 0.0f);
	m_Normals[2] = p2Vec2(0.0f, 1.0f);
	m_Normals[3] = p2Vec2(-1.0f, 0.0f);
	m_Center = p2Vec2(0.0f, 0.0f);
}

void p2PolygonShape::ComputeAABB(p2AABB * aabb, const p2Transform * tr) const
{
	// TODO: All type of polygon AABB

	aabb->bottomLeft = m_Vertices[0];
	aabb->topRight = m_Vertices[2];
}
