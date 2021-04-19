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

	// test();
};