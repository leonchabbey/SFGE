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

#include <p2matrix.h>

p2Mat22::p2Mat22()
{
	this->columns[0] = p2Vec2();
	this->columns[1] = p2Vec2();
}

p2Mat22::p2Mat22(p2Vec2 c1, p2Vec2 c2)
{
	this->columns[0] = c1;
	this->columns[1] = c2;
}

p2Mat22 & p2Mat22::operator+=(p2Mat22 & m2)
{
	this->columns[0] += m2.columns[0];
	this->columns[1] += m2.columns[1];
	return *this;
}

p2Mat22 & p2Mat22::operator-=(p2Mat22 & m2)
{
	this->columns[0] -= m2.columns[0];
	this->columns[1] -= m2.columns[1];
	return *this;
}

p2Mat22 & p2Mat22::operator*=(p2Mat22 & m2)
{
	return p2Mat22(
		p2Vec2(
			columns[0].x * m2.columns[0].x + columns[1].x * m2.columns[0].y,
			columns[0].y * m2.columns[0].x + columns[1].y * m2.columns[0].y
		),
		p2Vec2()
	);
}

p2Mat22 & p2Mat22::operator/=(p2Mat22 & m2)
{
	// TODO: insert return statement here
}

p2Vec2 & p2Mat22::operator*=(p2Vec2 & m2)
{
	// TODO: insert return statement here
}

p2Mat22 p2Mat22::operator+(p2Mat22 & m2)
{
	return p2Mat22();
}

p2Mat22 p2Mat22::operator-(p2Mat22 & m2)
{
	return p2Mat22();
}

p2Mat22 p2Mat22::operator*(p2Mat22 & m2)
{
	return p2Mat22();
}



p2Mat22 p2Mat22::operator*(float f)
{
	return p2Mat22();
}

p2Mat22 p2Mat22::operator/(float f)
{
	return p2Mat22();
}

p2Mat22 p2Mat22::Invert()
{
	return p2Mat22();
}

float p2Mat22::GetDeterminant()
{
	return 0.0f;
}

p2Mat33::p2Mat33()
{
}

p2Mat33::p2Mat33(p2Vec3 r1, p2Vec3 r2, p2Vec3 r3)
{
}

p2Mat33 p2Mat33::operator+(p2Mat33 m2)
{
	return p2Mat33();
}

p2Mat33 p2Mat33::operator-(p2Mat33 m2)
{
	return p2Mat33();
}

p2Mat33 p2Mat33::operator*(p2Mat33 m2)
{
	return p2Mat33();
}

p2Vec3 p2Mat33::operator*(p2Vec3)
{
	return p2Vec3();
}

p2Mat33 p2Mat33::operator*(float f)
{
	return p2Mat33();
}

p2Mat33 p2Mat33::operator/(float f)
{
	return p2Mat33();
}

p2Mat33 p2Mat33::Invert()
{
	return p2Mat33();
}

float p2Mat33::GetDeterminant()
{
	return 0.0f;
}
