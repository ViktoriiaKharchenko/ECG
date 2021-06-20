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
		//if (it.second == 'A')
		{
			if (it.first < "A01000")
			{
				continue;
			}

			cout << it.first << " " << it.second << "\n";
			ECG ecg;

			ecg.readFromFile("../../../Data/TXTFiltered/" + it.first + ".txt");
			cout << ecg.data.size() << endl;
			if (ecg.data.size() < 8999)
			{
				continue;
			}

			ecg.data = vector<double>(ecg.data.begin() + 2000, ecg.data.begin() + 7000);

			vector <double> transform = ecg.transformPeaks1(0, 5000);
			for (auto& it : transform)
			{
				it -= 2500;
			}

			vector <int> peaks = ecg.getRPeaks(0, 5000);
			vector <int> what = ecg.potentRPeaks;

			Drawer d;

			d.add(ecg);
			d.addGraph(transform, 0, Color::Green);
			for (int i = 0; i < what.size(); i++)
			{
				if (what[i] == 1)
				{
					vector <double> sm;
					sm.push_back(transform[i - 1]);
					sm.push_back(transform[i]);
					sm.push_back(transform[i + 1]);

					d.addGraph(sm, i-1, Color::Blue);
				}
			}
			for (auto it : peaks)
			{
				d.addVerticalLine(it);
			}

			d.show();
		}
	}
}

void Solver::solve2()
{
	for (auto it : ECG::reference)
	{
		if (it.first < "A00001")
		{
			continue;
		}

		//if (it.second == 'O')
		{
			cout << it.first << " " << it.second << "\n";
			ECG ecg;

			ecg.readFromFile("../../../Data/TXT/" + it.first + ".txt");

			if (ecg.data.size() < 8999)
			{
				continue;
			}

			ecg.data = vector<double>(ecg.data.begin() + 900, ecg.data.begin() + 4900);

			vector <double> filter1Average = ecg.averageFilter(ecg.averageFilter(ecg.data, 60), 180);
			//vector <double> filter1Average =ecg.averageFilter(ecg.data, 100);
			ECG ecgFilteredA;
			ecgFilteredA.drawingColor = Color::Green;
			ecgFilteredA.data = ecg.data;
			for (int i = 0; i < ecg.data.size(); i++)
			{
				ecgFilteredA.data[i] -= filter1Average[i] + 800;
			}

			vector <double> filter1Median = ecg.medianFilter(ecg.medianFilter(ecg.data, 60), 180);
			//vector <double> filter1Median = ecg.medianFilter(ecg.data, 100);
			ECG ecgFilteredM;
			ecgFilteredM.drawingColor = Color::Blue;
			ecgFilteredM.data = ecg.data;
			for (int i = 0; i < ecg.data.size(); i++)
			{
				ecgFilteredM.data[i] -= filter1Median[i] + 1600;
			}

			Drawer d;

			d.add(ecg);
			//d.add(ecgFilteredA);
			//d.add(ecgFilteredM);
			d.addGraph(filter1Average, 0, Color::Green);
			d.addGraph(filter1Median, 0, Color::Blue);

			d.show();
		}
	}
}

void Solver::drawECG()
{
	int cntN = 0, cntA = 0, cntO = 0, cntNoi = 0;

	for (auto it : ECG::reference)
	{
		if (it.second == 'N')
		{
			cntN++;
		}
		if (it.second == 'A')
		{
			cntA++;
		}
		if (it.second == 'O')
		{
			cntO++;
		}
		if (it.second == '~')
		{
			cntNoi++;
		}

		//if (it.second == '~')
		{
			cout << it.first << " " << it.second << "\n";
			ECG ecg;

			ecg.readFromFile("../../../Data/TXTFiltered/" + it.first + ".txt");

			//ecg.data = vector <double>(ecg.data.begin(), ecg.data.begin() + 900);

			if (ecg.data.size() < 8999)
			{
				//continue;
			}

			ECG transform = ecg;
			transform.data.clear();
			transform.data = ECG::rescale(ecg.data, ecg.data.size() / 2);
			transform.drawingColor = sf::Color::Blue;
			for (auto& it : transform.data)
			{
				it -= 1000;
			}

			/*
			ecg.data = vector<double>(ecg.data.begin(), ecg.data.begin() + 8500);

			//vector <double> filter1Average = ecg.averageFilter(ecg.averageFilter(ecg.data, 60), 180);
			vector <double> filter1Average = ecg.averageFilter(ecg.data, 100);
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
			*/

			Drawer d;

			d.add(ecg);
			d.add(transform);

			d.show();

			//cnt++;
		}
	}
}

