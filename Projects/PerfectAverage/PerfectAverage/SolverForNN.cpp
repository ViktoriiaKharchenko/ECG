#include "SolverForNN.h"

void SolverForNN::makeClassificationData()
{
	ofstream out("../../../../NonGitData/NormalClasification/dataScaledForTrainedModel.txt");
	ofstream outName("../../../../NonGitData/NormalClasification/nameScaledForTrainedModel.txt");

	for (auto it : ECG::reference)
	{
		cout << it.first << "\n";

		ECG ecg;

		ecg.readFromFile("../../../Data/TXTFiltered/" + it.first + ".txt");
		vector <int> rPeaks = ecg.getRPeaks(0, ecg.data.size());

		for (int i = 4; i < rPeaks.size(); i += 4)
		{
			vector <double> data;
			for (int j = rPeaks[i - 4]; j < rPeaks[i]; j++)
			{
				data.push_back(ecg.data[j]);
			}

			vector <double> scaledData = ECG::rescale(data, 900);

			out << scaledData[0];
			for (int j = 1; j < scaledData.size(); j++)
			{
				out << " " << scaledData[j];
			}
			out << "\n";

			outName << it.first << "\n";
		}
	}
}

void SolverForNN::makeDataForNvsAF()
{
	vector <string> listN, listA;

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
	}

	ofstream out("../../../../NonGitData/NormalClasification/NvsAFScaled/dataN_AFScaled.txt");
	ofstream out2("../../../../NonGitData/NormalClasification/NvsAFScaled/typeN_AFcaled.txt");
	ofstream outV("../../../../NonGitData/NormalClasification/NvsAFScaled/dataValidationN_AFScaled.txt");
	ofstream out2V("../../../../NonGitData/NormalClasification/NvsAFScaled/typeValidationN_AFScaled.txt");

	random_shuffle(listN.begin(), listN.end());
	random_shuffle(listA.begin(), listA.end());

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

void SolverForNN::makeDataForNvsO()
{
	vector <string> listN, listO;

	for (auto it : ECG::reference)
	{
		if (it.second == 'N')
		{
			listN.push_back(it.first);
		}
		if (it.second == 'O')
		{
			listO.push_back(it.first);
		}
	}

	ofstream out("../../../../NonGitData/NormalClasification/NvsOScaled/dataN_OScaled.txt");
	ofstream out2("../../../../NonGitData/NormalClasification/NvsOScaled/typeN_OScaled.txt");
	ofstream outV("../../../../NonGitData/NormalClasification/NvsOScaled/dataValidationN_OScaled.txt");
	ofstream out2V("../../../../NonGitData/NormalClasification/NvsOScaled/typeValidationN_OScaled.txt");

	random_shuffle(listN.begin(), listN.end());
	random_shuffle(listO.begin(), listO.end());

	int cntN = 0;
	for (auto it : listN)
	{
		if (cntN > 2000 + 1000)
		{
			continue;
		}

		cout << it << " N\n";
		ECG ecg;

		if (cntN < 2000)
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

				out << scaledData[0];
				for (int j = 1; j < scaledData.size(); j++)
				{
					out << " " << scaledData[j];
				}
				out << "\n";
				out2 << "0\n";
			}
		}
		else if (cntN < 2000 + 1000)
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

	int cntO = 0;
	for (auto it : listO)
	{
		if (cntO > 1200 + 800)
		{
			continue;
		}

		cout << it << " O\n";
		ECG ecg;

		if (cntO < 1200)
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

				out << scaledData[0];
				for (int j = 1; j < scaledData.size(); j++)
				{
					out << " " << scaledData[j];
				}
				out << "\n";
				out2 << "1\n";
			}
		}
		else if (cntO < 1200 + 800)
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

				outV << scaledData[0];
				for (int j = 1; j < scaledData.size(); j++)
				{
					outV << " " << scaledData[j];
				}
				outV << "\n";
				out2V << "1\n";
			}
		}

		cntO++;
	}
}

