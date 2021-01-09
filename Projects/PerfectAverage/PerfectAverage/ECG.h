#pragma once

#include <vector>
#include <string>
#include <set>
#include <map>
#include <fstream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class ECG
{
	const static int MaxPeakDuration;
	const static int HalfPeakDuration;

public:
	
	static map<string, char> reference;
	static void initType();

	const static int numbersPerSecond = 300.0;

	vector <double> data;

	Color drawingColor;

	ECG();
	bool readFromFile(string path);

	vector <double> averageFilter(vector <double> _data, int D);
	vector <double> medianFilter(vector <double> _data, int D);

	vector <double> transformPeaks1(int l, int r);
	vector <int> getRPeaks(int l, int r);
};