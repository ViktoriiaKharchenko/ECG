#include "Sol4.h"

void Sol4::makeNoi_notNoiData()
{
	const int inpSize = 900;

	mt19937 rng(47);

	vector <string> listN, listA, listO, listI; // I - noIsy
	vector <string> listNv, listAv, listOv, listIv; // I - noIsy

	for (auto it : ECG::reference)
	{
		if (it.second == 'N')
		{
			if (ECG::validNamas.find(it.first) == ECG::validNamas.end())
			{
				listN.push_back(it.first);
			}
			else
			{
				listNv.push_back(it.first);
			}
		}
		if (it.second == 'A')
		{
			if (ECG::validNamas.find(it.first) == ECG::validNamas.end())
			{
				listA.push_back(it.first);
			}
			else
			{
				listAv.push_back(it.first);
			}
		}
		if (it.second == 'O')
		{
			if (ECG::validNamas.find(it.first) == ECG::validNamas.end())
			{
				listO.push_back(it.first);
			}
			else
			{
				listOv.push_back(it.first);
			}
		}
		if (it.second == '~')
		{
			if (ECG::validNamas.find(it.first) == ECG::validNamas.end())
			{
				listI.push_back(it.first);
			}
			else
			{
				listIv.push_back(it.first);
			}
		}
	}

	cout << "List Sizes\n";
	cout << listN.size() << " " << listA.size() << " " << listO.size() << " " << listI.size() << "\n";
	cout << listNv.size() << " " << listAv.size() << " " << listOv.size() << " " << listIv.size() << "\n\n";

	vector <pair<int, int> > bounds;
	vector <double> classes;
	vector <string> names;

	for (auto name : listN)
	{
		ECG ecg;
		ecg.readFromFile("../../../Data/TXT/" + name + ".txt");

		for (int i = 0; i + inpSize <= ecg.data.size(); i += inpSize)
		{
			bounds.push_back({ i, i + inpSize - 1 });
			classes.push_back(0.0);
			names.push_back(name);
		}
	}

	cout << "Finish N\n";

	int normCnt = bounds.size(), acnt = 0, ocnt = 0, noicnt = 0;

	for (auto name : listA)
	{
		ECG ecg;
		ecg.readFromFile("../../../Data/TXT/" + name + ".txt");

		for (int i = 0; i + inpSize <= ecg.data.size(); i += inpSize)
		{
			bounds.push_back({ i, i + inpSize - 1 });
			classes.push_back(0.0);
			names.push_back(name);

			acnt++;
		}
	}
	while (acnt < normCnt)
	{
		int ind = rng() % listA.size();

		string name = listA[ind];

		ECG ecg;
		ecg.readFromFile("../../../Data/TXT/" + name + ".txt");

		int start = rng() % (ecg.data.size() - inpSize + 1);

		bounds.push_back({ start, start + inpSize - 1 });
		classes.push_back(0.0);
		names.push_back(name);

		acnt++;
	}

	cout << "Finish A\n";

	for (auto name : listO)
	{
		ECG ecg;
		ecg.readFromFile("../../../Data/TXT/" + name + ".txt");

		for (int i = 0; i + inpSize <= ecg.data.size(); i += inpSize)
		{
			bounds.push_back({ i, i + inpSize - 1 });
			classes.push_back(0.0);
			names.push_back(name);

			ocnt++;
		}
	}
	while (ocnt < normCnt)
	{
		int ind = rng() % listO.size();

		string name = listO[ind];

		ECG ecg;
		ecg.readFromFile("../../../Data/TXT/" + name + ".txt");

		int start = rng() % (ecg.data.size() - inpSize + 1);

		bounds.push_back({ start, start + inpSize - 1 });
		classes.push_back(0.0);
		names.push_back(name);

		ocnt++;
	}

	cout << "Finish O\n";

	for (auto name : listI)
	{
		ECG ecg;
		ecg.readFromFile("../../../Data/TXT/" + name + ".txt");

		for (int i = 0; i + inpSize <= ecg.data.size(); i += inpSize)
		{
			bounds.push_back({ i, i + inpSize - 1 });
			classes.push_back(1.0);
			names.push_back(name);

			noicnt++;
		}
	}
	while (noicnt < normCnt)
	{
		int ind = rng() % listI.size();

		string name = listI[ind];

		ECG ecg;
		ecg.readFromFile("../../../Data/TXT/" + name + ".txt");

		int start = rng() % (ecg.data.size() - inpSize + 1);

		bounds.push_back({ start, start + inpSize - 1 });
		classes.push_back(1.0);
		names.push_back(name);

		noicnt++;
	}

	cout << "Finish I\n\n";

	map <char, int> cnt;

	for (auto name : names)
	{
		cnt[ECG::reference[name]]++;
	}

	cout << "Final stats:\n";
	cout << cnt['N'] << " " << cnt['A'] << " " << cnt['O'] << " " << cnt['~'] << "\n\n";

	ofstream out("../../../../DataDiplome/noisy_ok_data_1111.csv");
	out.precision(1);

	for (int iter = 0; iter < bounds.size(); iter++)
	{
		ECG ecg;
		ecg.readFromFile("../../../Data/TXT/" + names[iter] + ".txt");

		for (int i = bounds[iter].first; i <= bounds[iter].second; i++)
		{
			out << fixed << ecg.data[i] << ",";
		}
		out << fixed << classes[iter] << "," << names[iter] << "\n";

		if (iter % 100 == 0)
		{
			out.flush();
		}

		if (iter % 1000 == 0)
		{
			cout << "iter = " << iter << "\n";
		}
	}

	out.close();

	cout << "Finish\n";
}

