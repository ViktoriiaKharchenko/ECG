#include "Drawer.h"

Drawer::Drawer()
{
	timer = 0;
}

void Drawer::rescaleCoordinates(double windowX, double windowY)
{
	double sizeX = windowX - 2.0 * windowShift;
	double sizeY = windowY - 2.0 * windowShift;

	double minX = toDrawLines[0].p1.x, minY = toDrawLines[0].p1.y, maxX = toDrawLines[0].p1.x, maxY = toDrawLines[0].p1.y;
	double scaleX, scaleY;

	for (auto line : toDrawLines)
	{
		minX = min(minX, line.p1.x);
		minY = min(minY, line.p1.y);
		maxX = max(maxX, line.p1.x);
		maxY = max(maxY, line.p1.y);

		minX = min(minX, line.p2.x);
		minY = min(minY, line.p2.y);
		maxX = max(maxX, line.p2.x);
		maxY = max(maxY, line.p2.y);
	}
	for (auto line : verticalLines)
	{
		minX = min(minX, line.first);
		maxX = max(maxX, line.first);
	}


	scaleX = sizeX / (maxX - minX);
	scaleY = sizeY / (maxY - minY);

	for (auto& line : toDrawLines)
	{
		line.p1.x = (line.p1.x - minX) * scaleX + windowShift;
		line.p1.y = (line.p1.y - minY) * scaleY + windowShift;
		line.p2.x = (line.p2.x - minX) * scaleX + windowShift;
		line.p2.y = (line.p2.y - minY) * scaleY + windowShift;
	}
	for (auto& line : verticalLines)
	{
		line.first = (line.first - minX) * scaleX + windowShift;
	}
}

void Drawer::show(int windowX, int windowY)
{
	rescaleCoordinates(windowX, windowY);

	RenderWindow window(VideoMode(windowX, windowY), "Drawer");

	window.setKeyRepeatEnabled(0);

	process(window);
}

void Drawer::process(RenderWindow& window)
{
	while (window.isOpen())
	{
		timer += clock.getElapsedTime().asMicroseconds() / 1000.0;
		clock.restart();

		if (window.pollEvent(event))
		{
			if (!switchEvent(event, window))
			{
				window.close();
			}
		}

		if (timer > 200.0)
		{
			draw(window);

			timer = 0.0;
		}
	}
}

bool Drawer::switchEvent(Event event, RenderWindow& window)
{
	if (event.type == Event::Closed)
	{
		return false;
	}
	if (event.type == Event::KeyPressed)
	{
		if (event.key.code == Keyboard::Enter)
		{
			return false;
		}
	}

	return true;
}

void Drawer::draw(RenderWindow& window)
{
	window.clear(Color::White);

	for (auto vLine : verticalLines)
	{
		Vertex line[2] = { Vertex(Vector2f(vLine.first, 0)), Vertex(Vector2f(vLine.first, window.getSize().y)) };
		line[0].color = vLine.second;
		line[1].color = vLine.second;

		window.draw(line, 2, Lines);
	}

	for (auto gline : toDrawLines)
	{
		Vertex line[2] = { Vertex(Vector2f(gline.p1.x, gline.p1.y)), Vertex(Vector2f(gline.p2.x, gline.p2.y)) };
		line[0].color = gline.c;
		line[1].color = gline.c;

		window.draw(line, 2, Lines);
	}

	window.display();
}

void Drawer::add(ECG ecg)
{
	for (int i = 1; i < ecg.data.size(); i++)
	{
		toDrawLines.push_back(GLine(GPoint(i - 1.0, -ecg.data[i - 1]), GPoint(i, -ecg.data[i]), ecg.drawingColor));
	}
}

void Drawer::addGraph(vector <double> data, int l, Color c)
{
	for (int i = 1; i < data.size(); i++)
	{
		GLine line = GLine(GPoint(l + i - 1.0, -data[i - 1]), GPoint(l + i, -data[i]));
		line.c = c;

		toDrawLines.push_back(line);
	}
}

void Drawer::addVerticalLine(double pos, Color c)
{
	verticalLines.push_back({ pos, c });
}

void Drawer::clear()
{
	toDrawLines.clear();
}