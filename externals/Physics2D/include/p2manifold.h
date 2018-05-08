#ifndef SFGE_P2MANIFOLD_H
#define SFGE_P2MANIFOLD_H

#include <p2body.h>

struct p2Manifold
{
	p2Body* bodyA;
	p2Body* bodyB;
	float penetration;
	p2Vec2 contacts[2]; // Max two contact points
	float contact_count = 0;
	p2Vec2 normal;

	void ResolveCollision();
};

#endif // !SFGE_P2MANIFOLD_H
