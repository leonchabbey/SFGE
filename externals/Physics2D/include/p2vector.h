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

#ifndef SFGE_P2VECTOR_H
#define SFGE_P2VECTOR_H

struct p2Vec3;

/**
* \brief Vector class
*/
struct p2Vec2
{
	float x = 0.0f;
	float y = 0.0f;

	p2Vec2();
	p2Vec2(float x, float y);

	/*
	* Should use const ref as arguments
	* but would need to duplicate each function
	* for a const and non-const version (const-cast
	* to avoid code duplication), and that's annoying to do.
	*/
	p2Vec2& operator=(const p2Vec2& v);
	p2Vec2& operator+=(const p2Vec2& v);
	p2Vec2& operator-=(const p2Vec2& v);
	p2Vec2& operator*=(const float& f);
	p2Vec2& operator/=(const float& f);

	p2Vec2 operator+(const p2Vec2& v) const;
	p2Vec2 operator-(const p2Vec2& v) const;
	p2Vec2 operator /(const float& f) const;
	p2Vec2 operator *(const float& f) const;

	float& operator[](const int& i);

	/**
	* \brief Calculate the magnitude of the p2Vec2
	*/
	float GetMagnitude();
	/**
	* \brief Calculate the magnitude of the p2Vec2
	*/
	float GetMagnitudeSquared();
	/**
	* \brief Calculate a normalized version of the p2Vec2
	*/
	p2Vec2 Normalized();
	/**
	* \brief Normalize the p2Vec2
	*/
	void Normalize();
	/**
	* \brief Make it a vector3
	*/
	p2Vec3 to3();
	/*
	* \brief Console log it
	*/
	void Show();

	/**
	* \brief Dot product of two vectors
	*/
	static float Dot(p2Vec2 v1, p2Vec2 v2);
	/**
	* \brief Cross product of two vectors and return a p2Vec3
	*/
	static p2Vec3 CrossTo3(p2Vec2 v1, p2Vec2 v2);
	/**
	* \brief Cross product of two vectors and return float
	*/
	static float Cross(p2Vec2 v1, p2Vec2 v2);

};

struct p2Vec3
{
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	p2Vec3();
	p2Vec3(float x, float y, float z);

	p2Vec3& operator=(const p2Vec3& v);
	p2Vec3& operator+=(const p2Vec3& v);
	p2Vec3& operator-=(const p2Vec3& v);
	p2Vec3& operator*=(const float& f);
	p2Vec3& operator/=(const float& f);

	p2Vec3 operator+(const p2Vec3& v);
	p2Vec3 operator-(const p2Vec3& v);
	p2Vec3 operator /(const float& f);
	p2Vec3 operator *(const float& f);

	float& operator[](const int& i);

	/**
	* \brief Calculate the magnitude of the p2Vec2
	*/
	float GetMagnitude();
	/**
	* \brief Calculate a normalized version of the p2Vec2
	*/
	p2Vec3 Normalized();
	/**
	* \brief Normalize the p2Vec2
	*/
	void Normalize();
	/*
	* \brief Console log it
	*/
	void Show();

	/**
	* \brief Dot product of two vectors
	*/
	static float Dot(p2Vec3 v1, p2Vec3 v2);
	/**
	* \brief Cross product of two vectors
	*/
	static p2Vec3 Cross(p2Vec3 v1, p2Vec3 v2);
	/**
	* \brief Lerp of two vectors
	*/
	static p2Vec3 Lerp(p2Vec3 v1, p2Vec3 v2, float ratio);
	/**
	* \brief Projection of two vectors
	*/
	static p2Vec3 Proj(p2Vec3 v1, p2Vec3 v2);
	/**
	* \brief Vector's reflection on a normal
	*/
	static p2Vec3 Refl(p2Vec3 inDir, p2Vec3 normal);
	/**
	* \brief Angle between vectors
	*/
	static float AnglesBetween(p2Vec3 v1, p2Vec3 v2);
};

#endif
