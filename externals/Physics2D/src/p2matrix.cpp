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
#include <math.h>
#include <p2matrix.h>

#define MATRIX_22_SIZE 2
#define MATRIX_33_SIZE 3

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

p2Mat22 & p2Mat22::operator+=(p2Mat22 m2)
{
	for (int i = 0; i < MATRIX_22_SIZE; i++) {
		this->columns[i] += m2.columns[i];
	}
	return *this;
}

p2Mat22 & p2Mat22::operator-=(p2Mat22 m2)
{
	for (int i = 0; i < MATRIX_22_SIZE; i++) {
		this->columns[i] -= m2.columns[i];
	}
	return *this;
}

p2Mat22 & p2Mat22::operator*=(p2Mat22 m2)
{
	p2Mat22 mTemp;

	for (int u = 0; u < MATRIX_22_SIZE; u++) {
		for (int i = 0; i < MATRIX_22_SIZE; i++) {
			float newVal = 0.0f;

			for (int j = 0; j < MATRIX_22_SIZE; j++) {
				newVal += this->columns[j][i] * m2.columns[u][j];
			}

			mTemp.columns[u][i] = newVal;
		}
	}
    
	for (int i = 0; i < MATRIX_22_SIZE; i++) {
		this->columns[i] = mTemp.columns[i];
	}

    return *this;
}

p2Mat22 & p2Mat22::operator*=(float f)
{
	for (int i = 0; i < MATRIX_22_SIZE; i++) {
		this->columns[i] *= f;
	}
    return *this;
}

p2Mat22 p2Mat22::operator+(p2Mat22 m2)
{
    p2Mat22 copy = *this;
    copy += m2;
	return copy;
}

p2Mat22 p2Mat22::operator-(p2Mat22 m2)
{
    p2Mat22 copy = *this;
    copy -= m2;
    return copy;
}

p2Mat22 p2Mat22::operator*(p2Mat22 m2)
{
    p2Mat22 copy = *this;
    copy *= m2;
    return copy;
}

p2Vec2 p2Mat22::operator*(p2Vec2 v)
{
	v.x = this->columns[0].x * v.x + this->columns[1].x * v.y;
	v.y = this->columns[0].y * v.x + this->columns[1].y * v.y;
	return v;
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

p2Mat22 p2Mat22::GetTranspose()
{
	return p2Mat22(
		p2Vec2(columns[0][0], columns[1][0]),
		p2Vec2(columns[0][1], columns[1][1])
	);
}

p2Mat22 p2Mat22::Rotate(float angle)
{
	return p2Mat22(
		p2Vec2(cos(angle), sin(angle)),
		p2Vec2(-sin(angle), cos(angle))
	);;
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
	for (int i = 0; i < MATRIX_33_SIZE; i++) {
		this->columns[i] += m2.columns[i];
	}
	return *this;
}

p2Mat33& p2Mat33::operator-=(p2Mat33 m2)
{
	for (int i = 0; i < MATRIX_33_SIZE; i++) {
		this->columns[i] -= m2.columns[i];
	}
	return *this;
}

p2Mat33& p2Mat33::operator*=(p2Mat33 m2)
{
	p2Mat33 newM;

	for (int u = 0; u < MATRIX_33_SIZE; u++) {
		for (int i = 0; i < MATRIX_33_SIZE; i++) {
			float newVal = 0.0f;

			for (int j = 0; j < MATRIX_33_SIZE; j++) {
				newVal += this->columns[j][i] * m2.columns[u][j];
			}

			newM.columns[u][i] = newVal;
		}
	}

	for (int i = 0; i < MATRIX_33_SIZE; i++) {
		this->columns[i] = newM.columns[i];
	}

	return *this;
}

p2Mat33 & p2Mat33::operator*=(float f)
{
	for (int i = 0; i < MATRIX_33_SIZE; i++) {
		this->columns[i] *= f;
	}
	return *this;
}

p2Mat33 p2Mat33::operator+(p2Mat33 m2)
{
	p2Mat33 copy = *this;
	copy += m2;
	return copy;
}

p2Mat33 p2Mat33::operator-(p2Mat33 m2)
{
	p2Mat33 copy = *this;
	copy -= m2;
	return copy;
}

p2Mat33 p2Mat33::operator*(p2Mat33 m2)
{
	p2Mat33 copy = *this;
	copy *= m2;
	return copy;
}

p2Mat33 p2Mat33::operator*(float f)
{
	p2Mat33 copy = *this;
	copy *= f;
	return copy;
}

p2Mat33 p2Mat33::Invert()
{
	p2Mat33 tmpM;

	// Calculate submatrix22
	for (int i = 0; i < MATRIX_33_SIZE; i++) {
		for (int j = 0; j < MATRIX_33_SIZE; j++) {
			p2Mat22 subM22;
			int numOfUsedNum = 0;
			for (int k = 0; k < MATRIX_33_SIZE; k++) {
				for (int l = 0; l < MATRIX_33_SIZE; l++) {
					if (k != i && l != j) {
						switch (numOfUsedNum) {
						case 0:
							subM22.columns[0][0] = this->columns[k][l];
						case 1:
							subM22.columns[0][1] = this->columns[k][l];
						case 2:
							subM22.columns[1][0] = this->columns[k][l];
						case 3:
							subM22.columns[1][1] = this->columns[k][l];
						}
						numOfUsedNum++;
					}
				}
			}

			tmpM.columns[i][j] = subM22.GetDeterminant();
		}
	}

	// Minus
	tmpM.columns[0][1] *= -1;
	tmpM.columns[1][0] *= -1;
	tmpM.columns[1][2] *= -1;
	tmpM.columns[2][1] *= -1;

	// Transpose
	for (int i = 0; i < MATRIX_33_SIZE; i++) {
		for (int j = 0; j < MATRIX_33_SIZE; j++) {
			if (i != j && i < j) {
				float tmpVal = tmpM.columns[i][j];
				tmpM.columns[i][j] = tmpM.columns[j][i];
				tmpM.columns[j][i] = tmpVal;
			}
		}
	}

	std::cout << "Determinant: " << this->GetDeterminant() << "\n";
	tmpM.Show();

	return tmpM * (1.0f / this->GetDeterminant());
}

float p2Mat33::GetDeterminant()
{
	float det = 0.0f;
	int maxRange = MATRIX_33_SIZE - 1;

	for (int i = 0; i < MATRIX_33_SIZE; i++) {
		float posTmp = 1.0f;
		float negTmp = 1.0f;

		for (int j = 0; j < MATRIX_33_SIZE; j++) {
			int idx = i + j;

			if (idx > maxRange)
				idx -= MATRIX_33_SIZE;

			posTmp *= this->columns[idx][j];
			negTmp *= this->columns[idx][maxRange - j];
		}

		det += posTmp - negTmp;
	}
	return det;
}

void p2Mat33::Show() {
	std::cout << "Matrix3x3:" << "\n";
	std::cout << "| " << this->columns[0].x << " " << this->columns[1].x << " " << this->columns[2].x << " |\n";
	std::cout << "| " << this->columns[0].y << " " << this->columns[1].y << " " << this->columns[2].y << " |\n";
	std::cout << "| " << this->columns[0].z << " " << this->columns[1].z << " " << this->columns[2].z << " |\n";
}