void Solver::testButterworthFilterSin()
{
	ButterworthFilter btwFilter1;
	ButterworthFilter btwFilter2;

	double rate = 1.0 / 300.0;

	btwFilter1.setParameters(rate, 35, 3);
	btwFilter2.setParameters(rate, 35, 10);

	vector <double> arr;

	for (int i = 0; i < 2000; i++)
	{
		arr.push_back(sin(2.0 * i * rate) + sin(50.0 * i * rate));
	}

	vector <double> filtered1 = btwFilter1.filter(arr);
	vector <double> filtered2 = btwFilter2.filter(arr);

	for (auto& it : filtered1)
	{
		it -= 3;
	}

	for (auto& it : filtered2)
	{
		it -= 6;
	}

	Drawer d;

	ECG e1, e2, e3;

	e1.data = arr; e1.drawingColor = Color::Black;
	e2.data = filtered1; e2.drawingColor = Color::Blue;
	e3.data = filtered2; e3.drawingColor = Color::Green;

	d.add(e1);
	d.add(e2);
	d.add(e3);

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
			btwFilter.setParameters(1.0 / 300.0, 40.0 * M_PI, 12);
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
				//continue;
			}

			/*
			if (ecg.data.size() > 4000)
			{
				ecg.data = vector <double>(ecg.data.begin(), ecg.data.begin() + 4000);
			}
			*/

			// median filter
			ECG ecgMedian;
			ecgMedian.drawingColor = Color::Blue;
			vector <double> filter1 = ecg.medianFilter(ecg.data, 100);
			ecgMedian.data = filter1;
			for (int i = 0; i < filter1.size(); i++)
			{
				filter1[i] =  ecg.data[i] - filter1[i];
			}

			ECG ecgFilteredMedian;
			ecgFilteredMedian.drawingColor = Color::Blue;
			ecgFilteredMedian.data = filter1;
			ecgFilteredMedian.data = ecg.transformPeaks1(0, ecg.data.size());

			// butterworth filter

			ButterworthFilter btw;
			btw.setParameters(1.0 / 300.0, 35.0 * M_PI, 10);
			
			ECG filteredEcg;
			filteredEcg.drawingColor = Color::Green;
			filteredEcg.data = btw.filter(filter1);

			
			vector <int> peaks = filteredEcg.getRPeaks(0, filteredEcg.data.size());

			/*
			ofstream out("../../../Data/RPeaks/" + it.first + ".txt");
			for (auto it : peaks)
			{
				out << it << "\n";
			}
			out.close();
			*/

			Drawer d;

			for (auto& it : ecgFilteredMedian.data)
			{
				it -= 2000;
				// it -= 1000
			}

			for (auto& it : filteredEcg.data)
			{
				it -= 2000;
			}

			d.add(ecg);
			d.add(ecgMedian);
			d.add(ecgFilteredMedian);
			//d.add(filteredEcg);
			for (auto it : peaks)
			{
				//d.addVerticalLine(it);
			}

			d.show();

			/*
			ofstream out("../../../Data/TXTFiltered/" + it.first + ".txt");
			for (auto it : filteredEcg.data)
			{
				out << it << "\n";
			}
			out.close();
			*/
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
		//name = "207";

		// read ECG
		cout << name << "\n";
		ECG ecg(360);

		ecg.readFromFile2("../../../Data/CSV2/" + name + ".csv");
		cout << ecg.data.size() << endl;
		
		// median filter
		vector <double> filter1 = ecg.medianFilter(ecg.data, ecg.numbersPerSecond * 0.35);
		for (int i = 0; i < filter1.size(); i++)
		{
			filter1[i] = ecg.data[i] - filter1[i];
		}

		// butterworth filter

		ButterworthFilter btw;
		btw.setParameters(1.0 / ecg.numbersPerSecond, 40.0 * M_PI, 12);

		ECG filteredEcg(360);
		filteredEcg.drawingColor = Color::Blue;
		filteredEcg.data = btw.filter(filter1);

		vector <int> peaks = filteredEcg.getRPeaks(0, filteredEcg.data.size());
		cout << "find " << peaks.size() << " R peaks\n";

		ofstream peakWriter("../../../Data/CSV2RPeaksOurAlgorithm/" + name + ".txt");
		for (auto it : peaks) {
			peakWriter << it << "\n";
		}
		peakWriter.close();

		//filteredEcg.data = vector<double>(filteredEcg.data.begin(), filteredEcg.data.begin() + 3600);
		//ecg.data = vector<double>(ecg.data.begin(), ecg.data.begin() + 3600);

		/*
		Drawer d;

		for (auto& it : filteredEcg.data)
		{
			it += 1500;
		}

		d.add(ecg);
		d.add(filteredEcg);
		for (auto it : peaks)
		{
			if (it < 3600)
			{
				d.addVerticalLine(it);
			}
		}

		d.show();
		*/
		
		//break;
	}
}

void Solver::drawPart(string ecgPath, string filteredPath, string myPeaksPath, string refPeaksPath, string name, int l, int r)
{
	int mid = (l + r) / 2;

	if (l < 0)
	{
		l = 0;
	}
	if (r >= 650000)
	{
		r = 649999;
	}

	mid -= l;

	int pos;
	double _pos;

	ECG ecgOriginal, ecgFiltered;

	ecgOriginal.readFromFile2(ecgPath);
	ecgFiltered.readFromFile(filteredPath);

	ecgOriginal.data = vector <double>(ecgOriginal.data.begin() + l, ecgOriginal.data.begin() + r);
	ecgFiltered.data = vector <double>(ecgFiltered.data.begin() + l, ecgFiltered.data.begin() + r);

	ecgFiltered.drawingColor = Color::Blue;
	for (auto& it : ecgFiltered.data)
	{
		it -= 3000;
	}

	vector <int> myPeaks, refPeaks;

	ifstream inMy(myPeaksPath);
	while (inMy >> pos)
	{
		if (l <= pos && pos <= r)
		{
			myPeaks.push_back(pos);
		}
	}
	inMy.close();

	int isOkType[50] = { 0 };
	isOkType[1] = isOkType[2] = isOkType[3] = isOkType[4] = isOkType[5] = isOkType[6] = isOkType[7] = isOkType[8] = 1;
	isOkType[9] = isOkType[10] = isOkType[11] = isOkType[12] = isOkType[13] = isOkType[31] = isOkType[34] = isOkType[38] = 1;

	ifstream inRef(refPeaksPath);
	ifstream inRefType("../../../Data/CSVatr/" + name + "atr.csv");
	while (inRef >> _pos)
	{
		int tp;
		inRefType >> tp;
		pos = _pos * 360.0;
		if (l <= pos && pos <= r)
		{
			if (isOkType[tp] == 1)
			{
				refPeaks.push_back(pos);
			}
		}
	}
	inRef.close();

	Drawer d;

	
	for (auto it : myPeaks)
	{
		d.addVerticalLine(it - l, Color::Green);
	}
	for (auto it : refPeaks)
	{
		d.addVerticalLine(it - l - 3, Color::Red);
		d.addVerticalLine(it - l + 3, Color::Red);
		//d.addVerticalLine(it - l, Color::Red);
	}
	//d.addVerticalLine(mid - 15, Color::Magenta);
	//d.addVerticalLine(mid + 15, Color::Magenta);
	d.add(ecgOriginal);
	d.add(ecgFiltered);

	d.show();
}

