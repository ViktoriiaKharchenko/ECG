#pragma once

#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <complex>
using namespace std;

class ButterworthFilter
{
	vector <double> xCoefs, yCoefs;


public:

	void setParameters(double TSample, double cutoffFrequency, int filterOrder);

	vector <double> filter(vector <double> signal);

};