#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "GLine.h"
#include "ECG.h"

using namespace sf;

class Drawer
{
	Clock clock;
	double timer;

	Event event;

	bool switchEvent(Event event, RenderWindow& window);
	void draw(RenderWindow& window);

	void process(RenderWindow& window);

	vector <GLine> toDrawLines;
	vector <pair<double, Color> > verticalLines;

	void rescaleCoordinates(double windowX, double windowY);

public:

	const static int windowShift = 50.0;

	Drawer();

	void add(ECG ecg);
	void addGraph(vector <double> data, int l, Color c = Color::Black);
	void addVerticalLine(double pos, Color c = Color::Red);
	void clear();

	void show(int windowX = 1800, int windowY = 900);
};