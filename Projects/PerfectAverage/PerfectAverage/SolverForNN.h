#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

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
	int classify1_N_vs_AF_vs_O(vector <double>& types); // N vs AF vs O // tested

	vector <vector <int> > tree1(); // ((N vs AF) vs O) vs noisy
	vector <vector <int> > tree2(); // ((N vs O) vs AF) vs noisy
	vector <vector <int> > tree3(); // ((AF vs O) vs N) vs noisy
	vector <vector <int> > tree4(); // (N vs AF vs O) vs noisy

	void test1_1();
	void test1_2();

	void test2();


	pair<double, double> split2(string s);
	pair<pair<double, double>, double> split3(string s);

	int p_classify0_filtered(vector <pair<double, double> >& types); // non-noisy vs noisy // tested
	int p_classify0_unfiltered(vector <pair<double, double>>& types); // non-noisy vs noisy // tested
	int p_classify1_AFO_vs_N(vector <pair<double, double>>& types); // AF and O vs N // tested
	int p_classify1_NAF_vs_O(vector <pair<double, double>>& types); // N and AF vs O // tested
	int p_classify1_NO_vs_AF(vector <pair<double, double>>& types); // N and O vs AF // tested
	int p_classify2_AF_vs_O(vector <pair<double, double>>& types); // AF vs O // tested
	int p_classify2_N_vs_AF(vector <pair<double, double>>& types); // N vs AF // tested
	int p_classify2_N_vs_O(vector <pair<double, double>>& types); // N vs O // tested
	int p_classify1_N_vs_AF_vs_O(vector <pair<pair<double, double>, double> >& types); // N vs AF vs O  // tested

	vector <vector <int> > p_tree1(); // ((N vs AF) vs O) vs noisy
	vector <vector <int> > p_tree2(); // ((N vs O) vs AF) vs noisy
	vector <vector <int> > p_tree3(); // ((AF vs O) vs N) vs noisy
	vector <vector <int> > p_tree4(); // (N vs AF vs O) vs noisy

	void p_test1_1();
	void p_test1_2();

	void p_test2();
};