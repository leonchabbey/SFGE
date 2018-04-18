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

#include <iostream>
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

p2Mat22 & p2Mat22::operator+=(const p2Mat22 & m2)
{
	this->columns[0] += m2.columns[0];
	this->columns[1] += m2.columns[1];
	return *this;
}

p2Mat22 & p2Mat22::operator-=(const p2Mat22 & m2)
{
	this->columns[0] -= m2.columns[0];
	this->columns[1] -= m2.columns[1];
	return *this;
}

p2Mat22 & p2Mat22::operator*=(const p2Mat22 & m2)
{
    float x1 = this->columns[0].x * m2.columns[0].x + this->columns[1].x * m2.columns[0].y;
    float x2 = this->columns[0].x * m2.columns[1].x + this->columns[1].x * m2.columns[1].y;
    float y1 = this->columns[0].y * m2.columns[0].x + this->columns[1].y * m2.columns[0].y;
    float y2 = this->columns[0].y * m2.columns[1].x + this->columns[1].y * m2.columns[1].y;
    
    columns[0].x = x1;
    columns[0].y = y1;
    columns[1].x = x2;
    columns[1].y = y2;
    
    return *this;
}

p2Mat22 & p2Mat22::operator*=(const float & f)
{
    this->columns[0] *= f;
    this->columns[1] *= f;
    return *this;
}

p2Mat22 p2Mat22::operator+(const p2Mat22 & m2)
{
    p2Mat22 copy = *this;
    copy += m2;
	return copy;
}

p2Mat22 p2Mat22::operator-(const p2Mat22 & m2)
{
    p2Mat22 copy = *this;
    copy -= m2;
    return copy;
}

p2Mat22 p2Mat22::operator*(const p2Mat22 & m2)
{
    p2Mat22 copy = *this;
    copy *= m2;
    return copy;
}

p2Mat22 p2Mat22::operator*(float f)
{
    p2Mat22 copy = *this;
    copy *= f;
    return copy;
}

p2Mat22 p2Mat22::Invert()
{
    p2Mat22 swaped(
                 p2Vec2(columns[1].y, -columns[0].y),
                 p2Vec2(-columns[1].x, columns[0].x)
                 );
    swaped *= (1.0f / GetDeterminant());
	return swaped;
}

float p2Mat22::GetDeterminant()
{
	return columns[0].x * columns[1].y - columns[1].x * columns[0].y;
}

void p2Mat22::Show() {
    std::cout << "Matrix2x2:" << "\n";
    std::cout << "| " << this->columns[0].x << " " << this->columns[1].x << " |\n";
    std::cout << "| " << this->columns[0].y << " " << this->columns[1].y << " |\n";
}

/////////////////// MATRIX 3x3 ///////////////////

p2Mat33::p2Mat33()
{
	this->columns[0] = p2Vec3();
	this->columns[1] = p2Vec3();
	this->columns[2] = p2Vec3();
}

p2Mat33::p2Mat33(p2Vec3 c1, p2Vec3 c2, p2Vec3 c3)
{
	this->columns[0] = c1;
	this->columns[1] = c2;
	this->columns[2] = c3;
}

p2Mat33& p2Mat33::operator+=(p2Mat33 m2)
{
	this->columns[0] += m2.columns[0];
	this->columns[1] += m2.columns[1];
	this->columns[2] += m2.columns[2];
	return *this;
}

p2Mat33& p2Mat33::operator-=(p2Mat33 m2)
{
	this->columns[0] -= m2.columns[0];
	this->columns[1] -= m2.columns[1];
	this->columns[2] -= m2.columns[2];
	return *this;
}

p2Mat33& p2Mat33::operator*=(p2Mat33 m2)
{
	p2Mat33 newM;
	for (int u = 0; u < 3; u++) {
		for (int i = 0; i < 3; i++) {
			float newVal = 0.0f;

			for (int j = 0; j < 3; j++) {
				std::cout << this->columns[j][i] << " * " << m2.columns[i][j] << "\n";
				newVal += this->columns[j][i] * m2.columns[i][j];
			}

			std::cout << newVal << "\n";

			switch (i) {
			case 0:
				newM.columns[u].x = newVal;
				break;
			case 1:
				newM.columns[u].y = newVal;
				break;
			case 2:
				newM.columns[u].z = newVal;
				break;
			}
		}
	}
	

	this->columns[0] = newM.columns[0];
	this->columns[1] = newM.columns[1];
	this->columns[2] = newM.columns[2];
	return *this;
}

p2Mat33 p2Mat33::operator*(p2Mat33 m2)
{
	p2Mat33 copy = *this;
	copy *= m2;
	return copy;
}

p2Mat33 p2Mat33::operator*(float f)
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

void p2Mat33::Show() {
	std::cout << "Matrix3x3:" << "\n";
	std::cout << "| " << this->columns[0].x << " " << this->columns[1].x << " " << this->columns[2].x << " |\n";
	std::cout << "| " << this->columns[0].y << " " << this->columns[1].y << " " << this->columns[2].y << " |\n";
	std::cout << "| " << this->columns[0].z << " " << this->columns[1].z << " " << this->columns[2].z << " |\n";
}
