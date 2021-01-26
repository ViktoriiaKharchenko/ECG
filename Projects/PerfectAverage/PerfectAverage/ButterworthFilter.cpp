#include "ButterworthFilter.h"

void ButterworthFilter::setParameters(double TSample, double cutoffFrequency, int filterOrder)
{
	//TSample = 1.0; //
	//cutoffFrequency = 0.75; // 
	//filterOrder = 2; //

	// make analog filter

	double nominator;
	vector <double>	analogDenominatorPoly;

	if (filterOrder % 2 == 0)
	{
		analogDenominatorPoly.push_back(1.0);

		for (int k = 1; k <= filterOrder / 2; k++)
		{
			double a = 1.0, b = -2.0 * cos((2.0*k + filterOrder - 1.0) / (2.0 * filterOrder) * M_PI), c = 1.0;

			vector <double> analogDenominatorPoly2(analogDenominatorPoly.size() + 2, 0.0);

			for (int i = 0; i < analogDenominatorPoly.size(); i++)
			{
				analogDenominatorPoly2[i + 2] += a * analogDenominatorPoly[i];
				analogDenominatorPoly2[i + 1] += b * analogDenominatorPoly[i];
				analogDenominatorPoly2[i] += c * analogDenominatorPoly[i];
			}

			analogDenominatorPoly = analogDenominatorPoly2;
		}
	}
	else
	{
		analogDenominatorPoly.push_back(1.0);
		analogDenominatorPoly.push_back(1.0);

		for (int k = 1; k <= (filterOrder - 1) / 2; k++)
		{
			double a = 1.0, b = -2.0 * cos((2.0 * k + filterOrder - 1.0) / (2.0 * filterOrder) * M_PI), c = 1.0;

			vector <double> analogDenominatorPoly2(analogDenominatorPoly.size() + 2, 0.0);

			for (int i = 0; i < analogDenominatorPoly.size(); i++)
			{
				analogDenominatorPoly2[i + 2] += a * analogDenominatorPoly[i];
				analogDenominatorPoly2[i + 1] += b * analogDenominatorPoly[i];
				analogDenominatorPoly2[i] += c * analogDenominatorPoly[i];
			}

			analogDenominatorPoly = analogDenominatorPoly2;
		}
	}

	{
		double tDenomCoef = 1.0;

		for (int i = analogDenominatorPoly.size() - 1; i >= 0; i--)
		{
			analogDenominatorPoly[i] *= tDenomCoef;

			tDenomCoef *= cutoffFrequency;
		}

		nominator = tDenomCoef / cutoffFrequency;
	}

	for (auto& it : analogDenominatorPoly)
	{
		it /= nominator;
	}

	// billinear transform

	vector <double> BLTnominatorPoly, BLTdenominatorPoly;
	double BLTcoef = cutoffFrequency / tan(cutoffFrequency * TSample / 2.0);
	//double BLTcoef = 2.0 / TSample;

	vector <vector <double> > zp1Power(1), zm1Power(1);
	zp1Power[0].push_back(1.0);
	zm1Power[0].push_back(1.0);

	for (int i = 1; i <= filterOrder; i++)
	{
		zp1Power.push_back(vector <double>(zp1Power[i - 1].size() + 1, 0.0));
		zm1Power.push_back(vector <double>(zm1Power[i - 1].size() + 1, 0.0));

		for (int j = 0; j < zp1Power[i-1].size(); j++)
		{
			zp1Power[i][j + 1] += zp1Power[i - 1][j];
			zp1Power[i][j] += zp1Power[i - 1][j];

			zm1Power[i][j + 1] += zm1Power[i - 1][j];
			zm1Power[i][j] -= zm1Power[i - 1][j];
		}
	}

	BLTnominatorPoly = zp1Power[filterOrder];

	BLTdenominatorPoly.resize(filterOrder + 1, 0.0);

	double BLTcoefmult = 1;
	for (auto& it : analogDenominatorPoly)
	{
		it *= BLTcoefmult;

		BLTcoefmult *= BLTcoef;
	}

	for (int i = 0; i < analogDenominatorPoly.size(); i++)
	{
		for (int j1 = 0; j1 < zp1Power[filterOrder - i].size(); j1++)
		{
			for (int j2 = 0; j2 < zm1Power[i].size(); j2++)
			{
				BLTdenominatorPoly[j1 + j2] += analogDenominatorPoly[i] * zp1Power[filterOrder - i][j1] * zm1Power[i][j2];
			}
		}
	}

	double normalizer = BLTdenominatorPoly.back();

	for (auto it : BLTdenominatorPoly)
	{
		yCoefs.push_back(it / normalizer);
	}
	reverse(yCoefs.begin(), yCoefs.end());

	for (auto it : BLTnominatorPoly)
	{
		xCoefs.push_back(it / normalizer);
	}
	reverse(xCoefs.begin(), xCoefs.end());
}

vector <double> ButterworthFilter::filter(vector <double> x)
{
	vector <double> y;

	for (int i = 0; i < x.size(); i++)
	{
		double a = 0;
		for (int j = 0; i - j >= 0 && j < xCoefs.size(); j++)
		{
			if (j != 0)
			{
				a -= y[i - j] * yCoefs[j];
			}

			a += x[i - j] * xCoefs[j];
		}

		y.push_back(a);
	}

	return y;
}