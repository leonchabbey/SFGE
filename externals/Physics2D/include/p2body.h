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
#include <p2Fixture.h>

class p2Collider;
struct p2ColliderDef;

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
		gravityScale = 1;
	}

	p2BodyType type;
	p2Vec2 position;
	p2Vec2 linearVelocity;
	float gravityScale;
};

/**
* \brief Rigidbody representation
*/
class p2Body
{
public:
	p2Body(const p2BodyDef&);

	p2Fixture* CreateFixture(const p2FixtureDef* def);

	void AddForce(const p2Vec2& velocity);
	void SetLinearVelocity(const p2Vec2& velocity);
	void SetAngularVelocity(const float& angVelocity);
	void SetPosition(const p2Vec2& pos);

	p2Vec2 GetLinearVelocity();
	float GetAngularVelocity();
	p2Vec2 GetPosition();

	~p2Body();
private:
	std::list<p2Fixture*> m_FixtureList = {};
	p2Vec2 position;
	p2Vec2 linearVelocity;
	float angularVelocity;
	float mass;
};

#endif