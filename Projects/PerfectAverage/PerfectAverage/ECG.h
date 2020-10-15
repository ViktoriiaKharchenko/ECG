#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class ECG
{
public:

	const static int numbersPerSecond = 300.0;

	vector <double> data;

	Color drawingColor;

	ECG();

};