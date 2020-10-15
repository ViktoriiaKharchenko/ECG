#include <SFML/Graphics.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "Drawer.h"

using namespace std;
using namespace sf;


int main()
{
	ifstream in("../../../Data/TXT/A00001.txt");
	int s;

	ECG ecg1;

	while (in >> s)
	{
		ecg1.data.push_back(s);
	}

	Drawer d;

	d.add(ecg1);

	d.show();
	
	cout << "end\n";

	return 0;
}