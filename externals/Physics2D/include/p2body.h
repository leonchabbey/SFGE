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

#ifndef SFGE_P2BODY_H
#define SFGE_P2BODY_H

#include <list>
#include <p2aabb.h>
#include <p2fixture.h>

enum class p2BodyType
{
	STATIC,
	KINEMATIC,
	DYNAMIC
};

/**
* \brief Struct Defining the p2Body when creating it
*/
struct p2BodyDef
{
	p2BodyDef() {
		type = p2BodyType::DYNAMIC;
		position = p2Vec2();
		linearVelocity = p2Vec2();
		angularVelocity = 0.0f;
		gravityScale = 1;
		density = 1;
		angle = 0.0f;
	}

	p2BodyType type;
	p2Vec2 position;
	p2Vec2 linearVelocity;
	float angularVelocity;
	float gravityScale;
	float density;
	float angle;
};

/**
* \brief Rigidbody representation
*/
class p2Body
{
public:
	p2Body(const p2BodyDef*);

	p2Fixture* CreateFixture(const p2FixtureDef* def);

	void AddForce(const p2Vec2& velocity);
	void SetLinearVelocity(const p2Vec2& velocity);
	const p2Vec2& GetLinearVelocity() const;

	void SetAngularVelocity(const float& angVelocity);
	float GetAngularVelocity() const;

	void SetTransform(const p2Vec2& pos, float angle);
	p2Transform& GetTransform();

	void SetPosition(const p2Vec2& pos);
	p2Vec2 GetPosition() const;

	void SetRotation(const float& f);
	float GetRotation() const;

	void SetDensity(const float& d);
	float GetDensity();

	void SetMass(const float& m);
	float GetMass();

	void SetInvMass(const float& invM);
	float GetInvMass();

	void SetInertia(const float& i);
	float GetInertia();

	void SetInvInertia(const float& invI);
	float GetInvInertia();

	void ApplyForce(const p2Vec2& f);
	void ApplyImpulse(const p2Vec2& impulse, const p2Vec2& contactVector);

	// Get the AABB that contains all attached fixtures
	void GetFatAABB(p2AABB* aabb) const;

	std::list<p2Fixture*> GetAttachedFixtures() const;

	~p2Body();
private:
	std::list<p2Fixture*> m_FixtureList = {};

	p2BodyType m_Type;
	p2Transform m_Transform;
	p2Vec2 m_Force;
	p2Vec2 m_LinearVelocity;
	float m_AngularVelocity;
	float m_GravityScale;
	float m_Density;
	float m_Mass;
	float m_InvMass; // inverse
	float m_Inertia; // Moment of inertia
	float m_InvInertia; // inverse
};

#endif