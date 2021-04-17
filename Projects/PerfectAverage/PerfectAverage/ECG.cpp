#include "ECG.h"

ECG::ECG() : numbersPerSecond(300), MaxPeakDuration(18), HalfPeakDuration(9)
{
	drawingColor = Color::Black;
}

ECG::ECG(int _numbersPerSecond) : numbersPerSecond(_numbersPerSecond), MaxPeakDuration(int(0.06 * _numbersPerSecond / 2.0 + 0.5) * 2),
							HalfPeakDuration(int(0.06 * _numbersPerSecond / 2.0 + 0.5))
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

bool ECG::readFromFile2(string path)
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
		val *= 1000;
		data.push_back(val);
	}

	return true;
}

vector <double> ECG::averageFilter(vector <double> _data, int D)
{
	vector <double> pref;
	vector <double> res;

	int R = D / 2;

	pref.push_back(0.0);
	for (auto it : _data)
	{
		pref.push_back(pref.back() + it);
	}

	for (int i = 0; i < _data.size(); i++)
	{
		int l = max(i - R, 0), r = min(i + R, int(_data.size()) - 1);

		res.push_back((pref[r + 1] - pref[l]) / double(r - l + 1));
	}

	return res;
}

vector <double> ECG::medianFilter(vector <double> _data, int D)
{
	multiset<double> ls, rs;
	int l = 0, r = 0;
	int R = D / 2;

	vector <double> res;

	for (int i = 0; i < _data.size(); i++)
	{
		int tl = max(i - R, 0), tr = min(i + R, int(_data.size()) - 1);

		while (l < tl)
		{
			if (ls.find(_data[l]) != ls.end())
			{
				ls.erase(ls.find(_data[l]));
			}
			else
			{
				rs.erase(rs.find(_data[l]));
			}

			l++;
		}

		while (r <= tr)
		{
			if (rs.size() != 0 && _data[r] < (*rs.begin()))
			{
				ls.insert(_data[r]);
			}
			else
			{
				rs.insert(_data[r]);
			}

			r++;
		}

		while (ls.size() != rs.size() && ls.size() + 1 != rs.size())
		{
			if (ls.size() < rs.size())
			{
				ls.insert(*rs.begin());
				rs.erase(rs.begin());
			}
			else
			{
				rs.insert(*ls.rbegin());
				ls.erase(--ls.end());
			}
		}

		res.push_back(*rs.begin());
	}

	return res;
}

vector <double> ECG::rescale(vector <double> data, int size)
{
	data.push_back(data.back());

	vector <double> res;

	int n = data.size() - 2;
	size--;

	for (int i = 0; i <= size; i++)
	{
		int i1 = i * n / double(size), i2 = i1 + 1;
		double t = i / double(size), t1 = i1 / double(n), t2 = i2 / double(n);
		double dt1 = t - t1, dt2 = t2 - t, tSum = dt1 + dt2;

		dt1 /= tSum;
		dt2 /= tSum;

		res.push_back(data[i1] * dt2 + data[i2] * dt1);
	}

	return res;
}

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

vector <int> ECG::getRPeaks(int l, int r, double WSiseP, double WSiftP,
	double MBTLeftP, double MBTRightP, double SBPThresholdP)
{
	vector <double> transform = transformPeaks1(l, r);

	vector <int> isPeak(r - l, 0);

	int windowSize = numbersPerSecond * WSiseP; // 1.25, 1.5, 1.75, 2.0, 2.25
	int windowShift = numbersPerSecond * WSiftP; // 0.1, 0.2, 0.3, 0.45, 0.6, 0.8
	int minBeatTimeLeft = numbersPerSecond * MBTLeftP; // 0.27, 0.31, 0.35, 0.39, 0.43
	int minBeatTimeRight = numbersPerSecond * MBTRightP; // 0.2, 0.225, 0.25, 0.275, 0.3
	int sameBeatPeakThreshold = numbersPerSecond * SBPThresholdP; // 0.15, 0.2, 0.25, 0.3
	
	int n = r - l;
	int minBeatTimeSum = minBeatTimeLeft + minBeatTimeRight + 1;

	while (transform.size() % minBeatTimeSum != 0) { transform.push_back(0); }

	vector <double> transformMaxPref(transform.size()), transformMaxSuff(transform.size());
	transformMaxSuff[transform.size() - 1] = transform[transform.size() - 1];
	
	for (int i = 0; i < transform.size(); i++)
	{
		if (i % minBeatTimeSum == 0)
		{
			transformMaxPref[i] = transform[i];
		}
		else
		{
			transformMaxPref[i] = max(transformMaxPref[i - 1], transform[i]);
		}
	}
	for (int i = transform.size() - 2; i >= 0; i--)
	{
		if (i % minBeatTimeSum == minBeatTimeSum - 1)
		{
			transformMaxSuff[i] = transform[i];
		}
		else
		{
			transformMaxSuff[i] = max(transformMaxSuff[i + 1], transform[i]);
		}
	}

	for (int i = 0; i + windowSize <= n; i += windowShift)
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
			double mx;

			if (i - minBeatTimeLeft < 0)
			{
				mx = transformMaxPref[i + minBeatTimeRight];
			}
			else if (i + minBeatTimeRight >= n)
			{
				mx = transformMaxSuff[i - minBeatTimeLeft];
			}
			else
			{
				mx = max(transformMaxPref[i + minBeatTimeRight], transformMaxSuff[i - minBeatTimeLeft]);
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
			int ost = sameBeatPeakThreshold;
			int j;

			for (j = i + 1; j < n; j++)
			{
				if (isPeak[j] == 1)
				{
					ost = sameBeatPeakThreshold;
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

			if (j == n) 
			{
				j--;
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

			i = j;
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