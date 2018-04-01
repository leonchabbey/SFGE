#ifndef SFGE_VECTOR3_H
#define SFGE_VECTOR3_H

namespace sfge {
	class Vector3 {
	public:
		float x, y, z;

		Vector3(float x, float y, float z);

		Vector3 & operator=(Vector3 & v2);
		Vector3 & operator+=(Vector3 & v2);
		Vector3 & operator-=(Vector3 & v2);
		Vector3 & operator*=(float m);
		Vector3 & operator/=(float d);

		Vector3 operator+(Vector3 & v2);
		Vector3 operator-(Vector3 & v2);
		Vector3 operator*(float m);
		Vector3 operator/(float d);

		float getMagnitude();

		static float Dot(Vector3 & v1, Vector3 & v2);
		static Vector3 Cross(Vector3 & v1, Vector3 & v2);
		static Vector3 Lerp(Vector3 & v1, Vector3 & v2, float ratio);
		static Vector3 Proj(Vector3 & v1, Vector3 & v2);
		static Vector3 Refl(Vector3 & inDir, Vector3 & normal);
		static float AnglesBetween(Vector3 & v1, Vector3 & v2);

		void Show();

		~Vector3();
	};
}

#endif // !SFGE_VECTOR3_H
