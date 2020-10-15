#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

class GPoint
{
public:

	double x, y;

	Color c;

	GPoint();
	GPoint(double _x, double _y);
	GPoint(double _x, double _y, Color _c);

};