void Sol4::makeNoi_notNoiData_validation()
{
	const int inpSize = 900;

	mt19937 rng(47);

	vector <string> listNv, listAv, listOv, listIv; // I - noIsy

	for (auto it : ECG::reference)
	{
		if (it.second == 'N')
		{
			if (ECG::validNamas.find(it.first) == ECG::validNamas.end())
			{
				
			}
			else
			{
				listNv.push_back(it.first);
			}
		}
		if (it.second == 'A')
		{
			if (ECG::validNamas.find(it.first) == ECG::validNamas.end())
			{
				
			}
			else
			{
				listAv.push_back(it.first);
			}
		}
		if (it.second == 'O')
		{
			if (ECG::validNamas.find(it.first) == ECG::validNamas.end())
			{
				
			}
			else
			{
				listOv.push_back(it.first);
			}
		}
		if (it.second == '~')
		{
			if (ECG::validNamas.find(it.first) == ECG::validNamas.end())
			{
				
			}
			else
			{
				listIv.push_back(it.first);
			}
		}
	}

	cout << "List Sizes\n";
	cout << listNv.size() << " " << listAv.size() << " " << listOv.size() << " " << listIv.size() << "\n\n";

	vector <pair<int, int> > bounds;
	vector <string> names;

	for (auto name : listNv)
	{
		ECG ecg;
		ecg.readFromFile("../../../Data/TXT/" + name + ".txt");

		for (int i = 0; i + inpSize <= ecg.data.size(); i += inpSize)
		{
			bounds.push_back({ i, i + inpSize - 1 });
			names.push_back(name);
		}
	}

	cout << "Finish N\n";

	for (auto name : listAv)
	{
		ECG ecg;
		ecg.readFromFile("../../../Data/TXT/" + name + ".txt");

		for (int i = 0; i + inpSize <= ecg.data.size(); i += inpSize)
		{
			bounds.push_back({ i, i + inpSize - 1 });
			names.push_back(name);
		}
	}

	cout << "Finish A\n";

	for (auto name : listOv)
	{
		ECG ecg;
		ecg.readFromFile("../../../Data/TXT/" + name + ".txt");

		for (int i = 0; i + inpSize <= ecg.data.size(); i += inpSize)
		{
			bounds.push_back({ i, i + inpSize - 1 });
			names.push_back(name);
		}
	}

	cout << "Finish O\n";

	for (auto name : listIv)
	{
		ECG ecg;
		ecg.readFromFile("../../../Data/TXT/" + name + ".txt");

		for (int i = 0; i + inpSize <= ecg.data.size(); i += inpSize)
		{
			bounds.push_back({ i, i + inpSize - 1 });
			names.push_back(name);
		}
	}

	cout << "Finish I\n\n";

	ofstream out("../../../../DataDiplome/noisy_ok_data_validation.csv");
	out.precision(1);

	for (int iter = 0; iter < bounds.size(); iter++)
	{
		ECG ecg;
		ecg.readFromFile("../../../Data/TXT/" + names[iter] + ".txt");

		for (int i = bounds[iter].first; i <= bounds[iter].second; i++)
		{
			out << fixed << ecg.data[i] << ",";
		}
		out << names[iter] << "\n";

		if (iter % 100 == 0)
		{
			out.flush();
		}

		if (iter % 1000 == 0)
		{
			cout << "iter = " << iter << "\n";
		}
	}

	out.close();

	cout << "Finish\n";
}

