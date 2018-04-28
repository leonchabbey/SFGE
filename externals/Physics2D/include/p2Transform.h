#ifndef SFGE_P2TRANSFORM_H

#include <p2vector.h>

/*
* \brief Transform class for physics2d
*/
struct p2Transform
{
	p2Transform() {}
	p2Transform(const p2Vec2& pos, const float& rot);

	void SetPosition(const p2Vec2&);
	void SetRotation(const float&);

	p2Vec2 GetPosition();
	float GetRotation();

	p2Vec2 pos;
	float eulerAngle;
};

#endif // !SFGE_P2TRANSFORM_H
