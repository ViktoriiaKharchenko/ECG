#pragma once

#include "GPoint.h"

class GLine
{
public:

	GPoint p1, p2;
	Color c;

	GLine();
	GLine(GPoint p1, GPoint p2);
	GLine(double p1x, double p1y, double p2x, double p2y);
	GLine(GPoint p1, GPoint p2, Color c);

};