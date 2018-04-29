#include "..\include\p2Fixture.h"

p2Fixture::p2Fixture(p2Body * b, const p2FixtureDef * def): m_Body(b)
{
	m_Shape = def->shape;
	m_Friction = def->friction;
	m_Restitution = def->restitution;
	m_Density = def->density;
	m_IsSensor = def->isSensor;
}

p2Shape::Type p2Fixture::GetType() const
{
	return m_Shape->GetType();
}

p2Shape * p2Fixture::GetShape()
{
	return m_Shape;
}

p2Body * p2Fixture::GetBody()
{
	return m_Body;
}

void p2Fixture::SetSensor(bool s)
{
	m_IsSensor = s;
}

bool p2Fixture::IsSensor() const
{
	return m_IsSensor;
}

void p2Fixture::SetFriction(float f)
{
	m_Friction = f;
}

float p2Fixture::GetFriction() const
{
	return m_Friction;
}

void p2Fixture::SetRestitution(float r)
{
	m_Restitution = r;
}

float p2Fixture::GetRestitution() const
{
	return m_Restitution;
}

void p2Fixture::SetDensity(float d)
{
	m_Density = d;
}

float p2Fixture::GetDensity() const
{
	return m_Density;
}
