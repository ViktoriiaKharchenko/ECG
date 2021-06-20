#include "SolverForNN2.h"

void SolverForNN2::makeClassificationData()
{
	ofstream out("../../../../NonGitData/Class2/FullDataset.txt");
	ofstream outScale("../../../../NonGitData/Class2/ScaleFullDataset.txt");
	ofstream outName("../../../../NonGitData/Class2/NameFullDataset.txt");

	for (auto it : ECG::reference)
	{
		cout << it.first << "\n";

		ECG ecg;

		ecg.readFromFile("../../../Data/TXTFiltered/" + it.first + ".txt");
		vector <int> rPeaks = ecg.getRPeaks(0, ecg.data.size());

		for (int i = 4; i < rPeaks.size(); i += 4)
		{
			vector <double> data[4];
			for (int ci = 0; ci < 4; ci++)
			{
				for (int j = rPeaks[i - 4 + ci]; j < rPeaks[i - 3 + ci]; j++)
				{
					data[ci].push_back(ecg.data[j]);
				}
			}

			vector <double> scaledData[4];
			for (int ci = 0; ci < 4; ci++)
			{
				scaledData[ci] = ECG::rescale(data[ci], 225);
			}

			for (int ci = 0; ci < 4; ci++)
			{
				scaledData[ci] = ECG::rescale(data[ci], 225);

				if (ci == 0)
				{
					outScale << double(data[ci].size()) / scaledData[ci].size();
				}
				else
				{
					outScale << " " << double(data[ci].size()) / scaledData[ci].size();
				}

				for (int j = 0; j < scaledData[ci].size(); j++)
				{
					if (ci == 0 && j == 0)
					{
						out << scaledData[ci][j];
					}
					else
					{
						out << " " << scaledData[ci][j];
					}
				}
			}
			out << "\n";
			outScale << "\n";

			outName << it.first << "\n";
		}
	}
}

void SolverForNN2::makeDataForNvsAF()
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

	ofstream out("../../../../NonGitData/Class2/N_vs_AF/dataN_AF.txt");
	ofstream outScale("../../../../NonGitData/Class2/N_vs_AF/scaleN_AF.txt");
	ofstream out2("../../../../NonGitData/Class2/N_vs_AF/typeN_AF.txt");
	ofstream outV("../../../../NonGitData/Class2/N_vs_AF/dataValidationN_AF.txt");
	ofstream outScaleV("../../../../NonGitData/Class2/N_vs_AF/scaleValidationN_AF.txt");
	ofstream out2V("../../../../NonGitData/Class2/N_vs_AF/typeValidationN_AF.txt");

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
				vector <double> data[4];
				for (int ci = 0; ci < 4; ci++)
				{
					for (int j = rPeaks[i - 4 + ci]; j < rPeaks[i - 3 + ci]; j++)
					{
						data[ci].push_back(ecg.data[j]);
					}
				}

				vector <double> scaledData[4];
				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);
				}

				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);

					if (ci == 0)
					{
						outScale << double(data[ci].size()) / scaledData[ci].size();
					}
					else
					{
						outScale << " " << double(data[ci].size()) / scaledData[ci].size();
					}

					for (int j = 0; j < scaledData[ci].size(); j++)
					{
						if (ci == 0 && j == 0)
						{
							out << scaledData[ci][j];
						}
						else
						{
							out << " " << scaledData[ci][j];
						}
					}
				}
				out << "\n";
				outScale << "\n";
				out2 << "0\n";
			}
		}
		else if (cntN < 840 + 600)
		{
			ecg.readFromFile("../../../Data/TXTFiltered/" + it + ".txt");
			vector <int> rPeaks = ecg.getRPeaks(0, ecg.data.size());

			for (int i = 4; i < rPeaks.size(); i += 4)
			{
				vector <double> data[4];
				for (int ci = 0; ci < 4; ci++)
				{
					for (int j = rPeaks[i - 4 + ci]; j < rPeaks[i - 3 + ci]; j++)
					{
						data[ci].push_back(ecg.data[j]);
					}
				}

				vector <double> scaledData[4];
				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);
				}

				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);

					if (ci == 0)
					{
						outScaleV << double(data[ci].size()) / scaledData[ci].size();
					}
					else
					{
						outScaleV << " " << double(data[ci].size()) / scaledData[ci].size();
					}

					for (int j = 0; j < scaledData[ci].size(); j++)
					{
						if (ci == 0 && j == 0)
						{
							outV << scaledData[ci][j];
						}
						else
						{
							outV << " " << scaledData[ci][j];
						}
					}
				}
				outV << "\n";
				outScaleV << "\n";
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
				vector <double> data[4];
				for (int ci = 0; ci < 4; ci++)
				{
					for (int j = rPeaks[i - 4 + ci]; j < rPeaks[i - 3 + ci]; j++)
					{
						data[ci].push_back(ecg.data[j]);
					}
				}

				vector <double> scaledData[4];
				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);
				}

				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);

					if (ci == 0)
					{
						outScale << double(data[ci].size()) / scaledData[ci].size();
					}
					else
					{
						outScale << " " << double(data[ci].size()) / scaledData[ci].size();
					}

					for (int j = 0; j < scaledData[ci].size(); j++)
					{
						if (ci == 0 && j == 0)
						{
							out << scaledData[ci][j];
						}
						else
						{
							out << " " << scaledData[ci][j];
						}
					}
				}
				out << "\n";
				outScale << "\n";
				out2 << "1\n";
			}
		}
		else if (cntA < 420 + 300)
		{
			ecg.readFromFile("../../../Data/TXTFiltered/" + it + ".txt");
			vector <int> rPeaks = ecg.getRPeaks(0, ecg.data.size());

			for (int i = 4; i < rPeaks.size(); i += 4)
			{
				vector <double> data[4];
				for (int ci = 0; ci < 4; ci++)
				{
					for (int j = rPeaks[i - 4 + ci]; j < rPeaks[i - 3 + ci]; j++)
					{
						data[ci].push_back(ecg.data[j]);
					}
				}

				vector <double> scaledData[4];
				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);
				}

				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);

					if (ci == 0)
					{
						outScaleV << double(data[ci].size()) / scaledData[ci].size();
					}
					else
					{
						outScaleV << " " << double(data[ci].size()) / scaledData[ci].size();
					}

					for (int j = 0; j < scaledData[ci].size(); j++)
					{
						if (ci == 0 && j == 0)
						{
							outV << scaledData[ci][j];
						}
						else
						{
							outV << " " << scaledData[ci][j];
						}
					}
				}
				outV << "\n";
				outScaleV << "\n";
				out2V << "1\n";
			}
		}

		cntA++;
	}
}

