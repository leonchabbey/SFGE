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

#include <p2aabb.h>

p2Vec2 p2AABB::GetCenter()
{
	return (bottomLeft + topRight) * 0.5f;
}

p2Vec2 p2AABB::GetExtents()
{
	return (topRight - bottomLeft) * 0.5f;
}

bool p2AABB::Contains(p2AABB & aabb) const
{
	bool result = true;
	result = result && bottomLeft.x <= aabb.bottomLeft.x;
	result = result && bottomLeft.y <= aabb.bottomLeft.y;
	result = result && topRight.y >= aabb.topRight.y;
	result = result && topRight.y >= aabb.topRight.y;
	return result;
}
