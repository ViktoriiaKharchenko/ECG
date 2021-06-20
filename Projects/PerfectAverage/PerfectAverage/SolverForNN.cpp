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
		if (it.second == 'A')
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
		if (cntO > 950 + 550)
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

int SolverForNN::classify0_filtered(vector <double>& types)
{
	int cnt0 = 0, cnt1 = 0;

	for (auto it : types)
	{
		if (it < 0.5)
		{
			cnt0++;
		}
		else
		{
			cnt1++;
		}
	}

	if (cnt1 > types.size() / 2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int SolverForNN::classify0_unfiltered(vector <double>& types)
{
	int cnt0 = 0, cnt1 = 0;

	for (auto it : types)
	{
		if (it < 0.5)
		{
			cnt0++;
		}
		else
		{
			cnt1++;
		}
	}

	if (cnt1 > types.size() / 2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int SolverForNN::classify1_AFO_vs_N(vector <double>& types)
{
	int cnt0 = 0, cnt1 = 0;

	for (auto it : types)
	{
		if (it < 0.5)
		{
			cnt0++;
		}
		else
		{
			cnt1++;
		}
	}

	if (cnt0 > types.size() * 0.45)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int SolverForNN::classify1_NAF_vs_O(vector <double>& types)
{
	int cnt0 = 0, cnt1 = 0;

	for (auto it : types)
	{
		if (it < 0.5)
		{
			cnt0++;
		}
		else
		{
			cnt1++;
		}
	}

	if (cnt1 > types.size() * 0.20)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int SolverForNN::classify1_NO_vs_AF(vector <double>& types)
{
	int cnt0 = 0, cnt1 = 0;

	for (auto it : types)
	{
		if (it < 0.5)
		{
			cnt0++;
		}
		else
		{
			cnt1++;
		}
	}

	if (cnt1 > types.size() * 0.65)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int SolverForNN::classify2_AF_vs_O(vector <double>& types)
{
	int cnt0 = 0, cnt1 = 0;

	for (auto it : types)
	{
		if (it < 0.5)
		{
			cnt0++;
		}
		else
		{
			cnt1++;
		}
	}

	if (cnt0 > types.size() * 0.50)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int SolverForNN::classify2_N_vs_AF(vector <double>& types)
{
	int cnt0 = 0, cnt1 = 0;

	for (auto it : types)
	{
		if (it < 0.5)
		{
			cnt0++;
		}
		else
		{
			cnt1++;
		}
	}

	if (cnt1 > types.size() * 0.55)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int SolverForNN::classify2_N_vs_O(vector <double>& types)
{
	int cnt0 = 0, cnt1 = 0;

	for (auto it : types)
	{
		if (it < 0.5)
		{
			cnt0++;
		}
		else
		{
			cnt1++;
		}
	}

	if (cnt1 > types.size() * 0.25)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int SolverForNN::classify1_N_vs_AF_vs_O(vector <double>& types)
{
	double cnt[3] = {0, 0, 0};

	for (auto it : types)
	{
		cnt[int(it + 0.5)] += 1.0;
	}

	if (cnt[1] >= cnt[0])
	{
		if (cnt[1] >= cnt[2] * 1.6)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	else
	{
		if (cnt[0] > cnt[2] * 1.9)
		{
			return 0;
		}
		else
		{
			return 2;
		}
	}
}

vector <vector <int> > SolverForNN::tree1()
{
	// ((N vs AF) vs O) vs noisy

	map <string, vector <double> > infNonNoi_vs_Noi;
	map <string, vector <double> > infNAF_vs_O;
	map <string, vector <double> > infN_vs_AF;

	{
		string name;
		double type, type1, type2;

		ifstream inType0("../../../../NonGitData/NormalClasification/ClassificationResults/0_UnfilteredNoisePrediction.txt");
		ifstream inName0("../../../../NonGitData/NormalClasification/ClassificationResults/0_nameUnfilteredForTrainedModel.txt");

		while (inName0 >> name)
		{
			inType0 >> type;

			infNonNoi_vs_Noi[name].push_back(type);
		}
		
		ifstream inType1("../../../../NonGitData/NormalClasification/ClassificationResults/1_NAF_vs_O_model.txt");
		ifstream inType2("../../../../NonGitData/NormalClasification/ClassificationResults/2_N_vs_AF_model.txt");
		ifstream inName1_2("../../../../NonGitData/NormalClasification/ClassificationResults/1_2_nameScaledForTrainedModel.txt");

		while (inName1_2 >> name)
		{
			inType1 >> type1;
			inType2 >> type2;

			infNAF_vs_O[name].push_back(type1);
			infN_vs_AF[name].push_back(type2);
		}
	}

	vector <vector <int> > res(4, vector <int>(4, 0));

	for (auto it : ECG::reference)
	{
		int realType, myType;
		if (it.second == 'N')
		{
			realType = 0;
		}
		else if (it.second == 'A')
		{
			realType = 1;
		}
		else if (it.second == 'O')
		{
			realType = 2;
		}
		else
		{
			realType = 3;
		}

		int class0 = classify0_unfiltered(infNonNoi_vs_Noi[it.first]);
		int class1 = classify1_NAF_vs_O(infNAF_vs_O[it.first]);
		int class2 = classify2_N_vs_AF(infN_vs_AF[it.first]);

		if (class0 == 1)
		{
			myType = 3;
		}
		else
		{
			if (class1 == 1)
			{
				myType = 2;
			}
			else
			{
				if (class2 == 1)
				{
					myType = 1;
				}
				else
				{
					myType = 0;
				}
			}
		}

		res[realType][myType]++;
	}

	return res;
}

vector <vector <int> > SolverForNN::tree2()
{
	// ((N vs O) vs AF) vs noisy

	map <string, vector <double> > infNonNoi_vs_Noi;
	map <string, vector <double> > infNO_vs_AF;
	map <string, vector <double> > infN_vs_O;

	{
		string name;
		double type, type1, type2;

		ifstream inType0("../../../../NonGitData/NormalClasification/ClassificationResults/0_UnfilteredNoisePrediction.txt");
		ifstream inName0("../../../../NonGitData/NormalClasification/ClassificationResults/0_nameUnfilteredForTrainedModel.txt");

		while (inName0 >> name)
		{
			inType0 >> type;

			infNonNoi_vs_Noi[name].push_back(type);
		}

		ifstream inType1("../../../../NonGitData/NormalClasification/ClassificationResults/1_NO_vs_AF_model2.txt");
		ifstream inType2("../../../../NonGitData/NormalClasification/ClassificationResults/2_N_vs_O_model.txt");
		ifstream inName1_2("../../../../NonGitData/NormalClasification/ClassificationResults/1_2_nameScaledForTrainedModel.txt");

		while (inName1_2 >> name)
		{
			inType1 >> type1;
			inType2 >> type2;

			infNO_vs_AF[name].push_back(type1);
			infN_vs_O[name].push_back(type2);
		}
	}

	vector <vector <int> > res(4, vector <int>(4, 0));

	for (auto it : ECG::reference)
	{
		int realType, myType;
		if (it.second == 'N')
		{
			realType = 0;
		}
		else if (it.second == 'A')
		{
			realType = 1;
		}
		else if (it.second == 'O')
		{
			realType = 2;
		}
		else
		{
			realType = 3;
		}

		int class0 = classify0_unfiltered(infNonNoi_vs_Noi[it.first]);
		int class1 = classify1_NO_vs_AF(infNO_vs_AF[it.first]);
		int class2 = classify2_N_vs_O(infN_vs_O[it.first]);

		if (class0 == 1)
		{
			myType = 3;
		}
		else
		{
			if (class1 == 1)
			{
				myType = 1;
			}
			else
			{
				if (class2 == 1)
				{
					myType = 2;
				}
				else
				{
					myType = 0;
				}
			}
		}

		res[realType][myType]++;
	}

	return res;
}

vector <vector <int> > SolverForNN::tree3()
{
	// ((AF vs O) vs N) vs noisy

	map <string, vector <double> > infNonNoi_vs_Noi;
	map <string, vector <double> > infAFO_vs_N;
	map <string, vector <double> > infAF_vs_O;

	{
		string name;
		double type, type1, type2;

		ifstream inType0("../../../../NonGitData/NormalClasification/ClassificationResults/0_UnfilteredNoisePrediction.txt");
		ifstream inName0("../../../../NonGitData/NormalClasification/ClassificationResults/0_nameUnfilteredForTrainedModel.txt");

		while (inName0 >> name)
		{
			inType0 >> type;

			infNonNoi_vs_Noi[name].push_back(type);
		}

		ifstream inType1("../../../../NonGitData/NormalClasification/ClassificationResults/1_AFO_vs_N_model2.txt");
		ifstream inType2("../../../../NonGitData/NormalClasification/ClassificationResults/2_AF_vs_O_model2.txt");
		ifstream inName1_2("../../../../NonGitData/NormalClasification/ClassificationResults/1_2_nameScaledForTrainedModel.txt");

		while (inName1_2 >> name)
		{
			inType1 >> type1;
			inType2 >> type2;

			infAFO_vs_N[name].push_back(type1);
			infAF_vs_O[name].push_back(type2);
		}
	}

	vector <vector <int> > res(4, vector <int>(4, 0));

	for (auto it : ECG::reference)
	{
		int realType, myType;
		if (it.second == 'N')
		{
			realType = 0;
		}
		else if (it.second == 'A')
		{
			realType = 1;
		}
		else if (it.second == 'O')
		{
			realType = 2;
		}
		else
		{
			realType = 3;
		}

		int class0 = classify0_unfiltered(infNonNoi_vs_Noi[it.first]);
		int class1 = classify1_AFO_vs_N(infAFO_vs_N[it.first]);
		int class2 = classify2_AF_vs_O(infAF_vs_O[it.first]);

		if (class0 == 1)
		{
			myType = 3;
		}
		else
		{
			if (class1 == 1)
			{
				myType = 0;
			}
			else
			{
				if (class2 == 1)
				{
					myType = 2;
				}
				else
				{
					myType = 1;
				}
			}
		}

		res[realType][myType]++;
	}

	return res;
}

vector <vector <int> > SolverForNN::tree4()
{
	// (N vs AF vs O) vs noisy

	map <string, vector <double> > infNonNoi_vs_Noi;
	map <string, vector <double> > infN_vs_N_vs_O;

	{
		string name;
		double type, type1;

		ifstream inType0("../../../../NonGitData/NormalClasification/ClassificationResults/0_UnfilteredNoisePrediction.txt");
		ifstream inName0("../../../../NonGitData/NormalClasification/ClassificationResults/0_nameUnfilteredForTrainedModel.txt");

		while (inName0 >> name)
		{
			inType0 >> type;

			infNonNoi_vs_Noi[name].push_back(type);
		}

		ifstream inType1("../../../../NonGitData/NormalClasification/ClassificationResults/1_N_vs_AF_vs_O_model.txt");
		ifstream inName1_2("../../../../NonGitData/NormalClasification/ClassificationResults/1_2_nameScaledForTrainedModel.txt");

		while (inName1_2 >> name)
		{
			inType1 >> type1;

			infN_vs_N_vs_O[name].push_back(type1);
		}
	}

	vector <vector <int> > res(4, vector <int>(4, 0));

	for (auto it : ECG::reference)
	{
		int realType, myType;
		if (it.second == 'N')
		{
			realType = 0;
		}
		else if (it.second == 'A')
		{
			realType = 1;
		}
		else if (it.second == 'O')
		{
			realType = 2;
		}
		else
		{
			realType = 3;
		}

		int class0 = classify0_unfiltered(infNonNoi_vs_Noi[it.first]);
		int class1 = classify1_N_vs_AF_vs_O(infN_vs_N_vs_O[it.first]);

		if (class0 == 1)
		{
			myType = 3;
		}
		else
		{
			myType = class1;
		}

		res[realType][myType]++;
	}

	return res;
}

void SolverForNN::test1_1()
{
	map<string, vector <double> > inf;

	{
		ifstream inType("../../../../NonGitData/NormalClasification/ClassificationResults/1_NO_vs_AF_model2.txt");
		ifstream inName("../../../../NonGitData/NormalClasification/ClassificationResults/1_2_nameScaledForTrainedModel.txt");

		string name;
		double type;

		while (inName >> name)
		{
			inType >> type;

			inf[name].push_back(type);
		}
	}

	int res[2][2] = { {0, 0}, {0, 0} };

	for (auto& it : inf)
	{
		//*
		if (ECG::reference[it.first] == '~')
		{
			continue;
		}
		//*/

		int f = classify1_NO_vs_AF(it.second);
		int ff = ECG::reference[it.first] == 'A';

		res[ff][f]++;
	}

	cout << res[0][0] << " " << res[0][1] << "\n";
	cout << res[1][0] << " " << res[1][1] << "\n";

	double f1_0 = (2.0 * res[0][0]) / (2.0 * res[0][0] + res[1][0] + res[0][1]);
	double f1_1 = (2.0 * res[1][1]) / (2.0 * res[1][1] + res[1][0] + res[0][1]);
	double f1 = (f1_0 + f1_1) / 2.0;

	cout << "f1_0 = " << f1_0 << "\n";
	cout << "f1_1 = " << f1_1 << "\n";
	cout << "f1 = " << f1 << "\n";
}

void SolverForNN::test1_2()
{
	map<string, vector <double> > inf;

	{
		ifstream inType("../../../../NonGitData/NormalClasification/ClassificationResults/1_N_vs_AF_vs_O_model.txt");
		ifstream inName("../../../../NonGitData/NormalClasification/ClassificationResults/1_2_nameScaledForTrainedModel.txt");

		string name;
		double type;

		while (inName >> name)
		{
			inType >> type;

			inf[name].push_back(type);
		}
	}

	int res[3][3] = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };

	for (auto& it : inf)
	{
		if (ECG::reference[it.first] == '~')
		{
			continue;
		}

		int f = classify1_N_vs_AF_vs_O(it.second);
		int ff;
		if (ECG::reference[it.first] == 'N')
		{
			ff = 0;
		}
		else if (ECG::reference[it.first] == 'A')
		{
			ff = 1;
		}
		else
		{
			ff = 2;
		}

		res[ff][f]++;
	}

	cout << res[0][0] << "\t" << res[0][1] << "\t" << res[0][2] << "\n";
	cout << res[1][0] << "\t" << res[1][1] << "\t" << res[1][2] << "\n";
	cout << res[2][0] << "\t" << res[2][1] << "\t" << res[2][2] << "\n";

	double f1_N = (2.0 * res[0][0]) / (2.0 * res[0][0] + res[1][0] + res[2][0] + res[0][1] + res[0][2]);
	double f1_A = (2.0 * res[1][1]) / (2.0 * res[1][1] + res[1][0] + res[1][2] + res[0][1] + res[2][1]);
	double f1_O = (2.0 * res[2][2]) / (2.0 * res[2][2] + res[2][0] + res[2][1] + res[0][2] + res[1][2]);
	double f1 = (f1_N + f1_A + f1_O) / 3.0;

	cout << "f1_N = " << f1_N << "\n";
	cout << "f1_A = " << f1_A << "\n";
	cout << "f1_O = " << f1_O << "\n";
	cout << "f1 = " << f1 << "\n";
}

void SolverForNN::test2()
{
	vector <vector <int> > res;
	double f1_N, f1_A, f1_O, f1_Noi;
	double f1;
	double aa, bb, cc, dd;

	res = tree1();
	cout << "((N vs AF) vs O) vs noisy\n";
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << res[i][j] << "\t";
		}
		cout << "\n";
	}
	f1_N = (2.0 * res[0][0]) / (2.0 * res[0][0] + res[0][1] + res[0][2] + res[0][3] + res[1][0] + res[2][0] + res[3][0]);
	f1_A = (2.0 * res[1][1]) / (2.0 * res[1][1] + res[1][0] + res[1][2] + res[1][3] + res[0][1] + res[2][1] + res[3][1]);
	f1_O = (2.0 * res[2][2]) / (2.0 * res[2][2] + res[2][0] + res[2][1] + res[2][3] + res[0][2] + res[1][2] + res[3][2]);
	f1_Noi = (2.0 * res[3][3]) / (2.0 * res[3][3] + res[3][0] + res[3][1] + res[3][2] + res[0][3] + res[1][3] + res[2][3]);
	f1 = (f1_N + f1_A + f1_O) / 3.0;

	/*
	aa = res[0][0] + res[0][1] + res[0][2] + res[1][0] + res[1][1] + res[1][2] + res[2][0] + res[2][1] + res[2][2];
	bb = res[3][0] + res[3][1] + res[3][2];
	cc = res[0][3] + res[1][3] + res[2][3];
	dd = res[3][3];
	f1_Noi = (aa + dd) / (aa + dd + bb + cc);
	//*/

	cout << "f1_N = " << f1_N << "  f1_A = " << f1_A << "  f1_O = " << f1_O << "  f1_Noi = " << f1_Noi << "\n";
	cout << "F1 = " << f1 << "\n\n\n";


	res = tree2();
	cout << "((N vs O) vs AF) vs noisy\n";
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << res[i][j] << "\t";
		}
		cout << "\n";
	}
	f1_N = (2.0 * res[0][0]) / (2.0 * res[0][0] + res[0][1] + res[0][2] + res[0][3] + res[1][0] + res[2][0] + res[3][0]);
	f1_A = (2.0 * res[1][1]) / (2.0 * res[1][1] + res[1][0] + res[1][2] + res[1][3] + res[0][1] + res[2][1] + res[3][1]);
	f1_O = (2.0 * res[2][2]) / (2.0 * res[2][2] + res[2][0] + res[2][1] + res[2][3] + res[0][2] + res[1][2] + res[3][2]);
	f1_Noi = (2.0 * res[3][3]) / (2.0 * res[3][3] + res[3][0] + res[3][1] + res[3][2] + res[0][3] + res[1][3] + res[2][3]);
	f1 = (f1_N + f1_A + f1_O) / 3.0;
	cout << "f1_N = " << f1_N << "  f1_A = " << f1_A << "  f1_O = " << f1_O << "  f1_Noi = " << f1_Noi << "\n";
	cout << "F1 = " << f1 << "\n\n\n";

	
	res = tree3();
	cout << "((AF vs O) vs N) vs noisy\n";
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << res[i][j] << "\t";
		}
		cout << "\n";
	}
	f1_N = (2.0 * res[0][0]) / (2.0 * res[0][0] + res[0][1] + res[0][2] + res[0][3] + res[1][0] + res[2][0] + res[3][0]);
	f1_A = (2.0 * res[1][1]) / (2.0 * res[1][1] + res[1][0] + res[1][2] + res[1][3] + res[0][1] + res[2][1] + res[3][1]);
	f1_O = (2.0 * res[2][2]) / (2.0 * res[2][2] + res[2][0] + res[2][1] + res[2][3] + res[0][2] + res[1][2] + res[3][2]);
	f1_Noi = (2.0 * res[3][3]) / (2.0 * res[3][3] + res[3][0] + res[3][1] + res[3][2] + res[0][3] + res[1][3] + res[2][3]);
	f1 = (f1_N + f1_A + f1_O) / 3.0;
	cout << "f1_N = " << f1_N << "  f1_A = " << f1_A << "  f1_O = " << f1_O << "  f1_Noi = " << f1_Noi << "\n";
	cout << "F1 = " << f1 << "\n\n\n";


	res = tree4();
	cout << "(N vs AF vs O) vs noisy\n";
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << res[i][j] << "\t";
		}
		cout << "\n";
	}
	f1_N = (2.0 * res[0][0]) / (2.0 * res[0][0] + res[0][1] + res[0][2] + res[0][3] + res[1][0] + res[2][0] + res[3][0]);
	f1_A = (2.0 * res[1][1]) / (2.0 * res[1][1] + res[1][0] + res[1][2] + res[1][3] + res[0][1] + res[2][1] + res[3][1]);
	f1_O = (2.0 * res[2][2]) / (2.0 * res[2][2] + res[2][0] + res[2][1] + res[2][3] + res[0][2] + res[1][2] + res[3][2]);
	f1_Noi = (2.0 * res[3][3]) / (2.0 * res[3][3] + res[3][0] + res[3][1] + res[3][2] + res[0][3] + res[1][3] + res[2][3]);
	f1 = (f1_N + f1_A + f1_O) / 3.0;
	cout << "f1_N = " << f1_N << "  f1_A = " << f1_A << "  f1_O = " << f1_O << "  f1_Noi = " << f1_Noi << "\n";
	cout << "F1 = " << f1 << "\n\n\n";
}

pair<double, double> SolverForNN::split2(string s)
{
	int split;
	string s1, s2;

	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == ',')
		{
			split = i;
		}
	}

	s1 = s.substr(0, split);
	s2 = s.substr(split + 1, s.size() - split - 1);

	istringstream os1(s1);
	double v1;
	os1 >> v1;

	istringstream os2(s2);
	double v2;
	os2 >> v2;

	return { v1, v2 };
}