void Solver::drawPartWrap()
{
	string name = "104";
	string pathECG = "../../../Data/CSV2/" + name + ".csv";
	string pathFilt = "../../../Data/CSV2Filtered/" + name + ".txt";

	int val = 113700;

	drawPart(pathECG, pathFilt, "", "", name, val - 2500, val + 2500);
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

	int isOkType[50] = { 0 };
	isOkType[1] = isOkType[2] = isOkType[3] = isOkType[4] = isOkType[5] = isOkType[6] = isOkType[7] = isOkType[8] = 1;
	isOkType[9] = isOkType[10] = isOkType[11] = isOkType[12] = isOkType[13] = isOkType[31] = isOkType[34] = isOkType[38] = 1;

	for (auto name : records)
	{
		//ecg.readFromFile2("../../../Data/CSV2/" + name + ".csv");
		//cout << ecg.data.size() << endl;

		//name = "114";

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

			if (isOkType[tp] == 1)
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

		// erase start and end
		while (peaks.size() != 0 && *peaks.begin() < 360)
		{
			peaks.erase(peaks.begin());
		}
		while (peaks.size() != 0 && *(--peaks.end()) > 650000 - 360)
		{
			peaks.erase(--peaks.end());
		}
		while (reference.size() != 0 && *reference.begin() < 360)
		{
			reference.erase(reference.begin());
		}
		while (reference.size() != 0 && *(--reference.end()) > 650000 - 360)
		{
			reference.erase(--reference.end());
		}

		fp = peaks.size();
		fn = reference.size();
		
		cout << "name=" << name << "   \tok = " << ok << "   \tfp = " << fp << "   \tfn = " << fn << "\n";

		/*
		cout << "fp:\n";
		for (auto it : peaks)
		{
			cout << it << " ";

			drawPart("../../../Data/CSV2/" + name + ".csv", "../../../Data/CSV2Filtered/" + name + ".txt", 
				"../../../Data/CSV2RPeaksOurAlgorithm/" + name + ".txt", "../../../Data/CSVatrTime/" + name + "atr.csv", name, it - 2000, it + 2000);
		}
		cout << "\n";

		
		cout << "fn:\n";
		for (auto it : reference)
		{
			cout << it << " ";

			drawPart("../../../Data/CSV2/" + name + ".csv", "../../../Data/CSV2Filtered/" + name + ".txt",
				"../../../Data/CSV2RPeaksOurAlgorithm/" + name + ".txt", "../../../Data/CSVatrTime/" + name + "atr.csv", name, it - 2000, it + 2000);
		}
		cout << "\n";
		*/

		//break;
	}
}

void Solver::showAllTypes()
{
	string ts;
	vector<string> records;

	ifstream in("../../../Data/CSV2/RECORDS");

	while (in >> ts)
	{
		records.push_back(ts);
	}

	in.close();

	set <int> allTypes;
	map<int, int> cntTypes;

	for (auto name : records)
	{
		//ecg.readFromFile2("../../../Data/CSV2/" + name + ".csv");
		//cout << ecg.data.size() << endl;

		//name = "109";

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

			cntTypes[tp]++;

			/*
			if (tp == 38)
			{
				drawPart("../../../Data/CSV2/" + name + ".csv", "../../../Data/CSV2Filtered/" + name + ".txt",
					"../../../Data/CSV2RPeaksOurAlgorithm/" + name + ".txt", "../../../Data/CSVatrTime/" + name + "atr.csv", val - 1000, val + 1000);
			}
			*/

			if (allTypes.find(tp) == allTypes.end())
			{
				allTypes.insert(tp);

				cout << "type == " << tp << "\n\n";
				drawPart("../../../Data/CSV2/" + name + ".csv", "../../../Data/CSV2Filtered/" + name + ".txt",
					"../../../Data/CSV2RPeaksOurAlgorithm/" + name + ".txt", "../../../Data/CSVatrTime/" + name + "atr.csv", name, val - 1000, val + 1000);
			}
		}
		inRef.close();
		inRefType.close();
	}

	for (auto it : cntTypes)
	{
		cout << it.first << " " << it.second << "\n";
	}
}

