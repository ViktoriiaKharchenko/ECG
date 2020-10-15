#pragma once

#include <SFML/Graphics.hpp>

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

	void rescaleCoordinates(double windowX, double windowY);

public:

	const static int windowShift = 100.0;

	Drawer();

	void add(ECG ecg);
	void clear();

	void show(int windowX = 1800, int windowY = 500);
};