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

#ifndef SFGE_P2SAT_H
#define SFGE_P2SAT_H

#include <list>
#include <p2body.h>
#include <p2fixture.h>

struct p2Projection {
	float min;
	float max;

	bool Overlap(p2Projection&);
};

struct p2SAT {
	void EvaluateSAT();

	void CirclevsCircle();
	void CirclevsPolygon();
	void PolygonvsPolygon();
	void PolygonvsCircle();

	bool areOverlapping = false;

	p2Fixture * fixtureA;
	p2Fixture * fixtureB;
};

bool IsPolygonCounterClockwise(p2PolygonShape* s);
void GetAxis(p2PolygonShape* s, p2Vec2(&vertices)[MAX_POLYGON_VERTICES], p2Vec2(&axis)[MAX_POLYGON_VERTICES]);
void ProjectOnAxis(const p2Vec2& axis, p2PolygonShape* s, p2Projection&);
void RotateAndWorldSpaceVertices(p2PolygonShape* s, p2Body* b, p2Vec2(&v)[MAX_POLYGON_VERTICES]);

#endif