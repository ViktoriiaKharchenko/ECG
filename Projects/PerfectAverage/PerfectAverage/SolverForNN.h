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

class SolverForNN
{

public:

	void makeClassificationData();

	void makeDataForNvsAF();
	void makeDataForNvsO();
	void makeDataForAFvsO();

	void makeDataForNAFvsO();
	void makeDataForNOvsAF();
	void makeDataForAFOvsN();

	void makeDataForNvsAFvsO();

	
	int classify0_filtered(vector <double>& types); // non-noisy vs noisy // tested
	int classify0_unfiltered(vector <double>& types); // non-noisy vs noisy // tested
	int classify1_AFO_vs_N(vector <double>& types); // AF and O vs N // tested
	int classify1_NAF_vs_O(vector <double>& types); // N and AF vs O // tested
	int classify1_NO_vs_AF(vector <double>& types); // N and O vs AF // tested
	int classify2_AF_vs_O(vector <double>& types); // AF vs O // tested
	int classify2_N_vs_AF(vector <double>& types); // N vs AF // tested
	int classify2_N_vs_O(vector <double>& types); // N vs O // tested

	vector <vector <int> > tree1(); // ((N vs AF) vs O) vs noisy
	vector <vector <int> > tree2(); // ((N vs O) vs AF) vs noisy
	vector <vector <int> > tree3(); // ((AF vs O) vs N) vs noisy

	void test();

	void test2();
};