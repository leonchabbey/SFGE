#include "..\include\p2math.h"

p2Transform::p2Transform(const p2Vec2 & pos) : pos(pos), eulerAngle(0.0f)
{
	SetRotation(0.0f);
}

p2Transform::p2Transform(const p2Vec2 & pos, const float & rot) : pos(pos), eulerAngle(rot)
{
	SetRotation(rot);
}

void p2Transform::SetRotation(float rot)
{
	matrix = p2Mat22::Rotate(rot);
}
