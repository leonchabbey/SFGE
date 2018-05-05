#ifndef SFGE_P2MATH_H
#define SFGE_P2MATH_H
#include <p2vector.h>
#include <p2matrix.h>

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

inline p2Vec2 p2ApplyRotation(const p2Transform& tr, const p2Vec2& v)
{
	return p2Mat22::Rotate(v, tr.eulerAngle) + tr.pos;
}

#endif // !SFGE_P2MATH_H
