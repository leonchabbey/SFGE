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

#ifndef SFGE_P2CONTACT_H
#define SFGE_P2CONTACT_H

#include <list>
#include <p2fixture.h>
#include <p2contactmanager.h>

class p2ContactListener;

/**
* \brief Representation of a contact given as argument in a p2ContactListener
*/
class p2Contact
{
public:
	p2Contact(p2Fixture* fxA, p2Fixture* fxB);

	void Update(p2ContactListener* listener);

	/*
	* \brief Get Fixture A
	*/
	p2Fixture* GetFixtureA() const;
	/*
	* \brief Get Fixture B
	*/
	p2Fixture* GetFixtureB() const;
	/*
	* \brief Get if fixtures are touching
	*/
	bool IsTouching() const;
private:
	void Evaluate();

	p2Fixture* m_FixtureA;
	p2Fixture* m_FixtureB;

	p2Manifold m_Manifold;
	bool m_IsTouching = false;
};

void CirclevsCircle(p2Manifold& m, const p2Fixture* fxA, const p2Fixture* fxB);
void CirclevsPolygon(p2Manifold& m, const p2Fixture* fxA, const p2Fixture* fxB);
void PolygonvsPolygon(p2Manifold& m, const p2Fixture* fxA, const p2Fixture* fxB);
void PolygonvsCircle(p2Manifold& m, const p2Fixture* fxA, const p2Fixture* fxB);

#endif