pair<pair<double, double>, double> SolverForNN::split3(string s)
{
	vector <int> split;
	string s1, s2, s3;

	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == ',')
		{
			split.push_back(i);
		}
	}

	s1 = s.substr(0, split[0]);
	s2 = s.substr(split[0] + 1, split[1] - split[0] - 1);
	s3 = s.substr(split[1] + 1, s.size() - split[1] - 1);

	istringstream os1(s1);
	double v1;
	os1 >> v1;

	istringstream os2(s2);
	double v2;
	os2 >> v2;

	istringstream os3(s3);
	double v3;
	os3 >> v3;

	return { {v1, v2}, v3 };
}

int SolverForNN::p_classify0_filtered(vector <pair<double, double> >& types)
{
	double prb0 = 1.0, prb1 = 1.0;

	for (auto it : types)
	{
		prb0 *= it.first;
		prb1 *= it.second;
	}

	if (prb1 * pow(0.7, types.size()) > prb0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int SolverForNN::p_classify0_unfiltered(vector <pair<double, double>>& types)
{
	double prb0 = 1.0, prb1 = 1.0;

	for (auto it : types)
	{
		prb0 *= it.first;
		prb1 *= it.second;
	}

	if (prb1 * pow(1.4, types.size()) > prb0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int SolverForNN::p_classify1_AFO_vs_N(vector <pair<double, double>>& types)
{
	double prb0 = 1.0, prb1 = 1.0;

	for (auto it : types)
	{
		prb0 *=	it.first;
		prb1 *= it.second;
	}

	if (prb1 > prb0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int SolverForNN::p_classify1_NAF_vs_O(vector <pair<double, double>>& types)
{
	double sum0 = 0.0, sum1 = 0.0;

	for (auto it : types)
	{
		sum0 += (it.first > it.second);
		sum1 += (it.second > it.first);
	}

	if (sum1 > types.size() * 0.2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int SolverForNN::p_classify1_NO_vs_AF(vector <pair<double, double>>& types)
{
	double prb0 = 1.0, prb1 = 1.0;

	for (auto it : types)
	{
		prb0 *= it.first;
		prb1 *= it.second;
	}

	if (prb1 * pow(0.6, types.size()) > prb0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int SolverForNN::p_classify2_AF_vs_O(vector <pair<double, double>>& types)
{
	double prb0 = 1.0, prb1 = 1.0;

	for (auto it : types)
	{
		prb0 *= it.first;
		prb1 *= it.second;
	}

	if (prb1 > prb0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int SolverForNN::p_classify2_N_vs_AF(vector <pair<double, double>>& types)
{
	double prb0 = 1.0, prb1 = 1.0;

	for (auto it : types)
	{
		prb0 *= it.first;
		prb1 *= it.second;
	}

	if (prb1 > prb0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int SolverForNN::p_classify2_N_vs_O(vector <pair<double, double>>& types)
{
	double prb0 = 1.0, prb1 = 1.0;

	for (auto it : types)
	{
		prb0 *= it.first;
		prb1 *= it.second;
	}

	if (prb1 > prb0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int SolverForNN::p_classify1_N_vs_AF_vs_O(vector <pair<pair<double, double>, double> >& types)
{
	double prb0 = 1.0, prb1 = 1.0, prb2 = 1.0;

	for (auto it : types)
	{
		prb0 *= it.first.first;
		prb1 *= it.first.second;
		prb2 *= it.second;
	}

	if (prb0 > prb1 && prb0 > prb2 * pow(1.15, types.size()))
	{
		return 0;
	}
	else
	{
		if (prb1 > prb2 * pow(1.2, types.size()))
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
}

void SolverForNN::p_test1_1()
{
	map<string, vector <pair<double, double> > > inf;

	{
		ifstream inType("../../../../NonGitData/NormalClasification/ClassifResProb/0_noise_unfiltered_probability_model.txt");
		ifstream inName("../../../../NonGitData/NormalClasification/ClassifResProb/0_nameUnfilteredForTrainedModel.txt");

		string name;
		string type;

		while (inName >> name)
		{
			inType >> type;

			inf[name].push_back(split2(type));
		}
	}

	int res[2][2] = { {0, 0}, {0, 0} };

	for (auto& it : inf)
	{
		/*
		if (ECG::reference[it.first] == '~')
		{
			continue;
		}
		//*/

		int f = p_classify0_unfiltered(it.second);
		int ff = ECG::reference[it.first] == '~';

		res[ff][f]++;
	}

	cout << res[0][0] << " " << res[0][1] << "\n";
	cout << res[1][0] << " " << res[1][1] << "\n";

	double f1_0 = (2.0 * res[0][0]) / (2.0 * res[0][0] + res[1][0] + res[0][1]);
	double f1_1 = (2.0 * res[1][1]) / (2.0 * res[1][1] + res[1][0] + res[0][1]);
	double f1 = (f1_0 + f1_1) / 2.0;

	cout << "f1_0 = " << f1_0 << "\n";
	cout << "f1_1 = " << f1_1 << "\n";
	cout << "f1 = " << f1 << "\n";
}

void SolverForNN::p_test1_2()
{
	map<string, vector <pair<pair<double, double>, double> > > inf;

	{
		ifstream inType("../../../../NonGitData/NormalClasification/ClassifResProb/12_N_vs_AF_vs_O_probability_model.txt");
		ifstream inName("../../../../NonGitData/NormalClasification/ClassifResProb/1_2_nameScaledForTrainedModel.txt");

		string name;
		string type;

		while (inName >> name)
		{
			inType >> type;

			inf[name].push_back(split3(type));
		}
	}

	int res[3][3] = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };

	for (auto& it : inf)
	{
		if (ECG::reference[it.first] == '~')
		{
			continue;
		}

		int f = p_classify1_N_vs_AF_vs_O(it.second);
		int ff;
		if (ECG::reference[it.first] == 'N')
		{
			ff = 0;
		}
		else if (ECG::reference[it.first] == 'A')
		{
			ff = 1;
		}
		else
		{
			ff = 2;
		}

		res[ff][f]++;
	}

	cout << res[0][0] << "\t" << res[0][1] << "\t" << res[0][2] << "\n";
	cout << res[1][0] << "\t" << res[1][1] << "\t" << res[1][2] << "\n";
	cout << res[2][0] << "\t" << res[2][1] << "\t" << res[2][2] << "\n";

	double f1_N = (2.0 * res[0][0]) / (2.0 * res[0][0] + res[1][0] + res[2][0] + res[0][1] + res[0][2]);
	double f1_A = (2.0 * res[1][1]) / (2.0 * res[1][1] + res[1][0] + res[1][2] + res[0][1] + res[2][1]);
	double f1_O = (2.0 * res[2][2]) / (2.0 * res[2][2] + res[2][0] + res[2][1] + res[0][2] + res[1][2]);
	double f1 = (f1_N + f1_A + f1_O) / 3.0;

	cout << "f1_N = " << f1_N << "\n";
	cout << "f1_A = " << f1_A << "\n";
	cout << "f1_O = " << f1_O << "\n";
	cout << "f1 = " << f1 << "\n";
}

vector <vector <int> > SolverForNN::p_tree1()
{
	// ((N vs AF) vs O) vs noisy

	map <string, vector <pair<double, double> > > infNonNoi_vs_Noi;
	map <string, vector <pair<double, double> > > infNAF_vs_O;
	map <string, vector <pair<double, double> > > infN_vs_AF;

	{
		string name;
		string type, type1, type2;

		ifstream inType0("../../../../NonGitData/NormalClasification/ClassifResProb/0_noise_unfiltered_probability_model.txt");
		ifstream inName0("../../../../NonGitData/NormalClasification/ClassifResProb/0_nameUnfilteredForTrainedModel.txt");

		while (inName0 >> name)
		{
			inType0 >> type;

			infNonNoi_vs_Noi[name].push_back(split2(type));
		}

		ifstream inType1("../../../../NonGitData/NormalClasification/ClassifResProb/1_NAF_vs_O_probability_model.txt");
		ifstream inType2("../../../../NonGitData/NormalClasification/ClassifResProb/2_N_vs_AF_probability_model.txt");
		ifstream inName1_2("../../../../NonGitData/NormalClasification/ClassifResProb/1_2_nameScaledForTrainedModel.txt");

		while (inName1_2 >> name)
		{
			inType1 >> type1;
			inType2 >> type2;

			infNAF_vs_O[name].push_back(split2(type1));
			infN_vs_AF[name].push_back(split2(type2));
		}
	}

	vector <vector <int> > res(4, vector <int>(4, 0));

	for (auto it : ECG::reference)
	{
		int realType, myType;
		if (it.second == 'N')
		{
			realType = 0;
		}
		else if (it.second == 'A')
		{
			realType = 1;
		}
		else if (it.second == 'O')
		{
			realType = 2;
		}
		else
		{
			realType = 3;
		}

		int class0 = p_classify0_unfiltered(infNonNoi_vs_Noi[it.first]);
		int class1 = p_classify1_NAF_vs_O(infNAF_vs_O[it.first]);
		int class2 = p_classify2_N_vs_AF(infN_vs_AF[it.first]);

		if (class0 == 1)
		{
			myType = 3;
		}
		else
		{
			if (class1 == 1)
			{
				myType = 2;
			}
			else
			{
				if (class2 == 1)
				{
					myType = 1;
				}
				else
				{
					myType = 0;
				}
			}
		}

		res[realType][myType]++;
	}

	return res;
}

vector <vector <int> > SolverForNN::p_tree2()
{
	// ((N vs O) vs AF) vs noisy

	map <string, vector <pair<double, double> > > infNonNoi_vs_Noi;
	map <string, vector <pair<double, double> > > infNO_vs_AF;
	map <string, vector <pair<double, double> > > infN_vs_O;

	{
		string name;
		string type, type1, type2;

		ifstream inType0("../../../../NonGitData/NormalClasification/ClassifResProb/0_noise_unfiltered_probability_model.txt");
		ifstream inName0("../../../../NonGitData/NormalClasification/ClassifResProb/0_nameUnfilteredForTrainedModel.txt");

		while (inName0 >> name)
		{
			inType0 >> type;

			infNonNoi_vs_Noi[name].push_back(split2(type));
		}

		ifstream inType1("../../../../NonGitData/NormalClasification/ClassifResProb/1_NO_vs_AF_probability_model.txt");
		ifstream inType2("../../../../NonGitData/NormalClasification/ClassifResProb/2_N_vs_O_probability_model.txt");
		ifstream inName1_2("../../../../NonGitData/NormalClasification/ClassifResProb/1_2_nameScaledForTrainedModel.txt");

		while (inName1_2 >> name)
		{
			inType1 >> type1;
			inType2 >> type2;

			infNO_vs_AF[name].push_back(split2(type1));
			infN_vs_O[name].push_back(split2(type2));
		}
	}

	vector <vector <int> > res(4, vector <int>(4, 0));

	for (auto it : ECG::reference)
	{
		int realType, myType;
		if (it.second == 'N')
		{
			realType = 0;
		}
		else if (it.second == 'A')
		{
			realType = 1;
		}
		else if (it.second == 'O')
		{
			realType = 2;
		}
		else
		{
			realType = 3;
		}

		int class0 = p_classify0_unfiltered(infNonNoi_vs_Noi[it.first]);
		int class1 = p_classify1_NO_vs_AF(infNO_vs_AF[it.first]);
		int class2 = p_classify2_N_vs_O(infN_vs_O[it.first]);

		if (class0 == 1)
		{
			myType = 3;
		}
		else
		{
			if (class1 == 1)
			{
				myType = 1;
			}
			else
			{
				if (class2 == 1)
				{
					myType = 2;
				}
				else
				{
					myType = 0;
				}
			}
		}

		res[realType][myType]++;
	}

	return res;
}

vector <vector <int> > SolverForNN::p_tree3()
{
	// ((AF vs O) vs N) vs noisy

	map <string, vector <pair<double, double> > > infNonNoi_vs_Noi;
	map <string, vector <pair<double, double> > > infAFO_vs_N;
	map <string, vector <pair<double, double> > > infAF_vs_O;

	{
		string name;
		string type, type1, type2;

		ifstream inType0("../../../../NonGitData/NormalClasification/ClassifResProb/0_noise_unfiltered_probability_model.txt");
		ifstream inName0("../../../../NonGitData/NormalClasification/ClassifResProb/0_nameUnfilteredForTrainedModel.txt");

		while (inName0 >> name)
		{
			inType0 >> type;

			infNonNoi_vs_Noi[name].push_back(split2(type));
		}

		ifstream inType1("../../../../NonGitData/NormalClasification/ClassifResProb/1_AFO_vs_N_probability_model.txt");
		ifstream inType2("../../../../NonGitData/NormalClasification/ClassifResProb/2_AF_vs_O_probability_model.txt");
		ifstream inName1_2("../../../../NonGitData/NormalClasification/ClassifResProb/1_2_nameScaledForTrainedModel.txt");

		while (inName1_2 >> name)
		{
			inType1 >> type1;
			inType2 >> type2;

			infAFO_vs_N[name].push_back(split2(type1));
			infAF_vs_O[name].push_back(split2(type2));
		}
	}

	vector <vector <int> > res(4, vector <int>(4, 0));

	for (auto it : ECG::reference)
	{
		int realType, myType;
		if (it.second == 'N')
		{
			realType = 0;
		}
		else if (it.second == 'A')
		{
			realType = 1;
		}
		else if (it.second == 'O')
		{
			realType = 2;
		}
		else
		{
			realType = 3;
		}

		int class0 = p_classify0_unfiltered(infNonNoi_vs_Noi[it.first]);
		int class1 = p_classify1_AFO_vs_N(infAFO_vs_N[it.first]);
		int class2 = p_classify2_AF_vs_O(infAF_vs_O[it.first]);

		if (class0 == 1)
		{
			myType = 3;
		}
		else
		{
			if (class1 == 1)
			{
				myType = 0;
			}
			else
			{
				if (class2 == 1)
				{
					myType = 2;
				}
				else
				{
					myType = 1;
				}
			}
		}

		res[realType][myType]++;
	}

	return res;
}

vector <vector <int> > SolverForNN::p_tree4()
{
	// (N vs AF vs O) vs noisy

	map <string, vector <pair<double, double> > > infNonNoi_vs_Noi;
	map <string, vector <pair<pair<double, double>, double> > > infN_vs_N_vs_O;

	{
		string name;
		string type, type1;

		ifstream inType0("../../../../NonGitData/NormalClasification/ClassifResProb/0_noise_unfiltered_probability_model.txt");
		ifstream inName0("../../../../NonGitData/NormalClasification/ClassifResProb/0_nameUnfilteredForTrainedModel.txt");

		while (inName0 >> name)
		{
			inType0 >> type;

			infNonNoi_vs_Noi[name].push_back(split2(type));
		}

		ifstream inType1("../../../../NonGitData/NormalClasification/ClassifResProb/12_N_vs_AF_vs_O_probability_model.txt");
		ifstream inName1_2("../../../../NonGitData/NormalClasification/ClassifResProb/1_2_nameScaledForTrainedModel.txt");

		while (inName1_2 >> name)
		{
			inType1 >> type1;

			infN_vs_N_vs_O[name].push_back(split3(type1));
		}
	}

	vector <vector <int> > res(4, vector <int>(4, 0));

	for (auto it : ECG::reference)
	{
		int realType, myType;
		if (it.second == 'N')
		{
			realType = 0;
		}
		else if (it.second == 'A')
		{
			realType = 1;
		}
		else if (it.second == 'O')
		{
			realType = 2;
		}
		else
		{
			realType = 3;
		}

		int class0 = p_classify0_unfiltered(infNonNoi_vs_Noi[it.first]);
		int class1 = p_classify1_N_vs_AF_vs_O(infN_vs_N_vs_O[it.first]);

		if (class0 == 1)
		{
			myType = 3;
		}
		else
		{
			myType = class1;
		}

		res[realType][myType]++;
	}

	return res;
}

void SolverForNN::p_test2()
{
	vector <vector <int> > res;
	double f1_N, f1_A, f1_O, f1_Noi;
	double f1;
	double aa, bb, cc, dd;

	res = p_tree1();
	cout << "((N vs AF) vs O) vs noisy\n";
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << res[i][j] << "\t";
		}
		cout << "\n";
	}
	f1_N = (2.0 * res[0][0]) / (2.0 * res[0][0] + res[0][1] + res[0][2] + res[0][3] + res[1][0] + res[2][0] + res[3][0]);
	f1_A = (2.0 * res[1][1]) / (2.0 * res[1][1] + res[1][0] + res[1][2] + res[1][3] + res[0][1] + res[2][1] + res[3][1]);
	f1_O = (2.0 * res[2][2]) / (2.0 * res[2][2] + res[2][0] + res[2][1] + res[2][3] + res[0][2] + res[1][2] + res[3][2]);
	f1_Noi = (2.0 * res[3][3]) / (2.0 * res[3][3] + res[3][0] + res[3][1] + res[3][2] + res[0][3] + res[1][3] + res[2][3]);
	f1 = (f1_N + f1_A + f1_O) / 3.0;

	//*
	aa = res[0][0] + res[0][1] + res[0][2] + res[1][0] + res[1][1] + res[1][2] + res[2][0] + res[2][1] + res[2][2];
	bb = res[3][0] + res[3][1] + res[3][2];
	cc = res[0][3] + res[1][3] + res[2][3];
	dd = res[3][3];
	f1_Noi = (aa + dd) / (aa + dd + bb + cc);
	//*/

	cout << "f1_N = " << f1_N << "  f1_A = " << f1_A << "  f1_O = " << f1_O << "  f1_Noi = " << f1_Noi << "\n";
	cout << "F1 = " << f1 << "\n\n\n";


	res = p_tree2();
	cout << "((N vs O) vs AF) vs noisy\n";
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << res[i][j] << "\t";
		}
		cout << "\n";
	}
	f1_N = (2.0 * res[0][0]) / (2.0 * res[0][0] + res[0][1] + res[0][2] + res[0][3] + res[1][0] + res[2][0] + res[3][0]);
	f1_A = (2.0 * res[1][1]) / (2.0 * res[1][1] + res[1][0] + res[1][2] + res[1][3] + res[0][1] + res[2][1] + res[3][1]);
	f1_O = (2.0 * res[2][2]) / (2.0 * res[2][2] + res[2][0] + res[2][1] + res[2][3] + res[0][2] + res[1][2] + res[3][2]);
	f1_Noi = (2.0 * res[3][3]) / (2.0 * res[3][3] + res[3][0] + res[3][1] + res[3][2] + res[0][3] + res[1][3] + res[2][3]);
	f1 = (f1_N + f1_A + f1_O) / 3.0;
	cout << "f1_N = " << f1_N << "  f1_A = " << f1_A << "  f1_O = " << f1_O << "  f1_Noi = " << f1_Noi << "\n";
	cout << "F1 = " << f1 << "\n\n\n";


	res = p_tree3();
	cout << "((AF vs O) vs N) vs noisy\n";
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << res[i][j] << "\t";
		}
		cout << "\n";
	}
	f1_N = (2.0 * res[0][0]) / (2.0 * res[0][0] + res[0][1] + res[0][2] + res[0][3] + res[1][0] + res[2][0] + res[3][0]);
	f1_A = (2.0 * res[1][1]) / (2.0 * res[1][1] + res[1][0] + res[1][2] + res[1][3] + res[0][1] + res[2][1] + res[3][1]);
	f1_O = (2.0 * res[2][2]) / (2.0 * res[2][2] + res[2][0] + res[2][1] + res[2][3] + res[0][2] + res[1][2] + res[3][2]);
	f1_Noi = (2.0 * res[3][3]) / (2.0 * res[3][3] + res[3][0] + res[3][1] + res[3][2] + res[0][3] + res[1][3] + res[2][3]);
	f1 = (f1_N + f1_A + f1_O) / 3.0;
	cout << "f1_N = " << f1_N << "  f1_A = " << f1_A << "  f1_O = " << f1_O << "  f1_Noi = " << f1_Noi << "\n";
	cout << "F1 = " << f1 << "\n\n\n";


	res = p_tree4();
	cout << "(N vs AF vs O) vs noisy\n";
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << res[i][j] << "\t";
		}
		cout << "\n";
	}
	f1_N = (2.0 * res[0][0]) / (2.0 * res[0][0] + res[0][1] + res[0][2] + res[0][3] + res[1][0] + res[2][0] + res[3][0]);
	f1_A = (2.0 * res[1][1]) / (2.0 * res[1][1] + res[1][0] + res[1][2] + res[1][3] + res[0][1] + res[2][1] + res[3][1]);
	f1_O = (2.0 * res[2][2]) / (2.0 * res[2][2] + res[2][0] + res[2][1] + res[2][3] + res[0][2] + res[1][2] + res[3][2]);
	f1_Noi = (2.0 * res[3][3]) / (2.0 * res[3][3] + res[3][0] + res[3][1] + res[3][2] + res[0][3] + res[1][3] + res[2][3]);
	f1 = (f1_N + f1_A + f1_O) / 3.0;
	cout << "f1_N = " << f1_N << "  f1_A = " << f1_A << "  f1_O = " << f1_O << "  f1_Noi = " << f1_Noi << "\n";
	cout << "F1 = " << f1 << "\n\n\n";
}