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

#ifndef SFGE_P2SHAPE_H
#define SFGE_P2SHAPE_H

#include <vector>
#include <p2vector.h>
#include <p2aabb.h>
#include <p2math.h>

#define MAX_POLYGON_VERTICES 20

class p2Body;

/**
* \brief Abstract representation of a shape
*/
class p2Shape
{
public:
	enum Type {
		CIRCLE,
		POLYGON
	};

	Type GetType() const;

	void Initialize(p2Body* b);

	virtual void ComputeMass(p2Body* body) const = 0;
	virtual void ComputeAABB(p2AABB* aabb, p2Transform* tr) const = 0;

protected:
	Type m_Type;
	p2Vec2 m_Center; // Default 0,0
};

/**
* \brief Representation of a physics circle
*/
class p2CircleShape : public p2Shape
{
public:
	p2CircleShape() { m_Type = p2Shape::Type::CIRCLE; };
	/**
	* \brief Setter for the radius
	*/
	void SetRadius(float radius);
	float GetRadius() const;

	void ComputeMass(p2Body* body) const;
	void ComputeAABB(p2AABB* aabb, p2Transform* tr) const;
private:
	float m_Radius;
};

/** 
* \brief Representation of a rectangle
*/
class p2PolygonShape : public p2Shape
{
public:
	p2PolygonShape() { m_Type = p2Shape::Type::POLYGON; };

	// Create a polygon with multiple points
	void Set(const std::vector<p2Vec2>& vertices);

	// Create a polygon as a box (rectangle / square)
	void SetAsBox(float hx, float hy);

	void ComputeMass(p2Body* body) const;
	void ComputeAABB(p2AABB* aabb, p2Transform* tr) const;

	/*
	* \brief Get the farthest point along a direction within the polygon
	*/
	p2Vec2 GetSupport(const p2Vec2& dir);

	p2Vec2 m_Vertices[MAX_POLYGON_VERTICES];
	p2Vec2 m_Normals[MAX_POLYGON_VERTICES];
	int m_VerticesCount;
};

#endif