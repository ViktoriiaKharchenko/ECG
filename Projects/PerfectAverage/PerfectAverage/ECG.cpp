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

vector <double> ECG::getRs1(int l, int r)
{
	const int MaxPeakDuration = 20;
	const int halfDuration = MaxPeakDuration / 2;

	int n = r - l;
	vector <double> subData = vector <double> (data.begin() + l, data.begin() + r);
	vector <double> prefMin, suffMin;
	vector <double> prefMax, suffMax;

	for (int i = 0; i < n; i++)
	{
		if (i % halfDuration == 0)
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
	for (int i = n - 1; i >= 0; i--)
	{
		if (i % halfDuration == halfDuration - 1)
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

	vector <double> peakValue;
	for (int i = halfDuration; i + halfDuration < n; i++)
	{
		//double minLeft = min(suffMin[i - 1], prefMin[i - halfDuration]), minRight = min(prefMin[i + 1], suffMin[i + halfDuration]);
		//double maxLeft = max(suffMax[i - 1], prefMax[i - halfDuration]), maxRight = max(prefMax[i + 1], suffMax[i + halfDuration]);
		double minLeft = min(prefMin[i - 1], suffMin[i - halfDuration]), minRight = min(suffMin[i + 1], prefMin[i + halfDuration]);
		double maxLeft = max(prefMax[i - 1], suffMax[i - halfDuration]), maxRight = max(suffMax[i + 1], prefMax[i + halfDuration]);
		double val = max(abs(subData[i] - minLeft) + abs(subData[i] - minRight), abs(subData[i] - maxLeft) + abs(subData[i] - maxRight));

		peakValue.push_back(val);
	}


	return peakValue;
}