void Sol4::makeNAO_data()
{
	const int inpSize = 1575;

	mt19937 rng(47);

	vector <string> listN, listA, listO, listI; // I - noIsy
	vector <string> listNv, listAv, listOv, listIv; // I - noIsy

	for (auto it : ECG::reference)
	{
		if (it.second == 'N')
		{
			if (ECG::validNamas.find(it.first) == ECG::validNamas.end())
			{
				listN.push_back(it.first);
			}
			else
			{
				listNv.push_back(it.first);
			}
		}
		if (it.second == 'A')
		{
			if (ECG::validNamas.find(it.first) == ECG::validNamas.end())
			{
				listA.push_back(it.first);
			}
			else
			{
				listAv.push_back(it.first);
			}
		}
		if (it.second == 'O')
		{
			if (ECG::validNamas.find(it.first) == ECG::validNamas.end())
			{
				listO.push_back(it.first);
			}
			else
			{
				listOv.push_back(it.first);
			}
		}
		if (it.second == '~')
		{
			if (ECG::validNamas.find(it.first) == ECG::validNamas.end())
			{
				listI.push_back(it.first);
			}
			else
			{
				listIv.push_back(it.first);
			}
		}
	}

	cout << "List Sizes\n";
	cout << listN.size() << " " << listA.size() << " " << listO.size() << " " << listI.size() << "\n";
	cout << listNv.size() << " " << listAv.size() << " " << listOv.size() << " " << listIv.size() << "\n\n";

	int cntn = 0, cnta = 0, cnto = 0;

	vector <vector <double> > info; // ecg
	vector <double> classes;
	vector <string> names;

	for (auto name : listN)
	{
		ECG ecg;
		ecg.readFromFile("../../../Data/TXTFiltered/" + name + ".txt");
		vector <int> rPeaks = ecg.getRPeaks(0, ecg.data.size());

		for (int i = 7; i < rPeaks.size(); i += 5)
		{
			vector <double> segm;
			segm.reserve(inpSize * 2);

			for (int j = rPeaks[i - 7]; j < rPeaks[i]; j++)
			{
				segm.push_back(ecg.data[j]);
			}

			vector <double> scaledData = ECG::rescale(segm, inpSize);

			info.push_back(scaledData);
			classes.push_back(0.0);
			names.push_back(name);

			cntn++;
		}
	}

	cout << "Finish N\n";

	for (auto name : listA)
	{
		ECG ecg;
		ecg.readFromFile("../../../Data/TXTFiltered/" + name + ".txt");
		vector <int> rPeaks = ecg.getRPeaks(0, ecg.data.size());

		for (int i = 7; i < rPeaks.size(); i++)
		{
			vector <double> segm;
			segm.reserve(inpSize * 2);

			for (int j = rPeaks[i - 7]; j < rPeaks[i]; j++)
			{
				segm.push_back(ecg.data[j]);
			}

			vector <double> scaledData = ECG::rescale(segm, inpSize);

			info.push_back(scaledData);
			classes.push_back(1.0);
			names.push_back(name);

			cnta++;
		}
	}

	cout << "Finish A\n";

	for (auto name : listO)
	{
		ECG ecg;
		ecg.readFromFile("../../../Data/TXTFiltered/" + name + ".txt");
		vector <int> rPeaks = ecg.getRPeaks(0, ecg.data.size());

		for (int i = 7; i < rPeaks.size(); i += 3)
		{
			vector <double> segm;
			segm.reserve(inpSize * 2);

			for (int j = rPeaks[i - 7]; j < rPeaks[i]; j++)
			{
				segm.push_back(ecg.data[j]);
			}

			vector <double> scaledData = ECG::rescale(segm, inpSize);

			info.push_back(scaledData);
			classes.push_back(2.0);
			names.push_back(name);

			cnto++;
		}
	}

	cout << "Finish O\n";

	cout << "Final stats:\n";
	cout << cntn << " " << cnta << " " << cnto << "\n\n";

	ofstream out("../../../../DataDiplome/NAO_data.csv");
	out.precision(1);

	for (int iter = 0; iter < info.size(); iter++)
	{
		for (int i = 0; i <= info[iter].size(); i++)
		{
			out << fixed << info[iter][i] << ",";
		}
		out << fixed << classes[iter] << "," << names[iter] << "\n";

		if (iter % 100 == 0)
		{
			out.flush();
		}

		if (iter % 1000 == 0)
		{
			cout << "iter = " << iter << "\n";
		}
	}

	out.close();

	cout << "Finish\n";
}

