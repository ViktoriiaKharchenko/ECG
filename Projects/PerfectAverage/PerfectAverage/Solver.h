#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "Drawer.h"

using namespace std;
using namespace sf;

class Solver
{

	string toECGString(int num);

	double mean(vector <double> peaks);

	double var(vector <double> peaks, double mean);

	vector <double> filterDiff(vector <double> diff);


public:

	void solve1();

	void solve2();

	void testButterworthFilterSin();

	void testButterworthFilterECG();

	void solve3();

	void makeRPeaksCSV2();

	void drawPart(string ecgPath, string filteredPath, string myPeaksPath, string refPeaksPath, int l, int r);

	void calcAlgorithmStatsCSV2();

	void showAllTypes();
};