void SolverForNN2::makeDataForNvsO()
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

	ofstream out("../../../../NonGitData/Class2/N_vs_O/dataN_O.txt");
	ofstream outScale("../../../../NonGitData/Class2/N_vs_O/scaleN_O.txt");
	ofstream out2("../../../../NonGitData/Class2/N_vs_O/typeN_O.txt");
	ofstream outV("../../../../NonGitData/Class2/N_vs_O/dataValidationN_O.txt");
	ofstream outScaleV("../../../../NonGitData/Class2/N_vs_O/scaleValidationN_O.txt");
	ofstream out2V("../../../../NonGitData/Class2/N_vs_O/typeValidationN_O.txt");

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
				vector <double> data[4];
				for (int ci = 0; ci < 4; ci++)
				{
					for (int j = rPeaks[i - 4 + ci]; j < rPeaks[i - 3 + ci]; j++)
					{
						data[ci].push_back(ecg.data[j]);
					}
				}

				vector <double> scaledData[4];
				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);
				}

				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);

					if (ci == 0)
					{
						outScale << double(data[ci].size()) / scaledData[ci].size();
					}
					else
					{
						outScale << " " << double(data[ci].size()) / scaledData[ci].size();
					}

					for (int j = 0; j < scaledData[ci].size(); j++)
					{
						if (ci == 0 && j == 0)
						{
							out << scaledData[ci][j];
						}
						else
						{
							out << " " << scaledData[ci][j];
						}
					}
				}
				out << "\n";
				outScale << "\n";
				out2 << "0\n";
			}
		}
		else if (cntN < 2000 + 1000)
		{
			ecg.readFromFile("../../../Data/TXTFiltered/" + it + ".txt");
			vector <int> rPeaks = ecg.getRPeaks(0, ecg.data.size());

			for (int i = 4; i < rPeaks.size(); i += 4)
			{
				vector <double> data[4];
				for (int ci = 0; ci < 4; ci++)
				{
					for (int j = rPeaks[i - 4 + ci]; j < rPeaks[i - 3 + ci]; j++)
					{
						data[ci].push_back(ecg.data[j]);
					}
				}

				vector <double> scaledData[4];
				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);
				}

				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);

					if (ci == 0)
					{
						outScaleV << double(data[ci].size()) / scaledData[ci].size();
					}
					else
					{
						outScaleV << " " << double(data[ci].size()) / scaledData[ci].size();
					}

					for (int j = 0; j < scaledData[ci].size(); j++)
					{
						if (ci == 0 && j == 0)
						{
							outV << scaledData[ci][j];
						}
						else
						{
							outV << " " << scaledData[ci][j];
						}
					}
				}
				outV << "\n";
				outScaleV << "\n";
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
				vector <double> data[4];
				for (int ci = 0; ci < 4; ci++)
				{
					for (int j = rPeaks[i - 4 + ci]; j < rPeaks[i - 3 + ci]; j++)
					{
						data[ci].push_back(ecg.data[j]);
					}
				}

				vector <double> scaledData[4];
				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);
				}

				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);

					if (ci == 0)
					{
						outScale << double(data[ci].size()) / scaledData[ci].size();
					}
					else
					{
						outScale << " " << double(data[ci].size()) / scaledData[ci].size();
					}

					for (int j = 0; j < scaledData[ci].size(); j++)
					{
						if (ci == 0 && j == 0)
						{
							out << scaledData[ci][j];
						}
						else
						{
							out << " " << scaledData[ci][j];
						}
					}
				}
				out << "\n";
				outScale << "\n";
				out2 << "1\n";
			}
		}
		else if (cntO < 1200 + 800)
		{
			ecg.readFromFile("../../../Data/TXTFiltered/" + it + ".txt");
			vector <int> rPeaks = ecg.getRPeaks(0, ecg.data.size());

			for (int i = 4; i < rPeaks.size(); i += 4)
			{
				vector <double> data[4];
				for (int ci = 0; ci < 4; ci++)
				{
					for (int j = rPeaks[i - 4 + ci]; j < rPeaks[i - 3 + ci]; j++)
					{
						data[ci].push_back(ecg.data[j]);
					}
				}

				vector <double> scaledData[4];
				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);
				}

				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);

					if (ci == 0)
					{
						outScaleV << double(data[ci].size()) / scaledData[ci].size();
					}
					else
					{
						outScaleV << " " << double(data[ci].size()) / scaledData[ci].size();
					}

					for (int j = 0; j < scaledData[ci].size(); j++)
					{
						if (ci == 0 && j == 0)
						{
							outV << scaledData[ci][j];
						}
						else
						{
							outV << " " << scaledData[ci][j];
						}
					}
				}
				outV << "\n";
				outScaleV << "\n";
				out2V << "1\n";
			}
		}

		cntO++;
	}
}

