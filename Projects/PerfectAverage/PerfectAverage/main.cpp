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

double mean(vector <double> peaks)
{
	double sum = 0;

	for (auto it : peaks)
	{
		sum += it;
	}

	sum /= peaks.size();

	return sum;
}

double var(vector <double> peaks, double mean)
{
	double res = 0;

	for (auto it : peaks)
	{
		res += abs(mean - it) * abs(mean - it);
	}

	res /= peaks.size();

	return res;
}

vector <double> filter(vector <double> diff)
{
	sort(diff.begin(), diff.end());

	vector <double> res;

	for (int i = 2; i + 2 < diff.size(); i++)
	{
		res.push_back(diff[i]);
	}

	return diff;
}



int main()
{
	ECG::initType();

	int goodN = 0, goodA = 0, badN = 0, badA = 0;

	int aa = 0;

	for (auto it:ECG::reference)
	{
		//if (it.second == 'N')
		{
			cout << it.first << " " << it.second << "\n";
			ECG ecg;

			ecg.readFromFile("../../../Data/TXT/" + it.first + ".txt");
			cout << ecg.data.size()<<endl;
			if (ecg.data.size() < 8999)
			{
				continue;
			}
			vector <double> transform = ecg.transformPeaks1(900, 8000);
			
			vector <int> peaks = ecg.getRPeaks(900, 8000);
			ecg.data = vector<double>(ecg.data.begin() + 600, ecg.data.begin() + 8300);

			Drawer d;

			d.add(ecg);
			//d.addGraph(transform, 300, Color::Green);
			for (auto it : peaks)
			{
				d.addVerticalLine(300 + it);
			}

			d.show();
		}
	}
	
	return 0;
}