void Solver::computeRPeaksDetectionResults()
{
	cout << "Start working\n";

	vector <string> records;
	string ts;

	cout << "Start reading record\n";

	ifstream inNames("../../../Data/CSV2/RECORDS");
	while (inNames >> ts)
	{
		records.push_back(ts);
	}
	inNames.close();

	cout << "End reading record\n";

	int tn, val, tp;
	double td, _val;
	vector <double> pars[5];

	cout << "Start reading parameters\n";

	ifstream inParams("../Parameters/parameters.txt");

	for (int i = 0; i < 5; i++)
	{
		inParams >> tn;
		for (int j = 0; j < tn; j++)
		{
			inParams >> td;
			pars[i].push_back(td);
		}
	}

	inParams.close();

	cout << "End reading parameters\n";

	TasksQueue workerSupervisor;

	ButterworthFilter btw;
	btw.setParameters(1.0 / 360.0, 35 * M_PI, 10);

	int isOkType[50] = { 0 };
	isOkType[1] = isOkType[2] = isOkType[3] = isOkType[4] = isOkType[5] = isOkType[6] = isOkType[7] = isOkType[8] = 1;
	isOkType[9] = isOkType[10] = isOkType[11] = isOkType[12] = isOkType[13] = isOkType[31] = isOkType[34] = isOkType[38] = 1;

	cout << "Start reading ECG data and filter it\n";

	for (auto name : records)
	{
		// read and set ECG
		ECG ecg(360);
		ecg.readFromFile2("../../../Data/CSV2/" + name + ".csv");

		vector <double> filter1 = ecg.medianFilter(ecg.data, ecg.numbersPerSecond * 0.35);
		for (int i = 0; i < filter1.size(); i++)
		{
			filter1[i] = ecg.data[i] - filter1[i];
		}

		ecg.data = btw.filter(filter1);

		workerSupervisor.filteredData[name] = ecg.data;

		// read and set reference peaks
		vector <int> referencePeaks;
		ifstream inRef("../../../Data/CSVatrTime/" + name + "atr.csv");
		ifstream inRefType("../../../Data/CSVatr/" + name + "atr.csv");
		while (inRef >> _val)
		{
			inRefType >> tp;
			val = _val * 360;

			if (isOkType[tp] == 1)
			{
				referencePeaks.push_back(val);
			}
		}
		inRef.close();
		inRefType.close();

		workerSupervisor.referencePeaks[name] = referencePeaks;

		// set all tasks
		for (auto par0 : pars[0])
		{
			for (auto par1 : pars[1])
			{
				for (auto par2 : pars[2])
				{
					for (auto par3 : pars[3])
					{
						for (auto par4 : pars[4])
						{
							vector <double> params;

							params.push_back(par0);
							params.push_back(par1);
							params.push_back(par2);
							params.push_back(par3);
							params.push_back(par4);

							workerSupervisor.addTask(name, params);
						}
					}
				}
			}
		}

		cout << "Readed, filtered and created tasks for " << name << "\n";
	}

	cout << "End reading ECG data and filter it\n";

	cout << "Start making tasks\n";

	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	workerSupervisor.run(8);

	while (!workerSupervisor.workDone())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	workerSupervisor.stop();

	cout << "End making tasks\n";

	cout << "Start writing results\n";

	workerSupervisor.showResults("../Parameters/results.txt");

	cout << "End writing results\n";

	cout << "End working\n";
}

void Solver::analyzeComputedStats1()
{
	set <string> names;
	vector <pair<string, pair<vector<double>, vector <int> > > > allStats;

	ifstream in("../Parameters/results.txt");
	string ts;

	while (in >> ts)
	{
		double p0, p1, p2, p3, p4;
		in >> p0 >> p1 >> p2 >> p3 >> p4;

		int ok, fp, fn;
		in >> ok >> fp >> fn;

		vector <double> params;
		params.push_back(p0);
		params.push_back(p1);
		params.push_back(p2);
		params.push_back(p3);
		params.push_back(p4);

		vector <int> res;
		res.push_back(ok);
		res.push_back(fp);
		res.push_back(fn);

		allStats.push_back({ ts, {params, res} });

		names.insert(ts);
	}

	in.close();

	map<string, pair<int, int> > minFp, minFn, minSum;

	for (auto name : names)
	{
		minFp[name] = { 1000000, -1 };
		minFn[name] = { 1000000, -1 };
		minSum[name] = { 1000000, -1 };
	}

	for (int i = 0; i < allStats.size(); i++)
	{
		auto it = allStats[i];

		if (minFp[it.first].first > it.second.second[1])
		{
			minFp[it.first] = { it.second.second[1], i };
		}

		if (minFn[it.first].first > it.second.second[2])
		{
			minFn[it.first] = { it.second.second[2], i };
		}

		if (minSum[it.first].first > it.second.second[1] + it.second.second[2])
		{
			minSum[it.first] = { it.second.second[1] + it.second.second[2], i };
		}
	}

	for (auto name : names)
	{
		cout << "results for name = " << name << "\n";
		vector <double> tps;
		vector <int> trs;

		tps = allStats[minFp[name].second].second.first;
		trs = allStats[minFp[name].second].second.second;
		cout << "fp: ok = " << trs[0] << "   fp = " << trs[1] << "   fn = " << trs[2];
		cout << "  (" << tps[0] << " " << tps[1] << " " << tps[2] << " " << tps[3] << " " << tps[4] << ")\n";

		tps = allStats[minFn[name].second].second.first;
		trs = allStats[minFn[name].second].second.second;
		cout << "fn: ok = " << trs[0] << "   fp = " << trs[1] << "   fn = " << trs[2];
		cout << "  (" << tps[0] << " " << tps[1] << " " << tps[2] << " " << tps[3] << " " << tps[4] << ")\n";

		tps = allStats[minSum[name].second].second.first;
		trs = allStats[minSum[name].second].second.second;
		cout << "sm: ok = " << trs[0] << "   fp = " << trs[1] << "   fn = " << trs[2];
		cout << "  (" << tps[0] << " " << tps[1] << " " << tps[2] << " " << tps[3] << " " << tps[4] << ")\n";

		cout << "\n\n";
	}

}

