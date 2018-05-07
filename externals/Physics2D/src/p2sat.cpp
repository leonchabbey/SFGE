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

#include <p2sat.h>

void p2SAT::EvaluateSAT()
{
	p2Shape::Type shapeTypeA = fixtureA->GetShape()->GetType();
	p2Shape::Type shapeTypeB = fixtureB->GetShape()->GetType();

	switch (shapeTypeA) {
	case p2Shape::Type::POLYGON: {
		if (shapeTypeB == p2Shape::Type::CIRCLE)
			PolygonvsCircle();
		else
			PolygonvsPolygon();
		break;
	}
	case p2Shape::Type::CIRCLE: {
		if (shapeTypeB == p2Shape::Type::POLYGON)
			CirclevsPolygon();
		else
			CirclevsCircle();
		break;
	}
	}
}

void p2SAT::CirclevsCircle()
{
}

void p2SAT::CirclevsPolygon()
{
}

void p2SAT::PolygonvsPolygon()
{
}

void p2SAT::PolygonvsCircle()
{
}
