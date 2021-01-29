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

void Solver::testButterworthFilterSin()
{
	ButterworthFilter btwFilter;

	double rate = 1.0 / 300.0;

	btwFilter.setParameters(rate, 35, 10);

	vector <double> arr;

	for (int i = 0; i < 2000; i++)
	{
		arr.push_back(100 * sin(1.0 * i * rate) + 50 * sin(50.0 * i * rate));
	}

	vector <double> filtered = btwFilter.filter(arr);

	for (auto& it : filtered)
	{
		it += 500;
	}

	Drawer d;

	ECG e1, e2;

	e1.data = arr; e1.drawingColor = Color::Blue;
	e2.data = filtered; e2.drawingColor = Color::Green;

	d.add(e1);
	d.add(e2);

	d.show();

	cout << "+\n";
}

void Solver::testButterworthFilterECG()
{
	for (auto it : ECG::reference)
	{
		//if (it.second == 'O')
		{
			cout << it.first << " " << it.second << "\n";
			ECG ecg;
			ECG ecg2;

			ecg.readFromFile("../../../Data/TXT/" + it.first + ".txt");

			if (ecg.data.size() < 8999)
			{
				continue;
			}

			ecg.data = vector<double>(ecg.data.begin(), ecg.data.begin() + 8500);
			
			//vector <double> filter1Median = ecg.medianFilter(ecg.medianFilter(ecg.data, 60), 180);
			vector <double> filter1Median = ecg.medianFilter(ecg.data, 100);
			ECG ecgFilteredM;
			ecgFilteredM.drawingColor = Color::Blue;
			ecgFilteredM.data = ecg.data;
			for (int i = 0; i < ecg.data.size(); i++)
			{
				ecgFilteredM.data[i] -= filter1Median[i] + 1000;
			}

			ButterworthFilter btwFilter;
			btwFilter.setParameters(1.0 / 300.0, 109, 10);
			ECG filteredECG;
			filteredECG.data = btwFilter.filter(ecg.data);
			filteredECG.drawingColor = Color::Green;
			for (int i = 0; i < filteredECG.data.size(); i++)
			{
				filteredECG.data[i] -= 2000;
			}
			filteredECG.data = vector<double>(filteredECG.data.begin() + 25, filteredECG.data.end());

			Drawer d;

			d.add(ecg);
			d.add(ecgFilteredM);
			d.add(filteredECG);
			d.addGraph(filter1Median, 0, Color::Blue);

			d.show();
		}
	}


}

void Solver::solve3()
{
	// filtering + R peak detection

	for (auto it : ECG::reference)
	{
		//if (it.second == 'N')
		{
			// read ECG
			cout << it.first << " " << it.second << "\n";
			ECG ecg;

			ecg.readFromFile("../../../Data/TXT/" + it.first + ".txt");
			cout << ecg.data.size() << endl;
			if (ecg.data.size() < 8999)
			{
				continue;
			}

			// median filter
			vector <double> filter1 = ecg.medianFilter(ecg.data, 100);
			for (int i = 0; i < filter1.size(); i++)
			{
				filter1[i] =  ecg.data[i] - filter1[i];
			}

			// butterworth filter

			ButterworthFilter btw;
			btw.setParameters(1.0 / 300.0, 35.0 * M_PI, 10);
			
			ECG filteredEcg;
			filteredEcg.drawingColor = Color::Blue;
			filteredEcg.data = btw.filter(filter1);

			vector <int> peaks = filteredEcg.getRPeaks(0, filteredEcg.data.size());

			Drawer d;

			for (auto& it : filteredEcg.data)
			{
				it += 1500;
			}

			d.add(ecg);
			d.add(filteredEcg);
			for (auto it : peaks)
			{
				d.addVerticalLine(it);
			}

			d.show();
		}
	}
}