void Solver::analyzeComputedStats2()
{
	cout << "\n\n-------------------------------------------------\n\n";

	set <string> names;

	vector <pair<string, pair<vector<double>, vector <int> > > > allStats;

	ifstream in("../Parameters/results.txt");
	string ts;

	while (in >> ts)
	{
		double p0, p1, p2, p3, p4;
		in >> p0 >> p1 >> p2 >> p3 >> p4;

		int ok, fp, fn;
		in >> ok >> fp >> fn;

		if (ts == "203" || ts == "207" || ts == "208" || ts == "210" || ts == "228" || ts == "232" || ts == "223"
			|| ts == "104" || ts == "105" || ts == "106" || ts == "108" || ts == "109" || ts == "111" || ts == "201")
		{
			continue;
		}

		vector <double> params;
		params.push_back(p0);
		params.push_back(p1);
		params.push_back(p2);
		params.push_back(p3);
		params.push_back(p4);

		vector <int> res;
		res.push_back(ok);
		res.push_back(fp);
		res.push_back(fn);

		allStats.push_back({ ts, {params, res} });

		names.insert(ts);
	}

	in.close();

	reverse(allStats.begin(), allStats.end());

	map<vector <double>, double> sumStats;

	for (auto it : allStats)
	{
		vector <int> stats = it.second.second;
		double errP = (stats[1] + stats[2]) / double(stats[0] + stats[1] + stats[2]);

		sumStats[it.second.first] += errP;
	}

	for (auto& it : sumStats)
	{
		it.second = it.second * 100.0 / names.size();
	}

	double mn = 10000;
	vector <double> bestSumParams;

	for (auto it : sumStats)
	{
		if (mn > it.second)
		{
			mn = it.second;
			bestSumParams = it.first;
		}
	}

	cout << "Best persentage = " << mn << "%\n";
	cout << "Params = " << bestSumParams[0] << " " << bestSumParams[1] << " " << bestSumParams[2] << " "
		<< bestSumParams[3] << " " << bestSumParams[4] << "\n\n";

	for (auto it : allStats)
	{
		if (it.second.first == bestSumParams)
		{
			string name = it.first;
			vector <int> stats = it.second.second;

			cout << name << "+  ";

			double errP = (stats[1] + stats[2]) / double(stats[0] + stats[1] + stats[2]) * 100.0;

			cout.precision(5);
			cout << "ok = " << stats[0] << "  fp = " << stats[1] << "  fn = " << stats[2] << "   " << fixed << errP << "%\n";
		}
	}
}

void Solver::analyzeComputedStats3()
{
	cout << "\n\n-------------------------------------------------\n\n";

	set <string> names;
	names.insert("100"); names.insert("101"); names.insert("103"); names.insert("109"); names.insert("113");
	names.insert("114"); names.insert("115"); names.insert("116"); names.insert("117"); names.insert("119");
	names.insert("122"); names.insert("123"); names.insert("124"); names.insert("201"); names.insert("202");
	names.insert("205"); names.insert("209"); names.insert("213"); names.insert("219"); names.insert("220");
	names.insert("221"); names.insert("222"); names.insert("230"); names.insert("231"); names.insert("234");

	vector <pair<string, pair<vector<double>, vector <int> > > > allStats;

	ifstream in("../Parameters/results.txt");
	string ts;

	while (in >> ts)
	{
		double p0, p1, p2, p3, p4;
		in >> p0 >> p1 >> p2 >> p3 >> p4;

		int ok, fp, fn;
		in >> ok >> fp >> fn;

		vector <double> params;
		params.push_back(p0);
		params.push_back(p1);
		params.push_back(p2);
		params.push_back(p3);
		params.push_back(p4);

		vector <int> res;
		res.push_back(ok);
		res.push_back(fp);
		res.push_back(fn);

		allStats.push_back({ ts, {params, res} });
	}

	in.close();

	reverse(allStats.begin(), allStats.end());

	map<vector <double>, double> sumStats;

	for (auto it : allStats)
	{
		if (names.find(it.first) != names.end())
		{
			vector <int> stats = it.second.second;
			double errP = (stats[1] + stats[2]) / double(stats[0] + stats[2]);

			sumStats[it.second.first] += errP;
		}
	}

	for (auto& it : sumStats)
	{
		it.second = it.second * 100.0 / names.size();
	}

	double mn = 10000;
	vector <double> bestSumParams;

	for (auto it : sumStats)
	{
		if (mn > it.second)
		{
			mn = it.second;
			bestSumParams = it.first;
		}
	}

	cout << "Best persentage = " << mn << "%\n";
	cout << "Params = " << bestSumParams[0] << " " << bestSumParams[1] << " " << bestSumParams[2] << " "
		<< bestSumParams[3] << " " << bestSumParams[4] << "\n\n";

	for (auto it : allStats)
	{
		if (it.second.first == bestSumParams)
		{
			string name = it.first;
			vector <int> stats = it.second.second;

			if (names.find(name) != names.end())
			{
				cout << name << "+  ";
			}
			else
			{
				continue;
			}

			double errP = (stats[1] + stats[2]) / double(stats[0] + stats[2]) * 100.0;

			cout.precision(5);
			cout << "ok = " << stats[0] << "  fp = " << stats[1] << "  fn = " << stats[2] << "   " << fixed << errP << "%\n";
		}
	}
}

