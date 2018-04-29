#include "..\include\p2math.h"

p2Transform::p2Transform(const p2Vec2 & pos) : pos(pos), eulerAngle(0.0f)
{
}

p2Transform::p2Transform(const p2Vec2 & pos, const float & rot) : pos(pos), eulerAngle(rot)
{
}