void SolverForNN2::makeDataForAFvsO()
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

	ofstream out("../../../../NonGitData/Class2/AF_vs_O/dataAF_O.txt");
	ofstream outScale("../../../../NonGitData/Class2/AF_vs_O/scaleAF_O.txt");
	ofstream out2("../../../../NonGitData/Class2/AF_vs_O/typeAF_O.txt");
	ofstream outV("../../../../NonGitData/Class2/AF_vs_O/dataValidationAF_O.txt");
	ofstream outScaleV("../../../../NonGitData/Class2/AF_vs_O/scaleValidationAF_O.txt");
	ofstream out2V("../../../../NonGitData/Class2/AF_vs_O/typeValidationAF_O.txt");

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
				vector <double> data[4];
				for (int ci = 0; ci < 4; ci++)
				{
					for (int j = rPeaks[i - 4 + ci]; j < rPeaks[i - 3 + ci]; j++)
					{
						data[ci].push_back(ecg.data[j]);
					}
				}

				vector <double> scaledData[4];
				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);
				}

				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);

					if (ci == 0)
					{
						outScale << double(data[ci].size()) / scaledData[ci].size();
					}
					else
					{
						outScale << " " << double(data[ci].size()) / scaledData[ci].size();
					}

					for (int j = 0; j < scaledData[ci].size(); j++)
					{
						if (ci == 0 && j == 0)
						{
							out << scaledData[ci][j];
						}
						else
						{
							out << " " << scaledData[ci][j];
						}
					}
				}
				out << "\n";
				outScale << "\n";
				out2 << "0\n";
			}
		}
		else if (cntA < 400 + 300)
		{
			ecg.readFromFile("../../../Data/TXTFiltered/" + it + ".txt");
			vector <int> rPeaks = ecg.getRPeaks(0, ecg.data.size());

			for (int i = 4; i < rPeaks.size(); i += 4)
			{
				vector <double> data[4];
				for (int ci = 0; ci < 4; ci++)
				{
					for (int j = rPeaks[i - 4 + ci]; j < rPeaks[i - 3 + ci]; j++)
					{
						data[ci].push_back(ecg.data[j]);
					}
				}

				vector <double> scaledData[4];
				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);
				}

				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);

					if (ci == 0)
					{
						outScaleV << double(data[ci].size()) / scaledData[ci].size();
					}
					else
					{
						outScaleV << " " << double(data[ci].size()) / scaledData[ci].size();
					}

					for (int j = 0; j < scaledData[ci].size(); j++)
					{
						if (ci == 0 && j == 0)
						{
							outV << scaledData[ci][j];
						}
						else
						{
							outV << " " << scaledData[ci][j];
						}
					}
				}
				outV << "\n";
				outScaleV << "\n";
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
				vector <double> data[4];
				for (int ci = 0; ci < 4; ci++)
				{
					for (int j = rPeaks[i - 4 + ci]; j < rPeaks[i - 3 + ci]; j++)
					{
						data[ci].push_back(ecg.data[j]);
					}
				}

				vector <double> scaledData[4];
				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);
				}

				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);

					if (ci == 0)
					{
						outScale << double(data[ci].size()) / scaledData[ci].size();
					}
					else
					{
						outScale << " " << double(data[ci].size()) / scaledData[ci].size();
					}

					for (int j = 0; j < scaledData[ci].size(); j++)
					{
						if (ci == 0 && j == 0)
						{
							out << scaledData[ci][j];
						}
						else
						{
							out << " " << scaledData[ci][j];
						}
					}
				}
				out << "\n";
				outScale << "\n";
				out2 << "1\n";
			}
		}
		else if (cntO < 950 + 550)
		{
			ecg.readFromFile("../../../Data/TXTFiltered/" + it + ".txt");
			vector <int> rPeaks = ecg.getRPeaks(0, ecg.data.size());

			for (int i = 4; i < rPeaks.size(); i += 4)
			{
				vector <double> data[4];
				for (int ci = 0; ci < 4; ci++)
				{
					for (int j = rPeaks[i - 4 + ci]; j < rPeaks[i - 3 + ci]; j++)
					{
						data[ci].push_back(ecg.data[j]);
					}
				}

				vector <double> scaledData[4];
				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);
				}

				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);

					if (ci == 0)
					{
						outScaleV << double(data[ci].size()) / scaledData[ci].size();
					}
					else
					{
						outScaleV << " " << double(data[ci].size()) / scaledData[ci].size();
					}

					for (int j = 0; j < scaledData[ci].size(); j++)
					{
						if (ci == 0 && j == 0)
						{
							outV << scaledData[ci][j];
						}
						else
						{
							outV << " " << scaledData[ci][j];
						}
					}
				}
				outV << "\n";
				outScaleV << "\n";
				out2V << "1\n";
			}
		}

		cntO++;
	}
}

