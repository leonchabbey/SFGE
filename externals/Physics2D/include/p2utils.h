#ifndef SFGE_P2UTILS_H

#include <p2vector.h>

/*
* \brief Transform class for physics2d
*/
struct p2Transform
{
	p2Transform() {}
	p2Transform(const p2Vec2& pos, const float& rot);

	p2Vec2 pos;
	float eulerAngle;
};

#endif // !SFGE_P2UTILS_H