void SolverForNN::makeDataForAFvsO()
{
	vector <string> listA, listO;

	for (auto it : ECG::reference)
	{
		if (it.second == 'N')
		{
			listA.push_back(it.first);
		}
		if (it.second == 'O')
		{
			listO.push_back(it.first);
		}
	}

	ofstream out("../../../../NonGitData/NormalClasification/AFvsOScaled/dataAF_OScaled.txt");
	ofstream out2("../../../../NonGitData/NormalClasification/AFvsOScaled/typeAF_OScaled.txt");
	ofstream outV("../../../../NonGitData/NormalClasification/AFvsOScaled/dataValidationAF_OScaled.txt");
	ofstream out2V("../../../../NonGitData/NormalClasification/AFvsOScaled/typeValidationAF_OScaled.txt");

	random_shuffle(listA.begin(), listA.end());
	random_shuffle(listO.begin(), listO.end());

	int cntA = 0;
	for (auto it : listA)
	{
		if (cntA > 400 + 300)
		{
			continue;
		}

		cout << it << " AF\n";
		ECG ecg;

		if (cntA < 400)
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

				out << scaledData[0];
				for (int j = 1; j < scaledData.size(); j++)
				{
					out << " " << scaledData[j];
				}
				out << "\n";
				out2 << "0\n";
			}
		}
		else if (cntA < 400 + 300)
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

				outV << scaledData[0];
				for (int j = 1; j < scaledData.size(); j++)
				{
					outV << " " << scaledData[j];
				}
				outV << "\n";
				out2V << "0\n";
			}
		}

		cntA++;
	}

	int cntO = 0;
	for (auto it : listO)
	{
		if (cntO > 850 + 650)
		{
			continue;
		}

		cout << it << " O\n";
		ECG ecg;

		if (cntO < 950)
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

				out << scaledData[0];
				for (int j = 1; j < scaledData.size(); j++)
				{
					out << " " << scaledData[j];
				}
				out << "\n";
				out2 << "1\n";
			}
		}
		else if (cntO < 950 + 550)
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

				outV << scaledData[0];
				for (int j = 1; j < scaledData.size(); j++)
				{
					outV << " " << scaledData[j];
				}
				outV << "\n";
				out2V << "1\n";
			}
		}

		cntO++;
	}
}

void SolverForNN::makeDataForNAFvsO()
{
	vector <string> listN, listA, listO;

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
	}

	ofstream out("../../../../NonGitData/NormalClasification/NAFvsOScaled/dataNAF_OScaled.txt");
	ofstream out2("../../../../NonGitData/NormalClasification/NAFvsOScaled/typeNAF_OScaled.txt");
	ofstream outV("../../../../NonGitData/NormalClasification/NAFvsOScaled/dataValidationNAF_OScaled.txt");
	ofstream out2V("../../../../NonGitData/NormalClasification/NAFvsOScaled/typeValidationNAF_OScaled.txt");

	random_shuffle(listN.begin(), listN.end());
	random_shuffle(listA.begin(), listA.end());
	random_shuffle(listO.begin(), listO.end());

	vector <string> mix;
	for (int i = 0; i < 1200; i++)
	{
		mix.push_back(listN[i]);
	}
	for (int i = 0; i < 400; i++)
	{
		mix.push_back(listA[i]);
	}
	for (int i = 1200; i < 2000; i++)
	{
		mix.push_back(listN[i]);
	}
	for (int i = 400; i < 700; i++)
	{
		mix.push_back(listA[i]);
	}
	random_shuffle(mix.begin(), mix.begin() + 1600);
	random_shuffle(mix.begin() + 1600, mix.end());

	int cntM = 0;
	for (auto it : mix)
	{
		if (cntM > 1600 + 1100)
		{
			continue;
		}

		cout << it << " NAF\n";
		ECG ecg;

		if (cntM < 1600)
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

				out << scaledData[0];
				for (int j = 1; j < scaledData.size(); j++)
				{
					out << " " << scaledData[j];
				}
				out << "\n";
				out2 << "0\n";
			}
		}
		else if (cntM < 1600 + 1100)
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

				outV << scaledData[0];
				for (int j = 1; j < scaledData.size(); j++)
				{
					outV << " " << scaledData[j];
				}
				outV << "\n";
				out2V << "0\n";
			}
		}

		cntM++;
	}

	int cntO = 0;
	for (auto it : listO)
	{
		if (cntO > 900 + 600)
		{
			continue;
		}

		cout << it << " O\n";
		ECG ecg;

		if (cntO < 900)
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

				out << scaledData[0];
				for (int j = 1; j < scaledData.size(); j++)
				{
					out << " " << scaledData[j];
				}
				out << "\n";
				out2 << "1\n";
			}
		}
		else if (cntO < 900 + 600)
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

				outV << scaledData[0];
				for (int j = 1; j < scaledData.size(); j++)
				{
					outV << " " << scaledData[j];
				}
				outV << "\n";
				out2V << "1\n";
			}
		}

		cntO++;
	}
}

