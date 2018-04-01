#include "type/vector3.h"
#include <iostream>

int main()
{
	sfge::Vector3 a(1.0f, 2.0f, 3.0f);
	sfge::Vector3 b(4.0f, 5.0f, 6.0f);

	(a + b).Show();
	(a - b).Show();
	std::cout << "Dot product: " << sfge::Vector3::Dot(a, b) << "\n";
	sfge::Vector3::Cross(a, b).Show();
	sfge::Vector3::Lerp(a, b, 0.5f).Show();
	sfge::Vector3::Proj(a, b).Show();
	sfge::Vector3::Proj(b, a).Show();
	sfge::Vector3::Refl(a, b).Show();
	sfge::Vector3::Refl(b, a).Show();
	std::cout << "Angle between the vectors: " << sfge::Vector3::AnglesBetween(a,b) << "\n";
	system("pause");
	return 0;
}