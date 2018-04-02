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

#include <p2vector.h>
#include <iostream>
#include <cmath>


// Constructors

p2Vec2::p2Vec2()
{
}

p2Vec2::p2Vec2(float x, float y): x(x), y(y)
{
}

// Operators overloading

p2Vec2& p2Vec2::operator=(p2Vec2& v)
{
	if (this == &v)
		return *this;

	this->x = v.x;
	this->y = v.y;
	return *this;
}

p2Vec2& p2Vec2::operator+=(p2Vec2& v)
{
	this->x += v.x;
	this->y += v.y;
	return *this;
}

p2Vec2& p2Vec2::operator-=(p2Vec2& v)
{
	this->x -= v.x;
	this->y -= v.y;
	return *this;
}

p2Vec2& p2Vec2::operator/=(float f)
{
	this->x /= f;
	this->y /= f;
	return *this;
}

p2Vec2& p2Vec2::operator*=(float f)
{
	this->x *= f;
	this->y *= f;
	return *this;
}

p2Vec2 p2Vec2::operator+(p2Vec2& v)
{
	p2Vec2 copy = *this;
	copy += v;
	return copy;
}

p2Vec2 p2Vec2::operator-(p2Vec2& v)
{
	p2Vec2 copy = *this;
	copy -= v;
	return copy;
}

p2Vec2 p2Vec2::operator*(float f)
{
	p2Vec2 copy = *this;
	copy *= f;
	return copy;
}

p2Vec2 p2Vec2::operator/(float f)
{
	p2Vec2 copy = *this;
	copy /= f;
	return copy;
}

// Functions

float p2Vec2::GetMagnitude()
{
	return sqrt(x*x + y*y);
}

p2Vec2 p2Vec2::Normalized()
{
	p2Vec2 copy = *this;
	return copy /= GetMagnitude();
}

void p2Vec2::Normalize()
{
	float m = GetMagnitude();
	this->operator/=(m);
}

p2Vec3 p2Vec2::to3()
{
	return p2Vec3(x, y, 0.0f);
}

void p2Vec2::Show()
{
	std::cout << "{x: " << x << ", y: " << y << "}" << "\n";
}

// Static functions

float p2Vec2::Dot(p2Vec2 v1, p2Vec2 v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

p2Vec3 p2Vec2::Cross(p2Vec2 v1, p2Vec2 v2)
{
	return p2Vec3(
		v1.y * 0.0f - 0.0f * v2.y,
		0.0f * v2.x - v1.x * 0.0f,
		v1.x * v2.y - v1.y * v2.x
	);
}



/////////////////////////////////////////////////////
////////////////////// VECTOR3 //////////////////////
/////////////////////////////////////////////////////

// Constructors

p2Vec3::p2Vec3()
{
}

p2Vec3::p2Vec3(float x, float y, float z): x(x), y(y), z(z)
{
}

// Operators overloading

p2Vec3 & p2Vec3::operator=(p2Vec3 & v)
{
	if (this == &v)
		return *this;

	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	return *this;
}

p2Vec3 & p2Vec3::operator+=(p2Vec3 & v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	return *this;
}

p2Vec3 & p2Vec3::operator-=(p2Vec3 & v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	return *this;
}

p2Vec3 & p2Vec3::operator*=(float f)
{
	this->x *= f;
	this->y *= f;
	this->z *= f;
	return *this;
}

p2Vec3 & p2Vec3::operator/=(float f)
{
	this->x /= f;
	this->y /= f;
	this->z /= f;
	return *this;
}

p2Vec3 p2Vec3::operator+(p2Vec3 & v)
{
	p2Vec3 copy = *this;
	copy += v;
	return copy;
}

p2Vec3 p2Vec3::operator-(p2Vec3 & v)
{
	p2Vec3 copy = *this;
	copy -= v;
	return copy;
}

p2Vec3 p2Vec3::operator/(float f)
{
	p2Vec3 copy = *this;
	copy /= f;
	return copy;
}

p2Vec3 p2Vec3::operator*(float f)
{
	p2Vec3 copy = *this;
	copy *= f;
	return copy;
}

// Functions

float p2Vec3::GetMagnitude()
{
	return sqrt(x*x + y*y + z*z);
}

p2Vec3 p2Vec3::Normalized()
{
	p2Vec3 copy = *this;
	return copy /= GetMagnitude();
}

void p2Vec3::Normalize()
{
	float m = GetMagnitude();
	this->operator/=(m);
}

void p2Vec3::Show()
{
	std::cout << "{x: " << x << ", y: " << y << ", z: " << z << "}" << "\n";
}

// Static functions

float p2Vec3::Dot(p2Vec3& v1, p2Vec3& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

p2Vec3 p2Vec3::Cross(p2Vec3& v1, p2Vec3& v2)
{
	return p2Vec3(
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x
	);
}

p2Vec3 p2Vec3::Lerp(p2Vec3 & v1, p2Vec3 & v2, float ratio)
{
	p2Vec3 dir = v1 - v2;
	p2Vec3 step = dir * ratio;
	return v1 + step;
}

p2Vec3 p2Vec3::Proj(p2Vec3 & v1, p2Vec3 & v2)
{
	float dot = p2Vec3::Dot(v1, v2);
	return v1 * (dot / v1.GetMagnitude());
}

p2Vec3 p2Vec3::Refl(p2Vec3 & inDir, p2Vec3 & normal)
{
	return inDir.Normalized() - normal.Normalized() * 2 * p2Vec3::Dot(inDir.Normalized(), normal.Normalized());
}

float p2Vec3::AnglesBetween(p2Vec3 & v1, p2Vec3 & v2)
{
	float angle = p2Vec3::Dot(v1, v2) / (v1.GetMagnitude() * v2.GetMagnitude());
	return acos(angle);
}

