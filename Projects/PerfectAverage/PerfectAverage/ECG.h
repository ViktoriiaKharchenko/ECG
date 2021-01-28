#pragma once

#include <vector>
#include <string>
#include <set>
#include <map>
#include <fstream>
#include <SFML/Graphics.hpp>

#include "ButterworthFilter.h"

using namespace std;
using namespace sf;

class ECG
{
	const int MaxPeakDuration;
	const int HalfPeakDuration;

public:
	
	static map<string, char> reference;
	static void initType();

	const int numbersPerSecond;

	vector <double> data;

	Color drawingColor;

	ECG();
	ECG(int _numbersPerSecond);
	bool readFromFile(string path);
	bool readFromFile2(string path);

	vector <double> averageFilter(vector <double> _data, int D);
	vector <double> medianFilter(vector <double> _data, int D);

	vector <double> transformPeaks1(int l, int r);
	vector <int> getRPeaks(int l, int r);
};