void SolverForNN2::makeDataForNAFvsO()
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

	ofstream out("../../../../NonGitData/Class2/NAF_vs_O/dataNAF_O.txt");
	ofstream outScale("../../../../NonGitData/Class2/NAF_vs_O/scaleNAF_O.txt");
	ofstream out2("../../../../NonGitData/Class2/NAF_vs_O/typeNAF_O.txt");
	ofstream outV("../../../../NonGitData/Class2/NAF_vs_O/dataValidationNAF_O.txt");
	ofstream outScaleV("../../../../NonGitData/Class2/NAF_vs_O/scaleValidationNAF_O.txt");
	ofstream out2V("../../../../NonGitData/Class2/NAF_vs_O/typeValidationNAF_O.txt");

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
				vector <double> data[4];
				for (int ci = 0; ci < 4; ci++)
				{
					for (int j = rPeaks[i - 4 + ci]; j < rPeaks[i - 3 + ci]; j++)
					{
						data[ci].push_back(ecg.data[j]);
					}
				}

				vector <double> scaledData[4];
				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);
				}

				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);

					if (ci == 0)
					{
						outScale << double(data[ci].size()) / scaledData[ci].size();
					}
					else
					{
						outScale << " " << double(data[ci].size()) / scaledData[ci].size();
					}

					for (int j = 0; j < scaledData[ci].size(); j++)
					{
						if (ci == 0 && j == 0)
						{
							out << scaledData[ci][j];
						}
						else
						{
							out << " " << scaledData[ci][j];
						}
					}
				}
				out << "\n";
				outScale << "\n";
				out2 << "0\n";
			}
		}
		else if (cntM < 1600 + 1100)
		{
			ecg.readFromFile("../../../Data/TXTFiltered/" + it + ".txt");
			vector <int> rPeaks = ecg.getRPeaks(0, ecg.data.size());

			for (int i = 4; i < rPeaks.size(); i += 4)
			{
				vector <double> data[4];
				for (int ci = 0; ci < 4; ci++)
				{
					for (int j = rPeaks[i - 4 + ci]; j < rPeaks[i - 3 + ci]; j++)
					{
						data[ci].push_back(ecg.data[j]);
					}
				}

				vector <double> scaledData[4];
				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);
				}

				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);

					if (ci == 0)
					{
						outScaleV << double(data[ci].size()) / scaledData[ci].size();
					}
					else
					{
						outScaleV << " " << double(data[ci].size()) / scaledData[ci].size();
					}

					for (int j = 0; j < scaledData[ci].size(); j++)
					{
						if (ci == 0 && j == 0)
						{
							outV << scaledData[ci][j];
						}
						else
						{
							outV << " " << scaledData[ci][j];
						}
					}
				}
				outV << "\n";
				outScaleV << "\n";
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
				vector <double> data[4];
				for (int ci = 0; ci < 4; ci++)
				{
					for (int j = rPeaks[i - 4 + ci]; j < rPeaks[i - 3 + ci]; j++)
					{
						data[ci].push_back(ecg.data[j]);
					}
				}

				vector <double> scaledData[4];
				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);
				}

				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);

					if (ci == 0)
					{
						outScale << double(data[ci].size()) / scaledData[ci].size();
					}
					else
					{
						outScale << " " << double(data[ci].size()) / scaledData[ci].size();
					}

					for (int j = 0; j < scaledData[ci].size(); j++)
					{
						if (ci == 0 && j == 0)
						{
							out << scaledData[ci][j];
						}
						else
						{
							out << " " << scaledData[ci][j];
						}
					}
				}
				out << "\n";
				outScale << "\n";
				out2 << "1\n";
			}
		}
		else if (cntO < 900 + 600)
		{
			ecg.readFromFile("../../../Data/TXTFiltered/" + it + ".txt");
			vector <int> rPeaks = ecg.getRPeaks(0, ecg.data.size());

			for (int i = 4; i < rPeaks.size(); i += 4)
			{
				vector <double> data[4];
				for (int ci = 0; ci < 4; ci++)
				{
					for (int j = rPeaks[i - 4 + ci]; j < rPeaks[i - 3 + ci]; j++)
					{
						data[ci].push_back(ecg.data[j]);
					}
				}

				vector <double> scaledData[4];
				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);
				}

				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);

					if (ci == 0)
					{
						outScaleV << double(data[ci].size()) / scaledData[ci].size();
					}
					else
					{
						outScaleV << " " << double(data[ci].size()) / scaledData[ci].size();
					}

					for (int j = 0; j < scaledData[ci].size(); j++)
					{
						if (ci == 0 && j == 0)
						{
							outV << scaledData[ci][j];
						}
						else
						{
							outV << " " << scaledData[ci][j];
						}
					}
				}
				outV << "\n";
				outScaleV << "\n";
				out2V << "1\n";
			}
		}

		cntO++;
	}
}

