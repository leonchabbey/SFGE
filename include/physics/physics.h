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

#ifndef SFGE_PHYSICS_H
#define SFGE_PHYSICS_H

#include <p2vector.h>
#include <p2world.h>

#include <SFML/System/Time.hpp>

#include <engine/engine.h>
#include <engine/component.h>

namespace sfge
{
	
class Body2d;

float pixel2meter(float pixel);
float pixel2meter(int pixel);
p2Vec2 pixel2meter(sf::Vector2f pixel);
p2Vec2 pixel2meter(sf::Vector2i pixel);

float meter2pixel(float meter);
sf::Vector2f meter2pixel(p2Vec2 meter);

/**
* \brief Child of the Physics2d p2ContactListener use to retrieve contacts between Body2d
*/
class ContactListener : public p2ContactListener
{

	void BeginContact(p2Contact* contact);

	void EndContact(p2Contact* contact);
};

/**
 * \brief The Physics Manager use Box2D to simulate 2D physics
 */
class PhysicsManager : public Module
{
public:
	using Module::Module;

	/**
	 * \brief Initialize the Physics Manager, but do not create a b2World
	 */
	void Init() override;

	/**
	* \brief Get The World
	*/
	p2World* GetWorld();
	/**
	 * \brief Called each frame to update the b2World if not in editor mode
	 * @param dt Delta time since last frame
	 */
	void Update(sf::Time dt) override;
	/**
	* \brief Called at the end of the program to Destroy the b2World, if it sill exists
	*/
	void Destroy() override;
	/**
	* \brief Called before the loading of a new scene, destroy the currentWorld and create a new one
	*/
	void Reset() override;
	/**
	* \brief Mandatory method
	*/
	void Collect() override;

	const static float pixelPerMeter;
private:
	friend class Body2d;
	friend class Collider;
	p2World* m_World = nullptr;
	ContactListener* m_ContactListener;
	std::list<Body2d*> m_Bodies;
	std::list<Collider*> m_Colliders;

};



}
#endif
