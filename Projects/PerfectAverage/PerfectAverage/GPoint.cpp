#include "GPoint.h"

GPoint::GPoint()
{
	x = y = 0;

	c = Color::Black;
}

GPoint::GPoint(double _x, double _y)
{
	x = _x;
	y = _y;

	c = Color::Black;
}

GPoint::GPoint(double _x, double _y, Color _c)
{
	x = _x;
	y = _y;

	c = _c;
}