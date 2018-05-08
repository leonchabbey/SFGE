#include "..\include\p2math.h"

#define _USE_MATH_DEFINES
#include <math.h>

p2Transform::p2Transform(const p2Vec2 & pos) : pos(pos)
{
	SetRotation(0.0f);
}
// By default this constructor assumes that the angle is given in degrees by default
p2Transform::p2Transform(const p2Vec2 & pos, const float & rot) : pos(pos)
{
	SetRotationInDegrees(rot);
}

void p2Transform::SetRotation(float rot)
{
	eulerAngle = rot;
	matrix = p2Mat22::Rotate(rot);
	matrix.Show();
}

void p2Transform::SetRotationInDegrees(float rot)
{
	float angle = DegToRad(rot);
	SetRotation(angle);
}

float p2Transform::GetRotation() const
{
	return eulerAngle;
}

float p2Transform::GetRotationInDegrees() const
{
	return RadToDeg(eulerAngle);
}

float DegToRad(float d)
{
	return d * M_PI / 180.0f;
}

float RadToDeg(float r)
{
	return r * 180.0f / M_PI;
}

void p2Manifold::ResolveCollision()
{
	if (contact_count <= 0) {
		return;
	}

	float massA = bodyA->GetMass();
	float massB = bodyB->GetMass();
	p2Vec2 velocityA = bodyA->GetLinearVelocity();
	p2Vec2 velocityB = bodyB->GetLinearVelocity();

	p2Vec2 newVelocityA = velocityA * ((massA - massB) / (massA + massB)) + velocityB * ((2.0f * massB) / (massA + massB));
	p2Vec2 newVelocityB = velocityA * ((2.0f * massA) / (massA + massB)) + velocityB * ((massA - massB) / (massA + massB));


	bodyA->SetLinearVelocity(newVelocityA);
	bodyB->SetLinearVelocity(newVelocityB);
}