void Solver::makeDataForNoisyClasification()
{
	vector <string> listN, listA, listO, listNo;

	for (auto it : ECG::reference)
	{
		if (it.second == 'N')
		{
			listN.push_back(it.first);
		}
		if (it.second == 'A')
		{
			listA.push_back(it.first);
		}
		if (it.second == 'O')
		{
			listO.push_back(it.first);
		}
		if (it.second == '~')
		{
			listNo.push_back(it.first);
		}
	}

	ofstream out("../../../../NonGitData/NoisyClasification/data4Types.txt");
	ofstream out2("../../../../NonGitData/NoisyClasification/type4Types.txt");
	// structure: 900 numbers from ECG
	// type of ECG (0 - not noisy, 1 - noisy)

	random_shuffle(listN.begin(), listN.end());
	random_shuffle(listA.begin(), listA.end());
	random_shuffle(listO.begin(), listO.end());
	random_shuffle(listNo.begin(), listNo.end());

	cout << listN.size() << " " << listA.size() << " " << listO.size() << " " << listNo.size() << "\n\n";

	//listN.resize(500);
	//listA.resize(250);
	//listO.resize(350);
	
	for (auto it : listN)
	{
		cout << it << " N\n";
		ECG ecg;

		ecg.readFromFile("../../../Data/TXTFiltered/" + it + ".txt");

		for (int i = 900; i <= ecg.data.size(); i += 900)
		{
			vector <double> data = vector<double>(ecg.data.begin() + (i - 900), ecg.data.begin() + i);

			out << data[0];
			for (int j = 1; j < data.size(); j++)
			{
				out << " " << data[j];
			}
			out << "\n";
			out2 << "0\n";
		}
	}

	for (auto it : listA)
	{
		cout << it << " A\n";
		ECG ecg;

		ecg.readFromFile("../../../Data/TXTFiltered/" + it + ".txt");

		for (int i = 900; i <= ecg.data.size(); i += 900)
		{
			vector <double> data = vector<double>(ecg.data.begin() + (i - 900), ecg.data.begin() + i);

			out << data[0];
			for (int j = 1; j < data.size(); j++)
			{
				out << " " << data[j];
			}
			out << "\n";
			out2 << "1\n";
		}
	}

	for (auto it : listO)
	{
		cout << it << " O\n";
		ECG ecg;

		ecg.readFromFile("../../../Data/TXTFiltered/" + it + ".txt");

		for (int i = 900; i <= ecg.data.size(); i += 900)
		{
			vector <double> data = vector<double>(ecg.data.begin() + (i - 900), ecg.data.begin() + i);

			out << data[0];
			for (int j = 1; j < data.size(); j++)
			{
				out << " " << data[j];
			}
			out << "\n";
			out2 << "2\n";
		}
	}

	for (auto it : listNo)
	{
		cout << it << " ~\n";
		ECG ecg;

		ecg.readFromFile("../../../Data/TXTFiltered/" + it + ".txt");

		for (int i = 900; i <= ecg.data.size(); i += 900)
		{
			vector <double> data = vector<double>(ecg.data.begin() + (i - 900), ecg.data.begin() + i);

			out << data[0];
			for (int j = 1; j < data.size(); j++)
			{
				out << " " << data[j];
			}
			out << "\n";
			out2 << "3\n";
		}
	}
}

void Solver::makeDataForNoisyClasification2()
{
	vector <pair<string, pair<int, int> > > info; // name, start, type
	info.push_back({ "A00001" ,{1800, 1} });
	info.push_back({ "A00002" ,{5400, 1} });
	info.push_back({ "A00011" ,{2500, 1} });
	info.push_back({ "A00032" ,{1500, 1} });
	info.push_back({ "A00050" ,{700, 1} });

	info.push_back({ "A02073" ,{700, 0} });
	info.push_back({ "A02110" ,{700, 0} });
	info.push_back({ "A02111" ,{1500, 0} });
	info.push_back({ "A02122" ,{1500, 0} });
	info.push_back({ "A02125" ,{1500, 0} });

	ofstream out("../../../../NonGitData/NoisyClasification/dataManual.txt");
	ofstream out2("../../../../NonGitData/NoisyClasification/typeManual.txt");
	// structure: 900 numbers from ECG
	// type of ECG (0 - not noisy, 1 - noisy)

	for (auto it : info)
	{
		ECG ecg;

		ecg.readFromFile("../../../Data/TXTFiltered/" + it.first + ".txt");

		vector <double> data = vector<double>(ecg.data.begin() + it.second.first, ecg.data.begin() + it.second.first + 900);

		out << data[0];
		for (int j = 1; j < data.size(); j++)
		{
			out << " " << data[j];
		}
		out << "\n";
		out2 << it.second.second << "\n";
	}
}