void Sol4::makeNAO_data_validation()
{
	const int inpSize = 1575;

	mt19937 rng(47);

	vector <string> listNv, listAv, listOv, listIv; // I - noIsy

	for (auto it : ECG::reference)
	{
		if (it.second == 'N')
		{
			if (ECG::validNamas.find(it.first) == ECG::validNamas.end())
			{
				
			}
			else
			{
				listNv.push_back(it.first);
			}
		}
		if (it.second == 'A')
		{
			if (ECG::validNamas.find(it.first) == ECG::validNamas.end())
			{
				
			}
			else
			{
				listAv.push_back(it.first);
			}
		}
		if (it.second == 'O')
		{
			if (ECG::validNamas.find(it.first) == ECG::validNamas.end())
			{
				
			}
			else
			{
				listOv.push_back(it.first);
			}
		}
		if (it.second == '~')
		{
			if (ECG::validNamas.find(it.first) == ECG::validNamas.end())
			{
				
			}
			else
			{
				listIv.push_back(it.first);
			}
		}
	}

	cout << "List Sizes\n";
	cout << listNv.size() << " " << listAv.size() << " " << listOv.size() << " " << listIv.size() << "\n\n";

	int cntn = 0, cnta = 0, cnto = 0;

	vector <vector <double> > info;
	vector <double> classes;
	vector <string> names;

	for (auto name : listNv)
	{
		ECG ecg;
		ecg.readFromFile("../../../Data/TXTFiltered/" + name + ".txt");
		vector <int> rPeaks = ecg.getRPeaks(0, ecg.data.size());

		for (int i = 7; i < rPeaks.size(); i += 1)
		{
			vector <double> segm;
			segm.reserve(inpSize * 2);

			for (int j = rPeaks[i - 7]; j < rPeaks[i]; j++)
			{
				segm.push_back(ecg.data[j]);
			}

			vector <double> scaledData = ECG::rescale(segm, inpSize);

			info.push_back(scaledData);
			classes.push_back(0.0);
			names.push_back(name);

			cntn++;
		}
	}

	cout << "Finish N\n";

	for (auto name : listAv)
	{
		ECG ecg;
		ecg.readFromFile("../../../Data/TXTFiltered/" + name + ".txt");
		vector <int> rPeaks = ecg.getRPeaks(0, ecg.data.size());

		for (int i = 7; i < rPeaks.size(); i++)
		{
			vector <double> segm;
			segm.reserve(inpSize * 2);

			for (int j = rPeaks[i - 7]; j < rPeaks[i]; j++)
			{
				segm.push_back(ecg.data[j]);
			}

			vector <double> scaledData = ECG::rescale(segm, inpSize);

			info.push_back(scaledData);
			classes.push_back(1.0);
			names.push_back(name);

			cnta++;
		}
	}

	cout << "Finish A\n";

	for (auto name : listOv)
	{
		ECG ecg;
		ecg.readFromFile("../../../Data/TXTFiltered/" + name + ".txt");
		vector <int> rPeaks = ecg.getRPeaks(0, ecg.data.size());

		for (int i = 7; i < rPeaks.size(); i += 1)
		{
			vector <double> segm;
			segm.reserve(inpSize * 2);

			for (int j = rPeaks[i - 7]; j < rPeaks[i]; j++)
			{
				segm.push_back(ecg.data[j]);
			}

			vector <double> scaledData = ECG::rescale(segm, inpSize);

			info.push_back(scaledData);
			classes.push_back(2.0);
			names.push_back(name);

			cnto++;
		}
	}

	cout << "Finish O\n";

	cout << "Final stats:\n";
	cout << cntn << " " << cnta << " " << cnto << "\n\n";

	ofstream out("../../../../DataDiplome/NAO_data_validation.csv");
	out.precision(1);

	for (int iter = 0; iter < info.size(); iter++)
	{
		for (int i = 0; i <= info[iter].size(); i++)
		{
			out << fixed << info[iter][i] << ",";
		}
		out << names[iter] << "\n";

		if (iter % 100 == 0)
		{
			out.flush();
		}

		if (iter % 1000 == 0)
		{
			cout << "iter = " << iter << "\n";
		}
	}

	out.close();

	cout << "Finish\n";
}