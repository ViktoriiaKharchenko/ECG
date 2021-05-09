#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "Drawer.h"

#include "TasksQueue.h"

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

	void drawECG();

	void testButterworthFilterSin();

	void testButterworthFilterECG();

	void solve3();

	void makeRPeaksCSV2();

	void drawPart(string ecgPath, string filteredPath, string myPeaksPath, string refPeaksPath, string name, int l, int r);

	void drawPartWrap();

	void calcAlgorithmStatsCSV2();

	void showAllTypes();

	void computeRPeaksDetectionResults();

	void analyzeComputedStats1();

	void analyzeComputedStats2();

	void analyzeComputedStats3();


	void makeDataForNoisyClasification();
	void makeDataForNoisyClasification2();
	void makeDataForNoisyClasification3();
	void makeDataForNoisyModel();

	void makeDataAFvsNormalScaled();

	void combineNoisyPrediction();
};