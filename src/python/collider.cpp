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


#include <physics/collider.h>
#include <physics/body2d.h>
#include <physics/physics.h>
namespace sfge
{
void Collider::Init()
{
}
void Collider::Update(float dt)
{
}
void Collider::OnColliderEnter(Collider * collider)
{
	if (collider->m_PhysicsFixture->IsSensor() or m_PhysicsFixture->IsSensor())
	{
		m_GameObject->OnTriggerEnter(collider);
	}
	else
	{
		m_GameObject->OnCollisionEnter(collider);
	}
}

void Collider::OnColliderExit(Collider * collider)
{
	if (collider->m_PhysicsFixture->IsSensor() or m_PhysicsFixture->IsSensor())
	{
		m_GameObject->OnTriggerExit(collider);
	}
	else
	{
		m_GameObject->OnCollisionExit(collider);
	}
}

Collider* Collider::LoadCollider(Engine & engine, GameObject * gameObject, json & componentJson)
{
	Body2d* body2d = gameObject->GetComponent<Body2d>();
	if (body2d != nullptr)
	{
		Collider* collider = new Collider(gameObject);
		p2FixtureDef fixtureDef;
		fixtureDef.userData = collider;
		
		ColliderType colliderType = ColliderType::NONE;
		if (CheckJsonNumber(componentJson, "collider_type"))
		{
			colliderType = (ColliderType)componentJson["collider_type"];
		}
		p2Shape* shape = nullptr;
		switch (colliderType)
		{
		case ColliderType::CIRCLE:
			{
				p2CircleShape* circleShape = new p2CircleShape();
				if (CheckJsonNumber(componentJson, "radius"))
				{
					circleShape->SetRadius(pixel2meter((float)componentJson["radius"]));
				}
				shape = circleShape;
			}
		break;
		case ColliderType::RECTANGLE:
			{
				p2PolygonShape* rectShape = new p2PolygonShape();
				p2Vec2 boxSize = pixel2meter(GetVectorFromJson(componentJson, "size"));
				rectShape->SetAsBox(boxSize.x, boxSize.y);
				shape = rectShape;
				break; 
			}
		}
		if (CheckJsonNumber(componentJson, "bouncing"))
		{
			fixtureDef.restitution = componentJson["bouncing"];
		}
		if (shape != nullptr)
		{
			fixtureDef.shape = shape;
		}
		if (CheckJsonParameter(componentJson, "sensor", json::value_t::boolean))
		{
			fixtureDef.isSensor = componentJson["sensor"];
		}
		
		collider->m_PhysicsFixture = body2d->GetBody()->CreateFixture(&fixtureDef);
		if (shape != nullptr)
		{
			delete(shape);
		}
		return collider;
	}
	else
	{
		Log::GetInstance()->Error("No body attached on the GameObject");
	}
	return nullptr;
}

}
