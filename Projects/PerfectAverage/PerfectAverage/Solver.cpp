#include "Solver.h"

string Solver::toECGString(int num)
{
	string s = to_string(num);

	while (s.size() != 5)
	{
		s = "0" + s;
	}

	return s;
}

double Solver::mean(vector <double> peaks)
{
	double sum = 0;

	for (auto it : peaks)
	{
		sum += it;
	}

	sum /= peaks.size();

	return sum;
}

double Solver::var(vector <double> peaks, double mean)
{
	double res = 0;

	for (auto it : peaks)
	{
		res += abs(mean - it) * abs(mean - it);
	}

	res /= peaks.size();

	return res;
}

vector <double> Solver::filterDiff(vector <double> diff)
{
	sort(diff.begin(), diff.end());

	vector <double> res;

	for (int i = 2; i + 2 < diff.size(); i++)
	{
		res.push_back(diff[i]);
	}

	return diff;
}




void Solver::solve1()
{
	// first try to detect R peaks


	int goodN = 0, goodA = 0, badN = 0, badA = 0;

	int aa = 0;

	for (auto it : ECG::reference)
	{
		//if (it.second == 'N')
		{
			cout << it.first << " " << it.second << "\n";
			ECG ecg;

			ecg.readFromFile("../../../Data/TXT/" + it.first + ".txt");
			cout << ecg.data.size() << endl;
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
}

void Solver::solve2()
{
	for (auto it : ECG::reference)
	{
		//if (it.second == 'O')
		{
			cout << it.first << " " << it.second << "\n";
			ECG ecg;

			ecg.readFromFile("../../../Data/TXT/" + it.first + ".txt");

			if (ecg.data.size() < 8999)
			{
				continue;
			}

			ecg.data = vector<double>(ecg.data.begin(), ecg.data.begin() + 8500);

			//vector <double> filter1Average = ecg.averageFilter(ecg.averageFilter(ecg.data, 60), 180);
			vector <double> filter1Average =ecg.averageFilter(ecg.data, 100);
			ECG ecgFilteredA;
			ecgFilteredA.drawingColor = Color::Green;
			ecgFilteredA.data = ecg.data;
			for (int i = 0; i < ecg.data.size(); i++)
			{
				ecgFilteredA.data[i] -= filter1Average[i] + 1000;
			}

			//vector <double> filter1Median = ecg.medianFilter(ecg.medianFilter(ecg.data, 60), 180);
			vector <double> filter1Median = ecg.medianFilter(ecg.data, 100);
			ECG ecgFilteredM;
			ecgFilteredM.drawingColor = Color::Blue;
			ecgFilteredM.data = ecg.data;
			for (int i = 0; i < ecg.data.size(); i++)
			{
				ecgFilteredM.data[i] -= filter1Median[i] + 2000;
			}

			Drawer d;

			d.add(ecg);
			d.add(ecgFilteredA);
			d.add(ecgFilteredM);
			d.addGraph(filter1Average, 0, Color::Green);
			d.addGraph(filter1Median, 0, Color::Blue);

			d.show();
		}
	}


}