void SolverForNN::makeDataForNOvsAF()
{
	vector <string> listN, listA, listO;

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
	}

	ofstream out("../../../../NonGitData/NormalClasification/NOvsAFScaled/dataNO_AFScaled.txt");
	ofstream out2("../../../../NonGitData/NormalClasification/NOvsAFScaled/typeNO_AFScaled.txt");
	ofstream outV("../../../../NonGitData/NormalClasification/NOvsAFScaled/dataValidationNO_AFScaled.txt");
	ofstream out2V("../../../../NonGitData/NormalClasification/NOvsAFScaled/typeValidationNO_AFScaled.txt");

	random_shuffle(listN.begin(), listN.end());
	random_shuffle(listA.begin(), listA.end());
	random_shuffle(listO.begin(), listO.end());

	vector <string> mix;
	for (int i = 0; i < 450; i++)
	{
		mix.push_back(listN[i]);
	}
	for (int i = 0; i < 350; i++)
	{
		mix.push_back(listO[i]);
	}
	for (int i = 450; i < 800; i++)
	{
		mix.push_back(listN[i]);
	}
	for (int i = 350; i < 600; i++)
	{
		mix.push_back(listO[i]);
	}
	random_shuffle(mix.begin(), mix.begin() + 800);
	random_shuffle(mix.begin() + 800, mix.end());

	int cntM = 0;
	for (auto it : mix)
	{
		if (cntM > 800 + 600)
		{
			continue;
		}

		cout << it << " NO\n";
		ECG ecg;

		if (cntM < 800)
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

				out << scaledData[0];
				for (int j = 1; j < scaledData.size(); j++)
				{
					out << " " << scaledData[j];
				}
				out << "\n";
				out2 << "0\n";
			}
		}
		else if (cntM < 800 + 600)
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

				outV << scaledData[0];
				for (int j = 1; j < scaledData.size(); j++)
				{
					outV << " " << scaledData[j];
				}
				outV << "\n";
				out2V << "0\n";
			}
		}

		cntM++;
	}

	int cntA = 0;
	for (auto it : listA)
	{
		if (cntA > 400 + 300)
		{
			continue;
		}

		cout << it << " AF\n";
		ECG ecg;

		if (cntA < 400)
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

				out << scaledData[0];
				for (int j = 1; j < scaledData.size(); j++)
				{
					out << " " << scaledData[j];
				}
				out << "\n";
				out2 << "1\n";
			}
		}
		else if (cntA < 400 + 300)
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

