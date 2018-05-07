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

#ifndef SFGE_P2WORLD_H
#define SFGE_P2WORLD_H

#include <list>
#include <memory>
#include <p2vector.h>
#include <p2body.h>
#include <p2contactmanager.h>
#include <p2quadtree.h>

/**
* \brief Representation of the physical world in meter
*/
class p2World
{
public:
	p2World(const p2Vec2& screenSize, const p2Vec2& gravity);
	~p2World();
	/**
	* \brief Simulate a new step of the physical world, simplify the resolution with a QuadTree, generate the new contacts
	*/
	void Step(const float& dt);
	/**
	* \brief Debug for quadtree (draw on screen quadrants)
	*/
	void Debug(sf::RenderWindow&);
	/**
	* \brief Factory method to create a new p2Body attached to the p2World
	*/
	p2Body* CreateBody(const p2BodyDef& bodyDef);
	/**
	* \brief Set the contact listener
	*/
	void SetContactListener(p2ContactListener* contactListener);
private:
	std::list<p2Body*> m_BodyList = {};
	p2Vec2 m_Gravity;
	p2ContactManager* m_ContactManager;
};

#endif