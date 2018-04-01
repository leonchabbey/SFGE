#include "type/vector3.h";
#include <memory>
#include <iostream>

namespace sfge {
	Vector3::Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z)
	{
	}

	Vector3 & Vector3::operator=(Vector3 & v2)
	{
		if (this == &v2)
			return *this;

		this->x = v2.x;
		this->y = v2.y;
		this->z = v2.z;
		return *this;
	}

	Vector3 & Vector3::operator+=(Vector3 & v2)
	{
		this->x + v2.x;
		this->y + v2.y;
		this->z + v2.z;
		return *this;
	}

	Vector3 & Vector3::operator-=(Vector3 & v2)
	{
		this->x - v2.x;
		this->y - v2.y;
		this->z - v2.z;
		return *this;
	}

	Vector3 & Vector3::operator*=(float m)
	{
		this->x * m;
		this->y * m;
		this->z * m;
		return *this;
	}

	Vector3 & Vector3::operator/=(float d)
	{
		this->x / d;
		this->y / d;
		this->z / d;
		return *this;
	}

	Vector3 Vector3::operator+(Vector3 & v2)
	{
		Vector3 res = *this;
		res += v2;
		return res;
	}

	Vector3 Vector3::operator-(Vector3 & v2)
	{
		Vector3 res = *this;
		res -= v2;
		return res;
	}

	Vector3 Vector3::operator*(float m)
	{
		Vector3 res = *this;
		res *= m;
		return res;
	}

	Vector3 Vector3::operator/(float d)
	{
		Vector3 res = *this;
		res /= d;
		return res;
	}

	float Vector3::getMagnitude()
	{
		return sqrt(x*x + y*y + z*z);
	}

	float Vector3::Dot(Vector3 & v1, Vector3 & v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	Vector3 Vector3::Cross(Vector3 & v1, Vector3 & v2)
	{
		return Vector3(
			v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x
		);
	}

	Vector3 Vector3::Lerp(Vector3 & v1, Vector3 & v2, float ratio)
	{
		Vector3 dir = v1 - v2;
		Vector3 step = dir * ratio;
		return v1 + step;
	}

	Vector3 Vector3::Proj(Vector3 & v1, Vector3 & v2)
	{
		float dot = Vector3::Dot(v1, v2);
		return v1 * (dot / v1.getMagnitude());
	}

	Vector3 Vector3::Refl(Vector3 & inDir, Vector3 & normal)
	{
		return inDir - normal * 2 * Vector3::Dot(inDir, normal);
	}

	float Vector3::AnglesBetween(Vector3 & v1, Vector3 & v2)
	{
		float angle = Vector3::Dot(v1, v2) / (v1.getMagnitude() * v2.getMagnitude());
		return acos(angle);
	}

	void Vector3::Show()
	{
		std::cout << "{x: " << x << ", y: " << y << ", z: " << z << "}" << "\n";
	}

	Vector3::~Vector3()
	{
	}
}
