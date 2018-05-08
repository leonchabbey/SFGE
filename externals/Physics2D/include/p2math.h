#ifndef SFGE_P2MATH_H
#define SFGE_P2MATH_H

#include <p2matrix.h>

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

#endif // !SFGE_P2MATH_H