void SolverForNN2::makeDataForNOvsAF()
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

	ofstream out("../../../../NonGitData/Class2/NO_vs_AF/dataNO_AF.txt");
	ofstream outScale("../../../../NonGitData/Class2/NO_vs_AF/scaleNO_AF.txt");
	ofstream out2("../../../../NonGitData/Class2/NO_vs_AF/typeNO_AF.txt");
	ofstream outV("../../../../NonGitData/Class2/NO_vs_AF/dataValidationNO_AF.txt");
	ofstream outScaleV("../../../../NonGitData/Class2/NO_vs_AF/scaleValidationNO_AF.txt");
	ofstream out2V("../../../../NonGitData/Class2/NO_vs_AF/typeValidationNO_AF.txt");

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
				vector <double> data[4];
				for (int ci = 0; ci < 4; ci++)
				{
					for (int j = rPeaks[i - 4 + ci]; j < rPeaks[i - 3 + ci]; j++)
					{
						data[ci].push_back(ecg.data[j]);
					}
				}

				vector <double> scaledData[4];
				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);
				}

				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);

					if (ci == 0)
					{
						outScale << double(data[ci].size()) / scaledData[ci].size();
					}
					else
					{
						outScale << " " << double(data[ci].size()) / scaledData[ci].size();
					}

					for (int j = 0; j < scaledData[ci].size(); j++)
					{
						if (ci == 0 && j == 0)
						{
							out << scaledData[ci][j];
						}
						else
						{
							out << " " << scaledData[ci][j];
						}
					}
				}
				out << "\n";
				outScale << "\n";
				out2 << "0\n";
			}
		}
		else if (cntM < 800 + 600)
		{
			ecg.readFromFile("../../../Data/TXTFiltered/" + it + ".txt");
			vector <int> rPeaks = ecg.getRPeaks(0, ecg.data.size());

			for (int i = 4; i < rPeaks.size(); i += 4)
			{
				vector <double> data[4];
				for (int ci = 0; ci < 4; ci++)
				{
					for (int j = rPeaks[i - 4 + ci]; j < rPeaks[i - 3 + ci]; j++)
					{
						data[ci].push_back(ecg.data[j]);
					}
				}

				vector <double> scaledData[4];
				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);
				}

				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);

					if (ci == 0)
					{
						outScaleV << double(data[ci].size()) / scaledData[ci].size();
					}
					else
					{
						outScaleV << " " << double(data[ci].size()) / scaledData[ci].size();
					}

					for (int j = 0; j < scaledData[ci].size(); j++)
					{
						if (ci == 0 && j == 0)
						{
							outV << scaledData[ci][j];
						}
						else
						{
							outV << " " << scaledData[ci][j];
						}
					}
				}
				outV << "\n";
				outScaleV << "\n";
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
				vector <double> data[4];
				for (int ci = 0; ci < 4; ci++)
				{
					for (int j = rPeaks[i - 4 + ci]; j < rPeaks[i - 3 + ci]; j++)
					{
						data[ci].push_back(ecg.data[j]);
					}
				}

				vector <double> scaledData[4];
				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);
				}

				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);

					if (ci == 0)
					{
						outScale << double(data[ci].size()) / scaledData[ci].size();
					}
					else
					{
						outScale << " " << double(data[ci].size()) / scaledData[ci].size();
					}

					for (int j = 0; j < scaledData[ci].size(); j++)
					{
						if (ci == 0 && j == 0)
						{
							out << scaledData[ci][j];
						}
						else
						{
							out << " " << scaledData[ci][j];
						}
					}
				}
				out << "\n";
				outScale << "\n";
				out2 << "1\n";
			}
		}
		else if (cntA < 400 + 300)
		{
			ecg.readFromFile("../../../Data/TXTFiltered/" + it + ".txt");
			vector <int> rPeaks = ecg.getRPeaks(0, ecg.data.size());

			for (int i = 4; i < rPeaks.size(); i += 4)
			{
				vector <double> data[4];
				for (int ci = 0; ci < 4; ci++)
				{
					for (int j = rPeaks[i - 4 + ci]; j < rPeaks[i - 3 + ci]; j++)
					{
						data[ci].push_back(ecg.data[j]);
					}
				}

				vector <double> scaledData[4];
				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);
				}

				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);

					if (ci == 0)
					{
						outScaleV << double(data[ci].size()) / scaledData[ci].size();
					}
					else
					{
						outScaleV << " " << double(data[ci].size()) / scaledData[ci].size();
					}

					for (int j = 0; j < scaledData[ci].size(); j++)
					{
						if (ci == 0 && j == 0)
						{
							outV << scaledData[ci][j];
						}
						else
						{
							outV << " " << scaledData[ci][j];
						}
					}
				}
				outV << "\n";
				outScaleV << "\n";
				out2V << "1\n";
			}
		}

		cntA++;
	}
}

