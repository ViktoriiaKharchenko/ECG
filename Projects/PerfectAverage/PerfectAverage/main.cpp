#include <SFML/Graphics.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "Drawer.h"

using namespace std;
using namespace sf;

string toECGString(int num)
{
	string s = to_string(num);

	while (s.size() != 5)
	{
		s = "0" + s;
	}

	return s;
}


int main()
{
	ECG::initType();

	for (auto it:ECG::reference)
	{
		//if (it.second == 'N')
		{
			cout << it.second << "\n";
			ECG ecg;

			ecg.readFromFile("../../../Data/TXT/" + it.first + ".txt");

			if (ecg.data.size() < 8999)
			{
				continue;
			}
			vector <double> peaks = ecg.getRs1(900, 3900);
			ecg.data = vector<double>(ecg.data.begin() + 600, ecg.data.begin() + 4200);


			Drawer d;

			d.add(ecg);
			d.addGraph(peaks, 310);

			d.show();
		}
	}

	return 0;
}