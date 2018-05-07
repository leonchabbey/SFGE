#ifndef SFGE_P2MATH_H
#define SFGE_P2MATH_H

#include <p2vector.h>
#include <p2matrix.h>

class p2Body;

/*
* \brief Transform class for physics2d
*/
struct p2Transform
{
	p2Transform() {}
	p2Transform(const p2Vec2& pos);
	p2Transform(const p2Vec2& pos, const float& rot);

	p2Vec2 pos;
	float eulerAngle; // in radians
};

struct p2Manifold
{
	p2Body* bodyA;
	p2Body* bodyB;
	float penetration;
	p2Vec2 contacts[2]; // Max two contact points
	float contact_count = 0;
	p2Vec2 normal;
};

inline p2Vec2 p2ApplyRotation(const p2Transform& tr, const p2Vec2& v)
{
	return p2Mat22::Rotate(tr.eulerAngle) * v + tr.pos;
}

#endif // !SFGE_P2MATH_H
