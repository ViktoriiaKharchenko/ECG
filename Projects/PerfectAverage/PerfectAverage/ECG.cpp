#include "ECG.h"

ECG::ECG()
{
	drawingColor = Color::Black;
}

void ECG::initType()
{
	ifstream in("../../../Data/REFERENCE.txt");

	string name;
	char type;

	while (in >> name)
	{
		in >> type;

		reference[name] = type;
	}
}

map<string, char> ECG::reference = map<string, char>();

bool ECG::readFromFile(string path)
{
	ifstream in(path);

	if (!in.is_open())
	{
		return false;
	}

	data.clear();

	double val;
	while (in >> val)
	{
		data.push_back(val);
	}

	return true;
}

const int ECG::MaxPeakDuration = 16;
const int ECG::HalfPeakDuration = ECG::MaxPeakDuration / 2;

vector <double> ECG::transformPeaks1(int l, int r)
{
	int n = r - l;
	vector <double> subData = vector <double> (data.begin() + l, data.begin() + r);
	vector <double> prefMin, suffMin;
	vector <double> prefMax, suffMax;

	for (int i = 0; i < n; i++)
	{
		if (i % HalfPeakDuration == 0)
		{
			prefMin.push_back(subData[i]);
			prefMax.push_back(subData[i]);
		}
		else
		{
			prefMin.push_back(min(prefMin.back(), subData[i]));
			prefMax.push_back(max(prefMax.back(), subData[i]));
		}
	}

	suffMin.resize(n);
	suffMax.resize(n);
	suffMin[n - 1] = subData[n - 1];
	suffMax[n - 1] = subData[n - 1];

	for (int i = n - 2; i >= 0; i--)
	{
		if (i % HalfPeakDuration == HalfPeakDuration - 1)
		{
			suffMin[i] = subData[i];
			suffMax[i] = subData[i];
		}
		else
		{
			suffMin[i] = min(suffMin[i + 1], subData[i]);
			suffMax[i] = max(suffMax[i + 1], subData[i]);
		}
	}

	vector <double> transform;
	for (int i = 0; i < n; i++)
	{
		if (i < HalfPeakDuration || i + HalfPeakDuration >= n)
		{
			transform.push_back(0);
		}
		else
		{
			double minLeft = min(prefMin[i - 1], suffMin[i - HalfPeakDuration]), minRight = min(suffMin[i + 1], prefMin[i + HalfPeakDuration]);
			double maxLeft = max(prefMax[i - 1], suffMax[i - HalfPeakDuration]), maxRight = max(suffMax[i + 1], prefMax[i + HalfPeakDuration]);
			double val = max(abs(subData[i] - minLeft) + abs(subData[i] - minRight), abs(subData[i] - maxLeft) + abs(subData[i] - maxRight));

			transform.push_back(val);
		}
	}


	return transform;
}

vector <int> ECG::getRPeaks(int l, int r)
{
	vector <double> transform = transformPeaks1(l, r);
	vector <int> isPeak(r - l, 0);

	int windowSize = numbersPerSecond * 1.5;
	int windowShift = numbersPerSecond * 0.2;
	int minBeatTimeLeft = numbersPerSecond * 0.35;
	int minBeatTimeRight = numbersPerSecond * 0.25;
	int sameBeatPeackThreshold = numbersPerSecond * 0.2;

	for (int i = 0; i + windowSize <= r - l; i += windowShift)
	{
		vector <pair<double, int> > windowInf;

		for (int j = 0; j < windowSize; j++)
		{
			windowInf.push_back({ transform[i + j], i + j });
		}

		sort(windowInf.begin(), windowInf.end());

		double threshold = max(windowInf[windowInf.size() * 95 / 100].first, windowInf.back().first / 4.0);

		for (int j = windowInf.size() - 1; j >= 0; j--)
		{
			if (windowInf[j].first < threshold)
			{
				break;
			}

			isPeak[windowInf[j].second] = 1;
		}
	}

	for (int i = 0; i < r - l; i++)
	{
		if (isPeak[i] == 1)
		{
			double mx = 0;
			for (int j = max(0, i - minBeatTimeLeft); j < min(r - l, i + minBeatTimeRight); j++)
			{
				mx = max(mx, transform[j]);
			}

			if (transform[i] * 2 < mx)
			{
				isPeak[i] = 0;
			}
		}
	}

	for (int i = 0; i < r - l; i++)
	{
		if (isPeak[i] == 1)
		{
			int ost = sameBeatPeackThreshold;
			int j;

			for (j = i + 1; j < r - l; j++)
			{
				if (isPeak[j] == 1)
				{
					ost = sameBeatPeackThreshold;
				}
				else
				{
					ost--;

					if (ost == 0)
					{
						break;
					}
				}
			}

			int bestPos = i;

			for (int k = i; k <= j; k++)
			{
				isPeak[k] = 0;

				if (transform[k] > transform[bestPos])
				{
					bestPos = k;
				}
			}

			isPeak[bestPos] = 1;
		}
	}

	vector <int> peaks;
	for (int i = 0; i < r - l; i++)
	{
		if (isPeak[i] == 1)
		{
			peaks.push_back(i);
		}
	}

	return peaks;
}