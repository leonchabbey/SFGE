#include "..\include\p2manifold.h"

#define _USE_MATH_DEFINES
#include <math.h>

void p2Manifold::ResolveCollision()
{
	if (contact_count <= 0) {
		return;
	}

	// Messes up everything because of too much difference of mass
	//float massA = bodyA->GetMass();
	//float massB = bodyB->GetMass();
	float massA = 1.0f;
	float massB = 1.0f;

	p2Vec2 velocityA = bodyA->GetLinearVelocity();
	p2Vec2 velocityB = bodyB->GetLinearVelocity();

	p2Vec2 newVelocityA = velocityA * ((massA - massB) / (massA + massB)) + velocityB * ((2.0f * massB) / (massA + massB));
	p2Vec2 newVelocityB = velocityA * ((2.0f * massA) / (massA + massB)) + velocityB * ((massA - massB) / (massA + massB));

	bodyA->SetLinearVelocity(newVelocityA);
	bodyB->SetLinearVelocity(newVelocityB);
}
