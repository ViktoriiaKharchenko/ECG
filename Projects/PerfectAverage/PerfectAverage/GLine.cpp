#include "GLine.h"

GLine::GLine()
{
	c = Color::Black;
}

GLine::GLine(GPoint _p1, GPoint _p2)
{
	p1 = _p1;
	p2 = _p2;

	c = Color::Black;
}

GLine::GLine(double p1x, double p1y, double p2x, double p2y)
{
	p1.x = p1x;
	p1.y = p1y;
	p2.x = p2x;
	p2.y = p2y;

	c = Color::Black;
}

GLine::GLine(GPoint _p1, GPoint _p2, Color _c)
{
	p1 = _p1;
	p2 = _p2;

	c = _c;
}