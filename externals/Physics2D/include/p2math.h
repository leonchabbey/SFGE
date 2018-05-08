#ifndef SFGE_P2MATH_H
#define SFGE_P2MATH_H

#include <p2matrix.h>
#include <p2body.h>
class p2Body;

/*
* \brief Transform class for physics2d
*/
struct p2Transform
{
	p2Transform() {}
	p2Transform(const p2Vec2& pos);
	p2Transform(const p2Vec2& pos, const float& rot);

	void SetRotation(float rot);
	void SetRotationInDegrees(float rot);
	float GetRotation() const;
	float GetRotationInDegrees() const;

	p2Vec2 pos;
	float eulerAngle; // in radians
	p2Mat22 matrix;
};

float DegToRad(float d);
float RadToDeg(float r);

struct p2Manifold
{
	p2Body* bodyA;
	p2Body* bodyB;
	float penetration;
	p2Vec2 contacts[2]; // Max two contact points
	float contact_count = 0;
	p2Vec2 normal;

	void ResolveCollision();
};

#endif // !SFGE_P2MATH_H