void Solver::makeDataForNoisyClasification3()
{
	vector <string> listN, listA, listO, listNo;

	for (auto it : ECG::reference)
	{
		if (it.second == 'N')
		{
			listN.push_back(it.first);
		}
		if (it.second == 'A')
		{
			listA.push_back(it.first);
		}
		if (it.second == 'O')
		{
			listO.push_back(it.first);
		}
		if (it.second == '~')
		{
			listNo.push_back(it.first);
		}
	}
	
	/*
	ofstream out("../../../../NonGitData/NoisyClasification/dataAF_Normal.txt");
	ofstream out2("../../../../NonGitData/NoisyClasification/typeAF_Normal.txt");
	ofstream out3("../../../../NonGitData/NoisyClasification/namesAF_Normal.txt");
	ofstream outV("../../../../NonGitData/NoisyClasification/dataValidationAF_Normal.txt");
	ofstream out2V("../../../../NonGitData/NoisyClasification/typeValidationAF_Normal.txt");
	ofstream out3V("../../../../NonGitData/NoisyClasification/nameValidationAF_Normal.txt");
	// structure: 900 numbers from ECG
	// type of ECG (0 - not noisy, 1 - noisy)
	
	random_shuffle(listN.begin(), listN.end());
	random_shuffle(listA.begin(), listA.end());
	random_shuffle(listO.begin(), listO.end());
	random_shuffle(listNo.begin(), listNo.end());
	*/

	cout << listN.size() << " " << listA.size() << " " << listO.size() << " " << listNo.size() << "\n\n";
	
	/*
	//listN.resize(400);
	//listA.resize(200);
	//listO.resize(200);

	int cntN = 0;
	for (auto it : listN)
	{
		if (cntN > 840 + 600)
		{
			continue;
		}

		cout << it << " N\n";
		ECG ecg;

		ecg.readFromFile("../../../Data/TXTFiltered/" + it + ".txt");

		if (cntN < 840)
		{
			for (int i = 900; i <= ecg.data.size(); i += 900)
			{
				out3 << it << "\n";

				vector <double> data = vector<double>(ecg.data.begin() + (i - 900), ecg.data.begin() + i);

				out << data[0];
				for (int j = 1; j < data.size(); j++)
				{
					out << " " << data[j];
				}
				out << "\n";
				out2 << "0\n";
			}
		}
		else if (cntN < 840 + 600)
		{
			for (int i = 900; i <= ecg.data.size(); i += 900)
			{
				out3V << it << "\n";

				vector <double> data = vector<double>(ecg.data.begin() + (i - 900), ecg.data.begin() + i);

				outV << data[0];
				for (int j = 1; j < data.size(); j++)
				{
					outV << " " << data[j];
				}
				outV << "\n";
				out2V << "0\n";
			}
		}

		cntN++;
	}

	int cntA = 0;
	for (auto it : listA)
	{
		if (cntA > 420 + 300)
		{
			continue;
		}

		cout << it << " A\n";
		ECG ecg;

		ecg.readFromFile("../../../Data/TXTFiltered/" + it + ".txt");

		if (cntA < 420)
		{
			for (int i = 900; i <= ecg.data.size(); i += 900)
			{
				out3 << it << "\n";

				vector <double> data = vector<double>(ecg.data.begin() + (i - 900), ecg.data.begin() + i);

				out << data[0];
				for (int j = 1; j < data.size(); j++)
				{
					out << " " << data[j];
				}
				out << "\n";
				out2 << "1\n";
			}
		}
		else if(cntA < 420 + 300)
		{
			for (int i = 900; i <= ecg.data.size(); i += 900)
			{
				out3V << it << "\n";

				vector <double> data = vector<double>(ecg.data.begin() + (i - 900), ecg.data.begin() + i);

				outV << data[0];
				for (int j = 1; j < data.size(); j++)
				{
					outV << " " << data[j];
				}
				outV << "\n";
				out2V << "1\n";
			}
		}

		cntA++;
	}
	*/

	/*
	for (auto it : listO)
	{
		cout << it << " O\n";
		ECG ecg;

		ecg.readFromFile("../../../Data/TXT/" + it + ".txt");

		for (int i = 1300; i <= ecg.data.size(); i += 900)
		{
			vector <double> data = vector<double>(ecg.data.begin() + (i - 900), ecg.data.begin() + i);

			out << data[0];
			for (int j = 1; j < data.size(); j++)
			{
				out << " " << data[j];
			}
			out << "\n";
			out2 << "0\n";
		}

		for (int i = 900; i <= ecg.data.size(); i += 900)
		{
			vector <double> data = vector<double>(ecg.data.begin() + (i - 900), ecg.data.begin() + i);

			outV << data[0];
			for (int j = 1; j < data.size(); j++)
			{
				outV << " " << data[j];
			}
			outV << "\n";
			out2V << "0\n";
		}
	}
	*/

	/*
	for (auto it : listNo)
	{
		cout << it << " ~\n";
		ECG ecg;

		ecg.readFromFile("../../../Data/TXT/" + it + ".txt");

		for (int i = 1300; i <= ecg.data.size(); i += 900)
		{
			vector <double> data = vector<double>(ecg.data.begin() + (i - 900), ecg.data.begin() + i);

			out << data[0];
			for (int j = 1; j < data.size(); j++)
			{
				out << " " << data[j];
			}
			out << "\n";
			out2 << "1\n";
		}

		for (int i = 900; i <= ecg.data.size(); i += 900)
		{
			vector <double> data = vector<double>(ecg.data.begin() + (i - 900), ecg.data.begin() + i);

			outV << data[0];
			for (int j = 1; j < data.size(); j++)
			{
				outV << " " << data[j];
			}
			outV << "\n";
			out2V << "1\n";
		}
	}
	*/
}

void Solver::makeDataForNoisyModel()
{
	ofstream out("../../../../NonGitData/NoisyClasification/dataUnfilteredForTrainedModel.txt");
	ofstream outName("../../../../NonGitData/NoisyClasification/nameUnfilteredForTrainedModel.txt");

	for (auto it : ECG::reference)
	{
		cout << it.first << " " << it.second << "\n";
		ECG ecg;

		ecg.readFromFile("../../../Data/TXT/" + it.first + ".txt");

		for (int i = 900; i <= ecg.data.size(); i += 900)
		{
			vector <double> data = vector<double>(ecg.data.begin() + (i - 900), ecg.data.begin() + i);

			out << data[0];
			for (int j = 1; j < data.size(); j++)
			{
				out << " " << data[j];
			}
			out << "\n";
			outName << it.first << "\n";
		}
	}
}

