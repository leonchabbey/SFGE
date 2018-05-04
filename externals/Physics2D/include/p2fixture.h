#ifndef SFGE_P2FIXTURE_H
#define SFGE_P2FIXTURE_H

#include <p2shape.h>

class p2Body;

struct p2FixtureDef
{
	p2FixtureDef() {
		shape = nullptr;
		friction = 0.0f;
		restitution = 0.0f;
		density = 0.0f;
		isSensor = false;
		userData = nullptr;
	}

	p2Shape* shape;

	float friction;
	float restitution;
	float density;
	bool isSensor;
	void* userData;
};

class p2Fixture
{
public:
	p2Fixture(p2Body* b, const p2FixtureDef* def);

	// Return type of shape
	p2Shape::Type GetType() const;

	p2Shape* GetShape() const;
	p2Body* GetBody() const;

	void SetSensor(bool s);
	bool IsSensor() const;

	void SetFriction(float f);
	float GetFriction() const;

	void SetRestitution(float r);
	float GetRestitution() const;

	void SetDensity(float d);
	float GetDensity() const;

	void SetUserData(void* p);
	void* GetUserData() const;
private:
	p2Shape* m_Shape;
	p2Body* m_Body;

	float m_Friction;
	float m_Restitution;
	float m_Density;
	bool m_IsSensor;
	void* m_UserData;
};

#endif // !SFGE_P2FIXTURE_H