void Solver::makeRPeaksCSV2()
{
	string ts;
	vector<string> records;

	ifstream in("../../../Data/CSV2/RECORDS");

	while (in >> ts)
	{
		records.push_back(ts);
	}

	in.close();

	for (auto name : records)
	{
		name = "104";

		// read ECG
		cout << name << "\n";
		ECG ecg(360);

		ecg.readFromFile2("../../../Data/CSV2/" + name + ".csv");
		cout << ecg.data.size() << endl;

		ecg.data = vector<double>(ecg.data.begin() + 40604 - 1000, ecg.data.begin() + 40604 + 1000);
		
		// median filter
		vector <double> filter1 = ecg.medianFilter(ecg.data, ecg.numbersPerSecond * 0.35);
		for (int i = 0; i < filter1.size(); i++)
		{
			filter1[i] = ecg.data[i] - filter1[i];
		}

		// butterworth filter

		ButterworthFilter btw;
		btw.setParameters(1.0 / ecg.numbersPerSecond, 35.0 * M_PI, 10);

		ECG filteredEcg;
		filteredEcg.drawingColor = Color::Blue;
		filteredEcg.data = btw.filter(filter1);

		vector <int> peaks = filteredEcg.getRPeaks(0, filteredEcg.data.size());
		cout << "find " << peaks.size() << " R peaks\n";

		/*
		ofstream out("../../../Data/CSV2RPeaksOurAlgorithm/" + name + ".txt");
		for (auto it : peaks)
		{
			out << it << "\n";
		}
		out.close();
		*/

		
		Drawer d;

		for (auto& it : filteredEcg.data)
		{
			it += 1500;
		}

		d.add(ecg);
		d.add(filteredEcg);
		for (auto it : peaks)
		{
			d.addVerticalLine(it);
		}

		d.show();
		
		break;
	}
}

void Solver::calcAlgorithmStatsCSV2()
{
	string ts;
	vector<string> records;

	ifstream in("../../../Data/CSV2/RECORDS");

	while (in >> ts)
	{
		records.push_back(ts);
	}

	in.close();

	for (auto name : records)
	{
		//ecg.readFromFile2("../../../Data/CSV2/" + name + ".csv");
		//cout << ecg.data.size() << endl;

		name = "101";

		int val, tp;
		double _val;

		vector <int> myPeaks;
		vector <int> referencePeaks;

		ifstream inMy("../../../Data/CSV2RPeaksOurAlgorithm/" + name + ".txt");
		while (inMy >> val)
		{
			myPeaks.push_back(val);
		}
		inMy.close();
		
		ifstream inRef("../../../Data/CSVatrTime/" + name + "atr.csv");
		ifstream inRefType("../../../Data/CSVatr/" + name + "atr.csv");
		while (inRef >> _val)
		{
			inRefType >> tp;
			val = _val * 360;

			//if (tp <= 20)
			{
				referencePeaks.push_back(val);
			}
		}
		inRef.close();
		inRefType.close();
		
		set<int> peaks, reference;
		for (auto it : myPeaks)
		{
			peaks.insert(it);
		}
		for (auto it : referencePeaks)
		{
			reference.insert(it);
		}

		const int maxR = 60;

		int ok = 0, fp = 0, fn = 0;

		cout << reference.size() << "\n";

		for (auto it : myPeaks)
		{
			val = it - maxR;

			auto iter = reference.lower_bound(val);

			if (iter != reference.end())
			{
				if (abs(it - *iter) <= maxR)
				{
					ok++;

					peaks.erase(it);
					reference.erase(iter);
				}
			}
		}

		fp = peaks.size();
		fn = reference.size();
		
		cout << "name=" << name << "   \tok = " << ok << "   \tfp = " << fp << "   \tfn = " << fn << "\n";

		cout << "fp:\n";
		for (auto it : peaks)
		{
			cout << it << " ";
		}
		cout << "\n";

		cout << "fn:\n";
		for (auto it : reference)
		{
			cout << it << " ";
		}
		cout << "\n";

		break;
	}
}