void SolverForNN2::makeDataForNvsAFO()
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

	ofstream out("../../../../NonGitData/Class2/N_vs_AFO/dataN_AFO.txt");
	ofstream outScale("../../../../NonGitData/Class2/N_vs_AFO/scaleN_AFO.txt");
	ofstream out2("../../../../NonGitData/Class2/N_vs_AFO/typeN_AFO.txt");
	ofstream outV("../../../../NonGitData/Class2/N_vs_AFO/dataValidationN_AFO.txt");
	ofstream outScaleV("../../../../NonGitData/Class2/N_vs_AFO/scaleValidationN_AFO.txt");
	ofstream out2V("../../../../NonGitData/Class2/N_vs_AFO/typeValidationN_AFO.txt");

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
	for (auto it : listN)
	{
		if (cntM > 1100 + 900)
		{
			continue;
		}

		cout << it << " N\n";
		ECG ecg;

		if (cntM < 1100)
		{
			ecg.readFromFile("../../../Data/TXTFiltered/" + it + ".txt");
			vector <int> rPeaks = ecg.getRPeaks(0, ecg.data.size());

			for (int i = 4; i < rPeaks.size(); i += 4)
			{
				vector <double> data[4];
				for (int ci = 0; ci < 4; ci++)
				{
					for (int j = rPeaks[i - 4 + ci]; j < rPeaks[i - 3 + ci]; j++)
					{
						data[ci].push_back(ecg.data[j]);
					}
				}

				vector <double> scaledData[4];
				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);
				}

				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);

					if (ci == 0)
					{
						outScale << double(data[ci].size()) / scaledData[ci].size();
					}
					else
					{
						outScale << " " << double(data[ci].size()) / scaledData[ci].size();
					}

					for (int j = 0; j < scaledData[ci].size(); j++)
					{
						if (ci == 0 && j == 0)
						{
							out << scaledData[ci][j];
						}
						else
						{
							out << " " << scaledData[ci][j];
						}
					}
				}
				out << "\n";
				outScale << "\n";
				out2 << "0\n";
			}
		}
		else if (cntM < 1100 + 900)
		{
			ecg.readFromFile("../../../Data/TXTFiltered/" + it + ".txt");
			vector <int> rPeaks = ecg.getRPeaks(0, ecg.data.size());

			for (int i = 4; i < rPeaks.size(); i += 4)
			{
				vector <double> data[4];
				for (int ci = 0; ci < 4; ci++)
				{
					for (int j = rPeaks[i - 4 + ci]; j < rPeaks[i - 3 + ci]; j++)
					{
						data[ci].push_back(ecg.data[j]);
					}
				}

				vector <double> scaledData[4];
				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);
				}

				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);

					if (ci == 0)
					{
						outScaleV << double(data[ci].size()) / scaledData[ci].size();
					}
					else
					{
						outScaleV << " " << double(data[ci].size()) / scaledData[ci].size();
					}

					for (int j = 0; j < scaledData[ci].size(); j++)
					{
						if (ci == 0 && j == 0)
						{
							outV << scaledData[ci][j];
						}
						else
						{
							outV << " " << scaledData[ci][j];
						}
					}
				}
				outV << "\n";
				outScaleV << "\n";
				out2V << "0\n";
			}
		}

		cntM++;
	}

	int cntN = 0;
	for (auto it : mix)
	{
		if (cntN > 1100 + 900)
		{
			continue;
		}

		cout << it << " AFO\n";
		ECG ecg;

		if (cntN < 1100)
		{
			ecg.readFromFile("../../../Data/TXTFiltered/" + it + ".txt");
			vector <int> rPeaks = ecg.getRPeaks(0, ecg.data.size());

			for (int i = 4; i < rPeaks.size(); i += 4)
			{
				vector <double> data[4];
				for (int ci = 0; ci < 4; ci++)
				{
					for (int j = rPeaks[i - 4 + ci]; j < rPeaks[i - 3 + ci]; j++)
					{
						data[ci].push_back(ecg.data[j]);
					}
				}

				vector <double> scaledData[4];
				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);
				}

				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);

					if (ci == 0)
					{
						outScale << double(data[ci].size()) / scaledData[ci].size();
					}
					else
					{
						outScale << " " << double(data[ci].size()) / scaledData[ci].size();
					}

					for (int j = 0; j < scaledData[ci].size(); j++)
					{
						if (ci == 0 && j == 0)
						{
							out << scaledData[ci][j];
						}
						else
						{
							out << " " << scaledData[ci][j];
						}
					}
				}
				out << "\n";
				outScale << "\n";
				out2 << "1\n";
			}
		}
		else if (cntN < 1100 + 900)
		{
			ecg.readFromFile("../../../Data/TXTFiltered/" + it + ".txt");
			vector <int> rPeaks = ecg.getRPeaks(0, ecg.data.size());

			for (int i = 4; i < rPeaks.size(); i += 4)
			{
				vector <double> data[4];
				for (int ci = 0; ci < 4; ci++)
				{
					for (int j = rPeaks[i - 4 + ci]; j < rPeaks[i - 3 + ci]; j++)
					{
						data[ci].push_back(ecg.data[j]);
					}
				}

				vector <double> scaledData[4];
				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);
				}

				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);

					if (ci == 0)
					{
						outScaleV << double(data[ci].size()) / scaledData[ci].size();
					}
					else
					{
						outScaleV << " " << double(data[ci].size()) / scaledData[ci].size();
					}

					for (int j = 0; j < scaledData[ci].size(); j++)
					{
						if (ci == 0 && j == 0)
						{
							outV << scaledData[ci][j];
						}
						else
						{
							outV << " " << scaledData[ci][j];
						}
					}
				}
				outV << "\n";
				outScaleV << "\n";
				out2V << "1\n";
			}
		}

		cntN++;
	}
}