void SolverForNN::makeDataForAFOvsN()
{
	vector <string> listN, listA, listO;

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
	}

	ofstream out("../../../../NonGitData/NormalClasification/AFOvsNScaled/dataAFO_NScaled.txt");
	ofstream out2("../../../../NonGitData/NormalClasification/AFOvsNScaled/typeAFO_NScaled.txt");
	ofstream outV("../../../../NonGitData/NormalClasification/AFOvsNScaled/dataValidationAFO_NScaled.txt");
	ofstream out2V("../../../../NonGitData/NormalClasification/AFOvsNScaled/typeValidationAFO_NScaled.txt");

	random_shuffle(listN.begin(), listN.end());
	random_shuffle(listA.begin(), listA.end());
	random_shuffle(listO.begin(), listO.end());

	vector <string> mix;
	for (int i = 0; i < 400; i++)
	{
		mix.push_back(listA[i]);
	}
	for (int i = 0; i < 700; i++)
	{
		mix.push_back(listO[i]);
	}
	for (int i = 400; i < 700; i++)
	{
		mix.push_back(listA[i]);
	}
	for (int i = 700; i < 1300; i++)
	{
		mix.push_back(listO[i]);
	}
	random_shuffle(mix.begin(), mix.begin() + 1100);
	random_shuffle(mix.begin() + 1100, mix.end());

	int cntM = 0;
	for (auto it : mix)
	{
		if (cntM > 1100 + 900)
		{
			continue;
		}

		cout << it << " AFO\n";
		ECG ecg;

		if (cntM < 1100)
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

				out << scaledData[0];
				for (int j = 1; j < scaledData.size(); j++)
				{
					out << " " << scaledData[j];
				}
				out << "\n";
				out2 << "0\n";
			}
		}
		else if (cntM < 1100 + 900)
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

				outV << scaledData[0];
				for (int j = 1; j < scaledData.size(); j++)
				{
					outV << " " << scaledData[j];
				}
				outV << "\n";
				out2V << "0\n";
			}
		}

		cntM++;
	}

	int cntN = 0;
	for (auto it : listN)
	{
		if (cntN > 1100 + 900)
		{
			continue;
		}

		cout << it << " N\n";
		ECG ecg;

		if (cntN < 1100)
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

				out << scaledData[0];
				for (int j = 1; j < scaledData.size(); j++)
				{
					out << " " << scaledData[j];
				}
				out << "\n";
				out2 << "1\n";
			}
		}
		else if (cntN < 1100 + 900)
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

				outV << scaledData[0];
				for (int j = 1; j < scaledData.size(); j++)
				{
					outV << " " << scaledData[j];
				}
				outV << "\n";
				out2V << "1\n";
			}
		}

		cntN++;
	}
}

void SolverForNN::makeDataForNvsAFvsO()
{
	vector <string> listN, listA, listO;

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
	}

	ofstream out("../../../../NonGitData/NormalClasification/NvsAFvsOScaled/dataNvsAFvsOScaled.txt");
	ofstream out2("../../../../NonGitData/NormalClasification/NvsAFvsOScaled/typeNvsAFvsOcaled.txt");
	ofstream outV("../../../../NonGitData/NormalClasification/NvsAFvsOScaled/dataValidationNvsAFvsOScaled.txt");
	ofstream out2V("../../../../NonGitData/NormalClasification/NvsAFvsOScaled/typeValidationNvsAFvsOScaled.txt");

	random_shuffle(listN.begin(), listN.end());
	random_shuffle(listA.begin(), listA.end());
	random_shuffle(listO.begin(), listO.end());

	int cntN = 0;
	for (auto it : listN)
	{
		if (cntN > 1000 + 800)
		{
			continue;
		}

		cout << it << " N\n";
		ECG ecg;

		if (cntN < 1000)
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

				out << scaledData[0];
				for (int j = 1; j < scaledData.size(); j++)
				{
					out << " " << scaledData[j];
				}
				out << "\n";
				out2 << "0\n";
			}
		}
		else if (cntN < 1000 + 800)
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

	int cntO = 0;
	for (auto it : listO)
	{
		if (cntO > 800 + 600)
		{
			continue;
		}

		cout << it << " O\n";
		ECG ecg;

		if (cntO < 800)
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

				out << scaledData[0];
				for (int j = 1; j < scaledData.size(); j++)
				{
					out << " " << scaledData[j];
				}
				out << "\n";
				out2 << "2\n";
			}
		}
		else if (cntO < 800 + 600)
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

				outV << scaledData[0];
				for (int j = 1; j < scaledData.size(); j++)
				{
					outV << " " << scaledData[j];
				}
				outV << "\n";
				out2V << "2\n";
			}
		}

		cntO++;
	}
}