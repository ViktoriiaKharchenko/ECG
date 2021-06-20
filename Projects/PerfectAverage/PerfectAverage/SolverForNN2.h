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

class SolverForNN2
{

public:

	void makeClassificationData();

	void makeDataForNvsAF();
	void makeDataForNvsO();
	void makeDataForAFvsO();

	void makeDataForNAFvsO();
	void makeDataForNOvsAF();
	void makeDataForNvsAFO();

	void makeDataForNvsAFvsO();


};