void SolverForNN2::makeDataForNvsAFvsO()
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

	ofstream out("../../../../NonGitData/Class2/N_vs_AF_vs_O/dataN_AF_O.txt");
	ofstream outScale("../../../../NonGitData/Class2/N_vs_AF_vs_O/scaleN_AF_O.txt");
	ofstream out2("../../../../NonGitData/Class2/N_vs_AF_vs_O/typeN_AF_O.txt");
	ofstream outV("../../../../NonGitData/Class2/N_vs_AF_vs_O/dataValidationN_AF_O.txt");
	ofstream outScaleV("../../../../NonGitData/Class2/N_vs_AF_vs_O/scaleValidationN_AF_O.txt");
	ofstream out2V("../../../../NonGitData/Class2/N_vs_AF_vs_O/typeValidationN_AF_O.txt");

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
				vector <double> data[4];
				for (int ci = 0; ci < 4; ci++)
				{
					for (int j = rPeaks[i - 4 + ci]; j < rPeaks[i - 3 + ci]; j++)
					{
						data[ci].push_back(ecg.data[j]);
					}
				}

				vector <double> scaledData[4];
				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);
				}

				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);

					if (ci == 0)
					{
						outScale << double(data[ci].size()) / scaledData[ci].size();
					}
					else
					{
						outScale << " " << double(data[ci].size()) / scaledData[ci].size();
					}

					for (int j = 0; j < scaledData[ci].size(); j++)
					{
						if (ci == 0 && j == 0)
						{
							out << scaledData[ci][j];
						}
						else
						{
							out << " " << scaledData[ci][j];
						}
					}
				}
				out << "\n";
				outScale << "\n";
				out2 << "0\n";
			}
		}
		else if (cntN < 1000 + 800)
		{
			ecg.readFromFile("../../../Data/TXTFiltered/" + it + ".txt");
			vector <int> rPeaks = ecg.getRPeaks(0, ecg.data.size());

			for (int i = 4; i < rPeaks.size(); i += 4)
			{
				vector <double> data[4];
				for (int ci = 0; ci < 4; ci++)
				{
					for (int j = rPeaks[i - 4 + ci]; j < rPeaks[i - 3 + ci]; j++)
					{
						data[ci].push_back(ecg.data[j]);
					}
				}

				vector <double> scaledData[4];
				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);
				}

				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);

					if (ci == 0)
					{
						outScaleV << double(data[ci].size()) / scaledData[ci].size();
					}
					else
					{
						outScaleV << " " << double(data[ci].size()) / scaledData[ci].size();
					}

					for (int j = 0; j < scaledData[ci].size(); j++)
					{
						if (ci == 0 && j == 0)
						{
							outV << scaledData[ci][j];
						}
						else
						{
							outV << " " << scaledData[ci][j];
						}
					}
				}
				outV << "\n";
				outScaleV << "\n";
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
				vector <double> data[4];
				for (int ci = 0; ci < 4; ci++)
				{
					for (int j = rPeaks[i - 4 + ci]; j < rPeaks[i - 3 + ci]; j++)
					{
						data[ci].push_back(ecg.data[j]);
					}
				}

				vector <double> scaledData[4];
				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);
				}

				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);

					if (ci == 0)
					{
						outScale << double(data[ci].size()) / scaledData[ci].size();
					}
					else
					{
						outScale << " " << double(data[ci].size()) / scaledData[ci].size();
					}

					for (int j = 0; j < scaledData[ci].size(); j++)
					{
						if (ci == 0 && j == 0)
						{
							out << scaledData[ci][j];
						}
						else
						{
							out << " " << scaledData[ci][j];
						}
					}
				}
				out << "\n";
				outScale << "\n";
				out2 << "1\n";
			}
		}
		else if (cntA < 420 + 300)
		{
			ecg.readFromFile("../../../Data/TXTFiltered/" + it + ".txt");
			vector <int> rPeaks = ecg.getRPeaks(0, ecg.data.size());

			for (int i = 4; i < rPeaks.size(); i += 4)
			{
				vector <double> data[4];
				for (int ci = 0; ci < 4; ci++)
				{
					for (int j = rPeaks[i - 4 + ci]; j < rPeaks[i - 3 + ci]; j++)
					{
						data[ci].push_back(ecg.data[j]);
					}
				}

				vector <double> scaledData[4];
				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);
				}

				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);

					if (ci == 0)
					{
						outScaleV << double(data[ci].size()) / scaledData[ci].size();
					}
					else
					{
						outScaleV << " " << double(data[ci].size()) / scaledData[ci].size();
					}

					for (int j = 0; j < scaledData[ci].size(); j++)
					{
						if (ci == 0 && j == 0)
						{
							outV << scaledData[ci][j];
						}
						else
						{
							outV << " " << scaledData[ci][j];
						}
					}
				}
				outV << "\n";
				outScaleV << "\n";
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
				vector <double> data[4];
				for (int ci = 0; ci < 4; ci++)
				{
					for (int j = rPeaks[i - 4 + ci]; j < rPeaks[i - 3 + ci]; j++)
					{
						data[ci].push_back(ecg.data[j]);
					}
				}

				vector <double> scaledData[4];
				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);
				}

				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);

					if (ci == 0)
					{
						outScale << double(data[ci].size()) / scaledData[ci].size();
					}
					else
					{
						outScale << " " << double(data[ci].size()) / scaledData[ci].size();
					}

					for (int j = 0; j < scaledData[ci].size(); j++)
					{
						if (ci == 0 && j == 0)
						{
							out << scaledData[ci][j];
						}
						else
						{
							out << " " << scaledData[ci][j];
						}
					}
				}
				out << "\n";
				outScale << "\n";
				out2 << "2\n";
			}
		}
		else if (cntO < 800 + 600)
		{
			ecg.readFromFile("../../../Data/TXTFiltered/" + it + ".txt");
			vector <int> rPeaks = ecg.getRPeaks(0, ecg.data.size());

			for (int i = 4; i < rPeaks.size(); i += 4)
			{
				vector <double> data[4];
				for (int ci = 0; ci < 4; ci++)
				{
					for (int j = rPeaks[i - 4 + ci]; j < rPeaks[i - 3 + ci]; j++)
					{
						data[ci].push_back(ecg.data[j]);
					}
				}

				vector <double> scaledData[4];
				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);
				}

				for (int ci = 0; ci < 4; ci++)
				{
					scaledData[ci] = ECG::rescale(data[ci], 225);

					if (ci == 0)
					{
						outScaleV << double(data[ci].size()) / scaledData[ci].size();
					}
					else
					{
						outScaleV << " " << double(data[ci].size()) / scaledData[ci].size();
					}

					for (int j = 0; j < scaledData[ci].size(); j++)
					{
						if (ci == 0 && j == 0)
						{
							outV << scaledData[ci][j];
						}
						else
						{
							outV << " " << scaledData[ci][j];
						}
					}
				}
				outV << "\n";
				outScaleV << "\n";
				out2V << "2\n";
			}
		}

		cntO++;
	}
}