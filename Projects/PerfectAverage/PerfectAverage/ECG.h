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

	static vector <double> rescale(vector <double> data, int size);

	vector <double> transformPeaks1(int l, int r);
	vector <int> getRPeaks(int l, int r, double WSiseP = 1.75, double WSiftP = 0.1,
		double MBTLeftP = 0.39, double MBTRightP = 0.3, double SBPThresholdP = 0.25);
};