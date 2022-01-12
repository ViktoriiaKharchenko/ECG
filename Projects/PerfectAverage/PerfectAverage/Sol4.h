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

class Sol4
{

public:

	void makeNoi_notNoiData();
	void makeNoi_notNoiData_validation();

	void makeNAO_data();
	void makeNAO_data_validation();

	void makeNAO_data_unfilt();
	void makeNAO_data_validation_unfilt();
};