void Solver::makeDataAFvsNormalScaled()
{
	vector <string> listN, listA, listO, listNo;

	for (auto it : ECG::reference)
	{
		if (it.second == 'N')
		{
			listN.push_back(it.first);
		}
		if (it.second == 'A')
		{
			listA.push_back(it.first);
		}
		if (it.second == 'O')
		{
			listO.push_back(it.first);
		}
		if (it.second == '~')
		{
			listNo.push_back(it.first);
		}
	}

	ofstream out("../../../../NonGitData/NoisyClasification/dataAF_NormalScaled.txt");
	ofstream out2("../../../../NonGitData/NoisyClasification/typeAF_NormalScaled.txt");
	ofstream out3("../../../../NonGitData/NoisyClasification/namesAF_NormalScaled.txt");
	ofstream outV("../../../../NonGitData/NoisyClasification/dataValidationAF_NormalScaled.txt");
	ofstream out2V("../../../../NonGitData/NoisyClasification/typeValidationAF_NormalScaled.txt");
	ofstream out3V("../../../../NonGitData/NoisyClasification/nameValidationAF_NormalScaled.txt");
	// structure: 900 numbers from ECG
	// type of ECG (0 - mormal, 1 - AF)

	random_shuffle(listN.begin(), listN.end());
	random_shuffle(listA.begin(), listA.end());
	random_shuffle(listO.begin(), listO.end());
	random_shuffle(listNo.begin(), listNo.end());

	cout << listN.size() << " " << listA.size() << " " << listO.size() << " " << listNo.size() << "\n\n";

	//listN.resize(400);
	//listA.resize(200);
	//listO.resize(200);

	int cntN = 0;
	for (auto it : listN)
	{
		if (cntN > 840 + 600)
		{
			continue;
		}

		cout << it << " N\n";
		ECG ecg;

		if (cntN < 840)
		{
			ecg.readFromFile("../../../Data/TXTFiltered/" + it + ".txt");
			vector <int> rPeaks = ecg.getRPeaks(0, ecg.data.size());

			for (int i = 4; i < rPeaks.size(); i += 4)
			{
				vector <double> data;
				for (int j = rPeaks[i - 4]; j < rPeaks[i]; j++)
				{
					data.push_back(ecg.data[j]);
				}

				vector <double> scaledData = ECG::rescale(data, 900);

				out3 << it << "\n";

				out << scaledData[0];
				for (int j = 1; j < scaledData.size(); j++)
				{
					out << " " << scaledData[j];
				}
				out << "\n";
				out2 << "0\n";
			}
		}
		else if (cntN < 840 + 600)
		{
			ecg.readFromFile("../../../Data/TXTFiltered/" + it + ".txt");
			vector <int> rPeaks = ecg.getRPeaks(0, ecg.data.size());

			for (int i = 4; i < rPeaks.size(); i += 4)
			{
				vector <double> data;
				for (int j = rPeaks[i - 4]; j < rPeaks[i]; j++)
				{
					data.push_back(ecg.data[j]);
				}

				vector <double> scaledData = ECG::rescale(data, 900);

				out3V << it << "\n";

				outV << scaledData[0];
				for (int j = 1; j < scaledData.size(); j++)
				{
					outV << " " << scaledData[j];
				}
				outV << "\n";
				out2V << "0\n";
			}
		}

		cntN++;
	}

	int cntA = 0;
	for (auto it : listA)
	{
		if (cntA > 420 + 300)
		{
			continue;
		}

		cout << it << " A\n";
		ECG ecg;

		ecg.readFromFile("../../../Data/TXTFiltered/" + it + ".txt");

		if (cntA < 420)
		{
			ecg.readFromFile("../../../Data/TXTFiltered/" + it + ".txt");
			vector <int> rPeaks = ecg.getRPeaks(0, ecg.data.size());

			for (int i = 4; i < rPeaks.size(); i += 4)
			{
				vector <double> data;
				for (int j = rPeaks[i - 4]; j < rPeaks[i]; j++)
				{
					data.push_back(ecg.data[j]);
				}

				vector <double> scaledData = ECG::rescale(data, 900);

				out3 << it << "\n";

				out << scaledData[0];
				for (int j = 1; j < scaledData.size(); j++)
				{
					out << " " << scaledData[j];
				}
				out << "\n";
				out2 << "1\n";
			}
		}
		else if (cntA < 420 + 300)
		{
			ecg.readFromFile("../../../Data/TXTFiltered/" + it + ".txt");
			vector <int> rPeaks = ecg.getRPeaks(0, ecg.data.size());

			for (int i = 4; i < rPeaks.size(); i += 4)
			{
				vector <double> data;
				for (int j = rPeaks[i - 4]; j < rPeaks[i]; j++)
				{
					data.push_back(ecg.data[j]);
				}

				vector <double> scaledData = ECG::rescale(data, 900);

				out3V << it << "\n";

				outV << scaledData[0];
				for (int j = 1; j < scaledData.size(); j++)
				{
					outV << " " << scaledData[j];
				}
				outV << "\n";
				out2V << "1\n";
			}
		}

		cntA++;
	}
}

void Solver::combineNoisyPrediction()
{
	ifstream inPrediction("../../../../NonGitData/NoisyClasification/NNOutput/UnFilteredNoisePrediction.txt");
	ifstream inName("../../../../NonGitData/NoisyClasification/NNOutput/nameUnfilteredForTrainedModel.txt");

	map<string, vector <int> > predictions;
	string s;
	double a;

	while (inPrediction >> a)
	{
		inName >> s;
		a += 0.5;

		predictions[s].push_back(int(a));
	}

	int nn = 0, np = 0, pn = 0, pp = 0;

	ifstream inRECORDS("../../../Data/RECORDS.txt");
	string name;

	ofstream outNonNoisy("../../../../NonGitData/NormalClasification/RECORDSAfterNoisy");

	while (inRECORDS >> name)
	{
		char type = ECG::reference[name];

		int cntNoisy = 0;

		for (auto itt : predictions[name])
		{
			if (itt == 1)
			{
				cntNoisy++;
			}
		}

		//if(cntNoisy > 0)
		if (cntNoisy > predictions[name].size() / 2.0) // if we predict as noisy
		{
			if (type == '~')
			{
				pp++;
			}
			else
			{
				np++;
			}
		}
		else
		{
			if (type == '~')
			{
				pn++;
			}
			else
			{
				nn++;
			}

			outNonNoisy << name << "\n";
		}
	}

	cout << "ref = normal  predict = normal: " << nn << "\n";
	cout << "ref = normal  predict = noisy: " << np << "\n";
	cout << "ref = noisy  predict = normal: " << pn << "\n";
	cout << "ref = noisy  predict = noisy: " << pp << "\n";

	double F_1p = 2.0 * double(pp) / (double(np) + double(pn) + 2.0 * double(pp));
	cout << "F_1p = " << F_1p << "\n";
}
